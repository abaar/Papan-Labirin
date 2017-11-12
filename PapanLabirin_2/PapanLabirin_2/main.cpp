#include "wx\wx.h"
#include "ImageFrame.h"
#include "MainBoard.h"

class MainApp : public wxApp {
public: 
	virtual bool OnInit();
};

IMPLEMENT_APP(MainApp)
DECLARE_APP(MainApp)

bool MainApp::OnInit() {
	
	ImageFrame *frame = new ImageFrame("PapanLabirin");
	frame->Show(true);
	MainBoard *currentBoard = new MainBoard();
	MainBoard::main = currentBoard;
	//while (1) {
		currentBoard->SwapGameObject(Vector2(2, 0), Vector2(2, 1));
		//Sleep(5000);
	//}

	return true;
}