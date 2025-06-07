#include "GameManager.h"
#include "ObjectManager.h"
#include <iostream>
#include "HtKeyboard.h"
#include "HtCamera.h"

GameManager::GameManager() : GameObject(ObjectType::GAMEMANAGER)
{
}

void GameManager::Initialise()
{
    levelComplete = false;
    m_levelNumber = 1;
    m_score = 0;
    m_playerLaunches = 0;
    m_playerLives = 3;
    m_levelLoader = nullptr;
    SetHandleEvents();
    levelCompleteSound = NO_SOUND_INDEX;
}

void GameManager::Update(double frametime)
{
    cameraPosition = HtCamera::instance.GetCameraCentre(Vector2D(0,0));
    if (levelComplete) {
        //loads the next level when enter is pressed
        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_RETURN)) {
            SetLevel(m_levelNumber);
            levelComplete = false;
        }
    }
}

void GameManager::startGame()
{
    SetLevel(1);
}

void GameManager::Render()
{
    if (levelComplete) {
        DisplayLevelComplete();
    }
}

void GameManager::HandleEvent(Event evt)
{
    if (evt.type == EventType::LEVELEND)
    {
        // upon getting the level end event message from the player, 
        // plays the completion sound and shows the level complete message
        levelCompleteSound = HtAudio::instance.LoadSound("assets/tada.mp3");
        int channel = HtAudio::instance.Play(levelCompleteSound);
        levelCompleteSound = NO_SOUND_INDEX;
        levelComplete = true;
        m_levelNumber++;
        SetSceneNumber(m_levelNumber);
        ObjectManager::instance.SetCurrentScene(m_levelNumber);
    }
}

void GameManager::SetPlayerLaunches(int launch)
{
}

void GameManager::SetPlayerLives(int lives)
{
}

void GameManager::SetLevel(int levelNumber)
{
    m_levelLoader = new LevelLoader();
    m_levelLoader->LoadLevel(m_levelNumber);
    delete m_levelLoader;
    m_levelLoader = nullptr;
    ObjectManager::instance.DeleteInactiveItems();
}

void GameManager::EndGame()
{

}

void GameManager::DisplayLaunches()
{
}

void GameManager::DisplayLives()
{
}

void GameManager::DisplayTip()
{
}

void GameManager::DisplayEndScreen()
{
}

void GameManager::DisplayLevelComplete()
{
    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
        "Level Complete",
        HtGraphics::WHITE,
        0,
        0.0,
        3.0
    );

    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
        "Press Enter to go to the next level",
        HtGraphics::GREY,
        0,
        0.0,
        2.0
    );
}
