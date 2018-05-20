//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"
#include <fstream.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int kolpol; //кол-во пользователей
double *bnbn=new double[kolpol];   //вектор, хранЯщий эталонные ответы пользователей


void Obrabotka()  //Ћбучение программы на данных - метод логистической регрессии
{
	double lambda=0;
	int len=86;      //Кколичество параметров клавиатурного почерка
	int raz=50;     //Кколичество раз ввода

	//подсчет кол-ва пользователей
	int strok = 20;
	int ll = 30;
	char **maspol=new char*[strok];
	for (int i = 0; i < strok; i++) {
		maspol[i]=new char[ll];
	}

	ifstream polz;
	polz.open("Data\\POLZ.txt", ios_base::in);
	for (int i = 0; i < strok; i++) {
		if (!polz.eof()) {
			polz>>maspol[i];
		}
		else break;
	}
	AnsiString bb="NUL";
	for (int i = 0; i < strok; i++) {
		if (maspol[i]==bb) {
			kolpol=i;
			break;
		}
	}
	polz.close();
	
	for (int i = 0; i < strok; i++) {
		delete []maspol[i];
	}
	delete []maspol;

	//конец подсчет кол-ва пользователей

	int t=kolpol*raz;   //общее кол-во строк в матрице
	double *yyy = new double[t];  //массив ответов
	double **matr = new double*[t];      //матрица значений
	for (int i = 0; i < t; i++) {
		matr[i] = new double[len];
	}


	ifstream Dan;      //загрузка значений в матрицу из файла
	Dan.open("Data\\DANNIE.txt", ios_base::in);
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < len+1; j++) {
			if (j<len) {
				Dan>>matr[i][j];
			}
			else Dan>>yyy[i];
		}
	}
	Dan.close();

	double **matrsred = new double*[kolpol];
	for (int i = 0; i < kolpol; i++) {
		matrsred[i] = new double [len];
	}
	for (int i=0; i < kolpol; i++) {
		for (int j = 0; j < len; j++) {
			matrsred[i][j] = 0;
		}
	}
	int jo;                       //подсчет среднего вектора длЯ каждого пользователя
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < len; j++) {
			jo=yyy[i];
			if ((raz*(jo+1)-i)<=(raz-10)) {      
				matrsred[jo][j]=matrsred[jo][j]+matr[i][j];
			}
		}
	}


	for (int i=0; i < kolpol; i++) {
		for (int j = 0; j < len; j++) {
			matrsred[i][j] = matrsred[i][j]/(raz-10);   
		}
	}

	//нормирование
	double *sr = new double[len+1]; //среднее значение
	double *skv = new double[len+1]; //среднеквадратичное значение
	for (int i = 0; i < len+1; i++) {
		sr[i]=0;
		skv[i]=0;
	}
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < len+1; j++) {
			if (j<len) {
				sr[j]=sr[j]+matr[i][j];
				skv[j]=skv[j]+matr[i][j]*matr[i][j];
			}
			else
			{
				sr[j]=sr[j]+yyy[i];
				skv[j]=skv[j]+yyy[i]*yyy[i];
			}
		}
	}
	for (int i = 0; i < len+1; i++) {
		sr[i]=sr[i]/t;
		skv[i]=sqrt(skv[i]/t);
	}
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < len+1; j++) {
			if (j<len) {
				matr[i][j]=(matr[i][j]-sr[j])/skv[j];
			}
			else
			{
				yyy[i]=(yyy[i]-sr[j])/skv[j];
			}
		}
	}
	//нормирование закончено

	double **matrtr = new double*[len];  //транспонированнаЯ матрица значений
	for (int i = 0; i < len; i++) {
		matrtr[i]=new double[t];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < t; j++) {
			matrtr[i][j]=matr[j][i];
		}
	}
	//транспонирование закончено

	//умножение матриц
	double **matr2 = new double*[len]; //результат умножениЯ матрицы значений и транспонированной матрицы значений
	for (int i = 0; i < len; i++) {
		matr2[i] = new double[len];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			matr2[i][j]=0;
			for (int k = 0; k < t; k++) {
				matr2[i][j]=matr2[i][j]+matrtr[i][k]*matr[k][j];
			}
		}
	}
	// перемножение матриц закончено


	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (i==j) {
				matr2[i][j]=matr2[i][j]+lambda;
			}
		}
	}

	//подсчет обратной матрицы

	double **obr = new double * [len];
	for (int i = 0; i < len; i++) {
		obr[i] = new double[len];
	}
	for (int i = 0; i < len; i++)
		for (int j = 0;j<len; j++) {
			obr[i][j]=matr2[i][j];
		}

	int           i1, i2, i3;
	double   mult, dt;
	double **E = new double*[len];
	for (int i = 0; i < len; i++)  E[i]=new double[len];
	for (int i = 0; i < len; i++)
		for (int j = 0;j<len; j++) {
			if (i==j) {
				E[i][j]=1;
			}
			else  E[i][j]=0;
		}
	// ставим на диагональ единицы
	for(i1 = 0; i1 < len; i1++)
	{
		mult = matr2[i1][i1];
		for(i2 = 0; i2 < len; i2++)
		{
			matr2[i1][i2] = matr2[i1][i2] / mult;
			E[i1][i2] = E[i1][i2] / mult;
		}
	}

  // обнулем все выше диагонали
	for(i1 = 1; i1 < len; i1++)            // идем по диагонали
	{
		for(i2 = i1 - 1; i2 >= 0; i2--)    // идем по строкам
		{
			mult = matr2[i2][i1];
			for(i3 = 0; i3 < len; i3++)        // идем по столбцам
			{
				matr2[i2][i3] = matr2[i2][i3] - (matr2[i1][i3] * mult);
				E[i2][i3] = E[i2][i3] - (E[i1][i3] * mult);
			}
		}
	}


  // перегрузка данных в temp
	for(i1 = 0; i1 < len; i1++)
		for(i2 = 0; i2 < len; i2++)
			matr2[i1][i2] = E[i1][i2];
  //конец подсчета обратной матрицы



	double **m2 = new double*[len]; // умножение после обратной матрицы
	for (int i = 0; i < len; i++) {
		m2[i] = new double[t];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < t; j++) {
			m2[i][j]=0;
			for (int k = 0; k < len; k++) {
				m2[i][j]=m2[i][j]+matr2[i][k]*matrtr[k][j];
			}
		}
	}

	double *Q = new double[len];    //вектор коэффициентов
	for (int i = 0; i < len; i++) {
			Q[i]=0;
			for (int k = 0; k < t; k++) {
				Q[i]=Q[i]+m2[i][k]*yyy[k];
			}

	}

	for (int i = 0; i < kolpol; i++) {
			  bnbn[i]=0;
	}

	for (int i=0; i < kolpol; i++) {
		for (int j = 0; j < len; j++) {
			bnbn[i]=bnbn[i]+Q[j]*matrsred[i][j];
		}
	}

	ofstream NNNX;
	NNNX.open("Data\\Y.txt", ios_base::app);
	for (int i = 0; i < kolpol; i++) {
			NNNX<<"bnbn="<<bnbn[i]<<"\t";
	}
	NNNX<<"\n"<<"matrsred=\t";
	for (int i=0; i < kolpol; i++) {
		for (int j = 0; j < len; j++) {
			NNNX<<matrsred[i][j]<<"\t";
		}
			NNNX<<"\n";
	}
	NNNX<<"\n";
	NNNX.close();



	ofstream NNN;
	NNN.open("Data\\Q.txt",ios_base::out | ios_base::trunc);
	for (int i = 0; i < len; i++) {
			NNN<<Q[i]<<"\t";
	}
	NNN.close();


}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	 Obrabotka();
	 Application->CreateForm(__classid(TForm2), &Form2); //каждый раз при нажатии кнопки создается окно-форма
	 Form2->ShowModal();    //созданное окно блокирует взаимодействие с другими окнами, пока оно открыто
	 Form2->Free();  //при закрытии окна занятая оперативная память освобождается
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	 Application->CreateForm(__classid(TForm4), &Form4); //каждый раз при нажатии кнопки создается окно-форма
	 Form4->ShowModal();    //созданное окно блокирует взаимодействие с другими окнами, пока оно открыто
	 Form4->Free();  //при закрытии окна занятая оперативная память освобождается
}
//---------------------------------------------------------------------------

