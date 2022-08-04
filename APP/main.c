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
#include "SysTick.h"
void LED(void);
void SystemInit(void){}
/*GLOBALVARIABLES*/
uint8 ON =0;
uint8 OFF = 0;	
uint8 counter_ON = 0;
uint8 counter_OFF = 0;
int main(void){
	UART_Init();
		Port_Config output = { PORT_F, PIN_MODE_GPIO, PIN_OUTPUT, PULL_DOWN_RES, DRIVE_CURRENT_2M, OPEN_DRAIN_INACTIVE,  0 };
		Pin_Init(PIN1, &output);
		
		SysTick_Init();
		SysTick_Callback(LED);
		
	while(1){
				do{
						
						Print_String("Enter OFF Time: ");
						OFF = UART_Receiver() - 0x30; //receive OFF time
						UART_Transmitter(OFF+0x30); //echo the number to the UART Terminal 
						Print_String(" Enter ON Time: ");
						ON = UART_Receiver() - 0x30; //receive ON time
						UART_Transmitter(ON+0x30); //echo the number to the UART Terminal 
						if((ON==0)&&(OFF==0)) Print_String(" --> on and off time cant be both zeros!\n");
						}while((ON==0)&&(OFF==0));
						if(ON == 0)
						{
							SysTick_Disable();
							Write_Pin(PORT_F, PIN1, 0);
						}
						else if(OFF == 0)
						{
							SysTick_Disable();
							Write_Pin(PORT_F, PIN1, 1);
						}
						else
						{
						SysTick_Start(0x00F42400);
						}
						UART_Transmitter('\n');

	}

}
void LED(void){

	
	if(Pin_Read(PORT_F,PIN1) == 0){
				counter_OFF++;
				if((counter_OFF >= OFF)){
						Write_Pin(PORT_F, PIN1, 1);
						counter_OFF =0;
				}
				
	}
	else if(Pin_Read(PORT_F,PIN1) == 1){
			counter_ON++;
			if(counter_ON>= ON){
						Write_Pin(PORT_F, PIN1, 0);
						counter_ON =0;
			}
	}
}
