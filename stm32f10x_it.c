/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.5.0
 * @date    08-April-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "hw_config.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include <string.h>

uint8_t buffer[1024];
int j;

/* public variable*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
 * @name	void EXTI9_5_IRQHandler(void)
 * @brief	Õ‚≤ø÷–∂œœÏ”¶∫Ø ˝£¨’‚¿ÔÕ‚≤øΩ”USER1º¸
 * @param  None
 * @retval	None
 */

void EXTI2_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line2) != RESET) {
		/*
		EXTI_ClearITPendingBit(EXTI_Line0);
		LEDUp();
		 */
		int i;
		//	LED4
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x80;
		}
		(*(volatile unsigned*)0x40011410) = 0x80;
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x80;
		}
		//	LED3
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x10;
		}
		(*(volatile unsigned*)0x40011410) = 0x10;
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x10;
		}
		//	LED2
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x8;
		}
		(*(volatile unsigned*)0x40011410) = 0x8;
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x8;
		}
		//	LED1
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x4;
		}
		(*(volatile unsigned*)0x40011410) = 0x4;

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI9_5_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		/*
		EXTI_ClearITPendingBit(EXTI_Line0);
		LEDUp();
		 */
		int i;
		//	LED1
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x4;
		}
		(*(volatile unsigned*)0x40011410) = 0x4;

		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x4;
		}

		//	LED2
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x8;
		}

		(*(volatile unsigned*)0x40011410) = 0x8;

		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x8;
		}

		//	LED3
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x10;
		}
		(*(volatile unsigned*)0x40011410) = 0x10;

		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011414) = 0x10;		//	14¥¬ reset«œ¥¬ ∫Œ∫–
		}

		//	LED4
		for(i=0;i<500000;i++){
			(*(volatile unsigned*)0x40011410) = 0x80;
		}
		(*(volatile unsigned*)0x40011410) = 0x80;

		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

/*
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
USARTx->DR = (Data & (uint16_t)0x01FF);
}
 */

void SerialPutChar(uint8_t c)
{
	USART_SendData(USART1, c);
	/*
	while(1){
	uint16_t test = (*(volatile unsigned *)USART1_BASE);
	test = test & USART_CR1_TXEIE;
	if(test != USART_CR1_TXEIE)
	break;
	}*/
}

void Serial_PutString(const uint8_t *s)
{
	while (*s != '\0')
	{
		SerialPutChar(*s);
		for(int i = 0; i < 100000; ++i);
		s ++;
	}
}

void SerialPutChar2(uint8_t c)
{
	USART_SendData(USART2, c);
	/*
	while(1){
	uint16_t test = (*(volatile unsigned *)USART1_BASE);
	test = test & USART_CR1_TXEIE;
	if(test != USART_CR1_TXEIE)
	break;
	}*/
}

void Serial_PutString2(const uint8_t *s)
{
	while (*s != '\0')
	{
		SerialPutChar2(*s);
		for(int i = 0; i < 100000; ++i);
		s ++;
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) {
		Serial_PutString("Thu Team4 UART_TEST");
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}

void USART1_IRQHandler(void)
{
	char receive_data;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//	µ•¿Ã≈Õ ∑π¡ˆΩ∫≈Õø° µ•¿Ã≈Õ∞° µÈæÓø‘¥¬ ¡ˆ »Æ¿Œ
	{
		//s = USART_ReceiveData(USART1) & 0xFF;
		receive_data = USART_ReceiveData(USART1) & 0xFF;
		USART_SendData(USART1, receive_data);
		USART_SendData(USART2, receive_data);

		//USART_SendData(USART1, receive_data);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

//USART2 Bluetooth control
void USART2_IRQHandler(void)
{
	char receive_data;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	//	µ•¿Ã≈Õ ∑π¡ˆΩ∫≈Õø° µ•¿Ã≈Õ∞° µÈæÓø‘¥¬ ¡ˆ »Æ¿Œ
	{
		//s = USART_ReceiveData(USART1) & 0xFF;
		receive_data = USART_ReceiveData(USART2) & 0xFF;
		USART_SendData(USART1, receive_data);

		//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );

		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}

}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
