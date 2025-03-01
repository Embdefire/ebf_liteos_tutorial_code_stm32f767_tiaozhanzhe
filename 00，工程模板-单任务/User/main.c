/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 全系列 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx.h"

 /* LiteOS 头文件 */
#include "los_sys.h"
#include "los_task.ph"

/* 板级外设头文件 */
#include "bsp_led.h"
#include "core_delay.h"  



/* 定义任务句柄 */
UINT32 Test1_Task_Handle;

/* 函数声明 */
static UINT32 AppTaskCreate(void);
static UINT32 Creat_Test1_Task(void);

static void Test1_Task(void);

extern void BSP_Init(void);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  UINT32 uwRet = LOS_OK;  //定义一个任务创建的返回值，默认为创建成功
	
  BSP_Init();
  
	printf("这是一个[野火]-STM32全系列开发板-LiteOS-SDRAM动态创建单任务实验！\n\n");
	
	/* LiteOS 内核初始化 */
	uwRet = LOS_KernelInit();
	
  if (uwRet != LOS_OK)
  {
		printf("LiteOS 核心初始化失败！失败代码0x%X\n",uwRet);
		return LOS_NOK;
  }

	uwRet = AppTaskCreate();
	if (uwRet != LOS_OK)
  {
		printf("AppTaskCreate创建任务失败！失败代码0x%X\n",uwRet);
		return LOS_NOK;
  }

  /* 开启LiteOS任务调度 */
  LOS_Start();
	
	//正常情况下不会执行到这里
	while(1);
	
}


/*******************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 任务创建，为了方便管理，所有的任务创建函数都可以放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  *************************************************************/
static UINT32 AppTaskCreate(void)
{
	/* 定义一个返回类型变量，初始化为LOS_OK */
	UINT32 uwRet = LOS_OK;

	uwRet = Creat_Test1_Task();
  if (uwRet != LOS_OK)
  {
		printf("Test1_Task任务创建失败！失败代码0x%X\n",uwRet);
		return uwRet;
  }
	return LOS_OK;
}


/******************************************************************
  * @ 函数名  ： Creat_Test1_Task
  * @ 功能说明： 创建Test1_Task任务
  * @ 参数    ：   
  * @ 返回值  ： 无
  ******************************************************************/
static UINT32 Creat_Test1_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;			
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;	

	task_init_param.usTaskPrio = 3;	/* 任务优先级，数值越小，优先级越高 */
	task_init_param.pcName = "Test1_Task";/* 任务名 */
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test1_Task;/* 任务函数入口 */
	task_init_param.uwStackSize = 1024;		/* 堆栈大小 */

	uwRet = LOS_TaskCreate(&Test1_Task_Handle, &task_init_param);/* 创建任务 */
	return uwRet;
}

/******************************************************************
  * @ 函数名  ： Test1_Task
  * @ 功能说明： Test1_Task任务实现
  * @ 参数    ： NULL 
  * @ 返回值  ： NULL
  *****************************************************************/
static void Test1_Task(void)
{
  /* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LED1_TOGGLE;
    printf("任务1运行中,每1000ms打印一次信息\r\n");
		LOS_TaskDelay(1000);		
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
