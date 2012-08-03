
/*****************************************************************************
File Name   :  cyk_find_mountdir.c

Description :  

     Author   :  changyukun

*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif



/*========== ͷ�ļ�==============================================================================================*/
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <unistd.h>
#include <string.h>






/*========== �ⲿ��������=======================================================================================*/






/*========== �궨��==============================================================================================*/






/*========== ���ݽṹ����======================================================================================*/






/*========== ��������===========================================================================================*/
			






/*========== ����ʵ��===========================================================================================*/

//-------------------------------------------------------------------------------------------------
int findUdiskDir(char* uMountDir, int len, int* uNum)
{
/*
	����:
		1��uMountDir	: �������ڷ��ػ�õ�Ŀ¼���ڴ�ռ�
		2��len			: ����uMountDir buffer �ĳ���
		3��uNum		: ���ڷ��ػ�õ���Ŀ¼�ĸ���
		
	����:
		1��0:�ɹ�   1:������ڴ�ռ䲻��   -1:ʧ��
		
	˵��:
		1����õ�������Ŀ¼֮���ú�INTERVAL ��������ݸ���
*/
	#define XXX_DATA_LEN 	1024
	#define CONDITION 		"/dev/sd"	
	#define INTERVAL			" "

	FILE* file = NULL;  
	char buf[XXX_DATA_LEN];
	char* p = NULL;
	int i = 0, num = 0, result = 0;

	if(NULL == uMountDir || len <= 0)
	{
		result = -1;
		goto out;
	}

	file = popen( "fdisk -l", "r" ); 

	if(file == NULL)
	{
		result = -1;
		goto out;
	}

	memset(uMountDir, 0, len);

	while(1)
	{
		memset(buf, 0, XXX_DATA_LEN);

		if(!(fgets(buf, XXX_DATA_LEN, file)))
			break;
		
		//printf("-----> %s",buf);

		if(strncmp(buf, CONDITION, strlen(CONDITION)) == 0)
		{
			i = 0;
			for(p = strtok(buf," \t\r\n"); p; p = strtok(NULL," \t\r\n"))
			{
				if(i == 0)
				{
					if(0 != access(p,F_OK))
						break;
				}
				else if(i == 2)
				{
					if(num == 0)
					{
						len = len -strlen(p);
						if(len > 0)
							sprintf(uMountDir, p);
						else
						{
							result = 1;
							goto out;
						}
					}
					else
					{
						len = len-strlen(p) - strlen(INTERVAL);
						if(len > 0)
						{
							strcat(uMountDir, INTERVAL);
							strcat(uMountDir, p);
						}
						else
						{
							result = 1;
							goto out;
						}
					}
					num++;
					//printf("----> %s\n",p);
				}
				i++;
			}
		}
	}
	pclose(file); 

out:

	if(NULL != uNum)
		*uNum = num;

	#undef  XXX_DATA_LEN
	#undef  CONDITION
	#undef  INTERVAL
	
	return result;
}










#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


