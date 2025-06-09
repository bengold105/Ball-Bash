#include "PlayerReticle.h"
#include "HtMouse.h"
#include <iostream>
#include "ObjectManager.h"

const double MAX_FORCE = 500;
const double MIN_RETICLE_SCALE = 1.2;
const double MAX_RETICLE_SCALE = 3;
const double MIN_TRIANGLE_SCALE = 1.4;
const double MAX_TRIANGLE_SCALE = 1.7 + MIN_TRIANGLE_SCALE;
const double RETICLE_SCALE_FACTOR = 6;

PlayerReticle::PlayerReticle() : GameObject(ObjectType::RETICLE)
{
    SetDrawDepth(3);
    activated = false;
}

PlayerReticle::~PlayerReticle()
{
    directionTriangle->Deactivate();
    directionTriangle = nullptr;
}

void PlayerReticle::Update(double frametime)
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    
    ScaleReticle(frametime);
    


    directionTriangle->SetPosition(m_position);
    directionTriangle->SetAngle(direction.angle() + 180); 
}

void PlayerReticle::Initialise()
{
    LoadImage("assets/UICircle.png");
    directionTriangle = new ReticleDisplay("assets/UITriangle.png");
    directionTriangle->Initialise();
    ObjectManager::instance.AddItem(directionTriangle);
    directionTriangle->SetPosition(m_position);
    directionTriangle->SetScale(0);
    m_scale = MIN_RETICLE_SCALE;
    
}

void PlayerReticle::SetPosition(Vector2D& position)
{
    m_position = position;
}

void PlayerReticle::SetAngle(double angle)
{
    m_angle = angle;
}

void PlayerReticle::Activate(bool isActive)
{
    activated = isActive;
}

bool PlayerReticle::IsActivated()
{
    return activated;
}

void PlayerReticle::SetForceVector(Vector2D force)
{
    m_force = force;
}

void PlayerReticle::ScaleReticle(double frametime)
{
    double force = m_force.magnitude();
    if (force > MAX_FORCE) {
        force = MAX_FORCE;
    }

    if (activated)
    {
        if (m_scale < MAX_RETICLE_SCALE) {
            m_scale += RETICLE_SCALE_FACTOR * frametime;
        }
        directionTriangle->SetScale(force / MAX_FORCE * (MAX_TRIANGLE_SCALE - MIN_TRIANGLE_SCALE) + MIN_TRIANGLE_SCALE);
    }
    else
    {
        if (m_scale > MIN_RETICLE_SCALE) {
            m_scale -= RETICLE_SCALE_FACTOR * frametime;
        }

        if (directionTriangle->GetScale() > MIN_RETICLE_SCALE) {
            directionTriangle->SetScale(directionTriangle->GetScale() - RETICLE_SCALE_FACTOR * frametime);
        }
        else {
            directionTriangle->SetScale(0);
        }
    }
}

