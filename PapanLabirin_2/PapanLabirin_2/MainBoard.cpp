#include "MainBoard.h"


MainBoard* MainBoard::main = NULL;

MainBoard::MainBoard()
{
	boardSize = 0;
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
		enemyData[i]->Move();
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
				boardMap[j][i] = Factory::CreateObject("Wall");
				break;
			case 2:
				boardMap[j][i] = Factory::CreateObject("Enemy");
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
