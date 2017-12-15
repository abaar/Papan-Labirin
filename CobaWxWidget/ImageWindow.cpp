#include "ImageWindow.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include <wx/mediactrl.h>
#include "MainBoard.h"
#include "ImageWindow.h"
#include "GameObject.h"
#include <wx\arrimpl.cpp>
#include <wx/dcbuffer.h>
#include <string>
#include "wx/sound.h"
#include <Windows.h>
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
	
	SetInitialSize(wxSize(518, 541));
	wxMessageOutputDebug().Printf("%d %d", GetClientSize().GetWidth(), GetClientSize().GetHeight());
	this->SetBackgroundColour(wxColour(*wxWHITE));
	jpegLoader = new wxJPEGHandler();
	pngLoader = new wxPNGHandler();
	wxImage::AddHandler(jpegLoader);
	wxImage::AddHandler(pngLoader);
	start = 0;
	score = 0;
	this->parent = parent;
	image = nullptr;
	for (int i = 0; i < 5; ++i) scorevalue[i] = nullptr;
	int width = parent->GetClientSize().GetWidth();
	int height = parent->GetClientSize().GetHeight();

	//wxSound *player = new wxSound("testMusic.wav");
	//player->Play(wxSOUND_LOOP | wxSOUND_ASYNC);
	//PlaySound(TEXT("testMusic.wav"), NULL, SND_LOOP | SND_ASYNC);
	
	ButtonImageLoader();
	playgames = new wxButton(this, 31, wxT(""), wxPoint(171, 210), wxSize(166, 63), wxBORDER_NONE);
	playgames->SetBitmap(*playImage);
	helps = new wxButton(this, 32, wxT(""), wxPoint(171, 291), wxSize(170, 68), wxBORDER_NONE);
	helps->SetBitmap(*howtoImage);
	credits = new wxButton(this, 34, wxT(""), wxPoint(171, 376), wxSize(170, 68), wxBORDER_NONE);
	credits->SetBitmap(*creditImage);

	buteas = new wxButton(this, 27, wxT(""), wxPoint(175, 209 ), wxSize(167, 66), wxBORDER_NONE);
	buteas->SetBitmap(*easyImage);
	buteas->Show(false);
	butmed = new wxButton(this, 28, wxT(""), wxPoint(175, 291), wxSize(167, 68), wxBORDER_NONE);
	butmed->SetBitmap(*medImage);
	butmed->Show(false);
	buthar = new wxButton(this, 29, wxT(""), wxPoint(175, 376), wxSize(167, 68), wxBORDER_NONE);
	buthar->SetBitmap(*hardImage);
	buthar->Show(false);


	back = new wxButton(this, 33, wxT(""), wxPoint(0, height - 25), wxSize(50, 25), wxBORDER_NONE);
	back->SetBitmap(*backImage);
	back->Show(false);
	retry = new wxButton(this, 30, wxT(""), wxPoint(width - 50, height - 25), wxSize(50, 25), wxBORDER_NONE);
	retry->SetBitmap(*retryImage);
	retry->Show(false);

	timer = new wxTimer(this, TIMER_ID);
	advanceTimer = new wxTimer(this, ADVANCE_TIMER_ID);
	timer->Start(100);
	advanceTimer->Start(1000);
	SetBackgroundColour(*wxBLACK);
	ImageLoader(0);
}

ImageWindow::~ImageWindow() {
	delete back;
	delete backImage;
	delete backLooseImage;
	delete backWinImage;

	delete playgames;
	delete playImage;

	delete helps;
	delete howtoImage;

	delete credits;
	delete creditImage;

	delete buteas;
	delete easyImage;

	delete butmed;
	delete medImage;

	delete buthar;
	delete hardImage; 

	delete image;

	delete retry;
	delete retryImage;


	for (int i = 0; i < 5; ++i) if (scorevalue[i]!=nullptr) delete scorevalue[i];

	if (timer != nullptr) { timer->Stop(); delete timer; }

	if (advanceTimer != nullptr) { advanceTimer->Stop(); delete advanceTimer; }

}



void ImageWindow::OnPaint(wxPaintEvent &event) {
		wxPaintDC pdc(this);
		if (start==1) {
			Vector2 hold;
			if (MainBoard::main->GetLvl() == 3) 
				hold = MainBoard::main->GetStart();
			else hold = Vector2(0, 0);
			//hard error
			int leftOffset = 1+ (500 - MainBoard::main->GetViewSize() * 50) / 2;
			int upperOffset = leftOffset;
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
			if (image != nullptr)pdc.DrawBitmap(*image, wxPoint(0, 0));
			int offset = 25;
			for (int i = 0; i < 5; ++i) {
				if (scorevalue[i]!=nullptr)pdc.DrawBitmap(*scorevalue[i], wxPoint(i*offset, 0));
			}

		}
		else
		{
			if (image!=nullptr)pdc.DrawBitmap(*image, wxPoint(0, 0));
		}
}

void ImageWindow::OnKeyDown(wxKeyEvent &event) { //here error ganti start pusatnya
	if (start==1) {		//solusi -> pindah sesuai sukses gerakan dan pusat characternya
		Vector2 hold = MainBoard::main->GetStart();
		Vector2 holder = MainBoard::main->GetPlayer()->GetPosition();
		wxMessageOutputDebug().Printf("%d %d | %d %d", hold.first, hold.second, holder.first, holder.second);
		++keystroke;
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
	back->Show(true);
	helps->Show(false);
	playgames->Show(false);
	credits->Show(false);
	start = 3;
	delete image;
	ImageLoader(0);
	Refresh();
}

void ImageWindow::ShowHomePage(wxCommandEvent & event)
{
	start = 0;
	delete image;
	ImageLoader(0);
	Refresh();
	retry->Show(false);
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	back->SetBitmap(*backImage);
	playgames->Show(true);
	helps->Show(true);
	credits->Show(true);
}


void ImageWindow::ShowCredits(wxCommandEvent & event)
{
	back->Show(true);
	helps->Show(false);
	playgames->Show(false);
	credits->Show(false);
	start = 4;
	delete image;
	ImageLoader(0);
	Refresh();
}


void ImageWindow::SetEasy(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);

	timeCounter = 0;
	MainBoard::main->LoadMap("map0");
	MainBoard::main->SetLvl(1);
	start = 1;
	delete image;
	Refresh();
}

void ImageWindow::SetMed(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);

	timeCounter = 0;
	MainBoard::main->LoadMap("map3");
	MainBoard::main->SetLvl(2);
	start = 1;
	delete image;
	Refresh();
}

void ImageWindow::SetHar(wxCommandEvent & event)
{
	buteas->Show(false);
	butmed->Show(false);
	buthar->Show(false);
	back->Show(false);
	timeCounter = 0;
	MainBoard::main->LoadMap("map10");
	MainBoard::main->SetLvl(3);
	start = 1;
	delete image;
	Refresh();
} //delete objeknya belum, jadi ketindes2

void ImageWindow::RetryGame(wxCommandEvent & event)
{
	start = 1;
	delete image;
	retry->Show(false);
	back->Show(false);
	int temp = MainBoard::main->GetCurrentMap();
	MainBoard::main->SetCurrentMap(temp - 2);// -2 karena get nya ++1 dipanggil 2x
	string changetomap_str = to_string(temp - 2);
	MainBoard::main->LoadMap("map" + changetomap_str);

}

void ImageWindow::ShutDown(int changetomap, int winloose)
{
	if (winloose == 0) {
		start = 2;
		timeCounter = 0;
		ImageLoader(winloose);
		retry->Show(true);
		back->SetBitmap(*backLooseImage);
		back->Show(true);
		ScoreLoader(score);
		score = 0;
		Refresh();
	}
	else if (changetomap<14) {
		int lvl = MainBoard::main->GetLvl();
		double score1;
		if (lvl == 1) {
			score1 = (double)((double)(20.0 / keystroke) * 1000.0);
		}
		else if (lvl == 2) {
			score1 = (double)((double)(30.0 / keystroke) * 2000.0);
		}
		else if (lvl == 3) {
			score1 = (double)((double)(60.0 / keystroke) * 3000.0);
		}keystroke = 0;

		this->score +=round(score1);
		timeCounter = 0;
		string changetomap_str = to_string(changetomap);
		MainBoard::main->LoadMap("map" + changetomap_str);
	}
	else if (changetomap == 14) {
		double score1;
		int lvl = MainBoard::main->GetLvl();
		if (lvl == 1) {
			score1 =(double) ((double)(20 / keystroke) * 1000.0);
		}
		else if (lvl == 2) {
			score1 = (double)((double)(30 / keystroke) * 2000.0);
		}
		else if (lvl == 3) {
			score1 = (double)((double)(60 / keystroke) * 3000.0);
		}
		this->score += round(score1);
		ImageLoader(winloose); 
		back->SetBitmap(*backWinImage);
		back->Show(true);
		ScoreLoader(score);
		score = 0;
		Refresh();
	}
}

void ImageWindow::ButtonImageLoader()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\play.jpg");
	wxImage image1(fileLocation, wxBITMAP_TYPE_JPEG);
	this->playImage = new wxBitmap(image1);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\howto.jpg");
	wxImage image2(fileLocation, wxBITMAP_TYPE_JPEG);
	this->howtoImage = new wxBitmap(image2);
	

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\credits.jpg");
	wxImage image3(fileLocation, wxBITMAP_TYPE_JPEG);
	this->creditImage = new wxBitmap(image3);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\easy.jpg");
	wxImage image4(fileLocation, wxBITMAP_TYPE_JPEG);
	this->easyImage = new wxBitmap(image4);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\medium.jpg");
	wxImage image5(fileLocation, wxBITMAP_TYPE_JPEG);
	this->medImage = new wxBitmap(image5);
	
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\hard.jpg");
	wxImage image6(fileLocation, wxBITMAP_TYPE_JPEG);
	this->hardImage = new wxBitmap(image6);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\back.jpg");
	wxImage images3(fileLocation, wxBITMAP_TYPE_JPEG);
	this->backImage = new wxBitmap(images3);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\back_loose.jpg");
	wxImage images7(fileLocation, wxBITMAP_TYPE_JPEG);
	this->backLooseImage = new wxBitmap(images7);

	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\back_win.jpg");
	wxImage images8(fileLocation, wxBITMAP_TYPE_JPEG);
	this->backWinImage = new wxBitmap(images8);


	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\retry.jpg");
	wxImage images9(fileLocation, wxBITMAP_TYPE_JPEG);
	this->retryImage = new wxBitmap(images9);
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
	else if (start == 3) {
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\PageHowTo.jpg");
	}
	else if (start == 4) {
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\PageCredits.jpg");
	}
	wxMessageOutputDebug().Printf("Relative path of image is at %s", fileLocation);
	wxImage images(fileLocation, wxBITMAP_TYPE_JPEG);
	this->image = new wxBitmap(images);
}

void ImageWindow::ScoreLoader(int score)
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	int puluhribuan;
	int ribuan;
	int ratusan;
	int puluhan;
	int satuan;
	wxMessageOutputDebug().Printf("%d", score);
	satuan = score % 10;
	score /= 10;
	puluhan = score % 10;
	score /= 10;
	ratusan = score % 10;
	score /= 10;
	ribuan = score % 10;
	score /= 10;
	puluhribuan = score % 10;
	score /= 10;



	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + to_string(satuan) + ".png");
	wxImage image1(fileLocation, wxBITMAP_TYPE_PNG);
	this->scorevalue[4] = new wxBitmap(image1);


	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + to_string(puluhan) + ".png");
	wxImage image2(fileLocation, wxBITMAP_TYPE_PNG);
	this->scorevalue[3] = new wxBitmap(image2);


	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + to_string(ratusan) + ".png");
	wxImage image3(fileLocation, wxBITMAP_TYPE_PNG);
	this->scorevalue[2] = new wxBitmap(image3);


	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + to_string(ribuan) + ".png");
	wxImage image4(fileLocation, wxBITMAP_TYPE_PNG);
	this->scorevalue[1] = new wxBitmap(image4);


	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\" + to_string(puluhribuan) + ".png");
	wxImage image5(fileLocation, wxBITMAP_TYPE_PNG);
	this->scorevalue[0] = new wxBitmap(image5);

}

