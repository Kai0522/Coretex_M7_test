CROSS-COMPILER = arm-none-eabi-
CFLAGS=gcc -Wall -std=gnu99 -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -nostartfiles -T stm32f7.ld

all: main.bin

main.bin: main.c vector_table.s GPIO.c
	$(CROSS-COMPILER)$(CFLAGS) $^ -o main.elf
	$(CROSS-COMPILER)objcopy -O binary main.elf main.bin

flash:
	st-flash --reset write main.bin 0x08000000

clean:
	rm -f *.o *.elf *.bin
