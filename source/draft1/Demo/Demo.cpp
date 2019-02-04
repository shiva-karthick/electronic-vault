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
void withdraw();
void deposit();
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
	// char image2[] = "C:\\images\\DEMOInv.BMP";

	// char welcome_image[] = "C:\\images\\.BMP";
	// char door_open[] = "C:\\images\\.BMP";

	// char second_one[] = "C:\\images\\.BMP";
	// char second_two[] = "C:\\images\\.BMP";
	// char second_three[] = "C:\\images\\.BMP";
	// char second_four[] = "C:\\images\\.BMP";
	// char second_five[] = "C:\\images\\.BMP";
	// char second_six[] = "C:\\images\\.BMP";
	// char second_seven[] = "C:\\images\\.BMP";
	// char second_eight[] = "C:\\images\\.BMP";
	// char second_nine[] = "C:\\images\\.BMP";
	// char second_ten[] = "C:\\images\\.BMP";

	// char vault_option_image[] = "C:\\images\\.BMP";

	char toggleIm, k, s[10];
	LedDisp(0xc);
	LcdInit(); /* Initialise Lcd screen */
	// LcdLine1();
	// LcdMsg(" Lab Assignment ");
	// LcdLine2();
	// LcdMsg("Press a Key  ...");
	BEEP();

	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic); /* initialise graphics */
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	EcsDrawBMP(image1, pScrMgr); /* Demo Welcome */
	// toggleIm = 0;

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
			LcdMsg("Press button 1");
			LcdLine2();
			LcdMsg("to open");

			// EcsDrawBMP(door_open, pScrMgr); /* Door Open Image*/

			switch (KeyBeep())
			{
			case 1:
				vault_options_screen();
				// Do not insert break; here. We want to execute the default so that
				// we can pres any button to close the door/
			default:
				// Press a button to close the safe
				LcdClear();
				LcdLine1();
				LcdMsg("Press any button");
				LcdLine2();
				LcdMsg("to close safe");
				switch (KeyBeep())
				{
				case 1:
					// closing door image to be inserted here
					welcome_flag = 1;
					break;
				default:
					// closing door image to be inserted here
					welcome_flag = 1;
					break;
				}

				break;
			}
		}

		if (result != 4231 && welcome_flag == 0 && welcome_counter <= 3)
		{
			++welcome_counter;
			LcdClear();
			LcdLine1();
			LcdMsg("One more time ");
			LcdLine2();
			LcdMsg("3 tries given");
			Sleep(1000);
			result = 0;
			welcome_flag = 1;
		}
		else if (result != 4231 && welcome_flag == 0 && welcome_counter > 3) // after 3 tries
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
	LcdMsg("Enter a 4");
	LcdLine2();
	LcdMsg(" digit key");

	// EcsDrawBMP(welcome_image, pScrMgr); /* Welcome Image*/

	// welcome_flag = 1; //seems unnecessary
	while (welcome_flag == 1)
	{
		switch (KeyBeep())
		{
		case 1: //Number 1 has been entered
			LcdClear();
			LcdLine1();
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
			LcdClear();
			LcdLine1();
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
			LcdClear();
			LcdLine1();
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
			LcdClear();
			LcdLine1();
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
		case 5:
			// int result = 0; // declared already just in case :)

			for (int i_result = 0; i_result < 4; i_result++)
			{
				result *= 10;
				result += security_key_array[i_result];
			}
			LcdClear();
			LcdLine1();
			LcdMsg("Your key is");
			LcdLine2();
			LcdMsg("shown in screen");
			printf("%d", result); // debugging
			Sleep(5000);		  // wait for the user to read

			welcome_flag = 0; // quit the welcome function
			break;
		}
	}
}

void vault_options_screen()
{
	// EcsDrawBMP(vault_option_image, pScrMgr); /* Vault Option Screen*/
	LcdClear();
	LcdLine1();
	LcdMsg("Enter option ");
	LcdLine2();
	LcdMsg("1 2 or 3");
	Sleep(10); // wait for the user to read

	switch (KeyBeep())
	{
	case 1:
		withdraw();
		break;
	case 2:
		deposit();
		break;
	case 3:
		// EcsDrawBMP(image1, pScrMgr); /* Default gold bar image */
		Sleep(50);
		break;
	default:
		// need to go back to main screen
		break;
	}
}

void withdraw()
{
	// EcsDrawBMP(vault_option_image, pScrMgr); /* Vault Option Screen*/
	LcdClear();
	LcdLine1();
	LcdMsg("Press 1");
	LcdLine2();
	LcdMsg(" to withdraw");
	Sleep(10); // wait for the user to read

	switch (KeyBeep())
	{
	case 1:
		// insert image here 1 goldbar removed from the default image
		// EcsDrawBMP(image1, pScrMgr); /* 1 gold bar missing */
		Sleep(50);
		break;
	case 2:
		//
		break;
	case 3:
		// insert image here 3 goldbars removed from the default image
		break;
	default:
		LcdClear();
		LcdLine1();
		LcdMsg("Try again!");
		LcdLine2();
		LcdMsg("one more time");
		Sleep(10); // wait for the user to read
		break;
	}
}

void deposit()
{
	// EcsDrawBMP(image1, pScrMgr); /* insert default gold image here */
	Sleep(10);

	LcdClear();
	LcdLine1();
	LcdMsg("Press 1");
	LcdLine2();
	LcdMsg(" to deposit");
	Sleep(10); // wait for the user to read

	switch (KeyBeep())
	{
	case 1:
		// insert image here 1 goldbar added to the default image
		// EcsDrawBMP(image1, pScrMgr); /* 1 gold bar added */
		Sleep(5000);
		break;
	case 2:
		//
		break;
	case 3:
		// insert image here 3 goldbars added to the default image
		break;
	default:
		LcdClear();
		LcdLine1();
		LcdMsg("Try again!");
		LcdLine2();
		LcdMsg("one more time");
		Sleep(10); // wait for the user to read
		break;
	}
}