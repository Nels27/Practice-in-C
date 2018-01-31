#include "F2806x_Device.h"
#define DISABLE(x) (x) << 6 | 1 << 5 | 1 << 3

/**
 * main.c TASK 1
 */

/*
 *  PB1 GPIO 17/88
 *  PB2 GPIO 40/30
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
    SysCtrlRegs.WDCR = DISABLE(1);
    /*
     * Initialization
     * All inputs are set to 0 and outputs to 1
     */
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; //PB1
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0; //PB2
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1; //LED1
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1; //LED2
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; //LED3
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1; //LED4

    /*
     * Initialization
     * All inputs have their pull up transistors enabled
     * All outputs have their pull up transistors disabled
     */
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;

    /*
    * Initialization
    * All MUXs are set to 0 to enable
    */
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;

    Uint32 PB1;
    Uint32 PB2;
    GpioDataRegs.GPBCLEAR.bit.GPIO41 = 0;
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 0;

    SysCtrlRegs.WDCR = DISABLE(0);

    while(1) {
        PB1 = GpioDataRegs.GPADAT.bit.GPIO17;
        PB2 = GpioDataRegs.GPBDAT.bit.GPIO40;
        if(!PB1){ //Turn LED1 ON
            GpioDataRegs.GPASET.bit.GPIO9 = 1;    
        } else if(PB1){ //TURN LED1 OFF
            GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
        }

        if(!PB2){ //TURN LED2 ON
            GpioDataRegs.GPASET.bit.GPIO11 = 1;
        } else if(PB1){ //TURN LED2 OFF
            GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        }
        SysCtrlRegs.WDKEY = 0x55;
        SysCtrlRegs.WDKEY = 0xAA;
    }
    return 0;
}
