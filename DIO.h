
#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"
#include "DIO_Mcu_HW.h"

typedef struct{
 
	 uint32 Port_Value; // which port to choose
	 uint8  Port_PinDirectionType; //
	 uint8  Port_PinModeType;// GPIO or not 
	 uint8  Port_PinInternalAttachType;//
	 uint8  Port_PinOutputCurrentType;//
	 uint8  Port_PinType;//Open drain
	 uint8  Port_PinInitialValue;//
	
	 // uint8 Port_ConfigType; what is this in the video
	
} Port_Config;

//Port_Config Pins[8] ;// Port_Config struct for every Pin in the port
//Port_Config *PinsPtr = Pins;

/*user interactions MACROS*/

#define PIN_MODE_GPIO          1
#define PIN_MODE_OTHER				 0

#define PIN_OUTPUT						 1
#define PIN_INPUT							 0

#define PULL_UP_RES            1
#define PULL_DOWN_RES          0

#define DRIVE_CURRENT_2M 			0
#define DRIVE_CURRENT_4M			1
#define DRIVE_CURRENT_8M			2

#define OPEN_DRAIN_ACTIVE     1
#define OPEN_DRAIN_INACTIVE   0

enum PINS { PIN0 = 0 ,PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7};

enum PORTS {  PORT_A = GPIO_PORT_A_BASE , PORT_B = GPIO_PORT_B_BASE 
						, PORT_C = GPIO_PORT_C_BASE , PORT_D = GPIO_PORT_D_BASE
						, PORT_E = GPIO_PORT_E_BASE , PORT_F = GPIO_PORT_F_BASE};




void Pin_Init(uint8 Pin,  Port_Config *configPtr);
void Port_Init(  Port_Config *configPtr);
void Port_Write(uint32 Port_Number, uint8 Value );
uint8 Port_Read(uint32 Port_Number);
void Write_Pin(uint32 Port_ID, uint8 Pin_ID,uint8 uint8_Value);
uint8 Pin_Read(uint32 Port_ID, uint8 Pin_ID);
//void Pin_Flip(uint32 Port_ID, uint8 Pin_ID);

//void Port_Init( Port_Config *configPtr);
#endif
