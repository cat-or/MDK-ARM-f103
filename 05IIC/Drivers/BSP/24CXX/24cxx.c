#include "./BSP/IIC/myiic.h"
#include "./BSP/24CXX/24cxx.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       ��ʼ��IIC�ӿ�
 * @param       ��
 * @retval      ��
 */
void at24cxx_init(void)
{
    iic_init();
}

/**
 * @brief       ��AT24CXXָ����ַ����һ������
 * @param       readaddr: ��ʼ�����ĵ�ַ
 * @retval      ����������
 */
uint8_t at24cxx_read_one_byte(uint16_t addr)
{
    uint8_t temp = 0;
    iic_start();                /* ������ʼ�ź� */
   
    iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* �������� 0XA0 + ��λa8/a9/a10��ַ,д���� */
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    iic_start();                /* ���·�����ʼ�ź� */ 
    iic_send_byte(0XA1);        /* �������ģʽ, IIC�涨���λ��1, ��ʾ��ȡ */
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    temp = iic_read_byte(0);    /* ����һ���ֽ����� */
    iic_stop();                 /* ����һ��ֹͣ���� */
    return temp;
}

/**
 * @brief       ��AT24CXXָ����ַд��һ������
 * @param       addr: д�����ݵ�Ŀ�ĵ�ַ
 * @param       data: Ҫд�������
 * @retval      ��
 */
void at24cxx_write_one_byte(uint16_t addr, uint8_t data)
{
    iic_start();                /* ������ʼ�ź� */
    
    if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
    {
        iic_send_byte(0XA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
        iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
        iic_send_byte(addr >> 8);/* ���͸��ֽڵ�ַ */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* �������� 0XA0 + ��λa8/a9/a10��ַ,д���� */
    }
    
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    /* ��Ϊд���ݵ�ʱ��,����Ҫ�������ģʽ��,�������ﲻ�����·�����ʼ�ź��� */
    iic_send_byte(data);        /* ����1�ֽ� */
    iic_wait_ack();             /* �ȴ�ACK */
    iic_stop();                 /* ����һ��ֹͣ���� */
    delay_ms(10);               /* ע��: EEPROM д��Ƚ���,����ȵ�10ms����д��һ���ֽ� */
}
 
/**
 * @brief       ���AT24CXX�Ƿ�����
 *   @note      ���ԭ��: ��������ĩ��ַд��0X55, Ȼ���ٶ�ȡ, �����ȡֵΪ0X55
 *              ���ʾ�������. ����,���ʾ���ʧ��.
 *
 * @param       ��
 * @retval      �����
 *              0: ���ɹ�
 *              1: ���ʧ��
 */
uint8_t at24cxx_check(void)
{
    uint8_t temp;
    uint16_t addr = EE_TYPE;
    temp = at24cxx_read_one_byte(addr); /* ����ÿ�ο�����дAT24CXX */

    if (temp == 0X55)   /* ��ȡ�������� */
    {
        return 0;
    }
    else    /* �ų���һ�γ�ʼ������� */
    {
        at24cxx_write_one_byte(addr, 0X55); /* ��д������ */
        temp = at24cxx_read_one_byte(255);  /* �ٶ�ȡ���� */

        if (temp == 0X55)return 0;
    }

    return 1;
}

/**
 * @brief       ��AT24CXX�����ָ����ַ��ʼ����ָ������������
 * @param       addr    : ��ʼ�����ĵ�ַ ��24c02Ϊ0~255
 * @param       pbuf    : ���������׵�ַ
 * @param       datalen : Ҫ�������ݵĸ���
 * @retval      ��
 */
void at24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = at24cxx_read_one_byte(addr++);
    }
}

/**
 * @brief       ��AT24CXX�����ָ����ַ��ʼд��ָ������������
 * @param       addr    : ��ʼд��ĵ�ַ ��24c02Ϊ0~255
 * @param       pbuf    : ���������׵�ַ
 * @param       datalen : Ҫд�����ݵĸ���
 * @retval      ��
 */
void at24cxx_write(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        at24cxx_write_one_byte(addr, *pbuf);
        addr++;
        pbuf++;
    }
}

// ˳���ȡ ����
void at24cxx_sequentialread(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
{
    if (datalen == 0)
    {
        return ;
    }
    
    iic_start();
    if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
    {
        iic_send_byte(0XA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
        iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
        iic_send_byte(addr >> 8);/* ���͸��ֽڵ�ַ */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* �������� 0XA0 + ��λa8/a9/a10��ַ,д���� */
    }
        
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    iic_start();                /* ���·�����ʼ�ź� */ 
    iic_send_byte(0XA1);
    iic_wait_ack();
    
    
    while (--datalen)
    {
        *pbuf++ = iic_read_byte(1);
    }
    *pbuf++ = iic_read_byte(0);
    iic_stop();
}

//ҳд
void at24cxx_pagewrite(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
{
    if (datalen == 0 || addr >= EE_TYPE)
    {
        return;
    }
    
    iic_start();
    if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
    {
        iic_send_byte(0XA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
        iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
        iic_send_byte(addr >> 8);/* ���͸��ֽڵ�ַ */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* �������� 0XA0 + ��λa8/a9/a10��ַ,д���� */
    }
        
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    for (uint16_t i = 0; i < datalen; i++)
    {
        iic_send_byte(pbuf[i]);
        iic_wait_ack();
        addr++;
        
        if (addr >= EE_TYPE) // �Ĵ�����
        {
            break;
        }
        
        if (addr % EE_TYPE_PageSize == 0) // ��ҳ
        {
            iic_start();
            if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
            {
                iic_send_byte(0XA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
                iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
                iic_send_byte(addr >> 8);/* ���͸��ֽڵ�ַ */
            }
            else 
            {
                iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* �������� 0XA0 + ��λa8/a9/a10��ַ,д���� */
            }
                
            iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
            iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
            iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */

        }
    }
    iic_stop();
    delay_ms(10);
}

//// ��ҳд������ֽ�
//void at24cxx_bufwrite(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
//{
//    uint8_t num_of_page = 0, num_of_single = 0, tempaddr = 0, count = 0, temp = 0;
//    // �������㣬�� addr �� EE_TYPE_PageSize �������������Ϊ 0
//    tempaddr = addr % EE_TYPE_PageSize;
//    // �� count ���ֽڣ��պö���ҳ��ַ
//    count = EE_TYPE_PageSize - tempaddr;
//    // ��Ҫ������ҳ��
//    num_of_page = datalen / EE_TYPE_PageSize;
//    // ����һҳ���ֽ���
//    num_of_single = datalen % EE_TYPE_PageSize;
//    
//    if (tempaddr == 0)
//    {
//        if (num_of_page == 0)
//        {
//            at24cxx_pagewrite(addr, pbuf, num_of_single);
//            
//        }
//        else 
//        {
//            while (num_of_page--)
//            {
//                at24cxx_pagewrite(addr, pbuf, EE_TYPE_PageSize);
//                //I2C_EE_WaitEepromStandbyState();
//                addr += EE_TYPE_PageSize;
//                pbuf += EE_TYPE_PageSize;
//            }
//            if (num_of_single != 0)
//            {
//                at24cxx_pagewrite(addr, pbuf, num_of_single);
//            }
//        }
//    }
//    else
//    {
//        if (num_of_page == 0)
//        {
//            if (num_of_single > count)
//            {
//                temp = num_of_single - count;
//                
//                at24cxx_pagewrite(addr, pbuf, count);
//                addr += count;
//                pbuf += count;
//                
//                at24cxx_pagewrite(addr, pbuf, temp);
//            }
//            else
//            {
//                at24cxx_pagewrite(addr, pbuf, datalen);
//            }
//        }
//        else 
//        {
//            datalen -= count;
//            num_of_page = datalen / EE_TYPE_PageSize;
//            num_of_single = datalen % EE_TYPE_PageSize;
//            
//            if (count != 0)
//            {
//                at24cxx_pagewrite(addr, pbuf, count);
//                
//                addr += count;
//                pbuf += count;
//            }
//            while (num_of_page--)
//            {
//                at24cxx_pagewrite(addr, pbuf, count);
//                addr += EE_TYPE_PageSize;
//                pbuf += EE_TYPE_PageSize;
//            }
//            if (num_of_single != 0)
//            {
//                at24cxx_pagewrite(addr, pbuf, count);
//            }
//        }
//    }
//    
//}

