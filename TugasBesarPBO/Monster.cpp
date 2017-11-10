#include "Monster.h"

Monster::~Monster()
{
}

Monster::Monster()
{
}

void Monster::gerakAcak(vector<string>map) //sementara fully random aja, klo udah advanced baru ada polanya
{
	char flag = '0';
	while (flag == '0') {
		srand((unsigned)time(NULL));

		gerak = (rand() % 4); // random valuenya, mod 4 agar keluarnya rentang 0-3
		if (gerak == 0 && getPosisiX()+1<map.size() &&map[getPosisiX() + 1][getPosisiY()] != '1') {
			setPosisiX(1); //keatas
			flag = '1';
		}
		else if (gerak == 1 && getPosisiX()-1>0 && map[getPosisiX() - 1][getPosisiY()] != '1') {
			setPosisiX(-1); //kebawah
			flag = '1';
		}
		else if (gerak == 2 && getPosisiY()+1<map[0].length() && map[getPosisiX()][getPosisiY() + 1] != '1') {
			setPosisiY(1); //kekanan
			flag = '1';
		}
		else if (gerak == 3 && getPosisiY()-1>0 && map[getPosisiX()][getPosisiY() - 1] != '1') {
			setPosisiY(-1); //kekiri
			flag = '1';
		}
	}
}
