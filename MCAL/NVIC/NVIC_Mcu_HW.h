/*-------------------------------------------------------*
* FILE DESCRIPTION
*--------------------------------------------------------
* FILE: NVIC_Mcu_HW.h
* 
*
*---------------------------------------------------------*/


#ifndef NVIC_MCU_HW_H_
#define NVIC_MCU_HW_H_

#include "Std_Types.h"

#define NVIC_BASE 				0xE000E100UL

#define NVIC						((NVIC_Type   *) NVIC_BASE      )

typedef struct{
			
	volatile uint32 ISER[5U];   
	volatile uint32 RESRVED[27U];
  volatile uint32 ICER[5U] ;	
	
} NVIC_Type;



#endif /*NVIC_MCU_HW_H_*/
