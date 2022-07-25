/*-------------------------------------------------------*
* FILE DESCRIPTION
*--------------------------------------------------------
* FILE: UART.h
* 
*
*---------------------------------------------------------*/
/****************** UART Initialization steps***************************************

To enable and initialize the UART, the following steps are necessary:

1. Enable the UART module using the RCGCUART register (see page 344).

2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
To find out which GPIO port to enable, refer to Table 23-5 on page 1351.

3. Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
configure, see Table 23-4 on page 1344.

4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
page 673 and page 681).

5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
pins (see page 688 and Table 23-5 on page 1351).

******************************END UART Init*******************************************/
#ifndef UART_H_
#define UART_H_

#include "Std_Types.h"
#include "DIO.h"

#define RCGCUART   *((volatile uint32 *)(0x400FE000+0x618))
#define UARTCTL    *((volatile uint32 *)(0x4000C000+0x030))
#define UARTDATA   *((volatile uint32 *)(0x4000C000+0x000))
#define UARTIBRD   *((volatile uint32 *)(0x4000C000+0x024))
#define UARTFBRD   *((volatile uint32 *)(0x4000C000+0x028))
#define UARTLCRH   *((volatile uint32 *)(0x4000C000+0x02C))
#define UARTFR     *((volatile uint32 *)(0x4000C000+0x018))


void UART_Init(void);
void UART_Transmitter(uint8 data);
uint8 UART_Receiver(void);
void Print_String(char *Str);







#endif /*UART_H_*/
