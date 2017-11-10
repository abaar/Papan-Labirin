#include "ObjekGame.h"
#include <time.h>
#include <windows.h>
#include <vector>
#pragma once
class Monster :public ObjekGame {
private:
	int gerak;
public:
	~Monster();
	Monster();
	void gerakAcak(vector<string>map);
};