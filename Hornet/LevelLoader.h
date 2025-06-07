#pragma once
class LevelLoader
{
public:
    LevelLoader();
    // Load a level from a file (1, 2 or 3)
    bool LoadLevel(int level);
private:
    void LoadWall(int x, int y);
    void LoadFloor(int x, int y);
    void LoadSpawnPoint(int x, int y);
    void LoadLevelEnd(int x, int y);

};

