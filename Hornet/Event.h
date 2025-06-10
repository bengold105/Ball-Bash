#pragma once
#include "vector2D.h"
#include <vector>
enum EventType { NONE, EXPLOSION, OBJECTCREATED, OBJECTDESTROYED, MISSIONCOMPLETE, LEVELEND, PLAYERDEAD, PLAYERLAUNCHED, REMOVETUTORIAL, CHEAT, PLAYERSPAWNED};

class GameObject;

struct Event
{
	GameObject* pSource;
    std::vector<GameObject*> objectList;
	EventType type;
	Vector2D position;
	double data1;
	double data2;
};

