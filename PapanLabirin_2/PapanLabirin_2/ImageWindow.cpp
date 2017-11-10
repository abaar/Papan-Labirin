#include "ImageWindow.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"

BEGIN_EVENT_TABLE(ImageWindow,wxWindow)
EVT_PAINT(ImageWindow::OnPaint)
EVT_KEY_DOWN(ImageWindow::OnKeyDown)
END_EVENT_TABLE()

ImageWindow::ImageWindow(wxFrame *parent) : wxWindow(parent, wxID_ANY) {
	this->SetBackgroundColour(wxColour(*wxWHITE));
	//load jpeg handler
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);

	this->LoadPotatoBitMap();
}

ImageWindow::~ImageWindow() {
	delete potatoBitMap;
	delete potatoBitMap2;
}

void ImageWindow::LoadPotatoBitMap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\Dazai.jpg");
	wxMessageOutputDebug().Printf("Relative path of image is at %s", fileLocation);
	wxImage image(fileLocation, wxBITMAP_TYPE_JPEG);
	fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\Dazai.jpg");
	wxMessageOutputDebug().Printf("Relative path of image is at %s", fileLocation);
	wxImage image2(fileLocation, wxBITMAP_TYPE_JPEG);
	image.Rescale(50, 50);
	potatoBitMap2 = new wxBitmap(image2);
}


void ImageWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	if (potatoBitMap != nullptr) {
		pdc.DrawBitmap(*potatoBitMap, wxPoint(10,10), true);
	}
	if (potatoBitMap2 != nullptr) {
		pdc.DrawBitmap(*potatoBitMap2, wxPoint(200, 200), true);
	}
}

void ImageWindow::OnKeyDown(wxKeyEvent &event) {
	if (event.GetKeyCode() == WXK_UP) {
		//goes up
	}
	else if (event.GetKeyCode() == WXK_DOWN) {
		//goes down
	}
	else if (event.GetKeyCode() == WXK_LEFT) {
		//goes left
	}
	else if (event.GetKeyCode() == WXK_RIGHT) {
		//goes right
	}
}