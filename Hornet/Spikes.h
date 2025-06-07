#pragma once
#include "GameObject.h"


class Spikes : public GameObject
{
public:
    Spikes();
    void Initialise(const char* image, Vector2D position, double angle, double scale) override;
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
    void Render() override;
    void SetDimensions(int width, int height);
private:
    Rectangle2D m_collisionShape;
    int m_width;
    int m_height;
};

