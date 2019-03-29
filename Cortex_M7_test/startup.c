#include <stdint.h>

extern int main(void);

void reset_handler(void)
{
	//symbols defined in linker script
	extern uint32_t _data_lma_start;
	extern uint32_t _data_vma_start;
	extern uint32_t _data_vma_end;
	extern uint32_t _bss_vma_start;
	extern uint32_t _bss_vma_end;
	//note that for the variables above, "symbol value" is equivalent to the address we want
	//use "&" operator to get symbol values

	uint32_t *data_lstart_ptr = &_data_lma_start;
	uint32_t *data_vstart_ptr = &_data_vma_start;
	uint32_t *data_vend_ptr = &_data_vma_end;

	uint32_t *bss_vstart_ptr = &_bss_vma_start;
	uint32_t *bss_vend_ptr = &_bss_vma_end;

	uint32_t *src_ptr, *dst_ptr;

	src_ptr = data_lstart_ptr;
	dst_ptr = data_vstart_ptr;

	while (dst_ptr < data_vend_ptr)
		*dst_ptr++ = *src_ptr++;

	dst_ptr = bss_vstart_ptr;

	while (dst_ptr < bss_vend_ptr)
		*dst_ptr++ = 0;

	main();
}
