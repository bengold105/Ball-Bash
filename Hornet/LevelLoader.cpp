#include "LevelLoader.h"
#include "Tile.h"
#include "ObjectManager.h"

const int tileDimension = 64;
const int tileScale = 6;

LevelLoader::LevelLoader()
{
}

bool LevelLoader::LoadLevel(int level)
{
    int level1Data[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 2, 2, 2, 1},
        {1, 2, 2, 2, 1},
        {1, 2, 3, 2, 1},
        {1, 1, 1, 1, 1}
    };




    switch (level) {
    case 1:
        // Load level 1 data
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                if (level1Data[x][y] == 1) {
                    // Load wall
                    Tile* tile = new Tile(ObjectType::WALL);
                    tile->Initialise("assets/bricks.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
                    tile->SetDimensions(tileDimension, tileDimension);
                    ObjectManager::instance.AddItem(tile);
                }
                else if (level1Data[x][y] == 2) {
                    // Load floor
                    Tile* tile = new Tile(ObjectType::TILE);
                    tile->Initialise("assets/floortile.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
                    tile->SetDimensions(tileDimension, tileDimension);
                    ObjectManager::instance.AddItem(tile);
                }
                else if (level1Data[x][y] == 3) {
                    // Load player spawn point
                    Tile* tile = new Tile(ObjectType::SPAWNPOINT);
                    tile->Initialise("assets/floortile.png", Vector2D(x * tileDimension * tileScale, y * tileDimension * tileScale), 0, tileScale);
                    tile->SetDimensions(tileDimension, tileDimension);
                    ObjectManager::instance.AddItem(tile);
                }
            }
        }
        return true;
    }





    return false;
}
