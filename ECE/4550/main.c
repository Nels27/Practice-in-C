
/*

Lab 2 Task 1

Nelson Raphael

Learning GPIO implementation with a push button


*/


int main(void) {

/*
PB1 GPIO 17/88
According to TRF it is manipulated by bits 2-3 in GPAMUX2

PB2 GPIO 40/82
According to TRF it is manipulated by bits 16-17 GPBMUX1

Digital for Arduion PB88

MUX

2 LED Activation

GPIO 09/49 LED 1
According to TRF it is manipulated by bits 18-19 GPAMUX1

GPIO 11/73 LED 2

MUX


*/

GpioCtrlRegs.GPAMUX2.bit.GPIO17 /* for pb1*/
GpioCtrlRegs.GPBMUX1.bit.GPIO40 /* for pb2*/

GpioCtrlRegs.GPAM

while(1) {

GpioDataRegs.GPASET.bit.GPIO17 /*  Sets it high - use this instead of writing one to it*/

GpioDataRegs.GP?CLEAR.bit.GPIO? /* Sets it low - use this instead of writing zero to it*/


GpioDataRegs.GP?TOGGLE.bit.GPIO? /* Sets it to the opposite state*/

}
return 0;

}
