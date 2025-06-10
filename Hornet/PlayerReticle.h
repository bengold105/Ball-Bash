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
    void Activate(bool activate);
    //sets force vector (used by player class to send the mouse movement vector)
    void SetForceVector(Vector2D force);
private:
    //if activated, scales the reticle and triangle based on recorded mouse movement
    void ScaleReticle(double frametime);

    //triangle showing the direction and launch power so the player can see how strong the launch will be
    ReticleDisplay* directionTriangle;
    //the reticle scales up while activated, showing the player what direction they would launch in if they release left click
    bool activated;
    //vector representing the recorded mouse movement from parent class
    Vector2D m_force;
};

