#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Dynamic.h"
#include "MainCharacter.h"

class MainBoard
{
public:
	MainBoard();
	~MainBoard();
	
	int GetBoardSize();
	GameObject* GetLocationData(Vector2 pos);
	void SetBoardSize(int size);
	void AdvanceStep();

private:
	vector<Dynamic*> enemyData;
	GameObject* boardMap[11][11];
	void SwapGameObject(GameObject* first, GameObject* second);
	int boardSize;
	
};

