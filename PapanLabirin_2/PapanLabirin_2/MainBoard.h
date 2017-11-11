#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Dynamic.h"
#include "MainCharacter.h"

class MainBoard
{
public:
	MainBoard();
	~MainBoard();
	static MainBoard* main;
	int GetBoardSize();
	GameObject* GetLocationData(Vector2 pos);
	void SetBoardSize(int size);
	void AdvanceStep();

private:
	vector<Dynamic*> enemyData;
	vector<vector<GameObject*> > boardMap;
	void SwapGameObject(GameObject* first, GameObject* second);
	int boardSize;
	
};

