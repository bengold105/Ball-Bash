#include "Adventurer.h"
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "HtMouse.h"
#include "HtGraphics.h"

const double FORWARD = 0;
const double BACKWARD = 180;
const double LEFT = 270;
const double RIGHT = 90;
const double PLAYER_SPEED = 200;

Adventurer::Adventurer() : GameObject(ObjectType::PLAYER)
{

}
//todo for next workshop: ask about whether to make attacks a different class with hitboxes, ask about movement
void Adventurer::Update(double frametime)
{
    
    m_position += m_velocity * frametime;

    Vector2D direction = HtMouse::instance.GetPointerGamePosition() - m_position;
    m_angle = direction.angle();
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (!HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_velocity = Vector2D(0,0);
    }
    HtCamera::instance.PlaceAt(m_position);
}

void Adventurer::initialise()
{
    m_scale = 1.5;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/placeholderplayer.png");
    m_collisionShape = Circle2D(m_position, 40);
    IsCollidable();
}

void Adventurer::ProcessCollision(GameObject& other)
{
}

IShape2D& Adventurer::GetCollisionShape()
{
    return m_collisionShape;
}