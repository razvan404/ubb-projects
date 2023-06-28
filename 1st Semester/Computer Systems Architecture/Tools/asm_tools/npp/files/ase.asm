bits 32

global start        

extern exit, printf          
import exit msvcrt.dll  
import printf msvcrt.dll  
                        

segment data use32 class=data
    ;12. Se dau doua siruri de caractere de lungimi egale. Se cere sa se calculeze si sa se afiseze rezultatele intercalarii literelor, pentru cele doua intercalari posibile (literele din primul sir pe pozitii pare, respectiv literele din primul sir pe pozitii impare).
    S1 db 'as531$xR4'           ;S1 = primul sir
    dimS1 equ $-S1              ;dimS1 = dimensiunea primului sir (9)
    S2 db '90y5z%@kK'           ;S2 = cel de-al doilea sir
    dimS2 equ $-S2              ;dimS2 = dimensiunea celui de-al doilea sir (9)
    ANS times dimS1 db 0        ;Ar trebui sa se afiseze: a0551%xk4%s
    print_format db '%s', 0    ;Formatul afisarii rezultatului

segment code use32 class=code
    start:       
        operatie:               
        cld
        mov EDI, ANS
        mov ESI, S1
        mov ECX, dimS1
        jecxz final
        
        repeta:
            mov EAX, dimS1
            sub EAX, ECX
            test EAX, 1
            jnz skip           
            movsb
            jmp end_repeta
        skip:
            inc ESI
            inc EDI
        end_repeta:
            loop repeta
        
        mov EDI, ANS
        mov ESI, S2
        mov ECX, dimS2
        jecxz final
        
        repeta2:
            mov EAX, dimS2
            sub EAX, ECX
            test EAX, 1
            jz skip2 
            movsb
            jmp end_repeta2
        skip2:
            inc ESI
            inc EDI
        end_repeta2:
            loop repeta2
        
        afisare:                ;printf(print_format, ANS)
            push dword ANS
            push dword print_format
            call [printf]
            add ESP, 4 * 2
            jmp final        
        
        final:
            push    dword 0     
            call    [exit]      
