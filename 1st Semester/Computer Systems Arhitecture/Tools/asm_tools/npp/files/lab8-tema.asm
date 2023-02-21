bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 29. Se dau doua siruri de octeti. Sa se parcurga cel mai scurt sir dintre cele doua siruri si sa se construiasca un al treilea sir care va contine cel mai mare element de acelasi rang din cele doua siruri, iar pana la lungimea celui mai lung sir, sirul al treilea se va completa alternativ cu valoarea 1 respectiv 0. (fara comenzi speciale)
    s1 db 2, 1, 3, 7, -4, 2, 6, 7, 8, 2, 15, -18, 13 ; 02 01 03 07 FC 02 06 07 08 02 0F EE 0D
    len1 equ $-s1                                    ; lungimea lui s1
    s2 db 4, 1, 5, 6, -6, 2, 8, -8                   ; 04 01 05 06 FA 02 08 F8
    len2 equ $-s2                                    ; lungimea lui s2
    d times len1 + len2 db 0                         ; 04 01 05 07 FC 02 08 07 01 00 01 00 01   

; our code starts here
segment code use32 class=code
    start:
        mov esi, 0                                   ; vom folosi pe esi drept contor
        mov ebx, 1                                   ; in ebx vom retine valoarea alternantei cu care se va completa sirul la final
        mov edx, len1
        cmp edx, len2                                ; comparam lungimea primului sir cu al doilea
        jge first
        jb second
        
        first:                                       ; daca primul sir este mai mare, eax <- dimensiunea sirului mai scurt (S2) | ecx <- dimensiunea sirului mai lung (S1)
            mov ecx, len1
            mov eax, len2
            jmp repeta
            
        second:                                      ; daca al doilea sir este mai mare, eax <- dimensiunea sirului mai scurt (S1) | ecx <- dimensiunea sirului mai lung (S2)
            mov ecx, len1
            mov eax, len2
        
        repeta:
            cmp esi, eax                             ; comparam esi cu eax pentru a vedea care dintre cerintele enuntului trebuie facute
            jb task1
            jge task2
        
        task1:                                       ; pentru prima cerinta, comparam elementele de pe pozitia esi din ambele siruri, iar pe cel mare il vom atasa sirului d
            mov dl, [s2 + esi]
            cmp [s1 + esi], dl
            jge fromS1
            jl fromS2
        
        fromS1:                                      ; daca elementul de pe pozitia esi din primul sir este mai mare, il vom atasa sirului d
            mov dl, [s1 + esi]
            mov [d + esi], dl
            inc esi
            jmp end_repeta
        
        fromS2:                                      ; daca elementul de pe pozitia esi din al doilea sir este mai mare, il vom atasa sirului d
            mov dl, [s2 + esi]
            mov [d + esi], dl
            inc esi
            inc edi
            jmp end_repeta
        
        task2:                                       ; pentru a doua cerinta, vom atasa sirului d elementul 1 sau 0, in functie de pozitia la care am ajuns
            mov [d + esi], ebx                       ; atasam pe ebx pe sirul d
            inc esi
            cmp ebx, 0                               ; comparam pe ebx cu 0 sa vedem ce urmeaza sa atasam
            jbe become1
            jg become0
        
        become1:                                     ; daca ebx este 0, atunci o sa devina 1
            mov ebx, 1
            jmp end_repeta

        become0:                                     ; daca ebx este 1, atunci o sa devina 0
            mov ebx, 0        
        
        end_repeta:
            loop repeta
        
    end:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
