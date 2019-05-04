#include "Kai_STM32f74xxx.h"
#include "reg.h"
#include <stdlib.h>
	        
int main(){
    GPIO_obj *PI1=NULL;
    GPIO_init(&PI1);
    PI1->PORT=GPIO_PORTI;
    PI1->PIN=1;
    while(1){
        PI1->OSTATUS=HIGH;
        PI1->digitalWrite(PI1);
        for(int i=0;i<100000;i++)
            ;
        PI1->OSTATUS=LOW;
        PI1->digitalWrite(PI1);
        for(int i=0;i<100000;i++)
            ;
    }
}
