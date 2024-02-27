goal1:-
 writeln("������� ��������: "),
 read(A),
 read(B),
 ���������������(A,B).
 

����������������(X,Y):-
 (Y>=X ->
  writeln(Y),
  Y1 is (Y-2),
  ����������������(X,Y1);
  writeln("��")
 ).

���������������(X,Y):-
 Y1 is (Y mod 2),
 (Y1=:=1 ->
  ����������������(X,Y);
  Y2 is (Y-1),
  ����������������(X,Y2)
 ).

 /*��������(1).

����������������(X,Y):-
 X=<Y,
 writeln(X),
 X2 is X+2,
 ����������������(X2,Y),!.

����������������(X,Y):-
 X>Y,!.

���������������(X,Y):-
 X1 is (X mod 2),
 ��������(X1),
 ����������������(X,Y),!.

���������������(X,Y):-
 X1 is (X mod 2)+1,
 ��������(X1),
 X2 is (X+1),
 ����������������(X2,Y),!.

*/
 /*������ �2*/
 
goal2:-
 repeat,
 writeln("������� ����� ����� ���������:"),
 read(A),
 (A>0 ->
  ����(A,P),
  format('F(~w)=~w',[A,P]),nl,fail;
  writeln("��."),!
 ).

����(0,1):-!.
����(1,1):-!.

����(A,P):-
 A1 is (A-1),
 A2 is (A-2),
 ����(A1,P1),
 ����(A2,P2),
 P is (P1+P2).
 

 /*
 � �������� ������ �� ��������:)
goal3:-
 writeln("������� ������:"),
 read(L),
 writeln("������� 1-�� �����������"),
 read(A1),
 writeln("������� 2-�� �����������"),
 read(A2),
 listsplit3(L,A1,A2,L1,L2,L3),
 writeln(L1),
 writeln(L2),
 writeln(L3).

listsplit3(L,A1,A2,L1,L2,L3):-
 A1<A2,!,
 N is A1,
 split(L,N,L1,Lt),
 N1 is (A2-A1),
 split(Lt,N1,L2,L3).

listsplit3(L,A1,A2,L1,L2,L3):-
 N is A2,
 split(L,N,L1,Lt),
 N1 is (A1-A2),
 split(Lt,N1,L2,L3).

split([],_,[],[]):-!.
split([Y|T],N,[Y|T1],T2):-N>0,!,N1 is (N-1),split(T,N1,T1,T2).
split([Y|T],N,T1,[Y|T2]):-N1 is (N-1), split(T,N1,T1,T2),!.

*/

goal3:-
 writeln("������� ������:"),
 read(L),
 writeln("������� 1-�� �����������"),
 read(A1),
 writeln("������� 2-�� �����������"),
 read(A2),
 �������������(L,A1,A2,L1,L2,L3),
 writeln(L1),
 writeln(L2),
 writeln(L3).

�������������(L,A1,A2,L1,L2,L3):-
 A1<A2,!,
 N is A1,
 ����������(L,N,L1,Lt),
 N1 is (A2+1),
 ����������(Lt,N1,L2,L3).

�������������(L,A1,A2,L1,L2,L3):-
 N is A2,
 ����������(L,N,L1,Lt),
 N1 is (A1+1),
 ����������(Lt,N1,L2,L3).

����������([],_,[],[]):-!.
����������([Y|T],N,[Y|T1],T2):-Y<N,!,����������(T,N,T1,T2).
����������([Y|T],N,T1,[Y|T2]):-����������(T,N,T1,T2).

/*������ 4*/

�������([],_,[]):-!.
�������([X|T],X,T2):-�������(T,X,T2),!.
�������([Y|T],X,[Y|T1]):-�������(T,X,T1).

�����([],0):-!.
�����([_|T],N):-�����(T,N1),N is N1+1.

goal4:-
 writeln("������� ������"),
 read(L),
 �������������(L,Max,L1),
 write("������� ����������� ����: "),
 writeln(Max),
 write("����� ����������� �����: "),
 writeln(L1).
 
�������������([],0,[]):-!.
 
�������������([H|T],Max,L0):-
 �����([H|T],N1),
 �������([H|T],H,L2),
 �����(L2,N2),
 Max2 is(N1-N2),
 �������������(L2,Max3,L3),
 (Max3<Max2 ->
  L0=[H],
  Max is Max2;
  Max is Max3,
  (Max3>Max2 ->
   L0=L3;
   L0=[H|L3]
  )
 ).
 
 %[2,1,1,2,1]
 