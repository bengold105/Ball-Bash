#include "Player.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "HtMouse.h"
#include "HtGraphics.h"
#include "ObjectManager.h"
#include <iostream>
#include <cmath>
#include "Explosion.h"
#include "Tile.h"

const double MAX_LAUNCH_POWER = 500;

Player::Player() : GameObject(ObjectType::PLAYER) 
{
    m_reticle = nullptr;
    lastCollidedObject = nullptr;
    lockedControls = false;
    prepLaunch = false;
}

Player::~Player()
{
    m_reticle->Deactivate();
    m_reticle = nullptr;
}

void Player::Update(double frametime)
{
    //locks the controls until the player has slowed down enough
    lockedControls = true;

    UpdateMovement(frametime);
    if (soundPlayed) {
        soundDelay += 6*frametime;
    }
    if(soundDelay > 1){
        soundDelay = 0;
        soundPlayed = false;
    }

    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;

    if (!lockedControls) {
        if (HtMouse::instance.IsNewMouseDown(HtMouseButton::LEFT)) {
            HtMouse::instance.SetPointerPosition(852, 548);
            m_reticle->Activate(true);
            prepLaunch = true;
            //removes the tutorial hint after clicking
            if (!tutorialRemoved) {
                tutorialRemoved = true;
                Event event = Event();
                event.pSource = this;
                event.type = REMOVETUTORIAL;
                ObjectManager::instance.HandleEvent(event);
            }
        }
    }

    if (!HtMouse::instance.IsMouseDown(HtMouseButton::LEFT))
    {
        if (prepLaunch)
        {
            Launch();
        }
        prepLaunch = false;
        m_reticle->Activate(false);
    }
    if (prepLaunch)
    {
        m_angle =  direction.angle() + 180;
        m_reticle->SetForceVector(direction);
    }

    HtCamera::instance.PlaceAt(m_position);
    m_collisionShape.PlaceAt(m_position, 64);
    m_reticle->SetPosition(m_position);
}

void Player::Initialise(Vector2D spawn)
{
    SetDrawDepth(9);
    m_reticle = new PlayerReticle();
    m_reticle->Initialise();
    ObjectManager::instance.AddItem(m_reticle);
    m_position = spawn;
    m_scale = 2;
    m_velocity = Vector2D(0, 0);
    soundPlayed = false;
    soundDelay = 0;
    LoadImage("assets/basketballA1.png");
    LoadImage("assets/basketballA2.png");
    LoadImage("assets/basketballA3.png");
    LoadImage("assets/basketballA4.png");
    LoadImage("assets/basketballA5.png");
    LoadImage("assets/basketballA6.png");
    LoadImage("assets/basketballA7.png");
    LoadImage("assets/basketballA8.png");
    LoadImage("assets/basketballA9.png");
    LoadImage("assets/basketballA10.png");
    m_collisionShape = Circle2D(m_position, 92);
    SetCollidable();
    tutorialRemoved = false;
}

void Player::ProcessCollision(GameObject& other)
{
    ObjectType collidedType = other.GetType();
    if (collidedType == ObjectType::WALL && lastCollidedObject != &other) {
        // calculate the surface normal for collision on walls
        Vector2D normal;
        double x = m_position.XValue - other.GetPosition().XValue;
        double y = m_position.YValue - other.GetPosition().YValue;
        double absX = std::abs(x);
        double absY = std::abs(y);
        if (absX > absY) {
            normal = Vector2D((x > 0) ? 1.0 : -1.0, 0.0);
        }
        else {
            normal = Vector2D(0.0, (y > 0) ? 1.0 : -1.0);
        }

        m_velocity = m_velocity - (normal * (m_velocity* normal * 2));
        lastCollidedObject = &other;
        if (soundPlayed == false) {
            ballBounce = HtAudio::instance.LoadSound("assets/ball-bounce.mp3");
            int channel = HtAudio::instance.Play(ballBounce);
            //volume scales with current velocity
            HtAudio::instance.SetChannelVolume(channel, m_velocity.magnitude() / (MAX_LAUNCH_POWER * 6));
            soundPlayed = true;
        }
    }
    
    if (collidedType == ObjectType::LEVELEND && !lockedControls) {
        Event event = Event();
        event.pSource = this;
        event.type = LEVELEND;
        ObjectManager::instance.HandleEvent(event);
        Deactivate();
    }

    if (collidedType == ObjectType::SPIKES || collidedType == ObjectType::PROJECTILE) {
        Explosion* explosion = new Explosion();
        explosion->Initialise(m_position, true, 6);
        ObjectManager::instance.AddItem(explosion);
        if (collidedType == ObjectType::PROJECTILE) {
            other.Deactivate(); 
        }
        Deactivate();
    }
    if (lastCollidedBoosts.empty()) {
        if (collidedType == ObjectType::BOOST) {
            Vector2D boostDirection = Vector2D(0, 0);
            boostDirection.setBearing(dynamic_cast<Tile&>(other).GetAngle(), MAX_LAUNCH_POWER * 6);
            m_velocity += boostDirection;
            lastCollidedBoosts.push_back(&other);
            dynamic_cast<Tile&>(other).EnableBoost(false);

        }
    }
    else {
        if (collidedType == ObjectType::BOOST && lastCollidedBoosts.back() != &other) {
            Vector2D boostDirection = Vector2D(0, 0);
            boostDirection.setBearing(dynamic_cast<Tile&>(other).GetAngle(), MAX_LAUNCH_POWER * 6);
            m_velocity += boostDirection;
            if (m_velocity.magnitude() > MAX_LAUNCH_POWER * 6) {
                m_velocity.setBearing(m_velocity.angle(), MAX_LAUNCH_POWER * 6);
            }
            lastCollidedBoosts.push_back(&other);
            dynamic_cast<Tile&>(other).EnableBoost(false);

        }
    }
    
}

IShape2D& Player::GetCollisionShape()
{
    return m_collisionShape;
}


void Player::Launch()
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    double launchPower = direction.magnitude();
    if (launchPower > MAX_LAUNCH_POWER) {
        launchPower = MAX_LAUNCH_POWER;
    }
    m_velocity.setBearing(m_angle, launchPower*6);

    Event event = Event();
    event.pSource = this;
    event.type = PLAYERLAUNCHED;
    ObjectManager::instance.HandleEvent(event);
    lastCollidedBoosts.clear();
}

void Player::UpdateMovement(double frametime)
{
    Vector2D friction = -m_velocity;
    m_velocity += friction * frametime;
    if (m_velocity.magnitude() > 10) {
        m_timer += 16 * frametime / MAX_LAUNCH_POWER * m_velocity.magnitude();
        if (static_cast<int>(m_timer) >= 10) {
            m_timer = 0;
        }
        m_imageNumber = static_cast<int>(m_timer);
    }
    if (m_velocity.magnitude() < 100) {
        m_velocity += 2 * friction * frametime;
    }
    if (m_velocity.magnitude() < 10) {
        EndLaunch();
    }
    m_position += m_velocity * frametime;
}

void Player::EndLaunch()
{
    m_velocity = Vector2D(0, 0);
    lockedControls = false;
    lastCollidedObject = nullptr;
    for (GameObject* boost : lastCollidedBoosts) {
        if (boost != nullptr && boost->GetType() == ObjectType::BOOST) {
            dynamic_cast<Tile&>(*boost).EnableBoost(true);
        }
    }
}
