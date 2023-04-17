/*
 * keypad.c
 *
 * Created: 9/1/2022 10:23:53 AM
 *  Author: Omar
 */

#include "keypad.h"


void KeyPad_init(portx KeyPad_Dir)
{
    // void DIO_init_nibble( portx PORTX, nibble upper_lower, dirction in_out );
    //KeyPad_Dir |= ( 0XF << KeyPad_Row );
    DIO_init_nibble( KeyPad_Dir, lower, out);
    //KeyPad_Dir &= ~( 0XF << KeyPad_Column );
    DIO_init_nibble( KeyPad_Dir, upper, input);
    // 	void DIO_write_port( portx PORTX, uint8_t data );
    //KeyPad_PORT = 0xFF;
    DIO_write_port( KeyPad_Dir, 0xFF);
}

void KeyPad_read(portx KeyPad_Dir,uint8_t *char_KeyPad)
{
    uint8_t row = 0;
    uint8_t column = 0;
    uint8_t *ptrData;
    for( row = 0; row < 4; row++)
    {
        // void DIO_write_port( portx PORTX, uint8_t data );
        //KeyPad_PORT = ( KeyPad_PORT | 0x0F);
        DIO_write_port(KeyPad_Dir, 0xFF);
        // void DIO_write_pin( portx PORTX, uint8_t PX, uint8_t data );
        //KeyPad_PORT &= ~( 1 << row );
        DIO_write_pin(KeyPad_Dir, row, LOW);
        for( column = 0; column < 4; column++)
        {
            //if(!( ( KeyPad_PIN & ( 1 << KeyPad_Column + column ) ) >> ( KeyPad_Column + column ) ) )
            // void DIO_read_pin( portx PORTX, uint8_t PX, uint8_t *ptrData);
			
            DIO_read_pin(KeyPad_Dir, (KeyPad_Column + column), ptrData);
			if((*ptrData == LOW))
            {
                _delay_ms(150);
                //if(!( ( KeyPad_PIN & ( 1 << KeyPad_Column + column ) ) >> ( KeyPad_Column + column ) ) )
                DIO_read_pin(KeyPad_Dir, (KeyPad_Column + column), ptrData);
			    if(*ptrData == LOW)
                {
                    *char_KeyPad = KeyPad_pressed( row, column );
                    return;
                }
            }
        }
    }
    *char_KeyPad = '@';
}

uint8_t KeyPad_pressed(uint8_t row, uint8_t column)
{
    switch(row)
    {
    case 0 :
        switch (column)
        {
        case 3 :
            return '/';
        case 2 :
            return '9';
        case 1 :
            return '8';
        case 0 :
            return '7';
        }
    case 1 :
        switch (column)
        {
        case 3 :
            return '*';
        case 2 :
            return '6';
        case 1 :
            return '5';
        case 0 :
            return '4';
        }
    case 2 :
        switch (column)
        {
        case 3 :
            return '-';
        case 2 :
            return '3';
        case 1 :
            return '2';
        case 0 :
            return '1';
        }
    case 3 :
        switch (column)
        {
        case 3 :
            return '+';
        case 2 :
            return '=';
        case 1 :
            return '0';
        case 0 :
            return '\\';
        }

    }
}
