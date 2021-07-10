

#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 25, 24, 26, 28);

int Fq[8] = { 0,1,2,3,4,5,6,7 };

void setup() {

	lcd.begin(20,4);
	Serial.begin(9600);
	lcd.clear();
	//lcd.print("hello world");
	for (int i = 0; i < 8; i++) {
		lcd.print(Fq[i]);
		Serial.println(i);
	}

}
void loop() {
	
	
	// Turn off the cursor:
	lcd.noCursor();
	delay(500);

	// Turn on the cursor:
	lcd.cursor();
		
	

	lcd.blink();
}
