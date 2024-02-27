goal:-
 writeln("������� 1-�� ������:"),
 read(L1),
 writeln("������� 2-�� ������:"),
 read(L2),
 diff(L1,L2,L_Res),
 writeln(L_Res).
 
diff([],_,[]):-!.

diff([H|T],L2,L_Res):-
 diff(T,L2,L_Res1),
 set_Res(H,L2,L_Res1,L_Res).
 
set_Res(H,L2,L_Res1,L_Res):-
 member(H,L2),!,
 L_Res=L_Res1.

set_Res(H,_,L_Res1,L_Res):-
 L_Res=[H|L_Res1].
