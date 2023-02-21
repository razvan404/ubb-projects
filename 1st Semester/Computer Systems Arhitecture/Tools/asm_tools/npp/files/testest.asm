bits 32

global start

extern exit, printf, scanf, strlen
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import strlen msvcrt.dll

segment data use32 class=data
    format db '%d', 0
segment code use32 class=code
    start:
        mov eax, 5
        push eax
        push dword [esp]
        push dword format
        call [printf]
        
    final:
        push dword 0
        call [exit]
       