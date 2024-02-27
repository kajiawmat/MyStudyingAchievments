goal_two:-
 exists_file('RGR2.txt'),!,
 read_words('RGR2.txt',L),
 count_words(L,L_Res,C_Res),
 write_not_unique_words('RGR2_Res.txt',L_Res,C_Res).
 
goal_two:-
 writeln("���� �� ����������").
 
read_words(Name,L):-
 see(Name),
 seeing(F),
 read_stream_to_codes(F,L_codes),
 seen,
 name(S,L_codes),
 split_string(S," .,:;-!?\n\t"," .,:;-!?\n\t",L).

count_words([],[],[]):-!.
 
count_words([X|T],L_Res,C_Res):-
 length([X|T],N),
 delete(T,X,L1),
 length(L1,N1),
 count_words(L1,L_Res1,C_Res1),
 Count is (N-N1),
 check_X(X,Count,L_Res1,C_Res1,L_Res,C_Res).

check_X(X,Count,L_Res1,C_Res1,L_Res,C_Res):-
 Count>1,!,
 L_Res=[X|L_Res1],
 C_Res=[Count|C_Res1].

check_X(_,_,L_Res1,C_Res1,L_Res,C_Res):-
 L_Res=L_Res1,
 C_Res=C_Res1.

write_not_unique_words(Name,L_Res,C_Res):-
 tell(Name),
 write_lists(L_Res,C_Res),
 told.
 
write_lists([],[]):-!.

write_lists([H0|T0],[H1|T1]):-
 write(H0),
 write(" - "),
 write(H1),
 writeln(" ��������"),
 write_lists(T0,T1).
