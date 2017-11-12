#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}

GameObject* Factory::CreateObject(string name)
{
	GameObject* data=NULL;
	if (name == "Wall") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Wall.jpg");
	}
	else if (name == "Enemy") {
		data = new Dynamic();
		data->SetName(name);
		data->SetBitMap("Enemy.jpg");
	}
	else if (name == "Relic") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Relic.jpg");
	}
	else if (name == "Free") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Free.jpg");
	}
	return data;
}
