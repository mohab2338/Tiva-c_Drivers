#include "Std_Types.h"
#include "SysTick.h"

void SysTick_Init(void){

		/*1. Disable Systick */
		CLR_BIT(STCTRL, STCTRL_ENABLE);
	  /*2. Reload for 1 sec min*/
		//STRELOAD = 0x00F42400 ;
	
		/*3. Clar Current (any value will clear it )*/
		STCURRENT	= 0;

		/*4. choose System Clk --> (STCTRL_CLK_SRC = 1)  PIOSC/4 -->(STCTRL.CL_SRC = 0)*/
		CLR_BIT(STCTRL,STCTRL_CLK_SRC );
	  /*5. Enable interrupt */
		SET_BIT(STCTRL, STCTRL_INTEN);

}

void SysTick_Start(uint32 Ticks_value){

		STRELOAD = Ticks_value ;
		SET_BIT(STCTRL, STCTRL_ENABLE);

}
void SysTick_Disable(void){

		CLR_BIT(STCTRL, STCTRL_ENABLE);

}
/*---------------------------------------------------------------------------------* 
*												           	CALL BACK PART
*----------------------------------------------------------------------------------*/

void (*SysTick_INT_FunctionPtr)(void) = NULL ;

void SysTick_Callback(void (* Timer0_FunctionPtr)(void) ){
	
		if(Timer0_FunctionPtr != NULL){
			 SysTick_INT_FunctionPtr = Timer0_FunctionPtr ;
		}
}
void SysTick_Handler(void){
   
	//SET_BIT( GPTMICR(TIMER0,0),0); // Clearing intrrupt flag 
	
	if(SysTick_INT_FunctionPtr != NULL){
		SysTick_INT_FunctionPtr();
	}

}
