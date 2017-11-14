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

void ImageWindow::OnKeyDown(wxKeyEvent &event) { //edit every mainPlayer's position as a key is pressed
	if (event.GetKeyCode() == WXK_UP) {
		Vector2 handler = MainBoard::main->mainPlayer->GetPosition(); //return current mainplayer position
		handler.first--; //x=x-1 or goes up  /*edit its position
		MainBoard::main->mainPlayer->SetPosition(handler);
		wxMessageOutputDebug().Printf("Key Up pressed");
	}
	else if (event.GetKeyCode() == WXK_DOWN) {
		Vector2 handler = MainBoard::main->mainPlayer->GetPosition();
		handler.first++; //x=x+1 or goes down
		MainBoard::main->mainPlayer->SetPosition(handler);
		wxMessageOutputDebug().Printf("Key Down pressed");
	}
	else if (event.GetKeyCode() == WXK_LEFT) {
		Vector2 handler = MainBoard::main->mainPlayer->GetPosition();
		handler.second--; //x=x-1 or goes left
		MainBoard::main->mainPlayer->SetPosition(handler);
		wxMessageOutputDebug().Printf("Key Left pressed");
	}
	else if (event.GetKeyCode() == WXK_RIGHT) {
		Vector2 handler = MainBoard::main->mainPlayer->GetPosition();
		handler.first++; //x=x-1 or goes right
		MainBoard::main->mainPlayer->SetPosition(handler);
		wxMessageOutputDebug().Printf("Key Right pressed");
	}
}