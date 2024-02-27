:- discontiguous func/1.
:-dynamic flight/4.

goal_3:-
 retractall(flight(_,_,_,_)),
 consult('RGZ3.txt'),
 menu.

menu:-
 repeat,
 nl,
 writeln('1) - просмотр содержимого базы данных;'),
 writeln('2) - добавления записи'),
 writeln('3) - удаления записи'),
 writeln('4) - рейсы до города в ближайшие 6 часов'),
 writeln('5) - выход и сохранение базы данных'),
 read(X),
 X>0,
 X<6,
 func(X),
 X=:=5,!.

func(1):-
 listing(flight/4).

func(2):-
 repeat,
 writeln("Введите номер рейса:"),
 read(N),
 writeln("Введите город назначения:"),
 read(C),
 writeln("Введите время отправления (24-ч. формат)"),
 read(T),
 writeln("Введите стоимость билета"),
 read(Pr),
 assertz(flight(N,C,T,Pr)),
 writeln("Вы хотите продолжить добавление [y/n]?"),
 read(Sw),
 Sw=n,!.

func(3):-
 repeat,
 writeln("Введите номер рейса:"),
 read(N),
 writeln("Введите город назначения:"),
 read(C),
 retract(flight(N,C,_,_)),
 writeln("Вы хотите продолжить удаление [y/n]?"),
 read(Sw),
 Sw=n,!.

func(4):-
 writeln("Введите инстересующий город назначения:"),
 read(C),
 writeln("Введите текущее время (24-ч. формат):"),
 read(T),
 nl,writeln("Самый дешёвый рейс, если существует (не n/a)"),
 search(C,T).

search(C,T):-
 findall(flight(N,C,T1,Pr),(flight(N,C,T1,Pr),check_time(T,T1)),Ln),
 Ln\=[],!,
 min_price(Ln,_,Res),
 write_list(Res).

search(_,_):-
 writeln("Рейс не найден").

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
