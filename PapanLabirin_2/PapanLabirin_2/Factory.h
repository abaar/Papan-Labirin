#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Enemy.h"
class Factory
{
public:
	Factory();
	~Factory();
	static GameObject* CreateObject(string name);
};

