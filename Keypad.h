#ifndef KEY_H
  #define KEY_H

#include "types.h"
#include "DIO.h"
void KeyPad_Init(void);
uint8 KeyPad_Read_task3(void);
uint8 KeyPad_Read_task2(void);
uint32 getDigits_task2();
//void SevenSegment_Display();
uint32 getDigits();
//void ReadInputs();
void display_on_LCD_initialValue();
int get_op_task2();
uint8 KeyPad_Read_task1(void);
uint32 checkFlag_task1(uint8 x, uint16 fflag);
int32 getDigits_task1(uint8_ptr op, uint16 firstflag);
uint8 ReadInputs_task1();
#endif