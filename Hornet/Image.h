#pragma once
#include "GameObject.h"
class Image : public GameObject
{
public:
    Image(const char* image);
    void Update(double frametime) override;
    void initialise();
    void setPosition(Vector2D& position);
    void setAngle(double angle);
    void setScale(double scale);
    double getScale();
    void Activate(bool activate);
    bool isActivated();
private:
    bool activated;
};

