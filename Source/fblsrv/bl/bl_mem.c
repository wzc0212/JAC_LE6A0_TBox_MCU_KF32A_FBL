/*****************************************************************************/
/* Copyright (C), 2019, DIAS Automotive Electronic Systems Co; Ltd.          */
/* File Name:    bl_mem.c                                                    */
/* Description:  Memory Layer interface implementation                       */
/*                                                                           */
/* Others:       other description                                           */
/*                                                                           */
/* Processor:    RH850F1L                                                    */
/* Compiler:     GHS_201517                                                  */
/********************************** 修改历史 *********************************/
/* Date            Version       Author      Description                     */
/* 2019-07-05   V11.01.01.00     陈惠        基线创建                              */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* 头文件                                                                    */
/*---------------------------------------------------------------------------*/
#include "bl_mem.h"
#include "ll_target.h"

/*---------------------------------------------------------------------------*/
/* 类型定义                                                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* 宏定义                                                                    */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* 常量定义                                                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* 变量定义                                                                  */
/*---------------------------------------------------------------------------*/
static MemSection_t tIntFlashSection[]=
{
    /*StartAddress; EndAddress;*/
    {0x00018000UL,   0x000fffffUL}
};


/*---------------------------------------------------------------------------*/
/* 外部参照变量                                                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* 内部函数声明                                                              */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* 外部函数定义                                                              */
/*---------------------------------------------------------------------------*/
/******************************************************************************
*  function name | ApiValidateFlashRead
*  content       | It validates the range of given parameters in case of memory read actions.
*				   (read data to RAM buffer for CRC calculation)
*  parameter     | vm_address:地址；vm_size：地址大小
*  return        | mem_o：返回memory类型
*  notice        | 无
******************************************************************************/
MemType_e ApiValidateFlashRead(UINT32 u32Address,UINT32 u32Size)
{
    MemSection_t* ptSection;
    UINT32 u32EndAddress;

    u32EndAddress = (u32Address + u32Size) - 1UL;

    /* check for overflow   */
    if(u32EndAddress < u32Address)
    {
        return(Invalid);
    }
	
    /* range check */
	ptSection=&tIntFlashSection[0];
    if((ptSection->u32StartAddress <= u32Address) &&
       (ptSection->u32EndAddress >= u32EndAddress))
    {
    	// TODO:可优化通过查表来确定是flash还是bt
        return INTFLASH;
    }

    return(Invalid);
}


/******************************************************************************
*  function name | ApiLlFlashRead
*  content       | 从一个地址copy到另一个地址(一般用于从flash中copy到ram)
*  parameter     | u8Buffer：目标地址，u32MemAddress：数据地址，u16Size：长度
*  return        | INT16
*  notice        | 无
******************************************************************************/
INT16 ApiFlashRead(UINT8* u8Buffer, UINT32 u32MemAddress, UINT16 u16Size)
{
    ApiLlCopyBuffer(u8Buffer,(UINT8*)u32MemAddress, u16Size);
    return (INT16)u16Size;
}

