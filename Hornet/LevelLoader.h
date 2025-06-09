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
    void LoadBoost(int x, int y, double angle);
    void LoadSpawnPoint(int x, int y);
    void LoadLevelEnd(int x, int y);
    void LoadSpikes(int x, int y, double angle);
    void LoadTurret(int x, int y, double angle);
};

