import java.io.File
import kotlin.math.abs
import java.util.Scanner

typealias MutMatr<T> = MutableList< MutableList<T> >
typealias MutVect<T> = MutableList<T>

fun Min(x:Int, y:Int): Int
{
	return if(x<y) x else y
}

class Index(val x: Int, val i: Int, val j: Int){}

fun printTable(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>)
{
	val n=A.size
	val m=B.size
	for(i in 0 until n)
	{
		for(j in 0 until m) print(String.format("%5d|",C[i][j]))
		println(String.format("%5d",A[i]))
		for(j in 0 until m) 
		{
			if(X[i][j]!=null) print(String.format("%-5d|",X[i][j]))
			else print("     |")
		}
		println("")
	}
	println("")
	for(j in 0 until m) print(String.format("%5d|",B[j]))
	println("\n\n")
}

fun printTablePotential(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>, Rows: MutVect<Int?>, Columns: MutVect<Int?>)
{
	val n=A.size
	val m=B.size
	for(i in 0 until n)
	{
		for(j in 0 until m) print(String.format("%5d|",C[i][j]))
		print(String.format("%5d ",A[i]))
		println("(${Rows[i]!!})")
		for(j in 0 until m) 
		{
			if(X[i][j]!=null) print(String.format("%-5d|",X[i][j]))
			else print(String.format("%5s|","(${C[i][j]-Rows[i]!!-Columns[j]!!})"))
		}
		println("")
	}
	println("")
	for(j in 0 until m) print(String.format("%5d|",B[j]))
	println("")
	for(j in 0 until m) print(String.format("%6s",String.format("(%d)",Columns[j]!!)))
	println("\n\n")
}

fun printValue(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>)
{
	val n=A.size
	val m=B.size
	var sum=0L
	for(i in 0 until n) for(j in 0 until m) if(X[i][j]!=null) sum+=X[i][j]!!.toLong()*C[i][j].toLong()
	println("Function value is equals $sum\n")
}

fun countNotNull(X: MutMatr<Int?>,n: Int, m: Int): Int
{
	var res=0
	
	for(i in 0 until n) for(j in 0 until m) if(X[i][j]!=null) res++
	return res
}

fun northWestAngle(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>)
{
	var i=0
	var j=0
	val n=A.size
	val m=B.size
	val count=n+m
	
	for(k in 1 until count)
	{
		if(i==n || j==m) break
		val min=Min(A[i],B[j])
		A[i]-=min
		B[j]-=min
		X[i][j]=min
		if(A[i]==0) i++ else j++
		printTable(A,B,C,X)
	}
}

/*  Метод минимальной стоимости

fun minCast(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>)
{
	val n=A.size
	val m=B.size
	var i:Int
	var j:Int
	var min:Int
	
	var AvailableRow=(0 until n).toMutableList()
	var AvailableColumn=(0 until m).toMutableList()
	
	var SortArray=mutableListOf<Index>()
	for(i in 0 until n) for(j in 0 until m) SortArray.add(Index(C[i][j],i,j))
	SortArray.sortBy{it.x}
	
	for(ind in SortArray)
	{
		i=ind.i
		j=ind.j
		if((i in AvailableRow) && (j in AvailableColumn))
		{
			min=Min(A[i],B[j])
			A[i]-=min
			B[j]-=min
			X[i][j]=min
			if(A[i]==0) AvailableRow.remove(i) 
			else AvailableColumn.remove(j) 
			printTable(A,B,C,X)
		}
	}
}

*/


/* Проверка оптимальности решения и метод потенциалов

fun checkSolution(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>): Int?
{
	val n=A.size
	val m=B.size
	var count=n+m-1
	var switch=0

	var rowInQueue=mutableListOf<Int>()
	var columnInQueue=mutableListOf<Int>()
	
	var rowPotentials=MutableList<Int?>(n, {null})
	var columnPotentials=MutableList<Int?>(m, {null})
	
	rowPotentials[0]=0
	rowInQueue.add(0)
	while(count>0)
	{
		if(switch==0)
		{
			for(i in rowInQueue) for(j in 0 until m) if(X[i][j]!=null && columnPotentials[j]==null)
			{
				columnPotentials[j]=C[i][j]-rowPotentials[i]!!.toInt()
				count--
				columnInQueue.add(j)
			}
			rowInQueue.clear()
		}
		else
		{
			for(j in columnInQueue) for(i in 0 until n) if(X[i][j]!=null && rowPotentials[i]==null)
			{
				rowPotentials[i]=C[i][j]-columnPotentials[j]!!.toInt()
				count--
				rowInQueue.add(i)
			}
			columnInQueue.clear()
		}
		switch=(1-switch)
	}
	printTablePotential(A,B,C,X,rowPotentials,columnPotentials)
	var min=Index(C[0][0]-(rowPotentials[0]!!.toInt()+columnPotentials[0]!!.toInt()),0,0)
	var temp: Index
	for(i in 0 until n) for(j in 0 until m)
	{
		temp=Index(C[i][j]-(rowPotentials[i]!!.toInt()+columnPotentials[j]!!.toInt()),i,j)
		if(min.x>temp.x) min=temp
	}
	if(min.x<0) return min.i*m+min.j
	return null
}

fun newBasisVariable(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>, _i: Int, _j: Int)
{
	val n=A.size
	val m=B.size
	
	var VertexList=mutableMapOf<Int, Int?>()
	var VertEdgeMapList=mutableMapOf<Int, MutVect<Int> >()
	var GorEdgeMapList=mutableMapOf<Int, MutVect<Int> >()
	var switch: Int
	var VertexQueue=mutableListOf<Int>()
	var VertexQueueNext=mutableListOf<Int>()
	var flag=true
	
	X[_i][_j]=0
	for(i in 0 until n) for(j in 0 until m) if(X[i][j]!=null)
	{
		VertexList.put(i*m+j, null)
		VertEdgeMapList.put(i*m+j, mutableListOf<Int>())
		GorEdgeMapList.put(i*m+j, mutableListOf<Int>())
	}
	for(k in VertexList.keys) for(i in 0 until n)
	{
		for(i in 0 until n)
		{
			if(i==k/m) continue
			if(X[i][k%m]!=null) VertEdgeMapList[k]!!.add(i*m+k%m)
		}
		for(j in 0 until m)
		{
			if(j==k%m) continue
			if(X[k/m][j]!=null) GorEdgeMapList[k]!!.add(k-k%m+j)
		}
	}
	
	//Место для поиска в глубину
	switch=0
	var _ind=_i*m+_j
	VertexList[_ind]=-1
	VertexQueue.add(_ind)
	while(flag)
	{
		for(vert in VertexQueue)
		{
			if(switch==0)
			{
				for(ind in (GorEdgeMapList[vert]!!))
				{
					if(VertexList[ind]==-1) 
					{
						VertexList[ind]=vert
						flag=false
					}
					VertexList[ind]=vert
					VertexQueueNext.add(ind)
				}
			}
			else
			{
				for(ind in (VertEdgeMapList[vert]!!))
				{
					if(VertexList[ind]==-1) 
					{
						VertexList[ind]=vert
						flag=false
					}
					VertexList[ind]=vert
					VertexQueueNext.add(ind)
				}
			}
		}
		switch=1-switch
		VertexQueue.clear()
		VertexQueue.addAll(VertexQueueNext)
		VertexQueueNext.clear()
	}
	if(switch==1)
	{
		println("What the...")
		return
	}
	
	switch=0
	var vertNow=_ind
	var vertNext=VertexList[_ind]!!
	var vertMin=vertNext
	print("(${vertNow/m},${vertNow%m})")
	while(true)
	{
		if(switch==1 && (X[vertNow/m][vertNow%m]!!<X[vertMin/m][vertMin%m]!!)) vertMin=vertNow
		vertNow=vertNext
		vertNext=VertexList[vertNow]!!
		switch=(1-switch)
		print(" -> (${vertNow/m},${vertNow%m})")
		if(vertNow==_ind) break
	}
	println("\n")
	switch=0
	vertNext=VertexList[_ind]!!
	var minValue=X[vertMin/m][vertMin%m]!!
	while(true)
	{
		if(switch==0) X[vertNow/m][vertNow%m]=X[vertNow/m][vertNow%m]!!+minValue
		else X[vertNow/m][vertNow%m]=X[vertNow/m][vertNow%m]!!-minValue
		vertNow=vertNext
		vertNext=VertexList[vertNow]!!
		switch=(1-switch)
		if(vertNow==_ind) break
	}
	X[vertMin/m][vertMin%m]=null
}


fun findBestSolution(A:MutVect<Int>, B:MutVect<Int>, C: MutMatr<Int>, X: MutMatr<Int?>)
{
	var position: Int?=checkSolution(A,B,C,X)
	var i: Int
	var j: Int
	val n=A.size
	val m=B.size
	while(position != null)
	{
		i=position.toInt()/m
		j=position.toInt()%m
		newBasisVariable(A,B,C,X,i,j)
		printTable(A,B,C,X)
		printValue(A,B,C,X)
		position=checkSolution(A,B,C,X)
	}
}

*/

fun main(args: Array<String>){
	val func=if(args.size>0) 1 else 1 
	val fileName=if(args.size>1) args[1] else "In.txt" 
	
	val scan=Scanner(File(fileName))
	val n=scan.nextInt()
	val m=scan.nextInt()
	var Matr_C=mutableListOf< MutableList<Int> >()
	var Matr_X=mutableListOf< MutableList<Int?> >()
	var Vect_A=mutableListOf<Int>()
	var Vect_B=mutableListOf<Int>()
	var sum_A=0
	var sum_B=0
	for(i in 0 until n)
	{
		Matr_C.add(mutableListOf<Int>())
		Matr_X.add(mutableListOf<Int?>())
		for(j in 0 until m)
		{
			Matr_C[i].add(scan.nextInt())
			Matr_X[i].add(null)
		}
		Vect_A.add(scan.nextInt())
		sum_A+=Vect_A[i]
	}
	for(j in 0 until m)
	{
		Vect_B.add(scan.nextInt())
		sum_B+=Vect_B[j]
	}
	when(func)
	{
		1 -> northWestAngle(Vect_A,Vect_B,Matr_C,Matr_X)
		//2 -> minCast(Vect_A,Vect_B,Matr_C,Matr_X)
	}
	var count: Int
	if(sum_A<sum_B)
	{
		Vect_A.add(sum_B-sum_A)
		val i0=Vect_A.size-1
		Matr_C.add(mutableListOf<Int>())
		Matr_X.add(mutableListOf<Int?>())
		for(j in 0 until m)
		{
			Matr_C[i0].add(0)
			Matr_X[i0].add(if(Vect_B[j]!=0) Vect_B[j] else null)
			Vect_A[i0]-=Vect_B[j]
			Vect_B[j]=0
		}
		count=countNotNull(Matr_X,n+1,m)
		for(j in 0 until m)
		{
			if(count==(n+m)) break
			if(Matr_X[i0][j]==null) 
			{
				Matr_X[i0][j]=0
				count++
			}
		}
	}
	else if(sum_A>sum_B)
	{
		Vect_B.add(sum_A-sum_B)
		val j0=Vect_B.size-1
		for(i in 0 until n)
		{
			Matr_C[i].add(0)
			Matr_X[i].add(if(Vect_A[i]!=0) Vect_A[i] else null)
			Vect_B[Vect_B.size-1]-=Vect_A[i]
			Vect_A[i]=0
		}
		count=countNotNull(Matr_X,n,m+1)
		for(i in 0 until n)
		{
			if(count==(n+m)) break
			if(Matr_X[i][j0]==null) 
			{
				Matr_X[i][j0]=0
				count++
			}
		}
	}
	println("Result Table")
	printTable(Vect_A,Vect_B,Matr_C,Matr_X)
	printValue(Vect_A,Vect_B,Matr_C,Matr_X)
	//findBestSolution(Vect_A,Vect_B,Matr_C,Matr_X)
}