#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::SetPosition(int x, int y)
{
	xPosition = x;
	yPosition = y;
}



void GameObject::SetPosition(Vector2 &position)
{
	xPosition = position.first;
	yPosition = position.second;
}

void GameObject::SetName(string name)
{
	objectName = name;
}

string GameObject::GetName()
{
	return objectName;
}

Vector2 GameObject::GetPosition()
{
	return Vector2(xPosition,yPosition);
}

int GameObject::onCollision(GameObject & collider)
{
	return 0;
}
