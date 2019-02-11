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
unsigned int digit5 = 0;
unsigned int digit6 = 0;
unsigned int digit7 = 0;
unsigned int digit8 = 0;
unsigned int digit9 = 0;
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
    // ===============images declaration start here===============
    char welcome_image[] = "C:\\safe\\WELCOME.BMP";
    char pressed_0[] = "C:\\safe\\PRESSED0.BMP";
    char pressed_1[] = "C:\\safe\\PRESSED1.BMP";
    char pressed_2[] = "C:\\safe\\PRESSED2.BMP";
    char pressed_3[] = "C:\\safe\\PRESSED3.BMP";
    char pressed_4[] = "C:\\safe\\PRESSED4.BMP";
    char pressed_5[] = "C:\\safe\\PRESSED5.BMP";
    char pressed_6[] = "C:\\safe\\PRESSED6.BMP";
    char pressed_7[] = "C:\\safe\\PRESSED7.BMP";
    char pressed_8[] = "C:\\safe\\PRESSED8.BMP";
    char pressed_9[] = "C:\\safe\\PRESSED9.BMP";

    char door_open[] = "C:\\safe\\OPENING.BMP";
    char door_close[] = "C:\\safe\\CLOSING.BMP";
    char door_close_2[] = "C:\\safe\\CLOSING2.BMP";

    // disable pictures
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
    char withdraw_image[] = "C:\\safe\\WITHDRAW.BMP";
    char deposit_image[] = "C:\\safe\\DEPOSIT.BMP";

    char three_gold[] = "C:\\safe\\3GB.BMP";
    char three_acc[] = "C:\\safe\\3ACC.BMP";

    char four_gold[] = "C:\\safe\\4GB.BMP";
    char four_acc[] = "C:\\safe\\4ACC.BMP";

    char five_gold[] = "C:\\safe\\5GB.BMP";
    char five_acc[] = "C:\\safe\\5ACC.BMP";

    char six_gold[] = "C:\\safe\\6GB.BMP";
    char six_acc[] = "C:\\safe\\6ACC.BMP";

    char seven_gold[] = "C:\\safe\\7GB.BMP";
    char seven_acc[] = "C:\\safe\\7ACC.BMP";

    char eight_gold[] = "C:\\safe\\8GB.BMP";
    char eight_acc[] = "C:\\safe\\8ACC.BMP";

    char nine_gold[] = "C:\\safe\\9GB.BMP";
    char nine_acc[] = "C:\\safe\\9ACC.BMP";

    char background[] = "C:\\safe\\BG.BMP";

    char try_again_1[] = "C:\\safe\\TRYAGAIN.BMP";
    char try_again_2[] = "C:\\safe\\TRYAGAIN2.BMP";

    char try_1[] = "C:\\safe\\1TRY.BMP";
    char try_2[] = "C:\\safe\\2TRY.BMP";
    char try_3[] = "C:\\safe\\3TRY.BMP";

    // ===============images declaration end here===============

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
                    // insert pressed_1.bmp image here
                    EcsDrawBMP(pressed_1, pScrMgr); /* pressed_1.bmp */
                    Sleep(500);

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
                    // insert pressed2.bmp image here
                    EcsDrawBMP(pressed_2, pScrMgr); /* pressed_2.bmp */
                    Sleep(500);

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
                    // insert pressed3.bmp image here
                    EcsDrawBMP(pressed_3, pScrMgr); /* pressed_3.bmp */
                    Sleep(500);

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
                    // insert pressed4.bmp image here
                    EcsDrawBMP(pressed_4, pScrMgr); /* pressed_4.bmp */
                    Sleep(500);

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

                case 5: // Number 5 has been entered
                    LcdClear();
                    LcdLine1();
                    LcdMsg("5 entered");
                    digit5 = 5;

                    EcsDrawBMP(pressed_5, pScrMgr); /* pressed_5.bmp */
                    Sleep(500);

                    if (*security_key_array == 0)
                    {

                        security_key_array[pointer_counter] = digit5;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit5;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit5;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit5;
                    }

                    break;

                case 6: // Number 6 has been entered
                    LcdClear();
                    LcdLine1();
                    LcdMsg("6 entered");
                    digit6 = 6;
                    // insert pressed_6.bmp image here
                    EcsDrawBMP(pressed_6, pScrMgr); /* pressed_6.bmp */
                    Sleep(500);

                    if (*security_key_array == 0)
                    {

                        security_key_array[pointer_counter] = digit6;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit6;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit6;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit6;
                    }

                    break;

                case 7: // Number 7 has been entered
                    LcdClear();
                    LcdLine1();
                    LcdMsg("7 entered");
                    digit7 = 7;
                    // insert pressed_7.bmp image here
                    EcsDrawBMP(pressed_7, pScrMgr); /* pressed_7.bmp */
                    Sleep(500);

                    if (*security_key_array == 0)
                    {

                        security_key_array[pointer_counter] = digit7;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit7;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit7;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit7;
                    }

                    break;

                case 8: // Number 8 has been entered
                    LcdClear();
                    LcdLine1();
                    LcdMsg("8 entered");
                    digit8 = 8;
                    // insert pressed_8.bmp image here
                    EcsDrawBMP(pressed_8, pScrMgr); /* pressed_8.bmp */
                    Sleep(500);

                    if (*security_key_array == 0)
                    {

                        security_key_array[pointer_counter] = digit8;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit8;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit8;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit8;
                    }

                    break;

                case 9: // Number 9 has been entered
                    LcdClear();
                    LcdLine1();
                    LcdMsg("9 entered");
                    digit9 = 9;
                    // insert pressed_9.bmp image here
                    EcsDrawBMP(pressed_9, pScrMgr); /* pressed_9.bmp */
                    Sleep(500);

                    if (*security_key_array == 0)
                    {

                        security_key_array[pointer_counter] = digit9;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit9;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit9;
                        ++pointer_counter;
                    }
                    else if (*(security_key_array + pointer_counter) == 0)
                    {

                        security_key_array[pointer_counter] = digit9;
                    }

                    break;

                case 0: // changed from case 5 to case 0
                    // int result = 0; // declared already just in case :)
                    EcsDrawBMP(pressed_0, pScrMgr); /* pressed_0.bmp */
                    Sleep(10);

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
            Sleep(10);

            switch (KeyBeep())
            {
            case 1:
                //===============vault_options_screen();===============

                // start of vault_options_screen();
                EcsDrawBMP(menu_image, pScrMgr); /* Menu Screen*/
                Sleep(1000);
                LcdClear();
                LcdLine1();
                LcdMsg("Enter option ");
                LcdLine2();
                LcdMsg("1 2 or 3");

                // insert option menu screen here
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

                    // insert withdraw menu here
                    EcsDrawBMP(withdraw_image, pScrMgr); /* Withdraw menu Screen*/
                    Sleep(1500);                         // wait for the user to read
                    //
                    EcsDrawBMP(six_gold, pScrMgr); /* Vault Option Screen*/
                    Sleep(1000);                   // wait for the user to read

                    switch (KeyBeep())
                    {
                    case 1:
                        // insert image here 1 goldbar removed from the default image
                        EcsDrawBMP(five_gold, pScrMgr); /* 1 goldbar removed*/
                        Sleep(1000);
                        EcsDrawBMP(five_acc, pScrMgr); /* 1 goldbar removed*/
                        Sleep(1000);
                        break;
                    case 2:
                        // insert image here 2 goldbar removed from the default image
                        EcsDrawBMP(four_gold, pScrMgr); /* 2 gold bars removed */
                        Sleep(1000);
                        EcsDrawBMP(four_acc, pScrMgr); /* 1 goldbar removed*/
                        Sleep(1000);
                        break;
                    case 3:
                        // insert image here 3 goldbars removed from the default image
                        EcsDrawBMP(three_gold, pScrMgr); /* 3 goldbars removed*/
                        Sleep(1000);
                        EcsDrawBMP(three_acc, pScrMgr); /* 1 goldbar removed*/
                        Sleep(1000);
                        break;
                    default:
                        LcdClear();
                        LcdLine1();
                        LcdMsg("Try again!");
                        LcdLine2();
                        LcdMsg("one more time");
                        EcsDrawBMP(try_again_1, pScrMgr); /* try again 1 image*/
                        Sleep(1000);                      // wait for the user to read
                        break;
                    }
                    // ===============end of withdraw function===============
                    break;
                case 2:
                    // =====deposit();=====
                    // start of deposit function

                    LcdClear();
                    LcdLine1();
                    LcdMsg("Press 1");
                    LcdLine2();
                    LcdMsg(" to deposit");

                    EcsDrawBMP(deposit_image, pScrMgr); /* deposit.bmp */
                    Sleep(1500);                        // wait for the user to read
                    EcsDrawBMP(six_gold, pScrMgr);      /* insert default gold image here */
                    Sleep(1000);                        // wait for the user to read

                    switch (KeyBeep())
                    {
                    case 1:
                        // insert image here 1 goldbar added to the default image
                        EcsDrawBMP(seven_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(1000);
                        EcsDrawBMP(seven_acc, pScrMgr); /* 1 gold bar added */
                        Sleep(1000);
                        break;
                    case 2:
                        // insert image here 2 goldbar added to the default image
                        EcsDrawBMP(eight_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(1000);
                        EcsDrawBMP(eight_acc, pScrMgr); /* 1 gold bar added */
                        Sleep(1000);
                        break;
                    case 3:
                        // insert image here 3 goldbar added to the default image
                        EcsDrawBMP(nine_gold, pScrMgr); /* 1 gold bar added */
                        Sleep(2000);
                        EcsDrawBMP(nine_acc, pScrMgr); /* 1 gold bar added */
                        Sleep(1000);
                        break;
                    default:
                        LcdClear();
                        LcdLine1();
                        LcdMsg("Try again!");
                        LcdLine2();
                        LcdMsg("one more time");
                        Sleep(1000);                      // wait for the user to read
                        EcsDrawBMP(try_again_2, pScrMgr); /* try again 2 */
                        Sleep(1000);
                        break;
                    }
                    // end of deposit function
                    break;
                case 3:
                    EcsDrawBMP(six_gold, pScrMgr); /* 6 gold bar */
                    Sleep(1000);
                    EcsDrawBMP(six_acc, pScrMgr); /* 6 account gold bar */
                    Sleep(1000);
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
                    EcsDrawBMP(door_close_2, pScrMgr); /* Door Close Image*/
                    welcome_flag = 1;
                    break;
                }

                break;
            }
        }

        if (result != 4231 && welcome_flag == 0 && welcome_counter <= 3)
        {
            ++welcome_counter;
            if (welcome_counter == 0)
            {
                // insert image here
                EcsDrawBMP(try_1, pScrMgr); /* 1 TRY Image*/
                Sleep(1000);
            }
            else if (welcome_counter == 1)
            {
                // insert image here
                EcsDrawBMP(try_2, pScrMgr); /* 2 TRY Image*/
                Sleep(1000);
            }
            else if (welcome_counter == 2)
            {
                // insert image here
                EcsDrawBMP(try_3, pScrMgr); /* 3 TRY Image*/
                Sleep(1000);
            }
            LcdClear();
            LcdLine1();
            LcdMsg("One more time ");
            LcdLine2();
            LcdMsg("3 tries given");
            Sleep(1000);

            result = 0; /*reset all variables*/
            digit1 = 0; /*reset all variables*/
            digit2 = 0; /*reset all variables*/
            digit3 = 0; /*reset all variables*/
            digit4 = 0; /*reset all variables*/
            // security_key_array[4] = {0, 0, 0, 0};

            welcome_flag = 1; // go back to the welcome screen
        }
        else if (result != 4231 && welcome_flag == 0 && welcome_counter > 3) // after 3 tries
        {
            LcdClear();
            LcdLine1();
            LcdMsg("System is");
            LcdLine2();
            LcdMsg("Disabled !");

            Sleep(1000);                     // sleep for 1s
            EcsDrawBMP(second_one, pScrMgr); /* 1 second Image*/

            Sleep(1000);                     // sleep for 1s
            EcsDrawBMP(second_two, pScrMgr); /* 2 second Image*/

            Sleep(1000);                       // sleep for 1s
            EcsDrawBMP(second_three, pScrMgr); /* 3 second Image*/

            Sleep(1000);                      // sleep for 1s
            EcsDrawBMP(second_four, pScrMgr); /* 4 second Image*/

            Sleep(1000);                      // sleep for 1s
            EcsDrawBMP(second_five, pScrMgr); /* 5 second Image*/

            Sleep(1000);                     // sleep for 1s
            EcsDrawBMP(second_six, pScrMgr); /* 6 second Image*/

            Sleep(1000);                       // sleep for 1s
            EcsDrawBMP(second_seven, pScrMgr); /* 7 second Image*/

            Sleep(1000);                       // sleep for 1s
            EcsDrawBMP(second_eight, pScrMgr); /* 8 second Image*/

            Sleep(1000);                      // sleep for 1s
            EcsDrawBMP(second_nine, pScrMgr); /* 9 second Image*/

            Sleep(1500);                     // sleep for 1.5s
            EcsDrawBMP(second_ten, pScrMgr); /* 10 second Image*/
            Sleep(1000);

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