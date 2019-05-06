#include "Kai_STM32f74xxx_system.h"
#include "malloc.h"
#include "reg.h"
#include <stdint.h>

int init_sysclk(sysclk_obj **self){
    if(NULL==(*self=malloc(sizeof(sysclk_obj)))) return -1;

    (*self)->source=PLL; (*self)->PLL_P=2 ;(*self)->PLL_M=4 ; (*self)->PLL_N=168;
    (*self)->set_sysclk=set_sysclk_impl;
    
    return 0;
}

void set_sysclk_impl(sysclk_obj *self){
    switch(source){
        case HSI:


        case HSE:


        case PLL:
            // enable HSE
            SET_BIT(RCC_BASE+RCC_CR_OFFSET,HSEON_BIT);
            
            // wait
            while (READ_BIT(RCC_BASE + RCC_CR_OFFSET,HSERDY_BIT)!=1){
            }
            
            //set pll
            SET_BIT(RCC_BASE+RCC_PLLCFGR_OFFSET,PLLSCR_BIT);
            
            //f_HSE=8Mhz
            //f_PLL_out=(8*N/M)/P
            if(PLL_N<2) PLL_N=2;
            if(PLL_N>432) PLL_N=432;
            if(PLL_M<2) PLL_M=2;
            switch(PLL_P){
                case 2:
                    uint8_t pll_p=0b00;
                case 4:
                    uint8_t pll_p=0b01;
                case 6: 
                    uint8_t pll_p=0b10;
                case 8:
                    uint8_t pll_p=0b11;
            }
            WRITE_BITS(RCC_BASE+RCC_PLLCFGR_OFFSET,PLLP_1_BIT,PLLP_0_BIT,pll_p);
            WRITE_BITS(RCC_BASE+RCC_PLLCFGR_OFFSET,PLLN_8_BIT,PLLN_0_BIT,PLL_N);
            WRITE_BITS(RCC_BASE+RCC_PLLCFGR_OFFSET,PLLM_5_BIT,PLLM_0_BIT,PLL_M);
            int PLL_OUT_FREQ=(8*PLL_N/PLL_M)/pll_p;
            //enable pll
            SET_BIT(RCC_BASE+RCC_CR_OFFSET,PLLON_BIT);

            //wait
            while(READ_BIT(RCC_BASE+RCC_CR_OFFSET,PLLRDY_BIT)!=1){
            }

            //enable flash prefetch buffer
            if (PLL_OUT_FREQ>30) SET_BIT(FLASH_BASE+FLASH_ACR_OFFSET,PRFTEN_BIT);

            //set flash wait state
            if (PLL_OUT_FREQ>30 && PLL_OUT_FREQ<=60)
                WRITE_BITS(FLASH_BASE+FLASH_ACR_OFFSET,LATENCY_2_BIT,LATENCY_0_BIT,0b001);
            if (PLL_OUT_FREQ>60 && PLL_OUT_FREQ<=90)
                WRITE_BITS(FLASH_BASE+FLASH_ACR_OFFSET,LATENCY_2_BIT,LATENCY_0_BIT,0b010);
            if (PLL_OUT_FREQ>90 && PLL_OUT_FREQ<=120)
                WRITE_BITS(FLASH_BASE+FLASH_ACR_OFFSET,LATENCY_2_BIT,LATENCY_0_BIT,0b011);
            if (PLL_OUT_FREQ>120 && PLL_OUT_FREQ<=150)
                WRITE_BITS(FLASH_BASE+FLASH_ACR_OFFSET,LATENCY_2_BIT,LATENCY_0_BIT,0b100);
            if (PLL_OUT_FREQ>150 && PLL_OUT_FREQ<=168) 
                WRITE_BITS(FLASH_BASE+FLASH_ACR_OFFSET,LATENCY_2_BIT,LATENCY_0_BIT,0b101);
            
            //use pll
            WRITE_BITS(RCC_BASE+RCC_CFGR_OFFSET,SW_1_BIT,SW_0_BIT,0b10);
            //wait
            while((READ_BIT(RCC_BASE+RCC_CFGR_OFFSET,SWS_1_BIT)!=1)||READ_BIT(RCC_BASE+RCC_CFGR_OFFSET,SWS_0_BIT)!=0){
            }            
    }

}