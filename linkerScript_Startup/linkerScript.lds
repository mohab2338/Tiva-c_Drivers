
MEMORY
{
	FLASH (RX) : ORIGIN = 0x00000000, LENGTH = 0x00040000
	SRAM (WX)  : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

SECTIONS {
		
	PROVIDE (_intvecs_base_address = 0x00);
	.intvecs (_intvecs_base_address) : AT (_intvecs_base_address){
		KEEP (*(.intvecs))
	} > FLASH
	
	.my_sec (0x00030000): AT(0x00030001){
		KEEP(*(.my_sec))
	} > FLASH
	
	.text :{
		CREATE_OBJECT_SYMBOLS
		*(.text)
		*(.text.*)
	} > FLASH
	
	.rodata :{
		*(.rodata)
		*(.rodata.*)
	} > FLASH
	.data :ALIGN (4) {
		__data_load__  = LOADADDR (.data);
		__data_start__ = .;
		*(.data)
		*(.data.*)
		__data_end__ = .;
	} > SRAM AT> FLASH
	
	.bss :{
		__bss_start__ = .;
		*(.shbss)
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN (4);
		__bss_end__ = .;
	} > SRAM
	
	.stack :ALIGN(0x8) {
		_stack = .;
		__stack = .;
		KEEP(*(.stack))
	} > SRAM
}