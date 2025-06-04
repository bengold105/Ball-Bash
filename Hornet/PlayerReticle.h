#pragma once
#include "GameObject.h"
#include "Image.h"
class PlayerReticle : public GameObject
{
public:
    PlayerReticle();
    void Update(double frametime) override;
    void initialise();
    void setPosition(Vector2D& position);
    void setAngle(double angle);
    void Activate(bool activate);
    bool isActivated();
    void setForceVector(Vector2D force);
private:
    Image* directionTriangle;
    bool activated;
    Vector2D m_force;
};

