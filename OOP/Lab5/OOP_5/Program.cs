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
	const int N=5;
	int obj_num=0;
	MyPoint[] A;
	MyLine[] B;
	MyCircle[] C;
	MyEllipse[] D;
	MyTriangle[] E;
	MyRectangle[] F;
	MyRhombus[] G;
	public MyForm():base()
	{
		Width=525;
		Height=700;
		StartPosition=FormStartPosition.CenterScreen;
		FormBorderStyle=FormBorderStyle.FixedToolWindow;
		Text="Движение точек";

		Byte[] Argb= new byte[3];
		Random rnd=new Random();
		A=new MyPoint[N];
		B=new MyLine[N];
		C=new MyCircle[N];
		D=new MyEllipse[N];
		E=new MyTriangle[N];
		F=new MyRectangle[N];
		G=new MyRhombus[N];
		string txtA="Point_";
		string txtB="Line_";
		for(int i=0;i<N;i++)
		{
			rnd.NextBytes(Argb);
			A[i]=new MyPoint(490,390,i,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			A[i].Name_Set(txtA+i);
			rnd.NextBytes(Argb);
			B[i]=new MyLine(490,390,i+100,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			B[i].Name_Set(txtB+i);
			rnd.NextBytes(Argb);
			C[i]=new MyCircle(490,390,i+200,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			C[i].Name_Set(txtB+i);
			rnd.NextBytes(Argb);
			D[i]=new MyEllipse(490,390,i+200,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			D[i].Name_Set(txtB+i);
			rnd.NextBytes(Argb);
			E[i]=new MyTriangle(490,390,i+200,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			E[i].Name_Set(txtB+i);
			rnd.NextBytes(Argb);
			F[i]=new MyRectangle(490,390,i+200,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			F[i].Name_Set(txtB+i);
			rnd.NextBytes(Argb);
			G[i]=new MyRhombus(490,390,i+200,Color.FromArgb(Argb[0],Argb[1],Argb[2]));
			G[i].Name_Set(txtB+i);
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
					for(int i=0;i<N;i++)
					{
						A[i].Mode=false;
						B[i].Mode=false;
						C[i].Mode=false;
						D[i].Mode=false;
						E[i].Mode=false;
						F[i].Mode=false;
						G[i].Mode=false;
					}
				}
				else
				{
					for(int i=0;i<N;i++)
					{
						A[i].Mode=true;
						B[i].Mode=true;
						C[i].Mode=true;
						D[i].Mode=true;
						E[i].Mode=true;
						F[i].Mode=true;
						G[i].Mode=true;
					}
				}
			}
			catch
			{
				for(int i=0;i<N;i++)
				{
					A[i].Mode=false;
					B[i].Mode=false;
					C[i].Mode=false;
					D[i].Mode=false;
					E[i].Mode=false;
					F[i].Mode=false;
					G[i].Mode=false;
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
		Pen p=new Pen(Color.Red,5);
		for(int i=0;i<N;i++)
		{
			br.Color=A[i].Color;
			A[i].Draw(br,g);
			p.Color=B[i].Color;
			B[i].Draw(p,g);
			p.Color=C[i].Color;
			C[i].Draw(p,g);
			p.Color=D[i].Color;
			D[i].Draw(p,g);
			p.Color=E[i].Color;
			E[i].Draw(p,g);
			p.Color=F[i].Color;
			F[i].Draw(p,g);
			p.Color=G[i].Color;
			G[i].Draw(p,g);
		}
		MyTimer time=new MyTimer(25);
		time.Stop();
		time.Tick+=(x,y)=>
		{
			//pnl.Hide();
			g.Clear(Color.White);
			lbl_Pos.Text=A[obj_num].Position_Get(2);
			if(A[obj_num].Mode) lbl_Speed.Text=A[obj_num].Speed_Get(2);
			for(int i=0;i<N;i++)
			{
				br.Color=A[i].Color;
				A[i].Draw(br,g);
				p.Color=B[i].Color;
				B[i].Draw(p,g);
				p.Color=C[i].Color;
				C[i].Draw(p,g);
				p.Color=D[i].Color;
				D[i].Draw(p,g);
				p.Color=E[i].Color;
				E[i].Draw(p,g);
				p.Color=F[i].Color;
				F[i].Draw(p,g);
				p.Color=G[i].Color;
				G[i].Draw(p,g);
			}
			pb.Image=bmp;
			//pnl.Show();
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
		Console.WriteLine(Math.Cos(Math.PI));
		MyForm app=new MyForm();
		Application.Run(app);
	}
}