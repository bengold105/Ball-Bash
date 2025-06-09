#include "Turret.h"
#include "HtCamera.h"
#include "Projectile.h"
#include "ObjectManager.h"

Turret::Turret() : GameObject(ObjectType::TURRET)
{
    SetDrawDepth(4);
}

void Turret::Initialise(Vector2D position, double angle, double scale)
{
    LoadImage("assets/TurretA1.png");
    LoadImage("assets/TurretA7.png");
    LoadImage("assets/TurretA6.png");
    LoadImage("assets/TurretA5.png");
    LoadImage("assets/TurretA4.png");
    LoadImage("assets/TurretA3.png");
    LoadImage("assets/TurretA2.png");
    m_position = position;
    m_angle = angle;
    m_scale = scale;
}

void Turret::Update(double frametime)
{
    if (reloading) {
        m_timer += 3.5*frametime;
        m_reloadTimer += frametime;
    }
    
    if (m_reloadTimer >= 2) // Example reload time
    {
        reloading = false;
        m_reloadTimer = 0;
        m_timer = 0;
    }
    if (!reloading) {
        Shoot();
    }
}

void Turret::Render()
{
    if (static_cast<int>(m_timer) > 6)
    {
        m_timer = 0;
    }

    Rectangle2D cameraArea = HtCamera::instance.GetCameraArea();
    Vector2D bottomLeft(m_position.XValue - (m_height / 2), m_position.YValue - (m_height / 2));
    Vector2D topRight(m_position.XValue + (m_height / 2), m_position.YValue + (m_height / 2));
    Rectangle2D tileArea = Rectangle2D(bottomLeft, topRight);
    if (tileArea.Intersects(cameraArea))
    {
        HtGraphics::instance.DrawAt(m_position, m_images[static_cast<int>(m_timer)], m_scale, m_angle);
    }
}

void Turret::Shoot()
{
    Projectile* projectile = new Projectile();
    projectile->Initialise(m_position, m_angle);
    ObjectManager::instance.AddItem(projectile);
    m_timer = 1;
    reloading = true;
}
