#include <Adafruit_MCP4725.h>
#include <Wire.h>

Adafruit_MCP4725 dac;

void setup() {
  // put your setup code here, to run once:
	dac.begin(0x62);

}

void loop() {
  // put your main code here, to run repeatedly:
	for (int i = 0; i < 4095; i++)
	{
		if (i == 4096) {
			i = 0;
		}
		dac.setVoltage(i, false);
	}
}
