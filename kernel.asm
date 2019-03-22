org 0x7e00
jmp 0x0000:start

nome_max equ 20
cpf_max equ 11
agencia_max equ 5
conta_max equ 8

string times 21 db 0
banco_de_dados times 2000 db 0


linha db '===========================================',0
apresentacao db 'Bem vindo ao seu banco de dados!',0
limites db 'Limites:',0
limites_nome db 'Seu nome pode ter no maximo 20 caracteres',0
limites_cpf db 'Seu CPF so pode ter no maximo 11 caracteres',0
limites_agencia db 'Sua agencia pode ter no maximo 5 caracteres',0
limites_conta  db 'Sua conta pode ter no maximo 8 caracteres',0

set_menu:
	pusha 
	mov dx,50
	mov si,linha
	call prints
	call endl
	mov si,apresentacao
	call prints
	call endl
	mov si,limites
	call prints
	call endl
	mov si,limites_nome
	call prints
	call endl
	mov si,limites_cpf
	call prints
	call endl
	mov si,limites_agencia
	call prints
	call endl
	mov si,limites_conta
	call prints
	call endl
	mov si,linha
	call prints
	call endl
	popa
ret

endl:
	pusha 
	mov ah,0x3
	mov bh,0
	int 0x10
	add dh,1
	mov dl,0
	mov ah,0x2;return(dh = row, dl = collum)
	int 0x10
	popa
ret

putchar: ; mov bl, number of color
    mov ah,0xe
    mov bh, 0 ;page number
    int 0x10
ret

del_name:
	mov al, 0x08
	call putchar
	mov al, ' '
	call putchar
	mov al, 0x08
	call putchar
ret

getchar:
	mov ah, 0
	int 16h
ret

gets:
	xor cx,cx
	_loop:
		call getchar
		cmp al, 0x08
		je backspace
		cmp al, 0x0d
		je end1
		cmp cx, dx
		je _loop
		stosb
		inc cx
		call putchar
	jmp _loop

	backspace:
		cmp cx,0x0
		je _loop
		dec cx
		dec di
		call del_name
		jmp _loop
	
	end1:
		add dx,1
	end2:
		cmp cx,dx
		jne complete
		jmp real_end
	complete:
		mov ax, 0x0
		stosb
		inc cx
		jmp end2
	real_end:

ret

prints: ;load string in si
    lodsb
    cmp al, 0x0
    je printend
    call putchar
    jmp prints
    printend: 
ret


set_video_mode:;320x200, center=160x100
    mov ah,0x0
    mov al,0x13
    int 0x10
ret

forinutil:
    pusha

    mov cx, 0x1
    mov dx, 0x0
    mov ah, 0x86
    int 0x15

    popa
ret

reverse:
	xor cx,cx
	reverse_loop:
		lodsb
		cmp al,0x0
		je end_reverse_loop
		inc cl
		push ax
		jmp reverse_loop
	end_reverse_loop:

	mov di,dx

	reverse_loop_two:
		cmp cl,0x0
		je end_reverse_loop_two
		dec cl
		pop ax
		stosb
		jmp reverse_loop_two

	end_reverse_loop_two:

	mov al , 0x0
	stosb
ret

itostr: ;the number must be in ax
    pusha
	push dx
	push di	
	itostr_loop:
		cmp ax, 0
		je end_itostr_loop
		xor dx,dx
		mov bx,10
		div bx
		add dx,'0'
		xchg ax,dx
		stosb
		xchg ax,dx
		jmp itostr_loop
	end_itostr_loop:

	pop si
	pop dx
	cmp si,di
	jne end_itostr
	mov al,'0'
	stosb
	end_itostr:
		mov al,0x0
		stosb
		call reverse
    popa
ret

start:
	xor ax, ax
	mov ds, ax
	mov es, ax

	call set_menu
	
	mov di,string
	mov dx,nome_max
	call gets
	call endl

	mov si,string
	call prints
	call endl

done:
	jmp $
