/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_dog.c
* filepath:	f:\draven\中控板\zk_dravenv100\bsp
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/25
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "stm8s.h"

/*
*****************************************************
* Method:       bsp_watchDog_init
* Description:	造狗
* Author:       @Draven 
* Date:  		2017/07/25
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void bsp_watchDog_init(void)
{
	IWDG->KR = 0xCC;		        /* 启动 */
	IWDG->KR = 0x55;		        /* 解除写保护 */

	IWDG->PR = 0x05;				/* 预分频 /128 */
	IWDG->RLR = 0xff;				/* 重装载  510ms */

	IWDG->KR = 0x00;		        /* 开启写保护 */
	IWDG->KR = 0xAA;				/* 喂狗 */
}

/*
*****************************************************
* Method:       bsp_dog_reload
* Description:	喂狗
* Author:       @Draven 
* Date:  		2017/07/25
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void bsp_dog_reload(void)
{
	IWDG->KR = 0xAA;
}

/*
*********************************************************************
* -bsp_dog.c	<File end.>
* -f:\draven\中控板\zk_dravenv100\bsp
*********************************************************************
*/

