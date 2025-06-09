#pragma once
#include "GameObject.h"
#include "ReticleDisplay.h"
class PlayerReticle : public GameObject
{
public:
    PlayerReticle();
    ~PlayerReticle();
    void Update(double frametime) override;
    void Initialise();
    //sets object position
    void SetPosition(Vector2D& position);
    //sets object angle
    void SetAngle(double angle);
    bool IsActivated();
    //activates or deactivates the reticle
    void Activate(bool activate);
    //sets force vector (used by player class to store mouse movement)
    void SetForceVector(Vector2D force);
private:
    //if activated, scales the reticle and triangle based on recorded mouse movement
    void ScaleReticle(double frametime);

    //triangle showing the direction and launch power so the player can see how strong the launch will be
    ReticleDisplay* directionTriangle;
    bool activated;
    //vector representing the recorded mouse movement from parent class
    Vector2D m_force;
};

