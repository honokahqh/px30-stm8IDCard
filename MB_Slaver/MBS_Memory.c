/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Memory.c
* filepath:	f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/05/08
* <version> V-0.0.1
* <desc>	-build this moudle	直接写数据到内存
*********************************************************************
*/

#include "modbusSlaver.h"

#if MBS_FUNCTION_01_ENABLE
/*
*****************************************************
* Method:       MBS_MesReadCoilState
* Description:	读取指定地址线圈的状态
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      uint8_t		返回 0,1 错误返回 线圈总数
* Parameter:   	uint16_t regNum	线圈地址
* History:
*****************************************************
*/
uint8_t MBS_MemReadCoilState(uint16_t _coilAddr)
{
	uint16_t i;
	for (i = 0; i < mbsCoil._num; i++)
	{
		if (mbsCoilValue[i]._coilAddr == _coilAddr)
		{
			if (*(mbsCoilValue[i]._pData))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return i;
}
#endif

#if MBS_FUNCTION_02_ENABLE
/*
*****************************************************
* Method:       MBS_MemReadDiscreteInputState
* Description:	读取离散输入位变量
* Author:       @Draven 
* Date:  		2017/05/11
* Returns:      uint8_t
* Parameter:   	uint16_t _Addr
* History:
*****************************************************
*/
uint8_t MBS_MemReadDiscreteInputState(uint16_t _Addr)
{
	uint16_t i;
	for (i = 0; i < mbsDiscreteInput._num; i++)
	{
		if (mbsDiscreteInputValue[i]._coilAddr == _Addr)
		{
			if (*(mbsDiscreteInputValue[i]._pData))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return i;
}
#endif

#if MBS_FUNCTION_05_ENABLE
/*
*****************************************************
* Method:       MBS_MemReadCoilState
* Description:	写指定地址的线圈状态
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      uint8_t				成功返回1 失败返回寄存器数量
* Parameter:   	uint16_t regNum
* Parameter:   	uint16_t nweState
* History:
*****************************************************
*/
uint8_t MBS_MemWriteCoilState(uint16_t _coilAddr, uint16_t nweState)
{
	uint16_t i;
	if (_coilAddr != 10000 && !coilState[COIL_SWITCH])		/* 总开关没有开 并且不是开总开关动作，数据不写入 */
	{
		return 1;
	}
	for (i = 0; i < mbsCoil._num; i++)
	{
		if (mbsCoilValue[i]._coilAddr == _coilAddr)
		{
			if (nweState)
			{
				*(mbsCoilValue[i]._pData) = 1;
			}
			else
			{
				*(mbsCoilValue[i]._pData) = 0;
			}
			return 1;
		}
	}
	return i;
}
#endif

#if MBS_FUNCTION_0F_ENABLE
/*
*****************************************************
* Method:       MBS_MemWriteCoilsState
* Description:	写多个线圈
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      uint16_t	成功返回 1.失败返回 线圈数目
* Parameter:   	uint16_t regNum
* Parameter:   	uint16_t writeNum
* Parameter:   	uint8_t byteNum
* Parameter:   	uint8_t * writeData
* History:
*****************************************************
*/
uint16_t MBS_MemWriteCoilsState(uint16_t regNum, uint16_t writeNum, uint8_t byteNum, uint8_t *writeData)
{
	uint16_t i, j;
	uint8_t k = 0;
	uint8_t	index = 0;
	if (!coilState[COIL_SWITCH])		/* 总开关没有开 并且不是开总开关动作，数据不写入 只能单个线圈写入才能打开总开关*/
	{
		return 1;
	}
	for (i = 0; i < mbsCoil._num; i++)	//查找符合地址
	{
		if (mbsCoilValue[i]._coilAddr == regNum)
		{
			break;
		}
	}
	if (i >= mbsCoil._num)
	{
		return i;		/*读取失败，地址错误*/
	}

	for (j = 0; j < writeNum; j++)		//都 OK 开始写入数据
	{
		if (writeData[index] & (0x01 << k))
		{
			*(mbsCoilValue[i + j]._pData) = 0x01;
		}
		else
		{
			*(mbsCoilValue[i + j]._pData) = 0x00;
		}
		k++;
		if (k == 8)
		{
			k = 0;
			index++;
		}

	}

	return 1;					/* 读取成功 */
}
#endif

#if MBS_FUNCTION_03_ENABLE
/*
*****************************************************
* Method:       MBS_MemReadHoldRegValue
* Description:	读指定保持寄存器
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      uint8_t
* Parameter:   	uint16_t _regAddr		地址
* Parameter:   	uint8_t * _regValue		待写入数据
* History:
*****************************************************
*/
uint8_t MBS_MemReadHoldRegValue(uint16_t _regAddr, uint8_t *_regValue)
{
	uint16_t i;

	for (i = 0; i < mbsHoldReg._num; i++)
	{
		if (mbsHoldRegValue[i]._regAddr == _regAddr)
		{
			_regValue[0] = *(mbsHoldRegValue[i]._pData) >> 8;
			_regValue[1] = *(mbsHoldRegValue[i]._pData);
			return 1;					/* 读取成功 */
		}
	}
	return i;
}
#endif

#if MBS_FUNCTION_04_ENABLE

/*
*****************************************************
* Method:       MBS_MemReadInputRegisterValue
* Description:	读输入寄存器
* Author:       @Draven 
* Date:  		2017/05/11
* Returns:      uint8_t
* Parameter:   	uint16_t _regAddr
* Parameter:   	uint8_t * _regValue
* History:
*****************************************************
*/
uint8_t MBS_MemReadInputRegisterValue(uint16_t _regAddr, uint8_t *_regValue)
{
	uint16_t i;

	for (i = 0; i < mbsInputRegister._num; i++)
	{
		if (mbsInputRegisterValue[i]._regAddr == _regAddr)
		{
			_regValue[0] = *(mbsInputRegisterValue[i]._pData) >> 8;
			_regValue[1] = *(mbsInputRegisterValue[i]._pData);
			return 1;					/* 读取成功 */

		}
	}
	return i;
}
#endif

#if MBS_FUNCTION_06_ENABLE
/*
*****************************************************
* Method:       MBS_MemWriteHoldRegValue
* Description:	写保持寄存器数据
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      uint8_t
* Parameter:   	uint16_t reg_addr
* Parameter:   	uint16_t reg_value
* History:
*****************************************************
*/
uint8_t MBS_MemWriteHoldRegValue(uint16_t _regAddr, uint16_t _regValue)
{
	uint16_t i;
	if (!coilState[COIL_SWITCH])		/* 总开关关闭 无法写入 ，但不会报错 */
	{
		return 1;
	}
	for (i = 0; i < mbsHoldReg._num; i++)
	{
		if (mbsHoldRegValue[i]._regAddr == _regAddr)
		{
			*(mbsHoldRegValue[i]._pData) = _regValue;
			return 1;
		}
	}

	return i;
}
#endif

/*
*********************************************************************
* -MBS_Memory.c	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/



