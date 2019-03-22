org 0x7e00
jmp 0x0000:start

green equ 0x2
blue equ 0x1
yellow equ 0xe
white equ 0xf
grey equ 0x7
magenta equ 0xd
space equ 0x20

string times 20 db 0

name_len db 20;

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
	xor cx, cx
	_loop:
		call getchar
		cmp al, 0x08
		je backspace
		cmp al, 0x0d
		je end
		cmp cl, [name_len]
		je _loop
		stosb
		inc cl
		call putchar
	jmp _loop

	backspace:
		cmp cl, 0
		je _loop
		dec cl
		dec di
		call del_name
		jmp _loop
	
	end:
		mov al, 0x0
		stosb
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

	mov di,string
	call gets
	call endl

	mov si,string
	call prints
	call endl

done:
	jmp $
