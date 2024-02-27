goal_2:-
 exists_file("RGR2.txt"),
 open("RGR2.txt",read,In),
 open("RGR2_out.txt",write,Out),
 set_input(In),
 set_output(Out),
 read_lines(In),
 close(Out),
 close(In).

read_lines(_):-
 at_end_of_stream,!.
 
read_lines(In):-
 read_line_to_codes(In,L),
 name(S,L),
 split_string(S," "," ",W),
 change_line(W,W_Res),
 write_res(W_Res),
 read_lines(In).

change_line([],[]):-!.

change_line([H|T],W_Res):-
 string_length(H,N),
 N=1,!,
 change_line(T,W_Res0),
 W_Res=W_Res0.
 
change_line([H|T],W_Res):-
 change_line(T,W_Res0),
 W_Res=[H|W_Res0].

write_res([H]):-
 writeln(H),!.
 
write_res([H|T]):-
 write(H),
 write(" "),
 write_res(T).
