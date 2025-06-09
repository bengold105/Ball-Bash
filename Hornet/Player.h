#pragma once
#include "GameObject.h"
#include "PlayerReticle.h"
#include "HtAudio.h"
#include <vector>

class Player :
    public GameObject
{
public:
    Player();
    ~Player();
    void Update(double frametime) override;
    void Initialise(Vector2D spawn);
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
private:
    void Launch();
    void UpdateMovement(double frametime);
    void EndLaunch();

    bool soundPlayed;
    double soundDelay;
    bool tutorialRemoved;
    double m_timer;
    SoundIndex ballBounce;
    Circle2D m_collisionShape;
    Vector2D m_velocity;
    PlayerReticle* m_reticle;
    bool prepLaunch;
    bool lockedControls;
    GameObject* lastCollidedObject;
    std::vector<GameObject*> lastCollidedBoosts;
};

