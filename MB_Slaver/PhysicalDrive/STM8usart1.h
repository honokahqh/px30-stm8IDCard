/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	STM8usart1.h
* filepath:	f:\draven\�пذ�\zk_dravenv100\mb_slaver\physicaldrive 
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/21
* <version> V-0.0.1   
* <desc>	-build this moudle  
*********************************************************************
*/
#ifndef _STM8USART1_H
#define _STM8USART1_H

#include "stm8s.h"

#define UART_IDLE_TIMEOUT		10
#define UART_BUF_MAX				64

typedef struct
{
	uint8_t IDLE;	  // 串口空闲-0:空闲
	uint8_t has_data; // 串口一帧数据接收完成

	uint8_t rx_buff[64];
	uint8_t rx_len;
} uart_state_t;
extern uart_state_t uart_state;

void uart_init(void);

void uart_idle_detect(void);

void mbs_sendData(uint8_t *_str, uint8_t _strLen);

#endif
/* 
*********************************************************************
* -STM8usart1.h	<File end.>
* -f:\draven\�пذ�\zk_dravenv100\mb_slaver\physicaldrive
*********************************************************************
*/

