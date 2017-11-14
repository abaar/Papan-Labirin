#include "Factory.h"



Factory::Factory()
{
}


Factory::~Factory()
{
}

GameObject* Factory::CreateObject(string name)
{
	/*Use the concept of polymorphism so we can still access the function*/
	/*Thus we need to declare a function at GameObject, so it'll have the funciton in his child*/
	/*this case is Enemy's move*/ //maybe ^_^

	GameObject* data=NULL; 
	if (name == "Wall") {
		Static *polymorph;
		polymorph = new Static();
		polymorph->SetName(name);
		polymorph->SetBitMap("Wall.jpg");
		data = polymorph;
	}
	else if (name == "Enemy") {
		Enemy *polymorph;
		polymorph = new Enemy();
		polymorph->SetName(name);
		polymorph->SetBitMap("Enemy.jpg");
		data = polymorph;
	}
	else if (name == "Relic") {
		Static *polymorph;
		polymorph = new Static();
		polymorph->SetBitMap("Relic.jpg");
		data = polymorph;
	}
	else if (name == "Free") {
		Static *polymorph;
		polymorph = new Static();
		polymorph->SetBitMap("Free.jpg");
		data = polymorph;
	}
	else if (name == "Character") {
		MainCharacter *polymorph = new MainCharacter("");
		polymorph->SetBitMap("Char.jpg");
		data = polymorph;
	}
	
	return data;
}
