nasm asm/bootloader.asm -f bin -o Binaires/bootloader.bin

nasm asm/ExtendedProgram.asm -f elf64 -o Binaires/ExtendedProgram.o

nasm Bins.asm -f elf64 -o Binaires/Bins.o

gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "noyau.c" -o "Binaires/noyau.o"
# i386-elf-gcc -ffreestanding -m32 -g -c "noyau.c" -o "Binaires/noyau.o"

ld -T "link.ld"

cat Binaires/bootloader.bin Binaires/noyau.bin > SE.flp

qemu-system-x86_64 -drive format=raw,file="SE.flp",index=0,if=floppy,  -m 128M -soundhw pcspk
