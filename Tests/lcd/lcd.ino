#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(34, 35, 39, 36, 37, 38);


void setup() {
   
  //screen 1 , displaing all the nececery information.
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FREQ:  10.000.000 Hz");
  lcd.setCursor(0,1);
  lcd.print("PHASE:        000 *");
  lcd.setCursor(0,2);
  lcd.print("AMPL:       00,00 V");
  lcd.setCursor(0,3);
  lcd.print("OFFSET:     00,00 V");
}

void loop() {
  //-------nothing--------
  }
