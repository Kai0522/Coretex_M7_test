#include <stdint.h>
#include "Kai_STM32f74xxx_GPIO.h"
#include "Kai_STM32f74xxx_system.h"
#include "reg.h"
#include "asm.h"

#define STACK_SIZE 256
#define TASK_LIMIT 2

void task_init(void)
{
	unsigned int empty[32];
	task_init_env(empty + 32);
}

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

/* Initialize user task stack and execute it one time.
 * We set `THREAD_PSP` to `lr` so that exception return
 * works correctly.
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Babefdjc.html
 */
unsigned int *create_task(unsigned int *stack, void (*start)(void))
{
	stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push */
	stack[8] = (unsigned int) THREAD_PSP;
	stack[15] = (unsigned int) start;
	stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit */
	stack = activate(stack);
	return stack;
}

/*Task_1*/
void task_1(){
    //Initialize task_1
    // Initial PI1
    GPIO_obj *PI1=NULL;
    GPIO_init(&PI1);
    PI1->PORT=GPIO_PORTI;
    PI1->PIN=1;
    syscall();

    //Running task_1
    while(1){
        //Set PI1
        PI1->OSTATUS=HIGH;
        PI1->digitalWrite(PI1);
        //Delay
        for(int i=0;i<1000000;i++)
            ;
        syscall();
    }
}

/*Task_2*/
void task_2(){
    //Initialize task_1 
    // Initial PI1
    GPIO_obj *PI1=NULL;
    GPIO_init(&PI1);
    PI1->PORT=GPIO_PORTI;
    PI1->PIN=1;
    syscall();

    //Running task_1
    while(1){
        //Set PI1
        PI1->OSTATUS=LOW;
        PI1->digitalWrite(PI1);
        //Delay
        for(int i=0;i<1000000;i++)
            ;
        syscall();
    }
}

int main(){
	unsigned int user_stacks[TASK_LIMIT][STACK_SIZE];
	unsigned int *usertasks[TASK_LIMIT];
	size_t task_count = 0;
	size_t current_task;

	task_init();
    //Set_system clock
    sysclk_obj *CLOCK=NULL;
    init_sysclk(&CLOCK);
    CLOCK->source=PLL;
    CLOCK->set_sysclk(CLOCK);

    //Regist User task_1
	usertasks[0] = create_task(user_stacks[0],&task_1);
	task_count += 1; 
    //Regist User task_2
	usertasks[1] = create_task(user_stacks[1], &task_2);
	task_count += 1;

    //Start multitasking
	current_task = 0;
    while(1){
		usertasks[current_task] = activate(usertasks[current_task]);
		current_task = current_task == (task_count - 1) ? 0 : current_task + 1;
    }
}
