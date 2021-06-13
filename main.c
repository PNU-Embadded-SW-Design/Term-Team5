/*
 * main.c
 *
 *  Created on: 2014. 11. 13.
 *      Author: team04
 */

#include "lcd.h"

static void LCD_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*DB00~DB16*/
	GPIO_InitStructure.GPIO_Pin = GPIO_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* LCD_RS  LCD_WR  LCD_RD*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* LCD_CS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

 int main(void)
{
	SystemInit();            
	LCD_Init();
	LCD_Configuration();
        
	u8 str[] = "OK";
        

	LCD_Clear(WHITE);
        while(1)
        {
	LCD_ShowString(10, 10, str, BLACK, WHITE);
	LCD_DrawRectangle(50, 50, 100, 100);
        }
}

