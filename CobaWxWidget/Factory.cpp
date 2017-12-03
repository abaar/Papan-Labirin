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
	string b;
	for (int i = 0; i < 4; ++i) b += name[i];
	if (b == "Wall") {
		data = new Static();
		data->SetName(b);
		data->SetBitMap(name);
	}
	else if (name == "Enemy") {
		data = new Dynamic();
		data->SetName(name);
		data->SetBitMap("Enemy");
	}
	else if (name == "Relic") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Relic");
	}
	else if (name == "Free") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Free");
	}
	else if (name == "Player") {
		data = new MainCharacter();
		data->SetName(name);
		data->SetBitMap("Player");
	}
	else if (name == "Portal") {
		data = new Static();
		data->SetName(name);
		data->SetBitMap("Portal");
	}
	return data;
}
