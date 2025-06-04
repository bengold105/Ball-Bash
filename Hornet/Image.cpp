#include "Image.h"
#include <iostream>

Image::Image(const char* image) : GameObject(ObjectType::IMAGE)
{
   LoadImage(image);
   activated = false;
   m_position = Vector2D(0, 0);
   m_angle = 0;
   m_scale = 1.0;
}

void Image::Update(double frametime)
{
}

void Image::initialise()
{
    if (m_images.size() == 0) {
        std::cerr << "Image not loaded properly!" << std::endl;
    }
}

void Image::setPosition(Vector2D& position)
{
    m_position = position;
}

void Image::setAngle(double angle)
{
    m_angle = angle;
}

void Image::setScale(double scale)
{
    m_scale = scale;
}

double Image::getScale()
{
    return m_scale;
}

void Image::Activate(bool activate)
{
    activated = activate;
}

bool Image::isActivated()
{
   return activated;
}
