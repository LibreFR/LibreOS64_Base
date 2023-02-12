#pragma once


#include "ES.c"
#include "typedefs.c"

/*struct IDT32{
	uint16_t offset_1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_2;
};*/

struct IDT64{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t types_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
};

extern struct IDT64 _idt[256];
extern uint64_t isr1;
extern void loadTDI();

void initIDT()
{
	_idt[1].zero = 0;
	_idt[1].offset_low = (uint16_t)((uint64_t) &isr1 & 0x000000000000ffff);
	_idt[1].offset_mid = (uint16_t)(((uint64_t) &isr1 & 0x00000000ffff0000) >> 16);
	_idt[1].offset_high = (uint32_t)(((uint64_t) &isr1 & 0xffffffff00000000) >> 32);
	_idt[1].ist = 0;
	_idt[1].selector = 0x08;
	_idt[1].types_attr = 0x8E;

    remapPIC();

	outb(0x21, 0xFD);
	outb(0xA1, 0xFF);
	loadTDI();
}

extern void isr1Handler()
{
    //Gérer le inb(0x60); un jour
	outb(0x20, 0x20);
	outb(0xA0, 0x20);
}
