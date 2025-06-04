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
private:
    GameObject* directionTriangle;
    bool activated;
};

