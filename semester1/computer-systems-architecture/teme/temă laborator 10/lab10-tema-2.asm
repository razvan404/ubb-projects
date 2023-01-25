bits 32

global start        

extern exit              
import exit msvcrt.dll   
                     
extern exit, fopen, fprintf, fclose, fscanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll 
import fprintf msvcrt.dll 
import fscanf msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 
                          
                        
segment data use32 class=data
    ;21. Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, cifre si spatii. Sa se inlocuiasca toate cifrele de pe pozitii impare cu caracterul ‘X’. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.
    file db "file.txt", 0
    write db "w", 0
    descriptor dd -1
    text db "as94cr 1431123 c53r41", 0 ; dupa compilare, textul va trebui sa fie "as9Xcr X4X1X2X c5XrX1"
    len equ $-text
    format db "%s", 0
    aux dd 0
    
segment code use32 class=code
    start:
    
        deschidere: ;eax = fopen(file, write)
            push dword write
            push dword file
            call [fopen]
            add esp, 4 * 2
        
        verificare_deschidere: ; verificam daca s-a deschis fisierul
            cmp eax, 0 
            je final
            mov [descriptor], eax
        
        parcurgere_text: ;parcurgem textul de la stanga la dreapta
            cld
            mov ecx, len
            mov esi, text
            mov edi, 0
        
        repeta:
            lodsb ;se salveaza in al caracterul
            cmp al, '0' ;verificam daca este un numar
            jge numar
            jl end_repeta
                
        numar: ;verificam daca este cifra
            cmp al, '9' 
            jle cifra
            jg end_repeta
                    
        cifra: ;verificam daca pozitia este impara
            test edi, 1 
            jnz pozitie_impara
            jz end_repeta
                    
        pozitie_impara: ;se indeplinesc toate cerintele, deci inlocuim caracterul curent cu X
            mov [aux], edi
            mov edi, esi
            mov al, 'X'
            dec edi
            stosb ; [ES:EDI]<-AL si add EDI, 1
            mov edi, [aux]                 
            jmp end_repeta
            
        end_repeta: ;parcurgem in continuare textul, trebuie incremenetat edi
            inc edi
            loop repeta
        
        salvare_fisier: ;fprintf(descriptor, format, var)
            push dword text
            push dword format
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
        
        final: ;inchidem fisierul
            push dword [descriptor]
            call [fclose]
        
        push    dword 0     
        call    [exit]      