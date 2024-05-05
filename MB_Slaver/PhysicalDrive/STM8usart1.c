/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	STM8usart1.c
* filepath:	f:\draven\�пذ�\zk_dravenv100\mb_slaver\physicaldrive
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/21
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "stm8s.h"
#include "modbusSlaver.h"
#include "STM8usart1.h"
#include "bsp.h"

uart_state_t uart_state;

void uart_init(void)
{
	/* TXD */
	GPIOD->DDR |= GPIO_PIN_5;		/* ���ģʽ */
	GPIOD->CR1 |= GPIO_PIN_5;		/* ������� */
	GPIOD->CR2 |= GPIO_PIN_5;		/* ����ٶ����Ϊ 10MHZ */
	/* RXD */
	GPIOD->DDR &= ~GPIO_PIN_6;		/* ����ģʽ */
	GPIOD->CR1 &= ~GPIO_PIN_6;		/* �������� */
	GPIOD->CR2 &= ~GPIO_PIN_6;		/* ��ֹ�ⲿ�ж� */
	/***************************************************************/
	CLK->PCKENR1 |= CLK_PCKENR1_UART1;
	UART1->CR1 = 0x00;				/* ��У�� 1λֹͣλ ����ģʽ*/
	UART1->CR2 = 0x00;
	UART1->CR3 = 0x00;
      uint16_t baud;
      baud = 16000000 / 115200;
      UART1->BRR2 = (baud & 0x0F) | ((baud >> 8) & 0xF0);
      UART1->BRR1 = ((baud >> 4) & 0xFF);
	// UART1->BRR2 = 0x02;				/* ������ 9600 */
	// UART1->BRR1 = 0x68;

	UART1->CR2 = 0x2C;				/* ������պͷ��� �����������ж� */
	/***************************************************************/
}

void uart_idle_detect(void)
{	
	if(uart_state.IDLE)
	{
		uart_state.IDLE++;
		if(uart_state.IDLE > UART_IDLE_TIMEOUT)
		{
			uart_state.IDLE = 0;
			uart_state.has_data = 1;
		}
	}
}

void mbs_sendData(uint8_t *_str, uint8_t _strLen)
{
	unsigned char i;
	while ((UART1->SR & 0x80) == 0x00);
	for (i = 0; i < _strLen; i++)
	{
		UART1->DR = _str[i];
		while ((UART1->SR & 0x80) == 0x00);
	}
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
	if (UART1->SR & 0x20)
	{
		if(uart_state.rx_len >= UART_BUF_MAX)
			uart_state.rx_len = 0;
		uart_state.rx_buff[uart_state.rx_len++] = UART1->DR;
		uart_state.IDLE = 1;
	}
}
