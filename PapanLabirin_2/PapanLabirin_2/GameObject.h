#pragma once
#include "Definer.h"


using namespace std;
class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPosition(int x, int y);
	void SetPosition(Vector2 &position);
	void SetName(string name);
	string GetName();
	Vector2 GetPosition();
	virtual int onCollision(GameObject &collider);
private:
	string objectName;
	int xPosition;
	int yPosition;
};

