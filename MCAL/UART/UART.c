/*---------------------------------------------------*
*  FILE DESCRIPTION
*----------------------------------------------------
*			File: UART.c
*			Description: Provide functions for The UART pirepheral
*
*----------------------------------------------------*/


#include "UART.h"
#include "Std_Types.h"
#include "DIO.h"

void UART_Init(void){

	SET_BIT(RCGCUART,0);
	SET_BIT(RCGCGPIO,0);
	
	Port_Config TX =  { PORT_A, PIN_MODE_OTHER, PIN_OUTPUT , PULL_DOWN_RES, DRIVE_CURRENT_2M, OPEN_DRAIN_INACTIVE,  0 };
	Port_Init(&TX);
	
	UARTCTL = 0; //disable uart
	UARTIBRD = 104;
	UARTFBRD = 11 ;

	UARTLCRH = 0x60; // 8-bit , no parity, 1 stop-bit , no FIFO
	UARTCTL = 0x301; //enable uart
	
	SET_BIT(GPIODEN(PORT_A),0);
	SET_BIT(GPIODEN(PORT_A),1);
	
	SET_BIT(GPIOAFSEL(PORT_A),0);
	SET_BIT(GPIOAFSEL(PORT_A),0);


	SET_BIT(GPIOPCTL(PORT_A),0);
	SET_BIT(GPIOPCTL(PORT_A),4);
	
	Print_String("UART Initialized\n");
}
void UART_Transmitter(uint8 data){

	while(GET_BIT(UARTFR,5)==1);
	UARTDATA = data ;
}
uint8 UART_Receiver(void){
  uint8 data; 
	while(GET_BIT(UARTFR,4)==1);

	data = UARTDATA  ;
	return (uint8)data;
}
void Print_String(char *Str){
	
	while( *Str ){	
		UART_Transmitter(*(Str++));
	}
}
