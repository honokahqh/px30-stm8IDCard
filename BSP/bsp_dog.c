/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_dog.c
* filepath:	f:\draven\�пذ�\zk_dravenv100\bsp
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
* Description:	�칷
* Author:       @Draven 
* Date:  		2017/07/25
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void bsp_watchDog_init(void)
{
	IWDG->KR = 0xCC;		        /* ���� */
	IWDG->KR = 0x55;		        /* ���д���� */

	IWDG->PR = 0x05;				/* Ԥ��Ƶ /128 */
	IWDG->RLR = 0xff;				/* ��װ��  510ms */

	IWDG->KR = 0x00;		        /* ����д���� */
	IWDG->KR = 0xAA;				/* ι�� */
}

/*
*****************************************************
* Method:       bsp_dog_reload
* Description:	ι��
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
* -f:\draven\�пذ�\zk_dravenv100\bsp
*********************************************************************
*/

