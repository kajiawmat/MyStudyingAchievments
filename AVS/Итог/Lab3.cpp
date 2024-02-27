#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<time.h>
#include<immintrin.h>

using namespace std;

double Min=0.125;
double Max=8;
const int BS=25;

double RandVal()
{
	return rand()*(Max-Min)/RAND_MAX+Min;
}

void Zero_Matr(double* Matr,int N)
{
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) Matr[i*N+j]=0;
}

void DGEMM_PASS(double* Matr_A, double* Matr_B,double* Matr_C,long long N)
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

void DGEMM_opt_1(double* Matr_A, double* Matr_B,double* Matr_C,long long N)
{
	double *a,*b,*c;
	for(long long i=0;i<N;i++)
	{
		a=Matr_A+i*N;
		c=Matr_C+i*N;
		for(long long k=0;k<N;k++)
		{
			b=Matr_B+k*N;
			for(long long j=0;j<N;j++)
			{
				c[j]+=a[k]*b[j];
			}
		}
	}
}

void DGEMM_opt_2(double* Matr_A, double* Matr_B,double* Matr_C,long long N)
{
	long long i0,j0,k0,i,j,k;
	double *a,*b,*c;
	for(i=0;i<N;i+=BS)
	{
		for(k=0;k<N;k+=BS)
		{
			for(j=0;j<N;j+=BS)
			{
				for(i0=0,a=Matr_A+i*N+k,c=Matr_C+i*N+j;i0<BS;i0++,a+=N,c+=N)
				{
					for(k0=0,b=Matr_B+k*N+j;k0<BS;k0++,b+=N)
					{
						for(j0=0;j0<BS;j0++)
						{
							c[j0]+=a[k0]*b[j0];
						}
					}
				}
			}
		}
	}
}

void DGEMM_opt_3(double* Matr_A, double* Matr_B,double* Matr_C,long long N)
{
	long long i0,j0,k0,i,j,k;
	double *a,*b,*c;
	for(i=0;i<N;i+=BS)
	{
		for(k=0;k<N;k+=BS)
		{
			for(j=0;j<N;j+=BS)
			{
				for(i0=0,a=Matr_A+i*N+k,c=Matr_C+i*N+j;i0<BS;i0++,a+=N,c+=N)
				{
					for(k0=0,b=Matr_B+k*N+j;k0<BS;k0++,b+=N)
					{
						for(j0=0;j0<BS;j0++)
						{
							c[j0]+=a[k0]*b[j0];
						}
					}
				}
			}
		}
	}
}

int main()
{
	long long start,end,N;
	double *Matr_A,*Matr_B,*Matr_C;
	cin>>N;
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
	start=clock();
	DGEMM_PASS(Matr_A,Matr_B,Matr_C,N);
	end=clock();
	cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
	cout<<Matr_C[0]<<" "<<Matr_C[1]<<endl;
	cout<<Matr_C[BS*N/2]<<" "<<Matr_C[BS*N/2+1]<<endl;
	Zero_Matr(Matr_C,N);
	start=clock();
	DGEMM_opt_1(Matr_A,Matr_B,Matr_C,N);
	end=clock();
	cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
	cout<<Matr_C[0]<<" "<<Matr_C[1]<<endl;
	cout<<Matr_C[BS*N/2]<<" "<<Matr_C[BS*N/2+1]<<endl;
	Zero_Matr(Matr_C,N);
	start=clock();
	DGEMM_opt_2(Matr_A,Matr_B,Matr_C,N);
	end=clock();
	cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
	cout<<Matr_C[0]<<" "<<Matr_C[1]<<endl;
	cout<<Matr_C[BS*N/2]<<" "<<Matr_C[BS*N/2+1]<<endl;
	/*Zero_Matr(Matr_C,N);
	start=clock();
	DGEMM_opt_3(Matr_A,Matr_B,Matr_C,N);
	end=clock();
	cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;*/
	return 0;
}
