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
    m_levelNumber = 4;
    m_score = 0;
    m_playerLaunches = 0;
    m_playerLives = 3;
    m_levelLoader = nullptr;
    SetHandleEvents();
    levelCompleteSound = NO_SOUND_INDEX;
    renderer = nullptr;
}

void GameManager::Update(double frametime)
{
    cameraPosition = HtCamera::instance.GetCameraCentre(Vector2D(0,0));
    if (levelComplete) {
        //loads the next level when enter is pressed
        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_RETURN)) {
            SetLevel(m_levelNumber);
            levelComplete = false;
            m_playerLaunches = 0;
        }
    }

    if (playerDead && m_playerLives > 0) {
        //loads the next level when enter is pressed
        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_RETURN)) {
            SetSceneNumber(m_levelNumber);
            ObjectManager::instance.SetCurrentScene(m_levelNumber);
            ObjectManager::instance.DeleteInactiveItems();
            SetLevel(m_levelNumber);
            playerDead = false;
        }
    }

    if (renderer != nullptr)
    {
        renderer->setLaunches(m_playerLaunches);
        renderer->setLives(m_playerLives);
    }
}

void GameManager::startGame()
{
    SetSceneNumber(1);
    ObjectManager::instance.SetCurrentScene(1);
    SetLevel(1);
}

void GameManager::Render()
{
    if (levelComplete && !playerDead) {
        DisplayLevelComplete();
    }
    if (playerDead)
    {
        DisplayGameOver();
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
        ObjectManager::instance.DeactivateScene(m_levelNumber - 1);
        totalLaunches += m_playerLaunches;
    }
    
    if(evt.type == EventType::PLAYERDEAD)
    {
        m_playerLives--;
        playerDead = true;
        SetSceneNumber(-1);
        ObjectManager::instance.SetCurrentScene(-1);
        ObjectManager::instance.DeactivateScene(m_levelNumber);
    }

    if (evt.type == EventType::PLAYERLAUNCHED) {
        m_playerLaunches++;
        if (renderer != nullptr) {
            renderer->setLaunches(m_playerLaunches);
        }
    }

    if (evt.type == EventType::REMOVETUTORIAL)
    {
        if (renderer != nullptr) {
            renderer->setDisplayHint(false);
        }
    }
}

void GameManager::SetPlayerLaunches(int launch)
{
    m_playerLaunches = launch;
}

void GameManager::SetPlayerLives(int lives)
{
    m_playerLaunches = lives;
}

void GameManager::SetLevel(int levelNumber)
{
    if (renderer != nullptr) {
        renderer->Deactivate();
        renderer = nullptr;
    }
    m_levelLoader = new LevelLoader();
    m_levelLoader->LoadLevel(m_levelNumber);
    delete m_levelLoader;
    m_levelLoader = nullptr;
    ObjectManager::instance.DeleteInactiveItems();
    renderer = new UIRenderer();
    renderer->Initialise(m_playerLives, m_playerLaunches, m_levelNumber);
    renderer->setLevel(levelNumber);
    ObjectManager::instance.AddItem(renderer);
}

void GameManager::EndGame()
{

}


void GameManager::DisplayEndScreen()
{
}

void GameManager::DisplayLevelComplete()
{
    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
        "Level Completed with " + std::to_string(m_playerLaunches) + " launches",
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

void GameManager::DisplayGameOver()
{

    if (m_playerLives > 0 && m_playerLives != 1) {
        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
            "You have died and have " + std::to_string(m_playerLives) + " lives left",
            HtGraphics::WHITE,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
            "Press Enter to continue",
            HtGraphics::GREY,
            0,
            0.0,
            2.0
        );
    }
    
    if (m_playerLives == 1) {
        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
            "You have died and have 1 life left",
            HtGraphics::WHITE,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
            "Press Enter to continue",
            HtGraphics::GREY,
            0,
            0.0,
            2.0
        );
    }
    
    if (m_playerLives <= 0) {
        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
            "You have died and have 0 lives left",
            HtGraphics::WHITE,
            0,
            0.0,
            4.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
            "Press Escape to exit the game",
            HtGraphics::GREY,
            0,
            0.0,
            3.0
        );
    }

    
}
