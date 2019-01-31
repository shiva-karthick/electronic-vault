/****************************************************************/
/* Lcd module                                                   */
/****************************************************************/
//#include "Header.h"
/* LCD Module */
#include <time.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "LCD.h"

#define Ubyte unsigned char
#define Ushort unsigned short int
#define Uword unsigned int
#define byte char
#define LEDPort   0x332
#define LcdPort   0x333


void LcdInit()
{
	_outp(LcdPort,0x00);
	Sleep(1);
    
    /* Initialize the Lcd */
    LcdCmd(0x33);     /* Initialise */
    LcdCmd(0x33);     /* Twice! */
    LcdCmd(0x32);     /* 4 bit mode */
    LcdCmd(0x28);     /* 4 bit, 2 lines font 0 */
    LcdCmd(0x08);     /* Display off */
    LcdCmd(0x0C);     /* Display on */
    LcdCmd(0x06);     /* entry mode set, incr, cursor move */
    LcdCmd(0x80);     /* cursor at 00H */
    LcdCmd(0x0F);     /* blink it */
	return;
}

/* Pin layout: 7  6  5  4  3  2  1  0
			   D7 D6 D5 D4 X  E R/W RS */

/* Outputs a Lcd command */            
void LcdOut(Ubyte data)
{
	_outp(LcdPort,data);
/*    Sleep(1);*/
}
            
void LcdData(Ubyte dval)
{
	Ubyte c;
	/* OUTPUT UPPER NIBBLE DATA */
	c = dval & 0xf0;
	c = c | 0x01;	/* RS = 1 */
	LcdOut(c);
	c = c | 0x04;	/* E = 1 */
	LcdOut(c);
	c = c & 0xfb;	/* E = 0 */
	LcdOut(c);

	/* OUTPUT LOWER NIBBLE DATA */
	c = dval;
	c <<= 4;
	c = c | 0x01;	/* RS = 1 */
	LcdOut(c);
	c = c | 0x04;	/* E = 1 */
	LcdOut(c);
	c = c & 0xfb;	/* E = 0 */
	LcdOut(c);
    Sleep(1);
}

void LcdCmd(Ubyte d)
{
	Ubyte c;
	/* OUTPUT UPPER NIBBLE DATA */
	c = d & 0xf0;	/* RS = 0 */		
	LcdOut(c);
	c = c | 0x04;	/* E = 1 */	
	LcdOut(c);
	c = c & 0xfb;	/* E = 0 */
	LcdOut(c);
	/* OUTPUT LOWER NIBBLE DATA */
	d <<= 4;
	c = d & 0xf0;	/* RS = 0 */
	LcdOut(c);
	c = c | 0x04;	/* E = 1 */
	LcdOut(c);
	c = c & 0xfb;	/* E = 0 */
	LcdOut(c);
    Sleep(1);
}

void LcdClear()
{
	LcdCmd(0x01);
	return;
}

/* Go to Lcd Line 1 */
void LcdLine1()
{
	LcdCmd(0x80);
	return;
}

/* Go to Lcd Line 2 */
void LcdLine2()
{
	LcdCmd(0xC0);
	return;
}

void LcdMsg(char *ptr)
{
    while(*ptr)
    {
	LcdData(*ptr);
	++ptr;
    }
    return;
}

