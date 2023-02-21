bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se dau doua siruri de caractere S1 si S2. Sa se construiasca sirul D prin concatenarea elementelor de pe pozitiile multiplu de 3 din sirul S1 cu elementele sirului S2 in ordine inversa.
    s1 db '+', '4', '2', 'a', '8', '4', 'X', '5'                 ; s1 reprezinta primul sir, il vom contoriza cu ajutorul esi
    len1 equ $-s1                                                ; in len1 vom retine lungimea sirului s1
    s2 db 'a', '4', '5'                                          ; s2 reprezinta al doilea sir, il vom contoriza cu ajutorul esi
    len2 equ $-s2                                                ; in len 2 vom retine lungimea sirului s2
    d times len1 / 3 + len2 + 1 db 0                             ; d reprezinta sirul destinatie, in care vom retine solutia, il vom contoriza cu ajutorul edi
    trei db 3

; our code starts here
segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0
        mov ecx, len1                                            ; pregatim parcurgerea primului sir
        repeta1:
            mov bl, [s1 + esi]                                   ; in bl se va retine elementul la care suntem in primul sir
            mov eax, 0
            mov eax, esi                                         ; in eax il vom retine pe esi pentru a putea sa verificam daca restul impartirii contorului la 3 este 0
           
            div byte[trei]                                       ; in al, ah va fi retinut catul, respectiv restul la impartirea lui ax cu 3
            cmp ah, 0                                            ; comparam resutl impartirii lui 3 cu 0 si vom avea 2 cazuri: cand este divizibil si cand nu                         
            JE divizibil                
            JNE nedivizibil
                 
                 divizibil:                                      ; daca este divizibil, la d atasam elementul corespunzator pozitiei si incrementam pe edi si pe esi
                     mov [d + edi], bl
                     inc edi
                     inc esi        
                 JMP end_repeta1
                 nedivizibil:                                    ; daca nu este divizibil, doar vom incrementa pe esi
                     inc esi                                     
        end_repeta1:
        loop repeta1
         
        mov esi, 0
        mov ecx, len2                                            ; pregatim parcurgerea celui de-al doilea sir
        repeta2:
            mov ebp, len2
            sub ebp, 1
            sub ebp, esi                                         ; ebp = len2 - 1 - esi
            mov bl, [s2 + ebp]                                   ; in bl vom lua al 'ebp'-lea element din al doilea sir, adica al 'esi'-lea element in ordine inversa
            mov [d + edi], bl                                    
            inc edi                                                  
            inc esi                                              ; la d atasam elementul din bl si incremenetam pe edi si pe esi
        end_repeta2:
        loop repeta2 
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
