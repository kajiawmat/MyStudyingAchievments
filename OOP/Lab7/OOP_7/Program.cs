/*
 * Created by SharpDevelop.
 * User: Alex
 * Date: 20.10.2021
 * Time: 8:57
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

class Element<T> 
{
	public T Data;
	public Element<T> Next;
	public Element()
	{
		Next=null;
	}
	public Element(T Data): this()
	{
		this.Data=Data;
	}
}

abstract class List<T>
{
	protected Element<T> Head;
	protected Element<T> Tail;
	protected List(Element<T> Head=null, Element<T> Tail=null)
	{
		this.Head=Head;
		this.Tail=Tail;
	}
	public abstract void Add_Element(T X);
	public void Show_List()
	{
		Element<T> p=Head;
		while(p!=null)
		{
			Console.Write("{0} ",p.Data);
			p=p.Next;
		}
		Console.WriteLine();
	}
}

class Queue<T>: List<T>
{
	public override void Add_Element(T X)
	{
		Element<T> p=new Element<T>(X);
		if(Head==null)
		{
			Head=p;
			Tail=p;
		}
		else
		{
			Tail.Next=p;
			Tail=p;
		}
		Tail.Next=null;
	}
}

class Stack<T>: List<T>
{
	public override void Add_Element(T X)
	{
		Element<T> p =new Element<T>(X);
		p.Next=Head;
		Head=p;
	}
}

class Program
{
	static int[] genRandArray(int size, int maxValue)
	{
		Random rnd = new Random();
		int[] matrix = new int[size];
		for(int i=0;i<size;i++)
		{
			matrix[i]= rnd.Next(maxValue)+1;
		}
		return matrix;
	}
	
	public static void Main(string[] args)
	{
		const int N=5;
		const int maxValue = 100;
		int[] array = genRandArray(N,maxValue);
		Queue<int> q =new Queue<int>();
		Stack<int> s =new Stack<int>();
		for(int i=0;i<array.Length;i++)
		{
			Console.WriteLine(array[i]+" ");
		}
		for(int i=0;i<array.Length;i++)
		{
			q.Add_Element(array[i]);
			s.Add_Element(array[i]);
		}
		q.Show_List();
		s.Show_List();
		Console.ReadLine();
	}
}