#include "ImageFrame.h"
#include "ImageWindow.h"
#include "MainBoard.h"




ImageFrame::ImageFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title) {
	this->SetInitialSize(wxSize(518, 541));
	this->SetMaxSize(wxSize(518, 541));
	gamewindow = new ImageWindow(this);
	gamewindow->Show(true);
}