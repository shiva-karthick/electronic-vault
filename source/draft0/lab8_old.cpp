/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#include "peg.hpp"
#include "lab8.h"
#include "math.h"
#include "HEADER.h"
#include <embkern.h>
#include <embclib.h>
#include <malloc.h>
#include <video.h>

#include "tunes.inc"
#include <process.h>



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

unsigned int __stdcall sm_thread(void* pArguments);
unsigned int __stdcall music_thread(void* pArguments);

void Count();


void main()
{

HANDLE hThread_sm,hThread_music;
	unsigned int threadID_sm,threadID_music;
    
	Ubyte key;
	char t;
	char LCDStr[7];
	char k, s[10];

    PegPresentationManager *pScrMgr;
	EcsPic *pEcsPic;

	HANDLE hpEcsPic, hpScrMgr,hGuiThread;

	char file1[] ="C:\\NEW\\LIFT.BMP";
	char file2[] ="C:\\NEW\\floor1.BMP";
	char file3[] ="C:\\NEW\\moving2.BMP";
	char file4[] ="C:\\NEW\\floor2.BMP";
	char file5[] ="C:\\NEW\\moving3.BMP";
	char file6[] ="C:\\NEW\\floor3.BMP";
	char file7[] ="C:\\NEW\\moving4.BMP";
	char file8[] ="C:\\NEW\\floor4.BMP";
	/*char file5[] ="C:\\NEW\\THANKYOU.BMP";*/

	/* Initialise graphics */	
	EcsGuiInit(&hGuiThread, &hpScrMgr, &hpEcsPic);	
	pEcsPic = (EcsPic *)hpEcsPic;
	pScrMgr = (PegPresentationManager *)hpScrMgr;
	/* Initialise graphics */	

char previouslevel=1, currentlevel, movelift;
 	LedDisp(0x1);
    LcdInit();		/* Initialise Lcd screen */
	LcdLine1();LcdMsg("    Level  1    ");
    LcdLine2();LcdMsg("                ");
	BEEP(); 
	hThread_sm = (HANDLE)_beginthreadex(NULL,0,&sm_thread,NULL,0,&threadID_sm);
	SuspendThread(hThread_sm);
	hThread_music = (HANDLE)_beginthreadex(NULL,0,&music_thread,NULL,0,&threadID_music);
	SuspendThread(hThread_music);

	while(1)
	{
		EcsDrawBMP(file1, pScrMgr);	/* Welcome */
		Sleep(3000);
		EcsDrawBMP(file2, pScrMgr);
		key = (KeyBeep());
		switch (key)
		{
		case 0: LcdLine1();LcdMsg("   Alarm Press ");
	            LcdLine2();LcdMsg("                ");
				ResumeThread(hThread_music);
				Count();
				Sleep(1000);
				SuspendThread(hThread_music);
				break;
		case 1 : //Go to Level 1
			    EcsDrawBMP(file2, pScrMgr);
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(1500);
				LcdClear();
                for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");

		
				}
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(1000);
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				previouslevel=1;
				break;
				
		case 2 : //Go to Level2
				EcsDrawBMP(file3, pScrMgr);
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  2    ");
				Sleep(1500);
				LcdClear();
				
				if(key>previouslevel)
				{
                	for(t=1;t<key;t++)
					{
					
						previouslevel++;
						Spin(CW,200,1);
						LcdLine1();
						itoa((int)previouslevel,s,16);
						EcsDrawBMP(file4, pScrMgr);
						LcdMsg("    Level  ");
						LcdMsg(s);
						LcdMsg("    ");
					}
					previouslevel=2;

				}
				else
				{
				
					for(t=previouslevel;t>key;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(file4, pScrMgr);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=2;
				}

				Sleep(1000);
	
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  2    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  2    ");
				LcdLine2();LcdMsg("                ");
			     Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
				break;
		case 3 : // Go to Level3
			EcsDrawBMP(file5, pScrMgr);
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  3    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(file6, pScrMgr);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=3;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(file6, pScrMgr);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=3;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  3    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  3    ");
				LcdLine2();LcdMsg("                ");
				 Sleep(2000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
		
				Sleep(1000);
				break;
				
		case 4 : //Go to Level4
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  4    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					EcsDrawBMP(file7, pScrMgr);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=4;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					EcsDrawBMP(file7, pScrMgr);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=4;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  4    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(4000);
				//SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  4    ");
				LcdLine2();LcdMsg("                ");
				 Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
				Sleep(1000);
				break;
case 5 : //Go to Level5
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  5    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=5;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=5;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  5    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				//SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  5    ");
				LcdLine2();LcdMsg("                ");
				 Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
				    break;
		case 6 : //Go to Level6
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  6    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");

		
					}
					previouslevel=6;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=6;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  6    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  6    ");
				LcdLine2();LcdMsg("                ");
			 Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
				break;
		case 7:
		    	LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  7    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=7;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=7;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  7    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  7    ");
				LcdLine2();LcdMsg("                ");
				 Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
				break;
		case 8:
			    LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  8    ");
				Sleep(1500);
				LcdClear();
				if(key>previouslevel)
				{
                	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");

	
					}
					previouslevel=8;
				}
				else
				{
					for(t=previouslevel;t<key;t--)
					{
					
					previouslevel--;
					Spin(CW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
					previouslevel=8;
				}

				
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  8    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  8    ");
				LcdLine2();LcdMsg("                ");
				 Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
		       break;
		case 9:
		    	LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  9    ");
				Sleep(1500);
				LcdClear();
               	for(t=previouslevel;t<key;t++)
					{
					
					previouslevel++;
					Spin(CW,200,1);
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					}
				previouslevel=9;		
				Sleep(1500);
				ResumeThread(hThread_music);
                LcdClear();
                LcdLine1();LcdMsg("    Level  9    ");
				LcdLine2();LcdMsg(" Floor reached! ");
				Sleep(1000);
				SuspendThread(hThread_music);
				LcdLine2();LcdMsg("   Door  Open   ");
				Sleep(2000);
				LcdLine2();LcdMsg("   Door Close   ");
				Sleep(2000);
				LcdLine1();LcdMsg("    Level  9    ");
				LcdLine2();LcdMsg("                ");
				  Sleep(10000);
		       if(ScanKey()==0xff)
				{
				LcdLine1();LcdMsg(" Lift moving to ");
	            LcdLine2();LcdMsg("    Level  1    ");
				Sleep(100);
				LcdClear();
				for(t=previouslevel;t>1;t--)
					{
					
					previouslevel--;
					Spin(CCW,200,1);	
					LcdLine1();
					itoa((int)previouslevel,s,16);
					LcdMsg("    Level  ");
					LcdMsg(s);
					LcdMsg("    ");
					
					}
				Sleep(1000);

				LcdClear();
				LcdLine1();LcdMsg("    Level  1    ");
				LcdLine2();LcdMsg("                ");
				Sleep(1000);
				previouslevel=1;

				}
	        	break;

		case 10: 
			    LcdLine1();LcdMsg("   Door  Open   ");
	            LcdLine2();LcdMsg("                ");
				break;

		case 11:  
			    LcdLine1();LcdMsg("   Door Close   ");
	            LcdLine2();LcdMsg("                ");
				break;

		default :
			 
				printf("Press select 2 to 9\n");
				LcdLine1();LcdMsg("    Wrong Key    ");
				LcdLine2();LcdMsg("Press Again:2-9");
				Sleep(1000);
				break;




		}
				

	}



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

unsigned int __stdcall sm_thread(void* pArguments)
{
	while(1)
	{
		Spin( CW,200,1); // turn motor clockwise, 100 steps
		Spin(CCW,200,1); // turn motor counterclockwise, 100 steps
	}
	return(0);
}


unsigned int __stdcall music_thread(void* pArguments)
{
	
	while(1) 
	{
		PlaySong((const char*)MinuetG);
		Sleep(500);
		PlaySong((const char*)Hawaii);
		Sleep(500);
		PlaySong((const char*)BuPaBuPa);
		Sleep(500);
	}
	return(0);
}

void Count()
{
 char time;
 char LCDStr[17];
 char Test;
 
 LcdClear();
 for(time=0; time<60;time++){
	 sprintf(LCDStr,"Minute:%d",time);

     LcdLine1();LcdMsg(LCDStr);Sleep(500); //Ubyte
 }
// return(0);
}

