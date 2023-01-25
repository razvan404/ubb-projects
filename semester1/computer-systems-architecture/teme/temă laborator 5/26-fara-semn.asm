bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a, c - word; b - byte; d - doubleword; x - qword
    a dw 9
    c dw 5
    b db 15
    d dd 186
    x dq 125
; our code starts here
segment code use32 class=code
    start:
        ; 26 fara semn. (a*a+b/c-1)/(b+c)+d-x
        mov eax, 0
        mov ax, [a]
        mul word [a] ; dx:ax = a * a
        mov bx, ax
        mov cx, dx; cx:bx = a * a
        
        mov dx, 0
        mov ax, 0
        mov al, [b]
        div word [c]; ax = b / c        
        add ax, bx
        adc dx, cx; dx:ax = a*a+b/c
        sub ax, 1
        sbb dx, 0; dx:ax = a*a+b/c-1
        
        mov ebx, 0
        mov bl, [b]
        add bx, [c] ;bx = b + c
        div bx ; ax = (a*a+b/c-1)/(b+c)

        movzx eax, ax
        add eax, [d]
        mov edx, 0
        sub eax, dword [x]
        sbb edx, dword [x + 4]; edx:eax = (a*a+b/c-1)/(b+c)+d-x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
