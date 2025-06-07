#pragma once
#include "GameObject.h"
#include "PlayerReticle.h"
#include "HtAudio.h"
class Adventurer :
    public GameObject
{
public:
    Adventurer();
    void Update(double frametime) override;
    void Initialise();
    void Initialise(Vector2D spawn);
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
    void Attack();
    void Launch();
    void UpdateMovement(double frametime);
private:
    SoundIndex ballBounce;
    Circle2D m_collisionShape;
    Vector2D m_velocity;
    PlayerReticle* m_reticle;
    bool prepLaunch;
    bool lockedControls;
    GameObject* lastCollidedObject;
};

