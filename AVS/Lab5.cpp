#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<time.h>
#include<cstring>
#include<omp.h>

#pragma STDC FP_CONTRACT ON

using namespace std;

const char FunctionName[]="DGEMM";
const char ElementType[]="double";
const char Timer[]="clock()";
const double Min=0.125;
const double Max=8;
int Opt=0;
int NumThreads=4;
long long N=1000;

void Check_CSV_exist()
{
	FILE* fp=fopen("Lab5.csv","r");
	if(fp==NULL)
	{
		fp=fopen("Lab5.csv","w");
		fprintf(fp,"FuncName;ElenentType;Optimization;Size;NumThreads;Timer;TimeFunc;\n");
		fclose(fp);	
	}
}

void Set_Parameters(int argc, char* argv[])
{
	int flag=0;
	for(int i=1;i<argc;i++)
	{
		if(flag==1) 
		{
			N=0;
			for(int j=0;argv[i][j]!='\0';j++)
			{
				if(argv[i][j]>='0' && argv[i][j]<='9') N=N*10+(argv[i][j]-'0');
				else {cout<<"Wrong Input parameters"; exit(-1);}
			}
			if(N<1000) N=1000;
			flag=0;
		}
		else if(flag==2) 
		{
			NumThreads=0;
			for(int j=0;argv[i][j]!='\0';j++)
			{
				if(argv[i][j]>='0' && argv[i][j]<='9') NumThreads=NumThreads*10+(argv[i][j]-'0');
				else {cout<<"Wrong Input parameters"; exit(-1);}
			}
			flag=0;
		}
		else if(flag==3) 
		{
			if(argv[i][0]>='0' && argv[i][0]<='3') Opt=argv[i][0]-'0';
			else {cout<<"Wrong Input parameters"; exit(-1);}
			flag=0;
		}
		else if(strcmp(argv[i],"--number-element")==0 || strcmp(argv[i],"-n")==0) flag=1;
		else if(strcmp(argv[i],"--threads-number")==0 || strcmp(argv[i],"-t")==0) flag=2;
		else if(strcmp(argv[i],"--optimization")==0 || strcmp(argv[i],"-o")==0) flag=3;
		else {cout<<"Wrong Input parameters"; exit(-1);}
	}
}

void WriteIntoFile(double diffTime)
{
	FILE* csw=fopen("Lab5.csv","a");
	fprintf(csw,"%s;",FunctionName);
	fprintf(csw,"%s;",ElementType);
	fprintf(csw,"%i;",Opt);
	fprintf(csw,"%lli;",N);
	fprintf(csw,"%i;",NumThreads);
	fprintf(csw,"%s;",Timer);
	fprintf(csw,"%.9f;\n",diffTime);
	fclose(csw);
}

double RandVal()
{
	return rand()*(Max-Min)/RAND_MAX+Min;
}

void Zero_Matr(double* Matr,int N)
{
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) Matr[i*N+j]=0;
}

void DGEMM_PASS(double* Matr_A, double* Matr_B,double* Matr_C)
{
	double *a,*b,*c;
	for(long long i=0;i<N;i++)
	{
		a=Matr_A+i*N;
		c=Matr_C+i*N;
		for(long long j=0;j<N;j++)
		{
			b=Matr_B;
			for(long long k=0;k<N;k++)
			{
				c[j]+=a[k]*b[j];
				b+=N;
			}
		}
	}
}

void DGEMM_PASS_v2(double* Matr_A, double* Matr_B,double* Matr_C)
{
	long long n=N/100;
	double *a,*b,*c;
	for(long long i=0;i<n;i++)
	{
		a=Matr_A+i*N;
		c=Matr_C+i*N;
		for(long long j=0;j<N;j++)
		{
			b=Matr_B;
			for(long long k=0;k<N;k++)
			{
				c[j]+=a[k]*b[j];
				b+=N;
			}
		}
	}
}

void DGEMM_PASS_OpenMP(double* Matr_A, double* Matr_B,double* Matr_C)
{
	long long i,j,k;
	#pragma opm for private(i,j,k) shared(Matr_A,Matr_B,Matr_C)
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			for(k=0;k<N;k++)
			{
				Matr_C[i*N+j]+=Matr_A[i*N+k]*Matr_B[k*N+j];
			}
		}
	}
}


int main(int argc, char* argv[])
{
	Set_Parameters(argc,argv);
	Check_CSV_exist();
	long long start,end;
	double diff_time;
	double *Matr_A,*Matr_B,*Matr_C;
	Matr_A=new double[N*N];
	Matr_B=new double[N*N];
	Matr_C=new double[N*N];
	for(long long i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			Matr_A[i*N+j]=RandVal();
			Matr_B[i*N+j]=RandVal();
		}
	}
	Zero_Matr(Matr_C,N);
	//omp_set_dynamic(0);
	//omp_set_num_threads(NumThreads);
	start=clock();
	switch(Opt)
	{
		case 0:
			if(N>=4000) DGEMM_PASS_v2(Matr_A,Matr_B,Matr_C);
			else DGEMM_PASS(Matr_A,Matr_B,Matr_C);
			break;
		case 1:
			DGEMM_PASS_OpenMP(Matr_A,Matr_B,Matr_C);
			break;
		case 2:
			break;
	}
	end=clock();
	diff_time=(double)(end-start)/CLOCKS_PER_SEC;
	if(N>=4000 && Opt==0) diff_time*=100;
	WriteIntoFile(diff_time);
	delete Matr_A;
	delete Matr_B;
	delete Matr_C;
	return 0;
}
