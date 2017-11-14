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
	Vector2 current_position = MainBoard::main->getPlayerCat();
	GameObject *current_object;
	if (event.GetKeyCode() == WXK_UP) {
		if (current_position.first - 1 > -1) {
			current_position.first--;
			current_object = MainBoard::main->GetLocationData(current_position);
			if (current_object->GetName() != "Wall") {
				
				MainBoard::main->SwapGameObject(current_position, MainBoard::main->getPlayerCat()); 
					//swap first the playerCat with current_position which has been edited					
				MainBoard::main->setPlayerCat(current_position); //then update the playerCat or playerCoordinat
			}
		}
		wxMessageOutputDebug().Printf("Key Up pressed");
	}
	else if (event.GetKeyCode() == WXK_DOWN) {
		if (current_position.first + 1 > MainBoard::main->GetBoardSize()) {
			current_position.first++;
			current_object = MainBoard::main->GetLocationData(current_position);
			if (current_object->GetName() != "Wall") {

				MainBoard::main->SwapGameObject(current_position, MainBoard::main->getPlayerCat());
				//swap first the playerCat with current_position which has been edited					
				MainBoard::main->setPlayerCat(current_position); //then update the playerCat or playerCoordinat
			}
		}
		wxMessageOutputDebug().Printf("Key Down pressed");
	}
	else if (event.GetKeyCode() == WXK_LEFT) {
		if (current_position.second - 1 > -1) {
			current_position.second--;
			current_object = MainBoard::main->GetLocationData(current_position);
			if (current_object->GetName() != "Wall") {

				MainBoard::main->SwapGameObject(current_position, MainBoard::main->getPlayerCat());
				//swap first the playerCat with current_position which has been edited					
				MainBoard::main->setPlayerCat(current_position); //then update the playerCat or playerCoordinat
			}
		}
		wxMessageOutputDebug().Printf("Key Left pressed");
	}
	else if (event.GetKeyCode() == WXK_RIGHT) {
		if (current_position.second +1 > MainBoard::main->GetBoardSize()) {
			current_position.second++;
			current_object = MainBoard::main->GetLocationData(current_position);
			if (current_object->GetName() != "Wall") {

				MainBoard::main->SwapGameObject(current_position, MainBoard::main->getPlayerCat());
				//swap first the playerCat with current_position which has been edited					
				MainBoard::main->setPlayerCat(current_position); //then update the playerCat or playerCoordinat
			}
		}
		wxMessageOutputDebug().Printf("Key Right pressed");
	}
}