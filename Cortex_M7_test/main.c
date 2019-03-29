#include "GPIO.h"
#include "reg.h"
int j=522;
int i=500;
int bss_test;

int main(){
    pinMode(GPIO_PORTI,1,OUTPUT);
    while(1){
     digitalWrite(GPIO_PORTI,1,HIGH);
     for(i=0;i<100000;i++)
         ;
     digitalWrite(GPIO_PORTI,1,LOW);
     for(i=0;i<100000;i++)
         ;
    }
}
