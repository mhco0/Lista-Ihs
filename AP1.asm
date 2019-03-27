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

    mov si, welcome
    call print_string

    call print_ln
    call main

    mov ax, 5307h
    mov bx, 0001h
    mov cx, 0003h
    int 15h       ; shutdown

    jmp -1

main:
    jmp .help

.loop:
    call print_ln

    mov si, prompt
    call print_string

    mov dl, 0x3F
    mov di, str_buffer
    xor cl, cl
    call get_string

    mov si, str_buffer
    cmp byte [si], 0  ; blank line?
    je .loop          ; yes, ignore it

    mov si, str_buffer
    mov di, cmd_help  ; "help" command
    call strcmp
    jc .help

    mov si, str_buffer
    mov di, cmd_exit  ; "exit" command
    call strcmp
    jc .exit

    mov si, str_buffer
    mov di, cmd_debug  ; "debug" command
    call strcmp
    jc .debug

    mov si, str_buffer
    mov di, cmd_register  ; "register" command
    call strcmp
    jc register

    mov si, str_buffer
    mov di, cmd_search  ; "search" command
    call strcmp
    jc search

    mov si, str_buffer
    mov di, cmd_edit  ; "edit" command
    call strcmp
    jc edit

    mov si, str_buffer
    mov di, cmd_unregister  ; "unregister" command
    call strcmp
    jc unregister

    mov si, str_buffer
    mov di, cmd_list_agencies  ; "list_agencies" command
    call strcmp
    jc list_agencies

    mov si, str_buffer
    mov di, cmd_list_accounts  ; "list_accounts" command
    call strcmp
    jc list_accounts

    mov si, badcommand
    call print_string 
    jmp .loop

.help:
    mov si, msg_help
    call print_string

    jmp .loop

.exit:
    ret

.debug:
    mov si, data
    mov cx, [data_length]
    call print_raw
    call print_ln

    jmp .loop

register:
    mov bx, data
    add bx, [data_length]

    add word [data_length], sizeof_entity
    inc byte [data_count]

.name:
    mov si, prompt_name
    call print_string

    mov dl, sizeof_name
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .name          ; yes, ignore it

    add bx, sizeof_name + 1

.cpf:
    mov si, prompt_cpf
    call print_string

    mov dl, sizeof_cpf
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .cpf           ; yes, ignore it

    add bx, sizeof_cpf + 1

.agency:
    mov si, prompt_agency
    call print_string

    mov dl, sizeof_agency
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .agency        ; yes, ignore it

    add bx, sizeof_agency + 1

.account:
    mov si, prompt_account
    call print_string

    mov dl, sizeof_account
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .account       ; yes, ignore it

    add bx, sizeof_account + 1

.done:
    call print_ln

    mov si, msg_register
    call print_string

    lea si, [bx - sizeof_entity]
    call print_entity
    
    jmp main.loop

search:
    lea bx, [temp_entity + (sizeof_name + 1) + (sizeof_cpf + 1)]

.agency:
    mov si, prompt_agency
    call print_string

    mov dl, sizeof_agency
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .agency        ; yes, ignore it

    add bx, sizeof_agency + 1

.account:
    mov si, prompt_account
    call print_string

    mov dl, sizeof_account
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .account       ; yes, ignore it

    add bx, sizeof_account + 1

.done:
    call print_ln

    mov al, [data_count]
    mov si, data
    mov di, temp_entity

    call get_account
    jnc .404

    call print_entity

    jmp main.loop

.404:
    mov si, msg_404
    call print_string

    jmp main.loop

edit:
    lea bx, [temp_entity + (sizeof_name + 1) + (sizeof_cpf + 1)]

.agency:
    mov si, prompt_agency
    call print_string

    mov dl, sizeof_agency
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .agency        ; yes, ignore it

    add bx, sizeof_agency + 1

.account:
    mov si, prompt_account
    call print_string

    mov dl, sizeof_account
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .account       ; yes, ignore it

    add bx, sizeof_account + 1

.search:
    call print_ln

    mov al, [data_count]
    mov si, data
    mov di, temp_entity

    call get_account
    jnc .404

    mov bx, si
    call print_entity
    call print_ln

.name:
    mov si, prompt_name
    call print_string

    mov si, bx
    call print_string

    mov dl, sizeof_name
    mov di, bx
    add di, cx
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .name          ; yes, ignore it

    add bx, sizeof_name + 1

.cpf:
    mov si, prompt_cpf
    call print_string

    mov si, bx
    call print_string

    mov dl, sizeof_cpf
    mov di, bx
    add di, cx
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .cpf           ; yes, ignore it

    add bx, sizeof_cpf + 1

.done:
    call print_ln

    lea si, [bx - ((sizeof_name + 1) + (sizeof_cpf + 1))]
    call print_entity

    jmp main.loop

.404:
    mov si, msg_404
    call print_string

    jmp main.loop

unregister:
    lea bx, [temp_entity + (sizeof_name + 1) + (sizeof_cpf + 1)]

.agency:
    mov si, prompt_agency
    call print_string

    mov dl, sizeof_agency
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .agency        ; yes, ignore it

    add bx, sizeof_agency + 1

.account:
    mov si, prompt_account
    call print_string

    mov dl, sizeof_account
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .account       ; yes, ignore it

    add bx, sizeof_account + 1

.search:
    call print_ln

    mov al, [data_count]
    mov si, data
    mov di, temp_entity

    call get_account
    jnc .404

.done:
    dec byte [data_count]
    sub word [data_length], sizeof_entity

    mov di, si
    lea si, [di + sizeof_entity]

    dec al
    mov dl, sizeof_entity
    mul dl
    mov cx, ax

    cld
    rep movsb

    mov si, msg_unregister
    call print_string

    jmp main.loop

.404:
    mov si, msg_404
    call print_string

    jmp main.loop

list_agencies:
    mov al, [data_count]

    mov si, data
    add si, (sizeof_name + 1) + (sizeof_cpf + 1)

.loop:
    cmp al, 0
    jle main.loop

    push ax
    push si
    call print_string_ln
    pop si
    pop ax

    add si, sizeof_entity
    dec al

    jmp .loop

list_accounts:
    lea bx, [temp_entity + (sizeof_name + 1) + (sizeof_cpf + 1)]

.agency:
    mov si, prompt_agency
    call print_string

    mov dl, sizeof_agency
    mov di, bx
    xor cl, cl
    call get_string

    cmp byte [bx], 0  ; blank line?
    je .agency        ; yes, ignore it

.list:
    mov al, [data_count]

    mov di, bx

    mov si, data
    add si, (sizeof_name + 1) + (sizeof_cpf + 1)

.loop:
    cmp al, 0
    jle main.loop

    push ax

    push di
    push si
    call strcmp
    pop si
    pop di
    jnc .continue

    push si
    sub si, (sizeof_name + 1) + (sizeof_cpf + 1)
    call print_ln
    call print_entity
    pop si

.continue:
    pop ax

    add si, sizeof_entity
    dec al

    jmp .loop

welcome db 'Welcome to 0x7E00!', 0x0D, 0x0A, 0

sizeof_name equ 20
sizeof_cpf equ 11
sizeof_agency equ 5
sizeof_account equ 8

sizeof_entity equ (sizeof_name + 1) + (sizeof_cpf + 1) + (sizeof_agency + 1) + (sizeof_account + 1)
temp_entity times sizeof_entity db 0

data_capacity equ 64
data_length dw 0
data_count db 0
data times data_capacity * sizeof_entity db 0

prompt db '>: ', 0
badcommand db 'Bad command entered.', 0x0D, 0x0A, 0

cmd_help db 'help', 0
msg_help db 'Commands: help, exit, debug, register, search, edit, unregister, list-agencies, and list-accounts', 0x0D, 0x0A, 0

cmd_exit db 'exit', 0

cmd_debug db 'debug', 0

cmd_register db 'register', 0
msg_register db 'Account Registered!', 0x0D, 0x0A, 0
prompt_name db 'Name    : ', 0
prompt_cpf db 'CPF     : ', 0
prompt_agency db 'Agency  : ', 0
prompt_account db 'Account : ', 0

cmd_search db 'search', 0

cmd_edit db 'edit', 0

cmd_unregister db 'unregister', 0
msg_unregister db 'Account Unregistered!', 0x0D, 0x0A, 0

cmd_list_agencies db 'list-agencies', 0

cmd_list_accounts db 'list-accounts', 0

msg_404 db 'Not Found!', 0x0D, 0x0A, 0

; ================
; calls start here
; ================

get_account:
    add si, (sizeof_name + 1) + (sizeof_cpf + 1)
    add di, (sizeof_name + 1) + (sizeof_cpf + 1)

.loop:
    cmp al, 0
    jle .break

    push ax

    push si
    push di

    call strcmp
    jnc .continue

    pop di
    pop si

    push si
    push di

    add si, (sizeof_agency + 1)
    add di, (sizeof_agency + 1)

    call strcmp
    jnc .continue

    pop di
    pop si

    pop ax

    sub di, (sizeof_name + 1) + (sizeof_cpf + 1)
    sub si, (sizeof_name + 1) + (sizeof_cpf + 1)

    stc
    ret

.continue:
    pop di
    pop si

    pop ax

    add si, sizeof_entity
    dec al

    jmp .loop

.break:
    sub di, (sizeof_name + 1) + (sizeof_cpf + 1)
    sub si, (sizeof_name + 1) + (sizeof_cpf + 1)

    clc
    ret

consume_whitespace:
    lodsb                   ; grab a byte from SI

    or al, al               ; logical or AL by itself
    jz consume_whitespace   ; if the result is zero, get out

    dec si
    ret

msg_name db 'Name', 0x0D, 0x0A, '        ', 0
msg_cpf db 'CPF', 0x0D, 0x0A, '        ', 0
msg_agency db 'Agency', 0x0D, 0x0A, '        ', 0
msg_account db 'Account', 0x0D, 0x0A, '        ', 0

print_entity:
    push dx
    push si

    mov dx, si
    mov si, msg_name
    call print_string

    mov si, dx
    call consume_whitespace
    call print_string_ln

    mov dx, si
    mov si, msg_cpf
    call print_string

    mov si, dx
    call consume_whitespace
    call print_string_ln

    mov dx, si
    mov si, msg_agency
    call print_string

    mov si, dx
    call consume_whitespace
    call print_string_ln

    mov dx, si
    mov si, msg_account
    call print_string

    mov si, dx
    call consume_whitespace
    call print_string_ln

    pop si
    pop dx

    ret

print_raw:
    lodsb        ; grab a byte from SI

    jcxz .done   ; if the result is zero, get out
    dec cx

    mov ah, 0x0E
    int 0x10      ; otherwise, print out the character!

    jmp print_raw

.done:
    ret

print_string:
    xor cx, cx

.loop:
    lodsb        ; grab a byte from SI

    or al, al  ; logical or AL by itself
    jz .done   ; if the result is zero, get out

    mov ah, 0x0E
    int 0x10      ; otherwise, print out the character!

    inc cl

    jmp .loop

.done:
    ret

print_ln:
    mov ax, 0x0E0D
    int 0x10

    mov ax, 0x0E0A
    int 0x10

    ret

print_string_ln:
    call print_string
    call print_ln
    ret

str_buffer times 256 db 0

get_string:

.loop:
    mov ah, 0
    int 0x16   ; wait for keypress

    cmp al, 0x08    ; backspace pressed?
    je .backspace   ; yes, handle it

    cmp al, 0x0D  ; enter pressed?
    je .done      ; yes, we're done

    cmp cl, dl    ; dl chars inputted?
    je .loop      ; yes, only let in backspace and enter

    mov ah, 0x0E
    int 0x10      ; print out character

    stosb  ; put character in str_buffer
    inc cl
    jmp .loop

.backspace:
    cmp cl, 0	; beginning of string?
    je .loop	; yes, ignore the key

    dec di
    mov byte [di], 0	; delete character
    dec cl		; decrement counter as well

    mov ah, 0x0E
    mov al, 0x08
    int 10h		; backspace on the screen

    mov al, ' '
    int 10h		; blank character out

    mov al, 0x08
    int 10h		; backspace again

    jmp .loop	; go to the main loop

.done:
    mov al, 0	; null terminator
    stosb

    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A
    int 0x10		; newline

    ret

strcmp:

.loop:
    mov al, [si]   ; grab a byte from SI
    mov bl, [di]   ; grab a byte from DI
    cmp al, bl     ; are they equal?
    jne .notequal  ; nope, we're done.

    cmp al, 0  ; are both bytes (they were equal before) null?
    je .done   ; yes, we're done.

    inc di     ; increment DI
    inc si     ; increment SI
    jmp .loop  ; loop!

.notequal:
    clc  ; not equal, clear the carry flag
    ret

.done: 	
    stc  ; equal, set the carry flag
    ret
