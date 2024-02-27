goal:-
 exists_file('RGZ.txt'),
 open('RGZ.txt',read,F),
 writeln("¬ведите искомую подстроку"),
 read(X),
 string_codes(X,L0),
 set_input(F),
 search_lines(F,L0,Res),
 close(F),
 writefile(Res).

check_line(_,_,[]):-!.

check_line([_|T],L0,_):-
 check_line(T,L0,L0).
 
check_line([X|T],L0,[X1|T1]):-
 X=:=X1,
 check_line(T,L0,T1).
 
search_lines(_,_,""):-
 at_end_of_stream,!.

search_lines(F,L0,Res):-
 read_line_to_codes(F,L),
 check_line(L,L0,L0),!,
 search_lines(F,L0,Res0),
 string_codes(S,L),
 string_concat(S,"\n",S_res),
 string_concat(S_res,Res0,Res).
 
search_lines(F,L0,Res):-
 read_line_to_codes(F,L),
 search_lines(F,L0,Res).


writefile(Res):-
 open('RGZ_Res(Ser).txt',write,F),
 set_output(F),
 write(Res),
 close(F).
