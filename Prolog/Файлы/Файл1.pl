:- dynamic parent/2.

parent("bob","amm").
parent("bob","joe").
parent("joe","bee").

goal:-
 F=parent("bob",_),
 writeln(F).
