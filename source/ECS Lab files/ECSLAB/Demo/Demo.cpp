/****************************************************************/
/* demo.c														*/
/****************************************************************/
#include "peg.hpp"
#include "demo.h"
#include "math.h"
#include "HEADER.h"
#include <embkern.h>
#include <embclib.h>
#include <malloc.h>
#include <video.h>

#include "Header.h"
#include "tunes.inc"
#include <process.h>

unsigned int __stdcall sm_thread(void* pArguments);
unsigned int __stdcall music_thread(void* pArguments);



/****************************************************************/
/* MAIN                                                         */
/****************************************************************/
Ubyte KeyBeep(void);  // wait for key, then BEEP


void demo()
{
	HANDLE hThread_sm,hThread_music;
	unsigned int threadID_sm,threadID_music;
    PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr,hGuiThread;

	void EcsGuiInit(HANDLE *hGuiThread, HANDLE *hpScrMgr , HANDLE *hpEcsPic);
	char EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);

	char image1[] ="C:\\images\\DEMO.BMP";
	char image2[] ="C:\\images\\DEMOInv.BMP";

	char toggleIm,k, s[10];
 	LedDisp(0xc);
    LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg(" Lab Assignment ");
    LcdLine2();LcdMsg("Press a Key  ...");
	BEEP();

	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic);	/* initialise graphics */
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	EcsDrawBMP(image1, pScrMgr);	/* Demo Welcome */
	toggleIm = 0;

	hThread_sm = (HANDLE)_beginthreadex(NULL,0,&sm_thread,NULL,0,&threadID_sm);
	SuspendThread(hThread_sm);
	hThread_music = (HANDLE)_beginthreadex(NULL,0,&music_thread,NULL,0,&threadID_music);


	//SuspendThread(hThread_music);
	while(1)
	{
		Sleep(10);
		switch (KeyBeep())
		{
		case 1 : //start music
				LcdLine1();LcdMsg(" Music Please   ");
			    LcdLine2();LcdMsg("    Maestro     ");
				ResumeThread(hThread_music);
				break;
		case 2 : //stop music
				LcdLine1();LcdMsg(" Music Pause    ");
				SuspendThread(hThread_music);
				Sleep(1000);	/* see message */
				break;
		case 3 : // start motor
				LcdLine1();LcdMsg(" Let's start    ");
			    LcdLine2();LcdMsg(" Rock & Roll    ");
				ResumeThread(hThread_sm);
				break;
		case 4 : //stop motor
				LcdLine1();LcdMsg(" Motor Pause    ");
				SuspendThread(hThread_sm);
				Sleep(1000);	/* let user see message */
				break;
		case 5 : //keypad test
				LcdClear();
				LcdLine1();LcdMsg(" Toggle image   ");
				LcdLine2();
				Sleep(1000);	/* let user see message */

				if (toggleIm)
				{
					EcsDrawBMP(image1, pScrMgr);
					toggleIm = 0;
				}
				else
				{
					EcsDrawBMP(image2, pScrMgr);
					toggleIm = 1;
				}
				break;
		case 6 : //keypad test
				LcdClear();
				LcdLine1();LcdMsg("Key test #-exits");
				LcdLine2();

				while ((k=KeyBeep())!= 0xb) // Press '#' to exit
				{	 
					LedDisp(k);
					itoa((int)k,s,16);
					LcdMsg(s);
				} 
				BEEP();
				break;

		default :
				printf("Press select 1 to 6");
				LcdLine2();LcdMsg("Wrong Key:1 to 6");Sleep(1000);
				break;
		}
			LcdLine1();LcdMsg(" One more time  ");
			LcdLine2();LcdMsg("Press a Key  ...");

	}
}


Ubyte KeyBeep(void)
{
	Ubyte c;
	c = KeyPressed();
	LedDisp(c);
	BEEP();
	return c;
}

unsigned int __stdcall sm_thread(void* pArguments)
{
	while(1)
	{
		Spin( CW,100,10); // turn motor clockwise, 100 steps
		Spin(CCW,100,10); // turn motor counterclockwise, 100 steps
	}
	return(0);
}

unsigned int __stdcall music_thread(void* pArguments)
{
	
	while(TRUE)
	{
		PlaySong((const char*)MinuetG);
		Sleep(500);
		PlaySong((const char*)Hawaii);
		Sleep(500);
		PlaySong((const char*)TurkishRondo);
		Sleep(500);
	}
	return(0);
}
