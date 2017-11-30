#pragma once
#include "wx\wx.h"

class ImageWindow;


class ImageFrame : public wxFrame {
private :
	ImageWindow *gamewindow;	
public:
	ImageFrame(const wxString &title);
};