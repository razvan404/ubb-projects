bits 32
global start        

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    Tabela db '0123456789ABCDEF'
    format db '%d', 0
segment code use32 class=code
    start:
        mov EAX, 0
        mov AL, 5
        mov EBX, Tabela
        SS XLAT
        push EAX
        push format
        call [printf]
        push    dword 0   
        call    [exit]     