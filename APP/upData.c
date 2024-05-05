/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	upData.c
* filepath:	f:\draven\中控板\中控app版本\app
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/08/11
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "bsp.h"
#include "appValue.h"
#include "upData.h"
#include "modbusSlaver.h"

void upData_CheckFrame(uint8_t *frame, uint8_t len)
{
	const uint8_t upFrame[8] = { 0xFF, MY_SELF_ADDR, 0x50, 0xA5, 0x5A, 0x38, 0x26, 0xFE };	/* @2017/08/11 14:57:21 0~F7 */
	uint8_t i;
	if (len != 8)
	{
		return;
	}
	for (i = 0; i < 8; i++)
	{
		if (frame[i] != upFrame[i])
		{
			break;
		}
	}
	if (i >= 8)	/* @2017/08/11 14:55:47 执行升级命令 */
	{
		uint8_t txValue = 0xFF;
		mbs_sendData(&txValue, 1);		/* @2017/08/11 15:00:08 发送响应 */
		_run(BOOT);							/* @2017/08/11 15:00:24 跳转到引导程序 */
	}
}





/*
*********************************************************************
* -upData.c	<File end.>
* -f:\draven\中控板\中控app版本\app
*********************************************************************
*/

