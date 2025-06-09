#pragma once
#include "GameObject.h"
class Projectile : public GameObject
{
public:
    Projectile();
    void Initialise(Vector2D position, double angle);
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
    
private:
    Circle2D m_collisionShape;
    Vector2D m_velocity;

};

