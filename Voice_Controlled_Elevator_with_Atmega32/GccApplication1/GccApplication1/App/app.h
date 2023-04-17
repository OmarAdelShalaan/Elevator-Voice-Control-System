/*
 * app.h
 *
 * Created: 4/11/2023 5:19:26 PM
 *  Author: Omar
 */ 


#ifndef APP_H_
#define APP_H_



#include "../ECUAL/DCMotor_Driver/DCmotor.h"
#include "../ECUAL/Delay_Driver/delay.h"
#include "../ECUAL/External_Interrupt/interrupt.h"
#include "../ECUAL/KeyPad_Driver/keypad.h"
#include "../ECUAL/SevenSegment_Driver/SevenSegment.h"
#include "../MCAL/UART_Driver/UART.h"
#include "../FIFO_Driver/fifo_buf.h"

#define KeyPad_Dir portc

void APP_init();
void APP_start();

void Keypad_controll();
void UART_controll();

void Controlled_Elevator(uint16_t floor_plan);

#endif /* APP_H_ */