//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "windows.h"
#include <fstream.h>
#include "Unit4.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int n = 0;  //������� �������� ����� ������
int n2 = 0;  //������� �������� ����� ��������
int raz;  //������� ��� �������� ������ �����
std::vector<DWORD> tkeydownmas;     //������, �������� ������� ������� ������
std::vector<DWORD> tkeyupmas; //������, �������� ������� ���������� ������
AnsiString name;   //��� ������������

int L;  //����� ������������

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
    LoadKeyboardLayout("00000409", KLF_ACTIVATE); //������������ �� ���������� ��������� (�� ������� - 00000419)
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	Label2->Visible = True;
	Label3->Visible = True;
	Edit2->Visible = True;
	Label4->Visible = True;
	Label5->Visible = True;
	Edit2->SetFocus();  //������ ���� ����� ����� � ������, �.�. ������ ��� ���

	raz = 50;     //������������� ���������� ������ ����������� �����
	Label5->Caption = IntToStr(raz);
	name = Edit1->Text;

	int BaseHandle;
	if (!DirectoryExists("Data")) {  //�������� ������������� ����� � ������� ������
		CreateDir("Data");   //���� ��� ���, �� �������
	}
	if (!FileExists("Data\\DANNIE.txt")) {  //�������� ������������� ����� � ����� ������ ������������������ �������������
		BaseHandle = FileCreate("Data\\DANNIE.txt"); //���� ��� ���, �� ������� ���� ����
		FileClose(BaseHandle);
	}

	//������� ������ ������������ � ������ ������ ������������ � ����
	int strok = 20;  //������������ ���������� ������������� ����� ����, ������� ����� ����������
	int len = 30;      //������������ ��� ������������
	char **maspol=new char*[strok];
	for (int i = 0; i < strok; i++) {
		maspol[i]=new char[len];
	}

	ifstream XXX;     //���������� ���� �������������
	XXX.open("Data\\POLZ.txt", ios_base::in);
	for (int i = 0; i < 10; i++) {
		if (!XXX.eof()) {
			XXX>>maspol[i];
		}
		else break;

	}
	AnsiString bb="NUL";
	for (int i = 0; i < 10; i++) {
		if (maspol[i]==bb) {
			maspol[i]=name.c_str();
			maspol[i+1]="NUL";
			L=i;
			break;
		}
	}
	XXX.close();
	ofstream XX;  //������ ������ ������������ � ���� �������������
	XX.open("Data\\POLZ.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < L+2; i++) {
		XX<<maspol[i]<<"\n";
	}
	XX.close();

	for (int i = 0; i < strok; i++) {
		delete []maspol[i];
	}
	delete []maspol;
	//����� �������� ������ ������������� � ������ ������ ������������ � ����

}
//---------------------------------------------------------------------------
void __fastcall TForm4::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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
		}
		else {       //���� ����� �� ��� ������, ��� ���� � ����������� �����
			Application->MessageBox(L"������. ���������� ������", L"������ �����", MB_OK | MB_ICONERROR);
			Edit2->Text = "";
			n = 0;
			n2 = 0;
			tkeydownmas.clear();
			tkeyupmas.clear();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Edit2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	DWORD t2;   //���������� ��� �������� �������
	int i2;    //���������� ��� ���������
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //���� ������ ��, ��� ����������� � ���� �����, ��� backspace
		n2++;  //�������� �������, ������� ����� ���������� � �������� ����������� ������
		t2 = GetTickCount(); //����� �������� �������
		tkeyupmas.push_back(t2);  //��������� ����� �������� ������� � ������
		if (n2==Label3->Caption.Length()) {      //���� ����� ��������� ������ ����������� �����
				//������ ���� 43

				//���������� � DANNIE.txt ������ �������� ���� ������������
                ofstream DDD;
				DDD.open("Data\\DANNIE.txt", ios_base::app);
                for (i2 = 1; i2 < n2; i2++) {
				   DDD<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t"; //���������� ������� ����� ���������
				}
                for (i2 = 0; i2 < n2; i2++) {
				   DDD<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t"; //���������� ������������ ������� (�� ������� �� ����������)
				}
                DDD<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\t"; //���������� �������� �����
                DDD<<L<<"\n";
				DDD.close();

                Application->MessageBox(L"����� ������� �������!", L"�������� ����", MB_OK | MB_ICONINFORMATION);

				raz = raz-1;
				Label5->Caption = IntToStr(raz);
				Edit2->Text = "";
				n = 0;
				n2 = 0;
				tkeydownmas.clear();
				tkeyupmas.clear();

				if (raz==0) {
					Application->MessageBox(L"������������ ������� ���������������!", L"�����������", MB_OK | MB_ICONINFORMATION);
					Close();
				}
			}
	}
}
//---------------------------------------------------------------------------


