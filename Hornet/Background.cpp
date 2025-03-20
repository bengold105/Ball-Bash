#include "Background.h"

Background::Background() : GameObject(ObjectType::BACKGROUND)
{
}

void Background::initialise()
{
    m_scale = 16;
    LoadImage("assets/spacebackground.jpg");
    SetDrawDepth(-1);
}
