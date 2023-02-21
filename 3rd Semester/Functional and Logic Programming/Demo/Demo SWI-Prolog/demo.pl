% Sa se calculeze suma elementelor pare dintr-o lista cu elemente numerice.

% sumaPar(L: lista, R: integer)
% L - lista de numere pentru care calculam suma numerelor pare
% R - rezultatul
% model de flux (i,o) sau (i,i)

sumaPar([],0):-!. % daca lista este vida, suma este 0. ! - taietura- se ignora restul clauzelor
sumaPar([A|L],S):-  %impartim lista in doua (capul A si coada L)
    A mod 2=:=0,
    sumaPar(L,S1), % calculam suma numerelor pare din restul listei
    S is A+S1,!. % rezultatul final este rezultatul apelului recursiv plus primul element
sumaPar([_|L],S):- % impartim lista in doua, dar nu ne intereseaza primul element (_ in loc de nume)
    sumaPar(L,S).

% Apel la executie:   sumaPar([1,2,3,4],S).
% se va afisa solutia  S=6

% -------------------------------------------------------------------------------
% Se da o lista formata din liste de numere intregi. Se cere sublista de
% suma maxima.

%suma(L:lista, R:integer)
%L - lista de numere pentru care calculam suma numerelor
%R - rezultatul
%model de flux (i,o) sau (i, i)
suma([],0):-!.
suma([A|L],S):-
    suma(L,S1),
    S is A+S1.

%sublista(L:lista de lista, R: lista)
%L - lista de liste
%R - sublista cu suma maxima din L
%model de flux (i,o), (i, i)

sublista([],[]):-!.
sublista([L1|L2],L1):- % impartim lista in doua (capul L1 si coada L2), dar acum L1 reprezinta o lista
    sublista(L2,L3), %maximul pentru restul listei e L3
    suma(L1,S1),
    suma(L3,S2), % calculam sumele pentru maximul din restul listei si capul listei
    S1>S2,!. % capul listei (L1) va fi solutia daca suma pentru L1 e mai mare ca suma pentru restul listei
  sublista([_|L],L1):-
    sublista(L,L1).

% Apel la executie sublista([[1,2],[-1,4]],L1).
%      se va afisa L1=[-1,5]

% ------------------------------------------------------------------------
% Se da o lista formata din simboluri. Se cere al n-lea element al listei.

% mylength(L:lista, R:integer) - length e functie predefinita in
% SWI-Prolog, ne trebuie alta denumire
% L - lista de simboluri
% R - rezultatul, lungimea listei
% model de flux (i, o), (i, i)
%
mylength([],0):-!.
mylength([_|L],M):-
    mylength(L,M1),
    M=M1+1.

%run(L: lista)
%L - lista de simboluri
%model de flux (i)
run(L):-
    write("N="),
    read(N),
    tipar(L,N).

%tipar(L: lista, N: integer)
%L - lista de simboluri
%N - pozitia de pe care vrem sa afisam simbolul
% model de flux (i, i)
tipar(L,N):-
    length(L,M),
    N>M,
    write("nu exista element"),
    nl,!.
tipar(L,N):-
    select(L,N,S),
    write("ELEMENT "),
    write(S),
    nl.

%select(L: lista, N: integer, S: simbol)
%L - lista de simboluri
%N - pozitia de pe care vrem sa returnam simbolul
%S - rezultatul
%model de flux (i, i, o),(i,i,i)
select([A|_],1,A):-!.
select([_|L],N,S):-
    N1 is N-1,
    select(L, N1, S).

% Apel la executie
% run ([a,b,c,d]).
%       N=2. (atentie, puneti punct dupa ce introduceti pozitia!)
% se va afisa ELEMENT b
