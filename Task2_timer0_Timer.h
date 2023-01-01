#ifndef timer0_Timer_H
  #define timer0_Timer_H

#include "LCD.h"
#include "Keypad.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void Timer_init();
void Timer_start();


#endif