
/*

Lab 2 Task 1

Nelson Raphael

Learning GPIO implementation with a push button


*/


int main(void) {

/* PB1 GPIO 17/88
PB2 GPIO 48/30
Digital for Arduion PB88

MUX

2 LED Activation

GPIO 09/78 LED 1

GPIO 11/79 LED 2

MUX


*/

GpioCtrlRegs.GP17MUX.bit.GPIO

while(1) {

GpioDataRegs.GP?SET.bit.GPIO? /*  Sets it high - use this instead of writing one to it*/

GpioDataRegs.GP?CLEAR.bit.GPIO? /* Sets it low - use this instead of writing zero to it*/


GpioDataRegs.GP?TOGGLE.bit.GPIO? /* Sets it to the opposite state*/







}
return 0;

}
