/*-------------------------------------------
* FILE DISCRIPTION
*--------------------------------------------
*  FILE: Timer.h
*  Description: Header for Timer.c contains
*  							rgisters addresses and functions prototypes.
								The Files support initialization for all Timers,
								but can enable only 16/32 Timers.
								also for now only Timer0 can be used.
*--------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

#include "Std_Types.h"

typedef struct{
/*I didn't use the Tick frequency yet*/
		uint8 WideTimer; // this one to choose timer of wider range timer 
		uint8 GptChannel;
		uint32 GptTickFrquency;
		uint32 GptTickValueMax;
		uint8  GptMode;
	  
}Gpt_ConfigType;

enum WideTimerChoose{ NON_WIDE = 0,
											WIDE = 1 };

enum Timers{TIMER0 = 0,
						TIMER2, 
						TIMER3, 
						TIMER4, 
						TIMER5 };

enum WideTimers{TIMERW0 = 0,
								TIMERW1,
								TIMERW2,
								TIMERW3,
								TIMERW4,
								TIMERW5};

enum TimerMode{PERIODIC = 0,
							 ONE_SHOT};


void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
void Gpt_Interrupt_Enable(uint8 Channel);
void Gpt_Timer_Enable(uint8 Channel, uint32 Value);
void Gpt_Timer_Disable(uint8 Channel);

/*CallBack Part*/
void Gpt_Timer0_Callback(void (* Timer0_FunctionPtr)(void) );

#endif /*TIMER_H_*/
