#pragma once
#include "GameObject.h"
class Static :
	public GameObject
{
public:
	Static();
	~Static();
	int onCollision(GameObject *collider);
};

