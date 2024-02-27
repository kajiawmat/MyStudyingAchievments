goal:-
 exists_file('In.txt'),!,
 see('In.txt'),
 tell('Out.txt'),
 seeing(F),
 new_line_out(F),
 seen,
 told.
 
goal:-
 writeln('Файл In.txt не найден').
 
new_line_out(F):-
 at_end_of_stream,!.
 
new_line_out(F):-
 read_line_to_codes(F,L),
 name(S,L),
 split_string(S," .,;:!?-\n"," .,;:!?-\n",L_words),
 write_words(L_words),
 new_line_out(F).
 
write_words([]):-
 nl,!.
 
write_words([X|T]):-
 write(X),
 write('*'),
 write_words(T).
