#include "PlayerReticle.h"
#include "HtMouse.h"
#include <iostream>

PlayerReticle::PlayerReticle()
{
}

void PlayerReticle::Update(double frametime)
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    

    if (activated)
    {
        if (m_scale < 2.5) {
            m_scale += 6 * frametime;
        } 
    }
    else
    {
        if (m_scale > 1.43) {
            m_scale -= 4 * frametime;
        }
    }
}

void PlayerReticle::initialise()
{
    LoadImage("assets/UICircle.png");
    m_scale = 1.43;
    activated = false;
    
}

void PlayerReticle::setPosition(Vector2D& position)
{
    m_position = position;
}

void PlayerReticle::setAngle(double angle)
{
    m_angle = angle;
}

void PlayerReticle::Activate(bool isActive)
{
    activated = isActive;
}

bool PlayerReticle::isActivated()
{
    return activated;
}

