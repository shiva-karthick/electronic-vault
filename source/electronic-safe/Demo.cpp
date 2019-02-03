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

// ================== Electronic Safe ==================
void welcome();							  // welcome function
int welcome_flag = 1;					  // welcome function's global variable
int welcome_counter = 0;				  // count until 3 tries
int security_key_array[4] = {0, 0, 0, 0}; // array created to store the 4 digits
int pointer_counter = 0;
unsigned int digit1 = 0;
unsigned int digit2 = 0;
unsigned int digit3 = 0;
unsigned int digit4 = 0;
int result = 0;

// Vault Options Screen
void vault_options_screen();

// ================== End of Electronic Safe ============

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

		if (welcome_flag == 1)
		{
			welcome();
		}

		if (result == 4231 && welcome_flag == 0)
		{
			// Press a button to open the safe
			LcdClear();
			LcdLine1();
			LcdMsg("Press any button");
			LcdLine2();
			LcdMsg("to open");

			switch (KeyBeep())
			{
			case 1:
				vault_options_screen();
			default:
				vault_options_screen();
			}
		}

		if (result != 4231 && welcome_flag == 0 && welcome_counter < 4)
		{
			++welcome_counter;
			LcdClear();
			LcdLine1();
			LcdMsg(" One more time  ");
			LcdLine2();
			LcdMsg("3 tries");
			welcome_flag = 1;
		}
		else if (welcome_counter >= 3) // after 3 tries
		{
			LcdClear();
			LcdLine1();
			LcdMsg("System is");
			LcdLine2();
			LcdMsg("Disabled !");
			Sleep(10000); // sleep for 10s
			welcome_flag = 1;
		}

		// LcdLine1();
		// LcdMsg(" One more time  ");
		// LcdLine2();
		// LcdMsg("Press a Key  ...");
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
	// welcome_flag = 1; //seems unnecessary
	while (welcome_flag == 1)
	{
		switch (KeyBeep())
		{
		case 1: //Number 1 has been entered

			LcdLine2();
			LcdMsg("1 entered");
			digit1 = 1;

			if (*security_key_array == 0)
			{

				security_key_array[pointer_counter] = digit1;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit1;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit1;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit1;
			}

			break;
		case 2: //Number 2 has been entered
			LcdLine2();
			LcdMsg("2 entered");
			digit2 = 2;

			if (*security_key_array == 0)
			{

				security_key_array[pointer_counter] = digit2;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit2;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit2;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit2;
			}

			break;
		case 3: // Number 3 has been entered
			LcdLine2();
			LcdMsg("3 entered");
			digit3 = 3;

			if (*security_key_array == 0)
			{

				security_key_array[pointer_counter] = digit3;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit3;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit3;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit3;
			}

			break;
		case 4: // Number 4 has been entered
			LcdLine2();
			LcdMsg("4 entered");
			digit4 = 4;

			if (*security_key_array == 0)
			{

				security_key_array[pointer_counter] = digit4;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit4;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit4;
				++pointer_counter;
			}
			else if (*(security_key_array + pointer_counter) == 0)
			{

				security_key_array[pointer_counter] = digit4;
			}

			break;
		default:
			int result = 0; // declared already just in case :)

			for (int i_result = 0; i_result < 4; i_result++)
			{
				result *= 10;
				result += security_key_array[i_result];
			}
			LcdClear();
			LcdLine1();
			LcdMsg("Your key");
			LcdLine2();
			LcdMsg("is " + result);
			Sleep(10); // wait for the user to read

			welcome_flag = 0; // quit the welcome function
			break;
		}
	}
}

void vault_options_screen()
{
	// insert image here
	LcdClear();
	LcdLine1();
	LcdMsg("Enter option ");
	LcdLine2();
	LcdMsg("1 2 or 3");
	Sleep(10); // wait for the user to read

	switch (KeyBeep())
	{
	case 1:
		// withdraw();
	case 2:
		// deposit();
	case 3:
		EcsDrawBMP(image1, pScrMgr); /* Demo Welcome */
		Sleep(5000);
	default:
		// need to go back to main screen
	}
}