bits 32 

global start        

extern exit               
import exit msvcrt.dll 
   
segment data use32 class=data
    ; ...

    a dw 9
    b dw 5
    c dw 7
    d dw 3

segment code use32 class=code
    start:
        ;WORD - 19. b + a - (4 - d + 2) + c + (a - b) 
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        ;(4 - d + 2)
        add bx, 4
        sub bx, [d]
        add bx, 2
        ;(a - b)
        add cx, [a]
        sub cx, [b]
        ;b + a - (4 - d + 2) + c + (a - b)
        add ax, [b]
        add ax, [a]
        sub ax, bx
        add ax, [c]
        add ax, cx

        push    dword 0      
        call    [exit] 
