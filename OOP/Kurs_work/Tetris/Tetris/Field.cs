/*
 * Created by SharpDevelop.
 * User: Alex
 * Date: 01.11.2021
 * Time: 13:23
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;

class Field
{
	public int score;
	int width;
	int height;
	bool[,] values;
	Color[,] Colors;
	public Tetramino Figure;
	public Tetramino Figure_Next;
	public Field(int Cols, int Rows, int Level)
	{
		score=0;
		width=Cols;
		height=Rows;
		values=new bool[width,height];
		Colors=new Color[width,height];
		Fill_Matrix(Level);
		Figure=Create_Tetramino();
		Figure_Next=Create_Tetramino();
	}
	void Fill_Matrix(int Level)
	{
		for(int j=0;j<values.GetLength(1)-Level;j++)
		{
			for(int i=0;i<values.GetLength(0);i++)
			{
				values[i,j]=false;
				Colors[i,j]=Color.Black;
			}
		}
		Random rnd=new Random(DateTime.Now.Millisecond);
		for(int j=values.GetLength(1)-Level;j<values.GetLength(1);j++)
		{
			for(int i=0;i<values.GetLength(0);i++)
			{
				values[i,j]=true;
				Colors[i,j]=Color.Gray;
			}
			for(int k=0;k<3;k++)
			{
				int i=rnd.Next(0,values.GetLength(0));
				values[i,j]=false;
				Colors[i,j]=Color.Black;
			}
		}
	}
	Tetramino Create_Tetramino()
	{
		Tetramino fig;
		Random rnd=new Random(DateTime.Now.Millisecond*DateTime.Now.Second);
		switch(rnd.Next(7))
		{
			case 0:
				{
					fig=new O_Tetramino(width/2,0);
					break;
				}
			case 1:
				{
					fig=new I_Tetramino(width/2,0);
					break;
				}
			case 2:
				{
					fig=new S_Tetramino(width/2,0);
					break;
				}
			case 3:
				{
					fig=new Z_Tetramino(width/2,0);
					break;
				}
			case 4:
				{
					fig=new L_Tetramino(width/2,0);
					break;
				}
			case 5:
				{
					fig=new J_Tetramino(width/2,0);
					break;
				}
			default:
				{
					fig=new T_Tetramino(width/2,0);
					break;
				}
		}
		return fig;
	}
	public bool CheckValue(int x, int y)
	{
		if(x<0 || x>=width) return true;
		if(y<0 ||  y>=height) return true;
		if(values[x,y]) return true;
		return false;
	}
	public void Draw_Frame(Bitmap frame, Graphics g, SolidBrush br, Pen p, int Size)
	{
		for(int k=0;k<=height;k++)
		{
			g.DrawLine(p,0,k*Size,frame.Width,k*Size);
		}
		for(int k=0;k<=width;k++)
		{
			g.DrawLine(p,k*Size,0,k*Size,frame.Height);
		}
		for(int i=0;i<width;i++)
		{
			for(int j=0;j<height;j++)
			{
				br.Color=Colors[i,j];
				g.FillRectangle(br,i*Size+2,j*Size+2,Size-4,Size-4);
			}
		}
	}
	
	public int Change_Figure()
	{
		Color temp=Figure.Get_Color();
		int i,j;
		for(int k=0;k<Figure.blocks.Length;k++)
		{
			i=Figure.blocks[k].Get_X();
			j=Figure.blocks[k].Get_Y();
			Colors[i,j]=temp;
			values[i,j]=true;
		}
		Check_Line();
		Figure=Figure_Next;
		Figure_Next=Create_Tetramino();
		for(int k=0;k<Figure.blocks.Length;k++)
		{
			i=Figure.blocks[k].Get_X();
			j=Figure.blocks[k].Get_Y();
			if(CheckValue(i,j)) return 1;
		}
		return 0;
	}
	
	void Down_Values(int y_line)
	{
		bool empty;
		for(int j=y_line;j>0;j--)
		{
			empty=true;
			for(int i=0;i<width;i++)
			{
				if(values[i,j-1]) empty=false;
				values[i,j]=values[i,j-1];
				Colors[i,j]=Colors[i,j-1];
			}
			if(empty) break;
		}
	}
	
	void Check_Line()
	{
		int factor=1;
		int y_min=height, y_max=0;
		int y_temp;
		for(int k=0;k<Figure.blocks.Length;k++)
		{
			y_temp=Figure.blocks[k].Get_Y();
			if(y_temp>y_max) y_max=y_temp;
			if(y_temp<y_min) y_min=y_temp;
		}
		bool full;
		for(int j=y_min;j<=y_max;j++)
		{
			full=true;
			for(int i=0;i<width;i++)
			{
				if(values[i,j]==false) full=false;
			}
			if(full) 
			{
				Down_Values(j);
				score+=100*factor;
				factor++;
			}
		}
	}
}
