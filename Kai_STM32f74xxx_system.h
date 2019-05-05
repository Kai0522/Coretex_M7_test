#ifndef __OS_H_
#define __OS_H_

#define MAX_TASKS 10
#define STACK_SIZE 256
#define MAX_HEAPS 4096

#define HSI 0
#define HSE 1
#define PLL 2

typedef struct sysclk sysclk_obj; 
typedef void (*clkfunc_t)(sysclk_obj *);

struct sysclk {
    int source,PLL_P,PLL_M,PLL_N;
    clkfunc_t set_sysclk;
};

int init_sysclk(sysclk_obj **self);
void set_sysclk_impl(sysclk_obj *self);
#endif
