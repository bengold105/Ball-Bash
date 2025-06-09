#pragma once
#include "GameObject.h"
class UIRenderer : public GameObject
{
public:
    void Initialise(int lives, int launches, int currentLevel);
    void Render() override;
    void Update(double frametime) override;

    void DisplayLaunches();
    void DisplayLives();
    void DisplayTip();
    void setLives(int lives);
    void setLaunches(int launches);
    void setLevel(int level);
    void setDisplayHint(bool display);
private:
    bool displayHint;
    int m_currentLevel;
    int m_lives;
    int m_launches;
};

