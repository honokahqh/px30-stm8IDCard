/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Port.c
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

MBS_PortFrameTypes	eMBS_Port;

/*
*****************************************************
* Method:       MBS_PortSendWithCRC
* Description:	发送消息自动追加CRC校验码
* Author:       @Draven 
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	uint8_t * _pBuf
* Parameter:   	uint8_t _ucLen
* History:
*****************************************************
*/
void MBS_PortSendWithCRC(uint8_t *_pBuf, uint8_t _ucLen)
{
	uint16_t crc;
	crc = CRC16_Modbus(_pBuf, _ucLen);
	_pBuf[_ucLen++] = crc;
	_pBuf[_ucLen++] = crc >> 8;

	MBS_PhysicalSendBuff(_pBuf, _ucLen);
}

/*
*****************************************************
* Method:       MBS_PortSendAck
* Description:	发送应答消息
* Author:       @Draven 
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	MBS_EX_STATE ackCode
* History:
*****************************************************
*/
void MBS_PortSendAck(MBS_EX_STATE	ackCode)
{
	if (ackCode)		
	{
		eMBS_Port._txBuff[MBS_FRAME_SLAVER_ADDR] = MBS_SelfAddr;
		eMBS_Port._txBuff[MBS_FRAME_FUNCTION_CODE] = eMBS_Port._rxBuff[MBS_FRAME_FUNCTION_CODE] | 0x80;
		eMBS_Port._txBuff[MBS_FRAME_FUNCTION_CODE + 1] = (uint8_t)ackCode;			//发送错误码
		eMBS_Port._txLen = 3;
	}
	else
	{
		uint8_t i;
		for ( i = 0; i < 6; i++)
		{
			eMBS_Port._txBuff[i] = eMBS_Port._rxBuff[i];
		}
		eMBS_Port._txLen = 6;
	}
	MBS_PortSendWithCRC(eMBS_Port._txBuff, eMBS_Port._txLen);
}


/*
*********************************************************************
* -MBS_Port.c	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/



