#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
	delete sprite; //Should delete to avoid memory leak :)
}

void GameObject::SetPosition(int x, int y)
{
	xPosition = x;
	yPosition = y;
}



void GameObject::SetPosition(Vector2 &position)
{
	xPosition = position.first;
	yPosition = position.second;
}

void GameObject::SetName(string name)
{
	objectName = name;
}

void GameObject::SetBitMap(string path)
{
	if (path.length()) {
		wxStandardPaths &stdPaths = wxStandardPaths::Get();
		wxString fileLocation = stdPaths.GetExecutablePath();
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + path);
		wxMessageOutputDebug().Printf("Relative path of image is at %s",fileLocation);
		wxImage image(fileLocation, wxBITMAP_TYPE_JPEG);
		//image.Rescale(50, 50);
		sprite = new wxBitmap(image);
	}
	else {
		sprite = nullptr;
	}
}

wxBitmap * GameObject::GetBitMap()
{
	return sprite;
}

string GameObject::GetName()
{
	return objectName;
}

Vector2 GameObject::GetPosition()
{
	return Vector2(xPosition,yPosition);
}

int GameObject::onCollision(GameObject *collider)
{
	return 0;
}

Vector2 GameObject::move()
{
	//backtrack with the shortest path to kill the mainPlayer
}
