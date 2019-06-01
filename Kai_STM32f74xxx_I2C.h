#ifndef I2C_H
#define I2C_H

#include "Kai_STM32f74xxx_GPIO.h"

typedef struct I2C I2C_obj
typedf int (*I2Crfun_t)(I2C_obj *)
typedef void (*I2Cwfun_t)(I2C_obj *)

struct I2C{
    int address , reg , channel;
    uint8_t data;
    I2Crfun_t   I2CReadData;
    I2Cwfun_t   I2CWriteData;
}

int I2C_init(I2C_obj **self);
int I2C_ReadData_impl(I2C_obj *self);
void I2C_WriteData_impl(I2C_obj *self);
#endif
