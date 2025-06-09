#pragma once
#include "GameObject.h"
class ReticleDisplay : public GameObject
{
public:
    ReticleDisplay(const char* image);
    void Update(double frametime) override;
    void Initialise();
    void SetPosition(Vector2D& position);
    void SetAngle(double angle);
    void SetScale(double scale);
    double GetScale();
    void Activate(bool activate);
    bool IsActivated();
private:
    bool activated;
};

