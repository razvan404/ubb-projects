% 6. Sa se genereze toate sirurile de n paranteze ce se inchid corect.
% Exemplu: n=4 sunt 2 solutii: (()) si ()()

% CharList = Character*
% scrie(L: CharList)
% Model de flux: (i) determinist
% L - lista de caractere pe care dorim sa o tiparim
scrie([]).
scrie([H | T]) :-  write(H), scrie(T).

% paranteze(N: Intreg, K: Intreg, R: CharList)
% Model de flux: (i, i, o), (i, i, i) deterministe
% N - numarul de paranteze ce trebuie sa fie afisat, trebuie sa fie un
%     numar par
% K - numarul curent de paranteze care nu au fost inca inchise, atunci
%     cand va ajunge la 0 inseamna ca toate parantezele au fost inchise
% R - lista rezultat formata din caractere de tip paranteza deschisa sau
%     inchisa, care respecta cerinta problemei
paranteze(0, 0, []) :- !.

paranteze(N, N, [')' | R]) :- !,
	N1 is N - 1,
	paranteze(N1, N1, R).

paranteze(N, K, ['(' | R]) :-
	N1 is N - 1,
	K1 is K + 1,
	paranteze(N1, K1, R).

paranteze(N, K, [')' | R]) :-
	K > 0,
	N1 is N - 1,
	K1 is K - 1,
	paranteze(N1, K1, R).

% paranteze(N: Intreg)
% Model de flux: (i) determinist
% N - numarul de paranteze ce trebuie sa fie afisat conform cerintei
paranteze(N) :-
	0 < N,
	0 is N mod 2,
	paranteze(N, 0, R),
	scrie(R), nl, fail.
