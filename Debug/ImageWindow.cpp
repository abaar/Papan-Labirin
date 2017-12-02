#include "ImageWindow.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "MainBoard.h"
#include "ImageWindow.h"
#include "GameObject.h"
#include <wx\arrimpl.cpp>
#include <wx/dcbuffer.h>
#include <string>

#define TIMER_ID 2000
#define ADVANCE_TIMER_ID 2001

BEGIN_EVENT_TABLE(ImageWindow,wxWindow)
EVT_PAINT(ImageWindow::OnPaint)
EVT_KEY_DOWN(ImageWindow::OnKeyDown)
EVT_BUTTON(27,ImageWindow::SetEasy)
EVT_BUTTON(28, ImageWindow::SetMed)
EVT_BUTTON(29, ImageWindow::SetHar)
EVT_BUTTON(30, ImageWindow::RetryGame)//edit this void
EVT_BUTTON(31,ImageWindow::PlayTheGame)
EVT_BUTTON(32,ImageWindow::ShowTheHelp)
EVT_BUTTON(33,ImageWindow::ShowHomePage)
EVT_BUTTON(34,ImageWindow::ShowCredits)
EVT_TIMER(TIMER_ID, ImageWindow::OnTimer)
EVT_TIMER(ADVANCE_TIMER_ID, ImageWindow::OnAdvanceTime)
END_EVENT_TABLE()

ImageWindow::ImageWindow(wxFrame *parent) : wxWindow(parent, 2) {
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	start = 0;
	this->parent = parent;
	image = nullptr;
	int width = parent->GetClientSize().GetWidth();
	int height = parent->GetClientSize().GetHeight();

	ButtonImageLoader();
	ImageLoader(0);
	playgames = new wxButton(this, 31, wxT(""), wxPoint(width / 2 - 75, height / 2), wxSize(50, 25), wxBORDER_NONE);
	playgames->SetBitmap(*playImage);
	helps = new wxButton(this, 32, wxT(""), wxPoint(width / 2 - 104, height / 2+62), wxSize(120, 25), wxBORDER_NONE);
	helps->SetBitmap(*howtoImage);
	credits = new wxButton(this, 34, wxT(""), wxPoint(width / 2 - 97, height / 2 + 62*2), wxSize(100, 25), wxBORDER_NONE);
	credits->SetBitmap(*creditImage);

	buteas = new wxButton(this, 27, wxT(""), wxPoint(width / 2 - 75, height / 2 ), wxSize(50, 25), wxBORDER_NONE);
	buteas->SetBitmap(*easyImage);
	buteas->Show(false);
	butmed = new wxButton(this, 28, wxT(""), wxPoint(width / 2 - 100, height / 2 + 62), wxSize(100, 25), wxBORDER_NONE);
	butmed->SetBitmap(*medImage);
	butmed->Show(false);
	buthar = new wxButton(this, 29, wxT(""), wxPoint(width / 2 - 75, height / 2 + 62 *2), wxSize(50, 25), wxBORDER_NONE);
	buthar->SetBitmap(*hardImage);
	buthar->Show(false);
	back = new wxButton(this, 33, wxT(""), wxPoint(0, height - 25), wxSize(50, 25), wxBORDER_NONE);
	back->SetBitmap(*backImage);
	back->Show(false);
	timer = new wxTimer(this, TIMER_ID);
	advanceTimer = new wxTimer(this, ADVANCE_TIMER_ID);
	timer->Start(100);
	advanceTimer->Start(1000);
}

ImageWindow::~ImageWindow() {
	delete playImage;
	delete howtoImage;
	delete creditImage;
	delete easyImage;
	delete medImage;
	delete hardImage;
	delete backImage;
	if (buteas != nullptr) delete buteas;

	if (playgames != nullptr) delete playgames;

	if (helps != nullptr) delete helps;

	if (credits != nullptr) delete credits;

	if (back != nullptr) delete back;

	if (butmed != nullptr) delete butmed;

	if (buthar != nullptr) delete buthar;

	if (image != nullptr) delete image;

	if (timer != nullptr) { timer->Stop(); delete timer; }

	if (advanceTimer != nullptr) { advanceTimer->Stop(); delete advanceTimer; }

	if (retry != nullptr) delete retry;
}



void ImageWindow::OnPaint(wxPaintEvent &event) {
		wxPaintDC pdc(this);
		if (start == 0) {
			if (image != nullptr) { pdc.DrawBitmap(*image, wxPoint(0, 0)); }
		}
		
		else if (start==1) {
			Vector2 hold;
			if (MainBoard::main->GetLvl() == 3) 
				hold = MainBoard::main->GetStart();
			else hold = Vector2(0, 0);
			//hard error
			int leftOffset = (500 - MainBoard::main->GetViewSize() * 50) / 2;
			int upperOffset = leftOffset + 50;
			if (MainBoard::main != NULL) {
				for (int i = hold.first; i <hold.first+MainBoard::main->GetViewSize(); i++) {
					for (int j = hold.second; j <hold.second+MainBoard::main->GetViewSize(); j++) {
						GameObject* datas = MainBoard::main->GetLocationData(Vector2(j, i));
						if (datas != NULL) {
							pdc.DrawBitmap(*(datas->GetBitMap()), wxPoint((j-hold.second) * TILESIZE + leftOffset, (i-hold.first) * TILESIZE + upperOffset), true);
						}													//substarct with hold so , it show with max 10 tiles
					}
				}
			}
		}
		else if (start == 2) {
			if (image!=nullptr)pdc.DrawBitmap(*image, wxPoint(0, 0));
		}
}

void ImageWindow::OnKeyDown(wxKeyEvent &event) { //here error ganti start pusatnya
	if (start==1) {					//solusi -> pindah sesuai sukses gerakan dan pusat characternya
		Vector2 hold = MainBoard::main->GetStart();
		Vector2 holder = MainBoard::main->GetPlayer()->GetPosition();
		wxMessageOutputDebug().Printf("%d %d | %d %d", hold.first, hold.second, holder.first, holder.second);
				
		if (event.GetKeyCode() == WXK_UP || event.GetKeyCode() == 'W') {
			if (MainBoard::main->GetPlayer()->GetName() == "Player") {
				moved = MainBoard::main->GetPlayer()->Move(Vector2(0, -1));
				//////MainBoard::main->AdvanceStep();
				if (moved) {
					hold.first--;
					if (hold.first == 9 && holder.second - hold.first + 1 <= 6) {
						MainBoard::main->SetStart(hold);
					}
					else if (hold.first != -1 && hold.first != 9) {
						MainBoard::main->SetStart(hold);
					}
				}	//ketika pusat nya mentok di pojok atas
			}
			else {
				MainBoard::main->GetPlayer()->SetBitMap("Player");
				MainBoard::main->GetPlayer()->SetName("Player");
			}
		}
		else if (event.GetKeyCode() == WXK_DOWN) {
			if (MainBoard::main->GetPlayer()->GetName() == "Player1") {
				moved = MainBoard::main->GetPlayer()->Move(Vector2(0, 1));
				//goes down
				if (moved) {
					hold.first++;
					if (hold.first == 1 && holder.second - hold.first - 1 >= 3) MainBoard::main->SetStart(hold);
					else if (hold.first <= 10 && hold.first != 1) {
						MainBoard::main->SetStart(hold);
					}
				}
			}
			else {
				MainBoard::main->GetPlayer()->SetBitMap("Player1");
				MainBoard::main->GetPlayer()->SetName("Player1");
			}
		}
		else if (event.GetKeyCode() == WXK_LEFT) {
			if (MainBoard::main->GetPlayer()->GetName() == "Player3") {
				moved = MainBoard::main->GetPlayer()->Move(Vector2(-1, 0));
				//goes left
				if (moved) {
					hold.second--;
					if (hold.second == 9 && holder.first - hold.second + 1 <= 6) {
						MainBoard::main->SetStart(hold);
					}
					else if (hold.second != -1 && hold.second != 9) { MainBoard::main->SetStart(hold); }


				}//ketika pusatnya mentok di pojok kiri
			}
			else {
				MainBoard::main->GetPlayer()->SetBitMap("Player3");
				MainBoard::main->GetPlayer()->SetName("Player3");
			}
		}
		else if (event.GetKeyCode() == WXK_RIGHT) {
			if (MainBoard::main->GetPlayer()->GetName() == "Player2") {
				moved = MainBoard::main->GetPlayer()->Move(Vector2(1, 0));
				//goes right
				if (moved) {
					hold.second++;
					if (hold.second == 1 && holder.first - hold.second - 1 >= 3) MainBoard::main->SetStart(hold);
					else if (hold.second <= 10 && hold.second != 1) { MainBoard::main->SetStart(hold); }
				}//end of set start
			}
			else {
				MainBoard::main->GetPlayer()->SetBitMap("Player2");
				MainBoard::main->GetPlayer()->SetName("Player2");
			}
		}
	}
	Refresh();
	//wxMessageOutputDebug().Printf("Pushed %d",event.GetKeyCode());
}

void ImageWindow::OnTimer(wxTimerEvent &event){
	if (start == 1) {
		timeCounter += 100;
		if (timeCounter >= 1000) {
			timeCounter %= 1000;
			MainBoard::main->IncrementTime();
			//wxMessageOutputDebug().Printf("Elapsed Time %d",MainBoard::main->GetElapsedTime());
		}
		//MainBoard::main->SwapGameObject(Vector2(2, 0), Vector2(2, 1));
		Refresh();
	}
}

void ImageWindow::OnAdvanceTime(wxTimerEvent & event)
{
	if (start == 1) {
		MainBoard::main->AdvanceStep();
	}
}

void ImageWindow::PlayTheGame(wxCommandEvent & event)
{
	playgames->Show(false);
	helps->Show(false);
	credits->Show(false);
	buteas->Show(true);
	butmed->Show(true);
	buthar->Show(true);
	back->Show(true);
}

void ImageWindow::ShowTheHelp(wxCommandEvent & event)
{
	playgames->Show(false);
	helps->Show(false);
	credits->Show(false);
	back->Show(true);
}

void ImageWindow::ShowHomePage(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	playgames->Show(true);
	helps->Show(true);
	credits->Show(true);
	ImageLoader(0);
}


void ImageWindow::ShowCredits(wxCommandEvent & event)
{
	playgames->Show(false);
	helps->Show(false);
	credits->Show(false);
	back->Show(true);
}


void ImageWindow::SetEasy(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	//timer = new wxTimer(this, TIMER_ID);
	//advanceTimer = new wxTimer(this, ADVANCE_TIMER_ID);
	//timer->Start(100);
	//advanceTimer->Start(1000);
	timeCounter = 0;
	MainBoard::main->LoadMap("map0");
	MainBoard::main->SetLvl(1);
	start = 1;
	Refresh();
}

void ImageWindow::SetMed(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	//timer = new wxTimer(this, TIMER_ID);
	//advanceTimer = new wxTimer(this, ADVANCE_TIMER_ID);
	//timer->Start(100);
	//advanceTimer->Start(1000);
	timeCounter = 0;
	MainBoard::main->LoadMap("map3");
	MainBoard::main->SetLvl(2);
	start = 1;
	Refresh();
}

void ImageWindow::SetHar(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	//timer = new wxTimer(this, TIMER_ID);
	//advanceTimer = new wxTimer(this, ADVANCE_TIMER_ID);
	//timer->Start(100);
	//advanceTimer->Start(1000);
	timeCounter = 0;
	MainBoard::main->LoadMap("map10");
	MainBoard::main->SetLvl(3);
	start = 1;
	Refresh();
} //delete objeknya belum, jadi ketindes2

void ImageWindow::RetryGame(wxCommandEvent & event)
{

}

void ImageWindow::ShutDown(int changetomap, int winloose)
{
	/*Object should deleted here,but somehow it thrown exception*/
	//Somehow, this is wrong approach, and break most rule in KISS, chaos bar kodinganmu --
	if (winloose == 0) {
		start = 2;
		//timer->Stop(); //Bad Approach, timer should never be stopped, used by automatic gameObject rendering!
		//advanceTimer->Stop();
		timeCounter = 0;
		//delete timer; //wtf??
		//delete advanceTimer; //wtf??
		//timer = nullptr;
		//advanceTimer = nullptr;
		ImageLoader(winloose);
		Refresh();
	}
	else if (changetomap<20) {
		//timer->Stop();
		//advanceTimer->Stop();
		timeCounter = 0;
		//delete timer;
		//delete advanceTimer;
		//timer = nullptr;
		//advanceTimer = nullptr;
		string changetomap_str = to_string(changetomap);
		//MainBoard::main->ClearObject(); //Bad implementation of singleton design pattern
		MainBoard::main->LoadMap("map" + changetomap_str);
	}
	else if (changetomap == 20) {
		//load win
	}
}

void ImageWindow::ButtonImageLoader()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\play.jpg");
	wxImage images(fileLocation, wxBITMAP_TYPE_JPEG);
	this->playImage = new wxBitmap(images);
	
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\credits.jpg");
	wxImage images1(fileLocation, wxBITMAP_TYPE_JPEG);
	this->creditImage = new wxBitmap(images1);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\howto.jpg");
	wxImage images2(fileLocation, wxBITMAP_TYPE_JPEG);
	this->howtoImage = new wxBitmap(images2);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\back.jpg");
	wxImage images3(fileLocation, wxBITMAP_TYPE_JPEG);
	this->backImage = new wxBitmap(images3);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\easy.jpg");
	wxImage images4(fileLocation, wxBITMAP_TYPE_JPEG);
	this->easyImage = new wxBitmap(images4);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\medium.jpg");
	wxImage images5(fileLocation, wxBITMAP_TYPE_JPEG);
	this->medImage = new wxBitmap(images5);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\hard.jpg");
	wxImage images6(fileLocation, wxBITMAP_TYPE_JPEG);
	this->hardImage = new wxBitmap(images6);
}

void ImageWindow::ImageLoader(int winloose)
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\background.jpg");
	if (start == 0) {
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\1.jpg");
	}
	else if (start == 2) {
		if (winloose) {
			fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\Win.jpg");
		}
		else
		{
			fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\Loose.jpg");
		}
	}
	wxMessageOutputDebug().Printf("Relative path of image is at %s", fileLocation);
	wxImage images(fileLocation, wxBITMAP_TYPE_JPEG);
	this->image = new wxBitmap(images);
}

