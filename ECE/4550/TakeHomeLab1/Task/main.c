/*
 Take Home Lab 1
 Nelson Raphael
 Pendulum Imitation


Will need to use ISR

Will need the GPIO for the various LEDs

Will also need to check the boot mode for the launchpad using the TRST
and GPIO pins (GPIO34 and GPIO37)

TRST is pin 3 on S1 and pin 2 on U1 

GPIO34 can be muxed from pin 19
GPIO37 can be accessed from pin 


All of these can be changed to GPIOs

ADCINA2 pin 8 (U1)/ pin 8 (J1)
ADCINA4 pin 5 (U1)/ pin 6 (J1)
ADCINA6 pin 4 (U1)/ pin 2 (J1)
ADCINB2 pin 14 (U1)/ pin 9 (J1)
ADCINB4 pin 16 (U1)/ pin 10 (J1)
ADCINB6 pin 17 (U1)/ pin 10 (J2)

GPIO 


Use emulation boot to ram since it is the boot mode we want during any CCS
debug session.




*/


#include
#

int softwareInterrupt(void){

/* Used to make sure it is visited every 1ms */


}


int main(void) 
	{
	

	/* Initialization of important things */

		Uint 32 LED0, LED1, LED2, LED3;

		EALLOW;
while (1) {

	

	if(theta >= 90 || theta <= 180) {
		/* Activate LED 1 */

	} else if (theta >= 0.1 || theta <= 90) {
		/* Activate LED 2 */

	} else if (-theta >= 90 || -theta <= 180) {
		/* Activate LED 3 */

	} else if (-theta >= 90 || -theta <= 180) {
		/* Activate LED 4 */

	}




return 0;
}
