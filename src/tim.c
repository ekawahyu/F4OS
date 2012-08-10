#include "types.h"
#include "registers.h"
#include "task.h"
#include "semaphore.h"
#include "usart.h"
#include "tim.h"

void init_timer(void) {
    /* Enable TIM2 clock */
    *RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Enable interrupt */
    *NVIC_ISER0 |= (1 << 28);
    *TIM2_DIER |= TIM2_DIER_UIE;

    *TIM2_PSC = 84-1;
    *TIM2_ARR = 100-1;  /* Period in microseconds */

    *TIM2_CR1 |= TIM2_CR1_ARPE;

    /* Enable timer */
    *TIM2_CR1 |= TIM2_CR1_CEN;
    *TIM2_EGR = 1;
}

void tim2_handler(void) {
    *TIM2_SR = 0;

    task_node *node = periodic_task_list.head;

    while (node) {
        if (node->task->ticks_until_wake == 0) {
            if (!node->task->running) {
                append_task(&task_list, node->task->task_list_node);
            }
            node->task->ticks_until_wake = node->task->period;
        }
        else {
            node->task->ticks_until_wake--;
        }

        node = node->next;
    }
}
