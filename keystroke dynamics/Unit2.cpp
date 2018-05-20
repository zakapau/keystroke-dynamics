//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
#include "windows.h"
#include <fstream.h>
#include <vector>
#include <math.h>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int n = 0;  //������� �������� ����� ������
int n2 = 0; //������� �������� ����� ��������
std::vector<DWORD> tkeydownmas;     //������, �������� ������� ������� ������
std::vector<DWORD> tkeyupmas; //������, �������� ������� ���������� ������
AnsiString whois;  //��� ����, ���� ���������������� ��������� (����� ������������ � Unit3)
int all = 0;  //����� ������� �����
int yy = 0;   //������������ ���� � ���� � �� ��������� ���������
int yn1 = 0;   //������������ ���� � ����, �� �������, ��� ��� ��� � ����
int yn2 = 0;   //������������ ���� � ����, �� �� ��������� ��� ������ ������������
int ny = 0;   //������������ ��� � �������, ��� ��� ��� � ���� (�.�. ��������� ���������)
int nn = 0;   //������������ ���, �� �� ��������� �����-�� �� ��������� ������������� (�.�. ��������� �����������)

int m; //�����, ����� ������������
extern kolpol;
extern  double *bnbn;

double Klas()    //�������������, ����� ���������� ������������� ������������
{
	double len=86;  //���������� ���������� ������������� �������
	double *mas = new double[len];

	ifstream Q;
	Q.open("Data\\Q.txt", ios_base::in);
	for (int i = 0; i < len; i++) {
		Q>>mas[i];
	}
	Q.close();

	double *zna = new double[len];   //���������� ��������� ��������
	ifstream znn;
	znn.open("Data\\zna.txt", ios_base::in);
	for (int i = 0; i < len; i++) {
		znn>>zna[i];
	}
	znn.close();


	ofstream Y;
	Y.open("Data\\Y.txt", ios_base::app);
	Y<<"zna=\t";
	for (int i = 0; i < len; i++) {
		Y<<zna[i]<<"\t";
	}
	Y<<"\n";
	Y.close();

	double otv=0;
	for (int i = 0; i < len; i++) {
		otv=otv+zna[i]*mas[i];
	}

	ofstream R;
	R.open("Data\\Y.txt", ios_base::app);

	double *xrxr=new double[kolpol];
	for (int i = 0; i < kolpol; i++)
	{
		xrxr[i]=abs(bnbn[i]-otv);
		R<<"  xrxr[i]= "<<xrxr[i]<<" ";
	}
	double min=xrxr[0];
	m=0;
	for (int i = 1; i < kolpol; i++) {
		if (min>xrxr[i]) {
			min=xrxr[i];
			m=i;
		}
	}

	R<<"\n";

	R<<"otv="<<otv<<"\n";
	R<<"min="<<min<<"  m="<<m<<"\n";
	R<<"--------------------------------------\n";
	R.close();

	int strok = 20;
	int ll = 30;
	char **maspol=new char*[strok];
	for (int i = 0; i < strok; i++) {
		maspol[i]=new char[ll];
	}

	ifstream XX;
	XX.open("Data\\POLZ.txt", ios_base::in);
	for (int i = 0; i < 10; i++) {
		if (!XX.eof()) {
			XX>>maspol[i];
		}
		else break;

	}
	XX.close();

	whois=maspol[m];

	return(min);
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	   LoadKeyboardLayout("00000409", KLF_ACTIVATE); //����� ������������ �� ���������� ��������� (�� ������� - 00000419)
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	n = 0;
    n2 = 0;
	tkeydownmas.clear();
	tkeyupmas.clear();
	Close();  //��������� ��� ������
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	Edit1->Text = "";  //������� ���� �����
	n = 0;
	n2 = 0;
	tkeydownmas.clear();
	tkeyupmas.clear();
    Edit1->SetFocus();  //������ ���� ����� ����� � ������, �.�. ������ ��� ���
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift) //�������������� ������� ��� ������� ����� �������
{
	DWORD t;   //���������� ��� �������� �������
	int i;     //���������� ��� ���������
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //���� ������ ��, ��� ����������� � ���� �����, ��� backspace
		n++;  //������ �������, ������� ����� ���������� � �������� ����������� ������
		if (Key>=65 && Key<=90) {  //���� ����� ������, ���������� ��������� �������� ��� ����������� ���������
			Key = Key + 32;
		}
		if (n<=Label3->Caption.Length() && Key==Label3->Caption[n]) {    //���������� ��������� ������ � ����������� ������� � ��������, ����� ��������� ������� �� �������� � �� �������� ������ Range
			t = GetTickCount(); //����� �������� �������
			tkeydownmas.push_back(t);  //��������� ����� �������� ������� � ������
			Label2->Caption = t; //����� ������ �� label, ����� �������� �� ���)
		}
		else {       //���� ����� �� ��� ������, ��� ���� � ����������� �����
			Application->MessageBox(L"������. ���������� ������", L"������ �����", MB_OK | MB_ICONERROR);
			Edit1->Text = "";
			n = 0;
			n2 = 0;
			tkeydownmas.clear();
			tkeyupmas.clear();
   		}
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
	//���������� � stat ���������� �� ������ � ������� �������������
	int OutHandle2;
	if (!DirectoryExists("Data")) {  //�������� ������������� ����� � ������� ������
		CreateDir("Data");   //���� ��� ���, �� �������
	}
	if (!FileExists("Data\\stat.txt")) {  //�������� ������������� ����� ����������
		OutHandle2 = FileCreate("Data\\stat.txt"); //���� ��� ���, �� ������� ���� ����
		FileClose(OutHandle2);
	}
	ofstream statout ("Data\\stat.txt", ios_base::app); //������� ���� ��� ���������� ���������� � �����
	statout << "all: " << all << ", yy: " << yy << ", yn1: " << yn1 << ", yn2: " << yn2 << ", ny: " << ny << ", nn: " << nn << "\n";  //���������� ����������
	statout.close(); //������� �������� ����
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)   //�������������� ������� ��� ������� ����� �������
{
	DWORD t2;   //���������� ��� �������� �������
	int i2;    //���������� ��� ���������
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //���� ������ ��, ��� ����������� � ���� �����, ��� backspace
		n2++;  //�������� �������, ������� ����� ���������� � �������� ����������� ������
		t2 = GetTickCount(); //����� �������� �������
		tkeyupmas.push_back(t2);  //��������� ����� �������� ������� � ������
		Label2->Caption = t2; //����� ������ �� label, ����� �������� �� ���)
		if (n2==Label3->Caption.Length()) {      //���� ����� ��������� ������ ����������� �����
			//������ ���� 43

			//���������� � log �������� �������
			int OutHandle;
			if (!DirectoryExists("Data")) {  //�������� ������������� ����� � ������� ������
				CreateDir("Data");   //���� ��� ���, �� �������
			}
			if (!FileExists("Data\\log.txt")) {  //�������� ������������� ����� � ������� �� �������� �������� �����
				OutHandle = FileCreate("Data\\log.txt"); //���� ��� ���, �� ������� ���� ����
				FileClose(OutHandle);
			}
			ofstream logout ("Data\\log.txt", ios_base::app); //������� ���� ��� ���������� ���������� � �����
			logout<<Now()<<"\t";  //������� ����-�����

			ofstream ZZZ ("Data\\zna.txt"); //���� �� ����������

			for (i2 = 1; i2 < n2; i2++) {
				logout<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t"; //���������� ������� ����� ���������
				ZZZ<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t";
			}
			for (i2 = 0; i2 < n2; i2++) {
				logout<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t"; //���������� ������������ ������� (�� ������� �� ����������)
				ZZZ<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t";
			}
			logout<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\t"; //���������� �������� �����
			ZZZ<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\n";
			logout<<"\n";
			ZZZ.close();
			logout.close(); //������� �������� ����

			//��� ������ ����!!!
			if (Klas()<50) {   //50 - ��� ����� ����������������
				Application->CreateForm(__classid(TForm3), &Form3); //��� �������� ����� ��������� ����-����� ��� ������������
				Form3->ShowModal();    //��������� ���� ��������� �������������� � ������� ������, ���� ��� �������
				Form3->Free();  //��� �������� ���� ������� ����������� ������ �������������
			}
			else {
				whois = "";
                Application->CreateForm(__classid(TForm3), &Form3); //��� �������� ����� ��������� ����-����� ��� ������������
				Form3->ShowModal();    //��������� ���� ��������� �������������� � ������� ������, ���� ��� �������
				Form3->Free();  //��� �������� ���� ������� ����������� ������ �������������
				//Application->MessageBox(L"���������� ���������������� ������������. ��������� ������� ������ ������������ � ���� � ��������� ����.", L"������������ �� ���������", MB_OK | MB_ICONWARNING);

			}

			Label2->Caption = "all: " + IntToStr(all) + ", yy: " + IntToStr(yy) + ", yn1: " + IntToStr(yn1) + ", yn2: " + IntToStr(yn2) + ", ny: " + IntToStr(ny) + ", nn: " + IntToStr(nn);

			Edit1->Text = "";
			n = 0;
			n2 = 0;
			tkeydownmas.clear();
			tkeyupmas.clear();
			}
	}
}
//---------------------------------------------------------------------------

