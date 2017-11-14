#pragma once
#include "GameObject.h"
#include "MainBoard.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();
	virtual void move();
private:
	bool left;
	bool right;
	bool up;
	bool down;
};

