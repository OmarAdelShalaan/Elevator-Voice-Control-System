/*
 * LCD.h
 *
 * Created: 8/30/2022 9:02:58 AM
 *  Author: Omar
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO_Driver/DIO.h"
#include "../../ECUAL/Delay_Driver/delay.h"

#define _delay_ms(x)  delay_ms(x)
#define _delay_us(x)  delay_us(x)

#define LCD_Command_Dir   portd
//#define LCD_Command_PORT PORTD
#define LCD_Data_Dir   portc
//#define LCD_Data_PORT    PORTC
#define RS   0
#define RW   1
#define EN   2



void LCD_init();
void LCD_8_sendCommand(uint8_t cmnd);
void LCD_8_sendChar(uint8_t char_data);
void LCD_8_sendString(uint8_t *str);
void LCD_Clear();
void LCD_activate_second_line();
void LCD_jump_to_second_line();
void LCD_jump_to_second_line_position(uint8_t _position);
void LCD_jump_to_first_line();
void LCD_jump_to_first_line_position(uint8_t _position);
void save_position();

/*
void LCD_4_sendCommand(uint8_t cmnd);
void LCD_4_sendChar(uint8_t char_data);
void LCD_4_sendString(uint8_t *str);
*/

#endif /* LCD_H_ */