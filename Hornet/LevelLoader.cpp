#include "LevelLoader.h"
#include "Tile.h"
#include "ObjectManager.h"
#include <iostream>
#include "Spikes.h"
#include "Turret.h"
#include "Background.h"

const int TILE_DIMENSION = 64;
const int TILE_SCALE = 6;
const int LEVEL_1_DIMENSION_X = 5;
const int LEVEL_1_DIMENSION_Y = 5;
const int LEVEL_2_DIMENSION_X = 16;
const int LEVEL_2_DIMENSION_Y = 16;

LevelLoader::LevelLoader()
{
}

bool LevelLoader::LoadLevel(int level)
{

    //first level: tutorial level, L shaped 
    //second level: still l shape, spike so player needs to control their launch
    //third level: add boostpad, with multiple bends where the boostpad launches you in the right direction
    //fourth level: combination of level 2 and 3 but with boostpad in backwards orientation so it blocks the player



    int level1Data[LEVEL_1_DIMENSION_X][LEVEL_1_DIMENSION_Y] = {
        {1, 1, 1, 1, 1},
        {1, 2, 6, 2, 1},
        {1, 3, 2, 4, 1},
        {1, 2, 5, 11, 1},
        {1, 1, 1, 1, 1}
    };

    int level2Data[LEVEL_2_DIMENSION_X][LEVEL_2_DIMENSION_Y] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 2, 2, 2, 2, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 2, 2, 2, 3, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };



    switch (level) {
    case 1: {
        Background* background = new Background();
        background->initialise();
        ObjectManager::instance.AddItem(background);
        // Load level 1 data
        for (int x = 0; x < LEVEL_1_DIMENSION_X; x++) {
            for (int y = 0; y < LEVEL_1_DIMENSION_Y; y++) {
                switch (level1Data[x][y]) {
                //wall
                case 1: {
                    // Load wall
                    LoadWall(x, y);
                    break;
                }
                //floor
                case 2: {
                    // Load floor
                    LoadFloor(x, y);
                    break;
                }
                //player spawn
                case 3: {
                    // Load player spawn point
                    LoadSpawnPoint(x, y);
                    break;
                }
                //finishline
                case 4: {
                    // Load level end
                    LoadLevelEnd(x, y);
                    break;
                }
                //spikes
                case 5: {
                    LoadFloor(x, y);
                    double angle = 0;
                    if (level1Data[x-1][y] == 1) {
                        angle = 90;
                    }else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    else if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    }
                    else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    }
                    LoadSpikes(x, y, angle);
                    break;
                }
                //upboost
                case 6:{
                    LoadBoost(x, y, 0);
                    break;
                }
                //rightboost
                case 7: {
                    LoadBoost(x, y, 90);
                    break;
                }
                //downboost
                case 8: {
                    LoadBoost(x, y, 180);
                    break;
                }
                //leftboost
                case 9: {
                    LoadBoost(x, y, 270);
                    break;
                }
                //turret horizontal
                case 10: {
                    int angle = 0;
                    if (level1Data[x - 1][y] == 1) {
                        angle = 90;
                    }
                    else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    else if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    }
                    else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    }
                    LoadFloor(x, y);
                    LoadTurret(x, y, angle); 
                    break;
                }
                //turret vertical
                case 11: {
                    int angle = 0;
                    if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    } else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    } else if (level1Data[x - 1][y] == 1) {
                        angle = 90;
                    } else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    LoadFloor(x, y);
                    LoadTurret(x, y, angle);
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
        for (int x = 0; x < LEVEL_2_DIMENSION_X; x++) {
            for (int y = 0; y < LEVEL_2_DIMENSION_Y; y++) {
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
                case 5: {
                    LoadFloor(x, y);
                    double angle = 0;
                    if (level1Data[x - 1][y] == 1) {
                        angle = 90;
                    }
                    else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    else if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    }
                    else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    }
                    LoadSpikes(x, y, angle);
                    break;
                }
                //upboost
                case 6: {
                    LoadBoost(x, y, 0);
                    break;
                }
                //rightboost
                case 7: {
                    LoadBoost(x, y, 90);
                    break;
                }
                //downboost
                case 8: {
                    LoadBoost(x, y, 180);
                    break;
                }
                //leftboost
                case 9: {
                    LoadBoost(x, y, 270);
                    break;
                }
                      //turret horizontal
                case 10: {
                    int angle = 0;
                    if (level1Data[x - 1][y] == 1) {
                        angle = 90;
                    }
                    else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    else if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    }
                    else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    }
                    LoadFloor(x, y);
                    LoadTurret(x, y, angle);
                    break;
                }
                       //turret vertical
                case 11: {
                    int angle = 0;
                    if (level1Data[x][y - 1] == 1) {
                        angle = 0;
                    }
                    else if (level1Data[x][y + 1] == 1) {
                        angle = 180;
                    }
                    else if (level1Data[x - 1][y] == 1) {
                        angle = 90;
                    }
                    else if (level1Data[x + 1][y] == 1) {
                        angle = 270;
                    }
                    LoadFloor(x, y);
                    LoadTurret(x, y, angle);
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
    tile->Initialise("assets/bricks.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), 0, TILE_SCALE);
    tile->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadFloor(int x, int y)
{
    // Load floor
    Tile* tile = new Tile(ObjectType::TILE);
    tile->Initialise("assets/floortile.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), 0, TILE_SCALE);
    tile->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadBoost(int x, int y, double angle)
{
    // Load floor
    Tile* tile = new Tile(ObjectType::BOOST);
    tile->Initialise("assets/floortile.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), angle, TILE_SCALE);
    tile->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadSpawnPoint(int x, int y)
{
    Tile* tile = new Tile(ObjectType::SPAWNPOINT);
    tile->Initialise("assets/floortile.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), 0, TILE_SCALE);
    tile->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadLevelEnd(int x, int y)
{
    Tile* tile = new Tile(ObjectType::LEVELEND);
    tile->Initialise("assets/floortile-finish.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), 0, TILE_SCALE);
    tile->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(tile);
}

void LevelLoader::LoadSpikes(int x, int y, double angle)
{
    Spikes* spikes = new Spikes();
    spikes->Initialise("assets/spikes.png", Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), angle, TILE_SCALE);
    spikes->SetDimensions(TILE_DIMENSION, TILE_DIMENSION);
    ObjectManager::instance.AddItem(spikes);
}

void LevelLoader::LoadTurret(int x, int y, double angle)
{
    // Load turret
    Turret* turret = new Turret();
    turret->Initialise(Vector2D(x * TILE_DIMENSION * TILE_SCALE, y * TILE_DIMENSION * TILE_SCALE), angle, TILE_SCALE);
    ObjectManager::instance.AddItem(turret);
}
