
/*****************************************************************************
File Name   :  test_no_gdb.c

Description :  

     Author   :  changyukun

*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif




/*========== ͷ�ļ�==============================================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>





/*========== �ⲿ��������=======================================================================================*/







/*========== �궨��==============================================================================================*/







/*========== ���ݽṹ����======================================================================================*/






/*========== ��������===========================================================================================*/






/*========== ��������===========================================================================================*/

//-------------------------------------------------------------------------------------------------
int hl_task_create(void (*Function)(void* Param), void* Param, pthread_t* Task, int Priority, const char* Name)
{
/*
	����:
		1��Function	: [in] �̺߳���
		2��Param	: [in] ��Ӧ�̺߳����Ĳ���
		3��Task	: [in/out] ���ڱ����߳�ID 
		4��Priority	: [in] �̵߳����ȼ���
		5��Name	: [in] �̵߳�����

	����:
		1��0:�ɹ�  other:ʧ��
		
	˵��:
		1��
*/
	int _err=0;
	pthread_t *_ptid;
	pthread_attr_t _attr;
	struct sched_param  _sparam;

	if(Task==NULL)
	{
		printf("Error : %s -->%s -->line=%d\n",__FILE__,__FUNCTION__,__LINE__);
		return -1;
	}

	printf("hl_task_create: %s !\n",Name);
	pthread_attr_init(&_attr);
	pthread_attr_setschedpolicy(&_attr,SCHED_RR);

	if (Priority < sched_get_priority_min(SCHED_RR))
		Priority = sched_get_priority_min(SCHED_RR);

	if (Priority > sched_get_priority_max(SCHED_RR))
		Priority = sched_get_priority_max(SCHED_RR);

	_sparam.sched_priority = Priority;
	pthread_attr_setschedparam(&_attr,&_sparam);

	_err = pthread_create(Task,&_attr,(void*)Function,(void *)Param);
	if(_err != 0)
	{
		printf("Error : %s -->%s -->line=%d\n",__FILE__,__FUNCTION__,__LINE__);
		
		free(*Task);
		return _err;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
static void pthread_fun_1(void* param)
{
	while(1)
	{
		printf("----pthread_fun_1------\n");
		sleep(4);

		#if 0 // test segment fault
		{
			char* buf=NULL;
			sprintf(buf, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			printf("%s\n",buf);
		}
		#endif
	}
}

//-------------------------------------------------------------------------------------------------
static void pthread_fun_2(void* param)
{
	while(1)
	{
		printf("----pthread_fun_2------\n");
		sleep(1);
	}
}


//-------------------------------------------------------------------------------------------------
int main()
{
	pthread_t Task_p_1, Task_p_2;

	//int s32Ret=0;
	//hl_task_t* s_av_thread = NULL; 
	//static int hl_av_comm_init_execed = 0;


	printf("99999999999999999999999999999999999999999999999999999999999000\n");
	return 0;

	dump_init();

	//s32Ret = hl_task_create(pthread_fun_1, NULL, &s_av_thread, 60, "pthread_fun_1", (100 * 1024), NULL, NULL);
	//if (s32Ret !=0)
	if (hl_task_create((void(*)(void *))pthread_fun_1, NULL, &Task_p_1, 60, "pthread_fun_1")!= 0)
	{
		printf("Error : %s -->%s -->line=%d\n",__FILE__,__FUNCTION__,__LINE__);
		return 0;
	}

	//s32Ret = hl_task_create(pthread_fun_2, NULL, &s_av_thread, 60, "pthread_fun_2", (100 * 1024), NULL, NULL);
	//if (s32Ret !=0)
	if (hl_task_create((void(*)(void *))pthread_fun_2, NULL, &Task_p_2, 60, "pthread_fun_2")!= 0)
	{
		printf("Error : %s -->%s -->line=%d\n",__FILE__,__FUNCTION__,__LINE__);
		return 0;
	}

	while(1)
		sleep(10);
	
	return 0;
}









#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 

