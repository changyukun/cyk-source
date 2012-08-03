
/*****************************************************************************
File Name   :  test_sleep_time.c

Description :  �������ʵ��һ���߳�ѭ����������ȶ�������ʱ�䣬���߳�ÿ10  ms ��һȦ

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
typedef unsigned long long uint64_t;





/*========== ��������===========================================================================================*/
			






/*========== ����ʵ��===========================================================================================*/

//-------------------------------------------------------------------------------------------------
static uint64_t get_cur_time(void)
{
/*
	����:
		1��
		
	����:
		1��

	˵��:
		1�����ڻ�ȡϵͳ�ĵ�ǰʱ��
*/
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC,&ts)<0)
	{
		printf("clock_gettime() doesn't work: %s",strerror(errno));
	}
	return (ts.tv_sec*1000LL) + (ts.tv_nsec/1000000LL);

}

//-------------------------------------------------------------------------------------------------
static void sleepMs(int ms)
{
/*
	����:
		1��
		
	����:
		1��

	˵��:
		1��sleep ����
*/
	struct timespec ts;
	ts.tv_sec=0;
	ts.tv_nsec=ms*1000000LL;
	nanosleep(&ts,NULL);
}

//-------------------------------------------------------------------------------------------------
void pthread_fun_test(void* param)
{
#define TIME_INTERVALE	10

	uint64_t realtime=0, time1=0, time2=0;
	static uint64_t time_next=0;
	static uint64_t time_org=0;
	long long diff;

	time_org = get_cur_time();
		
	while(1)
	{
		time_next += TIME_INTERVALE;
		while(1)
		{
			realtime = get_cur_time() - time_org;
			diff = time_next -realtime;
			
			if(diff>0)
			{
				//sleepMs(((int)diff)/2);
				usleep((((int)diff)/2)*1000);
			}
			else
			{
				break;
			}
		}

		#if 1  // --- cyk add for test (��ӡ��������ִ�е�ʱ���Ƿ�ΪTIME_INTERVALE ms)
		time1 = get_cur_time();
		diff = time1 - time2;
		time2 = time1;
		if(diff != TIME_INTERVALE)
			printf("-----pthread_fun_test------> %lld\n",diff);
		#endif 
		
	}
	
#undef TIME_INTERVALE
}








#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


