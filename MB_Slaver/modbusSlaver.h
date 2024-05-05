/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	modbusSlaver.h
* filepath:	f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/05/08
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/
#ifndef _MODBUSSLAVER_H
#define _MODBUSSLAVER_H

//#include "type.h"
#include "stm8s.h"
#include "STM8usart1.h"
#include "appValue.h"

/***************************************************************	CONFIG		*/
#define	MBS_FUNCTION_01_ENABLE			(1)			
#define	MBS_FUNCTION_02_ENABLE			(0)
#define	MBS_FUNCTION_03_ENABLE			(1)
#define	MBS_FUNCTION_04_ENABLE			(0)
#define	MBS_FUNCTION_05_ENABLE			(1)
#define	MBS_FUNCTION_06_ENABLE			(1)
#define	MBS_FUNCTION_0F_ENABLE			(1)
#define	MBS_FUNCTION_10_ENABLE			(1)

#define USER_COIL_NUM					(4)		/* 注意 appValue.h 文件同步更改*/
#define USER_HOLDREG_NUM				(28)		
#define USER_DISINPUT_NUM				(0)
#define USER_INPUTREG_NUM				(0)

#define MBS_PORT_RXBUFF_SIZE			64
#define MBS_PORT_TXBUFF_SIZE			64

/***************************************************************/

#define MBS_FRAME_SLAVER_ADDR			(0)
#define MBS_FRAME_FUNCTION_CODE			(1)
#define MBS_FRAME_START_ADD				(2)
#define MBS_FRAME_OPT_NUM				(4)
#define MBS_FRAME_WRITE_ONE_VALUE		(4)
#define MBS_FRAME_BYTE_NUM				(6)

typedef enum{
	MBS_EX_NONE = 0x00,	                /*无错误*/
	MBS_EX_ILLEGAL_FUNCTION = 0x01,     /*不支持的操作类型*/
	MBS_EX_ILLEGAL_DATA_ADDRESS = 0x02, /*非法的操作地址*/
	MBS_EX_ILLEGAL_DATA_VALUE = 0x03,   /*非法的操作数值*/
	MBS_EX_SLAVE_DEVICE_FAILURE = 0x04, /*设备故障*/
	MBS_EX_ACKNOWLEDGE = 0x05,          /*确认*/
	MBS_EX_SLAVE_BUSY = 0x06,           /*从设备忙*/
	MBS_EX_MEMORY_PARITY_ERROR = 0x08,  /*存储奇偶性差错*/
	MBS_EX_GATEWAY_PATH_FAILED = 0x0A,  /*不可用网关路径*/
	MBS_EX_GATEWAY_TGT_FAILED = 0x0B,   /*网关目标设备响应失败*/
}MBS_EX_STATE;

extern uint8_t	MBS_SelfAddr;

/***************************************************************	MBS_Function.h	*/

#if MBS_FUNCTION_01_ENABLE
void MBS_Function01H(void);
#endif
#if MBS_FUNCTION_02_ENABLE
void MBS_Function02H(void);
#endif
#if MBS_FUNCTION_03_ENABLE
void MBS_Function03H(void);
#endif
#if MBS_FUNCTION_04_ENABLE
void MBS_Function04H(void);
#endif

#if MBS_FUNCTION_05_ENABLE
void MBS_Function05H(void);
#endif
#if MBS_FUNCTION_06_ENABLE
void MBS_Function06H(void);
#endif
#if MBS_FUNCTION_0F_ENABLE
void MBS_Function0FH(void);
#endif
#if MBS_FUNCTION_10_ENABLE
void MBS_Function10H(void);
#endif

/***************************************************************	MBS_Memory.h	*/
#if MBS_FUNCTION_01_ENABLE
uint8_t MBS_MemReadCoilState(uint16_t _coilAddr);
#endif
#if MBS_FUNCTION_02_ENABLE
uint8_t MBS_MemReadDiscreteInputState(uint16_t _Addr);
#endif
#if MBS_FUNCTION_05_ENABLE
uint8_t MBS_MemWriteCoilState(uint16_t _coilAddr, uint16_t nweState);
#endif
#if MBS_FUNCTION_0F_ENABLE
uint16_t MBS_MemWriteCoilsState(uint16_t regNum, uint16_t writeNum, uint8_t byteNum, uint8_t *writeData);
#endif
#if MBS_FUNCTION_03_ENABLE
uint8_t MBS_MemReadHoldRegValue(uint16_t _regAddr, uint8_t *_regValue);
#endif
#if MBS_FUNCTION_02_ENABLE
uint8_t MBS_MemReadInputRegisterValue(uint16_t _regAddr, uint8_t *_regValue);
#endif
#if ((MBS_FUNCTION_06_ENABLE)|(MBS_FUNCTION_10_ENABLE))
uint8_t MBS_MemWriteHoldRegValue(uint16_t _regAddr, uint16_t _regValue);
#endif

/***************************************************************	MBS_Str.h	*/

uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen);
uint16_t BEBufToUint16(uint8_t *_pBuf);
uint16_t LEBufToUint16(uint8_t *_pBuf);

/***************************************************************	MBS_Map.h	*/
//线圈
#if ((MBS_FUNCTION_01_ENABLE)|(MBS_FUNCTION_05_ENABLE)|(MBS_FUNCTION_0F_ENABLE))
typedef struct
{
	uint16_t					_coilAddr;		//线圈地址
	uint8_t						*_pData;		//线圈数据值 
} MBS_CoilValueTypes;

typedef struct {
	MBS_CoilValueTypes			*const _Value;
	uint16_t					_startAddr;
	uint16_t					_endAddr;
	uint16_t					const _num;
}MBS_CoilTypes;

void MBS_MappingCoilInit(MBS_CoilValueTypes	*coil, uint16_t addr, uint8_t *pValue);
#endif
/************************/
//保持寄存器
#if ((MBS_FUNCTION_03_ENABLE)|(MBS_FUNCTION_06_ENABLE)|(MBS_FUNCTION_10_ENABLE))
typedef struct
{
	uint16_t					_regAddr;		//保持寄存器地址
	uint16_t					*_pData;		//保持寄存器数据
}MBS_HoldRegValueTypes;

typedef struct {
	MBS_HoldRegValueTypes		*const _Value;
	uint16_t					_startAddr;
	uint16_t					_endAddr;
	uint16_t					const _num;
}MBS_HoldRegTypes;

void MBS_MappingHoldRegInit(MBS_HoldRegValueTypes *reg, uint16_t addr, uint16_t *valueMapping);
#endif
/************************/
//离散输入
#if MBS_FUNCTION_02_ENABLE
typedef struct{
	uint16_t					_coilAddr;		//离散输入状态地址
	uint8_t						*_pData;		//对应数据值 的地址
}MBS_DiscreteInputValueTypes;

typedef struct {
	MBS_DiscreteInputValueTypes	*const _Value;
	uint16_t					_startAddr;
	uint16_t					_endAddr;
	uint16_t					const _num;
}MBS_DiscreteInputTypes;

void MBS_MappingsDiscreteInputInit(MBS_DiscreteInputValueTypes *DiscreteInput, uint16_t addr, uint8_t * DiscreteInputMapping);
#endif
/************************/
//输入寄存器
#if MBS_FUNCTION_04_ENABLE
typedef struct{
	uint16_t					_regAddr;		//输入寄存器地址
	uint16_t					*_pData;		//输入寄存器数据值地址
}MBS_InputRegisterValueTypes;

typedef struct {
	MBS_InputRegisterValueTypes	*const _Value;
	uint16_t					_startAddr;
	uint16_t					_endAddr;
	uint16_t					const _num;
}MBS_InputRegisterTypes;

void MBS_MappingsInputRegisterInit(MBS_InputRegisterValueTypes *InputRegister, uint16_t addr, uint16_t * InputRegisterMapping);
#endif

#if ((MBS_FUNCTION_01_ENABLE)|(MBS_FUNCTION_05_ENABLE)|(MBS_FUNCTION_0F_ENABLE))
extern MBS_CoilValueTypes			mbsCoilValue[USER_COIL_NUM];
extern MBS_CoilTypes				mbsCoil;
void MBS_MappingCoilInit(MBS_CoilValueTypes	*coil, uint16_t addr, uint8_t *pValue);
#endif
#if ((MBS_FUNCTION_03_ENABLE)|(MBS_FUNCTION_06_ENABLE)|(MBS_FUNCTION_10_ENABLE))
extern MBS_HoldRegValueTypes		mbsHoldRegValue[USER_HOLDREG_NUM];
extern MBS_HoldRegTypes			mbsHoldReg;
void MBS_MappingHoldRegInit(MBS_HoldRegValueTypes *reg, uint16_t addr, uint16_t *valueMapping);
#endif
#if MBS_FUNCTION_02_ENABLE
extern MBS_DiscreteInputValueTypes	mbsDiscreteInputValue[USER_DISINPUT_NUM];
extern MBS_DiscreteInputTypes		mbsDiscreteInput;
void MBS_MappingsDiscreteInputInit(MBS_DiscreteInputValueTypes *DiscreteInput, uint16_t addr, uint8_t * DiscreteInputMapping);
#endif
#if MBS_FUNCTION_04_ENABLE
extern MBS_InputRegisterValueTypes	mbsInputRegisterValue[USER_INPUTREG_NUM];
extern MBS_InputRegisterTypes		mbsInputRegister ;
#endif

/***************************************************************	MBS_Port.h	*/

typedef struct{
	uint8_t				_rxBuff[MBS_PORT_RXBUFF_SIZE];
	uint8_t				_rxLen;
	uint8_t				_rxState;

	uint8_t				_txBuff[MBS_PORT_TXBUFF_SIZE];
	uint8_t				_txLen;
	uint8_t				_txState;
}MBS_PortFrameTypes;

extern MBS_PortFrameTypes	eMBS_Port;

void MBS_PortSendAck(MBS_EX_STATE	ackCode);
void MBS_PortSendWithCRC(uint8_t *_pBuf, uint8_t _ucLen);

/***************************************************************	MBS_Physical.h	*/

void MBS_PhysicalSendBuff(uint8_t *_str, uint8_t _strLen);
void MBS_PhysicalReserveBuff(uint8_t *_str, uint8_t _strLen);

/***************************************************************	MBS_Core.h	*/

void MBS_Init(void);
void MBS_CorePoll(void);
void MBS_CoreAnalyze(void);

/**************************************************************		MBS_User.h	*/

void MBS_UserValueMapping(void);

/***************************************************************/
#endif
/*
*********************************************************************
* -modbusSlaver.h	<File end.>
* -f:\draven\房态灯\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/





