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

}

void Adventurer::Update(double frametime)
{
    Vector2D friction = -m_velocity;
    m_velocity += friction * frametime;
    if (m_velocity.magnitude() < 100) {
        m_velocity += 2 * friction * frametime; 
    }
    if (m_velocity.magnitude() < 10) {
        m_velocity = Vector2D(0, 0);
    }
    m_position += m_velocity * frametime;


    /*old movement code
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (!HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity = Vector2D(0,0);
    }*/

    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;

    if (HtMouse::instance.IsNewMouseDown(HtMouseButton::LEFT)) {
        HtMouse::instance.GetMouseMoveX();
        HtMouse::instance.GetMouseMoveY();
        mouseMovement = Vector2D(0, 0);
        m_reticle->Activate(true);
        prepLaunch = true;
        Attack();
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
        mouseMovement += Vector2D(HtMouse::instance.GetMouseMoveX(), HtMouse::instance.GetMouseMoveY());
        m_angle = direction.angle() + 180;
        m_reticle->setForceVector(mouseMovement);
    }

    HtCamera::instance.PlaceAt(m_position);
    m_collisionShape.PlaceAt(m_position, 40);
    m_reticle->setPosition(m_position);
}

void Adventurer::initialise()
{
    prepLaunch = false;
    m_reticle = new PlayerReticle();
    m_reticle->initialise();
    ObjectManager::instance.AddItem(m_reticle);
    m_scale = 2;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/newplaceholderplayer.png");
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

void Adventurer::Launch()
{
    double launchPower = mouseMovement.magnitude();
    if (launchPower > MAX_LAUNCH_POWER) {
        launchPower = MAX_LAUNCH_POWER;
    }
    m_velocity.setBearing(m_angle, launchPower*6);
}
