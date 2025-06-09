#pragma once
#include "GameObject.h"
class Turret : public GameObject
{
public:
    Turret();
    void Initialise(Vector2D position, double angle, double scale);
    void Update(double frametime) override;
    void Render() override;

private:
    void Shoot();
    bool reloading;
    double m_timer;
    double m_reloadTimer;
    int m_width;
    int m_height;
};

