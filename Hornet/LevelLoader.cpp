#include "LevelLoader.h"
#include "Tile.h"
#include "ObjectManager.h"
#include <iostream>

const int tileDimension = 64;
const int tileScale = 6;


//add speedup pads, periodical projectile cannons, 


LevelLoader::LevelLoader()
{
}

bool LevelLoader::LoadLevel(int level)
{
    int level1Data[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 2, 2, 2, 1},
        {1, 3, 2, 4, 1},
        {1, 2, 2, 2, 1},
        {1, 1, 1, 1, 1}
    };
    int level2Data[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 2, 2, 2, 1},
        {1, 4, 2, 3, 1},
        {1, 2, 2, 2, 1},
        {1, 1, 1, 1, 1}
    };




    switch (level) {
    case 1: {
        // Load level 1 data
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                switch (level1Data[x][y]) {
                case 1: {
                    // Load wall
                    LoadWall(x, y);
                    break;
                }
                case 2: {
                    // Load floor
                    LoadFloor(x, y);
                    break;
                }
                case 3: {
                    // Load player spawn point
                    LoadSpawnPoint(x, y);
                    break;
                }
                case 4: {
                    // Load level end
                    LoadLevelEnd(x, y);
                    break;
                }
                default:
                    break;
                }
            }
        }
    } break;
    case 2: {
        // Load level 2 data
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                switch (level2Data[x][y]) {
                case 1: {
                    // Load wall
                    LoadWall(x, y);
                    break;
                }
                case 2: {
                    // Load floor
                    LoadFloor(x, y);
                    break;
                }
                case 3: {
                    // Load player spawn point
                    LoadSpawnPoint(x, y);
                    break;
                }
                case 4: {
                    // Load level end
                    LoadLevelEnd(x, y);
                    break;
                }
                default:
                    break;
                }
            }
        }
    } break;
        return true;
    }





    return false;
}

void LevelLoader::LoadWall(int x, int y)
{
    Tile* tile = new Tile(ObjectType::WALL);
    tile->Initialise("assets/bricks.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
    tile->SetDimensions(tileDimension, tileDimension);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadFloor(int x, int y)
{
    // Load floor
    Tile* tile = new Tile(ObjectType::TILE);
    tile->Initialise("assets/floortile.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
    tile->SetDimensions(tileDimension, tileDimension);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadSpawnPoint(int x, int y)
{
    Tile* tile = new Tile(ObjectType::SPAWNPOINT);
    tile->Initialise("assets/floortile.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
    tile->SetDimensions(tileDimension, tileDimension);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadLevelEnd(int x, int y)
{
    Tile* tile = new Tile(ObjectType::LEVELEND);
    tile->Initialise("assets/floortile-finish.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
    tile->SetDimensions(tileDimension, tileDimension);
    ObjectManager::instance.AddItem(tile);
}
