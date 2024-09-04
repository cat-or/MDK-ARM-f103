#ifndef __CAN_H
#define __CAN_H

#include "./SYSTEM/sys/sys.h"


// ���Ŷ���

#define CAN_RX_GPIO_PORT                GPIOA
#define CAN_RX_GPIO_PIN                 GPIO_PIN_11
#define CAN_RX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define CAN_TX_GPIO_PORT                GPIOA
#define CAN_TX_GPIO_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)


// CAN����RX0�ж�ʹ��, 0 ��ʹ�ܣ�1 ʹ��
#define CAN_RX0_INT_ENABLE      0


// ��������
uint8_t can_receive_msg(uint32_t id, uint8_t *buf);
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len);
uint8_t can_init(uint32_t tsjw, uint32_t tbs2, uint32_t tbs1, uint16_t brp, uint32_t mode);


#endif
