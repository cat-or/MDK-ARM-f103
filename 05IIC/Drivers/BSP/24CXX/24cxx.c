#include "./BSP/IIC/myiic.h"
#include "./BSP/24CXX/24cxx.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       初始化IIC接口
 * @param       无
 * @retval      无
 */
void at24cxx_init(void)
{
    iic_init();
}

/**
 * @brief       在AT24CXX指定地址读出一个数据
 * @param       readaddr: 开始读数的地址
 * @retval      读到的数据
 */
uint8_t at24cxx_read_one_byte(uint16_t addr)
{
    uint8_t temp = 0;
    iic_start();                /* 发送起始信号 */
   
    iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr % 256);  /* 发送低位地址 */
    iic_wait_ack();             /* 等待ACK, 此时地址发送完成了 */
    
    iic_start();                /* 重新发送起始信号 */ 
    iic_send_byte(0XA1);        /* 进入接收模式, IIC规定最低位是1, 表示读取 */
    iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
    temp = iic_read_byte(0);    /* 接收一个字节数据 */
    iic_stop();                 /* 产生一个停止条件 */
    return temp;
}

/**
 * @brief       在AT24CXX指定地址写入一个数据
 * @param       addr: 写入数据的目的地址
 * @param       data: 要写入的数据
 * @retval      无
 */
void at24cxx_write_one_byte(uint16_t addr, uint8_t data)
{
    iic_start();                /* 发送起始信号 */
    
    if (EE_TYPE > AT24C16)      /* 24C16以上的型号, 分2个字节发送地址 */
    {
        iic_send_byte(0XA0);    /* 发送写命令, IIC规定最低位是0, 表示写入 */
        iic_wait_ack();         /* 每次发送完一个字节,都要等待ACK */
        iic_send_byte(addr >> 8);/* 发送高字节地址 */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    }
    
    iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr % 256);  /* 发送低位地址 */
    iic_wait_ack();             /* 等待ACK, 此时地址发送完成了 */
    
    /* 因为写数据的时候,不需要进入接收模式了,所以这里不用重新发送起始信号了 */
    iic_send_byte(data);        /* 发送1字节 */
    iic_wait_ack();             /* 等待ACK */
    iic_stop();                 /* 产生一个停止条件 */
    delay_ms(10);               /* 注意: EEPROM 写入比较慢,必须等到10ms后再写下一个字节 */
}
 
/**
 * @brief       检查AT24CXX是否正常
 *   @note      检测原理: 在器件的末地址写如0X55, 然后再读取, 如果读取值为0X55
 *              则表示检测正常. 否则,则表示检测失败.
 *
 * @param       无
 * @retval      检测结果
 *              0: 检测成功
 *              1: 检测失败
 */
uint8_t at24cxx_check(void)
{
    uint8_t temp;
    uint16_t addr = EE_TYPE;
    temp = at24cxx_read_one_byte(addr); /* 避免每次开机都写AT24CXX */

    if (temp == 0X55)   /* 读取数据正常 */
    {
        return 0;
    }
    else    /* 排除第一次初始化的情况 */
    {
        at24cxx_write_one_byte(addr, 0X55); /* 先写入数据 */
        temp = at24cxx_read_one_byte(255);  /* 再读取数据 */

        if (temp == 0X55)return 0;
    }

    return 1;
}

/**
 * @brief       在AT24CXX里面的指定地址开始读出指定个数的数据
 * @param       addr    : 开始读出的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要读出数据的个数
 * @retval      无
 */
void at24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = at24cxx_read_one_byte(addr++);
    }
}

/**
 * @brief       在AT24CXX里面的指定地址开始写入指定个数的数据
 * @param       addr    : 开始写入的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要写入数据的个数
 * @retval      无
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

// 顺序读取 连读
void at24cxx_sequentialread(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
{
    if (datalen == 0)
    {
        return ;
    }
    
    iic_start();
    if (EE_TYPE > AT24C16)      /* 24C16以上的型号, 分2个字节发送地址 */
    {
        iic_send_byte(0XA0);    /* 发送写命令, IIC规定最低位是0, 表示写入 */
        iic_wait_ack();         /* 每次发送完一个字节,都要等待ACK */
        iic_send_byte(addr >> 8);/* 发送高字节地址 */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    }
        
    iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr % 256);  /* 发送低位地址 */
    iic_wait_ack();             /* 等待ACK, 此时地址发送完成了 */
    
    iic_start();                /* 重新发送起始信号 */ 
    iic_send_byte(0XA1);
    iic_wait_ack();
    
    
    while (--datalen)
    {
        *pbuf++ = iic_read_byte(1);
    }
    *pbuf++ = iic_read_byte(0);
    iic_stop();
}

//页写
void at24cxx_pagewrite(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
{
    if (datalen == 0 || addr >= EE_TYPE)
    {
        return;
    }
    
    iic_start();
    if (EE_TYPE > AT24C16)      /* 24C16以上的型号, 分2个字节发送地址 */
    {
        iic_send_byte(0XA0);    /* 发送写命令, IIC规定最低位是0, 表示写入 */
        iic_wait_ack();         /* 每次发送完一个字节,都要等待ACK */
        iic_send_byte(addr >> 8);/* 发送高字节地址 */
    }
    else 
    {
        iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
    }
        
    iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr % 256);  /* 发送低位地址 */
    iic_wait_ack();             /* 等待ACK, 此时地址发送完成了 */
    
    for (uint16_t i = 0; i < datalen; i++)
    {
        iic_send_byte(pbuf[i]);
        iic_wait_ack();
        addr++;
        
        if (addr >= EE_TYPE) // 寄存器满
        {
            break;
        }
        
        if (addr % EE_TYPE_PageSize == 0) // 满页
        {
            iic_start();
            if (EE_TYPE > AT24C16)      /* 24C16以上的型号, 分2个字节发送地址 */
            {
                iic_send_byte(0XA0);    /* 发送写命令, IIC规定最低位是0, 表示写入 */
                iic_wait_ack();         /* 每次发送完一个字节,都要等待ACK */
                iic_send_byte(addr >> 8);/* 发送高字节地址 */
            }
            else 
            {
                iic_send_byte(0XA0 + ((addr >> 8) << 1));   /* 发送器件 0XA0 + 高位a8/a9/a10地址,写数据 */
            }
                
            iic_wait_ack();             /* 每次发送完一个字节,都要等待ACK */
            iic_send_byte(addr % 256);  /* 发送低位地址 */
            iic_wait_ack();             /* 等待ACK, 此时地址发送完成了 */

        }
    }
    iic_stop();
    delay_ms(10);
}

//// ‘页写’多个字节
//void at24cxx_bufwrite(uint16_t addr, uint8_t *pbuf,uint16_t datalen)
//{
//    uint8_t num_of_page = 0, num_of_single = 0, tempaddr = 0, count = 0, temp = 0;
//    // 求余运算，若 addr 是 EE_TYPE_PageSize 的整数倍，结果为 0
//    tempaddr = addr % EE_TYPE_PageSize;
//    // 差 count 个字节，刚好对齐页地址
//    count = EE_TYPE_PageSize - tempaddr;
//    // 需要的整数页数
//    num_of_page = datalen / EE_TYPE_PageSize;
//    // 不满一页的字节数
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

