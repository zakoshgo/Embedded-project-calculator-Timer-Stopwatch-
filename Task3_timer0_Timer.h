#ifndef case3timer0_Timer_H
  #define case3timer0_Timer_H

#include <stdio.h>
#include "LCD.h"
#include "Keypad.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void Timer_init_task3();
void Timer_start_task3(uint32 ,uint32 );
uint8 stopWatchChoice(uint8 choice);


#endif