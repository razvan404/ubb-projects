; B 
bits 32
global start        

extern exit, scanf, printf, fopen, fprintf, fclose     
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll   

segment data use32 class=data
    n dd 0
    text_n db 'Give the length of the array: ', 0
    format_n db '%d', 0
    curent dd 0
    text_array db 'Give the array: ', 0
    format_curent db '%d', 0
    format_fprint db '%d ', 0
    next_line db 10, 0
    x dd 0
    patru dd 4
    file_name db 'iesire.txt', 0
    write_mode db 'w', 0
    descr dd -1
    copy_ecx dd 0
    right_bound dd -99
    left_bound dd -11111
    
segment code use32 class=code
    start:
    
    open_file:
        push dword write_mode
        push dword file_name
        call [fopen]
        add esp, 8
        mov dword[descr], eax
        cmp eax, 0
        je final
    
    read_n:
        push dword text_n
        call [printf]
        add esp, 4
        push dword n
        push dword format_n
        call [scanf]
        add esp, 8
    
    array:
        push dword text_array
        call [printf]
        add esp, 4
        mov ecx, [n]
        mov ebx, 0
        cld
        jecxz close_file
        
    read_array:
        mov dword[copy_ecx], ecx
        push dword curent
        push dword format_curent
        call [scanf]
        mov eax, [curent]
        add esp, 8
        
        cmp eax, [right_bound]
        jg repeat_read_array
        
        cmp eax, [left_bound]
        jl repeat_read_array        
        
        cdq
        idiv dword[patru]
        cmp edx, 0
        jne repeat_read_array
        
        add ebx, [curent]
        
        push dword[curent]
        push dword format_fprint
        push dword[descr]
        call [fprintf]
        add esp, 12
        
        push dword next_line
        push dword[descr]
        call [fprintf]
        add esp, 12
        
    repeat_read_array:
        mov ecx, dword[copy_ecx]
        loop read_array
        
        
    close_file:
        push dword[descr]
        call [fclose]
        add esp, 4
    
    save_x:
        mov dword[x], ebx
        push dword[x]
        push dword format_n
        call [printf]
        add esp, 8
        
    final:
        push    dword 0   
        call    [exit]      
