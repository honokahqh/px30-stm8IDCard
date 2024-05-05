/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	MBS_Map.c
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

#if ((MBS_FUNCTION_01_ENABLE)|(MBS_FUNCTION_05_ENABLE)|(MBS_FUNCTION_0F_ENABLE))
MBS_CoilValueTypes			mbsCoilValue[USER_COIL_NUM];
MBS_CoilTypes				mbsCoil = { mbsCoilValue, 0, 0, USER_COIL_NUM };

void MBS_MappingCoilInit(MBS_CoilValueTypes	*coil, uint16_t addr, uint8_t *pValue)
{
	coil->_coilAddr = addr;
	coil->_pData = pValue;
}
#endif
#if ((MBS_FUNCTION_03_ENABLE)|(MBS_FUNCTION_06_ENABLE)|(MBS_FUNCTION_10_ENABLE))
MBS_HoldRegValueTypes		mbsHoldRegValue[USER_HOLDREG_NUM];
MBS_HoldRegTypes			mbsHoldReg = { mbsHoldRegValue, 0, 0, USER_HOLDREG_NUM };

void MBS_MappingHoldRegInit(MBS_HoldRegValueTypes *reg, uint16_t addr, uint16_t *valueMapping)
{
	reg->_regAddr = addr;
	reg->_pData = valueMapping;
}
#endif
#if MBS_FUNCTION_02_ENABLE
MBS_DiscreteInputValueTypes	mbsDiscreteInputValue[USER_DISINPUT_NUM];
MBS_DiscreteInputTypes		mbsDiscreteInput = { mbsDiscreteInputValue, 0, 0, USER_HOLDREG_NUM };

void MBS_MappingsDiscreteInputInit(MBS_DiscreteInputValueTypes *DiscreteInput, uint16_t addr, uint8_t * DiscreteInputMapping)
{
	DiscreteInput->_coilAddr = addr;
	DiscreteInput->_pData = DiscreteInputMapping;
}
#endif
#if MBS_FUNCTION_04_ENABLE
MBS_InputRegisterValueTypes	mbsInputRegisterValue[USER_INPUTREG_NUM];
MBS_InputRegisterTypes		mbsInputRegister = { mbsInputRegisterValue, 0, 0, USER_HOLDREG_NUM };

void MBS_MappingsInputRegisterInit(MBS_InputRegisterValueTypes *InputRegister, uint16_t addr, uint16_t * InputRegisterMapping)
{
	InputRegister->_regAddr = addr;
	InputRegister->_pData = InputRegisterMapping;
}

#endif




/*
*********************************************************************
* -MBS_Map.c	<File end.>
* -f:\draven\·¿Ì¬µÆ\modbus_slaverproj\draven-stm8-proj\mb-slaver
*********************************************************************
*/



