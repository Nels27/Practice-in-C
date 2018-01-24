#include "F2806x_Device.h"
#define DISABLE(x) (x) << 6 | 1 << 5 | 1 << 3
Uint32 i = 0;
Uint32 j = 2;


/**
 * main.c
 */
int main(void)
{
    Uint32 k;
    k = 0;
    EALLOW;

    if (j == 1) {

        SysCtrlRegs.WDCR = DISABLE(1);
    }
    while(1) {
        if (k++ == 100000){
            k = 0;
            i++;
        }


        if (j == 2) {
            SysCtrlRegs.WDKEY = 0x55;
            SysCtrlRegs.WDKEY = 0xAA;
        }
    }
	return 0;
}
