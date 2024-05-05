/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_stEEPROM.h
* filepath:	f:\draven\·¿Ì¬µÆ\·¿Ì¬µÆapp°æ±¾\bsp 
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/08/12
* <version> V-0.0.1   
* <desc>	-build this moudle  
*********************************************************************
*/
#ifndef _BSP_STEEPROM_H
#define _BSP_STEEPROM_H

#include "stm8s.h"

uint8_t bsp_eepromReadOneByte(uint16_t addr);
uint8_t bsp_eepromReadBuff(uint16_t sAddr, uint16_t rNum, uint8_t *buff);

uint8_t bsp_eepromWriteOneByte(uint16_t addr, uint8_t value);
uint8_t bsp_eepromWriteBuff(uint16_t sAddr, uint16_t wNum, uint8_t *buff);

void eeprom_sevice(void);

#endif
/* 
*********************************************************************
* -bsp_stEEPROM.h	<File end.>
* -f:\draven\·¿Ì¬µÆ\·¿Ì¬µÆapp°æ±¾\bsp
*********************************************************************
*/

