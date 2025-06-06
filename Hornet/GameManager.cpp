#include "GameManager.h"
#include "ObjectManager.h"
#include <iostream>

GameManager::GameManager() : GameObject(ObjectType::GAMEMANAGER)
{
}

void GameManager::Initialise()
{
    m_levelNumber = 1;
    m_score = 0;
    m_playerLaunches = 0;
    m_playerLives = 3;
    m_levelLoader = nullptr;
}

void GameManager::Update(double frametime)
{
}

void GameManager::startGame()
{
    SetLevel(1);
}

void GameManager::Render()
{
}

void GameManager::HandleEvent(Event evt)
{
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
    SetSceneNumber(levelNumber);
    ObjectManager::instance.SetCurrentScene(m_levelNumber);
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
