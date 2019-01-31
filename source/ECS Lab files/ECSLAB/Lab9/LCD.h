#define Ubyte unsigned char
#define Ushort unsigned short int
#define Uword unsigned int
#define byte char
#define LEDPort   0x332
#define LcdPort   0x333

void LcdInit();	// initialise LCD to 4 bits format
void LcdCmd (Ubyte d);	// outputs a LCD command
void LcdData (Ubyte data); // outputs a LCD data
void LcdClear();	// clears the LCD
void LcdLine1();	// goto line 1
void LcdLine2();	// goto line 2
void LcdMsg(char *ptr); // display a string on LCD
