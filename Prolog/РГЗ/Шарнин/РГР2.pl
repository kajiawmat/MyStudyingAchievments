task_2:-
 exists_file('WorkersFull.txt'),!,
 see('WorkersFull.txt'),
 seeing(F),
 tell('SurnameInit.txt'),
 convert_names(F),
 seen,
 told.
 
task_2:-
 writeln("Такого файла не существует").

convert_names(_):-
 at_end_of_stream,!.
 
convert_names(F):-
 read_line_to_codes(F,L),
 name(S,L),
 split_string(S," "," ",S_Name),
 write_name(S_Name),
 convert_names(F).
 

write_name([S|[F|[P]]]):-
 string_chars(F,[F_H|_]),
 string_chars(P,[P_H|_]),!,
 write(S),
 write(" "),
 write(F_H),
 write(". "),
 write(P_H),
 writeln(".").
 
write_name(_).
