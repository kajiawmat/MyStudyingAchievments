:- discontiguous func/1.
:-dynamic flight/4.

goal_3:-
 retractall(flight(_,_,_,_)),
 consult('RGZ3.txt'),
 menu.

menu:-
 repeat,
 nl,
 writeln('1) - �������� ����������� ���� ������;'),
 writeln('2) - ���������� ������'),
 writeln('3) - �������� ������'),
 writeln('4) - ����� �� ������ � ��������� 6 �����'),
 writeln('5) - ����� � ���������� ���� ������'),
 read(X),
 X>0,
 X<6,
 func(X),
 X=:=5,!.

func(1):-
 listing(flight/4).

func(2):-
 repeat,
 writeln("������� ����� �����:"),
 read(N),
 writeln("������� ����� ����������:"),
 read(C),
 writeln("������� ����� ����������� (24-�. ������)"),
 read(T),
 writeln("������� ��������� ������"),
 read(Pr),
 assertz(flight(N,C,T,Pr)),
 writeln("�� ������ ���������� ���������� [y/n]?"),
 read(Sw),
 Sw=n,!.

func(3):-
 repeat,
 writeln("������� ����� �����:"),
 read(N),
 writeln("������� ����� ����������:"),
 read(C),
 retract(flight(N,C,_,_)),
 writeln("�� ������ ���������� �������� [y/n]?"),
 read(Sw),
 Sw=n,!.

func(4):-
 writeln("������� ������������� ����� ����������:"),
 read(C),
 writeln("������� ������� ����� (24-�. ������):"),
 read(T),
 nl,writeln("����� ������� ����, ���� ���������� (�� n/a)"),
 search(C,T).

search(C,T):-
 findall(flight(N,C,T1,Pr),(flight(N,C,T1,Pr),check_time(T,T1)),Ln),
 Ln\=[],!,
 min_price(Ln,_,Res),
 write_list(Res).

search(_,_):-
 writeln("���� �� ������").

check_time(T,T1):-
 T>T1,
 T2 is (T1+24),
 Tf is (T+6),
 Tf>=T2.

check_time(T,T1):-
 T=<T1,
 Tf is (T+6),
 Tf>=T1.

min_price([H|[]],Pr,[H]):-
 H=flight(_,_,_,Pr).

min_price([H|T],Pr,Res):-
 H=flight(_,_,_,Pr1),
 min_price(T,Pr2,Res2),
 check_price(H,Pr1,Res2,Pr2,Res,Pr).

check_price(H,Pr1,_,Pr2,Res,Pr):-
 Pr1<Pr2,!,
 Pr=Pr1,
 Res=[H].
 
check_price(H,Pr1,Res2,Pr2,Res,Pr):-
 Pr1=:=Pr2,!,
 Pr=Pr1,
 Res=[H|Res2].
 
check_price(_,_,Res2,Pr2,Res,Pr):-
 Pr=Pr2,
 Res=Res2.

write_list([]):-!.

write_list([H|T]):-
 writeln(H),
 write_list(T).

func(5):-
 tell('RGZ3.txt'),
 listing(flight/4),
 told.


 %flight(11, moscow, 10, 1000).
 %flight(12, novosibirsk, 5, 1200).
