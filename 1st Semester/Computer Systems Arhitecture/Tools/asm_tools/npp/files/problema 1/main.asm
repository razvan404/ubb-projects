bits 32

global start        

extern exit, fopen, fprintf, fscanf, fclose, scanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    descr dd -1
    n dd 0
    read_mode db 'r', 0
    file_name db 'input.txt', 0
    n_format db "%d", 0
    elem_format db "%x", 0
    afisare_format db "%d ", 0
    curent dd 0
    copie_ecx dd 0
    minim_curent dd 20
    

segment code use32 class=code
    start:
    
    .deschidere_fisier:
        push dword read_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [descr], eax
        cmp eax, 0
        je .final
    
    .citire_n:
        push dword n
        push dword n_format
        push dword [descr]
        call [fscanf] 
        add esp, 4 * 3
    
    .pregatire_citire_sir:
        mov ecx, [n]
        jecxz .final
        cld
    
    .citire_sir:
        mov dword[copie_ecx], ecx
        push dword curent
        push dword elem_format
        push dword [descr]
        call [fscanf]
        add esp, 4 * 2
        mov ecx, 1
        mov eax, 0x11
        mov dword[minim_curent], eax
        mov eax, [curent]
        
    .cauta_cifra_minim:
        mov edx, 0
        mov ebx, 0x10
        div ebx
        cmp edx, dword[minim_curent]
        jae .repeta_cifra
        
        mov dword[minim_curent], edx
        cmp eax, 0
        je .afisare_cifra
        
    .repeta_cifra:
        inc ecx
        loop .cauta_cifra_minim
    
    .afisare_cifra:
        push dword [minim_curent]
        push dword afisare_format
        call [printf]
    
    .repeta_citire:
        mov ecx, dword[copie_ecx]
        loop .citire_sir    
        
    .inchidere_fisier:
        push dword [descr]
        call [fclose]
        add esp, 4
        
    .final:
        push dword 0
        call [exit]