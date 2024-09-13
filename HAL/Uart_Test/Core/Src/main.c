/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rom_communication.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t rx_data[42];
struct ROM_COMMUNICATION receive_data = {0};
struct ROM_COMMUNICATION transmit_data = {0};
struct e1234567_status e_leds_status = {0};
uint8_t t1 = -40;
uint8_t t2 = 50;
uint32_t t3 = -40434;
uint32_t t4 = 6029372;
uint8_t t5 = 12;
uint8_t t6 = -19;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char *pend; char *pend1; char *pend2; char *pend3;char *pend4;
	char *pend5; char *pend6; char *pend7;char *pend8;char *pend9;
	int16_t rar =  strtol(rx_data, &pend, 10);
	int16_t lar =  strtol(pend , &pend1, 10);
	int32_t rec =  strtol(pend1, &pend2, 10);
	int32_t lec =  strtol(pend2, &pend3, 10);
	int16_t rdr =  strtol(pend3, &pend4, 10);
	int16_t ldr =  strtol(pend4, &pend5, 10);
	int16_t free=  strtol(pend5, &pend6, 10);
	int16_t e123=  strtol(pend6, &pend7, 10);
	int16_t volt= (strtol(pend7, &pend8, 10)); //  & 0xff;
	float  amp  =  strtof(pend8, &pend9);
	int8_t checksum=(strtol(pend9, NULL, 10)) & 0xff;  //

	//printf("%s \r\n",rx_data);
	printf("rar: %d\r\n", rar);
	printf("lar: %d\r\n", lar);
	printf("rec: %d\r\n", rec);
	printf("lec: %d\r\n", lec);

	HAL_UART_Receive_DMA(&huart3,rx_data,26);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//int _write(int file, char *data, int len)
//{
//	for(int i = 0; i < len; i++)
//	{
//		ITM_SendChar(data[i]);
//	}
//	return len;
//}
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
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Receive_DMA(&huart3,rx_data,42);
  HAL_TIM_Base_Start_IT(&htim9);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	/*	HAL_GPIO_WritePin(GPIOD,Green_Pin,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOD,Green_Pin,GPIO_PIN_RESET);

		HAL_Delay(1000);*/
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// printf debug function အသုံးပြုနိုင်ရန်
int _write(int file, char *ptr, int len)
{
  (void)file;

  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
   ITM_SendChar(*ptr++);
  }
  return len;
}
//Program တစ်ခုလုံးတွက် Timer9 Interrupt
void TIM1_BRK_TIM9_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 0 */
	if(TIM9->SR & TIM_SR_UIF)
		{
			/*char tx_data[100]; // Buffer to hold the string representation of the integer
			sprintf(tx_data, "%d %d %ld %ld %d \r\n", t1, t2, t3, t4, t5); // Convert integer to string
			HAL_UART_Transmit_IT(&huart3, tx_data, 50);
			printf("hello\n");
			printf("TR_Data: %s\r\n",tx_data);*/
		transmit_data.right_actual_rpm = -3452;
		transmit_data.left_actual_rpm = 4353;
		transmit_data.right_encoder_count = -4536762;
		transmit_data.left_encoder_count = 4875743;
		transmit_data.free = 4;
		transmit_data.e1234567 = 8;
			encodeBuffer(&transmit_data.right_actual_rpm, &transmit_data.left_actual_rpm,
					&transmit_data.right_encoder_count, &transmit_data.left_encoder_count,
					&transmit_data.free, &transmit_data.e1234567,
					&transmit_data.volt, &transmit_data.ampere,
					transmit_data.buffer );

			HAL_UART_Transmit_IT(&huart3,transmit_data.buffer,26);
			HAL_UART_Receive_DMA(&huart3,rx_data,42);
			printf("%d\r\n",transmit_data.right_actual_rpm);
			printf("%d\r\n",transmit_data.left_actual_rpm);
			HAL_GPIO_TogglePin(GPIOD,Green_Pin);
		}
  /* USER CODE END TIM1_BRK_TIM9_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim9);
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM9_IRQn 1 */
}

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
