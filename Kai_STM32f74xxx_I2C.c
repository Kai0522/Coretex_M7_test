#include "Kai_STM32f74xxx_I2C.h"
#include <stddef.h>

void I2C_setting(){
;
}

int I2C_init(I2C_obj **self){
    if(NULL==(*self=malloc(sizeof(I2C_obj)))) return -1;
    (*self)->adress=0x00 ;(*self)->reg=0x00 ;
    (*self)->channel=1;(*self)->timeout=1;
    (*self)->data=0;

    //assign function pointer
    (*self)->I2CReadData=I2CReadData_impl;
    (*self)->I2CWriteData=I2CWriteData_impl;

    return 0;
}

void I2C_ReadData_impl(I2C_obj *self){

;
}

void I2C_WriteData_impl(I2C_obj *self){
;
}
