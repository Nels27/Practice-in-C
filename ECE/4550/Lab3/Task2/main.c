#include "F2806x_Device.h"
#define DISABLE(x) (x) << 6 | 1 << 5 | 1 << 3

/*
 *  LED1 GPIO09/78
 *  LED2 GPIO11/79
 *  LED3 GPIO34/46
 *  LED4 GPIO41/80
 */

Uint16 curr = 0, prev = 0, toggle = 0;
void initInterrupt(void *interruptAddress);
void setFreq(Uint16 div, Uint16 divsel);
void initLED(Uint16 num);
interrupt void softInterrupt();
Uint16 count = 0;
Uint16 hex0, hex1, hex2, hex3;
 int main(){
    EALLOW;
    initInterrupt(&softInterrupt);
    setFreq(9,3);
    initLED(4);


    SysCtrlRegs.WDCR = DISABLE(1);
    SysCtrlRegs.WDCR = DISABLE(0);
    GpioDataRegs.GPBSET.bit.GPIO41 = 1;


    while(1){
       SysCtrlRegs.WDKEY = 0x55;
       SysCtrlRegs.WDKEY = 0xAA;
    }
    return 0;
 }


 /*
  * function to start interrupts defined by User
  * @param address of interrupt functions
  * @return void return
*/
 void initInterrupt(void *interruptAddress){
     //Set the divider for the system clock to get ftmr
     CpuTimer0Regs.PRD.all = 8999999;
     CpuTimer0Regs.TPR.bit.TDDR = 0x4; //
     CpuTimer0Regs.TPRH.bit.TDDRH = 0x0;

     //TSS turns on/off the timer
     //TRB reads the value from TDDR:TDDRH
     //TIE enables the interrupt
     CpuTimer0Regs.TCR.bit.TSS = 0x1;
     CpuTimer0Regs.TCR.bit.TRB = 0x1;
     CpuTimer0Regs.TCR.bit.TIE = 0x1;
     CpuTimer0Regs.TCR.bit.TSS = 0x0;

     PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
     PieVectTable.TINT0 = &softInterrupt;//interruptAddress;

     PieCtrlRegs.PIEIER1.bit.INTx7= 1;
     PieCtrlRegs.PIEACK.all = 1;

     IER = 0x1;
     EINT;

 }


 /*
  * function to set frequency defined by User
  * @param freq the input from User
  * @return void return
 */
 void setFreq(Uint16 div, Uint16 divsel){
     if(SysCtrlRegs.PLLSTS.bit.MCLKSTS){
         SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
     } else{
         switch(SysCtrlRegs.PLLSTS.bit.DIVSEL){
             case 2:
             case 3:
                 SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
                 break;
         }
         SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
         SysCtrlRegs.PLLCR.bit.DIV = div;


         while(!SysCtrlRegs.PLLSTS.bit.PLLLOCKS){
             // continue to wait
         }
         SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
         SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;

     }
 }

 /*
 * function to initialize x number of LEDs
 * @param num the number of LEDs to initialize
 * @return void return
 */
 void initLED(Uint16 num){
    /*
    * 1 << Initializing LEDs as OUTPUT (1)
    * 2 << Disabling (1) LEDs pull-up resistor
    * 3 << Enabling (0) LED's MUX
    * 4 << Clear (1) LEDs (OFF)
    */

    switch(num){
        case 4:
            GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
            GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;
            GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;
            GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
        case 3:
            GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
            GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
            GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
            GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
        case 2:
            GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
            GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
            GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        case 1:
            GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
            GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
            GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
    }
 }

 interrupt void softInterrupt(){
     //TOGGLE FOR EVERY 2Hz
     switch(count){
     case 0: hex0 = 0; hex1 = 0; hex2 = 0; hex3 = 0 ; break;
     case 1: hex0 = 1; hex1 = 0; hex2 = 0; hex3 = 0 ;break;
     case 2: hex0 = 0; hex1 = 1; hex2 = 0; hex3 = 0 ;break;
     case 3: hex0 = 1; hex1 = 1; hex2 = 0; hex3 = 0 ;break;
     case 4: hex0 = 0; hex1 = 0; hex2 = 1; hex3 = 0 ;break;
     case 5: hex0 = 1; hex1 = 0; hex2 = 1; hex3 = 0 ;break;
     case 6: hex0 = 0; hex1 = 1; hex2 = 1; hex3 = 0;break;
     case 7: hex0 = 1; hex1 = 1; hex2 =1; hex3 = 0;break;
     case 8: hex0 = 0; hex1 = 0; hex2 = 0; hex3 = 1;break;
     case 9: hex0 = 1; hex1 = 0; hex2 = 0; hex3 = 1;break;
     case 10: hex0 = 0; hex1 = 1; hex2 = 0; hex3 = 1;break;
     case 11: hex0 = 1; hex1 = 1; hex2 = 0; hex3 = 1;break;
     case 12: hex0 = 0; hex1 = 0; hex2 = 1; hex3 = 1;break;
     case 13: hex0 = 1; hex1 = 0; hex2 = 1; hex3 = 1;break;
     case 14: hex0 = 0; hex1 = 1; hex2 = 1; hex3 = 1;break;
     case 15: hex0 = 1; hex1 = 1; hex2 = 1; hex3 = 1 ;break;
     }
     if(hex3){ //Turn LED4 ON
         GpioDataRegs.GPBSET.bit.GPIO41 = 1;
     } else if(!hex3){ //TURN LED4 OFF
         GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
     }

     if(hex2){ //Turn LED3 ON
         GpioDataRegs.GPBSET.bit.GPIO34 = 1;
     } else if(!hex2){ //TURN LED3 OFF
         GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
     }

     if(hex1){ //Turn LED2 ON
         GpioDataRegs.GPASET.bit.GPIO11 = 1;
     } else if(!hex1){ //TURN LED2 OFF
         GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
     }

     if(hex0){ //Turn LED1 ON
         GpioDataRegs.GPASET.bit.GPIO9 = 1;
     } else if(!hex0){ //TURN LED1 OFF
         GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
     }

     count = (count + 1)%16;

     PieCtrlRegs.PIEACK.all = 1;
 }
