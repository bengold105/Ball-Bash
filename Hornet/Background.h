#pragma once
#include "GameObject.h"
class Background :
    public GameObject
{
public:
    Background();
    void initialise();
    void initialise(const char* image);
    void Update(double frametime) override;
};

