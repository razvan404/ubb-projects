bits 32 

global start        

extern exit, fopen, fprintf, fclose, scanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll 
import fprintf msvcrt.dll 
import scanf msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 

segment data use32 class=data
    write db "w", 0
    file db "output.txt", 0
    descriptor dd -1
    format db "%d", 0
    mod_acces db "w", 0
    N dd 0
    Curent dd 0
    P dd 0
    I dd 0
segment code use32 class=code
    start:
        deschidere_fisier:
            push dword write
            push dword file
            call [fopen]
            add ESP, 4 * 2
            cmp EAX, 0
            je final
            mov [descriptor], EAX
            
        citireN: ; scanf(format, n)
            push dword N
            push dword format
            call [scanf]
            add ESP, 4 * 2
        
        mov ECX, [N]
        jecxz final
            
        rezolva:
            citireCurent:
                push ECX
                push dword Curent
                push dword format
                call [scanf]
                add ESP, 4 * 2  
                pop ECX
            paritate:
                mov EAX, [Curent]
                test EAX, 1
                jz par
                jnz impar
            par:
                add dword[P], EAX
                jmp loop_rezolva
            impar:
                add dword[I], EAX
        loop_rezolva:
            loop rezolva        
        
        mov EAX, [P]
        sub EAX, [I]
        
        tiparire_fisier: ; fprintf(descriptor, format, var)
            push dword EAX
            push dword format
            push dword [descriptor]
            call [fprintf]
            add ESP, 4 * 3
        
        final:
            push dword [descriptor]
            call [fclose]
            
            push    dword 0     
            call    [exit]     
