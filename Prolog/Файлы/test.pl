:- dynamic parent/2.

parent("bob","amm").
parent("bob","joe").
parent("joe","bee").

goal:-
 parent("bob",X),
 X="amm",
 writeln("bob"),
 fail.
 
goal_0:-
 goal.
