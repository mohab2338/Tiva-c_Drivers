/*-------------------------------------------------------*
* FILE DESCRIPTION
*--------------------------------------------------------
* FILE: Timer_Mcu_HW.h
* 
*
*---------------------------------------------------------*/

#ifndef TIMER_MCU_HW_H_
#define TIMER_MCU_HW_H_

#define UART_H_

#include "Std_Types.h"

#define RCGCTIMER			*((volatile uint32 *)(0x400FE000+0x604) ) //Timer 16/32
#define RCGCWTIMER    *((volatile uint32 *)(0x400FE000+0x65C) ) //Timer 32/64
	
#define GPTM_N_BASE(Timer)       (0x40030000+Timer*0x1000)
#define GPTWM_N_BASE(Timer)     ((Timer > 5)&&(Timer<8))?(0x40036000+(Timer)*0x1000):(0x4004C000+((Timer)*0x1000))

#define CTL_OFFSET							0x00C
#define CFG_OFFSET							0x000
#define TAMR_OFFSET							0x004
#define TAILR_OFFSET						0x028
#define IMR_OFFSET							0x018
#define ICR_OFFSET							0x024
#define TAPR_OFFSET							0x038

#define GPIMCTL(number,type)  	 *((volatile uint32 *)( ( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ CTL_OFFSET    )   )	
#define GPTMCFG(number,type)  	 *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ CFG_OFFSET		)   )	
#define GPTMTAMR(number,type)    *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ TAMR_OFFSET	  )   )	
#define GPTMTAILR(number,type) 	 *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ TAILR_OFFSET	)   )	
#define GPTMIMR(number,type)   	 *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ IMR_OFFSET		)   )
#define GPTMICR(number,type)  	 *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ ICR_OFFSET		)   )
#define GPTMTAPR(number,type) 	 *((volatile uint32 *)(	( (type==1)?(GPTWM_N_BASE(number)):(GPTM_N_BASE(number)) )+ TAPR_OFFSET	  )   )


#endif /*TIMER_MCU_HW_H_*/
