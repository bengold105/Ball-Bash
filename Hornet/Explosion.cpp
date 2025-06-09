#include "Explosion.h"
#include "ObjectManager.h"

Explosion::Explosion() : GameObject(ObjectType::EXPLOSION)
{

}

void Explosion::Initialise(Vector2D position, bool deadPlayer, int scale)
{
    m_timer = 0;
    m_position = position;
    LoadImage("assets/explosionA1.bmp");
    LoadImage("assets/explosionA2.bmp");
    LoadImage("assets/explosionA3.bmp");
    LoadImage("assets/explosionA4.bmp");
    LoadImage("assets/explosionA5.bmp");
    LoadImage("assets/explosionA6.bmp");
    LoadImage("assets/explosionA7.bmp");
    LoadImage("assets/explosionA8.bmp");
    playerDeath = deadPlayer;
    explosionSound = HtAudio::instance.LoadSound("assets/explosion1.wav");
    int channel = HtAudio::instance.Play(explosionSound);

    if (!playerDeath) {
        HtAudio::instance.SetChannelVolume(channel, 0.1); // Lower volume for player death explosion
    }
    SetDrawDepth(5);
    m_scale = scale;
}

void Explosion::Update(double frametime)
{
    m_timer += 8 * frametime;
    if (m_timer >= 8)
    {
        if (playerDeath)
        {
            Event event = Event();
            event.pSource = this;
            event.type = PLAYERDEAD;
            ObjectManager::instance.HandleEvent(event);
        }
        
        Deactivate();
    }
    m_imageNumber = static_cast<int>(m_timer);
}
