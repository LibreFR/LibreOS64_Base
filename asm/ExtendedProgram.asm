
jmp EnterProtectedMode

%include "asm/gdt.asm"
%include "asm/print.asm"

EnterProtectedMode:
	call EnableA20
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:StartProtectedMode

EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[BITS 32]

%include "asm/CPUID.asm"
%include "asm/SimplePaging.asm"

StartProtectedMode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call DetectCPUID
	call DetectLongMode
	call SetUpIdentityPaging
	call EditGDT

	jmp codeseg:Start64Bit

[BITS 64]

[extern _start]

%include "asm/TDI.asm"

Start64Bit:
	mov edi, 0xb8000

	mov rax, 0x0f200f200f200f20

	mov ecx, 500
	rep stosq
	call _start
	jmp $

times 2048-($-$$) db 0
