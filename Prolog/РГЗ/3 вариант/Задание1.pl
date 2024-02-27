goal_one:-
 writeln("������� 1-�� ������"),
 read(L1),
 writeln("������� 2-�� ������"),
 read(L2),
 func_one(L1,L2,L_Res),
 writeln(L_Res).
 
func_one([],_,[]):-!.

func_one([H|T],L2,L_Res):-
 delete(T,H,L0),
 func_one(L0,L2,L_Res0),
 check_H(H,L2,L_Res0,L_Res).
 
check_H(H,L2,L_Res0,L_Res):-
 member(H,L2),!,
 L_Res=[H|L_Res0].
 
check_H(_,_,L_Res0,L_Res):-
 L_Res=L_Res0.
