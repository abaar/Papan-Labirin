#include "wx\wx.h"
#include "ImageFrame.h"

class MainApp : public wxApp {
public: 
	virtual bool OnInit();
};

IMPLEMENT_APP(MainApp)
DECLARE_APP(MainApp)

bool MainApp::OnInit() {
	ImageFrame *frame = new ImageFrame("PapanLabirin");
	frame->Show(true);

	return true;
}