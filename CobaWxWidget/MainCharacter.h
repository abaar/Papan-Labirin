#pragma once
#include "Dynamic.h"


class MainCharacter : public Dynamic
{
public:
	MainCharacter();
	~MainCharacter();
private:
	string playerName;
};

