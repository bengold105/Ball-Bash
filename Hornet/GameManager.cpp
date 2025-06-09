#include "GameManager.h"
#include "ObjectManager.h"
#include <iostream>
#include "HtKeyboard.h"
#include "HtCamera.h"
#include "Background.h"

const int LEVEL_COUNT = 7;
const int MAX_LIVES = 5;
const int LAUNCH_MULTIPLIER = 100;
const int BASE_LEVEL_SCORE = 1000;
const int STARTING_LEVEL = 1;

GameManager::GameManager() : GameObject(ObjectType::GAMEMANAGER)
{
}

void GameManager::Initialise()
{
    levelComplete = false;
    m_levelNumber = STARTING_LEVEL;
    m_score = 0;
    m_playerLaunches = 0;
    m_playerLives = MAX_LIVES;
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
        if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_RETURN)) {
            SetSceneNumber(m_levelNumber);
            ObjectManager::instance.SetCurrentScene(m_levelNumber);
            SetLevel(m_levelNumber);

            levelComplete = false;
            m_playerLaunches = 0;
        }
    }

    if (playerDead && m_playerLives > 0) {
        if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_RETURN)) {
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
    if (endGame) {
        DisplayEndScreen();
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
        SetSceneNumber(0);
        ObjectManager::instance.SetCurrentScene(0);
        ObjectManager::instance.DeactivateScene(m_levelNumber - 1);
        totalLaunches += m_playerLaunches;
        if ((BASE_LEVEL_SCORE - (m_playerLaunches * LAUNCH_MULTIPLIER)) > 0 && m_levelNumber - 1 < 6) {
            m_score += BASE_LEVEL_SCORE - (m_playerLaunches * LAUNCH_MULTIPLIER);
        }
        else if (BASE_LEVEL_SCORE*2 - (m_playerLaunches * LAUNCH_MULTIPLIER) > 0) {
            m_score += BASE_LEVEL_SCORE*2 - (m_playerLaunches * LAUNCH_MULTIPLIER);
        }
        if (ObjectManager::instance.GetAllObjectsOfType(ObjectType::BACKGROUND).empty())
        {
            Background* background = new Background();
            background->initialise("assets/transition-background.png");
            ObjectManager::instance.AddItem(background);
        }
    }
    
    if(evt.type == EventType::PLAYERDEAD)
    {
        m_playerLives--;
        playerDead = true;
        SetSceneNumber(0);
        ObjectManager::instance.SetCurrentScene(0);
        ObjectManager::instance.DeactivateScene(m_levelNumber);

        if (ObjectManager::instance.GetAllObjectsOfType(ObjectType::BACKGROUND).empty())
        {
            Background* background = new Background();
            background->initialise("assets/transition-background.png");
            ObjectManager::instance.AddItem(background);
        }
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
    bool result = false;
    if (renderer != nullptr) {
        renderer->Deactivate();
        renderer = nullptr;
    }
    m_levelLoader = new LevelLoader();
    result = m_levelLoader->LoadLevel(m_levelNumber);
    ObjectManager::instance.DeleteInactiveItems();
    delete m_levelLoader;
    m_levelLoader = nullptr;
    renderer = new UIRenderer();
    renderer->Initialise(m_playerLives, m_playerLaunches, m_levelNumber);
    renderer->setLevel(levelNumber);
    ObjectManager::instance.AddItem(renderer);

    if (!result) {
        if (m_levelNumber < LEVEL_COUNT + 1) {
            std::cerr << "Error loading level " << m_levelNumber << std::endl;
        }
        else {
            EndGame();
        }
        
    }
}

void GameManager::EndGame()
{
    endGame = true;
    m_score *= m_playerLives;
    SetSceneNumber(0);
    ObjectManager::instance.SetCurrentScene(0);
}


void GameManager::DisplayEndScreen()
{
    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
        "Congratulations on completing the game!",
        HtGraphics::BLACK,
        0,
        0.0,
        3.0
    );

    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
        "Your final score was " + std::to_string(m_score),
        HtGraphics::BLACK,
        0,
        0.0,
        2.0
    );
}

void GameManager::DisplayLevelComplete()
{
    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
        "Level Completed with " + std::to_string(m_playerLaunches) + " launches",
        HtGraphics::BLACK,
        0,
        0.0,
        3.0
    );

    HtGraphics::instance.WriteTextCentered(
        Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
        "Press Enter to go to the next level",
        HtGraphics::BLACK,
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
            HtGraphics::BLACK,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
            "Press Enter to continue",
            HtGraphics::BLACK,
            0,
            0.0,
            2.0
        );
    }
    
    if (m_playerLives == 1) {
        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
            "You have died and have 1 life left",
            HtGraphics::BLACK,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 100),
            "Press Enter to continue",
            HtGraphics::BLACK,
            0,
            0.0,
            2.0
        );
    }
    
    if (m_playerLives <= 0) {
        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 300),
            "You have died and have 0 lives left",
            HtGraphics::BLACK,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue + 150),
            "Press Escape to exit the game",
            HtGraphics::BLACK,
            0,
            0.0,
            3.0
        );

        HtGraphics::instance.WriteTextCentered(
            Vector2D(cameraPosition.XValue, cameraPosition.YValue),
            "Final Score: " + std::to_string(m_score),
            HtGraphics::BLACK,
            0,
            0.0,
            3.0
        );
    }

    
}
