#include "Dynamic.h"
#include "Definer.h"
#include "MainBoard.h"
#include "GameObject.h"


Dynamic::Dynamic()
{
}


Dynamic::~Dynamic()
{
}

int Dynamic::Move()
{

	int xPos = rand() % 3 - 1;
	int yPos = 0;
	if (xPos == 0) {
		yPos = rand() % 3 - 1;
	}
	Vector2 moveData(xPos, yPos);
	int tempData = Move(moveData);
	return tempData;

}

void Dynamic::Destroy()
{
	delete this;
}

int Dynamic::Move(Vector2 pos)
{
	GameObject *collider = MainBoard::main->GetLocationData(Vector2(this->GetPosition().first + pos.first, this->GetPosition().second + pos.second));
	//GameObject *collider = NULL;
	if (collider->GetName() == "Wall") {
		return 0;
	}
	else if (collider->GetName() == "Enemy") {
		if (this->GetName() == "Enemy") {
			return 0;
		}
		else if (this->GetName() == "Player" || this->GetName() == "Player1" || this->GetName() == "Player2"
			|| this->GetName() == "Player3") {
			wxMessageOutputDebug().Printf("Game Ended, Player Dead");
			MainBoard::main->ResetMyImageWindow(MainBoard::main->GetCurrentMap(), 0);
		}
		else {
			MainBoard::main->SwapGameObject(this, collider);
			return 1;
		}
	}
	else if (collider->GetName() == "Relic") {
		if (this->GetName() == "Player" || this->GetName() == "Player1" || this->GetName() == "Player2"
			|| this->GetName() == "Player3") {
			MainBoard::main->DecrementRelic();
			MainBoard::main->SwapGameObject(this, collider);
			MainBoard::main->FillTile(collider, "Free");
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (collider->GetName() == "Portal") {
		if (this->GetName() == "Player" || this->GetName() == "Player1" || this->GetName() == "Player2"
			|| this->GetName() == "Player3") {
			wxMessageOutputDebug().Printf("Game Ended, Player Escaped");
			MainBoard::main->ResetMyImageWindow(MainBoard::main->GetCurrentMap(), 1);
		}
		return 0;
	}
	else  if (collider->GetName() == "Free") {
		if (this->GetName() == "Player" || this->GetName() == "Player1" || this->GetName() == "Player2"
			|| this->GetName() == "Player3") {
			MainBoard::main->SwapGameObject(this, collider);
			return 1;
		}
		else if (this->GetName() == "Enemy") {
			MainBoard::main->SwapGameObject(this, collider);
			return 1;
		}
	}
	else if (collider->GetName() == "Player" || collider->GetName() == "Player1" ||
		collider->GetName() == "Player2" || collider->GetName() == "Player3") {
		if (this->GetName() == "Enemy") {
			wxMessageOutputDebug().Printf("Game Ended, Player Eaten by Enemy cuk");
			MainBoard::main->ResetMyImageWindow(MainBoard::main->GetCurrentMap(), 0);
		}
	}
}


