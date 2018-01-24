#include "F2806x_Device.h"
#include "math.h"
#include <string.h>
#include <stdio.h>

#define PI 3.14159265
#define SIZE(x) sizeof(x)/sizeof(x[0])
#define SIZE_ARRAY 300

Uint32 j = 2;
/**
 * main.c
 */

float32 x[SIZE_ARRAY];
float32 y[SIZE_ARRAY];

int main(void)
{
    EALLOW;
    Uint32 i = 0;
    while(1){
        if(i < 300){
            x[i] = i/100.0;
            y[i] = 3*cos(2*PI*x[i])-cos(6*PI*x[i]);
        }
        i++;

        if(j == 2){
            SysCtrlRegs.WDKEY = 0x55;
            SysCtrlRegs.WDKEY = 0xAA;
        }
    }

	return 0;
}
