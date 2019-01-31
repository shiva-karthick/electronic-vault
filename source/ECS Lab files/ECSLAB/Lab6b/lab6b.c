#include <windows.h>
#define true 1
#define DACPort _____

unsigned char i;
unsigned char WaveTable []={___,___,___,___,___,___,___,___,___,___,___,___};
void main()
{
	i = 0;
	while(true)
	{
		_outp(DACPort, WaveTable[i]); /* DAC port */
		i++;				 /* increment */
		if (i>=12) i=0;
		Sleep(1);
	}
}
