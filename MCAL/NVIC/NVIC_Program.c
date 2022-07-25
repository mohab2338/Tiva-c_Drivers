/*-------------------------------------------------------
*		FILE DESCRIPTION
*--------------------------------------------------------
*				File: NVIC_Program.c
*				Description: Contains Functions for NVIC
*
*-------------------------------------------------------*/


#include "NVIC.h"
#include "NVIC_Mcu_HW.h"

void NVIC_EnableIRQ(uint8 IRQn){
		NVIC->ISER[IRQn/32] = (1UL << (IRQn));
}

void NVIC_DisableIRQ(uint8 IRQn){
		NVIC->ICER[IRQn/32] = (1UL << (IRQn));
}
