#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Dynamic.h"
#include "MainCharacter.h"
#include "Factory.h"

using namespace std;

class MainBoard
{
public:
	MainBoard();
	~MainBoard();
	static MainBoard* main;
	int GetBoardSize();
	bool LoadMap(string path);

	GameObject* GetLocationData(Vector2 pos);
	void SetBoardSize(int size);
	void AdvanceStep();
	void SwapGameObject(Vector2 first, Vector2 second);
	void SwapGameObject(GameObject* first, GameObject* second);

private:
	vector<Dynamic*> enemyData;
	vector<vector<GameObject*> > boardMap;
	
	
	int boardSize;
	
};

