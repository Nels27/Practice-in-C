#include "F2806x_Device.h"
#define DISABLE(x) (x) << 6 | 1 << 5 | 1 << 3

/**
 * main.c TASK 2
 */

/*
 *  hex0 = GPIO12/33
 *  hex1 = GPIO13/83
 *  hex2 = GPIO14/84
 *  hex3 = GPIO15/34
 *  LED1 GPIO09/78
 *  LED2 GPIO11/79
 *  LED3 GPIO34/46
 *  LED4 GPIO41/80
 */

Uint32 j = 2;

int main(void)
 {
    EALLOW;
    SysCtrlRegs.WDCR = DISABLE(1);
    /*
     * Initialization
     * All inputs are set to 0 and outputs to 1
     */
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0; //hex0
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0; //hex1
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0; //hex2
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 0; //hex3
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;  //LED1
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1; //LED2
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; //LED3
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1; //LED4


    /*
     * Initialization
     * All inputs have their pull up transistors enabled
     * All outputs have their pull up transistors disabled
     */

    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;

    /*
    * Initialization
    * All MUXs are set to 0 to enable
    */
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;


    Uint32 hex0, hex1, hex2, hex3;
    SysCtrlRegs.WDCR = DISABLE(0);

    GpioDataRegs.GPACLEAR.bit.GPIO9 = 0;
    GpioDataRegs.GPACLEAR.bit.GPIO11 = 0;
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 0;
    GpioDataRegs.GPBCLEAR.bit.GPIO41 = 0;
    while(1) {
        hex0 = GpioDataRegs.GPADAT.bit.GPIO12;
        hex1 = GpioDataRegs.GPADAT.bit.GPIO13;
        hex2 = GpioDataRegs.GPADAT.bit.GPIO14;
        hex3 = GpioDataRegs.GPADAT.bit.GPIO15;

        if(hex0){ //Turn LED4 ON
            GpioDataRegs.GPBSET.bit.GPIO41 = 1;
        } else if(!hex0){ //TURN LED4 OFF
            GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
        }

        if(hex1){ //Turn LED3 ON
            GpioDataRegs.GPBSET.bit.GPIO34 = 1;
        } else if(!hex1){ //TURN LED3 OFF
            GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
        }

        if(hex2){ //Turn LED2 ON
            GpioDataRegs.GPASET.bit.GPIO11 = 1;
        } else if(!hex2){ //TURN LED2 OFF
            GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        }

        if(hex3){ //Turn LED1 ON
            GpioDataRegs.GPASET.bit.GPIO9 = 1;
        } else if(!hex3){ //TURN LED1 OFF
            GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
        }


        SysCtrlRegs.WDKEY = 0x55;
        SysCtrlRegs.WDKEY = 0xAA;
    }
    return 0;
}
