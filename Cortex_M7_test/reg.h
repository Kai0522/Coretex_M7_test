#ifndef REG_H
#define REG_H
//Defign syntax
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
//REG OPERATIONS

#define UINT32_1 ((uint32_t)1)

#define REG(addr) (*((volatile uint32_t *)(addr)))

#define SET_BIT(addr, bit) (REG(addr) |= UINT32_1 << (bit))
#define CLEAR_BIT(addr, bit) (REG(addr) &= ~(UINT32_1 << (bit)))
#define READ_BIT(addr,bit) (((UINT32_1<<(bit))&REG(addr))^(UINT32_1<<(bit)))

//RCC
#define RCC_BASE 0x40023800

#define RCC_AHB1ENR_OFFSET 0x30
#define GPIO_EN_BIT(port) (port)

//GPIO
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5
#define GPIO_PORTG 6
#define GPIO_PORTH 7
#define GPIO_PORTI 8
#define GPIO_PORTJ 9
#define GPIO_PORTK 10

#define GPIO_BASE(port) (0x40020000 + 0x400 * (port))

#define GPIOx_MODER_OFFSET 0x00
#define MODERy_1_BIT(y) ((y)*2 + 1)
#define MODERy_0_BIT(y) ((y)*2)

#define GPIOx_OTYPER_OFFSET 0x04
#define OTy_BIT(y) (y)

#define GPIOx_OSPEEDR_OFFSET 0x08
#define OSPEEDRy_1_BIT(y) ((y)*2 + 1)
#define OSPEEDRy_0_BIT(y) ((y)*2)

#define GPIOx_PUPDR_OFFSET 0x0C
#define PUPDRy_1_BIT(y) ((y)*2 + 1)
#define PUPDRy_0_BIT(y) ((y)*2)

#define GPIOx_BSRR_OFFSET 0x18
#define BRy_BIT(y) ((y) + 16)
#define BSy_BIT(y) (y)

#define GPIOx_IDR_OFFSET 0x10

#endif
