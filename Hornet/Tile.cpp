#include "Tile.h"
#include "HtCamera.h"
#include "HtGraphics.h"
#include <iostream>
#include "Player.h"
#include "ObjectManager.h"

Tile::Tile(ObjectType type) : GameObject(type)
{
    SetDrawDepth(1);
    m_width = 0;
    m_height = 0;
}

void Tile::Initialise(const char* image, Vector2D position, double angle, double scale)
{
    if (GetType() != ObjectType::BOOST) {
        LoadImage(image);
    }
    else {
        LoadImage("assets/BoostpadA1.png");
        LoadImage("assets/BoostpadA2.png");
        LoadImage("assets/BoostpadA3.png");
        LoadImage("assets/BoostpadA4.png");
        LoadImage("assets/BoostpadA5.png");
    }
    m_position = position;
    m_angle = angle;
    m_scale = scale;
    pulsed = false;

    if ((GetType() == ObjectType::WALL) || (GetType() == ObjectType::LEVELEND))
    {
        SetCollidable();
    }
    if (GetType() == ObjectType::SPAWNPOINT)
    {
        Player* player = new Player();
        player->Initialise(m_position);
        ObjectManager::instance.AddItem(player);
    }
    if (GetType() == ObjectType::BOOST)
    {
        enableBoost = true;
        SetCollidable();
    }
}

void Tile::Update(double frametime)
{
    if (GetType() == ObjectType::BOOST)
    {

        if (pulsed)
        {
            m_timer -= 4 * frametime;
        }
        else
        {
            m_timer += 4 * frametime;
        }
    }
}

void Tile::SetDimensions(int width, int height)
{
    m_width = static_cast<int>(width * m_scale);
    m_height = static_cast<int>(height * m_scale);
    if (IsCollidable() && (GetType() == ObjectType::WALL || GetType() == ObjectType::BOOST))
    {
        Vector2D bottomLeft(m_position.XValue - (m_width / 2), m_position.YValue - (m_width / 2));
        Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
    if (IsCollidable() && GetType() == ObjectType::LEVELEND)
    { 
        //smaller hitbox for level end tiles
        Vector2D bottomLeft(m_position.XValue - (m_width / 4), m_position.YValue - (m_height / 4));
        Vector2D topRight(m_position.XValue + (m_width / 4), m_position.YValue + (m_height / 4));
        m_collisionShape.PlaceAt(bottomLeft, topRight);
    }
}

double Tile::GetAngle()
{
    return m_angle;
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
    if (static_cast<int>(m_timer) > 4)
    {
        m_timer = 4.0;
        pulsed = true;
    }
    else if (static_cast<int>(m_timer) < 0)
    {
        m_timer = 0;
        pulsed = false;
    }


    Rectangle2D cameraArea = HtCamera::instance.GetCameraArea();
    Vector2D bottomLeft(m_position.XValue - (m_height / 2), m_position.YValue - (m_height / 2));
    Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
    Rectangle2D tileArea = Rectangle2D(bottomLeft, topRight);
    if (tileArea.Intersects(cameraArea))
    {
        if (GetType() != ObjectType::BOOST)
        {
            HtGraphics::instance.DrawAt(m_position, m_images[0], m_scale, m_angle);
        }
        else if(enableBoost) {
            HtGraphics::instance.DrawAt(m_position, m_images[static_cast<int>(m_timer)], m_scale, m_angle);
        }
        else if (!enableBoost) {
            HtGraphics::instance.DrawAt(m_position, m_images[4], m_scale, m_angle);
        }
    }
}


void Tile::EnableBoost(bool enable)
{
    if (GetType() == ObjectType::BOOST)
    {
        enableBoost = enable;
    }
}
