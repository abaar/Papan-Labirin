#include "Static.h"



Static::Static()
{
}


Static::~Static()
{
}

int Static::onCollision(GameObject *collider)
{
	return 0;
}

void Static::Destroy()
{
	delete this;
}
