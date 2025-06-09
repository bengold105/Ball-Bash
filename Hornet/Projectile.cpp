#include "Projectile.h"
#include "Explosion.h"
#include "ObjectManager.h"
#include <iostream>

const int PROJECTILESPEED = 500;

Projectile::Projectile() : GameObject(ObjectType::PROJECTILE)
{
}

void Projectile::Initialise(Vector2D position, double angle)
{
    m_position = position;
    m_angle = angle;
    m_velocity = Vector2D(0, 0);
    m_velocity.setBearing(m_angle, 500); 
    m_collisionShape = Circle2D(m_position, 30);
    LoadImage("assets/cannonball.png");
    m_scale = 6;
    SetDrawDepth(5);
    SetCollidable();
}

void Projectile::Update(double frametime)
{
    m_position += m_velocity * frametime; 
    m_collisionShape.PlaceAt(m_position, 30);
}

void Projectile::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::WALL) {
        Explosion* explosion = new Explosion();
        explosion->Initialise(m_position, false, 2);
        ObjectManager::instance.AddItem(explosion);
        Deactivate();
    }
}

IShape2D& Projectile::GetCollisionShape()
{
    return m_collisionShape;
}
