
/*****************************************************************************
File Name   :  test_app_a_1_c++.cpp

Description :  

     Author   :  changyukun

*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif




/*========== 头文件==============================================================================================*/
#include <stdio.h>
#include <stdlib.h>







/*========== 外部变量引用=======================================================================================*/






/*========== 宏定义==============================================================================================*/






/*========== 数据结构定义======================================================================================*/
class App_a_CwnApp1
{
public:
	App_a_CwnApp1();
	int InitInstance1();

};





/*========== 变量定义===========================================================================================*/
App_a_CwnApp1 app_a_theApp1;			






/*========== 函数实现===========================================================================================*/
//-------------------------------------------------------------------------------------------------
App_a_CwnApp1::App_a_CwnApp1()
{
	printf("-------> App_a_CwnApp1::App_a_CwnApp1() \n");
}
//-------------------------------------------------------------------------------------------------
int App_a_CwnApp1::InitInstance1()
{
	printf("-------> App_a_CwnApp1::InitInstance1() \n");
	return 0;
}




//-------------------------------------------------------------------------------------------------
void app_a_1_init_cpp(void)
{
	printf("********** app_a_1_init_cpp *********************\n");
	app_a_theApp1.InitInstance1();
}







#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 


