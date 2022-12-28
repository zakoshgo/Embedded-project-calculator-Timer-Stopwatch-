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
#include "driverlib/timer.h"

void Task1_lab7(void){
  DIO_Init();
  SysTickPeriodSet(7999999);
  SysTickEnable();
    
    uint8_t pin_on = GPIO_PIN_1;
    uint8_t toggle_bit = 1;
    while(1)
    { 
        uint32_t pinF = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
        uint32_t pinB = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0);
        if(pinF == 0){
          if(pin_on == GPIO_PIN_3){
            pin_on = GPIO_PIN_1;
            
          }
          else{
            pin_on = pin_on<<1;
          }
        }
        if (pinB == 1 && (toggle_bit %2) == 1){
          while((NVIC_ST_CTRL_R & 1<<16)>>16 !=1);
          toggle_bit = 0;
          SysTickDisable();
        }else if(pinB == 0 && (toggle_bit %2) == 1){
          
        }else if(pinB == 1 && (toggle_bit %2) == 0){
          toggle_bit = 1;
          SysTickEnable();
          while((NVIC_ST_CTRL_R & 1<<16)>>16 !=1);
        }else if(pinB == 0 && (toggle_bit %2) == 0){
          
        }
        if((NVIC_ST_CTRL_R & 0x1) == 0x1){
          if(pin_on == GPIO_PIN_1){
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);
            toggle(pin_on);
            while((NVIC_ST_CTRL_R & 1<<16)>>16 !=1);
          }
          else{
          GPIOPinWrite(GPIO_PORTF_BASE,pin_on>>1, 0);
          toggle(pin_on);
          while((NVIC_ST_CTRL_R & 1<<16)>>16 !=1);
          }
        }
        
    }
}

void Task1_lab8(){
   DIO_Init();
   SysTickPeriodSet(7999999);
   SysTickEnable();
   SysTickIntEnable();
   while(1){
     __asm("wfi\n");
   }
}
void Task2_lab8(){
  DIO_Init();
  SysCtlClockSet(SYSCTL_SYSDIV_1| SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
  
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER0_BASE, TIMER_A);
  TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
  
    while(1)
    { 
     __asm("wfi\n");   
    }
}