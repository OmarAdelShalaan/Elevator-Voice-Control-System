/*
 * SevenSegment.c
 *
 * Created: 4/11/2023 7:53:23 AM
 *  Author: Omar
 */ 

#include "SevenSegment.h"


void SevenSegment_Init(portx PORTX, nibble lower_upper_nibble)
{
	DIO_init_nibble(PORTX , lower_upper_nibble , output);
}


void SevenSegmentDisplay( portx PORTX, nibble upper_lower, uint8_t data )
{
	DIO_write_nibble(  PORTX,  upper_lower,  data );
	
}
