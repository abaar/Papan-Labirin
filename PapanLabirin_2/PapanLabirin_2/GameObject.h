#pragma once
#include "Definer.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx\wx.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPosition(int x, int y);
	void SetPosition(Vector2 &position);
	void SetName(string name);
	void SetBitMap(string path);
	wxBitmap* GetBitMap();
	string GetName();
	Vector2 GetPosition();
	virtual int onCollision(GameObject *collider);
	virtual void move();
private:
	string objectName;
	int xPosition;
	int yPosition;
	wxBitmap *sprite = nullptr;
};

