#include <string>
#include <iostream>
#pragma once

using namespace std;

class ObjekGame {
private:
	int posisiX;
	int posisiY;
public:
	ObjekGame();
	~ObjekGame();
	void setPosisiX(int posisiX);
	int getPosisiX();
	void setPosisiY(int posisiY);
	int getPosisiY();
};
