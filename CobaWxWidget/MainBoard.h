#pragma once

#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Dynamic.h"
#include "MainCharacter.h"
#include "Factory.h"
#include "ImageWindow.h"

using namespace std;


class MainBoard
{
public:
	MainBoard();
	~MainBoard();
	static MainBoard* main;
	int GetBoardSize();
	int GetElapsedTime();
	int GetRequiredRelic();
	bool LoadMap(string path);
	void SetLvl(int lvl);
	int GetLvl();
	GameObject* GetLocationData(Vector2 pos);
	MainCharacter* GetPlayer();
	void SetBoardSize(int size);
	void AdvanceStep();
	void SwapGameObject(Vector2 first, Vector2 second);
	void SwapGameObject(GameObject* first, GameObject* second);
	void FillTile(Vector2 pos,string tileName);
	void FillTile(GameObject* data, string tileName);
	void IncrementTime();
	void DecrementRelic();
	void SetImageWindow(ImageWindow *temp);
	void ResetMyImageWindow(int currentlvl,int winloose);
	void ClearObject();
	int GetViewSize();
	void SetStart(Vector2 hold);
	void SetCurrentMap(int map);
	int GetCurrentMap();
	Vector2 GetStart();

private:
	ImageWindow *mywindow;
	vector<Dynamic*> enemyData;
	vector<vector<GameObject*> > boardMap;
	Vector2 portalLocation;
	MainCharacter* player;
	int elapsedTime;
	int boardSize;
	int requiredRelic;
	Static* dummyWall;
	int lvl;
	int viewSize;
	int xStart;
	int yStart;
	int current_map;
};

