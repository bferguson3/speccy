/*
 * Part of Jari Komppa's zx spectrum suite
 * https://github.com/jarikomppa/speccy
 * released under the unlicense, see http://unlicense.org 
 * (practically public domain)
*/

#define COLOR(BLINK, BRIGHT, PAPER, INK) (((BLINK) << 7) | ((BRIGHT) << 6) | ((PAPER) << 3) | (INK))

#include <string.h>

unsigned char *data_ptr;
unsigned char *screen_ptr;

unsigned short framecounter;

#define HWIF_IMPLEMENTATION

#include "yofstab.h"
#include "hwif.c"
#include "textout.c"

extern void playfx(unsigned short fx) __z88dk_fastcall;  

void cp(unsigned char *dst, unsigned short len, unsigned char *src)  __z88dk_callee
{
       dst; len; src;
    // de   bc   hl
    __asm
    pop iy
    pop de
    pop bc
    pop hl
    push iy
	ldir
    __endasm;
    
}

extern void initfbcopy();
extern void ingame();

void main()
{         
    unsigned short i;
    unsigned char *dst;//, *src;

    do_halt();
    
    dst = (unsigned char*)(0x4000 + (32*192));// + 20*32);
    for (i = 0; i < 32*24; i++)
        *dst++ = 7;
    
    cp((unsigned char*)0x4000, 32*64, (char*)0x5b00);
    cp((unsigned char*)0x4000+(32*192), 32*8, (char*)0x5b00+32*64);
    
    
    //initmusic();
    initfbcopy();

    framecounter = 0;
    ingame();
    
   
}
