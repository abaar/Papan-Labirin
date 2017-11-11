#include "ImageWindow.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "MainBoard.h"

BEGIN_EVENT_TABLE(ImageWindow,wxWindow)
EVT_PAINT(ImageWindow::OnPaint)
EVT_KEY_DOWN(ImageWindow::OnKeyDown)
END_EVENT_TABLE()

ImageWindow::ImageWindow(wxFrame *parent) : wxWindow(parent, wxID_ANY) {
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
}

ImageWindow::~ImageWindow() {
}




void ImageWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	if (MainBoard::main != NULL) {
		for (int i = 0;i < MainBoard::main->GetBoardSize();i++) {
			for (int j = 0;j < MainBoard::main->GetBoardSize();j++) {
				GameObject* datas = MainBoard::main->GetLocationData(Vector2(i, j));
				if (datas != NULL) {
					pdc.DrawBitmap(*(datas->GetBitMap()), wxPoint(i * 50, j * 50), true);
				}
			}
		}
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