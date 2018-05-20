//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
int mstimer = 600000; //10 ����� (� �������������) - �� ������� �������� ������, ������� ���� ����� ��������������
extern AnsiString whois;  //���������� �� Unit2, � ������� �������� ��� ������������������� ������������
int guess = -1; //����� ��� ������� ��������� ������������ -1 - ��� �� �������
extern int all; //���������� �� Unit2
extern int yy;  //���������� �� Unit2
extern int yn1; //���������� �� Unit2
extern int yn2; //���������� �� Unit2
extern int ny;  //���������� �� Unit2
extern int nn;  //���������� �� Unit2

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
    Timer1->Interval = mstimer;
	if (whois == "") {
		Label1->Caption = "������ ������������ �� ����������!";
		Button1->Visible = false;
		Button2->Visible = false;
		Button4->Visible = false;
	}
	else {
		Label1->Caption = "������������, " + whois + "!";
		Button5->Visible = false;
		Button6->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClick(TObject *Sender)   //���� �� ����� ���-�� ���������� (�� ����� ������� ������), �� ������ ������������
{
	  Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	  Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	  Timer1->Enabled = true;    //��������� ������ ������
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
	  guess = -1;
	  Close();  //���� ����� ������� ����� (����������� ����� �������) �� ���� �����������
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	  Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	  Timer1->Enabled = true;    //��������� ������ ������
	  guess = 1; //������������ ��������� �����
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
	 Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	 Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	 Timer1->Enabled = true;    //��������� ������ ������
	 guess = 3; //������������ ��������� �������
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button3Click(TObject *Sender)
{
	if (guess == -1) {  //�� ������ ������� ������ ����� ��� ������� ��������� ���������� ������������
		 Application->MessageBox(L"��������, ����� ��� ������� ��������� ������������, � ������� ��������������� �������", L"������", MB_OK | MB_ICONERROR);
		 Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
		 Timer1->Interval = mstimer;   //������������� ����� ����������� ����
		 Timer1->Enabled = true;    //��������� ������ ������
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
		all++;  //����������� ���������� ������
		guess = -1;
		Close();   //��������� ���� ����� �������������� ������
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button5Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	  Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	  Timer1->Enabled = true;    //��������� ������ ������
	  guess = 4; //������������ ��������� �����
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	  Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	  Timer1->Enabled = true;    //��������� ������ ������
	  guess = 2; //������������ ��������� �����
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button6Click(TObject *Sender)
{
	  Timer1->Enabled = false;    //����� �������, ����� ������ ������� ������
	  Timer1->Interval = mstimer;   //������������� ����� ����������� ����
	  Timer1->Enabled = true;    //��������� ������ ������
	  guess = 5; //������������ ��������� �����
}
//---------------------------------------------------------------------------

