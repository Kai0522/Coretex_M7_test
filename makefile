CROSS-COMPILER = arm-none-eabi-
CFLAGS=gcc -Wall -std=c11 -mcpu=cortex-m7 -mthumb -mfloat-abi=hard \
       -mfpu=fpv5-sp-d16 -nostartfiles -T stm32f7.ld -specs=nano.specs\
       -specs=nosys.specs

all: main.bin

main.bin:vector_table.s startup.c Kai_STM32f74xxx_GPIO.c main.c malloc.c
	$(CROSS-COMPILER)$(CFLAGS) $^ -o main.elf
	$(CROSS-COMPILER)objcopy -O binary main.elf main.bin

flash:
	st-flash --reset write main.bin 0x08000000

clean:
	rm -f *.o *.elf *.bin
