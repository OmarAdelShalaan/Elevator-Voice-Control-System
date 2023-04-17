/*
 * UART.h
 *
 * Created: 10/4/2022 12:58:51 PM
 *  Author: Omar
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../Utilities/register.h"

/*****************************************/
// Register A UCSRA
#define RXC   7 
#define TXC   6
#define UDRE  5 
#define FE    4
#define DOR   3 
#define PE    2 
#define U2X   1
#define MPCM  0
// Register B UCSRB
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0
// Register C UCSRC
#define URSEL 7
#define UMSEL 6
#define UPM1  5
#define UPM0  4
#define USBS  3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0
// Registers – UBRRL and UBRRH
#define URSEL 7

/*****************************************/

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void UART_SendString(char * str);



#endif /* UART_H_ */