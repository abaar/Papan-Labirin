#pragma once
#include "Definer.h"
#include "GameObject.h"
#include "Static.h"
#include "Dynamic.h"
#include "Enemy.h"
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
	MainCharacter *mainPlayer;


private:
	vector<Vector2> enemyData; //it should be enemy , so enemy data got the monster special move
	vector<vector<GameObject*> > boardMap;
	//Kegunaan EnemyData apa kalau datanya sudah di simpan di BoardMap?
	//di copy? ngehabisin memory :(
		//Mending GameObjectnya ditambahi fungsi move buat gerakin monster
		//gak usah pake static & dynamic & EnemyData diganti vector yg hold Vector2 koordinat enemy
		//jd nanti yg di otak atik boardMap di alamat enemydata.
	
	
	int boardSize;
	
};

