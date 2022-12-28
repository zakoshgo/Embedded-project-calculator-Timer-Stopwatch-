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

static uint32 minutes;
static uint32 seconds;
//timer intilization task 3
void Timer_init_task3()
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
void Timer_start_task3(uint32 minutes,uint32 seconds )
{
  
  ///////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////
    while(get_op() ==0);
    
    
   TimerEnable(TIMER0_BASE, TIMER_A);
   
   while(1)
    { 
      
      while((TIMER0_RIS_R & 0x01) == 0);
      setBit(TIMER0_ICR_R,0);
      if(seconds==59){
      minutes = minutes+1;
      seconds=0;
      }
      else{
        seconds++;
      }
      uint8 buffer[50]; 
      sprintf(buffer, "%d : %d",minutes, seconds);
      LCD_Cmd(0x01);		
      LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    //delayMs(500);											
      LCD_Write_String(buffer);
      LCD_Cmd(0xC0);
    }
   
   



}
uint8 stopWatchChoice(uint8 choice)
{
  int8 op='A';
  //Timer_init_task3();
  if (choice == 'P'){// pause
  
    
    while( op == 'A'){ // while nothing is clicked, do nothing and read from keypad
      op=KeyPad_Read_task3();
    }
    
    choice = op;
    }
    if (choice == 'R'){// reset
    display_on_LCD_initialValue();// get the inital value of the stopwatch
    minutes = 0;
    seconds=0;
    }
    if (choice == 'S') // stop watch start 
    {
      TimerEnable(TIMER0_BASE, TIMER_A);
      while( op == 'A')
      {
        
        while((TIMER0_RIS_R & 0x01) == 0);//1 second flag
      setBit(TIMER0_ICR_R,0);
      if(seconds==59){ // is second = 59 incremnt minutes , else increment seconds
      minutes = minutes+1;
      seconds=0;
      }
      else{
        seconds++;
      }
      uint8 buffer[50]; 
      sprintf(buffer, "%d : %d",minutes, seconds);
      LCD_Cmd(0x01);		
      LCD_Cmd(0x80);               //Force the cursor to beginning of 1st line
    //delayMs(500);											
      LCD_Write_String(buffer);
      LCD_Cmd(0xC0);
      op=KeyPad_Read_task3();
      }
      choice=op;
    }
    if (choice == 'B'){// Back home
    return 'F';
    }
  return choice;
    
}




// get dig 1 , git dig 2
// while()
// display out (x,y)
//update x,y