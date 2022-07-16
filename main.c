
#include "DIO.h"

/* remmmber Port c in pinconfig doesb't work*/
void SystemInit(void){

}
int main(void){
	
	uint8 pin_value = 0;
	Port_Config mode = { PORT_C, PIN_MODE_GPIO, PIN_INPUT, PULL_DOWN_RES, DRIVE_CURRENT_2M, OPEN_DRAIN_INACTIVE,  1 };
	
	 Pin_Init(PIN0, &mode);
	
	//Write_Pin(PORT_A, PIN0, 1 );
	
	//Port_Write(PORT_A, 0x0E );
	//Pin_Flip(PORT_A, PIN0);
	
	//pin_value = Pin_Read(PORT_A, PIN0);
	//Port_Write(PORT_A, port_value );
	
}
