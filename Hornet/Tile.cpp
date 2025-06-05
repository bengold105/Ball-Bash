#include "Tile.h"
#include "HtCamera.h"
#include "HtGraphics.h"
#include <iostream>

Tile::Tile(ObjectType type) : GameObject(type)
{
    SetDrawDepth(1);
    m_width = 0;
    m_height = 0;
}

void Tile::Initialise(const char* image, Vector2D position, double angle, double scale)
{
    LoadImage(image);
    m_position = position;
    m_angle = angle;
    m_scale = scale;

    if (GetType() == ObjectType::WALL)
    {
        SetCollidable();
    }
}

void Tile::Update(double frametime)
{
}

void Tile::SetDimensions(int width, int height)
{
    m_width = static_cast<int>(width * m_scale);
    m_height = static_cast<int>(height * m_scale);
    if (IsCollidable())
    {
        Vector2D bottomLeft(m_position.XValue - (m_width / 2), m_position.YValue - (m_width / 2));
        Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
}

IShape2D& Tile::GetCollisionShape()
{
    return m_collisionShape;
}

void Tile::ProcessCollision(GameObject& other)
{
    
}

void Tile::Render()
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
