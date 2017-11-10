#include "ObjekGame.h"
#pragma once
class Character : public ObjekGame{
private :
    string name;
    int nyawa;
    char gerakan;
public:
	void gerakin();
	Character();
	~Character();
	void setName(string name);
	string getName();
	void setNyawa(int nyawa);
	int getNyawa();
};