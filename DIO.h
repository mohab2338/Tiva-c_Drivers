
#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"

/*BASE Addrsses for APB */
#define SYSTEM_CTL_REG_BASE					0x400FE000
#define GPIO_PORT_A_BASE				    0x40004000
#define GPIO_PORT_B_BASE						0x40005000
#define GPIO_PORT_C_BASE				    0x40006000
#define GPIO_PORT_D_BASE						0x40007000
#define GPIO_PORT_E_BASE				    0x40024000
#define GPIO_PORT_F_BASE						0x40025000

/*registers offests*/
#define RCGCGPIO_OFFESET    0x608
#define GPIO_DIR_OFFSET   	0x400
#define GPIO_FSEL_OFFSET 		0x420
#define GPIO_DATA_OFFSET		0x3FC
#define GPIO_DEN_OFFSET			0x51C
#define GPIO_PUR_OFFEST     0x510
#define GPIO_PDR_OFFSET			0x514
#define GPIO_DR2R_OFFEST		0x500
#define GPIO_DR4R_OFFEST		0x504
#define GPIO_DR8R_OFFEST		0x508
#define GPIO_ODR_OFFEST		  0x50C



#define RCGCGPIO        *((volatile unsigned long *)(SYSTEM_CTL_REG_BASE + RCGCGPIO_OFFESET)) // Clock Eable
#define GPIODIR 				*((volatile unsigned long *)(GPIO_PORT_A_BASE 	 + GPIO_DIR_OFFSET ))
#define GPIOAFSEL				*((volatile unsigned long *)(GPIO_PORT_A_BASE 	 + GPIO_FSEL_OFFSET))
#define GPIODEN         *((volatile unsigned long *)(GPIO_PORT_A_BASE 	 + GPIO_DEN_OFFSET ))
#define GPIODATA        *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_DATA_OFFSET))//don't forget to find solution to port masking by address i have activated all bits 
#define GPIOPUR         *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_PUR_OFFEST ))
#define GPIOPDR         *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_PDR_OFFSET ))
#define GPIODR2R        *((volatile unsigned long *)(GPIO_PORT_A_BASE	 	 + GPIO_DR2R_OFFEST))
#define GPIODR4R        *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_DR4R_OFFEST))
#define GPIODR8R        *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_DR8R_OFFEST))
#define GPIOODR         *((volatile unsigned long *)(GPIO_PORT_A_BASE		 + GPIO_ODR_OFFEST ))


/*Bit Banding
*  To use it define a Pointer and assign the macro function to it
*  ex : uint32 *GPIOA_DATA_PIN1 = BITBAND_PERI(GPIOA_DATA_ADDR,0);
*  A pointer to the PIN 0 of DATA_PORTA
*/
/**Peripheral Bit Banding**/
#define BITBAND_PERI_BASE 0x40000000 // Base Address of priphral bit-band
#define ALIAS_PERI_BASE   0x42000000 // base address of pripheral alias band
/***this formula to use bit banding on priphrals***/
#define BITBAND_PERI(PERI_ADDRESS,BIT)  ((uint32 *)( ALIAS_PERI_BASE + (((uint32)PERI_ADDRESS - BITBAND_PERI_BASE)*32) +(BIT*4)) )
/**SRAM Bit Banding**/
#define BITBAND_SRAM_BASE  0x20000000	//Base Address of SRAM bit_band
#define ALIAS_SRAM_BASE 	 0x22000000 //Base Address of SRAM alias band
/***this formula to use bit banding on SRAM***/
#define BITBAND_SRAM(SRAM_ADDRESS,BIT)	((uint32 *)( ALIAS_SRAM_BASE + (((uint32)SRAM_ADDRESS - BITBAND_SRAM_BASE)*32) + (BIT*4)) ) 

typedef struct{
 
	 uint8 Port_PinDirectionType; //
	 uint8 Port_PinModeType;// GPIO or not 
	 uint8 Port_PinInternalAttachType;//
	 uint8 Port_PinOutputCurrentType;//
	 uint8 Port_PinType;//Open drain
	 uint8 Port_PinInitialValue;//
	
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





void Pin_Init(uint8 Pin,  Port_Config *configPtr);


//void Port_Init( Port_Config *configPtr);
#endif
