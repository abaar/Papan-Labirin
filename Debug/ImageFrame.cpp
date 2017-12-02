#include "ImageFrame.h"
#include "ImageWindow.h"
#include "MainBoard.h"



ImageFrame::ImageFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title) {
	this->SetInitialSize(wxSize(520, 600));
	this->SetMaxSize(wxSize(520, 600));
	gamewindow = new ImageWindow(this);
	gamewindow->Show(true);

	MainBoard::main->SetImageWindow(gamewindow);
}