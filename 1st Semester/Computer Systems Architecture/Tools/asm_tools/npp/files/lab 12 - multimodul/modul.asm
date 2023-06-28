bits 32
global intercalare

segment code use32 class=code public
    intercalare:
        ; [ESP +  0] == adresa de revenire
        ; [ESP +  4] == offset ANS
        ; [ESP +  8] == offset S1
        ; [ESP + 12] == offset S2
        ; [ESP + 16] == offset dimS1
        ; [ESP + 20] == offset dimS2
        
    prelucrare_primul_sir:
        cld
        mov EDI, [ESP + 4]            ; EDI <- ANS
        mov ESI, [ESP + 8]            ; ESI <- S1
        mov ECX, [ESP + 16]           ; ECX <- dimS1
        repeta:                       ; Parcurgem primul sir si punem elementele de pe pozitii pare in sirul rezultat
            mov EAX, [ESP + 16]       ; EAX <- dimS1
            sub EAX, ECX              ; EAX <- dimS1 - ECX (pozitia actuala in sirul S1)
            test EAX, 1               ; Verificam daca EAX este par sau impar // and EAX, 1
            jnz skip                  ; Daca pozitia este impara, vom sari peste pasul urmator
        pozitie_para:
            movsb                     ; Daca pozitia este para, vom muta in EDI octetul curent din ESI // <ES:EDI> <- <DS:ESI>, inc ESI, inc EDI
            jmp end_repeta            ; Vom sari la sfarsitul loop-ului daca pozitia este para 
        skip:                         ; Daca pozitia este para, ne asiguram ca incrementam pe ESI si pe EDI
            inc ESI
            inc EDI
        end_repeta:
            loop repeta
    
    prelucrare_al_doilea_sir:    
        mov EDI, [ESP + 4]            ; EDI <- ANS
        mov ESI, [ESP + 12]           ; ESI <- S2
        mov ECX, [ESP + 20]           ; ECX <- dimS2
        repeta2:                      ; Parcurgem al doilea sir si punem elementele de pe pozitii impare in sirul rezultat
            mov EAX, [ESP + 20]       ; EAX <- dimS2
            sub EAX, ECX              ; EAX <- dimS2 - ECX (pozitia actuala in sirul S2)
            test EAX, 1               ; Verificam daca EAX este par sau impar // and EAX, 1
            jz skip2                  ; Daca pozitia este para, vom sari peste pasul urmator
        pozitie_impara:
            movsb                     ; Daca pozitia este impara, vom muta in EDI octetul curent din ESI // <ES:EDI> <- <DS:ESI>, inc ESI, inc EDI
            jmp end_repeta2           ; Vom sari la sfarsitul loop-ului daca pozitia este impara
        skip2:                        ; Daca pozitia este impara, ne asiguram ca incrementam pe ESI si pe EDI
            inc ESI
            inc EDI
        end_repeta2:
            loop repeta2
        
    returnare:                        ; Ne asiguram ca ne intoarcem la adresa initiala
        ret