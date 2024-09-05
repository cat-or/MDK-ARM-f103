#include "./BSP/LED/led.h"

// 初始化LED相关IO口，使能时钟
void led_init(void)
{
    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();

    sys_gpio_set(LED0_GPIO_PORT, LED0_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PU);

    sys_gpio_set(LED1_GPIO_PORT, LED1_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PU);

    LED0(1);
    LED1(1);             
}
