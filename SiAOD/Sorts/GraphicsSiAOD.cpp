#include<graphics.h>
int const X=600, Y=600,X0=X+X/12, Y0=Y/12,Xleft=X+X/36, Xright=2*X-X/18;
int const DifY=Y/18, FY=3*Y/10-5-DifY, Size=100, Del_Y=30;
int L2=1;
void InitWindow()
{
	initwindow(2*X,Y);
}
void InitCoordinates(int Del)
{
	int z,z2,l;
	char m1337[7];
	char *p;
	setfillstyle(1,0);
	bar(0,0,X,Y);
	setcolor(2);
	moveto(50,Y-50);
	lineto(50,50);
	lineto(45,55);
	line(50,50,55,55);
	moveto(50,Y-50);
	lineto(X-50,Y-50);
	lineto(X-55,Y-55);
	line(X-50,Y-50,X-55,Y-45);
	setfillstyle(1,2);
	settextstyle(3,0,2);
	fillellipse(50,Y-50,5,5);
	L2=(X-100)/(Del+1);
	for(z=1;z<=Del;z++)
	{
		moveto(L2*z+50,Y-60);
		lineto(L2*z+50,Y-40);
		p=itoa(z*100,m1337,10);
		outtextxy (z*L2+50,Y-40,m1337);
	}
	outtextxy(30,Y-40,"0");
	for(z=(Y-100)/Del_Y-1,z2=1;z>=1;z--,z2++)
	{
		moveto(40,75+z2*Del_Y);
		lineto(60,75+z2*Del_Y);
		p=itoa(z*Del_Y*Size,m1337,10);
		outtextxy (60,70+z2*Del_Y,m1337);
	}

	outtextxy(X-50,Y-40,"n");
	outtextxy(60,50,"M+C");
}
void GraphicT(int T[], int color)
{
	setcolor(color);
	setfillstyle(1,color);
	int z,x1=50,y1=Y-50;
	moveto(50,Y-50);
	for(z=0;z<=((X-100)/L2-2);z++)
	{
		y1=Y-50-T[z]/Size;
		x1+=L2;
		lineto(x1,y1);
		fillellipse(x1,y1,5,5);
	}
}
void TableT(int Z[], int N, int Del, int Rown, char text[])
{
	int z,DifX=X0+((Xright-X0)/Del)*(N-1)+5;
	char m1337[7];
	char *p;
	setcolor(2);
	outtextxy (X0+(N-1)*(Xright-X0)/Del+5, Y/9, text);
	for(z=0;z<Rown;z++)
	{
		p=itoa(Z[z],m1337,10);
		outtextxy (DifX,z*DifY+FY-10,m1337);
	}
}
void TableInit(int Del, int Rown)
{
	int Ydown=FY+Rown*DifY;
	char m1337[7];
	char *p;
	int z,per=13*Y/60,DifX=(Xright-X0)/Del;
	rectangle(Xleft-2,Y0-2,Xright+2,Ydown+2);
	rectangle (Xleft,Y0,Xright,Ydown);
	settextstyle(3,0,X/360);
	for(z=0;z<Del;z++)
	{
		line(X0+DifX*z,Y0,X0+DifX*z,Ydown);
	}
	for(z=0;z<Rown;z++)
	{
		line(Xleft,per,Xright,per);
		per+=DifY;
	}
	outtextxy (X+3*X/72+5, Y/9, "n");
	for(z=0;z<Rown;z++)
	{
		p=itoa((z+1)*100,m1337,10);
		outtextxy (Xleft+2, FY+z*DifY-10,m1337);
	}
}
void Getch()
{
	getch();
}
