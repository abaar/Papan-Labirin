#include "wx\wx.h"
#include "ImageFrame.h"
#include "MainBoard.h"

class MainApp : public wxApp {
private:
	ImageFrame *frame;
public: 
	virtual bool OnInit();
	~MainApp();
};

IMPLEMENT_APP(MainApp)
DECLARE_APP(MainApp)

bool MainApp::OnInit() {
	
	MainBoard *currentBoard = new MainBoard();
	MainBoard::main = currentBoard;
	frame = new ImageFrame("PapanLabirin");
	frame->Show(true);
	
	return true;
}

MainApp::~MainApp()
{
	delete MainBoard::main;
	//delete frame;
}
