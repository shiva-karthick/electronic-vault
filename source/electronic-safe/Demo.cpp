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

unsigned int __stdcall sm_thread(void *pArguments);
unsigned int __stdcall music_thread(void *pArguments);

// Electronic Safe
void welcome();		  // welcome function
int welcome_flag = 0; // welcome function's global variable
unsigned int digit1 = 0;
unsigned int digit2 = 0;
unsigned int digit3 = 0;
unsigned int digit4 = 0;
unsigned int concatenate(unsigned x, unsigned y); // concatenate 2 integer function
unsigned int concatenate_result;

/****************************************************************/
/* MAIN                                                         */
/****************************************************************/
Ubyte KeyBeep(void); // wait for key, then BEEP

void demo()
{
	HANDLE hThread_sm, hThread_music;
	unsigned int threadID_sm, threadID_music;
	PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr, hGuiThread;

	void EcsGuiInit(HANDLE * hGuiThread, HANDLE * hpScrMgr, HANDLE * hpEcsPic);
	char EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);

	char image1[] = "C:\\images\\DEMO.BMP";
	char image2[] = "C:\\images\\DEMOInv.BMP";

	char toggleIm, k, s[10];
	LedDisp(0xc);
	LcdInit(); /* Initialise Lcd screen */
	LcdLine1();
	LcdMsg(" Lab Assignment ");
	LcdLine2();
	LcdMsg("Press a Key  ...");
	BEEP();

	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic); /* initialise graphics */
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	EcsDrawBMP(image1, pScrMgr); /* Demo Welcome */
	toggleIm = 0;

	hThread_sm = (HANDLE)_beginthreadex(NULL, 0, &sm_thread, NULL, 0, &threadID_sm);
	SuspendThread(hThread_sm);
	hThread_music = (HANDLE)_beginthreadex(NULL, 0, &music_thread, NULL, 0, &threadID_music);

	//SuspendThread(hThread_music);
	while (1)
	{
		Sleep(10);

		welcome();

		LcdLine1();
		LcdMsg(" One more time  ");
		LcdLine2();
		LcdMsg("Press a Key  ...");
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

unsigned int __stdcall sm_thread(void *pArguments)
{
	while (1)
	{
		Spin(CW, 100, 10);  // turn motor clockwise, 100 steps
		Spin(CCW, 100, 10); // turn motor counterclockwise, 100 steps
	}
	return (0);
}

unsigned int __stdcall music_thread(void *pArguments)
{

	while (TRUE)
	{
		PlaySong((const char *)MinuetG);
		Sleep(500);
		PlaySong((const char *)Hawaii);
		Sleep(500);
		PlaySong((const char *)TurkishRondo);
		Sleep(500);
	}
	return (0);
}

void welcome()
{
	LcdClear();
	LcdLine1();
	LcdMsg("Enter key");
	welcome_flag = 0;
	while (welcome_flag == 0)
	{
		switch (KeyBeep())
		{
		case 1: //start music

			LcdLine2();
			LcdMsg("1");
			digit1 = 1;
			break;
		case 2: //stop music
			LcdLine2();
			LcdMsg("2");
			digit2 = 2;
			break;
		case 3: // start motor
			LcdLine2();
			LcdMsg("3");
			digit3 = 3;
			break;
		case 4: //stop motor
			LcdLine2();
			LcdMsg("4");
			digit4 = 4;
			break;
		default:
			welcome_flag = 1;
			break;
		}
	}
}

unsigned int concatenate(unsigned x, unsigned y)
{
	unsigned pow = 10;
	while (y >= pow)
	{
		pow *= 10;
	}
	return x * pow + y;
}