#include "./BSP/LED/led.h"

// 通用定时器中断服务函数
void GTIM_TIMX_INT_IRQHandler(void)
{
    if (GTIM_TIMX_INT->SR & 0X0001) // 溢出中断
    {
        LED1_TOGGLE();
    }
    GTIM_TIMX_INT->SR &= ~(1 << 0); // 清除中断标志
}

// 中断初始化函数
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();
    GTIM_TIMX_INT->ARR = arr;
    GTIM_TIMX_INT->PSC = psc;
    GTIM_TIMX_INT->DIER |= 1 << 0;
    GTIM_TIMX_INT->CR1 |= 1 << 0;
    sys_nvic_init(1, 3, GTIM_TIMX_INT_IRQn, 2);
}
