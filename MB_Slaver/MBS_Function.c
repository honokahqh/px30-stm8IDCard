/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Function.c
* filepath:	f:\draven\·¿Ì¬µÆ\modbus_slaverproj\draven-stm8-proj\mb-slaver
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/05/08
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "modbusSlaver.h"

#if MBS_FUNCTION_01_ENABLE
/*
*****************************************************
* Method:       MBS_Function01H
* Description:	¶ÁÏßÈ¦×´Ì¬
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function01H(void)
{
	uint16_t coil;
	uint16_t num;
	uint16_t i;
	uint16_t m;
	uint8_t status[MBS_PORT_TXBUFF_SIZE] = { 0 };
	uint8_t temp;

	num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((num<1) || (num>2000))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	coil = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((coil < mbsCoil._startAddr) || ((coil + num -1) > mbsCoil._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}
	m = (num + 7) / 8;
	for (i = 0; i < m; i++)
	{
		status[i] = 0;
	}
	for (i = 0; i < num; i++)
	{
		temp = MBS_MemReadCoilState(coil + i);
		switch (temp)
		{
		case 0:
			//status[i / 8] |= (0 << (i % 8));
			break;
		case 1:
			status[i / 8] |= (1 << (i % 8));
			break;
		default:
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
	}

	eMBS_Port._txLen = 0;
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[0];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[1];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = m;
	for (i = 0; i < m; i++)
	{
		eMBS_Port._txBuff[eMBS_Port._txLen++] = status[i];
	}
	MBS_PortSendWithCRC(eMBS_Port._txBuff, eMBS_Port._txLen);
}
#endif

#if MBS_FUNCTION_02_ENABLE
/*
*****************************************************
* Method:       MBS_Function02H
* Description:	¶ÁÀëÉ¢ÊäÈë×´Ì¬
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function02H(void)
{
	uint16_t addr;
	uint16_t num;
	uint16_t i;
	uint16_t m;
	uint8_t status[MBS_PORT_TXBUFF_SIZE] = { 0 };
	uint8_t temp;

	num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((num<1) || (num>2000))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	addr = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((addr < mbsDiscreteInput._startAddr) || ((addr + num) > mbsDiscreteInput._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}
	m = (num + 7) / 8;
	for (i = 0; i < m; i++)
	{
		status[i] = 0;
	}
	for (i = 0; i < num; i++)
	{
		temp = MBS_MemReadDiscreteInputState(addr + i);
		switch (temp)
		{
		case 0:
			//status[i / 8] |= (0 << (i % 8));
			break;
		case 1:
			status[i / 8] |= (1 << (i % 8));
			break;
		default:
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
	}

	eMBS_Port._txLen = 0;
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[0];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[1];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = m;
	for (i = 0; i < m; i++)
	{
		eMBS_Port._txBuff[eMBS_Port._txLen++] = status[i];
	}
	MBS_PortSendWithCRC(eMBS_Port._txBuff, eMBS_Port._txLen);
}
#endif

#if MBS_FUNCTION_03_ENABLE
/*
*****************************************************
* Method:       MBS_Function03H
* Description:	¶ÁÈ¡±£³Ö¼Ä´æÆ÷
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function03H(void)
{
	uint16_t reg;
	uint16_t num;
	uint16_t i;
	uint8_t reg_value[MBS_PORT_TXBUFF_SIZE];

	num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((num<1) || (num>0x7D))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	reg = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((reg < mbsHoldReg._startAddr) || ((reg + num - 1) > mbsHoldReg._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}

	for (i = 0; i < num; i++)
	{
		if (MBS_MemReadHoldRegValue(reg, &reg_value[2 * i]) > 1)
		{
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
		reg++;
	}

	eMBS_Port._txLen = 0;
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[0];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[1];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = num * 2;
	for (i = 0; i < num; i++)
	{
		eMBS_Port._txBuff[eMBS_Port._txLen++] = reg_value[2 * i];
		eMBS_Port._txBuff[eMBS_Port._txLen++] = reg_value[2 * i + 1];
	}
	MBS_PortSendWithCRC(eMBS_Port._txBuff, eMBS_Port._txLen);
}
#endif

#if MBS_FUNCTION_04_ENABLE
/*
*****************************************************
* Method:       MBS_Function04H
* Description:	¶ÁÈ¡ÊäÈë¼Ä´æÆ÷
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function04H(void)
{

	uint16_t reg;
	uint16_t num;
	uint16_t i;
	uint8_t reg_value[MBS_PORT_TXBUFF_SIZE];

	num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((num<1) || (num>0x7D))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	reg = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((reg < mbsInputRegister._startAddr) || ((reg + num) > mbsInputRegister._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}

	for (i = 0; i < num; i++)
	{
		if (MBS_MemReadInputRegisterValue(reg, &reg_value[2 * i]) > 1)
		{
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
		reg++;
	}

	eMBS_Port._txLen = 0;
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[0];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = eMBS_Port._rxBuff[1];
	eMBS_Port._txBuff[eMBS_Port._txLen++] = num * 2;
	for (i = 0; i < num; i++)
	{
		eMBS_Port._txBuff[eMBS_Port._txLen++] = reg_value[2 * i];
		eMBS_Port._txBuff[eMBS_Port._txLen++] = reg_value[2 * i + 1];
	}
	MBS_PortSendWithCRC(eMBS_Port._txBuff, eMBS_Port._txLen);
}
#endif

#if MBS_FUNCTION_05_ENABLE
/*
*****************************************************
* Method:       MBS_Function05H
* Description:	Ç¿ÖÆÐ´µ¥¸öÏßÈ¦
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function05H(void)
{
	uint16_t coil;
	uint16_t value;

	value = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_WRITE_ONE_VALUE]);
	if ((value != 0x0000) && (value != 0xff00))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}

	coil = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]);
	if ((coil >= mbsCoil._startAddr) && (coil <= mbsCoil._endAddr))
	{
		if (MBS_MemWriteCoilState(coil, value) > 1)	//Ê§°Ü
		{
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
		else
		{
			MBS_PortSendAck(MBS_EX_NONE);
		}
	}
	else
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
	}
}
#endif

#if MBS_FUNCTION_06_ENABLE
/*
*****************************************************
* Method:       MBS_Function06H
* Description:	Ð´µ¥¸ö±£³Ö¼Ä´æÆ÷
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function06H(void)
{
	uint16_t reg;
	uint16_t value;

	value = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_WRITE_ONE_VALUE]);

	reg = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]);
	if ((reg >= mbsHoldReg._startAddr) && (reg <= mbsHoldReg._endAddr))
	{
		if (MBS_MemWriteHoldRegValue(reg, value) > 1)	//Ê§°Ü
		{
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
		else
		{
			MBS_PortSendAck(MBS_EX_NONE);
		}
	}
	else
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
	}
}
#endif

#if MBS_FUNCTION_0F_ENABLE
/*
*****************************************************
* Method:       MBS_Function0FH
* Description:	Á¬ÐøÐ´¶à¸öÏßÈ¦
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function0FH(void)
{
	uint16_t	coil;
	uint16_t	num;
	uint8_t		byteNum;

	num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((num<1) || (num>0x07B0))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}

	byteNum = num / 8;
	if ((num % 8) != 0)
	{
		byteNum++;
	}
	if (byteNum != eMBS_Port._rxBuff[MBS_FRAME_BYTE_NUM])
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}

	coil = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((coil < mbsCoil._startAddr) || ((coil + num - 1) > mbsCoil._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}

	if (MBS_MemWriteCoilsState(coil, num, eMBS_Port._rxBuff[MBS_FRAME_BYTE_NUM], &eMBS_Port._rxBuff[MBS_FRAME_BYTE_NUM + 1]) > 1)
	{
		MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
		return;
	}
	else
	{
		MBS_PortSendAck(MBS_EX_NONE);
	}
}
#endif

#if MBS_FUNCTION_10_ENABLE
/*
*****************************************************
* Method:       MBS_Function10H
* Description:	Á¬ÐøÐ´¶à¸ö±£³Ö¼Ä´æÆ÷
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Function10H(void)
{
	uint16_t reg_addr;
	uint16_t reg_num;
	uint8_t i;
	uint16_t value;

	reg_num = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_OPT_NUM]);				/* ¼Ä´æÆ÷¸öÊý */
	if ((reg_num<1) || (reg_num>0x007B))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	if (reg_num * 2 != eMBS_Port._rxBuff[MBS_FRAME_BYTE_NUM])
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_VALUE);
		return;
	}
	reg_addr = BEBufToUint16(&eMBS_Port._rxBuff[MBS_FRAME_START_ADD]); 			/* ¼Ä´æÆ÷ºÅ */
	if ((reg_addr < mbsHoldReg._startAddr) || ((reg_addr + reg_num - 1) > mbsHoldReg._endAddr))
	{
		MBS_PortSendAck(MBS_EX_ILLEGAL_DATA_ADDRESS);
		return;
	}

	for (i = 0; i < reg_num; i++)
	{
		value = BEBufToUint16(&eMBS_Port._rxBuff[7 + 2 * i]);	/* ¼Ä´æÆ÷Öµ */

		if (MBS_MemWriteHoldRegValue(reg_addr + i, value) >1)
		{
			MBS_PortSendAck(MBS_EX_SLAVE_DEVICE_FAILURE);	/*·µ»Ø´íÎó²¢ÇÒÍË³ö*/
			return;
		}
	}
	MBS_PortSendAck(MBS_EX_NONE);
}
#endif

/*
*********************************************************************
* -MBS_Function.c	<File end.>
* -f:\draven\·¿Ì¬µÆ\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/




