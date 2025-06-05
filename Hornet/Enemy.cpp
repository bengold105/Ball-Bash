#include "Enemy.h"
#include "ObjectManager.h"
#include "Adventurer.h"
#include <iostream>

const double MAX_SPEED = 300;
const double ACCELERATIONSPEED = 250;

Enemy::Enemy() : GameObject(ObjectType::ENEMY)
{
}

void Enemy::Update(double frametime)
{
    m_collisionShape.PlaceAt(m_position, 40);
    GameObject* player = ObjectManager::instance.FindClosestObject(m_position, ObjectType::PLAYER);


    //sees player
    if (true) {
        Vector2D direction = player->GetPosition() - m_position;
        direction = direction.unitVector()*MAX_SPEED;
        m_angle = direction.angle();
        m_acceleration = direction - m_velocity;
        m_acceleration = m_acceleration.unitVector() * ACCELERATIONSPEED;
        m_position += m_velocity * frametime;
        m_velocity += m_acceleration * frametime;
        m_acceleration = Vector2D(0, 0);

        
    }




}

void Enemy::Initialise()
{
    SetDrawDepth(9);
    m_scale = 1.5;
    m_position = Vector2D(100, 100);
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0, 0);
    LoadImage("assets/placeholderplayer.png");
    m_collisionShape = Circle2D(m_position, 40);
    IsCollidable();
    //important to make classes handle events
    SetHandleEvents();
}

void Enemy::ProcessCollision(GameObject& other)
{
    
}

IShape2D& Enemy::GetCollisionShape()
{
    return m_collisionShape;
}

void Enemy::HandleEvent(Event evt) 
{
    if (evt.type == PLAYERATTACK) {
        for (GameObject* enemy : evt.objectList) {
            if (enemy == this) {
                //code or method call for getting hit
                Vector2D distanceVector = m_position - evt.pSource->GetPosition();
                m_velocity.setBearing(distanceVector.angle(), 300);

                std::cout << "this enemy got hit" << std::endl;
            }
        }
    }
}
