/*---------------------------------------------------*
*  FILE DESCRIPTION
*----------------------------------------------------
*			File: Timer_Program.c
*			Description: Contains Timer Functions
*
*----------------------------------------------------*/

/* -----------------------NOTES--------------------------------------*
		configuring Timers to work as individual Doesn't work proberly!! check this.
		
*--------------------------------------------------------------------*/
#include "Timer.h"
#include "Timer_Mcu_HW.h"
#include "NVIC.h"
/*This function only support Normal mode for now*/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr){
	
		if(ConfigPtr->WideTimer == 0){
			SET_BIT(RCGCTIMER, ConfigPtr->GptChannel);
		}
		else{
			SET_BIT(RCGCWTIMER, ConfigPtr->GptChannel);
		}
		
		/*******************************/
		/*Disable the timer to configure*/
		CLR_BIT(GPIMCTL(ConfigPtr->GptChannel,ConfigPtr->WideTimer) ,0 );//  this "0" because we only support the normal mode
			
		/*choose indivital or concatnate*/
		if(ConfigPtr->GptTickValueMax <= ((2^16)-1)){
				
				GPTMCFG(ConfigPtr->GptChannel,ConfigPtr->WideTimer) = 0x4	;		
		
		}
		else{
				GPTMCFG(ConfigPtr->GptChannel,ConfigPtr->WideTimer) = 0x1	;
		}
		
		/*choosing mode ---> I only support periodic and one-shot*/
		if(ConfigPtr->GptMode == PERIODIC){
				CLR_BIT(GPTMTAMR(ConfigPtr->GptChannel,ConfigPtr->WideTimer), 0);
				SET_BIT(GPTMTAMR(ConfigPtr->GptChannel,ConfigPtr->WideTimer), 1);
		}
		else{
			  SET_BIT(GPTMTAMR(ConfigPtr->GptChannel,ConfigPtr->WideTimer), 0);
				CLR_BIT(GPTMTAMR(ConfigPtr->GptChannel,ConfigPtr->WideTimer), 1);
		}
		/*Direction is not supported yet (Default Down count)*/
		
		/* Load Start value in another function  */
		
	  /*Clear interrupt flag*/
		SET_BIT( GPTMICR(ConfigPtr->GptChannel,ConfigPtr->WideTimer),0);
		
}

void Gpt_Interrupt_Enable(uint8 Channel){

			
			/*Enable overflow interrupt only for now*/
			SET_BIT(GPTMIMR(Channel,0),0); //  this supports only 16/32 timers
	
			/*For simplicity i use one timer intrrupt (16/32 Timer0 A) */
			NVIC_EnableIRQ(19);

}

void Gpt_Timer_Enable(uint8 Channel, uint32 Value){

	//  this supports only 16/32 timers(for now only )
		GPTMTAILR(Channel,0) = Value-1;
		SET_BIT(GPIMCTL(Channel,0),0); 
    
}
void Gpt_Timer_Disable(uint8 Channel){

		CLR_BIT(GPIMCTL(Channel,0),0);

}
/*---------------------------------------------------------------------------------* 
*												           	CALL BACK PART
*----------------------------------------------------------------------------------*/
 
void (*Timer_INT_FunctionPtr)(void) = NULL ;

void Gpt_Timer0_Callback(void (* Timer0_FunctionPtr)(void) ){

		if(Timer0_FunctionPtr != NULL){
			 Timer_INT_FunctionPtr = Timer0_FunctionPtr ;
		}
}
void TIMER0A_Handler(void){
   /*Clearing intrrupt flag is confusing for me . 
	   should it be at the begining og the ISR or at the end!!!*/
	SET_BIT( GPTMICR(TIMER0,0),0); // Clearing intrrupt flag 
	
	if(Timer_INT_FunctionPtr != NULL){
		Timer_INT_FunctionPtr();
	}



}
