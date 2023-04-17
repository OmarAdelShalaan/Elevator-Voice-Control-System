/*
 * UART.c
 *
 * Created: 10/4/2022 12:58:41 PM
 *  Author: Omar
 */

#include "UART.h"

void USART_Init( unsigned int baud )
{
    /* Enable receiver and transmitter */
    UCSRB = (1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, no parity, 1stop bit */
    UCSRC = (1<<URSEL)|(3<<UCSZ0);
    /* Set baud rate */
    UBRRH = (unsigned char)(baud>>8);
    UBRRL = (unsigned char)baud;
}
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) );
    /* Get and return received data from buffer */
    return (UDR);
}
void UART_SendString(char * str)
{
	while(*str != '\0')
	{
		USART_Transmit(*str);
		str++;
	}
}
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) );
    /* Put data into buffer, sends the data */
    UDR = data;
}

void USART_Flush( void )
{
    unsigned char dummy;
    while ( UCSRA & (1<<RXC) ) dummy = UDR;
}

unsigned char USART_ReadUCSRC( void )
{
    unsigned char ucsrc;
    /* Read UCSRC */
    ucsrc = UBRRH;
    ucsrc = UCSRC;
    return ucsrc;
}
