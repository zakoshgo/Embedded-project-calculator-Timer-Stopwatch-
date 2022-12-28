#include "types.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "LCD.h"
#include "Keypad.h"
#include <time.h>
#include <stdlib.h>
#include "bitwise_operation.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "types.h"
#include "tm4c123gh6pm.h"
#include "driverlib/systick.h"
#include "DIO.h"
//#include "Systic_timer.h"

#include "bitwise_operation.h"
// timer_init task 2

void Timer_init()
{
  DIO_init();
  SysCtlClockSet(SYSCTL_SYSDIV_1| SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  clearBit(TIMER0_TAMR_R ,4);
  display_on_LCD_initialValue();
  TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
  
}
void Timer_start()
{
  
  uint32 minutes = getDigits_task2(); //get minutes from user
  uint32 seconds = getDigits_task2();//get seconds from user
  ///////////////////////////////////////////////////////////////////////
   uint8 buffer[50]; 
   sprintf(buffer, "%d : %d",minutes, seconds);
    LCD_Cmd(0x01);		
    LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    //delayMs(500);											
    LCD_Write_String(buffer);
    LCD_Cmd(0xC0);
    //delayMs(500);  
    /////////////////////////////////////////////////////////////////////
    while(get_op_task2() ==0); //nothing is clicked
 // TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()*3);
   TimerEnable(TIMER0_BASE, TIMER_A);
   while(minutes + seconds != 0)
    { 
     //if t seconds =0 decremnt the minutes , seconds =0
      // else decrement seconds
      while((TIMER0_RIS_R & 0x01) == 0); //timer for 1 second
      setBit(TIMER0_ICR_R,0);
      minutes = minutes-!(seconds);
      if(seconds == 0){
      seconds = 59;
      }
      else{
      seconds -=1;
      }
      uint8 buffer[50]; 
      sprintf(buffer, "%d : %d",minutes, seconds);
      LCD_Cmd(0x01);		
      LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    //delayMs(500);											
      LCD_Write_String(buffer);
      LCD_Cmd(0xC0);
     if(KeyPad_Read_task2()=='B'){
       return;
      }
      
    }
   // function of the buzzer
   int counter = 8;
   while(counter)
    { 
      
      
      delay(0.25);
      setBit(GPIO_PORTF_DATA_R,2);
      delay(0.25);
      clearBit(GPIO_PORTF_DATA_R,2);
      counter--;
    }

      

}
