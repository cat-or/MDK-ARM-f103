#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"

int main(void)
{
    uint8_t key;
    
	HAL_Init();                             /* ��ʼ�� HAL �� */
	sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
	delay_init(72);                         /* ��ʱ��ʼ�� */
	led_init();                             /* ��ʼ�� LED */
    beep_init();                            /* ��ʼ�� ������ */
    key_init();                             /* ��ʼ�� ���� */
    LED0(0);                                /* ����LED0 */
	
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
