; 3. Sa se construiasca o functie care verifica daca un atom e membru al unei liste nu neaparat liniara.

; Model matematic pentru functia apply-or:
;   apply_or(l1..ln) =  fals, n = 0
;                       adevarat, l1 = adevarat
;                       apply_or(l2..ln), altfel

; apply_or(L: lista booleana)
; L: lista booleana pe care se vrea a fi aplicata operatia OR intre elemente
(defun apply_or(LST)
    (cond
        ((null LST) nil)
        ((car LST) t)
        (t (apply_or (cdr LST)))
    )
)

; Model matematic pentru functia is_member:
;   is_member(e, l) =  true, e = l
;                      false, l este atom si e != l
;                      OR aplicat pe sirul {is_member(e, li)} cu i = 1..n,
;                                   atunci cand l este lista, unde l = l1..ln

; is_member(ELEM: atom, LST: lista neliniara)
; ELEM: atomul pe care il cautam in lista L
; LST: lista in care cautam elementul 
(defun is_member(ELEM LST)
    (cond
        ((eq ELEM LST) t)
        ((atom LST) nil)
        (t (apply_or (mapcar #'(lambda (X) (is_member ELEM X)) LST)))
    )
)
