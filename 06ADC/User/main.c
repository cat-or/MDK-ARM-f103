#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"


//int main(void)
//{
//    uint16_t adcx;
//    float temp;

//    HAL_Init();                             /* 初始化HAL库 */
//    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
//    delay_init(72);                         /* 延时初始化 */
//    usart_init(115200);                     /* 串口初始化为115200 */
//    led_init();                             /* 初始化LED */
//    lcd_init();                             /* 初始化LCD */
//    adc_init();                             /* 初始化ADC */

//    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
//    lcd_show_string(30, 70, 200, 16, 16, "ADC TEST", RED);
//    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
//    lcd_show_string(30, 110, 200, 16, 16, "ADC1_CH1_VAL:", BLUE);
//    lcd_show_string(30, 130, 200, 16, 16, "ADC1_CH1_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

//    while (1)
//    {
//        adcx = adc_get_result_average(ADC_ADCX_CHY, 10); /* 获取通道5的转换值，10次取平均 */
//        lcd_show_xnum(134, 110, adcx, 5, 16, 0, BLUE);   /* 显示ADCC采样后的原始值 */
// 
//        temp = (float)adcx * (3.3 / 4096);               /* 获取计算后的带小数的实际电压值，比如3.1111 */
//        adcx = temp;                                     /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
//        lcd_show_xnum(134, 130, adcx, 1, 16, 0, BLUE);   /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */

//        temp -= adcx;                                    /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
//        temp *= 1000;                                    /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
//        lcd_show_xnum(150, 130, temp, 3, 16, 0X80, BLUE);/* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */

//        LED0_TOGGLE();
//        delay_ms(100);
//    }
//}



////单通道ADC采集DMA读取
//#define ADC_DMA_BUF_SIZE        100         /* ADC DMA采集 BUF大小 */
//uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

//extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */

//int main(void)
//{
//    uint16_t i;
//    uint16_t adcx;
//    uint32_t sum;
//    float temp;

//    HAL_Init();                             /* 初始化HAL库 */
//    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
//    delay_init(72);                         /* 延时初始化 */
//    usart_init(115200);                     /* 串口初始化为115200 */
//    led_init();                             /* 初始化LED */
//    lcd_init();                             /* 初始化LCD */

//    adc_dma_init((uint32_t)&g_adc_dma_buf); /* 初始化ADC DMA采集 */

//    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
//    lcd_show_string(30,  70, 200, 16, 16, "ADC DMA TEST", RED);
//    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
//    lcd_show_string(30, 110, 200, 16, 16, "ADC1_CH1_VAL:", BLUE);
//    lcd_show_string(30, 130, 200, 16, 16, "ADC1_CH1_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

//    adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA采集 */

//    while (1)
//    {
//        if (g_adc_dma_sta == 1)
//        {
//            /* 计算DMA 采集到的ADC数据的平均值 */
//            sum = 0;

//            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)   /* 累加 */
//            {
//                sum += g_adc_dma_buf[i];
//            }

//            adcx = sum / ADC_DMA_BUF_SIZE;           /* 取平均值 */

//            /* 显示结果 */
//            lcd_show_xnum(134, 110, adcx, 4, 16, 0, BLUE);      /* 显示ADCC采样后的原始值 */

//            temp = (float)adcx * (3.3 / 4096);                  /* 获取计算后的带小数的实际电压值，比如3.1111 */
//            adcx = temp;                                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
//            lcd_show_xnum(134, 130, adcx, 1, 16, 0, BLUE);      /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */

//            temp -= adcx;                                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
//            temp *= 1000;                                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
//            lcd_show_xnum(150, 130, temp, 3, 16, 0X80, BLUE);   /* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */

//            g_adc_dma_sta = 0;                                  /* 清除DMA采集完成状态标志 */
//            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* 启动下一次ADC DMA采集 */
//        }

//        LED0_TOGGLE();
//        delay_ms(100);
//    }
//}


#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"


#define ADC_DMA_BUF_SIZE        50 * 6      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */

int main(void)
{
    uint16_t i,j;
    uint16_t adcx;
    uint32_t sum;
    float temp;

    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟, 72Mhz */
    delay_init(72);                             /* 延时初始化 */
    usart_init(115200);                         /* 串口初始化为115200 */
    led_init();                                 /* 初始化LED */
    lcd_init();                                 /* 初始化LCD */

    adc_nch_dma_init((uint32_t)&g_adc_dma_buf); /* 初始化ADC DMA采集 */

    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "ADC 6CH DMA TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    lcd_show_string(30, 110, 200, 12, 12, "ADC1_CH0_VAL:", BLUE);
    lcd_show_string(30, 122, 200, 12, 12, "ADC1_CH0_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */
    
    lcd_show_string(30, 140, 200, 12, 12, "ADC1_CH1_VAL:", BLUE);
    lcd_show_string(30, 152, 200, 12, 12, "ADC1_CH1_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    lcd_show_string(30, 170, 200, 12, 12, "ADC1_CH2_VAL:", BLUE);
    lcd_show_string(30, 182, 200, 12, 12, "ADC1_CH2_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    lcd_show_string(30, 200, 200, 12, 12, "ADC1_CH3_VAL:", BLUE);
    lcd_show_string(30, 212, 200, 12, 12, "ADC1_CH3_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    lcd_show_string(30, 230, 200, 12, 12, "ADC1_CH4_VAL:", BLUE);
    lcd_show_string(30, 242, 200, 12, 12, "ADC1_CH4_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    lcd_show_string(30, 260, 200, 12, 12, "ADC1_CH5_VAL:", BLUE);
    lcd_show_string(30, 272, 200, 12, 12, "ADC1_CH5_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA采集 */

    while (1)
    {
        if (g_adc_dma_sta == 1)
        {
            /* 循环显示通道0~通道5的结果 */
            for(j = 0; j < 6; j++)  /* 遍历6个通道 */
            {
                sum = 0; /* 清零 */
                for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++)  /* 每个通道采集了10次数据,进行10次累加 */
                {
                    sum += g_adc_dma_buf[(6 * i) + j];      /* 相同通道的转换数据累加 */
                }
                adcx = sum / (ADC_DMA_BUF_SIZE / 6);        /* 取平均值 */
                
                /* 显示结果 */
                lcd_show_xnum(108, 110 + (j * 30), adcx, 4, 12, 0, BLUE);   /* 显示ADCC采样后的原始值 */

                temp = (float)adcx * (3.3 / 4096);  /* 获取计算后的带小数的实际电压值，比如3.1111 */
                adcx = temp;                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
                lcd_show_xnum(108, 122 + (j * 30), adcx, 1, 12, 0, BLUE);   /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */

                temp -= adcx;                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
                temp *= 1000;                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
                lcd_show_xnum(120, 122 + (j * 30), temp, 3, 12, 0X80, BLUE);/* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */
            }
 
            g_adc_dma_sta = 0;                      /* 清除DMA采集完成状态标志 */
            adc_dma_enable(ADC_DMA_BUF_SIZE);       /* 启动下一次ADC DMA采集 */
        }

        LED0_TOGGLE();
        delay_ms(100);
    }
}



