goal_one:-
 writeln("¬ведите список:"),
 read(L),
 not_unique(L,L_Res),
 writeln("—писок из не уникальных элементов списка"),
 writeln(L_Res).

not_unique([],[]):-!.

not_unique([X|T],L_Res):-
 length([X|T],N),
 delete(T,X,L1),
 length(L1,N1),
 not_unique(L1,L_Res1),
 Count is (N-N1),
 check_X(X,Count,L_Res1,L_Res).

check_X(X,Count,L_Res1,L_Res):-
 Count>1,!,
 L_Res=[X|L_Res1].

check_X(_,_,L_Res1,L_Res):-
 L_Res=L_Res1.

