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
	if (currentlvl == 10) lvl = 3;
	else if (currentlvl == 3) lvl = 2;
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
	int arr[21][21];
	for (int i = 0;i < boardSizez;i++) {
		for (int j = 0; j < boardSizez; j++) {
			int objectType = mapData.get() - '0';
			arr[i][j] = objectType;
		}
		mapData.get();
		wxMessageOutputDebug().Printf("%d%d%d%d%d%d%d%d%d%d", arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6],
			arr[i][7],arr[i][8],arr[i][9]);
	}
	
	for (int i = 0; i < boardSizez; i++) {
		for (int j = 0; j < boardSizez; ++j) {
			string wall_str;
			int kiri_atas = 0, atas = 0, kanan_atas = 0;
			int kiri = 0, kanan = 0;
			int kiri_bawah = 0, bawah = 0, kanan_bawah = 0;
			switch (arr[i][j]) {
			case 1:
				
				if (i - 1 < 0) {
					atas = 1; kanan_atas = 1; kiri_atas = 1;
				}
				if (i + 1 == boardSizez) { bawah = 1; kiri_bawah = 1; kanan_bawah = 1; }
				if (j - 1 < 0) { kiri = 1; kiri_atas = 1; kiri_bawah = 1; }
				if (j + 1 == boardSizez) {
					kanan_atas = 1; kanan = 1; kanan_bawah = 1;
				}

					if (i - 1 >= 0 && arr[i-1][j] == 1) atas = 1;
					if (i + 1 < boardSizez && arr[i+1][j] == 1) bawah = 1;
					if (j- 1 >= 0 && arr[i][j-1] == 1) kiri = 1;
					if (j + 1 < boardSizez && arr[i][j+1] == 1) kanan = 1;
					if (i - 1 >= 0 && j - 1 >= 0 && arr[i-1][j - 1] == 1) { kiri_atas = 1; }
					if (i + 1 < boardSizez && j - 1 >= 0 && arr[i + 1][j - 1] == 1) { kiri_bawah = 1; }
					if (i - 1 >= 0 && j + 1 < boardSizez && arr[i - 1][j + 1] == 1) kanan_atas = 1;
					if (i + 1 >= 0 && j + 1 < boardSizez && arr[i + 1][j + 1] == 1) kanan_bawah = 1;

					if (!kiri_atas && !atas && !kanan_atas && !kiri &&
						!kanan && !kiri_bawah && !bawah && !kanan_bawah) wall_str = "Wall5";
					else if (kiri_atas && atas && bawah && kiri &&
						kanan && kiri_bawah && kanan_bawah && kanan_atas) wall_str = "Wall0";
					else if (atas && kiri & bawah && kanan && kiri_atas && kiri_bawah && kanan_bawah) wall_str = "Wall10";
					else if (atas && kiri && kanan && bawah && kiri_bawah && kanan_atas &&kiri_atas) wall_str = "Wall11";
					else if (atas && kiri_atas && kiri && kanan && bawah && kanan_atas && kanan_bawah) wall_str = "Wall12";
					else if (atas && kanan_atas && kiri && kanan && kiri_bawah && bawah && kanan_bawah) { wall_str = "Wall13"; }
					else if (kiri_atas && atas && kiri && kiri_bawah && bawah &&!kanan) wall_str = "Wall1";
					else if (atas && bawah && kanan && bawah && kanan_bawah && !kiri && kanan_atas) wall_str = "Wall2";
					else if (bawah && kiri && kanan && kiri_bawah && kanan_bawah &&!atas) wall_str = "Wall3";
					else if (kiri_atas && atas && kanan_atas && kiri && kanan &&!bawah) wall_str = "Wall4";
					else if (bawah && kanan && kanan_bawah &&!kiri && !atas && !kiri_atas) { wall_str = "Wall6"; }
					else if (kiri && kiri_bawah && bawah &&!kanan && !atas && !kanan_atas) wall_str = "Wall7";
					else if (atas && kiri_atas && kiri&& !kanan && !bawah && !kanan_bawah ) wall_str = "Wall8";
					else if (atas && kanan_atas && kanan && !kiri && !bawah && !kiri_bawah)wall_str = "Wall9";
					else if (kiri && atas && bawah && kanan && !kanan_atas && !kanan_bawah) wall_str = "Wall17";
					else if (kanan && atas && bawah && kanan && kanan_atas && kiri && !kiri_atas && !kiri_bawah) wall_str = "Wall15";
					else if (kiri&&kanan&&atas &&bawah && !kiri_bawah && !kanan_bawah) wall_str = "Wall14";
					else if (kiri && kanan && atas && bawah && kiri_bawah && !kiri_atas && !kanan_atas) wall_str = "Wall16";
					else if (kiri && !atas && !bawah && !kanan && !kanan_atas && !kanan_bawah) wall_str = "Wall19";
					else if (kanan && !atas && !bawah && !kiri && !kiri_atas && !kiri_bawah)wall_str = "Wall19";
					else if (atas && !kanan && !kiri && !bawah && !kanan_bawah && !kiri_bawah)wall_str = "Wall18";
					else if (bawah && !atas && !kiri && !kanan && !kiri_atas && !kanan_atas && kiri_bawah) wall_str = "Wall18";
					else if (((atas && bawah)|| atas ||bawah)  && !kiri && !kanan) wall_str = "Wall18";
					else if (kiri && kanan && !atas && !bawah) wall_str = "Wall19";
					else if (kiri && bawah && !atas && !kanan  && !kanan_atas && !kiri_bawah ) wall_str = "Wall20";
					else if (atas && kanan && !kiri&& !kanan_atas && !bawah && !kiri_bawah) wall_str = "Wall22";
					else if (kiri && atas && !kanan && !kiri_atas && !bawah )wall_str = "Wall21";
					else if (bawah && kanan && !atas && !kiri && !kiri_atas && !kanan_bawah) wall_str = "Wall23";
					else if (kiri && atas && kanan &&!bawah && !kiri_atas && !kanan_atas) wall_str = "Wall24";
					else if (atas && kanan && bawah && !kiri && !kanan_atas && !kanan_bawah) wall_str = "Wall25";
					else if (kiri &&  kanan && bawah && !atas && !kiri_bawah && !kanan_bawah) wall_str = "Wall26";
					else if (kiri && atas && bawah && !kanan && kiri_atas && !kiri_bawah) wall_str = "Wall27";
					else if (kiri && bawah && kanan && kiri_bawah && !kanan_bawah && !atas) wall_str = "Wall28";
					else if (atas && kiri && bawah && kiri_atas && !kanan && !kiri_bawah) wall_str = "Wall29";
					else if (atas && kiri && kanan && kanan_atas && !bawah && !kiri_atas) wall_str = "Wall30";
					else if (atas && kanan && bawah && kanan_bawah && !kanan_atas && !kiri) wall_str = "Wall31";
					else if (atas && kiri && bawah && kiri_bawah && !kanan && !kiri_atas) wall_str = "Wall32";
					else if (atas && kiri && kanan && kiri_atas && !bawah && !kanan_atas) wall_str = "Wall33";
					else if (atas && kanan && bawah && kanan_atas && !kiri && !kanan_bawah)wall_str = "Wall34";
					else if (kiri && kanan && bawah && kanan_bawah && !atas && !kiri_bawah) wall_str = "Wall35";
					else wall_str = "Wall";
			

				//wall_str = "Wall";
				boardMap[j][i] = Factory::CreateObject(wall_str);
				break;
			case 2:
				boardMap[j][i] = Factory::CreateObject("Enemy");
				enemyData.push_back((Dynamic*)boardMap[j][i]);
				break;
			case 3:
				boardMap[j][i] = Factory::CreateObject("Relic");
				requiredRelic++;
				wxMessageOutputDebug().Printf("Required Relic %d", requiredRelic);
				break;
			case 4:
				boardMap[j][i] = Factory::CreateObject("Player");
				player = (MainCharacter*)boardMap[j][i];

				if (j - 5 >= 0 && j + 4 < boardSize) {
					yStart = j - 5;
				}
				else if (j >= 10) {
					yStart = 10;
				}
				else yStart = 0;

				if (i - 5 >= 0 && i + 4 < boardSize) {
					xStart = i - 5;
				}
				else if (i >= 10) {
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

/*
*/