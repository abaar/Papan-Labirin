#pragma once
#include "GameObject.h"

class Dynamic :
	public GameObject
{
public:
	Dynamic();
	~Dynamic();
	virtual int Move();
	void Destroy();
	int Move(Vector2 pos);
};

