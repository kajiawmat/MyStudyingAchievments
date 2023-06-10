#include "RepositoriySiAOD.cpp"
int const N=5;
int main(int argc, char*argv[])
{
	int Index[N+1],Reserv[N+1],m,R;
	struct CellPhone Cell[N+1];
	char Last[20], First[20];
	FILE *f1, *f2;
	f1=fopen("C:\\Users\\Alex\\Desktop\\FileSpisok\\SpisokCout8.txt","r");
	f2=fopen("C:\\Users\\Alex\\Desktop\\FileSpisok\\SortSpisokCout8.txt","w");
	if(f1==NULL || f2==NULL)
	{
		printf("Error open file ");
		exit(1);
	}
	system("chcp 1251>nul");
	for(m=1;m<=N;m++)
	{
		fscanf(f1,"%s%s%s%s",Cell[m].lastname,Cell[m].name,Cell[m].phone,Cell[m].address);
		Index[m]=m;
		Reserv[m]=m;
	}
	PrintAllCell(Cell,N);
	PrintAllIndex(Cell,Index,N);
	ShellSortModStruct(Cell,Index,N);
	PrintAllCell(Cell,N);
	PrintAllIndex(Cell,Index,N);
	fprintf(f2,"Мы получили отсортированный массив структур\n\n");
	for(m=1;m<=N;m++)
	{
		fprintf(f2,"%22s%22s%17s%32s\n",Cell[Index[m]].lastname,Cell[Index[m]].name,Cell[Index[m]].phone,Cell[Index[m]].address);
	}
	
	printf("Please input lastname and name for binar search\n");
	scanf("%s",Last);
	scanf("%s",First);
	R=BSearch2Cell(Cell,Index,N,Last,First);
	fprintf(f2,"\n\nСтруктура с фамилией %s и именем %s ...   ",Last,First);
	if(R)
	{
		PrintCell(Cell[R]);
		fprintf(f2,"Найдена!!!\n\n%22s%22s%17s%32s\n",Cell[R].lastname,Cell[R].name,Cell[R].phone,Cell[R].address);
	}
	else
	{
		printf("не найдена");
		fprintf(f2,"Не найдена!!!");
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
