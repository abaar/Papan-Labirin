#pragma once
#include "wx\wx.h"
#include "vector"
using namespace std;

class ImageWindow : public wxWindow {

public: 
	ImageWindow(wxFrame *parent);
	~ImageWindow();
	void OnPaint(wxPaintEvent &event);
	void OnKeyDown(wxKeyEvent &event);

private:
	vector <wxBitmap*> wallData;
	wxBitmap *potatoBitMap= nullptr;
	wxBitmap *potatoBitMap2 = nullptr;
	DECLARE_EVENT_TABLE();
	void LoadPotatoBitMap();
};