#include "MainCharacter.h"






MainCharacter::MainCharacter(string name)
{
	playerName = name;
}

MainCharacter::~MainCharacter()
{
}

int MainCharacter::onCollision(GameObject & collider)
{
	return 0;
}
