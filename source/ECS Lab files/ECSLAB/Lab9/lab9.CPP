/* Lab9 - Multitasking

   Three threads will be created in this experimnet
   1. the main application threa
   2. the stepper motor thread
   3. the LCD display thread

	Event synchronization will be used between main thread and stepper motor thread
	to execute the commands array

*/
#include <time.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "LCD.h"
#define Ubyte unsigned char
#define Ushort unsigned short int
#define Uword unsigned int
#define byte char

#define LEDPort   0x332		// LED Port
#define LCDPort   0x333		//LCD port
#define KbdPort   0x334		//Key pad port
#define	SMPort	  0x335
#define CW 0				// define stepper directions
#define CCW 1


void  Spin(char dir, int steps, char time);
unsigned int __stdcall sm_thread(void* pArguments);
//prototype for lcd thread
__________________________________________________;
typedef struct
{
	char dir;
	int steps;
	char time;
}MOTOR_CMD;

HANDLE hEvent_start,hEvent_end;
MOTOR_CMD motor_cmd[3],command;
int cmd_count;  //number of commands to be executed
int step_remaining;	//global var to hold remaining steps to move for stepper motor
const unsigned char Bin2LED[] =
/*0,       1,       2,       3        0-3 */
{ 0x40    ,0x79    ,0x24    ,0x30,
/*4,       5,       6,       7        4-7 */
  0x19    ,0x12    ,0x02    ,0x78,
/*8,       9,       A,       B        8-B */
  0x00    ,0x10    ,0x08    ,0x03,
/*C,       D,       E,       F        C-F */
  0x46    ,0x21    ,0x06    ,0x0E 
};

void main ( void )
{
	HANDLE hThread_sm,hThread_lcd;
	DWORD result;
	unsigned int threadID_sm,threadID_lcd;
	int count;
	printf("\nStarting Main thread...\n");
	
	//create the stepper motor thread
	_____________________________________________________________________________;
	hThread_lcd = (HANDLE)_beginthreadex(NULL,0,&lcd_thread,NULL,0,&threadID_lcd);
	hEvent_start = CreateEvent(NULL,FALSE,FALSE,NULL);
	hEvent_end = CreateEvent(NULL,FALSE,FALSE,NULL);
	/* set up motor commands in an array structure */
	cmd_count=3;	
	motor_cmd[0].dir=CW; motor_cmd[0].steps=200; motor_cmd[0].time=20;
	motor_cmd[1].dir=CCW; motor_cmd[1].steps=200; motor_cmd[1].time=30;
	motor_cmd[2].dir=CW; motor_cmd[2].steps=200; motor_cmd[2].time=40;
	SetEvent(hEvent_end);	/* done */

	count=cmd_count;
	while(1)
	{
		result=WaitForSingleObject(hEvent_end,500);	/* wait for SM thread to end */
		if (count>0 && result==WAIT_OBJECT_0)
		{
			command.dir = motor_cmd[cmd_count-count].dir;
			command.steps = motor_cmd[cmd_count-count].steps;
			command.time = motor_cmd[cmd_count-count].time;
			count--;
			SetEvent(hEvent_start);		/* tell SM thread to start */
			_outp(LEDPort,Bin2LED[cmd_count-count]);
		}
	/* repeat the commands */
	//printf("Remaining step = %d\n",step_remaining); /* this will affect SM !!! */
	if (count==0) count=count=cmd_count;
	}
}


unsigned int __stdcall sm_thread(void* pArguments)
{
	int j;

	printf("\nStarting stepper motor thread...\n");

	while(1)
	{
		WaitForSingleObject(hEvent_start,INFINITE);	/* wait to start */
		//Spin(command.dir,command.steps,command.time);
		for (j=command.steps;j>0;j--)
		{
			Spin(command.dir,1,command.time);
			step_remaining = j;		/* update global variable - to display */
		}
		Sleep(500);					/* wait 500 ms */
		//set the hEvent_end to signal the end of current motor command
		________________________;

	}
	return(0);
}

void  Spin(char dir, int steps, char time)
{
#define	    PtableLen	4

unsigned char Ptable []={1,2,4,8};
int		j;
int		n1chg;		/* +1 or -1 */
static  int phasecnt;	/* keep value between calls TL 19/7/2k7 */

	if (dir == CCW)
		n1chg = 1;		/* read phase values forward */
	else
		n1chg = -1;		/* read phase values backward */

	for (j=steps;j>0;j--)
	{
		_outp (SMPort,Ptable [phasecnt]);		/* output to port */
        Sleep(time);
		phasecnt = phasecnt + n1chg;
		if (phasecnt>=PtableLen)	/* forward, reached end of phase table */
			phasecnt=0;				/* back to zero */
		if (phasecnt<0)				/* backward */
			phasecnt=PtableLen-1;	/* start at table end */
	}
  return;
}	
	
unsigned int __stdcall lcd_thread(void* pArguments)
{
	printf("\nStarting LCD display thread...\n");
	LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg("Multitasking Lab");
    LcdLine2();LcdMsg("<<>><<>>");

	while(1)
	{
		LcdLine2();LcdMsg(">>>>>>>>>>>>>>>>");
		Sleep(100);
		LcdLine2();LcdMsg("                ");
		Sleep(100);
		LcdLine2();LcdMsg("<<<<<<<<<<<<<<<<");
		Sleep(100);
		LcdLine2();LcdMsg("                ");
		Sleep(100);
	}
	return(0);
}