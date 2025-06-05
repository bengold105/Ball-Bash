#include "Game.h"
#include "HtCamera.h"
#include "ObjectManager.h"
#include "Adventurer.h"
#include "Background.h"
#include "Enemy.h"
#include "Tile.h"

/*
TODO List:
- tiled dungeon
use a config file with the tile as a list of numbers
- attacks
make them part of the player class
use closest objects and vectors to figure out if the enemy is in front and attackable, then add animations and effects
- move to mouse pointer
watch chris's video
- enemy pathing (diagonals)
use getclosestobject and then vectors to determine the directional movement
- minimap 
use objectmanager list of objects and their position, scaled down to show a minimap (draw objects as dots)
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
    Adventurer* player = new Adventurer();
    player->Initialise();
    ObjectManager::instance.AddItem(player);
    Tile* tile = new Tile(ObjectType::WALL);
    tile->Initialise("assets/bricks.png", Vector2D(512, 0), 0, 6);
    tile->SetDimensions(64, 64);
    ObjectManager::instance.AddItem(tile);
    /*
    Enemy* enemy = new Enemy();
    enemy->initialise();
    ObjectManager::instance.AddItem(enemy);
    */

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
