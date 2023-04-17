/*
 * DCmotor.h
 *
 * Created: 4/11/2023 3:30:48 PM
 *  Author: Omar
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "../../MCAL/DIO_Driver/DIO.h"


void DCMOTOR_Init(portx PORTX, uint8_t pinUP, uint8_t pinDown);
void DCMOTOR_up(portx PORTX, uint8_t pinUP,uint8_t pinDown);
void DCMotor_down(portx PORTX, uint8_t pinUP,uint8_t pinDown);
void DCMotor_Stop(portx PORTX, uint8_t pinUP,uint8_t pinDown);



#endif /* DCMOTOR_H_ */