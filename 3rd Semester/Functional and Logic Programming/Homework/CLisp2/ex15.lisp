; 15.  Sa se construiasca lista nodurilor unui arbore de tipul (1) parcurs in postordine.

;Functie pentru a gasi subarborele stang
; find_left_subtree (l1..ln) =
;	    multimea vida, daca n = 0
;	    l3..ln, daca l2 > 0
;       multimea vida, altfel
(defun find_left_subtree (L)
    (cond
        ((null L) nil)
        ((> (cadr L) 0) (cddr L))
        (T nil)
    )
)

;Functie pentru a gasi subarborele drept 
; find_right_subtree_aux(l1..ln, step) =
;       l1..ln, step = 0
;       right-aux(l3..ln, step + l2 - 1), l1 este numar
(defun find_right_subtree_aux (L step)
    (cond
        ((eq step 0) L)
        ((find_right_subtree_aux (cddr L) (- (+ step (cadr L)) 1)))
    )
)

;Functie pentru a gasi subarborele drept (wrapper pentru find_right_subtree_aux)
; find_right_subtree(l1..ln) =
;       multimea vida, l2 = 0
;       find_right_subtree_aux(l3..ln), atlfel
(defun find_right_subtree (L)
    (cond
        ((= (cadr l) 0) nil)
        (T (find_right_subtree_aux (cddr L) 1))
    )
)

;Functie pentru a parcurge un arbore in postordine
; inorder traversal(l1..ln)=
;				NIL, n = 0
;				inorder(find_left_subtree(tree)) U inorder(get_right(tree)) U l1 
(defun postorder (L)
    (cond
        ((null L) nil)
        (T (append (postorder (find_left_subtree L)) (postorder (find_right_subtree L)) (list (car L))))
    )
)

(print (postorder '(A 2 B 0 C 2 D 0 E 0)))
(print (postorder '(A 2 B 0 C 2 D 0 E 1 F 0)))