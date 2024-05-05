/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Physical.c
* filepath:	f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/05/08
* <version> V-0.0.1
* <desc>	-可支持多端口共用协议栈。只需要修改此文件
*********************************************************************
*/

#include "modbusSlaver.h"

/*
*****************************************************
* Method:       MBS_PhysicalSendBuff
* Description:	物理端口发送一帧数据，此函数名不要修改。函数被ModbusPort文件调用
* Author:       @Draven 
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	uint8_t * _str
* Parameter:   	uint8_t _strLen
* History:
*****************************************************
*/
void MBS_PhysicalSendBuff(uint8_t *_str, uint8_t _strLen)
{
	mbs_sendData(_str, _strLen);
}

/*
*****************************************************
* Method:       MBS_PhysicalReserveBuff
* Description:	当硬件接收到一帧数据后将会调用此函数，将收到的数据帧传到协议栈里面进行解析
* Author:       @Draven 
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	uint8_t * _str
* Parameter:   	uint8_t _strLen
* History:
*****************************************************
*/
void MBS_PhysicalReserveBuff(uint8_t *_str, uint8_t _strLen)
{
	uint16_t	i;
	for ( i = 0; i < _strLen; i++)
	{
		eMBS_Port._rxBuff[i] = _str[i];
	}
	eMBS_Port._rxLen = _strLen;
	eMBS_Port._rxState = 1;
}

/*
*********************************************************************
* -MBS_Physical.c	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/



