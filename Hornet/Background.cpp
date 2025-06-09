#include "Background.h"
#include "HtCamera.h"

Background::Background() : GameObject(ObjectType::BACKGROUND)
{
}

void Background::initialise()
{
    m_scale = 4;
    LoadImage("assets/spacebackground.jpg");
    SetDrawDepth(-1);
}

void Background::Update(double frametime)
{
    m_position = HtCamera::instance.GetCameraCentre(Vector2D(0, 0));
}
