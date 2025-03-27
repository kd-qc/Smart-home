/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  user_common.c
  *Author:  SIRI
  *Version: v1.0.1.202211215
  *Date:  20221/12/15
  *Description:  
  *Others:  
  *Function List:  
  ||主要函数列表，每条记录应包含函数名及功能简要说明||
     1.…………
     2.…………
  *History:  
  |修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介||
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/
#include "user_common.h"

/*--------------------------------------------------------------------------------*/
/*
  *Function:  User_MemCmp
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
u8 User_MemCmp( u8 *pMem1, u8 *pMem2, u16 len)
{
	u16 index;
	for (index=0; index<len; index++)
	{
		if (pMem1[index] != pMem2[index])
			return 1;
	}
	return 0;
}

/*
  *Function:  User_MemCpy
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
u8 User_MemCpy( u8 *pDesMem, u8 *pSrcMem, u16 len)
{
	for (u16 index=0; index<len; index++)
	{
		pDesMem[index] = pSrcMem[index];
	}
	return 0;
}

/*
  *Function:  User_MemCpy
  * Description：  //页面-主页时间处理
  *Input:  p_SysParamHandle, 系统参数句柄
  *Output:  //输出参数的说明
  *Return:  //函数返回值的说明
  *Others:  //其他说明
**/
u8 User_MemSet( u8 *Mem, u8 data, u16 len)
{
	for (u16 index=0; index<len; index++)
	{
		Mem[index] = data;
	}
	return 0;
}

/*--------------------------------------------------------------------------------*/

/****************************************** end file ********************************************/

