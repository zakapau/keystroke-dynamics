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
int n = 0;  //сколько символов фразы нажато
int n2 = 0; //сколько символов фразы отпущено
std::vector<DWORD> tkeydownmas;     //вектор, хранящий времена нажатий клавиш
std::vector<DWORD> tkeyupmas; //вектор, хранящий времена отпусканий клавиш
AnsiString whois;  //имя того, кого идентифицировала программа (будет передаваться в Unit3)
int all = 0;  //всего попыток ввода
int yy = 0;   //пользователь есть в базе и он определен правильно
int yn1 = 0;   //пользователь есть в базе, но говорят, что его нет в базе
int yn2 = 0;   //пользователь есть в базе, но он определен как другой пользователь
int ny = 0;   //пользователя нет и говорят, что его нет в базе (т.е. определен правильно)
int nn = 0;   //пользователя нет, но он определен каким-то из имеющихся пользователей (т.е. определен неправильно)

int m; //ответ, номер пользователя
extern kolpol;
extern  double *bnbn;

double Klas()    //Классификация, здесь происходит идентификация пользователя
{
	double len=86;  //Количество параметров клавиатурного почерка
	double *mas = new double[len];

	ifstream Q;
	Q.open("Data\\Q.txt", ios_base::in);
	for (int i = 0; i < len; i++) {
		Q>>mas[i];
	}
	Q.close();

	double *zna = new double[len];   //записываем введенные значения
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
	   LoadKeyboardLayout("00000409", KLF_ACTIVATE); //сразу переключение на английскую раскладку (на русскую - 00000419)
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	n = 0;
    n2 = 0;
	tkeydownmas.clear();
	tkeyupmas.clear();
	Close();  //закрываем это окошко
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	Edit1->Text = "";  //очистка поля ввода
	n = 0;
	n2 = 0;
	tkeydownmas.clear();
	tkeyupmas.clear();
    Edit1->SetFocus();  //делаем поле ввода сразу в фокусе, т.е. курсор уже там
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift) //обрабатывается событие при нажатии любой клавиши
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
			Label2->Caption = t; //вывод времен на label, чтобы смотреть на них)
		}
		else {       //если нажат не тот символ, что идет в контрольной фразе
			Application->MessageBox(L"Ошибка. Попробуйте заново", L"Ошибка ввода", MB_OK | MB_ICONERROR);
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
	//записываем в stat статистику по вводам и ошибкам идентификации
	int OutHandle2;
	if (!DirectoryExists("Data")) {  //проверка существования папки с файлами данных
		CreateDir("Data");   //если ещё нет, то создать
	}
	if (!FileExists("Data\\stat.txt")) {  //проверка существования файла статистики
		OutHandle2 = FileCreate("Data\\stat.txt"); //если ещё нет, то создаем этот файл
		FileClose(OutHandle2);
	}
	ofstream statout ("Data\\stat.txt", ios_base::app); //открыли файл для добавления информации в конец
	statout << "all: " << all << ", yy: " << yy << ", yn1: " << yn1 << ", yn2: " << yn2 << ", ny: " << ny << ", nn: " << nn << "\n";  //записываем статистику
	statout.close(); //закрыли открытый файл
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)   //обрабатывается событие при нажатии любой клавиши
{
	DWORD t2;   //переменная для хранения времени
	int i2;    //переменная для счетчиков
	if (Key>=65 && Key<=90 || Key==32 || Key==8 || Key>=48 && Key<=57 || Key>=186 && Key<=192 || Key>=219 && Key<=222) {     //если нажато то, что отобржается в поле ввода, или backspace
		n2++;  //отпущена клавиша, которую можно сравнивать с символом контрольной строки
		t2 = GetTickCount(); //время текущего отпуска
		tkeyupmas.push_back(t2);  //сохраняем время текущего нажатия в вектор
		Label2->Caption = t2; //вывод времен на label, чтобы смотреть на них)
		if (n2==Label3->Caption.Length()) {      //если нажат последний символ контрольной фразы
			//должно быть 43

			//записываем в log успешную попытку
			int OutHandle;
			if (!DirectoryExists("Data")) {  //проверка существования папки с файлами данных
				CreateDir("Data");   //если ещё нет, то создать
			}
			if (!FileExists("Data\\log.txt")) {  //проверка существования файла с данными об успешных попытках ввода
				OutHandle = FileCreate("Data\\log.txt"); //если ещё нет, то создаем этот файл
				FileClose(OutHandle);
			}
			ofstream logout ("Data\\log.txt", ios_base::app); //открыли файл для добавления информации в конец
			logout<<Now()<<"\t";  //текущие дата-время

			ofstream ZZZ ("Data\\zna.txt"); //файл со значениями

			for (i2 = 1; i2 < n2; i2++) {
				logout<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t"; //записываем времена между нажатиями
				ZZZ<<tkeydownmas[i2]-tkeydownmas[i2-1]<<"\t";
			}
			for (i2 = 0; i2 < n2; i2++) {
				logout<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t"; //записываем длительности нажатий (от нажатия до отпускания)
				ZZZ<<tkeyupmas[i2]-tkeydownmas[i2]<<"\t";
			}
			logout<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\t"; //записываем скорость ввода
			ZZZ<<(double)(tkeyupmas[n2-1]-tkeydownmas[0])/n2<<"\n";
			logout<<"\n";
			ZZZ.close();
			logout.close(); //закрыли открытый файл

			//ТУТ АНАЛИЗ БАЗЫ!!!
			if (Klas()<50) {   //50 - это порог чувствительности
				Application->CreateForm(__classid(TForm3), &Form3); //при успешном вводе создается окно-форма для пользователя
				Form3->ShowModal();    //созданное окно блокирует взаимодействие с другими окнами, пока оно открыто
				Form3->Free();  //при закрытии окна занятая оперативная память освобождается
			}
			else {
				whois = "";
                Application->CreateForm(__classid(TForm3), &Form3); //при успешном вводе создается окно-форма для пользователя
				Form3->ShowModal();    //созданное окно блокирует взаимодействие с другими окнами, пока оно открыто
				Form3->Free();  //при закрытии окна занятая оперативная память освобождается
				//Application->MessageBox(L"Невозможно идентифицировать пользователя. Проверьте наличие данных пользователя в базе и повторите ввод.", L"Пользователь не определен", MB_OK | MB_ICONWARNING);

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

