/******************************************************************************
 * (C) Copyright 2020 Anhui Domain Compute Co.Ltd
 * FILE NAME:    ecu_can.h
 * DESCRIPTION:
 * 
 * DATE BEGUN:   2021/05/15
 * BY:           feifei.xu
 * PRODUCT NAME:
 * APPLICATION:
 * TARGET H/W:
 * DOC REF:
 *****************************************************************************
 */

#ifndef __ECU_CAN_H__
#define __ECU_CAN_H__

/*****************************************************************************
**#include 
*****************************************************************************/
#include "type.h"
/*****************************************************************************
**  typedef
*****************************************************************************/
typedef struct
{
	UINT32 u32_id;
	UINT8 u8_len;
	UINT8 u8_data[8];
}CAN_MSG_S;
/*****************************************************************************
** Constant Macro Definition
*****************************************************************************/
/********can波特率*********/
#define CAN_BAUDRATE_1000K		(2)
#define CAN_BAUDRATE_500K		(5)
#define CAN_BAUDRATE_250K		(11)
#define CAN_BAUDRATE_125K		(23)


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


/*****************************************************************************s
** Function prototypeseb
*****************************************************************************/
void ApiCan0Init(void);
void ApiCan1Init(void);
void ApiCan2Init(void);
void ApiCan0CheckBusOff(void);
void ApiCan1CheckBusOff(void);
void ApiCan2CheckBusOff(void);
void ApiCanHandler5ms(void);
void ApiCanHandler1ms(void);
void ApiCan0IntDisable(void);
void ApiCan1IntDisable(void);
void ApiCan2IntDisable(void);
void ApiCan0Send(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
void ApiCan1Send(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
void ApiCan2Send(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
void ApiCan0ExtSend(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
void ApiCan1ExtSend(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
void ApiCan2ExtSend(UINT32 u32_id, UINT8 u8_len, UINT8* u8_data);
BOOL ApiCan0ReiciveMsg(CAN_MSG_S* p_can_msg,UINT8* u8_count);
BOOL ApiCan1ReiciveMsg(CAN_MSG_S* p_can_msg,UINT8* u8_count);
BOOL ApiCan2ReiciveMsg(CAN_MSG_S* p_can_msg,UINT8* u8_count);
/*****************************************************************************
** other
*****************************************************************************/


/****************************************************************************/

#endif	//__ECU_CAN_H__

/*****************************************************************************
** End File
*****************************************************************************/
