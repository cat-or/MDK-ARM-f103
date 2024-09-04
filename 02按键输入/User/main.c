#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"

int main(void)
{
    uint8_t key;
    
	HAL_Init();                             /* 初始化 HAL 库 */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
	delay_init(72);                         /* 延时初始化 */
	led_init();                             /* 初始化 LED */
    beep_init();                            /* 初始化 蜂鸣器 */
    key_init();                             /* 初始化 按键 */
    LED0(0);                                /* 点亮LED0 */
	
	while (1)
	{
        key = key_scan(0);
        
        if (key)
        {
            switch (key)
            {
                case WKUP_PRES:
                    BEEP_TOGGLE();
                    break;
                
                case KEY2_PRES:
                    LED0_TOGGLE();
                    break;
                
                case KEY1_PRES:
                    LED1_TOGGLE();
                    break;
                
                case KEY0_PRES:
                    LED0_TOGGLE();
                    LED1_TOGGLE();
                    break;
                
            }
        }
        else
        {
            delay_ms(10);
        }
	}
}
