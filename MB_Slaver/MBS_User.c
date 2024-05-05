/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_User.c
* filepath:	f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/05/08
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "modbusSlaver.h"
#include "appValue.h"
#include "bsp_Manchester.h"

extern uint8_t coilState[USER_COIL_NUM];
extern uint16_t holdRegValue[USER_HOLDREG_NUM];
//extern uint8_t	DiscreteInput[USER_DISINPUT_NUM];
//extern uint16_t InputRegister[USER_INPUTREG_NUM];

/*
*****************************************************
* Method:       MBS_UserValueMapping
* Description:	用户数据映射，以及变量约束设置
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_UserValueMapping(void)
{
	uint16_t	i;

	/***************************************************************/
	//mbsCoil._startAddr = 10000;
	//mbsCoil._endAddr = 10100;

	//for (i = 0; i < 100; i++)
	//{
	//	MBS_MappingCoilInit(&mbsCoilValue[i], 10000 + i, &coilState[i]);
	//}

	/***************************************************************/
	//mbsHoldReg._startAddr = 50000;
	//mbsHoldReg._endAddr = 50050;

	//for (i = 0; i < 50; i++)
	//{
	//	MBS_MappingHoldRegInit(&mbsHoldRegValue[i], 50000 + i, &holdRegValue[i]);
	//}
	/***************************************************************/
	//mbsDiscreteInput._startAddr = 30000;
	//mbsDiscreteInput._endAddr = 30020;

	//for ( i = 0; i < 20; i++)
	//{
	//	MBS_MappingsDiscreteInputInit(&mbsDiscreteInputValue[i], 30000 + i, &DiscreteInput[i]);
	//}
	/***************************************************************/
	//mbsInputRegister._startAddr = 40000;
	//mbsInputRegister._endAddr = 40013;

	//for (i = 0; i < 13; i++)
	//{
	//	MBS_MappingsInputRegisterInit(&mbsInputRegisterValue[i], 40000 + i, &InputRegister[i]);
	//}

	/***************************************************************/
	mbsCoil._startAddr = 10000;		/* 起始地址 */
	mbsCoil._endAddr = 10003;		/* 结束地址 */

	for (i = 0; i < 4; i++)
	{
		MBS_MappingCoilInit(&mbsCoilValue[i], i + 10000, &coilState[i]);
	}

	/***************************************************************/
	mbsHoldReg._startAddr = 50000;
	mbsHoldReg._endAddr = 59001;

	for (i = 0; i < 3; i++)
	{
		MBS_MappingHoldRegInit(&mbsHoldRegValue[i], 50000 + i, &holdRegValue[i]);
	}

	for (i = 0; i < 17; i++)
	{
		MBS_MappingHoldRegInit(&mbsHoldRegValue[i + 3], 50100 + i, &holdRegValue[i + 3]);
	}

	for ( i = 0; i < 2; i++)
	{
		MBS_MappingHoldRegInit(&mbsHoldRegValue[i + 20], 59000 + i, &holdRegValue[i + 20]);
	}

	for (i = 0; i < 4; i++)
	{
		MBS_MappingHoldRegInit(&mbsHoldRegValue[i+22], 50200 + i, &holdRegValue[i+22]);
	}
	for (i = 0; i < 2; i++)
	{
		MBS_MappingHoldRegInit(&mbsHoldRegValue[i + 26], 50300 + i, &holdRegValue[i + 26]);
	}
}





/*
*********************************************************************
* -MBS_User.c	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/





