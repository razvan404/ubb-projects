% 8. a) Definiti un predicat care determina succesorul unui numar
% reprezentat cifra cu cifra intr-o lista. De ex: [1 9 3 5 9 9] => [1 9
% 3 6 0 0]
%    b) Se da o lista eterogena, formata din numere intregi si
% liste de cifre. Pentru fiecare sublista sa se determine succesorul
% numarului reprezentat cifra cu cifra de lista respectiva. De ex: [1,
% [[2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [1, [2, 4], 4, 5,
% [6, 8, 0], 10, 11, [1, 2, 1], 6]



%Lista = Intreg+ (minim 1)
%succesor_aux(L: Lista, F: Intreg, R: lista)
%Model de flux: (i, o), (i, i) deterministe
% L: lista initiala de numere intregi
% R: lista rezultat care va fi succesorul listei initiale

succesor_aux([], [1]).
succesor_aux([H | T], [F, H1 | R]) :-
	succesor_aux(T, [F1 | R]),
	H1 is (H + F1) mod 10,
	F is (H + F1) div 10.

%Lista = Intreg+
%succesor(L: Lista, R: Lista)
%Model de flux: (i, o), (i, i) deterministe
% L: lista initiala de nr intregi
% R: lista rezultata din incrementarea listei initiale

succesor(L, R) :-
	succesor_aux(L, [0 | R]), !.

succesor(L, R) :-
	succesor_aux(L, R).

%ListaEter = (Intreg/Lista/ListaVida)*
%succesorListe(L: ListaEter, R: ListaEter)
% L: lista eterogena initiala
% R: lista rezultata din incrementarea sublistelor din lista initiala

succesorListe([], []).

succesorListe([H | T], [H1 | R]) :-
	is_list(H),
	H \= [], !,
	succesor(H, H1),
	succesorListe(T, R).

succesorListe([H | T], [H | R]) :-
	succesorListe(T, R).










