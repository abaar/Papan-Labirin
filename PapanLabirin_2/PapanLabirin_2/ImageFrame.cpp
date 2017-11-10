#include "ImageFrame.h"
#include "ImageWindow.h"

ImageFrame::ImageFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title) {
	this->window = new ImageWindow(this);
	this->SetInitialSize(wxSize(500, 500));
}