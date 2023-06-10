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

class Block
{
	int pos_x;
	int pos_y;
	public Block(int x=0,int y=0)
	{
		pos_x=x;
		pos_y=y;
	}
	
	public void Move()
	{
		pos_y++;
	}
	
	public void Move_Hor(int dir)
	{
		pos_x+=dir;
	}
	
	public void Set_Position(int x, int y)
	{
		pos_x=x;
		pos_y=y;
	}
	
	public int Get_X()
	{
		return pos_x;
	}
	
	public int Get_Y()
	{
		return pos_y;
	}
	
}

abstract class Tetramino
{
	public Block[] blocks;
	protected int pos_x0;
	protected int pos_y0;
	protected Color Block_Color;
	public Tetramino(int pos_x0, int pos_y0)
	{
		blocks=new Block[4];
		this.pos_x0=pos_x0;
		this.pos_y0=pos_y0;
	}
	
	public Color Get_Color()
	{
		return Block_Color;
	}
	
	public int Move(Field game)
	{
		for(int i=0;i<blocks.Length;i++)
		{
			if(game.CheckValue(blocks[i].Get_X(),blocks[i].Get_Y()+1)) return 1;
		}
		for(int i=0;i<blocks.Length;i++)
		{
			blocks[i].Move();
		}
		pos_y0++;
		return 0;
	}
	
	public void Move_Hor(Field game, int dir)
	{
		for(int i=0;i<blocks.Length;i++)
		{
			if(game.CheckValue(blocks[i].Get_X()+dir,blocks[i].Get_Y())) return;
		}
		for(int i=0;i<blocks.Length;i++)
		{
			blocks[i].Move_Hor(dir);
		}
		pos_x0+=dir;
	}
	
	public void Draw_Tetramino(Graphics g, SolidBrush br, int Size)
	{
		br.Color=Block_Color;
		for(int i=0;i<blocks.Length;i++)
		{
			g.FillRectangle(br, blocks[i].Get_X()*Size+2,blocks[i].Get_Y()*Size+2,Size-4,Size-4);
		}
	}
	abstract public void Rotate(Field game);
}

class Tetramino_Type_1: Tetramino
{
	public Tetramino_Type_1(int pos_x0, int pos_y0): base(pos_x0,pos_y0){}
	
	public override void Rotate(Field game)
	{
		int dx, dy;
		int[] x_new, y_new;
		x_new=new int[4];
		y_new=new int[4];
		for(int i=0;i<4;i++)
		{
			dx=blocks[i].Get_X()-pos_x0;
			dy=blocks[i].Get_Y()-pos_y0;
			x_new[i]=pos_x0+dy;
			y_new[i]=pos_y0-dx;
			if(game.CheckValue(x_new[i],y_new[i])) return;
		}
		for(int i=0;i<4;i++)
		{
			blocks[i].Set_Position(x_new[i],y_new[i]);
		}
	}
}

class Tetramino_Type_2: Tetramino
{
	public Tetramino_Type_2(int pos_x0, int pos_y0): base(pos_x0,pos_y0){}
	
	public override void Rotate(Field game)
	{
		int dx, dy;
		int[] x_new, y_new;
		x_new=new int[4];
		y_new=new int[4];
		for(int i=0;i<4;i++)
		{
			dx=blocks[i].Get_X()-pos_x0;
			dy=blocks[i].Get_Y()-pos_y0;
			x_new[i]=pos_x0+dy;
			y_new[i]=pos_y0+dx;
			if(game.CheckValue(x_new[i],y_new[i])) return;
		}
		for(int i=0;i<4;i++)
		{
			blocks[i].Set_Position(x_new[i],y_new[i]);
		}
	}
}

class O_Tetramino:Tetramino_Type_2
{
	public O_Tetramino(int pos_x0, int pos_y0): base(pos_x0,pos_y0)
	{
		blocks[0]=new Block(pos_x0,pos_y0);
		blocks[1]=new Block(pos_x0+1,pos_y0);
		blocks[2]=new Block(pos_x0,pos_y0+1);
		blocks[3]=new Block(pos_x0+1,pos_y0+1);
		Block_Color=Color.Yellow;
	}
	public O_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class I_Tetramino:Tetramino_Type_2
{
	public I_Tetramino(int pos_x0, int pos_y0): base(pos_x0,pos_y0)
	{
		blocks[0]=new Block(pos_x0-1,pos_y0);
		blocks[1]=new Block(pos_x0,pos_y0);
		blocks[2]=new Block(pos_x0+1,pos_y0);
		blocks[3]=new Block(pos_x0+2,pos_y0);
		Block_Color=Color.LightBlue;
	}
	public I_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class S_Tetramino:Tetramino_Type_1
{
	public S_Tetramino(int pos_x0, int pos_y0): base(pos_x0,pos_y0)
	{
		blocks[0]=new Block(pos_x0-1,pos_y0+1);
		blocks[1]=new Block(pos_x0,pos_y0+1);
		blocks[2]=new Block(pos_x0,pos_y0);
		blocks[3]=new Block(pos_x0+1,pos_y0);
		Block_Color=Color.Red;
	}
	public S_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class Z_Tetramino:Tetramino_Type_1
{
	public Z_Tetramino(int pos_x0, int pos_y0): base(pos_x0,pos_y0)
	{
		blocks[0]=new Block(pos_x0-1,pos_y0);
		blocks[1]=new Block(pos_x0,pos_y0);
		blocks[2]=new Block(pos_x0,pos_y0+1);
		blocks[3]=new Block(pos_x0+1,pos_y0+1);
		Block_Color=Color.Green;
	}
	
	public Z_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class L_Tetramino:Tetramino_Type_1
{
	public L_Tetramino(int pos_x0, int pos_y0): base(pos_x0-1,pos_y0+1)
	{
		blocks[0]=new Block(pos_x0-1,pos_y0);
		blocks[1]=new Block(pos_x0-1,pos_y0+1);
		blocks[2]=new Block(pos_x0-1,pos_y0+2);
		blocks[3]=new Block(pos_x0,pos_y0+2);
		Block_Color=Color.Orange;
	}
	public L_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class J_Tetramino:Tetramino_Type_1
{
	public J_Tetramino(int pos_x0, int pos_y0): base(pos_x0+1,pos_y0+1)
	{
		blocks[0]=new Block(pos_x0+1,pos_y0);
		blocks[1]=new Block(pos_x0+1,pos_y0+1);
		blocks[2]=new Block(pos_x0+1,pos_y0+2);
		blocks[3]=new Block(pos_x0,pos_y0+2);
		Block_Color=Color.Pink;
	}
	public J_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}

class T_Tetramino:Tetramino_Type_1
{
	public T_Tetramino(int pos_x0, int pos_y0): base(pos_x0,pos_y0)
	{
		blocks[0]=new Block(pos_x0-1,pos_y0);
		blocks[1]=new Block(pos_x0,pos_y0);
		blocks[2]=new Block(pos_x0+1,pos_y0);
		blocks[3]=new Block(pos_x0,pos_y0+1);
		Block_Color=Color.Purple;
	}
	public T_Tetramino(int pos_x0, int pos_y0, Color col): this(pos_x0,pos_y0)
	{
		Block_Color=col;
	}
}
