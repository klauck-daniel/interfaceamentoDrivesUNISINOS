#ifndef __USER_5110_H_
#define __USER_5110_H_

#include "main.h"
#include "stm32f1xx_hal.h" // trocar o include conforme a familia stm32f0xx_hal.h para o M0 e stm32f3xx_hal.h para o M4

extern SPI_HandleTypeDef hspi1; // Usar o mesmo nome da struct utilizada na config do SPI utilizado
extern SPI_HandleTypeDef hspi2; // Usar o mesmo nome da struct utilizada na config do SPI utilizado

#define LCD1_RESET_PIN LCD1_RST_Pin // Usar o nome do pino de reset configurado.
#define LCD1_RESET_PORT LCD1_RST_GPIO_Port  // Usar o nome da porta de reset configurado.

#define LCD2_RESET_PIN LCD2_RST_Pin // Usar o nome do pino de reset configurado.
#define LCD2_RESET_PORT LCD2_RST_GPIO_Port  // Usar o nome da porta de reset configurado.

#define LCD1_CE_PIN LCD1_CE_Pin // Usar o nome do pino de chip enable configurado
#define LCD1_CE_PORT LCD1_CE_GPIO_Port // Usar o nome da porta de chip enable configurado

#define LCD2_CE_PIN LCD2_CE_Pin // Usar o nome do pino de chip enable configurado
#define LCD2_CE_PORT LCD2_CE_GPIO_Port // Usar o nome da porta de chip enable configurado

#define LCD1_DC_PIN LCD1_DC_Pin // Usar o nome do pino de data/comando configurado
#define LCD1_DC_PORT LCD1_DC_GPIO_Port // Usar o nome da porta de data/comando configurado

#define LCD2_DC_PIN LCD2_DC_Pin // Usar o nome do pino de data/comando configurado
#define LCD2_DC_PORT LCD2_DC_GPIO_Port // Usar o nome da porta de data/comando configurado

#define LCD1_SPI_INTERFACE hspi1 // usar a struct da variavel extern
#define LCD2_SPI_INTERFACE hspi2 // usar a struct da variavel extern


void LCD1_Init(void);
void LCD1_Reset(void);
void LCD1_Write_Command(uint8_t cmd);
void LCD1_Write_Data(uint8_t data);
void LCD1_Set_Postion(uint8_t PosX, uint8_t PosY);
void LCD1_Clear(void);
void LCD1_Write_Char(uint8_t ch);
void LCD1_Write_String(uint8_t PosX, uint8_t PosY, char * str);

void LCD2_Init(void);
void LCD2_Reset(void);
void LCD2_Write_Command(uint8_t cmd);
void LCD2_Write_Data(uint8_t data);
void LCD2_Set_Postion(uint8_t PosX, uint8_t PosY);
void LCD2_Clear(void);
void LCD2_Write_Char(uint8_t ch);
void LCD2_Write_String(uint8_t PosX, uint8_t PosY, char * str);

#endif
