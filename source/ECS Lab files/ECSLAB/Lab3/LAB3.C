/***************************/
/*      Keypad lab     */
/***************************/


unsigned char ProcKey ();
unsigned char ScanKey ();

#define LEDPort   0x332          /* LED Port  */
#define KbdPort   0x334           /* Key pad port */

#define Col7Lo    ____                      /*  column 7 scan */
#define Col6Lo    ____                      /*  column 6 scan */
#define Col5Lo    ____                      /*  column 5 scan */
#define Col4Lo    ____                      /*  column 4 scan */
#define TRUE      1                         /*  neater to use! */

const unsigned char ScanTable [12] =
/*    0    1     2     3   */
{    ____, ____, ____, ____,
/*    4      5      6   7  */
     ____, ____, ____, ____,
/*    8     9     A     B  */
     ____, ____, ____, ____
};
/* store this table in code space (ROM) */
const unsigned char Bin2LED[] =
/*0,       1,       2,       3        0-3 */
{ ____    ,____    ,____    ,____,
/*4,       5,       6,       7        4-7 */
  ____    ,____    ,____    ,____,
/*8,       9,       A,       B        8-B */
  ____    ,____    ,____    ,____,
/*C,       D,       E,       F        C-F */
  ____    ,____    ,____    ,____ 
};

    unsigned char ScanCode;      /* hold scan code returned     */

/******************************************************************************/
/***************************      MAIN PROGRAM      ***************************/
/******************************************************************************/
void main ( void )
{                          /* main entry for program      */

    while (TRUE)
    {          
	unsigned char i;
	i = ScanKey();
	if (i != 0xFF)                  /* if key is pressed **/
	    _outp(LEDPort ,Bin2LED[i]);     /* output to LED */
    }                                   
}                                                       /* loop forever */
/* Check for key press: if none, return 0xFF */
unsigned char ScanKey() 
{
	_outp(KbdPort ,Col7Lo);             /* bit 7 low */
	  ScanCode = _inp(KbdPort);             /* Read */
	  ScanCode |= 0xF0;               /* high nybble to 1 */
	  ScanCode &= Col7Lo;             /* AND back scan value */        
  if (ScanCode != Col7Lo)         /* in <> out get key */
	    return ProcKey();

	_outp(KbdPort ,Col6Lo);               /* bit 6 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col6Lo;             /* AND back scan value */
	if (ScanCode != Col6Lo)         /* in <> out get key and display */
	    return ProcKey();

	_outp(KbdPort ,Col5Lo);               /* bit 5 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col5Lo;             /* AND back scan value */
	if (ScanCode != Col5Lo)         /* in <> out get key and display */
	    return ProcKey();

	_outp(KbdPort ,Col4Lo);               /* bit 4 low  */
	ScanCode = _inp(KbdPort);             /* Read */
	ScanCode |= 0xF0;               /* high nybble to 1 */
	ScanCode &= Col4Lo;             /* AND back scan value */
	if (ScanCode != Col4Lo)         /* in <> out get key and display */
	    return ProcKey();
	
	  return 0xFF;

    }   /* while */
    /* main */

/* Procedure here */
unsigned char ProcKey()
{
  unsigned char i;                      /* index of scan code returned */
    for (i = 0 ; i <= 12; i++)
    if (ScanCode == ScanTable [i])      /* search in table */
	    return i;                   /* exit loop if found */
    if (i == 12)               
	  return 0xFF;              /* if not found, return 0xFF */
    return (0);
}
