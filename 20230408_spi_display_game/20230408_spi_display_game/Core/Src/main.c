/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char stringBuffer[50];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

int ply_configura = 1;
int ply_adivinha = 2;

int B0 = 0;
int B1 = 0;

int B8 = 0;
int B9 = 0;

bool ply1_ok = false;
bool ply2_ok = false;

int jogada = 1;

int n_configura = 0;
int n_adivinha = 0;
int range = 10;
int compara =0;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */

  LCD1_Init();
  LCD1_Write_String(0,0,"AdvnhAi PLYR 1");

  LCD2_Init();
  LCD2_Write_String(0,0,"AdvnhAi PLYR 2");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)) {
		  B0 = 1;
	  } else {
		  B0 = 0;
	  }

	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)) {
		  B1 = 1;
	  } else {
		  B1 = 0;
	  }

	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)) {
		  B8 = 1;
	  } else {
		  B8 = 0;
	  }

	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)) {
		  B9 = 1;
	  } else {
		  B9 = 0;
	  }



	  if(jogada == 1){

		  if(ply_configura == 1){

		  		  LCD1_Write_String(0,1,"ESCOLHENDO:");
		  		  LCD1_Write_String(0,3,"Escolhe e OK:");

		  		  if(B0 == 0){
		  			  if(B1 == 1){
		  				  if(n_configura < range){
		  					  n_configura++;//faz a leitura e quando apertar ok finaliza
		  				  }
		  				  else{
		  					  n_configura = 0;
		  					  LCD1_Write_String(3,4,"                   " );
		  				  }
		  				  sprintf(stringBuffer,"Numero: %d", n_configura);
		  				  LCD1_Write_String(3,4, stringBuffer );
		  			  }
		  			  HAL_Delay(100);
		  		  }
		  		  if(B0 == 1){
		  			  ply1_ok = true;
		  			  ply_configura = 2;
		  			  B0 = 0;
		  			  HAL_Delay(1000);
		  		  }
		  	  }

		  	  if (ply1_ok == true){
		  		  LCD1_Write_String(0,3, "                        " );
		  		  LCD1_Write_String(0,4, "                        " );

		  		  HAL_Delay(100);

		  		  sprintf(stringBuffer,"Escolhido: %d", n_configura);
		  		  LCD1_Write_String(0,4, stringBuffer );

		  		  HAL_Delay(1000);

		  		  ply1_ok = false;
		  		  compara = compara + 1; //controle para executar a comparação dos valores escolhidos pelos players

		  	  }

		  	  if(ply_adivinha == 2){
		  		  LCD2_Write_String(0,1,"ADIVINHANDO");
		  		  LCD2_Write_String(0,3,"Escolhe e OK:");

		  		  if(B8 == 0){
		  		  			  if(B9 == 1){
		  		  				  if(n_adivinha < range){
		  		  					n_adivinha++;//faz a leitura e quando apertar ok finaliza
		  		  				  }
		  		  				  else{
		  		  					n_adivinha = 0;
		  		  					  LCD2_Write_String(3,4,"                   " );
		  		  				  }
		  		  				  sprintf(stringBuffer,"Numero: %d", n_adivinha);
		  		  				  LCD2_Write_String(3,4, stringBuffer );
		  		  			  }
		  		  			  HAL_Delay(100);
		  		  		  }
		  		  		  if(B8 == 1){
		  		  			  ply2_ok = true;
		  		  			  ply_adivinha = 1;
		  		  			  B8 = 0;
		  		  			  HAL_Delay(1000);
		  		  		  }
		  	  }
		  	  if (ply2_ok == true){
		  	  		  LCD2_Write_String(0,3, "                        " );
		  	  		  LCD2_Write_String(0,4, "                        " );

		  	  		  HAL_Delay(100);

		  	  		  sprintf(stringBuffer,"Escolhido: %d", n_adivinha);
		  	  		  LCD2_Write_String(0,4, stringBuffer );

		  	  		  HAL_Delay(1000);

		  	  		  ply2_ok = false;
		  	  		  compara = compara + 1; //controle para executar a comparação dos valores escolhidos pelos players

		  	  	  }


		  	  if(compara == 2){
		  		  LCD1_Write_String(0,3, "                        " );
		  		  LCD1_Write_String(0,4, "                        " );
		  		  LCD2_Write_String(0,3, "                        " );
		  		  LCD2_Write_String(0,4, "                        " );
		  		  if(n_configura == n_adivinha){
		  			  LCD1_Write_String(0,3, "PLY 2 ACERTOU!" );
		  			  LCD1_Write_String(0,4, "PARABENS PLY2!" );
		  			  LCD2_Write_String(0,3, "PLY 2 ACERTOU!" );
		  			  LCD2_Write_String(0,4, "PARABENS PLY2!" );
		  		  }
		  		  else{
		  			  LCD1_Write_String(0,3, "PLY 2 ERROU!" );
		  			  LCD2_Write_String(0,3, "PLY 2 ERROU!" );
		  		  }

		  		  HAL_Delay(3000);

		  		  LCD1_Write_String(0,1, "                        " );
		  		  LCD1_Write_String(0,2, "                        " );
		  		  LCD1_Write_String(0,3, "                        " );
		  		  LCD1_Write_String(0,4, "                        " );
		  		  LCD2_Write_String(0,1, "                        " );
		  		  LCD2_Write_String(0,2, "                        " );
		  		  LCD2_Write_String(0,3, "                        " );
		  		  LCD2_Write_String(0,4, "                        " );
		  		  n_configura = 0;
		  		  n_adivinha=0;
		  		  compara = 0;
		  		  jogada = 2;
		  		  ply1_ok = false;
		  		  ply2_ok = false;
		  	  }
	  }




	  if(jogada == 2){

		  if(ply_configura == 2){

		  		  LCD2_Write_String(0,1,"ESCOLHENDO:");
		  		  LCD2_Write_String(0,3,"Escolhe e OK:");

		  		  if(B8 == 0){
		  			  if(B9 == 1){
		  				  if(n_configura < range){
		  					  n_configura++;//faz a leitura e quando apertar ok finaliza
		  				  }
		  				  else{
		  					  n_configura = 0;
		  					  LCD2_Write_String(3,4,"                   " );
		  				  }
		  				  sprintf(stringBuffer,"Numero: %d", n_configura);
		  				  LCD2_Write_String(3,4, stringBuffer );
		  			  }
		  			  HAL_Delay(100);
		  		  }
		  		  if(B8 == 1){
		  			  ply2_ok = true;
		  			  ply_configura = 1;
		  			  B8 = 0;
					  HAL_Delay(1000);
		  		  }
		  	  }

		  	  if (ply2_ok == true){
		  		  LCD2_Write_String(0,3, "                        " );
		  		  LCD2_Write_String(0,4, "                        " );

		  		  HAL_Delay(100);

		  		  sprintf(stringBuffer,"Escolhido: %d", n_configura);
		  		  LCD2_Write_String(0,4, stringBuffer );

		  		  HAL_Delay(1000);

		  		  ply2_ok = false;
		  		  compara = compara + 1; //controle para executar a comparação dos valores escolhidos pelos players

		  	  }

		  	  if(ply_adivinha == 1){
		  		  LCD1_Write_String(0,1,"ADIVINHANDO");
		  		  LCD1_Write_String(0,3,"Escolhe e OK:");

		  		  if(B0 == 0){
		  		  			  if(B1 == 1){
		  		  				  if(n_adivinha < range){
		  		  					n_adivinha++;//faz a leitura e quando apertar ok finaliza
		  		  				  }
		  		  				  else{
		  		  					n_adivinha = 0;
		  		  					  LCD1_Write_String(3,4,"                   " );
		  		  				  }
		  		  				  sprintf(stringBuffer,"Numero: %d", n_adivinha);
		  		  				  LCD1_Write_String(3,4, stringBuffer );
		  		  			  }
		  		  			  HAL_Delay(100);
		  		  		  }
		  		  		  if(B0 == 1){
		  		  			  ply1_ok = true;
		  		  			  ply_adivinha = 2;
		  		  			  B0 = 0;
							  HAL_Delay(1000);
		  		  		  }
		  	  }
		  	  if (ply1_ok == true){
		  	  		  LCD1_Write_String(0,3, "                        " );
		  	  		  LCD1_Write_String(0,4, "                        " );

		  	  		  HAL_Delay(100);

		  	  		  sprintf(stringBuffer,"Escolhido: %d", n_adivinha);
		  	  		  LCD1_Write_String(0,4, stringBuffer );

		  	  		  HAL_Delay(1000);

		  	  		  ply1_ok = false;
		  	  		  compara = compara + 1; //controle para executar a comparação dos valores escolhidos pelos players

		  	  	  }


		  	  if(compara == 2){
		  		  LCD1_Write_String(0,3, "                        " );
		  		  LCD1_Write_String(0,4, "                        " );
		  		  LCD2_Write_String(0,3, "                        " );
		  		  LCD2_Write_String(0,4, "                        " );
		  		  if(n_configura == n_adivinha){
		  			  LCD1_Write_String(0,3, "PLY 1 ACERTOU!" );
		  			  LCD1_Write_String(0,4, "PARABENS PLY1!" );
		  			  LCD2_Write_String(0,3, "PLY 1 ACERTOU!" );
		  			  LCD2_Write_String(0,4, "PARABENS PLY1!" );
		  		  }
		  		  else{
		  			  LCD1_Write_String(0,3, "PLY 1 ERROU!" );
		  			  LCD2_Write_String(0,3, "PLY 1 ERROU!" );
		  		  }

		  		  HAL_Delay(3000);

		  		  LCD1_Write_String(0,1, "                        " );
		  		  LCD1_Write_String(0,2, "                        " );
		  		  LCD1_Write_String(0,3, "                        " );
		  		  LCD1_Write_String(0,4, "                        " );
		  		  LCD2_Write_String(0,1, "                        " );
		  		  LCD2_Write_String(0,2, "                        " );
		  		  LCD2_Write_String(0,3, "                        " );
		  		  LCD2_Write_String(0,4, "                        " );
		  		  n_configura = 0;
		  		  n_adivinha=0;
		  		  compara = 0;
		  		  jogada = 1;
		  		  ply1_ok = false;
				  ply2_ok = false;
		  	  }
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD1_RST_Pin|LCD1_CE_Pin|LCD1_DC_Pin|LCD2_DC_Pin
                          |LCD2_CE_Pin|LCD2_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD1_RST_Pin LCD1_CE_Pin LCD1_DC_Pin LCD2_DC_Pin
                           LCD2_CE_Pin LCD2_RST_Pin */
  GPIO_InitStruct.Pin = LCD1_RST_Pin|LCD1_CE_Pin|LCD1_DC_Pin|LCD2_DC_Pin
                          |LCD2_CE_Pin|LCD2_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_B0_Pin BTN_B1_Pin BTN_B8_Pin BTN_B9_Pin */
  GPIO_InitStruct.Pin = BTN_B0_Pin|BTN_B1_Pin|BTN_B8_Pin|BTN_B9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
