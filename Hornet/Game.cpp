#include "Game.h"
#include "HtCamera.h"
#include "ObjectManager.h"
#include "Adventurer.h"
#include "Background.h"
#include "Enemy.h"
#include "Tile.h"
#include "LevelLoader.h"
#include "GameManager.h"

/*
TODO List:
- add sound effects /
- add obstacles
- add level transition /
- add level end /
- add level end sound when level ends
- make level transition smoother
- add UI
- polish levels
*/


void Game::StartOfProgram()
{



    // This makes the operating system's mouse pointer invisible
    // It's usually best to use your own instead.
    HtMouse::instance.SetPointerVisiblity(true);
}

// Use this function to intialise your game objects and load any assets
void Game::StartOfGame()
{
    Background* background = new Background();
    background->initialise();
    ObjectManager::instance.AddItem(background);
    /*Adventurer* player = new Adventurer();
    player->Initialise();
    ObjectManager::instance.AddItem(player);*/

    /*ObjectManager::instance.SetCurrentScene(1);
    LevelLoader* levelLoader = new LevelLoader();
    levelLoader->LoadLevel(1);
    delete levelLoader;*/

    GameManager* gameManager = new GameManager();
    gameManager->Initialise();
    ObjectManager::instance.AddItem(gameManager);
    gameManager->startGame();
}

// Function runs each frame.
// "frametime" is the time in seconds since the last call (delta time)
void Game::Update(double frametime)
{
    // In the space below, you can write code to create a game the hard way.
    // To start with, we will use this area, but later will use game objects.




    // The code below runs the managed part of the game engine
    // Best to leave it alone
    ObjectManager::instance.UpdateAll(frametime);
    ObjectManager::instance.ProcessCollisions();
    ObjectManager::instance.RenderAll();
#ifdef _DEBUG
    ObjectManager::instance.CycleDebugObject();
    ObjectManager::instance.RenderDebug();
#endif
    ObjectManager::instance.DeleteInactiveItems();

    // Draws all graphics to the screen. Best not to remove this line.
    HtGraphics::instance.Present();
}

// Function runs when the user pauses the program.
// You may want to stop sound effects.
void Game::OnSuspend()
{
    HtAudio::instance.StopAllChannels();
}


// This function runs when the user resumes the game from pause
// You can start sound effects if needed, but it is usually
// best to just let the game create new sounds if needed.
void Game::OnResume()
{

}

// You can use this to clear up any memory, if needed
void Game::EndOfGame()
{    

    //This line automatically deletes all managed objects
    ObjectManager::instance.DeleteAllObjects();
    
}

void Game::EndOfProgram()
{
}
