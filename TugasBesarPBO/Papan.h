#include "ObjekGame.h"
#include "Character.h"
#include "Monster.h"
#include "Relik.h"
#include <vector>
#pragma once

class Papan {
private:
	vector<string>maap[3];
	char lvl;
	int panjangX;
	int panjangY;
	int luaspandang;
public:	
	vector<string> getMap(int index);
	Character *reggu;
	vector<Monster*>musuh;
	vector<Relik*>treasure;
	void ShowMap();
	void ReadMap();
	Papan();
	~Papan();
	void setLuaspandang(int luaspandang);
	int getLuaspandang();
	void setPanjangX(int panjangX);
	int getPanjangX();
	void setPanjangY(int panjangY);
	int getPanjangY();
	void setLvl(char lvl);
	char getLvl();
};
