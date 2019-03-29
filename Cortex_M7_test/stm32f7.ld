MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
}

SECTIONS
{
	.mytext :
	{
		KEEP(*(.vector_table))
		*(.text)
	} > FLASH
}
