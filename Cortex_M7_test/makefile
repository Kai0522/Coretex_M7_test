CROSS-COMPILER = arm-none-eabi-
<<<<<<< HEAD
CFLAGS=gcc -Wall -std=c11 -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -nostartfiles -T stm32f7.ld
=======
CFLAGS=gcc -Wall -std=gnu99 -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -nostartfiles -T stm32f7.ld
>>>>>>> f9a93842e6341b7a07612597ac0615453dcf2c5f

all: main.bin

main.bin:vector_table.s startup.c GPIO.c main.c
	$(CROSS-COMPILER)$(CFLAGS) $^ -o main.elf
	$(CROSS-COMPILER)objcopy -O binary main.elf main.bin

flash:
	st-flash --reset write main.bin 0x08000000

clean:
	rm -f *.o *.elf *.bin
