/*
 * Created by SharpDevelop.
 * User: Alex
 * Date: 11.10.2021
 * Time: 20:18
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;

class MyPoint
{
	SolidBrush br = new SolidBrush(Color.Red);
	protected string Name;
	protected double x;
	protected double y;
	protected double dx;
	protected double dy;
	protected int lim_x;
	protected int lim_y;
	protected bool mode;
	protected int v=5;
	public Color Color;
	public bool Mode
	{
		get
		{
			return mode;
		}
		set
		{
			mode=value;
			if(value==false)
			{
				Random rnd = new Random((int)x);
				dx = 6*rnd.NextDouble()-3;
				dy = 6*rnd.NextDouble()-3;
			}
		}
	}
	
	public MyPoint(int lim_x, int lim_y, int i, Color col)
	{
		Random rnd = new Random(i);
		this.lim_x=lim_x;
		this.lim_y=lim_y;
		x=rnd.Next(lim_x);
		y=rnd.Next(lim_y);
		Mode=false;
		Color=col;
	}
	
	protected int Mantissa(int x)
	{
		int num=1;
		for(int i=0; i<x; i++)
		{
			num*=10;
		}
		return num;
	}
	
	public int Get_X()
	{
		return (int) x;
	}
	
	public int Get_Y()
	{
		return (int) y;
	}
	
	public void Name_Set(string txt)
	{
		Name=txt;
	}
	
	public string Name_Get()
	{
		return "Имя: "+Name;
	}
	
	public void Speed_Set(int dx, int dy)
	{
		this.dx=dx;
		this.dy=dy;
	}
	
	public string Speed_Get(int m)
	{
		int num=Mantissa(m);
		double dx_double=(int) (dx*num*40);
		dx_double=(double) dx_double/num;
		double dy_double=(int) (dy*num*40);
		dy_double=(double) dy_double/num;
		return "Скорость по x:  "+dx_double+"  Скорость по y:  "+dy_double;
	}
	
	public string Position_Get(int m)
	{
		int num=Mantissa(m);
		double x_double=(int) (x*num);
		x_double=(double) x_double/num;
		double y_double=(int) (y*num);
		y_double=(double) y_double/num;
		return "Координата по x:  "+x_double+"  Координата по y:"+y_double;
	}
	
	protected virtual void Move()
	{
		if(mode==false)
		{
			x+=dx;
			y+=dy;
			if(x>lim_x || x<0)
			{
				if(x>lim_x) x=lim_x-(x-lim_x);
				else x=-x;
				dx=-dx;
			}
			if(y>lim_y || y<0)
			{
				if(y>lim_y) y=lim_y-(y-lim_y);
				else y=-y;
				dy=-dy;
			}
		}
	}
	public virtual void Draw(Pen p, Graphics g)
	{
		Move();
		br.Color=p.Color;
		g.FillEllipse(br,Get_X(),Get_Y(),8,8);
	}
}

class MyLine: MyPoint
{
	protected int a;
	protected double x1;
	protected double y1;
	protected double x0;
	protected double y0;
	protected const int Max_Length=100;
	public MyLine(int lim_x, int lim_y, int i, Color col):base(lim_x,lim_y,i,col)
	{
		Random rnd = new Random(i+(int) x);
		x1=x+rnd.Next(20,Max_Length);
		if(x1>lim_x)
		{
			double dif_x=(x1-x);
			x-=dif_x;
			x1-=dif_x;
		}
		y1=y+rnd.Next(20,Max_Length);
		if(y1>lim_y)
		{
			double dif_y=(y1-y);
			y-=dif_y;
			y1-=dif_y;
		}
		a=0;
	}
	
	protected virtual void Set_Centre()
	{
		x0=(x+x1)/2;
		y0=(y+y1)/2;
	}
	
	protected override void Move()
	{
		if(mode==false)
		{
			x+=dx;
			y+=dy;
			x1+=dx;
			y1+=dy;
			if(x1>lim_x)
			{
				x1=lim_x-(x1-lim_x);
				x-=2*(lim_x-x1);
				dx=-dx;
			}
			else if(x<0)
			{
				x=-x;
				x1+=2*x;
				dx=-dx;
			}
			if(y1>lim_y)
			{
				y1=lim_y-(y1-lim_y);
				y-=2*(lim_y-y1);
				dy=-dy;
			}
			else if(y<0)
			{
				y=-y;
				y1+=2*y;
				dy=-dy;
			}
			Set_Centre();
		}
	}
	public override void Draw(Pen p, Graphics g)
	{
		Move();
		if(Mode) a=(a+v)%360;
		g.TranslateTransform((int)x0,(int)y0);
		g.RotateTransform(a);
		g.DrawLine(p,(float)(x-x0),(float)(y-y0),(float)(x1-x0),(float)(y1-y0));
		g.RotateTransform(-a);
		g.TranslateTransform((int)-x0,(int)-y0);
	}
}

class MyCircle: MyPoint
{
	protected double d1;
	protected double d2;
	protected const int Max_d=100;
	protected const int Min_d=20;
	public MyCircle(int lim_x, int lim_y, int i, Color col):base(lim_x+5,lim_y+5,i,col)
	{
		Random rnd = new Random(i);
		d1=rnd.Next(Min_d,Max_d);
		d2=d1;
	}
	protected override void Move()
	{
		if(mode==false)
		{
			x+=dx;
			y+=dy;
			if(x>(lim_x-d1) || x<0)
			{
				if(x>(lim_x-d1)) x=lim_x-d1-(x-(lim_x-d1));
				else x=-x;
				dx=-dx;
			}
			if(y>(lim_y-d2) || y<0)
			{
				if(y>(lim_y-d2)) y=lim_y-d2-(y-(lim_y-d2));
				else y=-y;
				dy=-dy;
			}
		}
	}
	public override void Draw(Pen p, Graphics g)
	{
		Move();
		g.DrawEllipse(p,Get_X(),Get_Y(),(float)d1,(float)d2);
	}
}

class MyEllipse: MyCircle
{
	protected int a;
	public MyEllipse(int lim_x, int lim_y, int i, Color col):base(lim_x+5,lim_y+5,i,col)
	{
		Random rnd = new Random(i+(int)d1);
		d2=rnd.Next(Min_d,Max_d);
		a=0;
	}
	public override void Draw(Pen p, Graphics g)
	{
		Move();
		if(Mode) a=(a+v)%360;
		g.TranslateTransform((int)(x+d1/2),(int)(y+d2/2));
		g.RotateTransform(a);
		g.DrawEllipse(p,(float)-(d1/2),(float)-(d2/2),(float)d1,(float)d2);
		g.RotateTransform(-a);
		g.TranslateTransform((int)-(x+d1/2),(int)-(y+d2/2));
	}
}

class MyTriangle: MyLine
{
	protected double x2;
	protected double y2;
	public MyTriangle(int lim_x, int lim_y, int i, Color col):base(lim_x,lim_y,i,col)
	{
		Random rnd = new Random(i+(int)x1);
		x2=x+rnd.Next(-Max_Length,Max_Length);
		if(x2<0) x2=x+(x-x2);
		else if(x2>lim_x) x2=x-(x2-x);
		y2=y+rnd.Next(-Max_Length,Max_Length);
		if(y2<0) y2=y+(y-y2);
		else if(y2>lim_y) y2=y-(y2-y);
		a=0;
	}
	
	protected override void Set_Centre()
	{
		//долгое, нудное нахождение центра окружности описанной около треугольника
		/*double A1=-(x-x1)/(y-y1);
		double A2=-(x-x2)/(y-y2);
		double B1=((x-x1)*(x+x1)/((y-y1)*2))-((y+y1)/2);
		double B2=((x-x2)*(x+x2)/((y-y2)*2))-((y+y2)/2);
		x0=(B2-B1)/(A1-A2);
		y0=A1*x0+B1;*/
		double A1=((y+y1)/2-y2)/((x+x1)/2-x2);
		double A2=((y+y2)/2-y1)/((x+x2)/2-x1);
		double B1=-A1*x2+y2;
		double B2=-A2*x1+y1;
		x0=(B2-B1)/(A1-A2);
		y0=A1*x0+B1;
	}
	
	protected override void Move()
	{
		if(mode==false)
		{
			x+=dx;
			y+=dy;
			x1+=dx;
			y1+=dy;
			x2+=dx;
			y2+=dy;
			if(x>lim_x || x<0)
			{
				if(x>lim_x)
				{
					x=lim_x-(x-lim_x);
					x1-=2*(lim_x-x);
					x2-=2*(lim_x-x);
				}
				else
				{
					x=-x;
					x1+=2*x;
					x2+=2*x;
				}
				dx=-dx;
			}
			if(y>lim_y || y<0)
			{
				if(y>lim_y)
				{
					y=lim_y-(y-lim_y);
					y1-=2*(lim_y-y);
					y2-=2*(lim_y-y);
				}
				else
				{
					y=-y;
					y1+=2*y;
					y2+=2*y;
				}
				dy=-dy;
			}
			if(x1>lim_x || x1<0)
			{
				if(x1>lim_x)
				{
					x1=lim_x-(x1-lim_x);
					x-=2*(lim_x-x1);
					x2-=2*(lim_x-x1);
				}
				else
				{
					x1=-x1;
					x+=2*x1;
					x2+=2*x1;
				}
				dx=-dx;
			}
			if(y1>lim_y || y1<0)
			{
				if(y1>lim_y)
				{
					y1=lim_y-(y1-lim_y);
					y-=2*(lim_y-y1);
					y2-=2*(lim_y-y1);
				}
				else
				{
					y1=-y1;
					y+=2*y1;
					y2+=2*y1;
				}
				dy=-dy;
			}
			if(x2>lim_x || x2<0)
			{
				if(x2>lim_x)
				{
					x2=lim_x-(x2-lim_x);
					x-=2*(lim_x-x2);
					x1-=2*(lim_x-x2);
				}
				else
				{
					x2=-x2;
					x+=2*x2;
					x1+=2*x2;
				}
				dx=-dx;
			}
			if(y2>lim_y || y2<0)
			{
				if(y2>lim_y)
				{
					y2=lim_y-(y2-lim_y);
					y-=2*(lim_y-y2);
					y1-=2*(lim_y-y2);
				}
				else
				{
					y2=-y2;
					y+=2*y2;
					y1+=2*y2;
				}
				dy=-dy;
			}
			Set_Centre();
		}
	}
	public override void Draw(Pen p, Graphics g)
	{
		Move();
		if(Mode) a=(a+v)%360;
		g.TranslateTransform((int)x0,(int)y0);
		g.RotateTransform(a);
		g.DrawLine(p,(float)(x-x0),(float)(y-y0),(float)(x1-x0),(float)(y1-y0));
		g.DrawLine(p,(float)(x-x0),(float)(y-y0),(float)(x2-x0),(float)(y2-y0));
		g.DrawLine(p,(float)(x1-x0),(float)(y1-y0),(float)(x2-x0),(float)(y2-y0));
		g.RotateTransform(-a);
		g.TranslateTransform((int)-x0,(int)-y0);
	}
}


class MyRectangle: MyLine
{
	double dif_x;
	double dif_y;
	
	public MyRectangle(int lim_x, int lim_y, int i, Color col):base(lim_x,lim_y,2*i+30,col)
	{
		dif_x=x1-x;
		dif_y=y1-y;
	}

	protected override void Move()
	{
		base.Move();
		dif_x=x1-x;
		dif_y=y1-y;
	}
	
	public override void Draw( Pen p, Graphics g)
	{
		Move();
		if(Mode) a=(a+v)%360;
		g.TranslateTransform((int)x0,(int)y0);
		g.RotateTransform(a);
		g.DrawRectangle(p,(float)(-dif_x/2),(float)(-dif_y/2),(float)(dif_x),(float)(dif_y));
		g.RotateTransform(-a);
		g.TranslateTransform((int)-x0,(int)-y0);
	}
}

class MyRhombus: MyLine
{
	double x2;
	double y2;
	double x3;
	double y3;
	double dif_x;
	double dif_y;
	
	public MyRhombus(int lim_x, int lim_y, int i, Color col):base(lim_x,lim_y,10*i+100,col)
	{
		dif_x=x1-x;
		dif_y=y1-y;
		x2=x1+dif_x;
		if(x2>lim_x)
		{
			x-=dif_x;
			x1-=dif_x;
			x2-=dif_x;
		}
		y2=y;
		x3=x1;
		y3=y-dif_y;
		if(y3<0)
		{
			y+=dif_y;
			y1+=dif_y;
			y2+=y;
			y3+=dif_y;
		}
	}
	
	protected override void Set_Centre()
	{
		x0=x1;
		y0=y;
	}
	
	protected override void Move()
	{
		if(mode==false)
		{
			x+=dx;
			y+=dy;
			x1+=dx;
			y1+=dy;
			x2+=dx;
			y2+=dy;
			x3+=dx;
			y3+=dy;
			if(x2>lim_x)
			{
				x2=lim_x-(x2-lim_x);
				x-=2*(lim_x-x2);
				x1-=2*(lim_x-x2);
				x3=x1;
				dx=-dx;
			}
			else if(x<0)
			{
				x=-x;
				x1+=2*x;
				x2+=2*x;
				x3=x1;
				dx=-dx;
			}
			if(y1>lim_y)
			{
				y1=lim_y-(y1-lim_y);
				y-=2*(lim_y-y1);
				y2=y;
				y3-=2*(lim_y-y1);
				dy=-dy;
			}
			else if(y3<0)
			{
				y3=-y3;
				y+=2*y3;
				y1+=2*y3;
				y2=y;
				dy=-dy;
			}
			Set_Centre();
		}
	}
	
	public override void Draw(Pen p, Graphics g)
	{
		Move();
		if(Mode) a=(a+v)%360;
		g.TranslateTransform((int)x0,(int)y0);
		g.RotateTransform(a);
		g.DrawLine(p,(float)-dif_x,(float)0,(float)0,(float)dif_y);
		g.DrawLine(p,(float)0,(float)dif_y,(float)dif_x,(float)0);
		g.DrawLine(p,(float)dif_x,(float)0,(float)0,(float)-dif_y);
		g.DrawLine(p,(float)0,(float)-dif_y,(float)-dif_x,(float)0);
		g.RotateTransform(-a);
		g.TranslateTransform((int)-x0,(int)-y0);
	}
}
