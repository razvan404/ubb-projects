bits 32

global _min

segment data public data use32

segment code public code use32
    _min:                            ; functia este apelata in main astfel: min(int n, int *s)
        push       ebp
        mov        ebp, esp
                                     ; [ebp + 4] se va afla adresa de return
                                     ; [ebp] se afla valoarea ebp pentru apelant
        mov        ecx, [ebp + 8]    ; [ecx] = n
        jecxz      .final            ; daca este 0 vom sari peste urmatorii pasi pentru a evita un loop inutil
        cld                          ; ne asiguram ca direction flag este setat la 0
        mov        esi, [ebp + 12]   ; esi va pointa spre adresa elementului s[0]
        LODSD                      ; eax <- s[0], esi va pointa spre adresa elementului s[1]
        mov        ebx, eax          ; in ebx vom retine minimul, initial minimul va fi chiar primul element
        dec        ecx               ; decrementam ecx deoarece primul element al sirului a fost deja prelucrat
        jecxz      .save_the_result  ; in cazul in care sirul are un singur element, vom merge direct sa salvam rezultatul in eax pentru a evita un loop inutil
        
    .find_min:
        LODSD                        ; eax <- s[i], esi va pointa spre adresa elementului s[i], i reprezinta la al catelea loop este programul
        cmp        ebx, eax          ; comparam minimul cu elementul curent
        jle        .repeat_find      ; daca minimul este deja mai mic sau egal cu elementul curent, vom repeta loop-ul
        mov        ebx, eax          ; daca elementul curent este mai mic decat minimul, minimul va fi inlocuit cu noul minim
        
    .repeat_find:
        loop       .find_min         ; repetam instructiunea find_min pana cand ecx va fi 0, adica cand terminam de parcurs sirul
        
    .save_the_result:
        mov        eax, ebx          ; vom muta in eax rezultatul deoarece modulul .asm prin acest registru va returna rezultatul
    
    .final:
        mov        esp, ebp        
        pop        ebp
        ret
