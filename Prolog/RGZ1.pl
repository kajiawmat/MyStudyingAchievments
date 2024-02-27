goal_1:-
 writeln("¬ведите массив:"),
 read(L),
 square_every_three(L,1,L_res),
 write("L_res = "),
 write(L_res).
 
square_every_three([],_,[]):-!.

square_every_three([X|T],N,[X2|L_res]):-
 N=:=3,!,
 N1=1,
 X2 is (X*X),
 square_every_three(T,N1,L_res).
 
square_every_three([X|T],N,[X|L_res]):-
 N1 is (N+1),!,
 square_every_three(T,N1,L_res).
 

