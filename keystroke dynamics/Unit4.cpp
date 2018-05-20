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
int n = 0;  //сколько символов фразы нажато
int n2 = 0;  //сколько символов фразы отпущено
int raz;  //сколько раз осталось ввести фразу
std::vector<DWORD> tkeydownmas;     //вектор, хранящий времена нажатий клавиш
std::vector<DWORD> tkeyupmas; //вектор, хранящий времена отпусканий клавиш
AnsiString name;   //имя пользователя

int L;  //номер пользователя

TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
    LoadKeyboardLayout("00000409", KLF_ACTIVATE); //переключение на английскую раскладку (на русскую - 00000419)
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	Label2->Visible = True;
	Label3->Visible = True;
	Edit2->Visible = True;
	Label4->Visible = True;
	Label5->Visible = True;
	Edit2->SetFocus();  //делаем поле ввода сразу в фокусе, т.е. курсор уже там

	raz = 50;     //устанавливаем количество вводов контрольной фразы
	Label5->Caption = IntToStr(raz);
	name = Edit1->Text;

	int BaseHandle;
	if (!DirectoryExists("Data")) {  //проверка существования папки с файлами данных
		CreateDir("Data");   //если ещё нет, то создать
	}
	if (!FileExists("Data\\DANNIE.txt")) {  //проверка существования файла с базой вводов зарегистрированных пользователей
		BaseHandle = FileCreate("Data\\DANNIE.txt"); //если ещё нет, то создаем этот файл
		FileClose(BaseHandle);
	}

	//подсчет номера пользователя и запись нового пользователя в базу
	int strok = 20;  //максимальное количество пользователей минус один, которое может зарегаться
	int len = 30;      //максимальное имя пользователя
	char **maspol=new char*[strok];
	for (int i = 0; i < strok; i++) {
		maspol[i]=new char[len];
	}

	ifstream XXX;     //считывание имен пользователей
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
	ofstream XX;  //запись нового пользователя в базу пользователей
	XX.open("Data\\POLZ.txt", ios_base::out | ios_base::trunc);
	for (int i = 0; i < L+2; i++) {
		XX<<maspol[i]<<"\n";
	}
	XX.close();

	for (int i = 0; i < strok; i++) {
		delete []maspol[i];
	}
	delete []maspol;
	//конец подсчета номера пользователей и записи нового пользователя в базу

}
//---------------------------------------------------------------------------
void __fastcall TForm4::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    DWORD t;   //переменная для хранения времени
	int i;     //переменная для счетчиков
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //если нажато то, что отобржается в поле ввода, или backspace
		n++;  //нажата клавиша, которую можно сравнивать с символом контрольной строки
		if (Key>=65 && Key<=90) {  //если нажат символ, поправляем кодировку символов для дальнейшего сравнения
			Key = Key + 32;
		}
		if (n<=Label3->Caption.Length() && Key==Label3->Caption[n]) {    //сравниваем введенный символ с контрольной строкой и проверка, чтобы последнюю клавишу не зажимали и не вылетала ошибка Range
			t = GetTickCount(); //время текущего нажатия
			tkeydownmas.push_back(t);  //сохраняем время текущего нажатия в вектор
		}
		else {       //если нажат не тот символ, что идет в контрольной фразе
			Application->MessageBox(L"Ошибка. Попробуйте заново", L"Ошибка ввода", MB_OK | MB_ICONERROR);
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
	DWORD t2;   //переменная для хранения времени
	int i2;    //переменная для счетчиков
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //если нажато то, что отобржается в поле ввода, или backspace
		n2++;  //отпущена клавиша, которую можно сравнивать с символом контрольной строки
		t2 = GetTickCount(); //время текущего отпуска
		tkeyupmas.push_back(t2);  //сохраняем время текущего нажатия в вектор
		if (n2==Label3->Caption.Length()) {      //если нажат последний символ контрольной фразы
				//должно быть 43

				//записываем в DANNIE.txt каждый успешный ввод пользователя
                ofstream DDD;
				DDD.open("Data\\DANNIE.txt", ios_base::app);
                for (i2 = 1; i2 < n2; i2++) {
				   DDD<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t"; //записываем времена между нажатиями
				}
                for (i2 = 0; i2 < n2; i2++) {
				   DDD<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t"; //записываем длительности нажатий (от нажатия до отпускания)
				}
                DDD<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\t"; //записываем скорость ввода
                DDD<<L<<"\n";
				DDD.close();

                Application->MessageBox(L"Фраза успешно введена!", L"Успешный ввод", MB_OK | MB_ICONINFORMATION);

				raz = raz-1;
				Label5->Caption = IntToStr(raz);
				Edit2->Text = "";
				n = 0;
				n2 = 0;
				tkeydownmas.clear();
				tkeyupmas.clear();

				if (raz==0) {
					Application->MessageBox(L"Пользователь успешно зарегистрирован!", L"Регистрация", MB_OK | MB_ICONINFORMATION);
					Close();
				}
			}
	}
}
//---------------------------------------------------------------------------


