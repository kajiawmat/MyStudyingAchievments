task2:-
 exists_file('In.txt'),!,
 read_words('In.txt',L),
 list_max_length(L,_,Lmax),
 tell('Out.txt'),
 write_words(L,Lmax),
 told.
 
task2:-
 writeln('Input file does not exist').
 
read_words(FileName,L):-
 open(FileName,read,F),
 read_stream_to_codes(F,L0),
 name(S,L0),
 split_string(S," .,;:!?-\n"," .,;:!?-\n",L),
 close(F).

list_max_length([H|[]],Len,[H]):-
 string_length(H,Len),!.
 
list_max_length([H|T],Len,L_Res):-
 string_length(H,N1),
 list_max_length(T,N2,L_Res2),
 check_len(H,N1,L_Res2,N2,L_Res,Len).
 
check_len(_,N1,L_Res2,N2,L_Res,Len):-
 N1<N2,!,
 Len=N2,
 L_Res=L_Res2.
 
check_len(H,N1,L_Res2,N2,L_Res,Len):-
 N1=:=N2,!,
 Len=N2,
 L_Res=[H|L_Res2].

check_len(H,N1,_,_,L_Res,Len):-
 Len=N1,
 L_Res=[H].

write_words([],[]):-!.

write_words([H|T],[]):-!,
 write(H),
 write(' '),
 write_words(T,[]).

write_words([H|T],[H0|T0]):-
 H\==H0,!,
 write(H),
 write(' '),
 write_words(T,[H0|T0]).
 
write_words([_|T],[_|T0]):-
 write_words(T,T0).
