goal:-
 exists_file('RGZ.txt'),
 open('RGZ.txt',read,In),
 read_stream_to_codes(In,L),
 close(In),
 replace_symb(L,L_res),
 string_chars(S,L_res),
 open('RGZ_Vald.txt',write,Out),
 set_output(Out),
 write(S),
 close(Out).
 
replace_symb([],[]):-!.

replace_symb([X|T],[X1|T1]):-
 char_code(" ",K),
 K=:=X,!,
 char_code("*",K1),
 X1=K1,
 replace_symb(T,T1).

replace_symb([X|T],[X1|T1]):-
 X1=X,
 replace_symb(T,T1).
