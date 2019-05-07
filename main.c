#include "Kai_STM32f74xxx_GPIO.h"
#include "Kai_STM32f74xxx_system.h"
#include "reg.h"
#include <stdlib.h>
	        
int main(){
    //Set_system clock
    sysclk_obj *CLOCK=NULL;
    init_sysclk(&CLOCK);
    CLOCK->source=HSE;
    CLOCK->set_sysclk(CLOCK);
    // Initial PI1
    GPIO_obj *PI1=NULL;
    GPIO_init(&PI1);
    PI1->PORT=GPIO_PORTI;
    PI1->PIN=1;

    while(1){
        //Set PI1
        PI1->OSTATUS=HIGH;
        PI1->digitalWrite(PI1);
        //Delay
        for(int i=0;i<1000000;i++)
            ;
        //Reset PI1
        PI1->OSTATUS=LOW;
        PI1->digitalWrite(PI1);
        //Delay
        for(int i=0;i<1000000;i++)
            ;
    }

}
