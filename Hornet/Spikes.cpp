#include "Spikes.h"
#include "HtCamera.h"
#include <iostream>

Spikes::Spikes() : GameObject(ObjectType::SPIKES)
{
    SetDrawDepth(2);
}

void Spikes::Initialise(const char* image, Vector2D position, double angle, double scale)
{
    LoadImage(image);
    m_position = position;
    m_angle = angle;
    m_scale = scale;
    SetCollidable();
}

void Spikes::Update(double frametime)
{
}

IShape2D& Spikes::GetCollisionShape()
{
    return m_collisionShape;
}

void Spikes::ProcessCollision(GameObject& other)
{
}

void Spikes::Render()
{
    Rectangle2D cameraArea = HtCamera::instance.GetCameraArea();
    Vector2D bottomLeft(m_position.XValue - (m_height / 2), m_position.YValue - (m_height / 2));
    Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
    Rectangle2D tileArea = Rectangle2D(bottomLeft, topRight);
    if (tileArea.Intersects(cameraArea))
    {
        HtGraphics::instance.DrawAt(m_position, m_images[0], m_scale, m_angle);
    }

}

void Spikes::SetDimensions(int width, int height)
{
    m_width = static_cast<int>(width * m_scale);
    m_height = static_cast<int>(height * m_scale);

    if (m_angle == 0) {
        Vector2D bottomLeft(m_position.XValue - (m_width / 2), m_position.YValue - (m_width / 2));
        Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue);
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
    else if (m_angle == 90) {
        Vector2D bottomLeft(m_position.XValue - (m_width / 2), m_position.YValue - (m_width / 2));
        Vector2D topRight(m_position.XValue, m_position.YValue + (m_height / 2));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
    else if (m_angle == 180) {
        Vector2D bottomLeft(m_position.XValue - (m_width / 2), m_position.YValue);
        Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
    else if (m_angle == 270) {
        Vector2D bottomLeft(m_position.XValue, m_position.YValue - (m_width / 2));
        Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
    else {
        std::cerr << "Spikes angle not set to 0, 90, 180 or 270 degrees. Please check the angle." << std::endl;
    }
}


