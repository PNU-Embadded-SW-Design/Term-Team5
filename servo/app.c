/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include <includes.h>
#include <stm32f10x.h>
#include <servo.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include <stdbool.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB          AppTaskStartTCB; 
static  OS_TCB          AppTaskTempSensorTCB; 

static  BSP_STLM75_CFG  AppLM75_Cfg;
static  CPU_INT16S      AppTempSensor;           /* Temperature at the sensor                          */
static  CPU_BOOLEAN     AppTempSensorOverTemp;

static  CPU_INT16S      AppTempSensorDeg;
static  CPU_BOOLEAN     AppDegF_DegC_Sel;

/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK         AppTaskStartStk[APP_TASK_START_STK_SIZE];

static  CPU_STK         AppTaskTempSensorStk[APP_TASK_TEMP_SENSOR_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskCreate     (void);
static  void  AppTaskStart      (void *p_arg);

static  void  AppTaskTempSensor (void *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/
void Motor_Init(void);
void Delay(void);

void Delay(void) {
   int i =0;
   for (i = 0; i < 2000000; i++) {}
}

// Port PB9 or PB7
void Motor_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    int PrescalerValue;
    int SystemCoreClock = 72000000; // uint32_t SystemCoreClock = 72000000;
    
    
    
    PrescalerValue = (SystemCoreClock / 1000000) - 1; // PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1; 
    TIM_TimeBaseStructure.TIM_Period = 20000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}
/*
// Open -> 0
// Close -> 270

*/
void openDoor(){
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1750;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 700;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
}

void closeDoor() {
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1350;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 1650;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
}

void Sanitize() {
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 1000;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
}




int  main (void)
{
    //Servo start
    /*
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
      
	
    
    Sanitize();
    
    openDoor();
    Delay();
    closeDoor();
    
    
    
    OS_ERR  err;


    BSP_IntDisAll();                                            /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */

    OSSchedRoundRobinCfg((CPU_BOOLEAN)DEF_TRUE, 
                         (OS_TICK    )10,
                         (OS_ERR    *)&err);
    
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR )AppTaskStart, 
                 (void       *)0,
                 (OS_PRIO     )APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
    
    
    
    
    
    
    
    
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;
    
    

   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                                 */

    CPU_Init();

    cpu_clk_freq = BSP_CPU_ClkFreq();
    cnts         = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;/* Determine nbr SysTick increments                         */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running                */
#endif

    CPU_IntDisMeasMaxCurReset();
    
    AppTaskCreate();                                            /* Create application tasks                                 */

    BSP_LED_Off(0);
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.           */
        BSP_LED_Toggle(1);
        OSTimeDlyHMSM(0, 0, 0, 250, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &err);
    }
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  err;
    

    
    OSTaskCreate((OS_TCB     *)&AppTaskTempSensorTCB, 
                 (CPU_CHAR   *)"App Temp Sensor Start",
                 (OS_TASK_PTR )AppTaskTempSensor, 
                 (void       *)0,
                 (OS_PRIO     )APP_TASK_TEMP_SENSOR_PRIO,
                 (CPU_STK    *)&AppTaskTempSensorStk[0],
                 (CPU_STK_SIZE)APP_TASK_TEMP_SENSOR_STK_SIZE / 10,
                 (CPU_STK_SIZE)APP_TASK_TEMP_SENSOR_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
}


/*
*********************************************************************************************************
*                                          AppTaskTempSensor()
*
* Description : Monitors the STLM75 Sensor.
*
* Argument(s) : p_arg       Argument passed to 'AppTaskTempSensor()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a Task.
*
* Note(s)     : none.
*********************************************************************************************************
*/


static  void  AppTaskTempSensor  (void *p_arg)
{
    OS_ERR      err;
    

    BSP_STLM75_Init();                                                    /* Initlize the STLM75 Sensor              */
                                                                          
    AppLM75_Cfg.FaultLevel    = (CPU_INT08U )BSP_STLM75_FAULT_LEVEL_1;    /* Configure The sensor                    */
    AppLM75_Cfg.HystTemp      = (CPU_INT16S ) 1;
    AppLM75_Cfg.IntPol        = (CPU_BOOLEAN)BSP_STLM75_INT_POL_HIGH;
    AppLM75_Cfg.Mode          = (CPU_BOOLEAN)BSP_STLM75_MODE_INTERRUPT;
    AppLM75_Cfg.OverLimitTemp = (CPU_INT16S )88;

    while (DEF_TRUE) {                                                    /*  Sense the temperature every 100 ms     */
        BSP_LED_Toggle(3);
        BSP_STLM75_TempGet(BSP_STLM75_TEMP_UNIT_FAHRENHEIT, 
                           &AppTempSensor);
        
        
        if (AppDegF_DegC_Sel == 0) {
            AppTempSensorDeg = AppTempSensor;
        } else {
            AppTempSensorDeg = AppTempSensor * 5 / 8 - 32;
        }
        (void)&AppTempSensorDeg;
        BSP_STLM75_CfgSet(&AppLM75_Cfg);
        AppTempSensorOverTemp = BSP_StatusRd(1);
        (void)&AppTempSensorOverTemp;
        OSTimeDlyHMSM(0, 0, 0, 500,
                      OS_OPT_TIME_HMSM_STRICT, 
                      &err);
    }
}
        
