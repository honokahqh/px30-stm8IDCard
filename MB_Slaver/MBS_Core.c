/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Core.c
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

/*
*****************************************************
* Method:       MBS_CorePoll
* Description:	解析数据包. 轮训调用
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
extern int mbs_timeout;
void MBS_CorePoll(void)
{	
	if (eMBS_Port._rxState == 0)	/*未接收到数据 ，直接返回*/
	{	
		return;				
	}

	eMBS_Port._rxState = 0;	 		/* 清标志 */

	if (eMBS_Port._rxLen < 4)		/* 接收到的数据小于4个字节就认为错误 */
	{
		goto err_ret;
	}

	/* 站地址 (1字节） */
	if (eMBS_Port._rxBuff[MBS_FRAME_SLAVER_ADDR] != MBS_SelfAddr)	/* 判断主机发送的命令地址是否符合 (0地址广播) */
	{
		goto err_ret;
	}

	/* 计算CRC校验和 */
	if (CRC16_Modbus(eMBS_Port._rxBuff,eMBS_Port._rxLen))
	{
		goto err_ret;
	}
	mbs_timeout = 0;
	/* 分析应用层协议 */
	MBS_CoreAnalyze();

err_ret:
	eMBS_Port._rxLen = 0;			/*复位接收数据指针*/
}




/*
*****************************************************
* Method:       MBS_CoreAnalyze
* Description:	分析数据帧
* Author:       @Draven
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_CoreAnalyze(void)
{
	switch (eMBS_Port._rxBuff[1])		/* 第2个字节 功能码 */
	{
#if MBS_FUNCTION_01_ENABLE
	case 0x01:
		MBS_Function01H();
		coilState[COIL_CARD] = 0;
		break;
#endif
#if MBS_FUNCTION_02_ENABLE
	case 0x02:
		MBS_Function02H();
		break;
#endif
#if MBS_FUNCTION_03_ENABLE
	case 0x03:
		MBS_Function03H();
		break;
#endif
#if MBS_FUNCTION_04_ENABLE
	case 0x04:
		MBS_Function04H();
		break;
#endif
#if MBS_FUNCTION_05_ENABLE
	case 0x05:
		MBS_Function05H();
		break;
#endif
#if MBS_FUNCTION_06_ENABLE
	case 0x06:
		MBS_Function06H();
		break;
#endif
#if MBS_FUNCTION_0F_ENABLE
	case 0x0F:
		MBS_Function0FH();
		break;
#endif
#if MBS_FUNCTION_10_ENABLE
	case 0x10:
		MBS_Function10H();
		break;
#endif
	default:
		MBS_PortSendAck(MBS_EX_ILLEGAL_FUNCTION);
		break;
	}
}


/*
*****************************************************
* Method:       MBS_Init
* Description:	协议栈初始化
* Author:       @Draven 
* Date:  		2017/05/08
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void MBS_Init(void)
{
	uart_init();
	MBS_UserValueMapping();
}

/*
*********************************************************************
* -MBS_Core.c	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/


