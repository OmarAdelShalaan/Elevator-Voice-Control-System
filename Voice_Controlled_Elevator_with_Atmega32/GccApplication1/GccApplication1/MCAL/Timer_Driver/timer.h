/*
 * timer.h
 *
 * Created: 8/26/2022 3:38:21 AM
 *  Author: Omar
 */


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/register.h"

#define MICRO_UNIT 1000000
#define MILI_UNIT ( MICRO_UNIT / 1000 )
#define F_CPU	   8000000

typedef enum
{
    Normal_mode,
    CTC_mode, // Clear Timer on Compare match
} TimerMode;
typedef enum
{
    CTC_normal,
    CTC_toggle,
    CTC_clear,
    CTC_set
} CTC_mode_State;

typedef enum
{
    prescaler_0 = 0,
    prescaler_1 = 1,
    prescaler_8 = 8,
    prescaler_64 = 64,
    prescaler_256 = 256,
    prescaler_1024 = 1024
} prescaler;

void Timer0_init(TimerMode mode);
void Timer0_off();
/************************************************************************/
/* Normal Mode                                                          */
/************************************************************************/
void Timer0_normalMode(prescaler Prescaler);
void Timer0_read(uint8_t *timerData);
void Timer0_write(uint8_t timerdelay);
void Timer0_counter_rising_edge();
void Timer0_counter_falling_edge();
bool Timer0_overflow();
/**********************************************/
void Timer0_normalMode_squareWave();
/**********************************************/
/************************************************************************/
/* Clear Timer on Compare match (CTC) Mode						        */
/************************************************************************/
void Timer0_CTC_mode( CTC_mode_State State );
void Timer0_CTC_write_compare_value(uint8_t compare_value);
bool Timer0_CTC_occur();

#endif /* TIMER_H_ */


