/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	bsp_clock.c
* filepath:	f:\draven\中控板\zk_dravenv100\bsp
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/20
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/

#include "stm8s.h"
#include "string.h"
#include "bsp_clock.h"

void uart_idle_detect(void);

uint32_t sys_50us_id = 0;
volatile ID_Card_t ID_Card;           // 缓存，读完完整卡号后清零
volatile ID_Card_Info_t ID_Card_Info; //  读卡号后,由APP进行校验
volatile uint32_t sysTime = 0;        /* 周期时间 49天*/

// 50us定时器
void bsp_clock_init(void)
{
    /* Set the Prescaler value */
    TIM4->PSCR = (uint8_t)(TIM4_PRESCALER_8);
    /* Set the Autoreload value */
    TIM4->ARR = 99;
    /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ??has no effect*/
    TIM4->SR1 = (uint8_t)(~TIM4_FLAG_UPDATE);
    /* Enable the Interrupt sources */
    TIM4->IER |= (uint8_t)TIM4_IT_UPDATE;
    /* set or Reset the CEN Bit */
    TIM4->CR1 |= TIM4_CR1_CEN;
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
    static uint8_t count_50us = 0;
    TIM4->SR1 = (uint8_t)(~TIM4_IT_UPDATE);
    sys_50us_id++;
    count_50us++;
    if (count_50us >= 20)
    {
        count_50us = 0;
        sysTime++;
        uart_idle_detect();
    }
}

void delay_ms(uint16_t ms)
{
    uint32_t temp = sysTime;
    while ((sysTime - temp) < ms)
        ;
}
// 刷卡驱动
#define Half_Min 3  // 150us
#define Half_Max 7  // 350us
#define Full_Min 8  // 400us
#define Full_Max 13 // 650us
void bsp_idCardIO_init(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_IT);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL);
    TIM2_DeInit();                                                                     // 使能定时器2
    TIM2_TimeBaseInit(TIM2_PRESCALER_2, 63);                                           // 2分频，125khz
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 31, TIM2_OCPOLARITY_HIGH); // 占空比50%
    TIM2_Cmd(ENABLE);                                                                  // 使能定时器2
}

/**
 * checkCardData
 * @brief id卡卡号校验
 * @author Honokahqh
 * @date 2024-1-10
 */
int checkCardData(uint8_t *data, uint16_t bitNum)
{
    // 行校验
    for (int row = 0; row < (bitNum / 5) - 1; row++)
    {
        int rowSum = 0;
        for (int bit = 0; bit < 4; bit++)
        {
            rowSum += (data[(row * 5 + bit + 9) / 8] >> ((row * 5 + bit + 9) % 8)) & 1;
        }
        rowSum += (data[(row * 5 + 4 + 9) / 8] >> ((row * 5 + 4 + 9) % 8)) & 1; // 加上Px
        if (rowSum % 2 != 0)
        {
            return 0; // 行校验失败
        }
    }

    // 列校验
    for (int col = 0; col < 4; col++)
    {
        int colSum = 0;
        for (int row = 0; row < (bitNum / 5) - 1; row++)
        {
            colSum += (data[(row * 5 + col + 9) / 8] >> ((row * 5 + col + 9) % 8)) & 1;
        }
        colSum += (data[(59 + col) / 8] >> ((59 + col) % 8)) & 1; // 加上PCx
        if (colSum % 2 != 0)
        {
            return 0; // 列校验失败
        }
    }

    //
    memset((uint8_t *)&ID_Card_Info, 0, sizeof(ID_Card_Info_t));
    for (int i = 0; i < (bitNum / 5) - 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int bit = (data[((i * 5) + j + 9) / 8] & (1 << ((i * 5 + j + 9) % 8))) != 0; // 读取位
            if (bit)
            {
                int originalPos = (i * 4 + j);                                     // 计算原始位置
                int reversedPos = (originalPos / 8) * 8 + (7 - (originalPos % 8)); // 计算反转后的位置
                ID_Card_Info.ID[reversedPos / 8] |= 1 << (reversedPos % 8);
            }
        }
    }

    // 所有校验通过
    return 1;
}

uint8_t get_id_io_state()
{
    if (GPIOD->IDR & GPIO_PIN_3)
        return 0;
    else
        return 1;
}
void id_card_decode()
{
    // ID_Card.time[ID_Card.time_index++] = sys_50us_id;
    //  get start frame
    if (ID_Card.state == ID_IDLE)
    {
        if (sys_50us_id >= Full_Min && sys_50us_id <= Full_Max && get_id_io_state()) // 必然是一个翻转信号且为1
        {
            ID_Card.state = ID_START;
            ID_Card.ID[0] = 1;
        }
    }
    else if (ID_Card.state == ID_START)
    {
        if (sys_50us_id >= Half_Min && sys_50us_id <= Half_Max) // 16个空跳
        {
            ID_Card.count++;
            if (ID_Card.count == 16)
            {
                ID_Card.state = ID_DATA;
                ID_Card.count = 0;
                ID_Card.ID[0] = 0xFF;
                ID_Card.ID[1] = 1;
                ID_Card.bit = 9;
            }
        }
        else
        {
            memset((uint8_t *)&ID_Card, 0, sizeof(ID_Card_t));
        }
    }
    else if (ID_Card.state == ID_DATA) // (4 + 1)*10 + 4 + 1
    {
        if (sys_50us_id >= Full_Min && sys_50us_id <= Full_Max)
        {
            ID_Card.value = get_id_io_state();
            ID_Card.ID[ID_Card.bit / 8] |= (ID_Card.value << (ID_Card.bit % 8));
            ID_Card.bit++;
            ID_Card.count = 0;
        }
        else if (sys_50us_id >= Half_Min && sys_50us_id <= Half_Max)
        {
            ID_Card.count++;
            if (ID_Card.count % 2 == 0)
            {
                ID_Card.value = get_id_io_state();
                ID_Card.ID[ID_Card.bit / 8] |= (ID_Card.value << (ID_Card.bit % 8));
                ID_Card.bit++;
            }
        }
        else
        {
            memset((uint8_t *)&ID_Card, 0, sizeof(ID_Card_t));
        }
    }
    if (ID_Card.bit == 9 + 5 * 11) // 64bitnum 常见RFID卡标准
    {
        if (checkCardData((uint8_t *)ID_Card.ID, 5 * 11)) // !check的时间超过了500us,导致下一次中断进不来
        {
            ID_Card_Info.has_card = 1;
        }
        memset((uint8_t *)&ID_Card, 0, sizeof(ID_Card_t));
    }
    sys_50us_id = 0;
}

INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    id_card_decode();
}
