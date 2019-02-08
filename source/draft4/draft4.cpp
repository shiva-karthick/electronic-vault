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
void welcome();                           // welcome function
int welcome_flag = 1;                     // welcome function's global variable
int welcome_counter = 0;                  // count until 3 tries
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

    // Graphics code
    PegPresentationManager *pScrMgr;
    EcsPic *pEcsPic;

    HANDLE hpEcsPic, hpScrMgr, hGuiThread;

    void EcsGuiInit(HANDLE * hGuiThread, HANDLE * hpScrMgr, HANDLE * hpEcsPic);
    char EcsDrawBMP(char *file, PegPresentationManager *pScrMgr);

    // char image1[] = "C:\\images\\DEMO.BMP";
    // char image2[] = "C:\\images\\DEMOInv.BMP";

    char welcome_image[] = "C:\\safe\\WELCOME.BMP";
    char door_open[] = "C:\\safe\\OPENING.BMP";
	char door_close[] = "C:\\safe\\CLOSING.BMP";

    char second_one[] = "C:\\safe\\1.BMP";
    char second_two[] = "C:\\safe\\2.BMP";
    char second_three[] = "C:\\safe\\3.BMP";
    char second_four[] = "C:\\safe\\4.BMP";
    char second_five[] = "C:\\safe\\5.BMP";
    char second_six[] = "C:\\safe\\6.BMP";
    char second_seven[] = "C:\\safe\\7.BMP";
    char second_eight[] = "C:\\safe\\8.BMP";
    char second_nine[] = "C:\\safe\\9.BMP";
    char second_ten[] = "C:\\safe\\10.BMP";

    char menu_image[] = "C:\\safe\\MENU.BMP";

	char three_gold[] = "C:\\safe\\3GOLD.BMP";
	char four_gold[] = "C:\\safe\\4GOLD.BMP";
	char five_gold[] = "C:\\safe\\5GOLD.BMP";
	char six_gold[] = "C:\\safe\\6GOLD.BMP";
	char seven_gold[] = "C:\\safe\\7GOLD.BMP";
	char eight_gold[] = "C:\\safe\\8GOLD.BMP";
	char nine_gold[] = "C:\\safe\\9GOLD.BMP";
	
	char background[] = "C:\\safe\\BG.BMP";

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
    // EcsDrawBMP(image1, pScrMgr); /* Demo Welcome */
    // toggleIm = 0;

    hThread_sm = (HANDLE)_beginthreadex(NULL, 0, &sm_thread, NULL, 0, &threadID_sm);
    SuspendThread(hThread_sm);
    hThread_music = (HANDLE)_beginthreadex(NULL, 0, &music_thread, NULL, 0, &threadID_music);

    SuspendThread(hThread_music);
    while (1)
    {
        Sleep(10);

        if (welcome_flag == 1)
        {
            // ===============welcome(); function is placed here===============
            // ===============start of welcome() function===============
            LcdClear();
            LcdLine1();
            LcdMsg("Enter a 4");
            LcdLine2();
            LcdMsg(" digit key");

            EcsDrawBMP(welcome_image, pScrMgr); /* Welcome image */

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
                case 0: // changed from case 5 to case 0
                    // int result = 0; // declared already just in case :)

                    for (int i_result = 0; i_result < 4; i_result++)
                    {
                        result *= 10;
                        result += security_key_array[i_result];
                    }
                    LcdClear();
                    LcdLine1();
                    LcdMsg("Processing ...");
                    LcdLine2();
                    LcdMsg("Please wait...");
                    printf("%d", result); // debugging
                    Sleep(2000);          // wait for the user to read

                    welcome_flag = 0; // quit the welcome function
                    break;
                }
            }
            // ===============end of welcome function===============
        }

        if (result == 4231 && welcome_flag == 0)
        {
            // Press a button to open the safe
            LcdClear();
            LcdLine1();
            LcdMsg("Press button 1");
            LcdLine2();
            LcdMsg("to open");

            EcsDrawBMP(door_open, pScrMgr); /* Door Open Image*/

            switch (KeyBeep())
            {
            case 1:
                //===============vault_options_screen();===============

                // start of vault_options_screen();
                EcsDrawBMP(menu_image, pScrMgr); /* Menu Screen*/
                LcdClear();
                LcdLine1();
                LcdMsg("Enter option ");
                LcdLine2();
                LcdMsg("1 2 or 3");
                Sleep(10); // wait for the user to read

                switch (KeyBeep())
                {
                case 1:
                    //===============withdraw();===============

                    // ===============start of withdraw function===============
                    
                    LcdClear();
                    LcdLine1();
                    LcdMsg("Press 1");
                    LcdLine2();
                    LcdMsg(" to withdraw");
					EcsDrawBMP(six_gold, pScrMgr); /* Vault Option Screen*/
                    Sleep(10); // wait for the user to read
					 

                    switch (KeyBeep())
                    {
                    case 1:
                        // insert image here 1 goldbar removed from the default image
                        EcsDrawBMP(five_gold, pScrMgr); /* Vault Option Screen*/
                        Sleep(50);
                        break;
                    case 2:
                        // insert image here 2 goldbar removed from the default image
                        EcsDrawBMP(four_gold, pScrMgr); /* 2 gold bars removed */
                        Sleep(50);
                        break;
                    case 3:
                        // insert image here 3 goldbars removed from the default image
                        EcsDrawBMP(three_gold, pScrMgr); /* Vault Option Screen*/
                        Sleep(50);
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
                    // ===============end of withdraw function===============
                    break;
                case 2:
                    // =====deposit();=====
                    // start of deposit function
                    // EcsDrawBMP(image1, pScrMgr); /* insert default gold image here */
                    Sleep(10);

                    LcdClear();
                    LcdLine1();
                    LcdMsg("Press 1");
                    LcdLine2();
                    LcdMsg(" to deposit");
					EcsDrawBMP(six_gold, pScrMgr);
                    Sleep(10); // wait for the user to read

                    switch (KeyBeep())
                    {
                    case 1:
                        // insert image here 1 goldbar added to the default image
                        EcsDrawBMP(seven_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(2000);
                        break;
                    case 2:
                        // insert image here 2 goldbar added to the default image
                        EcsDrawBMP(eight_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(2000);
                        break;
                    case 3:
                        // insert image here 3 goldbar added to the default image
                        EcsDrawBMP(nine_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(2000);
                        break;
                    default:
                        LcdClear();
                        LcdLine1();
                        LcdMsg("Try again!");
                        LcdLine2();
                        LcdMsg("one more time");
                        Sleep(1000); // wait for the user to read
                        break;
                    }
                    // end of deposit function
                    break;
                case 3:
                    EcsDrawBMP(background, pScrMgr); /* Default gold bar image */
                    Sleep(2000);
                    break;
                default:
                    // need to go back to main screen
                    break;
                }

                // ===============end of vault_options_screen();===============

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
                    EcsDrawBMP(door_close, pScrMgr); /* Door Close Image*/
                    welcome_flag = 1;
                    break;
                default:
                    EcsDrawBMP(door_close, pScrMgr); /* Door Close Image*/
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

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_one, pScrMgr); /* 1 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_two, pScrMgr); /* 2 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_three, pScrMgr); /* 3 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_four, pScrMgr); /* 4 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_five, pScrMgr); /* 5 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_six, pScrMgr); /* 6 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_seven, pScrMgr); /* 7 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_eight, pScrMgr); /* 8 second Image*/

			Sleep(1000); // sleep for 1s
			EcsDrawBMP(second_nine, pScrMgr); /* 9 second Image*/

			Sleep(1500); // sleep for 1.5s
			EcsDrawBMP(second_ten, pScrMgr); /* 10 second Image*/
            
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

// ===============Own functions===============

void welcome()
{
    LcdClear();
    LcdLine1();
    LcdMsg("Enter a 4");
    LcdLine2();
    LcdMsg(" digit key");

    // EcsDrawBMP(image2, pScrMgr); /* Demo Welcome */

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
            Sleep(5000);          // wait for the user to read

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