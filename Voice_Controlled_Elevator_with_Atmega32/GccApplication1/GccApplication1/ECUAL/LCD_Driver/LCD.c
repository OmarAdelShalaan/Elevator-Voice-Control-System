/*
 * LCD.c
 *
 * Created: 8/30/2022 9:03:14 AM
 *  Author: Omar
 */

#include "LCD.h"

uint8_t position = 0;

void LCD_init()
{
    DIO_init_group(LCD_Command_Dir,RS,EN,out);
    DIO_init_port( LCD_Data_Dir, out );
    _delay_ms(20);			 //LCD Power ON delay always >15ms
    LCD_8_sendCommand (0x38);		// Initialization of 16X2 LCD in 8bit mode
    LCD_8_sendCommand (0x0C);		// Display ON Cursor OFF
    LCD_8_sendCommand (0x06);		// Auto Increment cursor
    LCD_8_sendCommand (0x01);		// clear display
    _delay_ms(2);		//	 Clear display command delay> 1.63 ms
    LCD_8_sendCommand (0x80);		// Cursor at home position
}
void LCD_8_sendCommand(uint8_t cmnd)
{
    DIO_write_port(LCD_Data_Dir, cmnd );
    DIO_write_pin( LCD_Command_Dir, RS, LOW);
    DIO_write_pin( LCD_Command_Dir, RW, LOW);
    DIO_write_pin( LCD_Command_Dir, EN, HIGH);
    _delay_us(1);
    DIO_write_pin( LCD_Command_Dir, EN, LOW);
    _delay_ms(2);
}
void LCD_8_sendChar(uint8_t char_data)
{
    save_position();
    DIO_write_port(LCD_Data_Dir, char_data );
    DIO_write_pin( LCD_Command_Dir, RS, HIGH);
    DIO_write_pin( LCD_Command_Dir, EN, HIGH);
    _delay_us(1);
    DIO_write_pin( LCD_Command_Dir, EN, LOW);
    _delay_ms(2);			// Data write delay
}
void LCD_8_sendString(uint8_t *str)
{
    int i;
    for(i=0; str[i]!=0; i++)		// Send each char of string till the NULL
    {
        LCD_8_sendChar (str[i]);
    }
}
void LCD_Clear()
{
    LCD_8_sendCommand (0x01);		//clear display
    LCD_8_sendCommand (0x80);		// cursor at home position
}
void LCD_activate_second_line()
{
    LCD_8_sendCommand(0x3C);
}
void LCD_jump_to_second_line()
{
    LCD_8_sendCommand(0xC0);
}
void LCD_jump_to_second_line_position(uint8_t _position)
{
    uint8_t temp = 0xC0 + _position - 1;
    LCD_8_sendCommand(temp);
}

void LCD_jump_to_first_line()
{
    LCD_8_sendCommand(0x80);
    position = 0;
}
void LCD_jump_to_first_line_position(uint8_t _position)
{
    uint8_t temp = 0x80 + _position - 1;
    LCD_8_sendCommand(temp);
}
void save_position()
{
    //static uint8_t position = 0;
    position++;
    if( position == 17)
    {
        LCD_jump_to_second_line();
    }
    if( position > 32 )
    {
        position = 0;
        LCD_jump_to_first_line();
    }
}
