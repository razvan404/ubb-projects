bits 32

global start        

extern exit, printf          
import exit msvcrt.dll  
import printf msvcrt.dll  
extern intercalare
                        

segment data use32 class=data
    ; 12. Se dau doua siruri de caractere de lungimi egale. Se cere sa se calculeze si sa se afiseze rezultatele intercalarii literelor, pentru cele doua intercalari posibile (literele din primul sir pe pozitii pare, respectiv literele din al doilea sir pe pozitii impare).
    print_format db 'Rezultatul intercalarii literelor dintre cele doua siruri date este: "%s"', 0    ; Formatul afisarii rezultatului
    not_equal_dimensions_error_format db 'Cele doua siruri nu au aceeasi dimensiune sau dimensiunile sunt egale cu 0!', 0
    S1 db 'SKrLa!o@iZfqr3c4t5!'      ; S1 = primul sir
    dimS1 equ $-S1                   ; dimS1 = dimensiunea primului sir (19)
    S2 db '2alb@t*rL %e@ili#eK'      ; S2 = cel de-al doilea sir
    dimS2 equ $-S2                   ; dimS2 = dimensiunea celui de-al doilea sir (19)
    ANS times dimS1 db 0             ; In ANS o sa retinem sirul rezultat

segment code use32 class=code
    start:
        verificare_eroare:           ; Verificam ca cele doua siruri sa nu aiba aceeasi dimensiune sau sa nu aiba 0, in caz contrar se va afisa pe ecran un mesaj de eroare
            mov EAX, dimS1
            mov EBX, dimS2
            cmp EAX, 0               ; Verificam daca dimensiunea unuia dintre siruri este 0
            je eroare
            cmp EAX, EBX
            jnz eroare               ; Verificam daca sirurile au dimensiuni diferite           
            
        operatie:                    ; Apelam functia de intercalare din modul: intercalare(ANS, S1, S2, dimS1, dimS2)
            push dword dimS2
            push dword dimS1
            push dword S2
            push dword S1
            push dword ANS
            call intercalare
            add ESP, 4 * 5
        
        afisare:                     ; Apelam functia de afisare: printf(print_format, ANS)
            push dword ANS
            push dword print_format
            call [printf]
            add ESP, 4 * 2
            jmp final                ; Ne asiguram ca programul se va incheia, fara sa afiseze vreun fel de eroare
            
        eroare:                      ; In cazul in care dam de una dintre erorile de mai sus, vom afisa un mesaj
            push dword not_equal_dimensions_error_format
            call [printf]
            add ESP, 4 * 1
         
        final:     
            push    dword 0     
            call    [exit]      
