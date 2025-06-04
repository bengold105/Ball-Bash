#include "PlayerReticle.h"
#include "HtMouse.h"
#include <iostream>

PlayerReticle::PlayerReticle()
{
}

void PlayerReticle::Update(double frametime)
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    if (HtMouse::instance.IsNewMouseDown(HtMouseButton::LEFT))
    {
        activated = true;
    }

    if (!HtMouse::instance.IsMouseDown(HtMouseButton::LEFT))
    {
        activated = false;
    }

    if (activated)
    {
        if (m_scale < 2.5) {
            m_scale += 4 * frametime;
        } 
    }
    else
    {
        if (m_scale > 1.43) {
            m_scale -= 3 * frametime;
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

