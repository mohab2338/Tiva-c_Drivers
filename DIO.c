#include "DIO.h"

void Pin_Init(uint8 Pin,  Port_Config *configPtr){
	int x = 0;//counter
	//Port_Config Pins[8] ;// Port_Config struct for every Pin in the port
 // Port_Config *PinsPtr = Pins + Pin; // points to the address of the choosen Pin
	
	/*Bit banding for all used registers*/
	uint32 *GPIO_RCGCGPIO_PIN = BITBAND_PERI(SYSTEM_CTL_REG_BASE + RCGCGPIO_OFFESET   , Pin);
	uint32 *GPIO_DATA_PIN		  = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DATA_OFFSET , Pin);
	uint32 *GPIO_DIR_PIN 		  = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DIR_OFFSET  , Pin);
	uint32 *GPIO_FSEL_PIN 	  = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_FSEL_OFFSET , Pin);
	uint32 *GPIO_DEN_PIN      = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DEN_OFFSET  , Pin);
	uint32 *GPIO_PUR_PIN      = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_PUR_OFFEST  , Pin);
	uint32 *GPIO_PDR_PIN      = BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_PDR_OFFSET  , Pin);
	
	uint32 *GPIO_R2R_PIN 		  =	BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DR2R_OFFEST , Pin);
	uint32 *GPIO_R4R_PIN  		= BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DR4R_OFFEST , Pin);
	uint32 *GPIO_R8R_PIN  		= BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_DR8R_OFFEST , Pin);

	uint32 *GPIO_ODR_PIN  		= BITBAND_PERI(GPIO_PORT_A_BASE + GPIO_ODR_OFFEST  , Pin);

 /*************************************/	
	
	/*activate clock for this Pin*/
	*GPIO_RCGCGPIO_PIN = STD_ACTIVE ;
	for( x=0 ;x<2;x++)
	{ // waith for 4 clock cycles  ||ask about this ??||
	}
	
	/*configure the Pin as GPIO
	* This statment is converted i.e. 
	* activation of GPIO with 0 put to get into the if use 1
	*/
	if( configPtr->Port_PinModeType == STD_HIGH) 
			*GPIO_FSEL_PIN = STD_LOW;  
	
	/*configure i/p --> 0 or o/p --> 1*/
	*GPIO_DIR_PIN = configPtr->Port_PinDirectionType; 
	
	/* 1 --> pull up      0 --> pull down*/
	if     ( configPtr->Port_PinInternalAttachType == PULL_UP_RES  )
		*GPIO_PUR_PIN = ENABLE;	
  else if( configPtr->Port_PinInternalAttachType == PULL_DOWN_RES)
	  *GPIO_PDR_PIN = ENABLE;	
	
	/*drive current choices*/
	switch (configPtr->Port_PinOutputCurrentType){
			
		case DRIVE_CURRENT_2M : *GPIO_R2R_PIN = STD_HIGH ; break ;
	  case DRIVE_CURRENT_4M : *GPIO_R4R_PIN = STD_HIGH ; break ;
		case DRIVE_CURRENT_8M : *GPIO_R8R_PIN = STD_HIGH ; break ; 
	}
	/*Open Drain configure 1 --> Open Drain  */
	
	*GPIO_ODR_PIN = configPtr->Port_PinType ;
	
	/*enable Pin*/
	
	*GPIO_DEN_PIN = ENABLE ;
	
	/*initial Value */
	
	*GPIO_DATA_PIN = configPtr->Port_PinInitialValue ;
	
}
