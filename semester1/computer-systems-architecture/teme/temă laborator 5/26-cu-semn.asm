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
    c dw -5
    b db 15
    d dd -186
    x dq 125

; our code starts here
segment code use32 class=code
    start:
        ; 26 cu semn. (a*a+b/c-1)/(b+c)+d-x
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        mov edx, 0
        mov ax, [a]
        imul word [a]
        mov bx, ax
        mov cx, dx; cx:bx = a * a
        
        mov al, [b]
        cbw
        cwde
        idiv word [c]; ax = b / c         
        mov dx, 0
        add ax, bx
        adc dx, cx; dx:ax = a*a+b/c
        sub ax, 1; dx:ax = a*a+b/c-1
        sbb dx, 0
        
        mov bl, [b]
        movsx bx, bl
        add bx, [c] ;bx = b + c
        idiv bx ; ax = (a*a+b/c-1)/(b+c)
        cwde
        
        
        add eax, [d]
        cdq
        sub eax, dword [x]
        sbb edx, dword [x + 4]; edx:eax = (a*a+b/c-1)/(b+c)+d-x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
