#pragma once
#include "GameObject.h"
#include "PlayerReticle.h"
class Adventurer :
    public GameObject
{
public:
    Adventurer();
    void Update(double frametime) override;
    void Initialise();
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
    void Attack();
    void Launch();
    void UpdateMovement(double frametime);
private:
    Circle2D m_collisionShape;
    Vector2D m_velocity;
    Vector2D mouseMovement;
    PlayerReticle* m_reticle;
    bool prepLaunch;
    bool lockedControls;
};

