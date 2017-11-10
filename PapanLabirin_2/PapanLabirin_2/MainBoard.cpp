#include "MainBoard.h"



MainBoard::MainBoard()
{
	boardSize = 5;
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
