#include "libs/typedefs.c"
#include "libs/ES.c"
#include "libs/TDI.c"

extern void _start()
{
    //Texte
	* (volatile char*) 0xB8000 = 'J';
	* (volatile char*) 0xB8002 = 'O';
	* (volatile char*) 0xB8004 = 'N';
	* (volatile char*) 0xB8006 = 'B';
	* (volatile char*) 0xB8008 = 'O';
	* (volatile char*) 0xB800A = 'U';
	* (volatile char*) 0xB800C = 'R';

    //Couleurs
	* (volatile char*) 0xB8001 = 0x9;
	* (volatile char*) 0xB8003 = 0x9;
	* (volatile char*) 0xB8005 = 0xF;
	* (volatile char*) 0xB8007 = 0xF;
	* (volatile char*) 0xB8009 = 0xF;
	* (volatile char*) 0xB800B = 0xC;
	* (volatile char*) 0xB800D = 0xC;

    //Curseur
    setBareCurPos(7);

	for(;;);
	return;
}
