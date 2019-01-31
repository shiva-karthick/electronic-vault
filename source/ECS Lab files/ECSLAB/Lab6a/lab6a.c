
#define DACPort 0x330

char DACout;

void main()
{
	DACout = 0;
	
	while (1)
	{
		_outp(DACPort,DACout); /* DAC port */
		DACout++;
	}
}
