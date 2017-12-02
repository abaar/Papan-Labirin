#include "MainBoard.h"


MainBoard* MainBoard::main = NULL;

MainBoard::MainBoard()
{
	boardSize = 0;
	dummyWall = (Static*)Factory::CreateObject("Wall");
	mywindow = nullptr;
	wxMessageOutputDebug().Printf("%d Initializing", boardSize);
	
}


MainBoard::~MainBoard()
{
	for (int i = 0;i < boardSize;i++) {
		for (int j = 0;j < boardSize;j++) {
			if (boardMap[j][i] != NULL) {
				boardMap[j][i]->Destroy();
			}
		}
	}
	dummyWall->Destroy();
}

int MainBoard::GetBoardSize()
{
	return boardSize;
}

int MainBoard::GetElapsedTime()
{
	return elapsedTime;
}

int MainBoard::GetRequiredRelic()
{
	return requiredRelic;
}

GameObject* MainBoard::GetLocationData(Vector2 pos)
{
	if (pos.first < 0 || pos.second < 0 || pos.first >= boardSize || pos.second >= boardSize) {
		return dummyWall;
	}
	return boardMap[pos.first][pos.second];
}

MainCharacter * MainBoard::GetPlayer()
{
	return player;
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
	if (first.first < 0 || first.second < 0 || first.first >= boardSize || first.second >= boardSize) {
		wxMessageOutputDebug().Printf("FIRST OUTOFBOUND!");
		return;
	}else if (second.first < 0 || second.second < 0 || second.first >= boardSize || second.second >= boardSize) {
		wxMessageOutputDebug().Printf("SECOND OUTOFBOUND!");
		return;
	}
	SwapGameObject(GetLocationData(first), GetLocationData(second));
}

void MainBoard::SwapGameObject(GameObject * first, GameObject * second)
{
	if (first->GetPosition().first != -1) {
		boardMap[first->GetPosition().first][first->GetPosition().second] = second;
	}
	boardMap[second->GetPosition().first][second->GetPosition().second] = first;
	Vector2 tempPosition = first->GetPosition();
	first->SetPosition(second->GetPosition());
	second->SetPosition(tempPosition);
	//wxMessageOutputDebug().Printf("Swapped %s with %s", first->GetName(),second->GetName());
	//wxMessageOutputDebug().Printf("Position first %s X:%d Y:%d second %s X:%d Y:%d", first->GetName(),first->GetPosition().first,first->GetPosition().second, second->GetName(),second->GetPosition().first,second->GetPosition().second);
}

void MainBoard::FillTile(Vector2 pos, string tileName)
{
	FillTile(GetLocationData(pos),tileName);
}

void MainBoard::FillTile(GameObject * data, string tileName)
{
	data->SetBitMap(tileName);
	data->SetName(tileName);
}

void MainBoard::IncrementTime()
{
	elapsedTime++;
}

void MainBoard::DecrementRelic()
{
	//wxMessageOutputDebug().Printf("Only %d relic left!", requiredRelic);

	if (requiredRelic > 0) {
		wxMessageOutputDebug().Printf("Only %d relic left!", --requiredRelic);
	}
	if (requiredRelic == 0) {
		FillTile(portalLocation, "Portal");
		wxMessageOutputDebug().Printf("ALL DONE YAY");
	}
}

void MainBoard::SetImageWindow(ImageWindow *temp)
{
	mywindow = temp; /*Somehow , error here*/
}

void MainBoard::ResetMyImageWindow(int currentlvl,int winloose)
{
	mywindow->ShutDown(currentlvl,winloose);
}

void MainBoard::ClearObject()
{
	enemyData.clear();
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			if (boardMap[j][i] != NULL) {
				wxMessageOutputDebug().Printf("Going to delete %s", boardMap[j][i]->GetName());
				boardMap[j][i]->Destroy(); //Do NOT EDIT, automatic delete operation!
			}
		}
	}
}

int MainBoard::GetViewSize()
{
	return viewSize;
}

void MainBoard::SetStart(Vector2 hold)
{
	xStart = hold.first;
	yStart = hold.second;
}

int MainBoard::GetCurrentMap()
{
	return ++current_map;
}

Vector2 MainBoard::GetStart()
{
	return Vector2(xStart, yStart);
}

bool MainBoard::LoadMap(string path)
{
	
	srand(time(NULL));
	ifstream mapData;
	requiredRelic = 0;
	mapData.open(path+".lmap");
	if (!mapData.is_open()) {
		return false;
	}
	int boardSizez;
	mapData >> boardSizez;
	mapData.get();
	SetBoardSize(boardSizez);
	boardMap.resize(boardSizez);
	for (int i = 0;i < boardSizez;i++) {
		boardMap[i].resize(boardSizez);
	}
	ClearObject();
	for (int i = 0;i < boardSizez;i++) {
		for (int j = 0;j < boardSizez;j++) {
			int objectType = mapData.get()-'0';
			switch (objectType) {
			case 1:
				boardMap[j][i] = Factory::CreateObject("Wall");
				break;
			case 2:
				boardMap[j][i] = Factory::CreateObject("Enemy");
				enemyData.push_back((Dynamic*)boardMap[j][i]);
				break;
			case 3:
				boardMap[j][i] = Factory::CreateObject("Relic");
				requiredRelic++;
				wxMessageOutputDebug().Printf("Required Relic %d",requiredRelic);
				break;
			case 4:
				boardMap[j][i] = Factory::CreateObject("Player");
				player = (MainCharacter*)boardMap[j][i];
				
				if (j - 5 >= 0 && j + 4 < boardSize) {
					yStart = j-5;
				}
				else if (j>=10) {
					yStart = 10;
				}
				else yStart = 0;

				if (i - 5 >= 0 && i + 4 < boardSize) {
					xStart = i-5;
				}
				else if (i>=10) {
					xStart = 10;
				}
				else xStart = 0;

				break;
			case 5:
				portalLocation = Vector2(j, i);
			default:
				boardMap[j][i] = Factory::CreateObject("Free");
				break;
			}
			boardMap[j][i]->SetPosition(Vector2(j, i));
		}
		mapData.get();
	}
	mapData.close();
	elapsedTime = 0;
	return true;
}

void MainBoard::SetLvl(int lvl)
{
	this->lvl = lvl;
	if (lvl == 3) {
		current_map = 10;
		viewSize = 10;
	}
	else if (lvl == 1) {
		viewSize = boardSize;
		current_map = 0;
	}
	else if (lvl == 2) {
		viewSize = boardSize;
		current_map = 3;
	}
}

int MainBoard::GetLvl()
{
	return lvl;
}

