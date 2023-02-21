% CharList = Character*
% scrie(L: CharList)
% Model de flux: (i) determinist
% L - lista de caractere pe care dorim sa o tiparim
scrie([]).
scrie([H | T]) :-  write(H), scrie(T).

% paranteze(N: Intreg, K: Intreg, R: CharList)
% Model de flux: (i, i, o), (i, i, i) deterministe
% N - numarul de paranteze, trebuie sa fie par
% K - contor, retinem cate paranteze au fost inchise la final si trebuie
%     inchise la inceput (algoritmul functioneaza din spate in fata)
% R - lista rezultat curenta in care se afla parantezele
paranteze(0, 0, R) :- !,
	scrie(R), nl, fail.
paranteze(N, N, R) :-
	!, N1 is N - 1,
	paranteze(N1, N1, ['(' | R]).
paranteze(N, K, R) :-
	N1 is N - 1,
	K1 is K + 1,
	paranteze(N1, K1, [')' | R]).
paranteze(N, K, R) :-
	K > 0,
	N1 is N - 1,
	K1 is K - 1,
	paranteze(N1, K1, ['(' | R]).

% paranteze(N: Intreg)
% Model de flux: (i) determinist
% N - numarul de paranteze cerut
paranteze(N) :-
	N > 0,
	0 is N mod 2,
	paranteze(N, 0, []).

