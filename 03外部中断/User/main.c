#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/EXTI/exti.h"


int main(void)
{
	HAL_Init();                             /* ��ʼ�� HAL �� */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
	delay_init(72);                         /* ��ʱ��ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ�� */
	led_init();                             /* ��ʼ�� LED */
    beep_init();                            /* ��ʼ�� ������ */
    extix_init();                             /* ��ʼ�� ���� */
    LED0(0);                                /* ����LED0 �� */
	
	while (1)
	{
        printf("OK\r\n");
        delay_ms(1000);
	}
}
