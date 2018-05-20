//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
int mstimer = 600000; //10 минут (в миллисекундах) - на столько заводить таймер, столько окно может бездействовать
extern AnsiString whois;  //переменная из Unit2, в которой хранится имя идентифицированного пользователя
int guess = -1; //верно или неверно определен пользователь -1 - ещё не выбрано
extern int all; //переменная из Unit2
extern int yy;  //переменная из Unit2
extern int yn1; //переменная из Unit2
extern int yn2; //переменная из Unit2
extern int ny;  //переменная из Unit2
extern int nn;  //переменная из Unit2

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
    Timer1->Interval = mstimer;
	if (whois == "") {
		Label1->Caption = "Такого пользователя не существует!";
		Button1->Visible = false;
		Button2->Visible = false;
		Button4->Visible = false;
	}
	else {
		Label1->Caption = "Здравствуйте, " + whois + "!";
		Button5->Visible = false;
		Button6->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClick(TObject *Sender)   //если на форме что-то происходит (по форме кликают мышкой), то таймер сбрасывается
{
	  Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	  Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	  Timer1->Enabled = true;    //запускаем таймер заново
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
	  guess = -1;
	  Close();  //если время таймера вышло (закончилось время простоя) то окно закрывается
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	  Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	  Timer1->Enabled = true;    //запускаем таймер заново
	  guess = 1; //пользователь определен верно
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
	 Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	 Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	 Timer1->Enabled = true;    //запускаем таймер заново
	 guess = 3; //пользователь определен неверно
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button3Click(TObject *Sender)
{
	if (guess == -1) {  //не нажата клавиша выбора верно или неверно программа определила пользователя
		 Application->MessageBox(L"Выясните, верно или неверно определен пользователь, и нажмите соответствующую клавишу", L"Ошибка", MB_OK | MB_ICONERROR);
		 Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
		 Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
		 Timer1->Enabled = true;    //запускаем таймер заново
	}
	else {
		switch (guess) {
		case 1:
			yy++;
			break;
		case 2:
			yn2++;
			break;
		case 3:
			nn++;
			break;
		case 4:
			ny++;
			break;
		case 5:
			yn1++;
			break;
		}
		all++;  //увеличиваем количество вводов
		guess = -1;
		Close();   //закрываем окно после окончательного выбора
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button5Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	  Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	  Timer1->Enabled = true;    //запускаем таймер заново
	  guess = 4; //пользователь определен верно
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	  Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	  Timer1->Enabled = true;    //запускаем таймер заново
	  guess = 2; //пользователь определен верно
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button6Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //сброс таймера, чтобы отсчет начался заново
	  Timer1->Interval = mstimer;   //устанавливаем время бездействия окна
	  Timer1->Enabled = true;    //запускаем таймер заново
	  guess = 5; //пользователь определен верно
}
//---------------------------------------------------------------------------

