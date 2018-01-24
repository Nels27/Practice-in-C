#include "F2806x_Device.h"
#define DISABLE(x) (x) << 6 | 1 << 5 | 1 << 3

/**
 * main.c
 */

/*
 *  PB1 GPIO 17/88
 *  PB2 GPIO 40/30
 *
 *  LED1 GPIO 09/78
 *  LED2 GPIO 11/79
 *  LED3 GPIO 34/46
 *  LED4 GPIO 41/80
 *
 */

Uint32 j = 2;

int main(void)
{
    EALLOW;

    if (j == 1) {
        SysCtrlRegs.WDCR = DISABLE(1);

    }
    /*
     * Initialization
     * All inputs are set to 0 and outputs to 1
     */

    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    /*
     * Initialization
     * All inputs have their pull up transistors enabled
     * All outputs have their pull up transistors disabled
     */
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 0;

    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;

    /*
       * Initialization
       * All MUXs are set to 0 to enable
       */
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0; //LED3
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; //led4


    Uint32 PB1;
    Uint32 PB2;

    Uint32 curr = 1;/*Setting up the toggle variables */
    Uint32 prev = 0;

    GpioDataRegs.GPBCLEAR.bit.GPIO41 = 0;
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 0;

    while(1) {

        /*
                 * Reading the input
                 */
                PB1 = GpioDataRegs.GPADAT.bit.GPIO17;
                PB2 = GpioDataRegs.GPBDAT.bit.GPIO40;



       // curr = !curr;
       // if(curr != prev){
            /*
             * Writing the output
             */
// CREATE IF STATEMETENTS INSTEAD OF THIS LOGIC
                    GpioDataRegs.GPASET.bit.GPIO9 = !PB1;
                    GpioDataRegs.GPASET.bit.GPIO11 = !PB2;
       // } else { /* turning off the LEDS */

            GpioDataRegs.GPACLEAR.bit.GPIO9 = !PB1;
            GpioDataRegs.GPACLEAR.bit.GPIO11 = !PB2;

           // prev = curr;

        //}





        if(j == 2) { /*Servicing the watchdog */

            SysCtrlRegs.WDKEY = 0x55;
            SysCtrlRegs.WDKEY = 0xAA;
        }
    }
	return 0;
}
