#pragma once

#define PIC1_CMD  32
#define PIC1_DATA 33
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 16
#define ICW1_ICW4 1
#define ICW4_8086 1

#include "typedefs.c"

void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
}

void remapPIC()
{
	uint8_t pic1_backup = inb(PIC1_DATA), pic2_backup = inb(PIC2_DATA);

	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);

	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 8);

	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, pic1_backup);
	outb(PIC2_DATA, pic2_backup);
}

void io_wait(void)
{
    outb(0x80, 0);
}

void setBareCurPos(uint16_t position)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));

	return;
}
