#pragma once
#include "GameObject.h"
#include "HtAudio.h"
class Explosion : public GameObject
{
public:
    Explosion();
    void Initialise(Vector2D position, bool deadPlayer, double scale);
    void Update(double frametime) override;
    
private:
    SoundIndex explosionSound;
    bool playerDeath;
    double m_timer;
};

