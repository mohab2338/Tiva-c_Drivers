
#include "DIO.h"


void SystemInit(void){

}
int main(void){
	
	
	Port_Config mode = { PIN_MODE_GPIO, PIN_OUTPUT, PULL_UP_RES, DRIVE_CURRENT_2M, OPEN_DRAIN_INACTIVE,  0xF1 };
	
	 Pin_Init(PIN0,  &mode);
	
	
}
