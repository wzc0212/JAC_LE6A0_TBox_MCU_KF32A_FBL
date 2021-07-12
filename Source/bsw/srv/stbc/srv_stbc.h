/******************************************************************************
 * (C) Copyright 2020 Anhui Domain Compute Co.Ltd
 * FILE NAME:    srv_sdbc.h
 * DESCRIPTION:
 * 
 * DATE BEGUN:   2021/07/06
 * BY:           feifei.xu
 * PRODUCT NAME:
 * APPLICATION:
 * TARGET H/W:
 * DOC REF:
 *****************************************************************************
 */

#ifndef __SRV_SDBC_H__
#define __SRV_SDBC_H__

/*****************************************************************************
**#include 
*****************************************************************************/
#include "type.h"


/*****************************************************************************
**  typedef
*****************************************************************************/


/*****************************************************************************
** Constant Macro Definition
*****************************************************************************/
#define MCU_WAKEUP_SOURCE_NONE	(0x00000000)
#define MCU_WAKEUP_SOURCE_ACC	(0x00000001)
#define MCU_WAKEUP_SOURCE_SOS	(0x00000002)
#define MCU_WAKEUP_SOURCE_LTE	(0x00000004)
#define MCU_WAKEUP_SOURCE_BLE	(0x00000008)
#define MCU_WAKEUP_SOURCE_SRS	(0x00000010)
#define MCU_WAKEUP_SOURCE_RTC	(0x00000020)
#define MCU_WAKEUP_SOURCE_LIS	(0x00000040)
#define MCU_WAKEUP_SOURCE_CAN0	(0x00000080)
#define MCU_WAKEUP_SOURCE_CAN1	(0x00000100)
#define MCU_WAKEUP_SOURCE_CAN2	(0x00000200)


#define RESF_NONE_RESET		(0x00000000)//无复位源
#define RESF_SOFT_RESET		(0x00000001)//软件复位
#define RESF_WDTA0_RESET	(0x00000002)//软件看门狗复位
#define RESF_CLMA0_RESET	(0x00000004)//PLL时钟异常复位
#define RESF_CLMA1_RESET	(0x00000008)//主时钟异常复位
#define RESF_CLMA2_RESET	(0x00000010)//高速时钟异常复位
#define RESF_LVI_RESET		(0x00000020)//寄存器低电复位
#define RESF_CVM_RESET		(0x00000040)//内核电压异常复位
#define RESF_EXT_RESET		(0x00000080)//外部复位
#define RESF_POWER_ON		(0x00000100)//上电复位
#define RESF_DEEP_RESET		(0x00000200)//Deepstop唤醒复位
#define RESF_ERROR			(0x00000400)//复位源异常
/*****************************************************************************
** System Macro Definition
*****************************************************************************/


/*****************************************************************************
** Action Macro Definition
*****************************************************************************/


/*****************************************************************************
** Config Macro Definition
*****************************************************************************/


/*****************************************************************************
** Task Macro Definition
*****************************************************************************/


/*****************************************************************************
** Variables
*****************************************************************************/


/*****************************************************************************
** Constants
*****************************************************************************/


/*****************************************************************************
** Function prototypeseb
*****************************************************************************/
void ApiStbcClrWakeupFactor(void);
UINT32 ApiStbcGetWakeupFactor(void);
void ApiStbcSetWakeupSource(UINT32 u32_wakeup_source);
void ApiStbcSoftReset(void);
UINT32 ApiStbcGetResetFactor(void);
void ApiStbcClrResetFactor(void);
/*****************************************************************************
** other
*****************************************************************************/


/****************************************************************************/

#endif	//__SRV_SDBC_H__

/*****************************************************************************
** End File
*****************************************************************************/

