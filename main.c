
/*1 - Enable clock RCGCGPIO  */
#define RCGCGPIO       (*((volatile unsigned long *)0x400FE608))
	
	
/*2 - Set The Direction GPIODIR ( 1 --> o/p , 0 --> i\p )*/
#define GPIODIR 				*((volatile unsigned long *)(0x40004000+0x400))

/*3 - configure GPIOAFSEL for GPIO or Alternate unction */
#define GPIOAFSEL				*((volatile unsigned long *)(0x40004000+0x420))

/*4 - Set th driv Strngth  GPIODR2R, GPIODR4R, and GPIODR8R*/
   /*ignore for now*/

/*5 - GPIOUP, GPIOPDR, GPIOODR  --> pull Up ,Pull down ,and open drain*/


/*6 - Enable Digital i/o Set DEN bit in GPIODEN (To
      enable GPIO pins to their analog function (if available)
			, set the GPIOAMSEL bit in the GPIOAMSEL register )*/
#define GPIODEN        *((volatile unsigned long *)(0x40004000+0x51C))

/*7 - Try to write in the Pin*/
#define GPIODATA        *((volatile unsigned long  *)(0x40004000+0x03C))
	

#define GPIODEN_F			  (*((volatile unsigned long *)0x4002551C))
#define GPIODIR_F		    (*((volatile unsigned long *)0x40025400))
#define GPIODATA_F		  (*((volatile unsigned long *)0x400253FC))
	

typedef unsigned long  uint32 ;
#define BITBAND_PERI_BASE 0x40000000 // Base Address of priphral bit-band
#define ALIAS_PERI_BASE   0x42000000 // base address of pripheral alias band
#define BITBAND_PERI(PERI_ADDRESS,BIT)  ((uint32 *)( ALIAS_PERI_BASE + (((uint32)PERI_ADDRESS - BITBAND_PERI_BASE)*32) +(BIT*4)) ) //this formula to use bit banding on priphrals

#define BITBAND_SRAM_BASE  0x20000000
#define ALIAS_SRAM_BASE 	 0x22000000
#define BITBAND_SRAM(SRAM_ADDRESS,BIT)	((uint32 *)( ALIAS_SRAM_BASE + (((uint32)SRAM_ADDRESS - BITBAND_SRAM_BASE)*32) + (BIT*4)) ) //this formula to use bit banding on SRAM

#define GPIOA_DATA_ADDR   0x4000403C
void SystemInit(void){

}

int main(){
	uint32 *GPIOA_DATA_PIN1 = BITBAND_PERI(GPIOA_DATA_ADDR,0);// a pointer to the PIN 0 of DATA_PORTA
		int x =0;
	RCGCGPIO = 0x01;    /* Enable Port A clock  */
	for( x=0 ;x==2;x++)
	{
	}
	GPIODIR  |= 0xFF;    /* Set Pin as o/p       */
//	GPIOAFSEL |= 0x0;  /* Configure pin as GPIO*/
	GPIODEN  |= 0xFF ;    /* Digital Enable      */
	//GPIODATA = 0x4 ;
//	uint32 GPIOA_DATA  = GPIOA_DATA_ADDR;
	
	
	*GPIOA_DATA_PIN1 = 0x03;
	
}
