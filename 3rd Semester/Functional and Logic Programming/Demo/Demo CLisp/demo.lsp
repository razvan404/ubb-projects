;primul element dintr-o lista
; ( (1 2) 3) --> (1 2)
(defun f(l)
   (car l)
)
;suma atomilor de la nivelul superficial al unei liste numerice
; (1 (2 (3 4) 5) 1) -->2
(defun s(l)
  (cond
     ((null l) 0)
     ((atom (car l)) (+ (car l) (s (cdr l))))
     (t (s (cdr l)))
  )
)

;sa se calculeze suma atomilor numerici dintr-o lista neliniara 
;(la toate nivelurile)   (1 (2 a (3 4) b 5) c 1) --> 16

(defun suma(l)
  (cond
     ((null l) 0)
     ((numberp (car l)) (+ (car l) (suma (cdr l))))
     ((atom (car l)) (suma (cdr l)))
     (t (+ (suma (car l)) (suma (cdr l))))
  )
)

;sa se numere de cate ori apare un element intr-o lista (la orice nivel)

(defun nrap(e l)
   (cond
     ((null l) 0)
     ((equal (car l) e) (+ 1 (nrap e (cdr l))))
     ((atom (car l)) (nrap e (cdr l)))
     (t (+ (nrap e (car l)) (nrap e (cdr l))))
   )
) 

; pentru CLisp
;    (ed)  - intrare in editor
;    (load 'nume)   - incarcare fisier "nume.lsp" 
;    (exit) - parasire mediu 
;    evaluarea functiei nrap: (nrap '1 '(2 f 1 (c 4 1)))--> 2    

