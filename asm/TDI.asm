[extern _idt]

tdiDesc:
	dw 4095
	dq _idt

%macro PUSHALL 0

push rax
push rcx
push rdx
push r8
push r9
push r10
push r11

%endmacro


%macro POPALL 0

pop r11
pop r10
pop r9
pop r8
pop rdx
pop rcx
pop rax

%endmacro

[extern isr1Handler]

isr1:
	PUSHALL
	call isr1Handler
	POPALL
	iretq
	GLOBAL isr1

loadTDI:
	lidt[tdiDesc]
	sti
	ret
	GLOBAL loadTDI
