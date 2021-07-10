#include <LiquidCrystal.h>
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>
#include <Wire.h>
#include <Keypad_I2C.h>
#include <Keypad.h>


//---- definitions---
#define UTILsW 13
#define RampSW 11
#define CHslcSW 12
#define NDsw 4
#define Rb 3
#define Ra 2
#define CH1ONoff 19
#define CH2ONoff 18
#define S_LFT A13
#define S_RT A14
#define KeyI2CADDR 0x38
#define DEBOUNCE 150

//-----virables---
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
byte rowPins[ROWS] = { 2, 1, 0,3 }; //connect to the row pinouts of the keypad  -
byte colPins[COLS] = { 6, 5, 4 }; //connect to the column pinouts of the keypad |
char hexaKeys[ROWS][COLS] = {
  {'7','8','9'},
  {'4','5','6'},
  {'1','2','3'},
  {',','0','#'}
};
unsigned int Pos = 7;
volatile bool encoderPinALast = LOW;
volatile bool encoderaPinALast = LOW;
volatile bool n= LOW;
unsigned long previousMillis = 0;
volatile int FQ[7]{0,0,0,0,0,0,0};
volatile long FrQ = 0000000;
volatile float Amp = 00.00;
volatile int dig=0;


//---flags---
bool CHFLG = false;
bool LCDupDate = false;
int Mode = 0; //0=F 1=A 2=O 3P


//-----object definitions ----
Keypad_I2C customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, KeyI2CADDR);
//LiquidCrystal lcd(34, 35, 39, 36, 37, 38);
LiquidCrystal lcd(22, 23, 25, 24, 26, 28);

void setup() {
	//---lib initialzation---
  Serial.begin(9600);
  lcd.begin(20, 4);
	Wire.begin();
	customKeypad.begin();
 	
	Serial.println("lib initialzation");


	//---pin initalzation---

	pinMode(CHslcSW, INPUT_PULLUP);
	pinMode(RampSW, INPUT_PULLUP);
	pinMode(Ra, INPUT_PULLUP);
	pinMode(Rb, INPUT_PULLUP);
	pinMode(S_LFT, INPUT_PULLUP); 
	pinMode(S_RT, INPUT_PULLUP);
  
 Serial.println("pin initalzation");

	//---interup setup--
	attachPinChangeInterrupt( digitalPinToPCINT(CHslcSW), ChannelSellect, FALLING);
	attachPinChangeInterrupt(digitalPinToPCINT(RampSW), ramp, FALLING);
	attachPinChangeInterrupt(digitalPinToPCINT(S_LFT), isr_lft, FALLING);
	attachPinChangeInterrupt(digitalPinToPCINT(S_RT), isr_rt, FALLING);
	attachInterrupt(digitalPinToInterrupt(Ra), Encoder, CHANGE);
 Serial.println("interupt");
	
 //Lcd inital draw , (to be moved to separete function ? ) 
	lcd.setCursor(0, 0);
	lcd.print("FREQ:    00000000 Hz");
	lcd.setCursor(0, 1);
	lcd.print("PHASE:        000 *");
	lcd.setCursor(0, 2);
	lcd.print("AMPL:       00,00 V");
	lcd.setCursor(0, 3);
	lcd.print("OFFSET:     00,00 V");
}

void lcdDraw() {
	if (LCDupDate) {
		//here we update sepere feilds like frq,amp,ofst,wavetype etc
	}
}

void loop() {
	char customKey = customKeypad.getKey();
	lcdDraw();
	if (customKey != NO_KEY && customKey != '#') {
		
    FQ[dig]=customKey - '0';
    for(int i=0;i<=6;i++){
		if (i != 6) { Serial.print(FQ[i]);}
		if (i == 6) { Serial.println(FQ[i]);} 
    }//code for handling the keypad,
		dig++;
	}
	
	//!!!! ?? CONNECTION TO THE ROTTERY ENCODER VIRABLE FROM THE KEYBOARD  !!!!

	//for the connection : while a key is pressed , the area of frq will be eraced . 
	//Fq[] will be displayd and the user will be able to set the frequency , with the # key ,
	// the value will be tranferd to the "main" value


	if (CHFLG) {
		Serial.println("chflag");
		CHFLG = false;
	}//flag testing
}

void ChannelSellect() {

	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 200)
	{
		CHFLG = true;//flag testing 
	}
	last_interrupt_time = interrupt_time;	
}
void Encoder() {//Rottery encoder interupt service rutine ,		
	n = digitalRead(Ra);
	double po= power(10, dig);
	if ((encoderPinALast == LOW) && (n == HIGH)) {
		if (digitalRead(Rb) == LOW) {
			switch (Mode)//this will select the mode that the 
			{//			encoder will operate at (frequency or amplitude ,another layer will be added for channel selection
			case 0://frq seting				
				FrQ -= po;
				/*
				with a 10mhz selectable range , the number gets to big to control with just the 
				encoder , thus with 2 buttons we select witch of the 8 digits will be controled .
				This is done with a power , eg: frq=10000hz and we want to set it to 11khz , 
				we take 10000 we add 10^3 and viola! 11000 
				*/
				break;
			case 1://amplitude
				break;
			}						
			
		}
		else {
			FrQ += po;
		}		
	}
	encoderPinALast = n;
	//---from this point ,feedback code to user 
Serial.print(FrQ);
Serial.print("  ");
Serial.println(po);
}
void isr_lft() {//button for moving the cursor left 
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 200)
	{			
		if (dig > 0) { dig--; }
		Serial.print("dig: ");
		Serial.println(dig);
	}
	last_interrupt_time = interrupt_time;
	
}
void isr_rt() {//button for moving the cursor right 
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 200)
	{
		if (dig >= 0 && dig < 7) { dig++; }
		Serial.print("dig: ");
		Serial.println(dig);
		
	}
	last_interrupt_time = interrupt_time;
}
void ramp() {//button for ramp ,temporaly for mode switch
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 200)
	{
		if (Mode == 4) {
			Mode = 0;
		}
		if (Mode >= 0) {
			Mode++;
		}
		Serial.println(Mode);

	}
	last_interrupt_time = interrupt_time;
}
unsigned long power(int a, int b) {//thats for calculating 10^...
	unsigned long res;
	if (b == 0) {
		res = 1;
	}
	else {
		res = a;
		for (int i = 0; i < (b - 1); i++) {
			res *= a;
		}
	}
	return res;
}