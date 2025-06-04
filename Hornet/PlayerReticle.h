#pragma once
#include "GameObject.h"
#include "Image.h"
class PlayerReticle : public GameObject
{
public:
    PlayerReticle();
    void Update(double frametime) override;
    void initialise();
    //sets object position
    void SetPosition(Vector2D& position);
    //sets object angle
    void SetAngle(double angle);
    //activates or deactivates the reticle
    void Activate(bool activate);
    bool IsActivated();
    //sets force vector (used by parent class to store mouse movement)
    void SetForceVector(Vector2D force);
    //if activated, scales the reticle and triangle based on recorded mouse movement
    void ScaleReticle(double frametime);
private:
    //triangle showing the direction and launch power so the player can see how strong the launch will be
    Image* directionTriangle;
    bool activated;
    //vector representing the recorded mouse movement from parent class
    Vector2D m_force;
};

