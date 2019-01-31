/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#include "peg.hpp"
#include "lab8.h"
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

	char key, exit=0;
	char file1[] ="C:\\NEW\\WELCOME.BMP";
	char file2[] ="C:\\NEW\\AMOUNT.BMP";
	char file3[] ="C:\\NEW\\20.BMP";
	char file4[] ="C:\\NEW\\50.BMP";
	char file5[] ="C:\\NEW\\THANKYOU.BMP";

	/* Initialise graphics */	
	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic);	
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	/* Initialise graphics */	

	LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg("---ATM Demo -----");
    LcdLine2();LcdMsg(" Follow screen...");
	while(1)
	{
		EcsDrawBMP(file1, pScrMgr);	/* Welcome */
		key = (KeyBeep());
		if (key == 2)					/* continue */
		{
			EcsDrawBMP(file2, pScrMgr);	/* Amount? */
			key = (KeyBeep());
			if (key == 4)				/* $20 */
			{
				EcsDrawBMP(file3, pScrMgr);	/* deducted $20 */
				while(KeyBeep()!=3);		/* wait for key */
				key = 0;			/* so as not to affect other if's */
			}

			if (key == 5)				/* $50 */
			{
				EcsDrawBMP(file4, pScrMgr);	/* deducted $50 */
				while(KeyBeep()!=3);		/* wait for key */
				key = 0;					/* so as not to affect other if's */
			}
		}

		if (key == 3)
			break;

		EcsDrawBMP(file5, pScrMgr);		/* thank you */
		while(KeyBeep()!=1);			/* wait for key */
	}

		
	LcdClear();
	LcdLine1();LcdMsg("     End Demo   ");

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