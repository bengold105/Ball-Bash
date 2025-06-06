#pragma once
#include "GameObject.h"
#include "LevelLoader.h"
class GameManager : public GameObject
{
public:
    GameManager();
    void Initialise();
    void Update(double frametime) override;
    void startGame();
    void Render() override;
    void HandleEvent(Event evt) override;
    void SetPlayerLaunches(int launch);
    void SetPlayerLives(int lives);
    void SetLevel(int levelNumber);
    void EndGame();
private:

    void DisplayLaunches();
    void DisplayLives();
    void DisplayTip();
    void DisplayEndScreen();

    int m_levelNumber;
    int m_score;
    int m_playerLaunches;
    int m_playerLives;
    LevelLoader* m_levelLoader;
};

