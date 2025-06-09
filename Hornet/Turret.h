#pragma once
#include "GameObject.h"
class Turret : public GameObject
{
public:
    Turret();
    void Initialise(Vector2D position, double angle, double scale);
    void Update(double frametime) override;
    void Render() override;
    void Shoot();

private:
    bool reloading;
    double m_timer;
    double m_reloadTimer;
    int m_width;
    int m_height;
};

