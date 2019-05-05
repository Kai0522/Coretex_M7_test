MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
	SRAM (rwx) : ORIGIN = 0x20010000, LENGTH =256K
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

}
