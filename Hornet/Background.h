#pragma once
#include "GameObject.h"
class Background :
    public GameObject
{
public:
    Background();
    void initialise();
    void Update(double frametime) override;
};

