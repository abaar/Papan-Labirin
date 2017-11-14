#include "MainCharacter.h"

MainCharacter::MainCharacter(string name)
{
	playerName = name;
	SetPosition(0, 0); //initialize that a player always starts at 0 0
}

MainCharacter::~MainCharacter()
{
}

int MainCharacter::onCollision(GameObject & collider)
{
	return 0;
}
