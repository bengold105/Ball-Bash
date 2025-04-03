#include "Adventurer.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "HtMouse.h"
#include "HtGraphics.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include <iostream>

const double FORWARD = 0;
const double BACKWARD = 180;
const double LEFT = 270;
const double RIGHT = 90;
const double PLAYER_SPEED = 200;
const double ATTACK_REACH = 150;

Adventurer::Adventurer() : GameObject(ObjectType::PLAYER)
{

}

void Adventurer::Update(double frametime)
{
    
    m_position += m_velocity * frametime;

    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    m_angle = direction.angle();
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (!HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity = Vector2D(0,0);
    }
    if (HtMouse::instance.IsNewMouseDown(HtMouseButton::LEFT)) {
        Attack();
    }
    HtCamera::instance.PlaceAt(m_position);
    m_collisionShape.PlaceAt(m_position, 40);
}

void Adventurer::initialise()
{
    m_scale = 1.5;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/placeholderplayer.png");
    m_collisionShape = Circle2D(m_position, 40);
    IsCollidable();
}

void Adventurer::ProcessCollision(GameObject& other)
{
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
