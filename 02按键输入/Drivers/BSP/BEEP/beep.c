#include "./BSP/BEEP/beep.h"

void beep_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    BEEP_GPIO_CLK_ENABLE();                             /* BEEP时钟使能 */
    
    gpio_init_struct.Pin = BEEP_GPIO_PIN;               /* 设置蜂鸣器引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        /* 设置推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉模式 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速50Mhz */
    HAL_GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);   /* 初始化蜂鸣器引脚 */
    
    BEEP(0);                                            /* 关闭蜂鸣器 */
}
