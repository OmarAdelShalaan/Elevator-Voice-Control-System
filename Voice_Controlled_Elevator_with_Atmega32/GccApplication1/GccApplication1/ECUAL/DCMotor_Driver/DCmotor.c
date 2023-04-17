/*
 * DCmotor.c
 *
 * Created: 4/11/2023 3:31:11 PM
 *  Author: Omar
 */ 

#include "DCmotor.h"

void DCMOTOR_Init(portx PORTX, uint8_t pinUP, uint8_t pinDown)
{
	DIO_init_pin(PORTX,pinUP,output);
	DIO_init_pin(PORTX,pinDown,output);
}
void DCMOTOR_up(portx PORTX, uint8_t pinUP,uint8_t pinDown)
{
	DIO_write_pin(PORTX,pinUP,HIGH);
	DIO_write_pin(PORTX,pinDown,low);
}
void DCMotor_down(portx PORTX, uint8_t pinUP,uint8_t pinDown)
{
	DIO_write_pin(PORTX,pinUP,low);
	DIO_write_pin(PORTX,pinDown,HIGH);
}
void DCMotor_Stop(portx PORTX, uint8_t pinUP,uint8_t pinDown)
{
	DIO_write_pin(PORTX,pinUP,low);
	DIO_write_pin(PORTX,pinDown,low);
}
