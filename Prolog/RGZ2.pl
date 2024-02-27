goal_2:-
  exists_file('RGZ2.txt'),
  readfile(L),
  reverse_words_in_file(L,L1,W),
  reverse(W,W1),
  append(W1,L1,L2),
  string_chars(S2,L2),
  writefile(S2).


readfile(L):-
  open('RGZ2.txt',read,F),
  read_stream_to_codes(F,L),
  close(F).

check_symb(X):-
  char_code("a",Min),
  char_code("z",Max),
  X>=Min,
  X=<Max.

check_symb(X):-
  char_code("A",Min),
  char_code("Z",Max),
  X>=Min,
  X=<Max.

reverse_words_in_file([],[],[]):-!.

reverse_words_in_file([X|T],L,[X|W]):-
  check_symb(X),!,
  reverse_words_in_file(T,L,W).

reverse_words_in_file([X|T],L,W):-
  reverse_words_in_file(T,L1,W1),
  reverse(W1,W2),
  W3=[X|W2],
  W=[],
  append(W3,L1,L).


writefile(S2):-
  open('RGZ2_red.txt',write,F),
  set_output(F),
  write(S2),
  close(F).

