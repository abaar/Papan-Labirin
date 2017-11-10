#pragma once
#include "wx\wx.h"

class ImageWindow : public wxWindow {

public: 
	ImageWindow(wxFrame *parent);
	~ImageWindow();
	void OnPaint(wxPaintEvent &event);

private:
	wxBitmap *potatoBitMap = nullptr;
	wxBitmap *potatoBitMap2 = nullptr;
	DECLARE_EVENT_TABLE();
	void LoadPotatoBitMap();
};