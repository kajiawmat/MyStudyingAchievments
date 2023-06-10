/*
 * Created by SharpDevelop.
 * User: Alex
 * Date: 30.10.2021
 * Time: 23:36
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;
using System.Drawing;

class Text_Label: Label
{
	public Text_Label(Rectangle Bounds): base()
	{
		this.Bounds=Bounds;
		//BackColor=Color.Aquamarine;
		TextAlign=ContentAlignment.MiddleCenter;
		Font=new Font("Monotype Corsiva",40,FontStyle.Regular);
		ForeColor=Color.Purple;
		Text="";
	}
	public Text_Label(Rectangle Bounds, string txt): this(Bounds)
	{
		Text=txt;
	}
}

class Info_Label: Label
{
	public Info_Label(Rectangle Bounds,int i): base()
	{
		this.Bounds=Bounds;
		BackColor=Color.Black;
		TextAlign=ContentAlignment.MiddleCenter;
		Font=new Font("Monotype Corsiva",40,FontStyle.Bold);
		ForeColor=Color.Blue;
		Text=""+i;
	}
}

class Change_Panel: Panel
{
	public int value;
	public Change_Panel(Rectangle Bounds, string txt, int val, int min, int max)
	{
		this.Bounds=Bounds;
		value=val;
		Text_Label Value_Text=new Text_Label(new Rectangle(0,0,Width,50));
		Value_Text.Text=txt;
		Info_Label Value_Num=new Info_Label(new Rectangle(50,50,Width-100,Height-50),value);
		Button Value_Down=new Button();
		Value_Down.Image=Image.FromFile("Left.png");
		Value_Down.Bounds=new Rectangle(0,Height/2-25,50,100);
		Value_Down.Click+=(x,y)=>
		{
			if(value>min) value--;
			Value_Num.Text=""+value;
		};
		Button Value_Up=new Button();
		Value_Up.Image=Image.FromFile("Right.png");
		Value_Up.Bounds=new Rectangle(Width-50,Height/2-25,50,100);
		Value_Up.Click+=(x,y)=>
		{
			if(value<max) value++;
			Value_Num.Text=""+value;
		};
		Controls.Add(Value_Text);
		Controls.Add(Value_Num);
		Controls.Add(Value_Down);
		Controls.Add(Value_Up);
	}
}

class Form_Settings: Form
{
	public int Speed;
	public int Level;
	public Form_Settings(int s, int l, int Rows)
	{
		Speed=s;
		Level=l;
		Height=300;
		Width=830;
		StartPosition=FormStartPosition.CenterScreen;
		FormBorderStyle=FormBorderStyle.Fixed3D;
		Text="Настройки игры";
		Button Continue = new Button();
		Continue.Bounds=new Rectangle(325,125,150,50);
		Continue.Text="Продолжить";
		Continue.Font=new Font("Comic Sans MS",15,FontStyle.Regular);
		Change_Panel Speed_Panel= new Change_Panel(new Rectangle(50,25,250,225),"Скорость",Speed,0,15);
		Change_Panel Level_Panel= new Change_Panel(new Rectangle(500,25,250,225),"Уровень",Level,0,Rows/2);
		Continue.Click+=(x,y)=>
		{
			Speed=Speed_Panel.value;
			Level=Level_Panel.value;
			Close();
		};
		Controls.Add(Continue);
		Controls.Add(Speed_Panel);
		Controls.Add(Level_Panel);
	}
}

class MyForm: Form
{
	int interval;
	const int Size=30;
	const int Rows=20;
	const int Cols=12;
	Field game;
	PictureBox field;
	Timer game_timer;
	Bitmap frame;
	Graphics g;
	PictureBox Next_Tetra;
	Bitmap bmp_Next;
	Graphics g_Next;
	SolidBrush br;
	Pen p;
	int Level=0;
	int Speed=0;
	public void Draw()
	{
		g.Clear(Color.White);
		game.Draw_Frame(frame,g,br,p,Size);
		game.Figure.Draw_Tetramino(g,br,Size);
		field.Image=frame;
	}
	public void Set_Settings(Form_Settings settings)
	{
		settings.ShowDialog();
		Speed=settings.Speed;
		Level=settings.Level;
	}
	public MyForm(): base()
	{
		Form_Settings settings=new Form_Settings(Speed,Level,Rows);
		Set_Settings(settings);
		Text="Тетрис";
		Width=50+Size*Cols+400;
		Height=50+Size*Rows+100;
		FormBorderStyle=FormBorderStyle.Fixed3D;
		StartPosition=FormStartPosition.CenterScreen;
		BackColor=Color.Aquamarine;
		interval=400;
		Next_Tetra=new PictureBox();
		Next_Tetra.Bounds=new Rectangle(Width-300,25,200,150);
		Next_Tetra.BackColor=Color.Black;
		bmp_Next=new Bitmap(Next_Tetra.Width,Next_Tetra.Height);
		g_Next=Graphics.FromImage(bmp_Next);
		g_Next.TranslateTransform(-3*Size,Next_Tetra.Height/2-Size);
		Text_Label lbl_1=new Text_Label(new Rectangle(Width-400,200,400,50),"Текущий Счёт");
		Text_Label lbl_2=new Text_Label(new Rectangle(Width-400,350,400,50),"Уровень");
		Text_Label lbl_3=new Text_Label(new Rectangle(Width-400,500,400,50),"Скорость");
		Info_Label lbl_Score = new Info_Label(new Rectangle(Width-300,250,200,100),0);
		Info_Label lbl_Level = new Info_Label(new Rectangle(Width-300,400,200,100),Level);
		Info_Label lbl_Speed = new Info_Label(new Rectangle(Width-300,550,200,100),Speed);
		field=new PictureBox();
		field.Bounds=new Rectangle(50,50,Size*Cols,Size*Rows);
		frame= new Bitmap(field.Width,field.Height);
		g=Graphics.FromImage(frame);
		br=new SolidBrush(Color.Red);
		p=new Pen(Color.White,2);
		game = new Field(Cols,Rows,Level);
		Draw();
		game.Figure_Next.Draw_Tetramino(g_Next,br,Size);
		Next_Tetra.Image=bmp_Next;
		game_timer=new Timer();
		game_timer.Interval=interval-20*Speed;
		game_timer.Tick+=(x,y)=>
		{
			if(game.Figure.Move(game)==1)
			{
				if(game.Change_Figure()==1) Game_Over_Screen();
				lbl_Score.Text=""+game.score;
				int temp=Speed+game.score/1000;
				temp=temp>15?15:temp;
				game_timer.Interval=interval-20*temp;
				lbl_Speed.Text=""+temp;
				g_Next.Clear(Color.Black);
				game.Figure_Next.Draw_Tetramino(g_Next,br,Size);
				Next_Tetra.Image=bmp_Next;
			}
			Draw();
		};
		KeyDown+=(x,e)=>
		{
			if(game_timer.Enabled)
			{
				switch(e.KeyCode)
				{
					case Keys.Left:
					case Keys.A:
						{
							game.Figure.Move_Hor(game,-1);
							Draw();
							break;
						}
					case Keys.Right:
					case Keys.D:
						{
							game.Figure.Move_Hor(game,1);
							Draw();
							break;
						}
					case Keys.Q:
					case Keys.W:
					case Keys.Up:
						{
							game.Figure.Rotate(game);
							Draw();
							break;
						}
					case Keys.E:
					case Keys.S:
					case Keys.Down:
						{
							game_timer.Interval=50;
							break;
						}
				}
			}
			if(e.KeyCode==Keys.R)
			{
				game = new Field(Cols,Rows,Level);
				game.Figure_Next.Draw_Tetramino(g_Next,br,Size);
				game_timer.Enabled=true;
			}
			if(e.KeyCode==Keys.P)
			{
				game_timer.Enabled=false;
				Set_Settings(settings);
				game_timer.Enabled=true;
			}
			if(e.KeyCode==Keys.Escape)
			{
				Application.Exit();
			}
		};
		KeyUp+=(x,e)=>
		{
			if(e.KeyCode==Keys.S || e.KeyCode==Keys.E || e.KeyCode==Keys.Down)
			{
				int temp=Speed+game.score/1000;
				temp=temp>15?15:temp;
				game_timer.Interval=interval-20*temp;
			}
		};
		Controls.Add(field);
		Controls.Add(lbl_1);
		Controls.Add(lbl_2);
		Controls.Add(lbl_3);
		Controls.Add(lbl_Level);
		Controls.Add(lbl_Score);
		Controls.Add(lbl_Speed);
		Controls.Add(Next_Tetra);
		game_timer.Start();
	}
	
	void Game_Over_Screen()
	{
		game_timer.Enabled=false;
	}
}

class Program
{
	public static void Main(string[] args)
	{
		Application.Run(new MyForm());
	}
}