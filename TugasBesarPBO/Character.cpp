#include "Character.h"

void Character::gerakin()
{
	while (getNyawa() > 0) {
		if (gerakan == 'w' || gerakan == 'W') { //jika dia pencet w keatas
			setPosisiX(-1);
		}
		else if (gerakan == 's' || gerakan == 'S'){ //pencet s kebawah
			setPosisiX(1);
		}
		else if (gerakan == 'a' || gerakan == 'A') { //pencet a kekiri
			setPosisiY(-1);
		}
		else if (gerakan == 'd' || gerakan == 'D') { //pencet d kekanan
			setPosisiY(1);
		}
	}
}

Character::Character()
{
	nyawa = 1; //inisialisasi nyawa karakter
}

Character::~Character()
{
}

void Character::setName(string name)
{
	this->name = name;
}

string Character::getName()
{
	return name;
}

void Character::setNyawa(int nyawa)
{
	this -> nyawa += nyawa; //klo m ati argument parameter tinggal di minus -1 aja
}

int Character::getNyawa()
{
	return nyawa;
}
