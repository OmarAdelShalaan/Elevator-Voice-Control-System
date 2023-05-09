/*
 * SevenSegment.h
 *
 * Created: 4/11/2023 7:53:39 AM
 *  Author: Omar
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include "../../MCAL/DIO_Driver/DIO.h"
void SevenSegment_Init(portx PORTX, nibble lower_upper_nibble);
void SevenSegmentDisplay( portx PORTX, nibble upper_lower, uint8_t data );
#endif /* SEVENSEGMENT_H_ */