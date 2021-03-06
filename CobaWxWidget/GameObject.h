#pragma once
#include "Definer.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx\wx.h"
//#include "MainBoard.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
	static int count;
	void SetPosition(int x, int y);
	void SetPosition(Vector2 &position);
	void SetName(string name);
	void SetBitMap(string path);
	virtual void Destroy();
	wxBitmap* GetBitMap();
	string GetName();
	Vector2 GetPosition();
private:
	string objectName;
	int xPosition;
	int yPosition;
	wxBitmap *sprite = nullptr;
};

