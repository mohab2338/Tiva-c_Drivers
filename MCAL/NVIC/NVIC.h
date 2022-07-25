/*-------------------------------------------------------
*		FILE DESCRIPTION
*--------------------------------------------------------
*				File: NVIC.h
*				Description: header file for NVIC register 
*										 The File doesn't support Priority Configurations yet

*-------------------------------------------------------*/

#ifndef NVIC_H_
#define NVIC_H_

#include "Std_Types.h"

void NVIC_EnableIRQ(uint8 IRQn);	
void NVIC_DisableIRQ(uint8 IRQn);

#endif /*NVIC_H_*/
