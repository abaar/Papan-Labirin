#include "Enemy.h"
#include <string>


Enemy::Enemy()
{
	left = right = up = down = false;
}


Enemy::~Enemy()
{
}

void Enemy::move()
{
	wxMessageOutputDebug().Printf("Macuk!");
	Vector2 holder = GetPosition();
	GameObject *currentdata;
	if (!left && holder.second-1 >= 0 ) {
		holder.second--;
		currentdata = (MainBoard::main->GetLocationData(holder));
		if (currentdata->GetName() != "Wall") {
			MainBoard::main->SwapGameObject(holder, GetPosition());
			wxMessageOutputDebug().Printf("Left!");
				//swap an object in Current Position to holder.
					//the specific is moving left
		}
		else {
			left = true;
		}
	}
	else if (!up && holder.first-1 >=0) {
		holder.first--;
		currentdata = (MainBoard::main->GetLocationData(holder));
		if (currentdata->GetName() != "Wall") {
			MainBoard::main->SwapGameObject(holder, GetPosition());
			wxMessageOutputDebug().Printf("Up!");
			//swap an object in Current Position to holder.
				//the specific is moving up
		}
		else {
			up = true;
		}

	}
	else if (!right && holder.second+1 < MainBoard::main->GetBoardSize()) {
		holder.second++;
		currentdata = (MainBoard::main->GetLocationData(holder));
		if (currentdata->GetName() != "Wall") {
			MainBoard::main->SwapGameObject(holder, GetPosition());
			wxMessageOutputDebug().Printf("Right!");
			//swap an object in Current Position to holder.
			//the specific is moving right
		}
		else {
			right = true;
		}

	}
	else if (!down && holder.first+1 < MainBoard::main->GetBoardSize()) {
		holder.first++;
		currentdata = (MainBoard::main->GetLocationData(holder));
		if (currentdata->GetName() != "Wall") {
			MainBoard::main->SwapGameObject(holder, GetPosition());
			wxMessageOutputDebug().Printf("Down!");
			//swap an object in Current Position to holder.
			//the specific is moving up
		}
		else {
			down = true;
			if (left&&right&&up) up = false;
		}

	}

}
