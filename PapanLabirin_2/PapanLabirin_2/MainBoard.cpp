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
	//here , should delete board Map since boardMap hold a 
		//heap memory from Factory CreateObject
	GameObject *deletion;
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			deletion = boardMap[i][j];
			delete deletion;
		}
	}
	boardMap.clear();
} //obj deletion automatically deleted here, it is only a pointer to reference
	//boardMap which hold a heap memmory. Maybe. 

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
		Vector2 holder = enemyData[i];
		boardMap[holder.first][holder.second]->move(); //here,the positionX & Y will change
		//so ensure that the movement doesn't hit the wall or out of the map
		
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

void MainBoard::setPlayerCat(Vector2 playerCat)
{
	this->playerCat = playerCat;
}

Vector2 MainBoard::getPlayerCat()
{
	return playerCat;
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
				boardMap[j][i]->SetPosition(Vector2(j, i));
				break;
			case 2:
				boardMap[j][i] =Factory::CreateObject("Enemy");
				boardMap[j][i]->SetPosition(Vector2(j, i));
				enemyData.push_back(Vector2(j,i)); //to know where the enemies are at initialization
				break;
			case 3:
				boardMap[j][i] = Factory::CreateObject("Relic");
				boardMap[j][i]->SetPosition(Vector2(j, i));
				break;
			case 4:
				boardMap[j][i] = Factory::CreateObject("Character");
				boardMap[j][i]->SetPosition(Vector2(j, i));
				playerCat = Vector2(j, i);
				break;
			default:
				boardMap[j][i] = Factory::CreateObject("Free");
				boardMap[j][i]->SetPosition(Vector2(j, i));
				break;
			}
		}
		mapData.get();
	}
	mapData.close();
	return true;
}
