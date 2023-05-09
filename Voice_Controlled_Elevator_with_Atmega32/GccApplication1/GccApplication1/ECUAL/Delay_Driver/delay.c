/*
 * delay.c
 *
 * Created: 9/5/2022 7:29:28 AM
 *  Author: Omar
 */

#include "delay.h"

void delay()
{
    uint32_t count = 0;
    Timer0_write(0x01);
    while(1)
    {
        if( Timer0_overflow() == 1)
        {
            count++;
        }
        if( count == 10000 )
            return ;
    }
}

void delay_us(uint16_t Time_delay)
{
    uint32_t count = 0;
    float32_t T_tick; // tick of timer
    uint8_t Timer_initial_value; // initial value that timer will start with it
    float32_t T_max_delay; // max value delay
    uint32_t N_overflows; // count of overflows that timer need to do delay we need
    /*************************************/
    if( 256 >= Time_delay )
    {
        /********************************/
        Timer0_normalMode(prescaler_1);
        /********************************/
        T_tick = ( MICRO_UNIT /F_CPU ) * prescaler_1; // convert 1 Micro of F_CPU to 1 prescaler
        T_max_delay = 256 * T_tick;
        Timer_initial_value = ( ( 256 - Time_delay ) / T_tick );
        //TCNT0 = Timer_initial_value;
        Timer0_write( Timer_initial_value );
        while(1)
        {
            if( Timer0_overflow() == 1)
            {
                return ;
            }
        }
    }
    else
    {
        /********************************/
        Timer0_normalMode(prescaler_8);
        /********************************/
        T_tick = ( MICRO_UNIT /F_CPU ) * prescaler_8; // convert 1 Micro of F_CPU to 1 prescaler
        T_max_delay = 256 * T_tick;
        N_overflows = ( Time_delay / T_max_delay );
        Timer_initial_value = 256 - ( ( Time_delay / T_tick ) / N_overflows );
        //TCNT0 = Timer_initial_value;
        Timer0_write( Timer_initial_value );
        while(1)
        {
            if( Timer0_overflow() == 1)
            {
                Timer0_write( Timer_initial_value );
                count++;
            }
            if ( count == N_overflows)
            {
                return;
            }

        }
    }
}
void delay_ms(uint32_t Time_delay)
{
    uint32_t count = 0;
	uint8_t F_CPU_counter = 0;
    float32_t T_tick = 0.0; // tick of timer
    uint8_t Timer_initial_value = 0; // initial value that timer will start with it
    float64_t T_max_delay = 0.0 ; // max value delay
    uint32_t N_overflows = 0; // count of overflows that timer need to do delay we need
    /******************************************/
    Time_delay *= 1000;
    /******************************************/
    Timer0_normalMode(prescaler_1024);
    /*****************************************/
    T_tick = (float)( MICRO_UNIT * 1.0 /F_CPU ) * prescaler_1024;
    T_max_delay = 256.0 * T_tick;
    if( T_max_delay >= Time_delay )
    {
        Timer_initial_value = ( ( T_max_delay - Time_delay ) / T_tick );
        Timer0_write( Timer_initial_value );
        while(1)
        {
            if( Timer0_overflow() == 1)
            {
                return ;
            }
        }
    }
    N_overflows = ( ( Time_delay / T_max_delay ) + 1.0 )  ;
    Timer_initial_value = 256.0 - ( ( Time_delay / T_tick ) / N_overflows );
    Timer0_write( Timer_initial_value );
    
	F_CPU_counter++;
	while(1)
	{
		if( Timer0_overflow() == 1)
		{
			Timer0_write( Timer_initial_value );
			count++;
		}
		if ( count  == N_overflows )
		{
			break;
		}

	}
}
