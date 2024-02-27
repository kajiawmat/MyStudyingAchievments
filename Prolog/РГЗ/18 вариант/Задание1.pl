goal_1:-
 writeln("¬ведите список:"),
 read(L),
 writeln("¬ведите X:"),
 read(X),
 func(L,X,L_Res),
 write("L_Res="),
 writeln(L_Res).
 
func([],_,[]):-!.

func([X|[X|T]],X,L_Res):-!,
 func([X|T],X,L_Res0),
 L_Res=[X|L_Res0].
 
func([X|[_|T]],X,L_Res):-!,
 func(T,X,L_Res0),
 L_Res=[X|L_Res0].

func([H|T],X,L_Res):-
 func(T,X,L_Res0),
 L_Res=[H|L_Res0].
