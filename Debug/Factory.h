#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Dynamic.h"
#include "MainCharacter.h"
class Factory
{
public:
	Factory();
	~Factory();
	static GameObject* CreateObject(string name);
};

