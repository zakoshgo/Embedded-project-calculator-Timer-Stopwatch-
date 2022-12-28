#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "types.h"
#include "tm4c123gh6pm.h"
#include "driverlib/systick.h"
#include "DIO.h"

void Systick_Init_int(){
  SysTickEnable();
  SysTickIntEnable();
}