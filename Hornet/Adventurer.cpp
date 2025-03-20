#include "Adventurer.h"
#include "HtKeyboard.h"
#include "HtCamera.h"

const double FORWARD = 0;
const double BACKWARD = 180;
const double LEFT = 270;
const double RIGHT = 90;
const double PLAYER_SPEED = 150;

Adventurer::Adventurer() : GameObject(ObjectType::PLAYER)
{

}
//todo for next workshop: ask about whether to make attacks a different class with hitboxes, ask about movement
void Adventurer::Update(double frametime)
{
    m_position += m_velocity * frametime;
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_A)) {
        m_angle = LEFT;
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D)) {
        m_angle = RIGHT;
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W)) {
        m_angle = FORWARD;
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_S)) {
        m_angle = BACKWARD;
        m_velocity.setBearing(m_angle, PLAYER_SPEED);
    }
    if (!HtKeyboard::instance.KeyPressed(SDL_SCANCODE_A) && !HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D) && !HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W) && !HtKeyboard::instance.KeyPressed(SDL_SCANCODE_S))
    {
        m_velocity = Vector2D(0, 0);
    }
    HtCamera::instance.PlaceAt(m_position);
}

void Adventurer::initialise()
{
    m_scale = 1.5;
    m_position = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);
    LoadImage("assets/placeholderplayer.png");
    
}

void Adventurer::ProcessCollision(GameObject& other)
{
}

IShape2D& Adventurer::GetCollisionShape()
{
    return m_collisionShape;
}