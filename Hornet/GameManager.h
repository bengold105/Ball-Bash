#pragma once
#include "GameObject.h"
#include "LevelLoader.h"
#include "HtAudio.h"
#include "HtGraphics.h"
#include "UIRenderer.h"
class GameManager : public GameObject
{
public:
    GameManager();
    void Initialise();
    void Update(double frametime) override;
    // gets called when the game starts
    void StartGame();
    void Render() override;
    void HandleEvent(Event evt) override;
    void SetPlayerLaunches(int launch);
    void SetPlayerLives(int lives);
    //changes scenes and loads the level using the level loader
    void SetLevel(int levelNumber);
    // gets called when the game ends
    void EndGame();
private:

    void DisplayEndScreen();
    void DisplayLevelComplete();
    void DisplayGameOver();

    //stores whether the player is using the invincibility cheat or not
    bool notCheating;
    int totalLaunches;
    UIRenderer* renderer;
    Vector2D cameraPosition;
    SoundIndex levelCompleteSound;
    // stores whether the game is currently showing the level end screen
    bool levelComplete;
    bool playerDead;
    // stores whether the UIRenderer should be showing the game end screen
    bool endGame;
    int m_levelNumber;
    int m_score;
    int m_playerLaunches;
    int m_playerLives;
    LevelLoader* m_levelLoader;
};

