org 0x7C00   ; add 0x7C00 to label addresses
bits 16      ; tell the assembler we want 16 bit code

    mov ah, 02h    ; Read Sectors from Drive
    mov al, 128    ; Sectors to Read Count
    mov ch, 0      ; Cylinder
    mov cl, 2      ; Sector
    mov dh, 0      ; Head
    mov dl, 80h    ; Drive
    mov bx, 0x7E00 ; Buffer Address Pointer (Lower)
    int 13h

    jmp 0x7E00

    times 510 - ($ - $$) db 0
    dw 0xAA55 ; some BIOSes require this signature

_start:
    xor ax, ax     ; set up segments
    mov ds, ax
    mov es, ax
    mov ss, ax     ; setup stack
    mov sp, 0x7C00 ; stack grows downwards from 0x7C00
           
    mov di, 0100H
    mov word[di], print_string
    mov word[di + 2], ds

    mov bx, welcome
    mov cx, 10
    int 40h

    jmp -1

welcome db 'AP2 de IHS'

; ================
; calls start here
; ================

print_string:
    mov si, bx

.loop:
    cmp cx, 0
    je .done

    lodsb        ; grab a byte from SI

    mov ah, 0x0E
    int 0x10      ; otherwise, print out the character!

    dec cx

    jmp .loop

.done:
    iret
