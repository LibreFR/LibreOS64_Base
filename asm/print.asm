puts:
	push ax
	push bx

	mov ah, 0x0e
		lodsb
		or al, al
		jz .fin
		int 0x10
		jmp puts
	.fin:
		pop ax
		pop bx
    		ret
