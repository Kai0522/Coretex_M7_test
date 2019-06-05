CROSS-COMPILER = arm-none-eabi-
CFLAGS=gcc -Wall -std=c11 -mcpu=cortex-m4 -mthumb -nostartfiles -T stm32f7.ld

all: main.bin

main.bin:vector_table.s startup.c Kai_STM32f74xxx_GPIO.c \
	Kai_STM32f74xxx_system.c main.c malloc.c context_switch.S \
	syscall.S usart.c
	$(CROSS-COMPILER)$(CFLAGS) $^ -o main.elf
	$(CROSS-COMPILER)objcopy -O binary main.elf main.bin

flash:
	st-flash --reset write main.bin 0x08000000

clean:
	rm -f *.o *.elf *.bin
