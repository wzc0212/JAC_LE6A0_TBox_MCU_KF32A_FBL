/******************************************************************************
 * (C) Copyright 2020 Anhui Domain Compute Co.Ltd
 * FILE NAME:    ecu_adc.c
 * DESCRIPTION:
 * 
 * DATE BEGUN:   2021/05/20
 * BY:           feifei.xu
 * PRODUCT NAME:
 * APPLICATION:
 * TARGET H/W:
 * DOC REF:
 *****************************************************************************
 */

/*****************************************************************************
** #include 
*****************************************************************************/
#include "system_init.h"
#include "ecu_adc.h"

/*****************************************************************************
** #define
*****************************************************************************/


/*****************************************************************************
** typedef
*****************************************************************************/
typedef struct
{
	ADC_SFRmap* ADCx;
	UINT32 u32_clk;
	UINT32 u32_clk_div;
	FunctionalState ScanMode;
	UINT32 u32_ContinuousMode;
	UINT32 u32_DataAlign;
	FunctionalState ExternalTrig_EN;
	UINT32 u32_ExternalTrig;
	FunctionalState HPExternalTrig_EN;
	UINT32 u32_HPExternalTrig;
	UINT32 u32_VoltageRef;
	UINT32 u32_NumOfConv;
	UINT32 u32_NumOfHPConv;
}ADC_CFG_S;


/*****************************************************************************
** global variable
*****************************************************************************/


/*****************************************************************************
** static variables
*****************************************************************************/
static const ADC_CFG_S s_c_st_adc0_cfg = 
{
	ADC0_SFR,
	ADC_HFCLK,
	ADC_CLK_DIV_8,
	FALSE,
	ADC_SINGLE_MODE,
	ADC_DATAALIGN_RIGHT,
	FALSE,
	ADC_EXTERNALTRIG_T1TRGO,
	FALSE,
	ADC_HPEXTERNALTRIG_CCP1_CH1,
	ADC_REF_AVDD,
	1,
	1
};

/*****************************************************************************
** static constants
*****************************************************************************/


/*****************************************************************************
** static function prototypes
*****************************************************************************/
static void Ecu_Adc_Delay(UINT32 u32_cnt);
static void Ecu_Adc_Configure(const ADC_CFG_S* p_adc_cfg);
static UINT16 Ecu_Adc_GetValue(ADC_SFRmap* ADCx,ADC_CHANNEL_E u32_channal);
/*****************************************************************************
** function prototypes
*****************************************************************************/
/****************************************************************************/
/**
 * Function Name: Ecu_Adc_Delay
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2021/06/21, feifei.xu create this function
 ****************************************************************************/
static void Ecu_Adc_Delay(UINT32 u32_cnt)
{
	while(u32_cnt--);
}

/****************************************************************************/
/**
 * Function Name: Ecu_Adc_Configure
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2021/06/21, feifei.xu create this function
 ****************************************************************************/
static void Ecu_Adc_Configure(const ADC_CFG_S* p_adc_cfg)
{
	ADC_InitTypeDef adcStruct;

	ADC_Reset (p_adc_cfg->ADCx);									//??????ADC???????????????ADC?????????
	adcStruct.m_Clock = p_adc_cfg->u32_clk;							//??????ADC??????
	adcStruct.m_ClockDiv = p_adc_cfg->u32_clk_div;					//??????ADC??????
	adcStruct.m_ScanMode = p_adc_cfg->ScanMode;						//????????????
	adcStruct.m_ContinuousMode = p_adc_cfg->u32_ContinuousMode; 	//???????????????????????????????????????????????????????????????
	adcStruct.m_DataAlign = p_adc_cfg->u32_DataAlign; 				//????????????????????????
	adcStruct.m_ExternalTrig_EN = p_adc_cfg->HPExternalTrig_EN; 	//????????????????????????????????????ADC?????????
	adcStruct.m_ExternalTrig = p_adc_cfg->u32_ExternalTrig; 		//??????????????????????????????????????????T1TRGO
	adcStruct.m_HPExternalTrig_EN = p_adc_cfg->HPExternalTrig_EN; 	//??????????????????????????????????????????ADC?????????
	adcStruct.m_HPExternalTrig = p_adc_cfg->u32_HPExternalTrig; 	//??????????????????????????????????????????CCP1?????????1
	adcStruct.m_VoltageRef=p_adc_cfg->u32_VoltageRef; 				//?????????????????????????????????VDDA
	adcStruct.m_NumOfConv = p_adc_cfg->u32_NumOfConv; 				//????????????????????????1?????????
	adcStruct.m_NumOfHPConv = p_adc_cfg->u32_NumOfHPConv; 			//?????????????????????????????????
	ADC_Configuration (p_adc_cfg->ADCx, &adcStruct);
	ADC_Cmd (p_adc_cfg->ADCx, TRUE); 								//ADC??????
	Ecu_Adc_Delay(0xFF);  											//ADC??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
}


/****************************************************************************/
/**
 * Function Name: Ecu_Adc_GetValue
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2021/06/21, feifei.xu create this function
 ****************************************************************************/
static UINT16 Ecu_Adc_GetValue(ADC_SFRmap* ADCx,ADC_CHANNEL_E u32_channal)
{
	ADC_Regular_Channel_Config(ADCx,(UINT32)u32_channal,0x01);
	ADC_Software_Start_Conv(ADCx);
	while(!ADC_Get_INT_Flag(ADCx,ADC_INT_EOC));

	return ADC_Get_Conversion_Value(ADCx);
}
/****************************************************************************/
/**
 * Function Name: ApiAdc0Init
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2021/06/21, feifei.xu create this function
 ****************************************************************************/
void ApiAdc0Init(void)
{
	Ecu_Adc_Configure(&s_c_st_adc0_cfg);
}
/****************************************************************************/
/**
 * Function Name: ApiAdcVoltRead
 * Description: none
 *
 * Param:   none
 * Return:  none
 * Author:  2021/06/21, feifei.xu create this function
 ****************************************************************************/
UINT32 ApiAdcVoltRead(ADC_CHANNEL_E u32_channal)
{
	UINT32 u32_temp = 0;
	UINT32 u32_adcmv = 0;
	
	u32_temp = (UINT32)Ecu_Adc_GetValue(s_c_st_adc0_cfg.ADCx,u32_channal);
	u32_adcmv = (UINT32)((((3300*10000)/4095)*u32_temp)/10000);

	if(NMBAT_DET == u32_channal)
	{
		u32_adcmv = u32_adcmv*2;
	}

	if(USB_DET == u32_channal)
	{
		u32_adcmv = u32_adcmv*2;
	}

	if(BAT_DET == u32_channal)
	{
		u32_adcmv = u32_adcmv*1.1+100;//y = 1100*x+100
	}

	return u32_adcmv;
}
/****************************************************************************/


/*****************************************************************************
** End File
*****************************************************************************/

