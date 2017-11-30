#pragma once
#include "GameObject.h"

class Dynamic :
	public GameObject
{
public:
	Dynamic();
	~Dynamic();
	virtual int Move();
	int Move(Vector2 pos);
};

