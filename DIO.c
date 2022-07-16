#include "DIO.h"
#include "DIO_Mcu_HW.h"



void Pin_Init(uint8 Pin,  Port_Config *configPtr){
	uint8 x = 0;//counter
	uint8 port;
	//Port_Config Pins[8] ;// Port_Config struct for every Pin in the port
 // Port_Config *PinsPtr = Pins + Pin; // points to the address of the choosen Pin

	
	/*Bit banding for all used registers*/
	switch(configPtr->Port_Value){
		case GPIO_PORT_A_BASE: port = 0;
													 break;
	  case GPIO_PORT_B_BASE: port = 1;
													 break;
		case GPIO_PORT_C_BASE: port = 2;
													 break;
		case GPIO_PORT_D_BASE: port = 3;
													 break;
		case GPIO_PORT_E_BASE: port = 4;
													 break;
		case GPIO_PORT_F_BASE: port = 5;
													 break;
	}
	uint32 *GPIO_RCGCGPIO_PIN = BITBAND_PERI(SYSTEM_CTL_REG_BASE + RCGCGPIO_OFFESET   , port );
	uint32 *GPIO_DATA_PIN		  = BITBAND_PERI(configPtr->Port_Value + GPIO_DATA_OFFSET , Pin);
	uint32 *GPIO_DIR_PIN 		  = BITBAND_PERI(configPtr->Port_Value + GPIO_DIR_OFFSET  , Pin);
	uint32 *GPIO_FSEL_PIN 	  = BITBAND_PERI(configPtr->Port_Value + GPIO_FSEL_OFFSET , Pin);
	uint32 *GPIO_DEN_PIN      = BITBAND_PERI(configPtr->Port_Value + GPIO_DEN_OFFSET  , Pin);
	uint32 *GPIO_PUR_PIN      = BITBAND_PERI(configPtr->Port_Value + GPIO_PUR_OFFEST  , Pin);
	uint32 *GPIO_PDR_PIN      = BITBAND_PERI(configPtr->Port_Value + GPIO_PDR_OFFSET  , Pin);
	uint32 *GPIO_R2R_PIN 		  =	BITBAND_PERI(configPtr->Port_Value + GPIO_DR2R_OFFEST , Pin);
	uint32 *GPIO_R4R_PIN  		= BITBAND_PERI(configPtr->Port_Value + GPIO_DR4R_OFFEST , Pin);
	uint32 *GPIO_R8R_PIN  		= BITBAND_PERI(configPtr->Port_Value + GPIO_DR8R_OFFEST , Pin);
	uint32 *GPIO_ODR_PIN  		= BITBAND_PERI(configPtr->Port_Value + GPIO_ODR_OFFEST  , Pin);



 /*************************************/	
	
	/*activate clock for this Pin*/
	*GPIO_RCGCGPIO_PIN = STD_ACTIVE ;
	//for( x=0 ;x<1;x++) // i don't need this loop any more it's working fine 
	//{ // waith for 4 clock cycles  ||ask about this ??||
	//}
/*-----------------------------------------------------------------*/		
	/*configure the Pin as GPIO
	* This statment is converted i.e. 
	* activation of GPIO with 0 put to get into the if use 1
	*/
	if( configPtr->Port_PinModeType == STD_HIGH) 
			*GPIO_FSEL_PIN = STD_LOW;  
/*-----------------------------------------------------------------*/	
	/*configure i/p --> 0 or o/p --> 1*/
	*GPIO_DIR_PIN = configPtr->Port_PinDirectionType; 
/*-----------------------------------------------------------------*/		
	/* 1 --> pull up      0 --> pull down*/
	if     ( configPtr->Port_PinInternalAttachType == PULL_UP_RES  )
		*GPIO_PUR_PIN = ENABLE;	
  else if( configPtr->Port_PinInternalAttachType == PULL_DOWN_RES)
	  *GPIO_PDR_PIN = ENABLE;	
/*-----------------------------------------------------------------*/		
	/*drive current choices*/
	switch (configPtr->Port_PinOutputCurrentType){
			
		case DRIVE_CURRENT_2M : *GPIO_R2R_PIN = STD_HIGH ; break ;
	  case DRIVE_CURRENT_4M : *GPIO_R4R_PIN = STD_HIGH ; break ;
		case DRIVE_CURRENT_8M : *GPIO_R8R_PIN = STD_HIGH ; break ; 
	}
/*-----------------------------------------------------------------*/		
	/*Open Drain configure 1 --> Open Drain  */
	
	*GPIO_ODR_PIN = configPtr->Port_PinType ;
/*-----------------------------------------------------------------*/		
	/*enable Pin*/
	
	*GPIO_DEN_PIN = ENABLE ;
/*-----------------------------------------------------------------*/		
	/*initial Value */
	
	*GPIO_DATA_PIN = configPtr->Port_PinInitialValue ;
	
}


void Write_Pin(uint32 Port_ID, uint8 Pin_ID,uint8 uint8_Value){
	
	uint32 *GPIO_DATA_PIN		  = BITBAND_PERI(Port_ID + GPIO_DATA_OFFSET , Pin_ID);
	
	*GPIO_DATA_PIN = uint8_Value;
}

uint8 Pin_Read(uint32 Port_ID, uint8 Pin_ID){

	uint32 *GPIO_DATA_PIN		  = BITBAND_PERI(Port_ID + GPIO_DATA_OFFSET , Pin_ID);

	return (*GPIO_DATA_PIN);

}
/*
void Pin_Flip(uint32 Port_ID, uint8 Pin_ID){
	
	uint32 *GPIO_DATA_PIN		  = BITBAND_PERI(Port_ID + GPIO_DATA_OFFSET , Pin_ID);
	if((*GPIO_DATA_PIN)) (*GPIO_DATA_PIN)= 0; 
	else (*GPIO_DATA_PIN)= 1 ;
	


}*/

void Port_Init(Port_Config *configPtr){
	
	
		RCGCGPIO = 0xFF;
		//*again Function select is active love to GPIO function but here i did it respond to high*/
	 if( (configPtr->Port_PinModeType) == STD_HIGH) 	GPIOAFSEL = 0x00 ;  
	 else 																						GPIOAFSEL = 0xFF ;
	
	 if( (configPtr->Port_PinDirectionType) == STD_HIGH)  GPIODIR = 0xFF ;
	 else 																								GPIODIR = 0x00;
	  
	 if( (configPtr->Port_PinInternalAttachType) == STD_HIGH) GPIOPUR = 0xFF ;
	 else 																										GPIOPDR = 0xFF ;
	
	 switch (configPtr->Port_PinOutputCurrentType){
			
	  	case DRIVE_CURRENT_2M : GPIODR2R = 0xFF ; break ;
	    case DRIVE_CURRENT_4M : GPIODR4R = 0xFF ; break ;
		  case DRIVE_CURRENT_8M : GPIODR8R = 0xFF ; break ; 
		 
	 }
	
	 if( (configPtr->Port_PinType) == STD_HIGH)  GPIOODR = 0xFF ;
	 else  																			 GPIOODR = 0x00 ;
	 
		GPIODEN	= 0xFF;
	 
	  GPIODATA = configPtr->Port_PinInitialValue ;
	
}

void Port_Write(uint32 Port_Number, uint8 Value ){
	
		GPIODATA  = Value ;

}

uint8 Port_Read(uint32 Port_Number){
	
		return GPIODATA;

}
