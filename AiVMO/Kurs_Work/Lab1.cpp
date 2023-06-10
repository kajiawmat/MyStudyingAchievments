#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>

using namespace std;

long long gcd(long long a, long long b) 
{
	if (a % b == 0) return b;
  	if (b % a == 0) return a;
	if (a > b) return gcd(a%b, b);
	return gcd(a, b%a);
}

long long lcm(long long a,long long b) 
{
	return (a*b)/gcd(a,b);
}

int Next_SetNum(vector<long long> &setNum, int p, int n)
{
	int k=setNum.size();
	setNum[p]++;
	for(int i=p+1;i<k;i++) setNum[i]=setNum[i-1]+1;
	if(setNum[k-1]==n-1) return p-1;
	return k-1;
}

class simp_frac
{
public:
	long long num;
	long long den;
	
	simp_frac(): num(0), den(1) {}
	simp_frac(long long _num): num(_num), den(1) {}
	simp_frac(long long _num, long long _den): num(_num), den(_den) {}
	
	simp_frac operator+(simp_frac other)
	{
		long long LCM=lcm(den,other.den);
		long long Num=num*LCM/den+other.num*LCM/other.den;
		if(Num==0) return simp_frac(0,1);
		else 
		{
			long long GCD=gcd(fabs(Num),LCM);
			return simp_frac(Num/GCD,LCM/GCD);
		}
	}
	simp_frac operator-(simp_frac other)
	{
		long long LCM=lcm(den,other.den);
		long long Num=num*LCM/den-other.num*LCM/other.den;
		if(Num==0) return simp_frac(0,1);
		else 
		{
			long long GCD=gcd(fabs(Num),LCM);
			return simp_frac(Num/GCD,LCM/GCD);
		}
	}
	simp_frac operator*(simp_frac other)
	{
		if(num==0 || other.num==0) return simp_frac(0);
		long long GCD_a=gcd(fabs(num),fabs(other.den));
		long long GCD_b=gcd(fabs(other.num),fabs(den));
		return simp_frac((num/GCD_a)*(other.num/GCD_b),(den/GCD_b)*(other.den/GCD_a));
	}
	simp_frac operator/(simp_frac other)
	{
		if(num==0) return simp_frac(0);
		long long GCD_a=gcd(fabs(num),fabs(other.num));
		long long GCD_b=gcd(fabs(other.den),fabs(den));
		long long _num=num;
		if(other.num<0) 
		{
			_num*=-1;
			other.num*=-1;
		}
		return simp_frac((_num/GCD_a)*(other.den/GCD_b),(den/GCD_b)*(other.num/GCD_a));
	}
	bool operator<(simp_frac other)
	{
		long double d1=num*other.den, d2=other.num*den;
		if(d1<d2) return true;
		else return false;
	}
};

void print_frac(simp_frac x)
{
	printf("%8lli/%-8lli",x.num,x.den);
}

void Print_Matr(vector< vector<simp_frac> > A, vector<simp_frac> B)
{
	for(long long i=0;i<A.size();i++)
	{
		for(long long j=0;j<A[i].size();j++) print_frac(A[i][j]);
		cout<<" | ";
		print_frac(B[i]);
		cout<<endl;	
	}
	cout<<endl;
}

void Print_Simp_Table(vector< vector<simp_frac> > A, vector<simp_frac> B,vector<simp_frac> Z, vector<long long> setNum)
{
	printf(" б.п. | %8c%-9i | ",' ',1);
	for(long long j=0;j<A[0].size();j++) printf("%8c%-9lli",'x',j+1);
	printf(" | С.О. ");
	cout<<"\n"<<string(14+18*(A[0].size()+1),'-')<<"\n";
	for(long long i=0;i<setNum.size();i++)
	{
		printf(" x%-4lli| ",setNum[i]+1);
		print_frac(B[i]);
		cout<<" | "; 
		for(long long j=0;j<A[i].size();j++) print_frac(A[i][j]);
		cout<<" | "; 
		cout<<endl;	
	}
	cout<<string(14+18*(A[0].size()+1),'-')<<"\n";
	printf("  Z   | ");
	print_frac(Z[Z.size()-1]);
	cout<<" | "; 
	for(long long j=0;j<Z.size()-1;j++) 
	{
		Z[j].num=-Z[j].num;
		print_frac(Z[j]);
	}
	cout<<" | \n\n\n";
}

void Calculate_Matr(vector< vector<simp_frac> > &A, vector<simp_frac> &B, long long k, long long s)
{
	simp_frac temp=A[k][s];
	simp_frac temp2;
	for(long long j=0;j<A[k].size();j++)
	{
		A[k][j]=A[k][j]/temp;
	}
	B[k]=B[k]/temp;
	for(long long i=0;i<A.size();i++)
	{
		if(i==k) continue;
		temp2=A[i][s];
		for(long long j=0;j<A[k].size();j++)
		{
			A[i][j]=A[i][j]-A[k][j]*temp2;
		}
		B[i]=B[i]-B[k]*temp2;
	}
}

int Check_Matr(vector< vector<simp_frac> > &A, vector<simp_frac> &B)
{
	int er=0;
	bool flag;
	for(long long i=0;i<A.size();i++)
	{
		flag=true;
		for(long long j=0;j<A[0].size();j++)
		{
			if(A[i][j].num!=0)
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			if(B[i].num==0)
			{
				er++;
				B.erase(B.begin()+i);
				A[i].clear();
				A.erase(A.begin()+i);
				i--;
			}
			else
			{
				return -1;
			}
		}
	}
	return er;
}

bool Exists_Num(long long x, vector<long long> setNum)
{
	for(long long i=0;i<setNum.size();i++) if(x==setNum[i]) return true;
	return false;
}

void Print_Solution(vector< vector<simp_frac> > A, vector<simp_frac> B, vector<long long> setNum, long long n)
{
	long long r=setNum.size();
	for(long long i=0;i<r;i++)
	{
		printf("x%lli=%lli/%lli",setNum[i]+1,B[i].num,B[i].den);
		for(long long j=0;j<n;j++)
		{
			if(!Exists_Num(j,setNum))
			{
				printf(" + (%lli/%lli)x%lli",A[i][j].num,A[i][j].den,j+1);
			}
		}
		printf(";\n");
	}
	printf("\n");
}

int Jordan_Gauss(vector< vector<simp_frac> > &A, vector<simp_frac> &B)
{
	vector<simp_frac> swap;
	simp_frac temp_b;
	int er;
	long long n=A[0].size();
	long long r=B.size(),k=0,s=0;
	while(k<r)
	{
		for(long long i=k;i<B.size();i++)
		{
			if(A[i][s].num!=0)
			{
				swap=A[i];
				A[i]=A[k];
				A[k]=swap;
				temp_b=B[i];
				B[i]=B[k];
				B[k]=temp_b;
				Calculate_Matr(A,B,k,s);
				er=Check_Matr(A,B);
				if(er==-1)
				{
					Print_Matr(A,B);
					cout<<"System hasn't solution"<<endl;
					return -1;
				}
				else r-=er;
				k++;
				break;
			}
		}
		s++;
	}
	return r;
}

int Jordan_Gauss(vector< vector<simp_frac> > &A, vector<simp_frac> &B, vector<long long> setNum)
{
	bool flag;
	vector<simp_frac> swap;
	simp_frac temp_b;
	int er;
	long long n=A[0].size();
	long long r=setNum.size(),k,s;
	for(k=0;k<r;k++)
	{
		s=setNum[k];
		flag=false;
		for(long long i=k;i<B.size();i++)
		{
			if(A[i][s].num!=0)
			{
				flag=true;
				swap=A[i];
				A[i]=A[k];
				A[k]=swap;
				temp_b=B[i];
				B[i]=B[k];
				B[k]=temp_b;
				Calculate_Matr(A,B,k,s);
				break;
			}
		}
		if(!flag) return -1;
	}
	for(long long i=0;i<B.size();i++) if(B[i]<0) return -1;
	return 0;
}

int Find_Basic_Solution(vector< vector<simp_frac> > &A, vector<simp_frac> &B, vector<long long> &setNum, long long n)
{
	bool flag=false;
	int r,p;
	r=Jordan_Gauss(A,B);
	if(r==-1) return -1;
	for(int i=0;i<r;i++) setNum.push_back(i);
	p=r-1;
	while(p>=0)
	{
		if(Jordan_Gauss(A,B,setNum)!=-1) 
		{
			flag=true;
			break;
		}
		p=Next_SetNum(setNum,p,n);
	}
	if(Jordan_Gauss(A,B,setNum)!=-1) flag=true;
	if(!flag) 
	{
		cout<<"Опорных решений не существует"<<endl; 
		return -1;
	}
	cout<<"Матрица системы с опорным базисом"<<endl;
	Print_Matr(A,B);
	return r;
}

void Calculate_Simp_Table(vector< vector<simp_frac> > &A, vector<simp_frac> &B, vector<simp_frac> &Z,long long k, long long s)
{
	Calculate_Matr(A,B,k,s);
	simp_frac temp=Z[s];
	long long n=Z.size()-1;
	for(long long j=0;j<n;j++)
	{
		Z[j]=Z[j]-A[k][j]*temp;
	}
	Z[n]=Z[n]+B[k]*temp;
}

long long Find_Simp_Div(vector< vector<simp_frac> > A, vector<simp_frac> B, long long s)
{
	vector<long long> pot;
	for(long long i=0;i<B.size();i++)
	{
		if(A[i][s].num>0) 
		{
			if(pot.size()==0) pot.push_back(i);
			else if((B[i]/A[i][s])<(B[pot[0]]/A[pot[0]][s])) pot[0]=i;
		}
	}
	if(pot.size()==0) 
	{
		printf("System has infinity value;\n\n");
		return -1;
	}
	return pot[0];
}

vector<simp_frac> Create_Solution(vector<simp_frac> B, vector<long long> setNum, long long k, long long s, long long n)
{
	setNum[k]=s;
	vector<simp_frac> X=vector<simp_frac>(n);
	for(long long i=0;i<n;i++)
	{
		X[i]=simp_frac(0);
		if(Exists_Num(i,setNum))
		{
			for(long long j=0;j<setNum.size();j++)
			{
				if(setNum[j]==i) 
				{
					X[i]=B[j];
					break;
				}
			}
		}
	}
	return X;
}

vector<simp_frac> Diff_Solutions(vector<simp_frac> X, vector<simp_frac> Y)
{
	vector<simp_frac> Z=vector<simp_frac>(X.size());
	for(long long i=0;i<Z.size();i++) Z[i]=X[i]-Y[i];
	return Z;
}

void Print_Simp_Solution(vector<simp_frac> X[],long long n, simp_frac res)
{
	printf("Zmax=Z(");
	for(long long j=0;j<X[0].size();j++)
	{
		for(long long i=0;i<n;i++)
		{
			printf("(%lli/%lli)",X[i][j].num,X[i][j].den);
			for(long long k=i+1;k<n;k++)
			{
				printf("*m%lli",k);
			}
			if(i!=n-1) cout<<"+";
		}
		if(j!=X[0].size()-1) cout<<",";
	}
	printf(")=%lli/%lli\n\n",res.num,res.den);
}

void Simp_Table(vector< vector<simp_frac> > &A, vector<simp_frac> &B, vector<simp_frac> &Z, vector<long long> &setNum)
{
	Print_Simp_Table(A,B,Z,setNum);
	vector<long long> pot;
	vector<long long> copy_setNum;
	long long n=A[0].size();
	long long r=B.size(),k=0,s=0;
	vector<simp_frac> *X;
	bool flag_neg;
	int zero_count;
	while(true)
	{
		flag_neg=false;
		zero_count=0;
		pot.clear();
		for(long long j=0;j<n;j++)
		{
			if(Exists_Num(j,setNum)) continue;
			if(-Z[j].num<0)
			{
				if(flag_neg)
				{
					if(Z[pot[0]]<Z[j]) pot[0]=j;
				}
				else
				{
					pot.push_back(j);
					flag_neg=true;
				}
			}
			else if(Z[j].num==0) zero_count++;
		}
		if(flag_neg)
		{
			s=pot[0];
			k=Find_Simp_Div(A,B,s);
			if(k==-1) return;
			Calculate_Simp_Table(A,B,Z,k,s);
			setNum[k]=s;
			Print_Simp_Table(A,B,Z,setNum);
		}
		else
		{
			X=new vector<simp_frac>[zero_count+1];
			X[0]=Create_Solution(B,setNum,0,setNum[0],n);
			for(long long i=0;i<setNum.size();i++) copy_setNum.push_back(setNum[i]);
			long long count=1;
			for(long long j=0;j<n;j++)
			{
				if(!Exists_Num(j,copy_setNum) && Z[j].num==0)
				{
					k=Find_Simp_Div(A,B,j);
					Calculate_Simp_Table(A,B,Z,k,j);
					setNum[k]=j;
					Print_Simp_Table(A,B,Z,setNum);
					X[count]=Create_Solution(B,setNum,k,j,n);
					count++;
				}
			}
			if(count!=zero_count+1) printf("Something was wrong!\n");
			for(long long j=0;j<zero_count;j++) X[j]=Diff_Solutions(X[j],X[j+1]);
			Print_Simp_Solution(X,zero_count+1,Z[n]);
			break;
		}
	}
}

int main()
{
	system("chcp 1251>0");
	ifstream cin("InInfZ.txt");
	long long n,m,temp,r;
	char temp_c;
	vector<long long> setNum;
	vector<simp_frac> temp_v;
	vector< vector<simp_frac> > A;
	vector<simp_frac> B,Z;
	vector<char> Op;
	cin>>n>>m; 
	for(long long i=0;i<m;i++)
	{
		temp_v.clear();
		for(long long j=0;j<n;j++)
		{
			cin>>temp;
			temp_v.push_back(simp_frac(temp));
		}
		A.push_back(temp_v);
		cin>>temp_c;
		Op.push_back(temp_c);
		cin>>temp;
		B.push_back(simp_frac(temp));
	}	
	for(long long j=0;j<n;j++) 
	{
		cin>>temp;
		Z.push_back(simp_frac(temp));
	}
	for(long long k=0;k<m;k++)
	{
		if(Op[k]!='=')
		{
			for(long long i=0;i<m;i++)
			{
				if(i==k) continue;
				A[i].push_back(simp_frac(0));
			}
			if(Op[k]=='<') A[k].push_back(simp_frac(1));
			else A[k].push_back(simp_frac(-1));
			Z.push_back(simp_frac(0));
			n++;
		}
	}
	Z.push_back(simp_frac(0));
	printf("\nZ=(%lli/%lli)",Z[n].num,Z[n].den);
	for(long long i=0;i<n;i++)
	{
		if(Z[i].num!=0)
		{
			printf(" + (%lli/%lli)x%lli",Z[i].num,Z[i].den,i+1);
		}
	}
	cout<<" -> max"<<endl<<endl;
	
	Print_Matr(A,B);
	r=Find_Basic_Solution(A,B,setNum,n);
	if(r==-1) return 0;
	
	for(long long i=0;i<r;i++)
	{
		for(long long j=0;j<n;j++)
		{
			if(!Exists_Num(j,setNum))
			{
				Z[j]=Z[j]-Z[setNum[i]]*A[i][j];
			}
		}
		Z[n]=Z[n]+Z[setNum[i]]*B[i];
		Z[setNum[i]]=simp_frac(0);
	}
	
	printf("\nZ=(%lli/%lli)",Z[n].num,Z[n].den);
	for(long long i=0;i<n;i++)
	{
		if(!Exists_Num(i,setNum))
		{
			printf(" + (%lli/%lli)x%lli",Z[i].num,Z[i].den,i+1);
		}
	}
	cout<<";"<<endl<<endl;
	Print_Solution(A,B,setNum,n);
	cout<<endl;
	Simp_Table(A,B,Z,setNum);
	return 0;
}
