#include "GameObject.h"

GameObject::GameObject()
{
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	sprite = nullptr;
}


GameObject::~GameObject()
{
	
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
		if (sprite != NULL) {
			delete sprite;
			sprite = NULL;
		}
		wxStandardPaths &stdPaths = wxStandardPaths::Get();
		wxString fileLocation = stdPaths.GetExecutablePath();
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + path + ".jpg");
		wxMessageOutputDebug().Printf("Relative path of image is at %s",fileLocation);
		wxImage image(fileLocation, wxBITMAP_TYPE_JPEG);
		image.Rescale(TILESIZE, TILESIZE);
		if (sprite != NULL) delete sprite;
		sprite = new wxBitmap(image);
	}
	else {
		if (sprite != NULL) {
			delete sprite;
		}
		sprite = nullptr;
	}
}

void GameObject::Destroy()
{
	delete this;
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


