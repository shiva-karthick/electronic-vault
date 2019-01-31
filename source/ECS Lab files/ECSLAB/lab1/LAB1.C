/************************/
/*       LED lab        */
/************************/
#include <windows.h>

#define LEDPort  0x332
#define TRUE      1			/*  neater to use! */

/* store this table in code space */
const unsigned char Bin2LED[] =

/*  0     1     2    3 */
{0x__, 0x__, 0x__,0x__,
/*  4     5     6    7*/
 0x__, 0x__, 0x__,0x__,
/*  8     9     A    B*/
 0x__, 0x__, 0x__,0x__,
/*  C     D     E    F*/
 0x__, 0x__, 0x__,0x__
};


/*************************************************************************/
/***************************      MAIN PROGRAM      **********************/
/*************************************************************************/
void main (void)
{/* main entry for program */
	unsigned char i,sec, LEDval;
	i = 0;
	printf("lab1");
	while (TRUE)
	{
		Sleep(____);			/* non blocking delay 1 second */
		sec = i / 10;
		LEDval = Bin2LED[i];
		_outp(LEDPort, LEDval);   /* output to LED */
		i++;		
		printf("%d",i);
		if (i == 10)
			i = 0;		/* only 1 to 10 */
    }   /* while */
}   /* main */
