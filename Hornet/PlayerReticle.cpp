#include "PlayerReticle.h"
#include "HtMouse.h"
#include <iostream>
#include "ObjectManager.h"

const double MAX_FORCE = 500;
const double MIN_RETICLE_SCALE = 1.43;
const double MAX_RETICLE_SCALE = 2.5;
const double MIN_TRIANGLE_SCALE = 1.2;
const double MAX_TRIANGLE_SCALE = 1.4 + MIN_TRIANGLE_SCALE;
const double RETICLE_SCALE_FACTOR = 6;

PlayerReticle::PlayerReticle() : GameObject(ObjectType::RETICLE)
{
    activated = false;
}

void PlayerReticle::Update(double frametime)
{
    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    double force = m_force.magnitude();
    if (force > MAX_FORCE) {
        force = MAX_FORCE;
    }

    if (activated)
    {
        if (m_scale < MAX_RETICLE_SCALE) {
            m_scale += RETICLE_SCALE_FACTOR * frametime;
        } 
        directionTriangle->setScale(force / MAX_FORCE * (MAX_TRIANGLE_SCALE - MIN_TRIANGLE_SCALE) + MIN_TRIANGLE_SCALE);
    }
    else
    {
        if (m_scale > MIN_RETICLE_SCALE) {
            m_scale -= RETICLE_SCALE_FACTOR * frametime;
        }

        if (directionTriangle->getScale() > MIN_RETICLE_SCALE) {
            directionTriangle->setScale(directionTriangle->getScale() - RETICLE_SCALE_FACTOR * frametime);
        }
        else {
            directionTriangle->setScale(0);
        }
    }


    directionTriangle->setPosition(m_position);
    directionTriangle->setAngle(direction.angle() + 180); 
}

void PlayerReticle::initialise()
{
    LoadImage("assets/UICircle.png");
    directionTriangle = new Image("assets/UITriangle.png");
    directionTriangle->initialise();
    ObjectManager::instance.AddItem(directionTriangle);
    directionTriangle->setPosition(m_position);
    directionTriangle->setScale(0);
    m_scale = 1.43;
    
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

void PlayerReticle::setForceVector(Vector2D force)
{
    m_force = force;
}

