#include <Wire.h>

#include <Adafruit_MCP4725.h>

#define DACi2cADDR 0x62

Adafruit_MCP4725 CH1OFSTDAC;

void setup() {
	CH1OFSTDAC.begin(DACi2cADDR);
	Serial.begin(9600);
}

void loop() {
	for (int i = 0; i <= 4096; i++) {
		//Serial.println(i*0.00122070312);
		CH1OFSTDAC.setVoltage(i, false);
	}

}
