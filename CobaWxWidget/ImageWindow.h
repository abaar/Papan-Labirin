#pragma once
#include "wx\wx.h"
#include "vector"

using namespace std;


class ImageWindow : public wxWindow {

public: 
	ImageWindow(wxFrame *parent);
	~ImageWindow();
	void OnPaint(wxPaintEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnAdvanceTime(wxTimerEvent &event);
	void PlayTheGame(wxCommandEvent &event);
	void ShowTheHelp(wxCommandEvent &event);
	void ShowHomePage(wxCommandEvent &event);
	void ShowCredits(wxCommandEvent &event);
	void SetEasy(wxCommandEvent &event);
	void SetMed(wxCommandEvent &event);
	void SetHar(wxCommandEvent &event);
	void RetryGame(wxCommandEvent &event);
	void ShutDown(int changetomap, int winloose);
	void ButtonImageLoader();
	void ImageLoader(int winloose);
	void ScoreLoader(int score);
private:
	wxFrame *parent;
	int start; //start = 0 (Starting Window) ; start=1 (in-game) ; start=2 (result)
	wxBitmap *image; //
	wxBitmap *playImage; //
	wxBitmap *creditImage; //
	wxBitmap *howtoImage; //
	wxBitmap *backImage; // 
	wxBitmap *backLooseImage; //
	wxBitmap *backWinImage; //
	wxBitmap *easyImage; //
	wxBitmap *medImage; //
	wxBitmap *hardImage; //
	wxBitmap *retryImage; //
	wxBitmap *scorevalue[5]; //
	wxButton *buteas; //
	wxButton *butmed; //
	wxButton *buthar; //
	wxButton *back; //
	wxButton *retry; //
	wxButton *playgames; //
	wxButton *helps; //
	wxButton *credits; //
	wxTimer *timer;//
	wxTimer *advanceTimer;//
	wxImageHandler *jpegLoader;
	wxImageHandler *pngLoader;
	DECLARE_EVENT_TABLE()
	int timeCounter;
	int keystroke;
	int score;
	int moved;
};