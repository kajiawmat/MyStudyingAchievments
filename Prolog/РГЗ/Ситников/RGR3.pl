:- discontiguous func/1.
:-dynamic employee/4.

goal_three:-
 retractall(employee(_,_,_,_)),
 exists_file('RGR3.txt'),!,
 consult('RGR3.txt'),
 menu.

goal_three:-
 open('RGZ3.txt',write,F),
 close(F),
 menu.

menu:-
 repeat,
 nl,
 writeln('1) - �������� ����������� ���� ������;'),
 writeln('2) - ���������� ������'),
 writeln('3) - �������� ������'),
 writeln('4) - ���������� � ������� ������ ��������'),
 writeln('5) - ����� � ���������� ���� ������'),
 read(X),
 X>0,
 X<6,
 func(X),
 X=:=5,!.

func(1):-
 listing(employee/4).

func(2):-
 repeat,
 writeln("������� ������� ����������:"),
 read(LN),
 writeln("������� ��� ���������� :"),
 read(FN),
 writeln("������� ��������� ����������:"),
 read(J),
 writeln("������� ����� ����������:"),
 read(Pr),
 assertz(employee(LN,FN,J,Pr)),
 writeln("�� ������ ���������� ���������� [y/n]?"),
 read(Sw),
 Sw=n,!.

func(3):-
repeat,
 writeln("������� ������� ����������:"),
 read(LN),
 writeln("������� ��� ����������:"),
 read(FN),
 writeln("������� ��������� ����������:"),
 read(J),
 retract(employee(LN,FN,J,_)),
 writeln("�� ������ ���������� ���������� [y/n]?"),
 read(Sw),
 Sw=n,!.

func(4):-
 findall(employee(LN,FN,J,Pr),employee(LN,FN,J,Pr),L),
 sum_price(L,Sum),
 length(L,N),
 Av is (Sum/N),
 findall(employee(LN,FN,J,Pr),(employee(LN,FN,J,Pr),Pr<Av),L_Res),
 write("������� ����� = "),
 writeln(Av),
 write_list(L_Res).

sum_price([],0):-!.

sum_price([H|T],Sum):-
 H=employee(_,_,_,Pr),
 sum_price(T,Sum1),
 Sum is (Pr+Sum1).
 
write_list([]):-!.

write_list([H|T]):-
 writeln(H),
 write_list(T).

func(5):-
 tell('RGR3.txt'),
 listing(employee/4),
 told.


 %flight(11, moscow, 10, 1000).
 %flight(12, novosibirsk, 5, 1200).
