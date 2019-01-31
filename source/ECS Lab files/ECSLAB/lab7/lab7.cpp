/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#include "peg.hpp"
#include "lab7.h"
#include "math.h"
#include "Header.h"
#include <embkern.h>
#include <embclib.h>
#include <malloc.h>
#include <video.h>


/* functions */
void    ShowDriveInfo(char *pWhere);
void	EcsConsoleMsg(char *pMsg);
//void	EcsGuiInit(HANDLE hGuiThread, PegPresentationManager * , EcsPic *);
//void	EcsGuiInit(HANDLE hGuiThread, struct PegPresentationManager  , struct EcsPic );
void	EcsGuiInit(HANDLE *hGuiThread, HANDLE *hpScrMgr , HANDLE *hpEcsPic);
void	EcsGuiQuit(EcsPic *pEcsPic);
char 	EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);


char	*gpECSBitmapfile;	/* global */


Ubyte KeyBeep(void);  // wait for key, then BEEP
//Ubyte KeyPressed(); // waits for key to be pressed
//void BEEP(); // sounds a beep on speaker*/


void main()
{

    PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr,hGuiThread;

	char c, exit=0;
	char file1[] ="C:\\IMAGES\\COLCHT.BMP";
	char file2[] ="C:\\IMAGES\\LIONS.BMP";
	char file3[] ="C:\\IMAGES\\SUNSET.BMP";

	/* Initialise graphics */	
	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic);	
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	/* Initialise graphics */	

	LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg(" Image to view? ");
    LcdLine2();LcdMsg(" 1/2/3: 4-exits  ");
	while(1)
	{

		switch (KeyBeep())
		{
		case 1 :
			EcsDrawBMP(file1, pScrMgr);
			break;
		case 2 : //stop music
			EcsDrawBMP(file2, pScrMgr);
			break;
		case 3 :
			EcsDrawBMP(file3, pScrMgr);
			break;
		case 4 :
			exit =1;
			break;
		default :
			LcdLine2();LcdMsg("Wrong Key:1 to 4");Sleep(1000);
			break;
		}
		if (exit)
			break;
		LcdLine1();LcdMsg(" One more time  ");
		LcdLine2();LcdMsg(" 1/2/3: 4-exits  ");
	}
	LcdClear();
	LcdLine1();LcdMsg("   B Y E   ");

	EcsGuiQuit(pEcsPic);

	WaitForSingleObject(hGuiThread, INFINITE);
    CloseHandle(hGuiThread);
    EcsConsoleMsg("ECS Demo has completed.\n");
}


Ubyte KeyBeep(void)
{
	char c;
	c = KeyPressed();
	LedDisp(c);
//	BEEP();
	return c;
}
/* display message to host console */
void EcsConsoleMsg(char *pMsg)
{
	EtsSelectConsole(ETS_CO_HOST);
	printf(pMsg);
}