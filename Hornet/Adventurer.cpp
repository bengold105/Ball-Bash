#include "Adventurer.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "HtMouse.h"
#include "HtGraphics.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>
#include "Explosion.h"

const double ATTACK_REACH = 150;
const double MAX_LAUNCH_POWER = 500;

Adventurer::Adventurer() : GameObject(ObjectType::PLAYER) 
{
    m_reticle = nullptr;
    lastCollidedObject = nullptr;
    lockedControls = false;
    prepLaunch = false;
}

Adventurer::~Adventurer()
{
    m_reticle->Deactivate();
    m_reticle = nullptr;
}

void Adventurer::Update(double frametime)
{
    //locks the controls until the player has slowed down enough
    lockedControls = true;

    UpdateMovement(frametime);

    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;

    if (!lockedControls) {
        if (HtMouse::instance.IsNewMouseDown(HtMouseButton::LEFT)) {
            HtMouse::instance.SetPointerPosition(852, 548);
            m_reticle->Activate(true);
            prepLaunch = true;
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

void Adventurer::Initialise()
{
    SetDrawDepth(3);
    m_reticle = new PlayerReticle();
    m_reticle->Initialise();
    ObjectManager::instance.AddItem(m_reticle);
    m_scale = 2;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/newplaceholderplayer.png");
    m_collisionShape = Circle2D(m_position, 92);
    ballBounce = NO_SOUND_INDEX;
    SetCollidable();
}

void Adventurer::Initialise(Vector2D spawn)
{
    SetDrawDepth(9);
    m_reticle = new PlayerReticle();
    m_reticle->Initialise();
    ObjectManager::instance.AddItem(m_reticle);
    m_position = spawn;
    m_scale = 2;
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/newplaceholderplayer.png");
    m_collisionShape = Circle2D(m_position, 92);
    SetCollidable();
}

void Adventurer::ProcessCollision(GameObject& other)
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
        ballBounce = HtAudio::instance.LoadSound("assets/ball-bounce.mp3");
        int channel = HtAudio::instance.Play(ballBounce);
        //volume scales with current velocity
        HtAudio::instance.SetChannelVolume(channel, m_velocity.magnitude()/(MAX_LAUNCH_POWER*6));
    }
    
    if (collidedType == ObjectType::LEVELEND && !lockedControls) {
        Event event = Event();
        event.pSource = this;
        event.type = LEVELEND;
        ObjectManager::instance.HandleEvent(event);
        Deactivate();
    }

    if (collidedType == ObjectType::SPIKES) {
        Explosion* explosion = new Explosion();
        explosion->Initialise(m_position, true);
        ObjectManager::instance.AddItem(explosion);
        m_reticle->Deactivate();
        Deactivate();
    }

}

IShape2D& Adventurer::GetCollisionShape()
{
    return m_collisionShape;
}


void Adventurer::Launch()
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
}

void Adventurer::UpdateMovement(double frametime)
{
    Vector2D friction = -m_velocity;
    m_velocity += friction * frametime;
    if (m_velocity.magnitude() < 100) {
        m_velocity += 2 * friction * frametime;
    }
    if (m_velocity.magnitude() < 10) {
        m_velocity = Vector2D(0, 0);
        lockedControls = false;
        lastCollidedObject = nullptr;
    }
    m_position += m_velocity * frametime;
}
