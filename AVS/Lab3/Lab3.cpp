#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<fstream>
#include<time.h>

using namespace std;

string FilepathROM="Lab3.txt";
string FilepathFlash="D:\\Lab3.txt";

const long long MIN = 10000, MAX = 20000;

int Start_Rows;
int Rows=1;

string MemoryType="RAM";
long long BlockSize=1024;
string ElementType="double";
long long BufferSize=sizeof(double);
long long LaunchNum=10;
string Timer="Clock";

void Set_Rows()
{
	FILE* fp=fopen("Lab3.csv","r");
	if(fp==NULL)
	{
		fp=fopen("Lab3.csv","w");
		fprintf(fp,"MemoryType;BlockSize;ElementType;BufferSize;LaunchNum;Timer;WriteTime;AverageWriteTime;WriteBandWidth;AbsError(write);RelError(write);ReadTime;AverageReadTime;ReadBandwidth;AbsError(read);RelError;\n");
		fclose(fp);
		fp=fopen("Lab3.csv","r");	
	}
	string temp;
	while(getline(fp,temp)) 
	{
		Rows++;
	}
	fclose(fp);
	Start_Rows=Rows;
}

void Set_Parameters(int argc, char* argv[])
{
	int flag=0;
	for(int i=1;i<argc;i++)
	{
		if(flag==1) 
		{
			if(strcmp(argv[i],"RAM")==0) MemoryType="RAM";
			else if(strcmp(argv[i],"SSD")==0) MemoryType="SSD";
			else if(strcmp(argv[i],"HDD")==0) MemoryType="HDD";
			else if(strcmp(argv[i],"flash")==0) MemoryType="flash";
			else {cout<<"Wrong Input parameters"; exit(-1);}
			flag=0;
		}
		else if(flag==2) 
		{
			BlockSize=0;
			for(int j=0;argv[i][j]!='\0';j++)
			{
				if(argv[i][j]>='0' && argv[i][j]<='9') BlockSize=BlockSize*10+(argv[i][j]-'0');
				else if (argv[i][j]=='K') {BlockSize*=1024; break;}
				else if (argv[i][j]=='M') {BlockSize*=1024*1024; break;}
				else {cout<<"Wrong Input parameters"; exit(-1);}
			}
			flag=0;
		}
		else if(flag==3) 
		{
			LaunchNum=0;
			for(int j=0;argv[i][j]!='\0';j++)
			{
				if(argv[i][j]>='0' && argv[i][j]<='9') LaunchNum=LaunchNum*10+(argv[i][j]-'0');
				else {cout<<"Wrong Input parameters"; exit(-1);}
			}
			flag=0;
		}
		else if(strcmp(argv[i],"--memory-type")==0 || strcmp(argv[i],"-m")==0) flag=1;
		else if(strcmp(argv[i],"--block-size")==0 || strcmp(argv[i],"-b")==0) flag=2;
		else if(strcmp(argv[i],"--launch-count")==0 || strcmp(argv[i],"-l")==0) flag=3;
		else {cout<<"Wrong Input parameters"; exit(-1);}
	}
}

string DToS(string str)
{
	for (long long i = 0; i < str.length(); i++) if (str[i] == '.') str[i] = ',';
	return str;
}

void FillTable(double TW[],double AVW, double TR[], double AVR)
{
	string tw,tr,avw=DToS(to_string(AVW)),avr=DToS(to_string(AVR));
	FILE* csw=fopen("Lab3.csv","a");
	for(long long i=0;i<LaunchNum;i++)
	{
		fprintf(csw,"%s;",MemoryType);
		fprintf(csw,"%lli;",BlockSize);
		fprintf(csw,"%s;",ElementType);
		fprintf(csw,"%lli;",BufferSize);
		fprintf(csw,"%lli;",i);
		fprintf(csw,"%s;",Timer);
		tw=DToS(to_string(TW[i]));
		fprintf(csw,"%s;",tw);
		fprintf(csw,"%s;",avw);
		fprintf(csw,"=(B%i/H%i)*1000000;",Rows,Rows);
		fprintf(csw,"=ABS(G%i-H%i);",Rows,Rows);
		fprintf(csw,"=J%i/H%i",Rows,Rows);
		tr=DToS(to_string(TR[i]));
		fprintf(csw,"%s;",tw);
		fprintf(csw,"%s;",avw);
		fprintf(csw,"=(B%i/N%i)*1000000;",Rows,Rows);
		fprintf(csw,"=ABS(M%i-N%i);",Rows,Rows);
		fprintf(csw,"=P%i/N%i",Rows,Rows);
		Rows++;
	}
	
}

void Random_Value(double& val)
{
	val = rand() * (double)(MAX - MIN) / RAND_MAX + MIN;
}

void LaunchRAM()
{
	struct timespec start,end;
	double *RAM_Array,*Array_val,*Array_val2;
	double *Time_Array,*Time_Array2;
	double Average_Time_Array,Average_Time_Array2;
	const long long N=(BlockSize/BufferSize);
	Time_Array=new double[LaunchNum];
	Time_Array2=new double[LaunchNum];
	for(int j=0;j<=LaunchNum;j++)
	{
		Array_val2=new double[N];
		Array_val=new double[N];
		for(long long i=0;i<N;i++) Random_Value(Array_val[i]);
		RAM_Array=new double[N];
		clock_gettime (CLOCK_REALTIME, &start);
		for(long long i=0;i<N;i++) RAM_Array[i]=Array_val[i];
		clock_gettime (CLOCK_REALTIME, &end);
		Time_Array[j]=(end.tv_sec-start.)(double)(end.tv_nsec-start.tv_nsec)/1000000000;
		clock_gettime (CLOCK_REALTIME, &start);
		for(long long i=0;i<N;i++) Array_val2[i]=RAM_Array[i];
		clock_gettime (CLOCK_REALTIME, &end);
		Time_Array2[j]=(end.tv_sec-start.)(double)(end.tv_nsec-start.tv_nsec)/1000000000;
		Average_Time_Array+=Time_Array[j];
		Average_Time_Array2+=Time_Array2[j];
		delete []Array_val;
		delete []Array_val2;
		delete []RAM_Array;
	}
	Average_Time_Array-=Time_Array[0];
	Average_Time_Array/=LaunchNum;
	Average_Time_Array2-=Time_Array2[0];
	Average_Time_Array2/=LaunchNum;
	FillTable(Time_Array,Average_Time_Array,Time_Array2,Average_Time_Array2);
}

void LaunchROM(string filepath)
{
	const num_el=BufferSize/sizeof(double);
	struct timespec start,end;
	double *Array_val,*Array_val2;
	double *Time_Array,*Time_Array2;
	double Average_Time_Array,Average_Time_Array2;
	const long long N=(BlockSize/BufferSize);
	Time_Array=new double[LaunchNum];
	Time_Array2=new double[LaunchNum];
	for(int j=0;j<=LaunchNum;j++)
	{
		Array_val2=new double[N];
		Array_val=new double[N];
		for(long long i=0;i<N;i++) Random_Value(Array_val[i]);
		FILE *fw=fopen(filepath,"w");
		clock_gettime (CLOCK_REALTIME, &start);
		for(long long i=0;i<N;i++) fwrite(Array_val+i*num_el,sizeof(double),num_el,fp);
		clock_gettime (CLOCK_REALTIME, &end);
		Time_Array[j]=(end.tv_sec-start.)(double)(end.tv_nsec-start.tv_nsec)/1000000000;
		fclose(fw);
		FILE *fr=fopen(filepath,"r");
		clock_gettime (CLOCK_REALTIME, &start);
		for(long long i=0;i<N;i++) fread(Array_val2+i*num_el,sizeof(double),num_el,fp);
		clock_gettime (CLOCK_REALTIME, &end);
		Time_Array2[j]=(end.tv_sec-start.)(double)(end.tv_nsec-start.tv_nsec)/1000000000;
		fclose(fr);
		Average_Time_Array+=Time_Array[j];
		Average_Time_Array2+=Time_Array2[j];
		delete []Array_val;
		delete []Array_val2;
	}
	Average_Time_Array-=Time_Array[0];
	Average_Time_Array/=LaunchNum;
	Average_Time_Array2-=Time_Array2[0];
	Average_Time_Array2/=LaunchNum;
	FillTable(Time_Array,Average_Time_Array,Time_Array2,Average_Time_Array2);
}

int main(int argc, char* argv[])
{
	Set_Parameters(argc,argv);
	Set_Rows();
	if(MemoryType=="RAM") LaunchRAM();
	else if(MemoryType=="HDD" || MemoryType=="SSD") LaunchROM(FilepathROM);
	else if(MemoryType=="flash") LaunchROM(FilepathFlash);
	return 0;
}
