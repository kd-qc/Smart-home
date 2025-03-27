/*********************************************************************************
  *Copyright(C),2020-2021, SIRI
  *FileName:  user_common.c
  *Author:  SIRI
  *Version: v1.0.1.202211215
  *Date:  20221/12/15
  *Description:  
  *Others:  
  *Function List:  
  ||��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��||
     1.��������
     2.��������
  *History:  
  |�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼��޸����ݼ��||
     1.Date:
       Author:
       Modification:
     2.��������
**********************************************************************************/
#include "user_common.h"

/*--------------------------------------------------------------------------------*/
/*
  *Function:  User_MemCmp
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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
  * Description��  //ҳ��-��ҳʱ�䴦��
  *Input:  p_SysParamHandle, ϵͳ�������
  *Output:  //���������˵��
  *Return:  //��������ֵ��˵��
  *Others:  //����˵��
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

