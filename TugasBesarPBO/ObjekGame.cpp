#include "ObjekGame.h"

ObjekGame::ObjekGame()
{
	posisiX = 0;
	posisiY = 0;
}

ObjekGame::~ObjekGame()
{
}

void ObjekGame::setPosisiX(int posisiX)
{
	this->posisiX += posisiX; // -1 brarti keatas ; +1 brarti ke bawah
}

int ObjekGame::getPosisiX()
{
	return posisiX;
}

void ObjekGame::setPosisiY(int posisiY)
{
	this->posisiY += posisiY; // -1 brarti kekiri ; +1 brarti ke kanan
}

int ObjekGame::getPosisiY()
{
	return posisiY;
}
