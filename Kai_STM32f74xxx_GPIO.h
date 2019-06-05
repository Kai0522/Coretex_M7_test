#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <malloc.h>
#include "reg.h"

#define push_pull 0
#define open_drain 1

#define Low_speed 0
#define Medium_speed 1
#define High_speed 2
#define Very_high_speed 3

#define No_pull_up_pull_down 0
#define Pull_up 1
#define Pull_down 2

#define HIGH 1
#define LOW 0

typedef struct GPIO GPIO_obj;
typedef int (*GPIN_func_t)(GPIO_obj *);
typedef void (*GPOUT_func_t)(GPIO_obj *);

struct GPIO{
    int PORT,PIN;
    int OTYPER,OSPEEDR,PUPDR,OSTATUS;
    GPOUT_func_t digitalWrite;
    GPIN_func_t  digitalRead;
};

int GPIO_init(GPIO_obj **self);    //Initial object , assign initial value and function pointer.
void digitalWrite_impl(GPIO_obj *self);
int digitalRead_impl(GPIO_obj *self);

#endif
