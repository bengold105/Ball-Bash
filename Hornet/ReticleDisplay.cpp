#include "ReticleDisplay.h"
#include <iostream>

ReticleDisplay::ReticleDisplay(const char* image) : GameObject(ObjectType::IMAGE)
{
   LoadImage(image);
   activated = false;
   SetDrawDepth(8);
}

void ReticleDisplay::Update(double frametime)
{
}

void ReticleDisplay::Initialise()
{
    m_position = Vector2D(0, 0);
    m_angle = 0;
    m_scale = 1.0;
    if (m_images.size() == 0) {
        std::cerr << "Image not loaded properly!" << std::endl;
    }
}

void ReticleDisplay::SetPosition(Vector2D& position)
{
    m_position = position;
}

void ReticleDisplay::SetAngle(double angle)
{
    m_angle = angle;
}

void ReticleDisplay::SetScale(double scale)
{
    m_scale = scale;
}

double ReticleDisplay::GetScale()
{
    return m_scale;
}

void ReticleDisplay::Activate(bool activate)
{
    activated = activate;
}

bool ReticleDisplay::IsActivated()
{
   return activated;
}
