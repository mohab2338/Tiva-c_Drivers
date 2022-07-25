/*---------------------------------------------------*
*  FILE DESCRIPTION
*----------------------------------------------------
*			File: main.c
*			Description: LED control on and off times 
**----------------------------------------------------*/
#include "DIO.h"
#include "NVIC.h"
#include "Timer.h"
#include "PLL.h"
#include "UART.h"

void LED(void);

void SystemInit(void){}

/*GLOBALVARIABLES*/
uint16 ON =0;
uint16 OFF = 0;	
uint32 NumberOfTicks_ON = 0;
uint32 NumberOfTicks_OFF = 0;

int main(void){
	
	UART_Init();	
	Port_Config output = { PORT_F, PIN_MODE_GPIO, PIN_OUTPUT, PULL_DOWN_RES, DRIVE_CURRENT_2M, OPEN_DRAIN_INACTIVE,  0 };
  Pin_Init(PIN1, &output);
	Gpt_ConfigType Timer = {NON_WIDE, TIMER0, 0, 5000000, PERIODIC };
	Gpt_Init(&Timer);
	Gpt_Interrupt_Enable(TIMER0);
	Gpt_Timer0_Callback(LED);
		
	while(1){
	
			do{
			
			Print_String("Enter OFF Time: ");
			OFF = UART_Receiver() - 0x30; //receive OFF time
			NumberOfTicks_OFF = OFF*(16000000-1);
			UART_Transmitter(OFF+0x30); //echo the number to the UART Terminal 
			Print_String(" Enter ON Time: ");
			ON = UART_Receiver() - 0x30; //receive ON time
			NumberOfTicks_ON  = ON*(16000000-1);
			UART_Transmitter(ON+0x30); //echo the number to the UART Terminal 
			if((ON==0)&&(OFF==0)) Print_String(" --> on and off time cant be both zeros!\n");
			
			
			}while((ON==0)&&(OFF==0));
			
			if(OFF != 0){
				Write_Pin(PORT_F, PIN1, 0);
				Gpt_Timer_Enable(TIMER0,NumberOfTicks_OFF);
			}
			
			
			UART_Transmitter('\n');
	}

}
void LED(void){
	
	Pin_Flip(PORT_F, PIN1);
	
	if(Pin_Read(PORT_F,PIN1) == 0){
		if(OFF != 0){
				Gpt_Timer_Enable(TIMER0,NumberOfTicks_OFF);
		}
		else{Pin_Flip(PORT_F, PIN1);}
	}
	else{
		if(ON != 0){
				Gpt_Timer_Enable(TIMER0,NumberOfTicks_ON);
		}
		else{Pin_Flip(PORT_F, PIN1);}
	}
}
