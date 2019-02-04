

#include "peg.hpp"
#include "demo.h"
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
void demo();
int choice=0;

//extern volatile BOOL StartDemo;

void main(int argc, char **argvp)
{
   demo();
   return;
}

/* display message to host console */
void EcsConsoleMsg(char *pMsg)
{
	EtsSelectConsole(ETS_CO_HOST);
	printf(pMsg);
}