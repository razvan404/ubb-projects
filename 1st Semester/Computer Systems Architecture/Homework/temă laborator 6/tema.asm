bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; R, T, Q - dublucuvinte
    R dd 10101010101001101000011010011111b
    T dd 11101010101010101111101001001010b
    Q dd 0

; our code starts here
segment code use32 class=code
    start:
        ; 26. Se dau 2 dublucuvinte R si T. Sa se obtina dublucuvantul Q astfel:
        ;       -bitii 0-6 din Q coincid cu bitii 10-16 a lui T
        ;       -bitii 7-24 din Q concid cu bitii obtinuti 7-24 in urma aplicarii R XOR T.
        ;       -bitii 25-31 din Q coincid cu bitii 5-11 a lui R.
        
        mov ebx, 0 ; in registrul ebx vom calcula rezultatul

        mov eax, [T]                    ; retinem in registrul eax pe T - eax: 111010101010101 0111110 1001001010b - 3937073738 - EAAAFA4Ah
        and eax, 00000000000000011111110000000000b ; izolam bitii 10-16 - eax: 000000000000000 0111110 000000000b  - 31744      - 7C00h
        mov cl, 10
        ror eax, cl                     ; rotim 10 pozitii spre dreapta - eax: 000000000000000000000000 0111110b   - 62         - 3Eh
        or ebx, eax                           ; punem bitii in rezultat - ebx: 000000000000000000000000 0111110b   - 62         - 3Eh
        
        mov eax, [R]                    ; retinem in registrul eax pe R - eax: 1010101 010100110100001101 0011111b - 2863040159 - AAA6869Fh
        xor eax, [T]                           ; facem operatia R XOR T - eax: 0100000 000001100011111001 1010101b - 1074560213 - 400C7CD5h
        and eax, 00000001111111111111111110000000b  ; izolam bitii 7-24 - eax: 0000000 000001100011111001 0000000b - 818304     - C7C80h
        or ebx, eax                           ; punem bitii in rezultat - ebx: 0000000 000001100011111001 0111110b - 818366     - C7CBEh
        
        mov eax, [R]                    ; retinem in registrul eax pe R - eax: 10101010101001101000 0110100 11111b - 2863040159 - AAA6869Fh
        and eax, 00000000000000000000111111100000b  ; izolam bitii 5-11 - eax: 00000000000000000000 0110100 00000b - 1664       - 680h
        mov cl, 20
        rol eax, cl                   ; rotim 20 de pozitii spre stanga - eax: 0110100 000000000000000000 0000000b - 1744830464 - 68000000h
        or ebx, eax                           ; punem bitii in rezultat - ebx: 0110100 000001100011111001 0111110b - 1745648830 - 680C7CBEh
        
        mov [Q], ebx                          ; punem bitii in rezultat - Q  : 01101000000011000111110010111110b   - 1745648830 - 680C7CBEh
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
