bits 32 
global start        

extern exit, printf, scanf               
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll     

segment data use32 class=data
    ; 21. Sa se citeasca de la tastatura doua numere a si b de tip word. Sa se afiseze in baza 16 numarul c de tip dword pentru care partea low este suma celor doua numere, iar
    ; partea high este diferenta celor doua numere. Exemplu:
    ;   a = 574, b = 136
    ;   c = 01B602C6h
    ;  574 - 136 = 01B6h
    ;  574 + 136 = 02C6h
    a dw 0
    b dw 0
    c dd 0
    amesaj db "a = ", 0
    bmesaj db "b = ", 0
    readformat db "%d", 0
    printformat db "c = 0%Xh", 0
    
segment code use32 class=code
    start:
        citire_a: ;citim primul numar | printf(amesaj); scanf(readformat, a)
            push dword amesaj
            call [printf]
            add esp, 4
            push dword a
            push dword readformat
            call [scanf]
            add esp, 4 * 2
        citire_b: ;citim al doilea numar | printf(bmesaj); scanf(readformat, b)
            push dword bmesaj
            call [printf]
            add esp, 4 * 1
            push dword b
            push dword readformat
            call [scanf]
            add esp, 4 * 2
        prelucrare: ;rezolvam cerinta
            mov ax, [a]
            sub ax, [b]
            rol eax, 4 * 4
            mov ax, [a]
            add ax, [b]
            mov [c], eax      
        afisare: ;afisam numarul | | printf(printformat, c)
            push dword [c]
            push dword printformat 
            call [printf]
            add esp, 4 * 2            
        push dword 0
        call [exit]
        