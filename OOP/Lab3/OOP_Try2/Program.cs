/*
 * Created by SharpDevelop.
 * User: aleks
 * Date: 28.09.2021
 * Time: 22:19
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;
using System.Drawing;


class MyPoint
{
	string Name;
	double x;
	double y;
	double dx;
	double dy;
	int lim_x;
	int lim_y;
	int Repeat=0;
	public bool mode;
	public Color Color;
	
	public MyPoint(int lim_x, int lim_y, int i, Color col)
	{
		Random rnd = new Random(i);
		this.lim_x=lim_x;
		this.lim_y=lim_y;
		x=rnd.Next(lim_x);
		y=rnd.Next(lim_y);
		dx = 6*rnd.NextDouble()-3;
		dy = 6*rnd.NextDouble()-3;
		Color=col;
		mode=false;
	}
	
	private int Mantissa(int x)
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
	
	void Move(int i)
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
		if(mode)
		{
			Random rnd = new Random(i+Repeat);
			dx = 6*rnd.NextDouble()-3;
			dy = 6*rnd.NextDouble()-3;
			Repeat++;
		}
	}
	public void Draw(int i, SolidBrush br, Graphics g)
	{
		Move(i);
		g.FillEllipse(br,Get_X(),Get_Y(),8,8);
	}
}

class MyLabel:Label
{
	public MyLabel(int x, int y, int wight, int height):base()
	{
		BorderStyle=BorderStyle.Fixed3D;
		Font=new Font("Comic Sans MS",10, FontStyle.Bold);
		TextAlign=ContentAlignment.MiddleCenter;
		Bounds=new Rectangle(x,y,wight,height);
	}
	
	public MyLabel(int x, int y, int wight, int height, string txt):this(x,y,wight,height)
	{
		Text=txt;
	}
}

class MyTextBox:TextBox
{
	public MyTextBox(int x, int y, int wight, int height): base()
	{
		BorderStyle=BorderStyle.FixedSingle;
		Font=new Font("Comic Sans MS",10, FontStyle.Bold);
		Bounds=new Rectangle(x,y,wight,height);
	}
}

class MyTimer: Timer
{
	public MyTimer(int x): base()
	{
		Interval=x;
	}
}

class MyButton: Button
{
	public int Value;
	public MyButton(): base()
	{
		Value=0;
		Bounds=new Rectangle(200,620,100,30);
		Text="Продолжить";
	}
}

class MyForm:Form
{
	int obj_num=0;
	MyPoint[] A;
	public MyForm():base()
	{
		Width=525;
		Height=700;
		StartPosition=FormStartPosition.CenterScreen;
		FormBorderStyle=FormBorderStyle.FixedToolWindow;
		Text="Движение точек";

		Byte[] Argb= new byte[3];
		Random rnd=new Random();
		A=new MyPoint[100];
		string txt="Point_";
		for(int i=0;i<100;i++)
		{
			rnd.NextBytes(Argb);
			A[i]=new MyPoint(490,390,i,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			A[i].Name_Set(txt+i);
		}
		
		MyLabel lbl_Name=new MyLabel(5,5,500,30, A[obj_num].Name_Get());
		MyLabel lbl_Pos=new MyLabel(5,45,500,30, A[obj_num].Position_Get(2));
		MyLabel lbl_Speed=new MyLabel(5,85,500,30, A[obj_num].Speed_Get(2));
		MyLabel lbl_Obj_Set=new MyLabel(5,525,300,30,"Введите номер точки (от 0 до 99):");
		MyLabel lbl_Mode_Set=new MyLabel(5,565,300,30,"Введите способ движения (0 или 1):");
		MyTextBox Obj_Set=new MyTextBox(320,525,185,30);
		MyTextBox Mode_Set=new MyTextBox(320,565,185,30);
		Obj_Set.KeyUp+=(x,y)=>
		{
			try
			{
				obj_num=Int32.Parse(Obj_Set.Text);
				lbl_Name.Text=A[obj_num].Name_Get();
				lbl_Pos.Text=A[obj_num].Position_Get(2);
				lbl_Speed.Text=A[obj_num].Speed_Get(2);
			}
			catch
			{
				obj_num=0;
			}
		};
		Mode_Set.KeyUp+=(x,y)=>
		{
			try
			{
				if(Int32.Parse(Mode_Set.Text)==0)
				{
					for(int i=0;i<100;i++)
					{
						A[i].mode=false;
					}
				}
				else
				{
					for(int i=0;i<100;i++)
					{
						A[i].mode=true;
					}
				}
			}
			catch
			{
				for(int i=0;i<100;i++)
				{
					A[i].mode=false;
				}
			}
		};
		Panel pnl=new Panel();
		pnl.Bounds=new Rectangle(5,120,500,400);
		pnl.BorderStyle=BorderStyle.Fixed3D;
		PictureBox pb =new PictureBox();
		pb.Bounds=pnl.Bounds;
		Bitmap bmp =new Bitmap(pnl.Width,pnl.Height);
		SolidBrush br=new SolidBrush(Color.Red);
		Graphics g=Graphics.FromImage(bmp);
		for(int i=0;i<100;i++)
		{
			br.Color=A[i].Color;
			A[i].Draw(i,br,g);
		}
		MyTimer time=new MyTimer(25);
		time.Stop();
		time.Tick+=(x,y)=>
		{
			g.Clear(Color.White);
			lbl_Pos.Text=A[obj_num].Position_Get(2);
			if(A[obj_num].mode) lbl_Speed.Text=A[obj_num].Speed_Get(2);
			for(int i=0;i<100;i++)
			{
				br.Color=A[i].Color;
				A[i].Draw(i,br,g);
			}
			pb.Image=bmp;
		};
		MyButton btn=new MyButton();
		btn.Click+=(x,y)=>
		{
			if(btn.Value==0)
			{
				time.Start();
				btn.Value=1;
				btn.Text="Пауза";
			}
			else
			{
				time.Stop();
				btn.Value=0;
				btn.Text="Продолжить";
			}
		};
		Controls.Add(pb);
		Controls.Add(lbl_Name);
		Controls.Add(lbl_Pos);
		Controls.Add(lbl_Speed);
		Controls.Add(lbl_Obj_Set);
		Controls.Add(lbl_Mode_Set);
		Controls.Add(Obj_Set);
		Controls.Add(Mode_Set);
		Controls.Add(btn);
		this.Controls.Add(pnl);
	}
}

class Program
{
	[STAThread]
	public static void Main(string[] args)
	{
		MyForm app=new MyForm();
		Application.Run(app);
	}
}