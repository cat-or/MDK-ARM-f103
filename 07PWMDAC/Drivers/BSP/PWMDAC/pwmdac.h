
#ifndef __PWMDAC_H
#define __PWMDAC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* PWM DAC 引脚 和 定时器 定义 */

/* PWMDAC 默认是使用 PB6, 对应的定时器为 TIM4_CH1, 如果你要修改成其他IO输出, 则相应
 * 的定时器及通道也要进行修改. 请根据实际情况进行修改.
 */
#define PWMDAC_GPIO_PORT                    GPIOB
#define PWMDAC_GPIO_PIN                     GPIO_PIN_6
#define PWMDAC_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) /* PB口时钟使能 */

#define PWMDAC_TIMX                         TIM4
#define PWMDAC_TIMX_CHY                     TIM_CHANNEL_1                               /* 通道Y,  1<= Y <=4 */
#define PWMDAC_TIMX_CCRX                    PWMDAC_TIMX->CCR1                           /* 通道Y的输出比较寄存器 */
#define PWMDAC_TIMX_CLK_ENABLE()            do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)  /* TIM1 时钟使能 */

/******************************************************************************************/

void pwmdac_init(uint16_t arr, uint16_t psc);   /* PWM DAC初始化 */
void pwmdac_set_voltage(uint16_t vol);          /* PWM DAC设置输出电压 */

#endif

















