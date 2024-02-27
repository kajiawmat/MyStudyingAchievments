#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main()
{
	ofstream f("test1.csv",ios::app);
	f<<"World"<<endl;
	return 0;
}
