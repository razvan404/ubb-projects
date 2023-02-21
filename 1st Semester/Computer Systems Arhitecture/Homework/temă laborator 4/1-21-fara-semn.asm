bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a, b, c - byte; d - word
    a db 3
    b db 4
    c db 2
    d dw 12

; our code starts here
segment code use32 class=code
    start:
        ; 21 fara semn. d - [3 * (a + b + 2) - 5 * (c + 2)] 
        mov eax, 0
        mov ebx, 0
        mov al, [a]
        add al, [b]
        add al, 2 ; al = a + b + 2
        mov ah, 3
        mul ah ; ax = 3 * (a + b + 2)
        mov bx, ax ; bx = 3 * (a + b + 2)
        mov ax, 0
        mov al, [c]
        add al, 2
        mov ah, 5
        mul ah ; ax = 5 * (c + 2)
        sub bx, ax ; bx = [3 * (a + b + 2) - 5 * (c + 2)]
        mov ax, [d]
        sub ax, bx ; ax = d - [3 * (a + b + 2) - 5 * (c + 2)] 
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
