/*
 * app.c
 *
 * Created: 4/11/2023 5:19:11 PM
 *  Author: Omar
 */ 


#include "app.h"
/********************************************************/
uint16_t ElevatorFloor = 0;
/********************************************************/
volatile uint8_t UART_RX = 'e';
volatile uint8_t char_KeyPad = 0;
/********************************************************/
FIFO_BUF_t * fifo_buf;
int buf[5];
void APP_init()
{
	/********************************************************/
	SevenSegment_Init(portb,lower);
	/********************************************************/
	DCMOTOR_Init( portb, 6, 7);
	/********************************************************/
	KeyPad_init(KeyPad_Dir);
	/********************************************************/
	EXT_INT0_sense_control(falling_edge);
	EXT_INT0_enable();
	sei();
	/********************************************************/
	USART_Init(51);
	/********************************************************/
	UART_SendString("Voice_Controlled_Elevator \r");
	UART_SendString("Graduation Project \r");
	/********************************************************/
	FIFO_BUF_init(fifo_buf,buf,5);
	/********************************************************/

}
void APP_start()
{
	while (1)
	{
		Keypad_controll();
		if( UART_RX != 'e')
		{
			//enqueue(fifo_buf,( UART_RX -'0'));
			/*************************************************************/
			UART_SendString("\rYou Enter with Voice : ");
			USART_Transmit(UART_RX);
			USART_Transmit('\r');
			
			/*************************************************************/
			Controlled_Elevator(UART_RX - '0');
			UART_controll();
			/*************************************************************/
		}
		if( char_KeyPad != '@')
		{
			//enqueue(fifo_buf,( char_KeyPad - '0'));
			/*************************************************************/
			UART_SendString("\rYou Enter with Keypad : ");
			USART_Transmit(char_KeyPad);
			USART_Transmit('\r');
			
			/*************************************************************/
			Controlled_Elevator(char_KeyPad - '0' );
		}	
// 		if (isFull(fifo_buf))
// 		{
// 			USART_Transmit('\r');
// 			USART_Transmit('\r');
// 			UART_SendString("full");
// 			USART_Transmit('\r');
// 			USART_Transmit('\r');
// 		}
	}
}
void Controlled_Elevator(uint16_t floorplan)
{
	if(floorplan == ElevatorFloor)
	{
		return;
	}
	cli();
	USART_Transmit('\r');
	USART_Transmit('\r');
	UART_SendString("You Are Welcome");
	USART_Transmit('\r');
	USART_Transmit('\r');
	if(floorplan > ElevatorFloor)
	{
		DCMOTOR_up( portb, 6, 7);
		while( floorplan >= ElevatorFloor )
		{
			ElevatorFloor++;
			SevenSegmentDisplay(portb,lower,ElevatorFloor - 1);
			USART_Transmit('\r');
			UART_SendString("ElevatorFloor : ");
			USART_Transmit(( ElevatorFloor - 1) + '0');
			USART_Transmit('\r');
			_delay_ms(1000);
		}
		ElevatorFloor--;
	}
	else if(floorplan < ElevatorFloor)
	{
		DCMotor_down( portb, 6, 7);
		while((int)floorplan <= (int)ElevatorFloor)
		{
			ElevatorFloor--;
			SevenSegmentDisplay(portb,lower,ElevatorFloor + 1);
			USART_Transmit('\r');
			UART_SendString("ElevatorFloor : ");
			USART_Transmit((ElevatorFloor + 1) + '0' );
			USART_Transmit('\r');
			_delay_ms(1000);
		}
		ElevatorFloor++;
	}
	DCMotor_Stop( portb, 6, 7);
	UART_SendString("\rHave been reached\r");
	sei();
}

void Keypad_controll(){	
	KeyPad_read( KeyPad_Dir,(uint8_t *)&char_KeyPad);
	if ( char_KeyPad != '@')
	{
		//enqueue(fifo_buf,( char_KeyPad - '0'));
	}
}
void UART_controll()
{
	if(UART_RX !='e')
	{
		UART_RX ='e';
	}
	return;
}
ISR(EXT_INT_0)
{
	cli();
	UART_RX = USART_Receive();
	//enqueue(fifo_buf,( UART_RX -'0'));
	sei();
}
