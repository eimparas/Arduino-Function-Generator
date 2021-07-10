#include <AD9833.h>     // Include the library
 
#define FNC_PIN 10       // Can be any digital IO pin
#define freQ 800000        // frequency in Hz

AD9833 gen(FNC_PIN);       // Defaults to 25MHz internal reference frequency
 
void setup() {
    gen.Begin();              
    gen.ApplySignal(SINE_WAVE,REG0,freQ);  
    gen.EnableOutput(true);   
}
 
void loop() {
}
