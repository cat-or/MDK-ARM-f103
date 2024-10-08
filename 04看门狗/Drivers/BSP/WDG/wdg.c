#include "./BSP/WDG/wdg.h"
#include "./BSP/LED/led.h"


IWDG_HandleTypeDef g_iwdg_handle;    /* 独立看门狗句柄 */

/**
 * @brief       初始化独立看门狗 
 * @param       prer: IWDG_PRESCALER_4~IWDG_PRESCALER_256,对应4~256分频
 *   @arg       分频因子 = 4 * 2^prer. 但最大值只能是256!
 * @param       rlr: 自动重装载值,0~0XFFF. 
 * @note        时间计算(大概):Tout=((4 * 2^prer) * rlr) / 40 (ms). 
 * @retval      无
 */
void iwdg_init(uint8_t prer, uint16_t rlr)
{
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = prer; /* 设置IWDG分频系数 */
    g_iwdg_handle.Init.Reload = rlr;    /* 重装载值 */
    HAL_IWDG_Init(&g_iwdg_handle);      /* 初始化IWDG并启动 */
}

/**
 * @brief       喂独立看门狗
 * @param       无
 * @retval      无
 */
void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);   /* 重装载计数器 */
}

/************************窗口看门狗代码********************************/

WWDG_HandleTypeDef g_wwdg_handle;   /* 窗口门狗句柄 */

/**
 * @brief       初始化窗口看门狗
 * @param       tr: T[6:0],计数器值
 * @param       tw: W[6:0],窗口值
 * @param       fprer:分频系数（WDGTB）,范围:WWDG_PRESCALER_1~WWDG_PRESCALER_8,表示2^WDGTB分频
 *              Fwwdg=PCLK1/(4096*2^fprer). 一般PCLK1=36Mhz
                最大-最小超时时间参考 RM0008或者《STM32F10xxx参考手册》P321
 * @retval      无
 */
void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer)
{
    g_wwdg_handle.Instance = WWDG;
    g_wwdg_handle.Init.Prescaler = fprer;           /* 预分频系数 */
    g_wwdg_handle.Init.Window = wr;                 /* 设置窗口值 */
    g_wwdg_handle.Init.Counter = tr;                /* 设置计数器值 */
    g_wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE;   /* 使能窗口门狗提前唤醒中断 */
    HAL_WWDG_Init(&g_wwdg_handle);                  /* 初始化WWDG */
}

/**
 * @brief       WWDG MSP回调
 * @param       WWDG句柄
 * @note        此函数会被HAL_WWDG_Init()调用
 * @retval      无
 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();/* 使能窗口看门狗时钟 */
    
    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);/* 抢占优先级2，子优先级3 */
    HAL_NVIC_EnableIRQ(WWDG_IRQn);/* 使能窗口看门狗中断 */
}

/**
 * @brief       窗口看门狗中断服务程序
 * @param       无
 * @retval      无
 */
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handle);/* 调用WWDG共用中断处理函数 */
}

/**
 * @brief       窗口看门狗喂狗提醒中断服务回调函数
 * @param       wwdg句柄
 * @note        此函数会被HAL_WWDG_IRQHandler()调用
 * @retval      无
 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    HAL_WWDG_Refresh(&g_wwdg_handle);/* 更新窗口看门狗值,当禁掉此句后,窗口看门狗将产生复位 */
    LED1_TOGGLE();/* LED1闪烁 */
}
