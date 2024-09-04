
#ifndef __PWMDAC_H
#define __PWMDAC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* PWM DAC ���� �� ��ʱ�� ���� */

/* PWMDAC Ĭ����ʹ�� PB6, ��Ӧ�Ķ�ʱ��Ϊ TIM4_CH1, �����Ҫ�޸ĳ�����IO���, ����Ӧ
 * �Ķ�ʱ����ͨ��ҲҪ�����޸�. �����ʵ����������޸�.
 */
#define PWMDAC_GPIO_PORT                    GPIOB
#define PWMDAC_GPIO_PIN                     GPIO_PIN_6
#define PWMDAC_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PB��ʱ��ʹ�� */

#define PWMDAC_TIMX                         TIM4
#define PWMDAC_TIMX_CHY                     TIM_CHANNEL_1                               /* ͨ��Y,  1<= Y <=4 */
#define PWMDAC_TIMX_CCRX                    PWMDAC_TIMX->CCR1                           /* ͨ��Y������ȽϼĴ��� */
#define PWMDAC_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)  /* TIM1 ʱ��ʹ�� */

/******************************************************************************************/

void pwmdac_init(uint16_t arr, uint16_t psc);   /* PWM DAC��ʼ�� */
void pwmdac_set_voltage(uint16_t vol);          /* PWM DAC���������ѹ */

#endif

















