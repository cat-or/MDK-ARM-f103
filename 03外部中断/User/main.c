#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/EXTI/exti.h"


int main(void)
{
	HAL_Init();                             /* 初始化 HAL 库 */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
	delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                         /* 串口初始化 */
	led_init();                             /* 初始化 LED */
    beep_init();                            /* 初始化 蜂鸣器 */
    extix_init();                             /* 初始化 按键 */
    LED0(0);                                /* 点亮LED0 红 */
	
	while (1)
	{
        printf("OK\r\n");
        delay_ms(1000);
	}
}
