#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/WDG/wdg.h"
#include "./BSP/KEY/key.h"


//int main(void)
//{
//    HAL_Init();                             /* ��ʼ��HAL�� */
//    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
//    delay_init(72);                         /* ��ʱ��ʼ�� */
//    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
//    led_init();                             /* ��ʼ��LED */
//    key_init();                             /* ��ʼ������ */
//    delay_ms(100);                          /* ��ʱ100ms�ٳ�ʼ�����Ź�,LED0�ı仯"�ɼ�" */
//    iwdg_init(IWDG_PRESCALER_64, 625);      /* Ԥ��Ƶ��Ϊ64,����ֵΪ625,���ʱ��ԼΪ1s */
//    LED0(0);                                /* ����LED0(���) */

//    while (1)
//    {
//        if (key_scan(1) == WKUP_PRES)       /* ���WK_UP����,��ι�� */
//        {
//            iwdg_feed();                    /* ι�� */
//        }

//        delay_ms(10);
//    }
//}

/* ���ڿ��Ź� */
int main(void)
{
	HAL_Init();                             /* ��ʼ��HAL�� */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
	delay_init(72);                         /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
	led_init();                             /* ��ʼ��LED */
    LED0(0);                                /* ����LED0 �� */
    delay_ms(300);                          /* ��ʱ300ms�ٳ�ʼ�����Ź���LED0�仯�ɼ� */
    wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8);/* ������ֵΪ7f�����ڼĴ���Ϊ5f����Ƶ��Ϊ8 */
	
	while (1)
	{
        LED0(1);/* �رպ�� */
	}
}
