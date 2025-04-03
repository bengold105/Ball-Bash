#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : GameObject(ObjectType::ENEMY)
{
}

void Enemy::Update(double frametime)
{
    m_collisionShape.PlaceAt(m_position, 40);
}

void Enemy::initialise()
{
    m_scale = 1.5;
    m_position = Vector2D(100, 100);
    m_velocity = Vector2D(0, 0);
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
                std::cout << "this enemy got hit" << std::endl;
            }
        }
    }
}
