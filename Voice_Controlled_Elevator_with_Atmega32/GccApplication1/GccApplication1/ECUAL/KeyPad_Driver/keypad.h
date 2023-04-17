/*
 * keypad.h
 *
 * Created: 9/1/2022 10:24:02 AM
 *  Author: Omar
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/DIO_Driver/DIO.h"
#include "../../ECUAL/Delay_Driver/delay.h"

#define _delay_ms(x)  delay_ms(x)
#define _delay_us(x)  delay_us(x)

//#define KeyPad_Dir  portc
//#define KeyPad_PORT PORTA
//#define KeyPad_PIN PINA
#define KeyPad_Row   0
#define KeyPad_Column 4

//void KeyPad_init( portx portRow, uint8_t startRowPin , portx portColumn, uint8_t startColumnPin );
void KeyPad_init(portx KeyPad_Dir);
void KeyPad_read(portx KeyPad_Dir,uint8_t *char_KeyPad);
uint8_t KeyPad_pressed(uint8_t row, uint8_t column);



#endif /* KEYPAD_H_ */
