#include "MainBoard.h"


MainBoard* MainBoard::main = NULL;

MainBoard::MainBoard()
{
	boardSize = 0;
	mainPlayer = new MainCharacter("");
	LoadMap("test");
	/*
	SetBoardSize(5);
	for (int i = 0;i < boardSize;i++) {
		for (int j = 0;j < boardSize;j++) {
			boardMap[i][j] = new Static();
			boardMap[i][j]->SetName("Wall");
			boardMap[i][j]->SetBitMap("Wall.jpg");
		}
	}
	*/

}


MainBoard::~MainBoard()
{
	delete mainPlayer;
	//here , should delete board Map since boardMap hold a 
		//heap memory from Factory CreateObject
}

int MainBoard::GetBoardSize()
{
	return boardSize;
}

GameObject* MainBoard::GetLocationData(Vector2 pos)
{
	return boardMap[pos.first][pos.second];
}

void MainBoard::SetBoardSize(int size)
{
	if (boardMap.size() < size) {
		boardMap.resize(size);
		for (int i = 0;i < boardMap.size();i++) {
			boardMap[i].resize(size);
		}
	}
	boardSize = size;

}

void MainBoard::AdvanceStep()
{
	for (int i = 0;i < enemyData.size();i++) {
		Vector2 holder = enemyData[i],target_movement;
		target_movement = boardMap[holder.first][holder.second]->move(); //move return a Vector2 value
		SwapGameObject(holder, target_movement); //swap the object
											//thus , we must ensure that we swap the enemy
											//with a free object. It is done in move().
	}
}

void MainBoard::SwapGameObject(Vector2 first, Vector2 second)
{
	SwapGameObject(GetLocationData(first), GetLocationData(second));
}

void MainBoard::SwapGameObject(GameObject * first, GameObject * second)
{
	boardMap[first->GetPosition().first][first->GetPosition().second] = second;
	boardMap[second->GetPosition().first][second->GetPosition().second] = first;
	wxMessageOutputDebug().Printf("Swapped %s with %s", first->GetName(),second->GetName());
}

bool MainBoard::LoadMap(string path)
{
	ifstream mapData;
	mapData.open(path+".lmap");
	if (!mapData.is_open()) {
		return false;
	}
	int boardSizez;
	mapData >> boardSizez;
	mapData.get();
	SetBoardSize(boardSizez);
	for (int i = 0;i < boardSizez;i++) {
		for (int j = 0;j < boardSizez;j++) {
			int objectType = mapData.get()-'0';
			switch (objectType) {
			case 1:
				boardMap[j][i] = Factory::CreateObject("Wall"); //enemyData trus gunanya apa?
				break;
			case 2:
				boardMap[j][i] = Factory::CreateObject("Enemy");
				enemyData.push_back(Vector2(j, i)); //to know where the enemies are at initialization
				break;
			case 3:
				boardMap[j][i] = Factory::CreateObject("Relic");
				break;
			default:
				boardMap[j][i] = Factory::CreateObject("Free");
				break;
			}
		}
		mapData.get();
	}
	mapData.close();
	return true;
}
