#include "Papan.h"
#include <Windows.h>
#include <fstream>

vector<string> Papan::getMap(int index)
{
	return maap[index];
}

void Papan::ShowMap()
{
	system("cls");
	if (lvl == 'A') {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (i == musuh[0]->getPosisiX() && j == musuh[0]->getPosisiY()) {
					cout << "X";
				}
				else if (i == treasure[0]->getPosisiX() && j == treasure[0]->getPosisiY()) {
					cout << "Y";
				}
				else cout << maap[0][i][j];
			}cout << endl;
		}
	}
}

void Papan::ReadMap()
{

	ifstream a("map.txt", ios::in);
	string hold;
	int map_easy, map_med, map_hard;
	a>>map_easy>>map_med>>map_hard; //read data from a file
	for (int i = 0; i < map_easy; ++i) {
		for (int j = 0; j < 4; ++j) {
			a >> hold;
			maap[0].push_back(hold);
		}
	}

	for (int i = 0; i < map_med; ++i) {
		for (int j = 0; j < 16; ++j) {
			a >> hold;
			maap[1].push_back(hold);
		}
	}

	for (int i = 0; i < map_hard; ++i) {
		for (int j = 0; j < 32; ++j) {
			a >> hold;
			maap[2].push_back(hold);
		}
	}
	a.close();

}

Papan::Papan()
{
	reggu = new Character;
}

Papan::~Papan()
{
}

void Papan::setLuaspandang(int luaspandang)
{
	this->luaspandang = luaspandang;
}

int Papan::getLuaspandang()
{
	return luaspandang;
}

void Papan::setPanjangX(int panjangX)
{
	this->panjangX = panjangX;
}

int Papan::getPanjangX()
{
	return panjangX;
}

void Papan::setPanjangY(int panjangY)
{
	this->panjangY = panjangY;
}

int Papan::getPanjangY()
{
	return panjangY;
}

void Papan::setLvl(char lvl)
{
	this->lvl = lvl;
	if (lvl == 'A') {
		Monster *holder = new Monster;
		holder->setPosisiX(0);
		holder->setPosisiY(0);
		musuh.push_back(holder);
	
		for (int i = 0; i < 3; ++i) {
			Relik *holderr = new Relik;
			holderr->setPosisiX(3);
			holderr->setPosisiY(3);
			treasure.push_back(holderr);
		}
	}
}

char Papan::getLvl()
{
	return lvl;
}
