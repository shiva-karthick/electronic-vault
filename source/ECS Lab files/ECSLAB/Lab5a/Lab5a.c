#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <time.h>

#define		SMPort		_____
#define		NumSteps	___
#define	    PtableLen	8

unsigned char Ptable []={____,____,____,____,____,____,____,____};

void main (void)
	{
	int i, j;
	i=0;
	for (j=NumSteps;j>0;j--)
		{
		_outp (SMPort,Ptable [i]);		/* output to port */
		Sleep (___);
		i++;
		if (i>=PtableLen) i=0;
		}
	}