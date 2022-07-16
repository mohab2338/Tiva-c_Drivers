typedef unsigned int uint32

extern uint32 __data_load__  ;
extern uint32 __data_start__ ;
extern uint32 __data_end__   ;
extern uint32 __bss_start__  ;
extern uint32 __bss_end__ 	 ;
extern uint32 _stack		 ;

void ResetHandlr(void)
{
	/*initialize Stack pointer : Done by harware 
	with the first address in vector table */

	uint32 *ptr2Sbss = (uint32*)&__bss_start__  ;
	uint32 *ptr2Ebss = (uint32*)&__bss_end__    ;
	
	uint32 *ptr2Src  = (uint32*)&__data_load__  ;
	uint32 *ptr2sDes = (uint32*)&__data_start__ ;
	uint32 *ptr2eDes = (uint32*)&__data_end__   ;
	
	/*Init .BSS*/
	while(ptr2Sbss<ptr2Ebss){
		*(ptr2Sbss++) = 0;
	}
	/*Init.DATA*/
	while(ptr2sDes<ptr2eDes){
		*(ptr2sDes++) = *(ptr2Src++);
	}
	/*Jump to Main*/
	main();
	
	while(1);/*code should not get out of main this just fo safety*/
}