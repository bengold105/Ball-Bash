#pragma once
#include "GameObject.h"
class Tile : public GameObject
{
public:
    Tile(ObjectType type);
    void Initialise(const char* image, Vector2D position, double angle, double scale) override;
    void Update(double frametime) override;
    void SetDimensions(int width, int height);
    double GetAngle();
    IShape2D& GetCollisionShape() override;
    void ProcessCollision(GameObject& other) override;
    void Render() override;
    void EnableBoost(bool enable);
private:
    bool enableBoost;
    double m_timer;
    bool pulsed;
    Rectangle2D m_collisionShape;
    int m_width;
    int m_height;
};

