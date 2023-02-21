; 12a. Definiti o functie care intoarce produsul scalar a doi vectori

;Model matematic:
; produs_scalar(a1..an, b1..bn) =
;   case n = 0 -> multimea vida
;   case n > 1 -> (a1 * a2) (+) produs_scalar(a2..an, b2..bn)

;Implementare:
; N-Vector: lista de N numere intregi
; produs_scalar(A: N-Vector, B: N-Vector)
(defun produs_scalar(A B)
    (cond
        ((or (null A) (null B)) nil)
        (t (cons (* (car A) (car B)) (produs_scalar (cdr A) (cdr B))))
    )
)

; 12b. Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la orice nivel.

;Model matematic
; maxim(l1..ln) =
;   case n = 0 -> -9999
;   case n > 1, l1 atom numeric si l1 > maxim(l2..ln) -> l1
;   case n > 1, a1 lista si maxim(l1) > maxim(l2..ln) -> maxim(l1)
;   default -> maxim(l2..ln)

;Implementare
; ListaElement: lista eterogena neliniara
; maxim(L: ListaElement)
(defun maxim(L)
    (cond
        ((null L) -9999)
        ((and (numberp (car L)) (> (car L) (maxim (cdr L)))) (car L))
        ((and (listp (car L)) (> (maxim (car L)) (maxim (cdr L)))) (maxim (car L)))
        (t (maxim (cdr L)))
    )
)

; 12c. Sa se scrie o functie care intoarce lista permutarilor unei liste date.

;Implementare
; Functie auxiliara pentru a insera un element pe o anumita pozitie:
; ins(E: Element, K: Intreg, L: ListaElement)
(defun ins(E K L)
    (cond
        ((= K 1) (cons E L))
        (T (cons (car L) (ins E (- K 1) (cdr L))))
    )
)
; Functie auxiliara care sa returneze multimea formata din listele obtinute prin inserarea unui element E pe pozitiile 1, 2, ..., lungimea listei + 1 intr-o lista
; insert(E: Element, N: Intreg, L: ListaElement)
(defun insert(E N L)
    (cond
        ((= N 0) nil)
        (T (cons (ins E N L) (insert E (- N 1) L)))
    )
)

(defun size(L)
    (cond
        ((null L) 0)
        (T (+ 1 (size (cdr L))))
    )
)

; ListaDeListaElement: Lista formata din ListaElement
; insert_in_each_list(E: Element, L: ListaDeListaElement)
(defun insert_in_each_list(E L)
    (cond
        ((null L) nil)
        (T (append (insert E (+ (size (car L)) 1) (car L)) (insert_in_each_list E (cdr L))))
    )
)

(defun permutari(L)
    (cond
        ((null L) (list nil))
        (T (insert_in_each_list (car L) (permutari (cdr L))))
    )
)

; 12d. Sa se scrie o functie care intoarce T daca o lista are numar par de elemente pe primul nivel si NIL in caz contrar, fara sa se numere elementele listei.

;Model matematic
; verifica_par(l1..ln) =
;   case n = 0 -> NIL
;   default -> verifica_par(l2..ln)

;Implementare
; Lista: lista eterogena neliniara
; maxim(L: Lista)
(defun verifica_par(L)
    (cond
        ((null L) T)
        (T (not (verifica_par (cdr L))))
    )
)
    