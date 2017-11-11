#include "MainBoard.h"

MainBoard* MainBoard::main = NULL;

MainBoard::MainBoard()
{
	
	SetBoardSize(5);
	for (int i = 0;i < boardSize;i++) {
		for (int j = 0;j < boardSize;j++) {
			boardMap[i][j] = new Static();
			boardMap[i][j]->SetName("Wall");
			boardMap[i][j]->SetBitMap("Wall.jpg");
		}
	}

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

void MainBoard::SwapGameObject(GameObject * first, GameObject * second)
{
	boardMap[first->GetPosition().first][first->GetPosition().second] = second;
	boardMap[second->GetPosition().first][second->GetPosition().second] = first;
}
