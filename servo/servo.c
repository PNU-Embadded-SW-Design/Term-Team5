
#include "servo.h"

void Servo_Write_Angle(u8 Angle)
{
	u16 us;
	us = Angle*1000/180 + 1000;
	TIM_SetCompare1(TIM3, us);	
}


void Servo_Write_us(u16 us)
{
	//TIM3->CCR1 = us;
	TIM_SetCompare1(TIM3, us);
}


void TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM3 clock enable */

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // ∏¥”√Õ∆ÕÏ ‰≥ˆ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void TIM3_Mode_Config(u16 CCR1_Val)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


//	u16 CCR1_Val = 1000;        

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 20000-1;       
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	    
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

void Servo_Angle_Init(u8 Angle)
{
	u16 us;
	us = Angle*1000/180 + 1000;
	TIM3_GPIO_Config();
	TIM3_Mode_Config(us);	
}

void Servo_us_Init(u8 us)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config(us);	
}
