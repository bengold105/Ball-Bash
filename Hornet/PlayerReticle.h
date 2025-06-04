#pragma once
#include "GameObject.h"
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
private:
    GameObject* directionTriangle;
    bool activated;
};

