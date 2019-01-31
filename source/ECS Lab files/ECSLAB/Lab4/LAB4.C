/***************************/
/*      Keypad and LCD interface     */
/***************************/
unsigned char ProcKey();
unsigned char ScanKey();

#include <time.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define Ubyte unsigned char
#define Ushort unsigned short int
#define Uword unsigned int
#define byte char
/* #define True 1 */
#define False 0
#define Line1 lcdcmd(0x80)
#define Line2 lcdcmd(0xc0)
#define DELAY 20

#define LEDPort   _____          /* LED Port  */
#define LCDPort   _____		 /* LCD Port */
#define KbdPort   _____          /* Key pad port */

#define Col7Lo    ____                      /*  column 7 scan */
#define Col6Lo    ____                      /*  column 6 scan */
#define Col5Lo    ____                      /*  column 5 scan */
#define Col4Lo    ____                      /*  column 4 scan */
#define TRUE      1                         /*  neater to use! */

const unsigned char ScanTable [12] =
/*    0    1     2     3   */
{    0x7D, 0xEB, 0xED, 0xEE,
/*    4      5      6   7  */
     0xDB, 0xDD, 0xDE, 0xBB,
/*    8     9     A     B  */
     0xBD, 0xBE, 0x7B, 0x7E
};

/* store this table in code space (ROM) */
const unsigned char Bin2LED[] =
/*0,       1,       2,       3        0-3 */
{ 0x40    ,0x79    ,0x24   , 0x30,
/*4,       5,       6,       7        4-7 */
  0x19    ,0x12    ,0x02    ,0x78,
/*8,       9,       A,       B        8-B */
  0x00    ,0x18    ,0x08    ,0x03,
/*C,       D,       E,       F        C-F */
  0x46    ,0x21    ,0x06    ,0x0E 
};

    unsigned char ScanCode;      /* hold scan code returned     */



void	lcddata(Ubyte dval);
void	lcdcmd(Ubyte d);
void	LCDOut(Ubyte data);
void	LCDprint(byte *sptr);
void	initlcd();
void	DispNum(Ubyte n);


/******************************************************************************/
/***************************      MAIN PROGRAM      ***************************/
/******************************************************************************/

void main ( void )
{
	initlcd();
	lcdcmd(0x80);
	LCDprint("LCD Lab");
	lcdcmd(0xC0);
	LCDprint("12345678");
		

	while (TRUE)
	{          
		unsigned char i,ii;
		i = ScanKey();
		if (i != 0xFF)                  /* if key is pressed **/
		
/*	{ii= i - 0x30;*/
		{	
			if (i > 0x39)
				ii = i - 0x37;
			else
				ii = i - 0x30;	 
		
			lcddata(i); 	               /* output to LCD */
			_outp(LEDPort,Bin2LED[ii]);     /* output to LED */
			Sleep(400);
		}
	}
}


			/*	LCDprint(ProcKey()); */ 
                       

void sleep1(clock_t wait)
{
	clock_t goal;
	goal = wait +clock();
	while (goal > clock());
}

void lcddata(Ubyte dval)
{
	Ubyte c;
	/* OUTPUT UPPER NIBBLE DATA */
	c = dval & 0xf0;
	c = c | 0x01;	/* RS = 1 */
	LCDOut(c);
	c = c | 0x04;	/* E = 1 */
	LCDOut(c);
	c = c & 0xfb;	/* E = 0 */
	LCDOut(c);

	/* OUTPUT LOWER NIBBLE DATA */
	c = dval;
	c <<= 4;
	c = c | 0x01;	/* RS = 1 */
	LCDOut(c);
	c = c | 0x04;	/* E = 1 */
	LCDOut(c);
	c = c & 0xfb;	/* E = 0 */
	LCDOut(c);
}

void lcdcmd(Ubyte d)
{
	Ubyte c;
	/* OUTPUT UPPER NIBBLE DATA */
	c = d & 0xf0;	/* RS = 0 */		
	LCDOut(c);
	c = c | 0x04;	/* E = 1 */	
	LCDOut(c);
	c = c & 0xfb;	/* E = 0 */
	LCDOut(c);
	/* OUTPUT LOWER NIBBLE DATA */
	d <<= 4;
	c = d & 0xf0;	/* RS = 0 */
	LCDOut(c);
	c = c | 0x04;	/* E = 1 */
	LCDOut(c);
	c = c & 0xfb;	/* E = 0 */
	LCDOut(c);
}
      
void LCDOut(Ubyte data)
{
	_outp(LCDPort,data);
    Sleep(1);

}

/* output a string at address sptr */
void LCDprint(byte *sptr)
{
	while (*sptr!=0)
	{
		int i=1;
		lcddata(*sptr);
		++sptr;
	}
}

void initlcd()
{
    _outp(LCDPort, 0);
	lcdcmd(0x33);		/* Initialise */
	lcdcmd(0x33);		/* Twice! */
	lcdcmd(0x32);		/* 4 bit mode */
	lcdcmd(____);		/* 4 bit, 2 lines, 5x7 font */
	lcdcmd(____);		/* display off */
	lcdcmd(____);		/* display on */
	lcdcmd(____);		/* entry mode set, increment, cursor move */
	lcdcmd(____);		/* cursor at 00H */
	lcdcmd(____);		/* blink */
	lcdcmd(____);		/* Clear Display and return to home position (address 00) */
}
void DispNum(Ubyte n)
{
	if (n > 9)
		n = n + 55;
	else
		n = n + 48;
	lcddata(n);
}

/* Check for key press: if none, return 0xFF */
unsigned char ScanKey() 
{
	_outp(KbdPort ,Col7Lo);             /* bit 7 low */
	  ScanCode = _inp(KbdPort);             /* Read */
	  ScanCode |= 0xF0;               /* high nybble to 1 */
	  ScanCode &= Col7Lo;             /* AND back scan value */        
  if (ScanCode != Col7Lo)         /* in <> out get key */
	    return ProcKey();

	_outp(KbdPort ,Col6Lo);               /* bit 6 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col6Lo;             /* AND back scan value */
	if (ScanCode != Col6Lo)         /* in <> out get key and display */
	    return ProcKey();

	_outp(KbdPort ,Col5Lo);               /* bit 5 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col5Lo;             /* AND back scan value */
	if (ScanCode != Col5Lo)         /* in <> out get key and display */
	    return ProcKey();

	_outp(KbdPort ,Col4Lo);               /* bit 4 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col4Lo;             /* AND back scan value */
	if (ScanCode != Col4Lo)         /* in <> out get key and display */
	    return ProcKey();
	
	  return 0xFF;

    }   /* while */
    /* main */

/* Procedure here */
unsigned char ProcKey()
{
  unsigned char i;                      /* index of scan code returned */
    for (i = 0 ; i <= 12; i++)
    if (ScanCode == ScanTable[i])      /* search in table */
	{
		if(i > 9)
		i = i + 0x37;
	else
		i = i + 0x30;		
	    return i;                   /* exit loop if found */
	}

    if (i == 12)               
	  return 0xFF;              /* if not found, return 0xFF */
    return (0);
}
