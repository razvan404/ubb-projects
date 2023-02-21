bits 32


global start        

extern exit, fopen, fprintf, fclose, scanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll 
import fprintf msvcrt.dll 
import scanf msvcrt.dll 
import fclose msvcrt.dll 
import printf msvcrt.dll 

segment data use32 class=data
    a dd 0
    aux dd 0
    format db "%c", 0
    format2 db "%d", 0
segment code use32 class=code
    start:
        push dword a
        push dword format2
        call [scanf]
        add ESP, 4 * 2
        
        mov EAX, [a]
        
        push EAX
        push dword format2
        call [printf]
        add ESP, 4 * 1
        pop EAX
        add ESP, 4 * 1
          
        push EAX
        push dword format
        call [printf]
        add ESP, 4 * 1
        pop EAX
        add ESP, 4 * 1
        
    push    dword 0     
    call    [exit]   