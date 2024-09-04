#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/WDG/wdg.h"
#include "./BSP/KEY/key.h"


//int main(void)
//{
//    HAL_Init();                             /* 初始化HAL库 */
//    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
//    delay_init(72);                         /* 延时初始化 */
//    usart_init(115200);                     /* 串口初始化为115200 */
//    led_init();                             /* 初始化LED */
//    key_init();                             /* 初始化按键 */
//    delay_ms(100);                          /* 延时100ms再初始化看门狗,LED0的变化"可见" */
//    iwdg_init(IWDG_PRESCALER_64, 625);      /* 预分频数为64,重载值为625,溢出时间约为1s */
//    LED0(0);                                /* 点亮LED0(红灯) */

//    while (1)
//    {
//        if (key_scan(1) == WKUP_PRES)       /* 如果WK_UP按下,则喂狗 */
//        {
//            iwdg_feed();                    /* 喂狗 */
//        }

//        delay_ms(10);
//    }
//}

/* 窗口看门狗 */
int main(void)
{
	HAL_Init();                             /* 初始化HAL库 */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
	delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
	led_init();                             /* 初始化LED */
    LED0(0);                                /* 点亮LED0 红 */
    delay_ms(300);                          /* 延时300ms再初始化看门狗，LED0变化可见 */
    wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8);/* 计数器值为7f，窗口寄存器为5f，分频数为8 */
	
	while (1)
	{
        LED0(1);/* 关闭红灯 */
	}
}
