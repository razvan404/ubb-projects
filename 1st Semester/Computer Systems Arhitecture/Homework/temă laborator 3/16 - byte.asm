bits 32 

global start        

extern exit               
import exit msvcrt.dll 
   
segment data use32 class=data
    ; ...

    a db 10
    b db 30
    c db 20
    d db 13

segment code use32 class=code
    start:
        ; BYTE - 16. a + 13 - c + d - 7 + b, byte 
        mov eax, 0
        add al, [a]
        add al, 13
        sub al, [c]
        add al, [d]
        sub al, 7
        add al, [b]

        push    dword 0      
        call    [exit] 
