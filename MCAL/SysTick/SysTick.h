
#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "Std_Types.h"



#define STCTRL   				*((volatile uint32 *)(0xE000E000+0x010))
#define STCTRL_ENABLE  		0
#define STCTRL_INTEN			1
#define STCTRL_CLK_SRC		2
#define STCTRL_COUNT		  16

	
#define STRELOAD  			 *((volatile uint32 *)(0xE000E000+0x014))
#define STCURRENT   			*((volatile uint32 *)(0xE000E000+0x018))


void SysTick_Init(void);
void SysTick_Start(uint32 Ticks_value);
void SysTick_Disable(void);
void SysTick_Callback(void (* Timer0_FunctionPtr)(void) );

#endif /*SYSTICK_H_*/
