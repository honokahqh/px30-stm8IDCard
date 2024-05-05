/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp.c
* filepath:	f:\draven\中控板\zk_dravenv100\bsp
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/19
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "stm8s.h"
#include "bsp.h"

void bsp_init(void)
{
	/* Clear High speed internal clock prescaler */
	CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
	/* Set High speed internal clock prescaler */
	CLK->CKDIVR |= (uint8_t)CLK_PRESCALER_HSIDIV1;

	CLK->ICKR |= 0x80;	/* 开启内部低速时钟 看门狗 */

	/*中断优先级设置*/
	bsp_idCardIO_init();
	bsp_watchDog_init();	  
	bsp_clock_init(); // tim4 1ms定时器
}



/*
*********************************************************************
* -bsp.c	<File end.>
* -f:\draven\中控板\zk_dravenv100\bsp
*********************************************************************
*/

