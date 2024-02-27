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
 writeln("Введите номер рейса (Они не должны повторяться):"),
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
 writeln("Введите время отправления (24-ч. формат)"),
 read(T),
 writeln("Введите стоимость билета"),
 read(Pr),
 retract(flight(N,C,T,Pr)),
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
 findall(N,(flight(N,C,T1,_),check_time(T,T1)),Ln),
 Ln\=[],!,
 min_price(Ln,Res),
 writeln(Res).

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

min_price([H|[]],Res):-
 flight(H,C,T,Pr),
 Res=flight(H,C,T,Pr).

min_price([H|Tail],Res):-
 flight(H,C,T,Pr1),
 Res1=flight(H,C,T,Pr1),
 min_price(Tail,Res2),
 check_price(Res1,Res2,Res).

check_price(Res1,Res2,Res):-
 Res1=flight(_,_,_,Pr1),
 Res2=flight(_,_,_,Pr2),
 Pr1<Pr2,!,
 Res=Res1.

check_price(_,Res2,Res2).

func(5):-
 tell('RGZ3.txt'),
 listing(flight/4),
 told.
 

 %flight(11, moscow, 10, 1000).
 %flight(12, novosibirsk, 5, 1200).
