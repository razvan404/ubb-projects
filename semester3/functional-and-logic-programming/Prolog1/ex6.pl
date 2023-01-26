% a) Sa se scrie un predicat care elimina dintr-o lista toate
%    elementele care se repeta (ex: l=[1,2,1,4,1,3,4] => l=[2,3])
% b) Sa se elimine toate aparitiile elementului maxim dintr-o lista
%    de numere intregi.



% Lista = Element*
% numarAparitii(L: Lista, E: Element, A: Intreg)
% Modele de flux: (i, i, o), (i, i, i)
% L : lista de elemente
% E : elementul al carui numar de aparitii il numaram
% A : numarul de aparitii al elementului E in lista L

numarAparitii([], _, 0).
numarAparitii([E | T], E, A) :- !, numarAparitii(T, E, A1),
	A is A1 + 1.
numarAparitii([_ | T], E, A) :-
	numarAparitii(T, E, A).

% eliminaElement(L: Lista, E: Element, R: Lista)
% Modele de flux: (i, i, o), (i, i, i)
% L : lista initiala de elemente
% E : elementul pe care dorim sa il eliminam
% R : lista L din care eliminam toate aparitiile ale elementului E

eliminaElement([], _, []).
eliminaElement([E | T], E, R) :- !, eliminaElement(T, E, R).
eliminaElement([H | T], E, [H | R]) :- H \= E,
	eliminaElement(T, E, R).

% eliminaAparitiiMultipleAuxiliar(L: Lista, C: Lista, R: Lista)
% Modele de flux: (i, o), (i, i)
% L : lista initiala de elemente
% C : copie a listei initiale
% R : lista din care am eliminat elementele cu aparitii multiple

eliminaAparitiiMultiple([], C, C).
eliminaAparitiiMultiple([H | T], C, R) :- numarAparitii(C, H, A),
	A > 1, !,
	eliminaElement(C, H, L1),
	eliminaAparitiiMultiple(T, L1, R).
eliminaAparitiiMultiple([_ | T], C, R) :-
	eliminaAparitiiMultiple(T, C, R).

eliminaAparitiiMultiple(L, R) :- eliminaAparitiiMultiple(L, L, R).

% Lista = Intreg*
% elementMaxim(L: Lista, C: Intreg, M: Intreg)
% Modele de flux: (i, i, o), (i, i, i)
% L : lista de elemente
% C : variabila colectoare in care retinem maximul curent
% M : elementul maxim al listei L

elementMaxim([], C, C).
elementMaxim([H | T], C, M) :- H > C,
	elementMaxim(T, H, M).
elementMaxim([H | T], C, M) :- H =< C,
	elementMaxim(T, C, M).

% eliminaElementMaxim(L: Lista, R: Lista)
% Modele de flux: (i, o), (i, i)
% L : lista de elemente
% R : rezultatul (L fara elementul maxim)

eliminaElementMaxim([H | T], R) :- elementMaxim([H | T], H, M),
	eliminaElement([H | T], M, R).
