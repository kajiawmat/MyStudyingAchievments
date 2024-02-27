#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>

using namespace std;

const long long MIN = 10000, MAX = 10000;
const vector<string> OptNames = { "None","O1","O2" };
const vector<string> OpTypeNames = { "int","long long","double" };
const vector<string> TaskNames = {"matrXvect"};
const char Filename[] = "lab2.csv";
const int N = 1000, M = 1000;
const double Epsilon = 1.25;

long long Rows = 1;
string PModel;
string Task;
string OpType;
string Opt;
string Timer="Chrono";
const int InsCount = N * M * 2 - 1;


void SetOpModel()
{
	system("PModel.bat");
	ifstream in("PModel.txt");
	string temp;
	getline(in, PModel);
	in.close();
}

void SetRows()
{
	string temp;
	ifstream fin(Filename, ios::app);
	while (getline(fin, temp)) Rows++;
	fin.close();
}

void SetAttributes(ofstream& fout)
{
	SetOpModel();
	int sw;
	cout << "Выберите дейтсвие для редактирования csv-файла." << endl;
	cout << "0) Создать новый файл csv" << endl;
	cout << "1) Дополнить в новый файл csv" << endl;
	cin >> sw;
	system("CLS");
	if (sw == 0)
	{
		fout.open(Filename);
		fout << "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;RelErr;TaskPerf" << endl;
	}
	else fout.open(Filename, ios::app);
	fout.precision(9);
	cout << "Выберите какой способ оптимизации использовать:" << endl;
	for (long long i = 0; i < OptNames.size(); i++)
	{
		cout << i << ")\t" << OptNames[i] << endl;
	}
	cin >> sw;
	Opt = OptNames[sw];
	system("CLS");
	cout << "Выберите тип данных для выполняемых операций" << endl;
	for (long long i = 0; i < OpTypeNames.size(); i++)
	{
		cout << i << ")\t" << OpTypeNames[i] << endl;
	}
	cin >> sw;
	OpType = OpTypeNames[sw];
}

string DToS(string str)
{
	for (long long i = 0; i < str.length(); i++) if (str[i] == '.') str[i] = ',';
	return str;
}

void Random_Value(int &val)
{
	val = rand() % (MAX - MIN) + MIN;
}

void Random_Value(long long& val)
{
	val = rand() % (MAX - MIN) + MIN;
}

void Random_Value(double& val)
{
	val = rand() * (double)(MAX - MIN) / RAND_MAX + MIN;
}
template<class Type>
void Random_Value(Type** matr, vector<Type> vect)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			Random_Value(matr[i][j]);
		}
	}
	for (int j = 0; j < M; j++)
	{
		Random_Value(vect[j]);
	}
}

template<class Type>
vector<Type> matrXvect(Type** matr, vector<Type> vect)
{
	vector<Type> res;
	res.resize(N);
	Type val;
	for (int i = 0; i < N; i++)
	{
		val = 0;
		for (int j = 0; j < M; j++)
		{
			val += matr[i][j] * vect[j];
		}
		res[i] = val;
	}
	return res;
}

template<class Type>
void OpPerform(ofstream& fout, Type b)
{
	double value;
	vector<Type> (*Func[])(Type**,vector<Type>) = { matrXvect };
	double* Func_time_Array[1];
	double Func_AVtime[1];
	Type** matr=new Type*[N];
	vector<Type> vect;
	for (int i = 0; i < N; i++) matr[i] = new Type[M];
	vect.resize(M);
	long long start, end;
	cout << "Введите количество испытаний: ";
	int n;
	cin >> n;
	if (n < 10) n = 10;
	n++;
	for (int i = 0; i < TaskNames.size(); i++)
	{
		Func_AVtime[i] = 0;
		Func_time_Array[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			Random_Value(matr,vect);
			start = clock();
			Func[i](matr,vect);
			end = clock();
			Func_time_Array[i][j] =(double)(end - start)/CLOCKS_PER_SEC;
			if (j > 0)
			{
				Func_AVtime[i] += Func_time_Array[i][j];
				/*if (((Func_time_Array[i][j] * j) / Func_AVtime[i])>Epsilon)
				{
					Func_AVtime[i] -= Func_time_Array[i][j];
					j--;
					continue;
				}*/
			}
		}
		Func_AVtime[i] /= n;
		cout << endl;
		cout << Func_AVtime[i] << endl;
		string temp;
		for (int j = 1; j < n; j++)
		{
			fout << PModel << ";";
			fout << TaskNames[i] << ";";
			fout << OpType << ";";
			fout << Opt << ";";
			fout << InsCount << ";";
			fout << Timer << ";";

			fout << fixed << DToS(to_string(Func_time_Array[i][j])) << ";";
			fout << j << ";";
			fout << fixed << DToS(to_string(Func_AVtime[i])) << ";";
			fout << "=G" << Rows << "-I" << Rows << ";";
			fout << "=J" << Rows << "/I" << Rows << ";";
			fout << "=1/I" << Rows << ";";
			fout << '\n';
			Rows++;
		}
	}
	//cout<<endl;
	//cout<<str;
}

int main()
{
	double value=1;
	cout.precision(7);
	system("chcp 1251>nul");
	ofstream fout;
	SetAttributes(fout);
	SetRows();
	if(OpType==OpTypeNames[0]) OpPerform(fout,(int)value);
	if (OpType == OpTypeNames[1]) OpPerform(fout, (long long)value);
	if (OpType == OpTypeNames[2]) OpPerform(fout, value);

	return 0;
}