bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 29. Se dau doua siruri de octeti. Sa se parcurga cel mai scurt sir dintre cele doua siruri si sa se construiasca un al treilea sir care va contine cel mai mare element de acelasi rang din cele doua siruri, iar pana la lungimea celui mai lung sir, sirul al treilea se va completa alternativ cu valoarea 1 respectiv 0. (cu comenzi speciale)
    s1 db 2, 1, 3, 7, -4, 2, 6, 7, 8, 2, 15, -18, 13 ; 02 01 03 07 FC 02 06 07 08 02 0F EE 0D
    len1 equ $-s1                                    ; lungimea lui s1
    s2 db 4, 1, 5, 6, -6, 2, 8, -8                   ; 04 01 05 06 FA 02 08 F8
    len2 equ $-s2                                    ; lungimea lui s2
    d times len1 + len2 db 0                         ; 04 01 05 07 FC 02 08 07 01 00 01 00 01
    doi db 2    
    mare dd 0
    mic dd 0

; our code starts here
segment code use32 class=code
    start:                                    
        mov edx, len1                                
        cmp edx, len2                                ; verificam lungimea carui sir este mai mare
        jge first
        jb second
        
        first:                                       ; in mic vom retine lungimea sirului mai scurt, iar in mare lungimea sirului mai lung | in d o sa copiam sirul s2
            mov ecx, len2
            mov [mic], ecx            
            mov eax, len1
            mov [mare], eax          
            
            mov esi, s2                              ; in esi vom retine sirul mai scurt, in edi vom retine sirul rezultat, iar in ebp facem o copie a sirului mai lung
            mov edi, d
            mov ebp, s1
            
            jmp copy_loop
            
        second:                                      ; in mic vom retine lungimea sirului mai scurt, iar in mare lungimea sirului mai lung | in d o sa copiam sirul s1
            mov ecx, len1
            mov [mic], ecx
            mov eax, len2
            mov [mare], eax
            
            mov esi, s1                              ; in esi vom retine sirul mai scurt, in edi vom retine sirul rezultat, iar in ebp facem o copie a sirului mai lung
            mov edi, d
            mov ebp, s2
            
        copy_loop:                                   ; copiam in d sirul mai lung
            lodsb
            stosb   
            
        end_copy_loop:
            loop copy_loop
  
        mov esi, ebp                                 ; acum cu ajutorul esi vom parcurge sirul mai lung pe dimensiunea sirului mai scurt
        mov edi, d
        mov ecx, [mic]                           
        
        repeta:                                      ; verificam daca un element din sirul mai lung este mai mare decat un element din sirul mai scurt de pe aceeasi pozitie
            lodsb
            dec esi
            cmpsb                            
            jg task
            jle end_repeta
            
        task:                                        ; daca este, vom pune in d acel element
            dec edi        
            stosb
            
        end_repeta:
            loop repeta
                        
        mov al, 1    
        mov ecx, [mare]
        sub ecx, [mic]
            
        repeta2:                                     ; pentru a doua cerinta, vom atasa sirului d elementul 1 sau 0, in functie de pozitia la care am ajuns 
            stosb                         
            add al, 1
            mov ah, 0
            div byte[doi]
            mov al, ah
            
        end_repeta2:
            loop repeta2

        
    end:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
