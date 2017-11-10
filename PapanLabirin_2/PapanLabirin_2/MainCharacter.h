#pragma once
#include "GameObject.h"
class MainCharacter : public GameObject
{
public:
	MainCharacter(string name);
	~MainCharacter();
	int onCollision(GameObject &collider);
private:
	string playerName;
};

