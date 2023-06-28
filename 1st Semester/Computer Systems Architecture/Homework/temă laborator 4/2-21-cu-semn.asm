bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a-byte; b-word; e-doubleword; x-qword
    a db 3
    b dw -3
    e dd 186
    x dq -125

; our code starts here
segment code use32 class=code
    start:
        ; 21 fara semn. (a*a/b+b*b)/(2+b)+e-x 
        mov eax, 0
        mov al, [a]
        imul byte [a] ; ax = a * a
        
        mov edx, 0
        idiv word [b]; ax = a * a / b 
        
        mov ebx, 0
        mov bx, ax ;bx = a * a / b

        mov ax, [b]
        imul word [b] ; dx:ax = b * b
        add ax, bx ; dx:ax = (a * a / b + b * b)
        
        mov bx, 2
        add bx, [b] ; bx = 2 + b
        idiv bx ; ax = (a*a/b+b*b)/(2+b)
        add eax, [e] ; eax = (a*a/b+b*b)/(2+b)+e
        add eax, dword [x]
        adc edx, dword [x + 4]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
