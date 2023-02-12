%macro includeBin 2
	SECTION .rodata
	GLOBAl %1

%1:
	incbin %2
	db 0
	%1_size: dq %1_size - %1

%endmacro

includeBin Test, "IncBin/test.txt"
