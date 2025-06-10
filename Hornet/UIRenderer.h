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
    void SetLives(int lives);
    void SetLaunches(int launches);
    void SetLevel(int level);
    void SetDisplayHint(bool display);
    void SetCheatsEnabled(bool enable);
    void DisplayCheats();
private:
    bool isCheating;
    bool displayHint;
    int m_currentLevel;
    int m_lives;
    int m_launches;
};

