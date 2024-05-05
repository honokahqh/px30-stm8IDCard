/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_stEEPROM.c
* filepath:	f:\draven\房态灯\房态灯app版本\bsp
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/08/12
* <version> V-0.0.1
* <desc>	-build this moudle	S003 640 Byte or 10 Page
*********************************************************************
*/

#include "stm8s.h"
#include "modbusSlaver.h"
#include "appValue.h"

/* @2017/08/12 11:21:57 写入或读出地址基于EEPROM的偏移地址 */

/*
*****************************************************
* Method:       bsp_eepromReadOneByte
* Description:	读一字节
* Author:       @Draven
* Date:  		2017/08/12
* Returns:      uint8_t
* Parameter:   	uint16_t addr
* History:
*****************************************************
*/
uint8_t bsp_eepromReadOneByte(uint16_t addr)
{
	uint8_t *p;
	p = (uint8_t *)0x4000 + addr;
	return *p;
}

/*
*****************************************************
* Method:       bsp_eepromWriteOneByte
* Description:	写一字节
* Author:       @Draven
* Date:  		2017/08/12
* Returns:      uint8_t
* Parameter:   	uint16_t addr
* Parameter:   	uint8_t value
* History:
*****************************************************
*/
uint8_t bsp_eepromWriteOneByte(uint16_t addr, uint8_t value)
{
	uint8_t *p;
	p = (uint8_t *)0x4000 + addr;
	do{
		FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
		FLASH->DUKR = FLASH_RASS_KEY1;
	} while (!(FLASH->IAPSR & 0x08));
	*p = value;
	while (!(FLASH->IAPSR & 0x04));
	FLASH->IAPSR &= 0xF7;
	return 1;
}

/*
*****************************************************
* Method:       bsp_eepromReadBuff
* Description:	读多字节
* Author:       @Draven
* Date:  		2017/08/12
* Returns:      uint8_t
* Parameter:   	uint16_t sAddr
* Parameter:   	uint16_t rNum
* Parameter:   	uint8_t * buff
* History:
*****************************************************
*/
uint8_t bsp_eepromReadBuff(uint16_t sAddr, uint16_t rNum, uint8_t *buff)
{
	uint8_t *p;
	p = (uint8_t *)0x4000 + sAddr;
	for (uint16_t i = 0; i < rNum; i++)
	{
		*buff++ = *p++;
	}
	return 1;
}

/*
*****************************************************
* Method:       bsp_eepromWriteBuff
* Description:	写多字节
* Author:       @Draven
* Date:  		2017/08/12
* Returns:      uint8_t
* Parameter:   	uint16_t sAddr
* Parameter:   	uint16_t wNum
* Parameter:   	uint8_t * buff
* History:
*****************************************************
*/
uint8_t bsp_eepromWriteBuff(uint16_t sAddr, uint16_t wNum, uint8_t *buff)
{
	uint8_t *p;
	p = (uint8_t *)0x4000 + sAddr;
	do{
		FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
		FLASH->DUKR = FLASH_RASS_KEY1;
	} while (!(FLASH->IAPSR & 0x08));
	for (uint16_t i = 0; i < wNum; i++)
	{
		*p++ = *buff++;
		while (!(FLASH->IAPSR & 0x04));
	}
	FLASH->IAPSR &= 0xF7;
	return 1;
}

/**
* @brief Eeprom EEC Interrupt routine.
* @param  None
* @retval None
*/
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
	/* In order to detect unexpected events during development,
	it is recommended to set a breakpoint on the following instruction.
	*/
}

void eeprom_sevice(void)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		if (coilState[i] != coilStateLast[i])
		{
			coilStateLast[i] = coilState[i];
			bsp_eepromWriteOneByte(i + 1, coilState[i]);		/* @2017/08/15 14:20:03 总开关和模式 */
		}
	}
	/***************************************************************/
	/* @2017/08/15 14:20:44 延时时间，模式，索引 */
	for (uint8_t i = 0; i < 3; i++)
	{
		if (holdRegValue[i] != holdRegValueLast[i])
		{
			holdRegValueLast[i] = holdRegValue[i];
			bsp_eepromWriteBuff(20 + i * 2, 2, (uint8_t*)&holdRegValue[i]);
		}
	}/* @2017/08/15 14:24:10 固定颜色变化太频繁 不写入 */
	/***************************************************************/
	/* @2017/08/15 14:24:55 色表 */
	for (uint8_t i = 0; i < 16; i++)
	{
		if (holdRegValue[i + HREG_TABLE_COLOR1] != holdRegValueLast[i + HREG_TABLE_COLOR1])
		{
			holdRegValueLast[i + HREG_TABLE_COLOR1] = holdRegValue[i + HREG_TABLE_COLOR1];
			bsp_eepromWriteBuff(28 + i * 2, 2, (uint8_t *)&holdRegValue[i + HREG_TABLE_COLOR1]);
		}
	}/* @2017/08/15 14:27:10 灯带闪烁颜色表 */
	/***************************************************************/
	/* @2017/08/15 14:27:32 本机地址 */
	if (holdRegValue[HREG_MY_ADDR] != holdRegValueLast[HREG_MY_ADDR])
	{
		holdRegValueLast[HREG_MY_ADDR] = holdRegValue[HREG_MY_ADDR];
		bsp_eepromWriteBuff(80, 2, (uint8_t*)&holdRegValue[HREG_MY_ADDR]);
	}
	/* @2017/08/15 14:31:48 固件版本不变化 */
	/***************************************************************/
	/* @2018/07/03 16:25:32 rfid卡号 */
	for (uint8_t i = 0; i < 4; i++)
	{
		if (holdRegValue[i + HREG_RFID_ID1] != holdRegValueLast[i + HREG_RFID_ID1])
		{
			holdRegValueLast[i + HREG_RFID_ID1] = holdRegValue[i + HREG_RFID_ID1];
			bsp_eepromWriteBuff(60 + i * 2, 2, (uint8_t *)&holdRegValue[i + HREG_RFID_ID1]);
		}
	}
	/***************************************************************/
	///* @2018/07/03 16:25:32 蜂鸣器 */
	//for (uint8_t i = 0; i < 2; i++)
	//{
	//	if (holdRegValue[i + HREG_BELL_NUM] != holdRegValueLast[i + HREG_BELL_NUM])
	//	{
	//		holdRegValueLast[i + HREG_BELL_NUM] = holdRegValue[i + HREG_BELL_NUM];
	//		bsp_eepromWriteBuff(70 + i * 2, 2, (uint8_t *)&holdRegValue[i + HREG_BELL_NUM]);
	//	}
	//}
}

/*
*********************************************************************
* -bsp_stEEPROM.c	<File end.>
* -f:\draven\房态灯\房态灯app版本\bsp
*********************************************************************
*/

