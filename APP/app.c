/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	app.c
* filepath:	f:\draven\�пذ�\zk_dravenv100\app
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/19
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/
#include <stm8s.h>
#include "pt.h"
#include "bsp.h"
#include "modbusSlaver.h"
#include "upData.h"

int mbs_timeout = 0;

static struct pt pt_modbus;
static struct pt pt_monitor;
static struct pt pt_rfid;

static int modbus_sevice(struct pt *pt); /* MODBUS ͨ�ŷ��� */
static int in_operation(struct pt *pt);	 /* ϵͳ���м�� ���Ź�ιʳ ���ݱ���*/
static int rfid_sevice(struct pt *pt);	 /* rfid������� */

#define FIRST_POWER_ON_CODE 113 /* @2017/08/15 09:56:57 �ϵ�У���� Ҳ��ͬ�ڰ汾�� */
/*
*****************************************************
* Method:       app_init
* Description:	Ӧ�ó����ʼ��
* Author:       @Draven
* Date:  		2017/07/20
* Returns:      void
* Parameter:   	void
* History:
*****************************************************
*/
void app_init(void)
{
	uint8_t temp[3];
	bsp_dog_reload();
	delay_ms(MY_SELF_ADDR * 5 + 100); /* @2017/08/14 10:55:33 �ϵ���ʱ���� */
	temp[0] = 0xff;
	temp[1] = MY_SELF_ADDR;
	temp[2] = 0xfe;
	mbs_sendData(temp, 3);
}

uint8_t flag = 0;
void system_run(void)
{
	PT_INIT(&pt_modbus);
	PT_INIT(&pt_monitor);
	PT_INIT(&pt_rfid);
	while (1)
	{
		modbus_sevice(&pt_modbus);
		rfid_sevice(&pt_rfid);
		in_operation(&pt_monitor);
	}
}

/*
*****************************************************
* Method:       modbus_sevice
* Description:	MODBUS ͨ�ŷ���
* Author:       @Draven
* Date:  		2017/07/21
* Returns:      int
* Parameter:   	struct pt * pt
* History:
*****************************************************
*/
static int modbus_sevice(struct pt *pt)
{
	PT_BEGIN(pt);

	while (1)
	{
		PT_WAIT_UNTIL(pt, uart_state.has_data);
		upData_CheckFrame(uart_state.rx_buff, uart_state.rx_len);
		MBS_PhysicalReserveBuff(uart_state.rx_buff, uart_state.rx_len); /* ��������֡ ������ */
		uart_state.has_data = 0;
		uart_state.rx_len = 0;
		MBS_CorePoll(); /* ����ͨ������ */
	}
	PT_END(pt);
}
/*
*****************************************************
* Method:       rfid_sevice
* Description:	rfid�������
* Author:       @linkai
* Date:  		2018/07/03
* Returns:      int
* Parameter:   	struct pt * pt
* History:
*****************************************************
*/
static int rfid_sevice(struct pt *pt)
{
	static uint32_t sys_ms_last;
	// static uint32_t init_flag = 1;
	PT_BEGIN(pt);
	while (1)
	{
		PT_WAIT_UNTIL(pt, ID_Card_Info.has_card);
		ID_Card_Info.has_card = 0;
		// if ((holdRegValue[HREG_RFID_ID1] != ID_Card_Info.ID[1]) ||
		// 	(holdRegValue[HREG_RFID_ID2] != ID_Card_Info.ID[2]) ||
		// 	(holdRegValue[HREG_RFID_ID3] != ID_Card_Info.ID[3]) ||
		// 	(holdRegValue[HREG_RFID_ID4] != ID_Card_Info.ID[4]))
		// {
		// 	// debug��,����һֱˢ��while����������
		// 	if (init_flag == 0)
		// 		while (1)
		// 			;
		// }
		if (sysTime > sys_ms_last + 600 ||
			(holdRegValue[HREG_RFID_ID1] != ID_Card_Info.ID[1]) ||
			(holdRegValue[HREG_RFID_ID2] != ID_Card_Info.ID[2]) ||
			(holdRegValue[HREG_RFID_ID3] != ID_Card_Info.ID[3]) ||
			(holdRegValue[HREG_RFID_ID4] != ID_Card_Info.ID[4]))
		{
			coilState[COIL_CARD] = 1;
			holdRegValue[HREG_RFID_ID1] = ID_Card_Info.ID[1];
			holdRegValue[HREG_RFID_ID2] = ID_Card_Info.ID[2];
			holdRegValue[HREG_RFID_ID3] = ID_Card_Info.ID[3];
			holdRegValue[HREG_RFID_ID4] = ID_Card_Info.ID[4];
			// init_flag = 0;
		}
		sys_ms_last = sysTime;
	}
	PT_END(pt);
}
/*
*****************************************************
* Method:       in_operation
* Description:	ϵͳ���м��
* Author:       @Draven
* Date:  		2017/07/22
* Returns:      int
* Parameter:   	struct pt * pt
* History:
*****************************************************
*/
static int in_operation(struct pt *pt)
{
	static uint32_t ssDelay = 0;
	PT_BEGIN(pt);
	while (1)
	{
		ssDelay = sysTime + 100;
		PT_WAIT_UNTIL(pt, sysTime >= ssDelay);
		bsp_dog_reload(); /* ��ʱι�� */
		mbs_timeout++;
		if (mbs_timeout >= 10 * 600)
		{
			WWDG->CR = 0x80; // WDGA=1 ��λ
		}
	}
	PT_END(pt);
}

/*
*********************************************************************
* -app.c	<File end.>
* -f:\draven\�пذ�\zk_dravenv100\app
*********************************************************************
*/
