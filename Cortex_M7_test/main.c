#include "GPIO.h"
#include "reg.h"
int i;

int main(){
    pinMode(GPIO_PORTI,1,OUTPUT);
    while(1){
     digitalWrite(GPIO_PORTI,1,HIGH);
     for(i=0;i<1000000;i++)
         ;
     digitalWrite(GPIO_PORTI,1,LOW);
     for(i=0;i<1000000;i++)
         ;
    }
}
