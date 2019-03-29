MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
<<<<<<< HEAD
	SRAM (rwx) : ORIGIN = 0x20010000, LENGTH = 256K
=======
>>>>>>> f9a93842e6341b7a07612597ac0615453dcf2c5f
}

SECTIONS
{
	.text :
	{
		KEEP(*(.vector_table))
		*(.text)
		*(.rodata)
		_data_lma_start = .; 
	} > FLASH
<<<<<<< HEAD

	.data : AT(_data_lma_start) 
	{
		_data_vma_start = .;
		*(.data)
		_data_vma_end = .;
	} > SRAM

	.bss :
	{
		_bss_vma_start = .;
		*(.bss)
		*(COMMON)
		_bss_vma_end = .;
	} > SRAM
	
	_msp_init = ORIGIN(SRAM) + LENGTH(SRAM);
=======
>>>>>>> f9a93842e6341b7a07612597ac0615453dcf2c5f
}
