#pragma once
#include "GameObject.h"
class Adventurer :
    public GameObject
{
public:
    Adventurer();
    void Update(double frametime) override;
    void initialise();
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
private:
    Circle2D m_collisionShape;
    Vector2D m_velocity;
};

