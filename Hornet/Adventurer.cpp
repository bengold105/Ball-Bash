#include "Adventurer.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "HtMouse.h"
#include "HtGraphics.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>

const double ATTACK_REACH = 150;
const double MAX_LAUNCH_POWER = 500;

Adventurer::Adventurer() : GameObject(ObjectType::PLAYER) 
{
    m_reticle = nullptr;
    lastCollidedObject = nullptr;
    lockedControls = false;
    prepLaunch = false;
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
            Attack();
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
    m_collisionShape.PlaceAt(m_position, 40);
    m_reticle->SetPosition(m_position);
}

void Adventurer::Initialise()
{
    SetDrawDepth(9);
    m_reticle = new PlayerReticle();
    m_reticle->Initialise();
    ObjectManager::instance.AddItem(m_reticle);
    m_scale = 2;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/newplaceholderplayer.png");
    m_collisionShape = Circle2D(m_position, 40);
    SetCollidable();
}

void Adventurer::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::WALL && lastCollidedObject != &other) {
        Vector2D normal = (m_position - other.GetPosition()).unitVector();
        m_velocity = m_velocity - (normal * (m_velocity* normal * 2));
        lastCollidedObject = &other;
    }
    


}

IShape2D& Adventurer::GetCollisionShape()
{
    return m_collisionShape;
}

void Adventurer::Attack()
{
    std::vector<GameObject*> enemiesAttacked;
    for (GameObject* enemy : ObjectManager::instance.GetAllObjectsOfType(ObjectType::ENEMY)) {
        Vector2D link = m_position - enemy->GetPosition();
        double linkAngle = link.angle() + 180;
        if (linkAngle > 360) {
            linkAngle -= 360;
        }
        std::cout << "enemy distance: " << link.magnitude() << std::endl << "vector angle: " << linkAngle << std::endl << "player angle: " << m_angle << std::endl;
        if ((link.magnitude() <= ATTACK_REACH) and ((linkAngle) > m_angle - 67) and ((linkAngle) < m_angle + 67)) {
            enemiesAttacked.push_back(enemy);
            std::cout << "enemy hit, distance: " << link.magnitude() << std::endl;
        }
    }
    Event event = Event();
    event.pSource = this;
    event.type = PLAYERATTACK;
    for (GameObject* enemy : enemiesAttacked) {
        event.objectList.push_back(enemy);
    }
    ObjectManager::instance.HandleEvent(event);
}

void Adventurer::Launch()
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    double launchPower = direction.magnitude();
    if (launchPower > MAX_LAUNCH_POWER) {
        launchPower = MAX_LAUNCH_POWER;
    }
    m_velocity.setBearing(m_angle, launchPower*6);
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
