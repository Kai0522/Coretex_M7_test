#include <stdint.h>
#include <malloc.h>
#include "reg.h"
#include "Kai_STM32f74xxx_GPIO.h"
int GPIO_init(GPIO_obj **self){
    if(NULL == (*self=malloc(sizeof(GPIO_obj)))) return -1;
    //Reset default parameter:OUTPUT LOW,push-pull,Loe speed,No pull-up,No pull-down 
    (*self)->PORT=0; (*self)->PIN=0;
    (*self)->OTYPER=push_pull; (*self)->OSPEEDR=Low_speed;(*self)->PUPDR=No_pull_up_pull_down; 
    (*self)->OSTATUS=LOW;
    (*self)->digitalWrite=digitalWrite_impl;
    (*self)->digitalRead=digitalRead_impl;
    return 0;
}


void digitalWrite_impl(GPIO_obj *self){
 	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(self->PORT));

	//MODER led pin = 01 => General purpose output mode
	CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_MODER_OFFSET, MODERy_1_BIT(self->PIN));
	SET_BIT(GPIO_BASE(self->PORT) + GPIOx_MODER_OFFSET, MODERy_0_BIT(self->PIN));

    if(self->OTYPER == push_pull)
   	    //OT led pin = 0 => Output push-pull
	    CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_OTYPER_OFFSET, OTy_BIT(self->PIN));
    else
   	    //OT led pin = 1 => Ouput open-drain
	    SET_BIT(GPIO_BASE(self->PORT) + GPIOx_OTYPER_OFFSET, OTy_BIT(self->PIN));
        
	switch(self->OSPEEDR){
        case Low_speed:
            //OSPEEDR led pin = 00 => Low speed
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(self->PIN));
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(self->PIN));
        case Medium_speed:
            //OSPEEDR led pin = 01 => Medium speed
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(self->PIN));
	        SET_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(self->PIN));
        case High_speed:
            //OSPEEDR led pin = 10 => High speed
	        SET_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(self->PIN));
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(self->PIN));
        case Very_high_speed:
            //OSPEEDR led pin = 11 => Very-high speed
	        SET_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(self->PIN));
	        SET_BIT(GPIO_BASE(self->PORT) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(self->PIN));
    }
    switch(self->PUPDR){
        case No_pull_up_pull_down:
	        //PUPDR led pin = 00 => No pull-up, pull-down
            CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(self->PIN));
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(self->PIN));
        case Pull_up:
	        //PUPDR led pin = 01 => Pull-up
            CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(self->PIN));
	        SET_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(self->PIN));
        case Pull_down:
	        //PUPDR led pin = 10 => Pull-down
            SET_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(self->PIN));
	        CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(self->PIN));

    }
    if((self->OSTATUS)==HIGH){
		//set GPIOD(port,pin)
		CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_BSRR_OFFSET, BRy_BIT(self->PIN));
    	SET_BIT(GPIO_BASE(self->PORT) + GPIOx_BSRR_OFFSET, BSy_BIT(self->PIN));
    }
		
    if((self->OSTATUS)==LOW){
		//reset GPIO(port,pin)
    	CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_BSRR_OFFSET, BSy_BIT(self->PIN));
		SET_BIT(GPIO_BASE(self->PORT) + GPIOx_BSRR_OFFSET, BRy_BIT(self->PIN));
    }
}

int digitalRead_impl(GPIO_obj *self){
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET,GPIO_EN_BIT(self->PORT));
        
    //MODER led pin =00 => General purpose input mode
    CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_MODER_OFFSET , MODERy_1_BIT(self->PIN));
    CLEAR_BIT(GPIO_BASE(self->PORT) + GPIOx_MODER_OFFSET , MODERy_0_BIT(self->PIN));
    
    if(READ_BIT(GPIO_BASE(self->PORT)+GPIOx_IDR_OFFSET,self->PIN)==0)
        return 0;
    else
        return 1;
}
