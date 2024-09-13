/* USER CODE BEGIN Header */
/*
 * rom_communication.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Pyae Soan Aung
 */
/* Macros --------------------------------------------------------------------*/
/* ဒီထဲက COMMUNICATION နည်း လမ်း ၃ခုထဲက တစ်ခု ကို ရွေးပါ။ */
//#define COMMUNICATION_METHOD_WIFI
//#define COMMUNICATION_METHOD_UART
#define COMMUNICATION_METHOD_USB

/* ဒီထဲက Motor Driver COMMUNICATION နည်း လမ်း ၂ ခုထဲက တစ်ခု ကို ရွေးပါ။ */
//#define MOTOR_DRIVER_UART
#define MOTOR_DRIVER_CAN

/* CAN အတွက် */
//#define USE_PDO 1
#define CAN_DEBUG 1

/* Serial Wire Viewer အတွက် */
#define ROM_SWV_DEBUG

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include <string.h>
#include "ROM_VARIABLES.h"
#include "ROM_LSDB4830_CAFC.h"

#ifdef COMMUNICATION_METHOD_USB
	#include "usbd_cdc_if.h"
#elif defined(COMMUNICATION_METHOD_UART)
	#define UART_DEBUG
	#define UART_RX_BUFFER_SIZE 42
	uint8_t uart3_rx_data[UART_RX_BUFFER_SIZE];
	uint8_t _data[UART_RX_BUFFER_SIZE];
#endif

#include "rom_communication.h"
struct ROM_COMMUNICATION receive_data = {0};
struct ROM_COMMUNICATION transmit_data = {0};
struct e1234567_status e_leds_status = {0};
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// 	CAN ERROR = BLUE LED
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* 10Hz, 50Hz, 100Hz သုံးမျိုး သုံးလို့ ရပါတယ်။ */
int main_loop_Hz = 10; // 10Hz

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef ROM_SWV_DEBUG
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
	int fputc(int ch, FILE *f) {
		ITM_SendChar(ch);
		return ch;
	}
#endif

void estop(void){};
void led(void){};
void volt_ampere(void){};
void structure_update(void)
{
	// data သည် CAN BUS က လာမယ်။
	//transmit_data.right_actual_rpm = right_actual_rpm;
	//transmit_data.left_actual_rpm  = left_actual_rpm;
	//transmit_data.right_actual_rpm = right_desire_rpm;
	//transmit_data.left_actual_rpm  = left_desire_rpm;
	transmit_data.right_actual_rpm = 0;
	transmit_data.left_actual_rpm  = 0;

	// data သည် CAN BUS က လာမယ်။
	transmit_data.right_encoder_count = right_actual_position;
	transmit_data.left_encoder_count = left_actual_position;
	transmit_data.right_encoder_count = 999;
	transmit_data.left_encoder_count = 0;

	/* No Need to update desire rpms,
	because it is decoded and implemented in USB_RECEIVE_CALLBACK() */
	//transmit_data.right_desire_rpm = right_desire_rpm;
	//transmit_data.left_desire_rpm  = left_desire_rpm;

	transmit_data.free = 0;

//	uint8_t lower_byte =
//	(uint8_t)(e_leds_status.estop_status << 7 ) +
//	(uint8_t)(e_leds_status.led1_status  << 6 ) +
//	(uint8_t)(e_leds_status.led1_status  << 5 ) +
//	(uint8_t)(e_leds_status.led1_status  << 4 ) +
//	(uint8_t)(e_leds_status.led1_status  << 3 ) +
//	(uint8_t)(e_leds_status.led1_status  << 2 ) +
//	(uint8_t)(e_leds_status.led1_status  << 1 ) +
//	(uint8_t)(e_leds_status.led1_status  << 0 );

	transmit_data.e1234567 = 0; //lower_byte;

	transmit_data.volt = 0;		// 1B
	transmit_data.ampere = -3.1415;  // 4B
};
void ROM_variables_init(void)
{
	speed_limit = 50;

	/*for(int x = 0; x<100 ; x++)
	{
		usb_tx_buf[x] = 0;
		//usb_rx_buf[x] = 0;
	} */

	right_actual_rpm = 0;
	left_actual_rpm = 0;
	
	right_actual_position = 0; // rec
	left_actual_position  = 0;// lec

	right_desire_rpm = 0;
	left_desire_rpm = 0;

	transmit_data.free = 0;
	transmit_data.e1234567 = 0;

	transmit_data.volt = 0;
	transmit_data.ampere = 0;
}

#ifdef MOTOR_DRIVER_CAN
	void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{ /* Right */
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, CAN_rxData);
	
	
	if( rxHeader.StdId == 0x181) 
	{
		#ifdef USE_PDO
		int32_t tmp_rpm = CAN_rxData[3] << 24;
		tmp_rpm = tmp_rpm + (CAN_rxData[2] << 16);
		tmp_rpm = tmp_rpm + (CAN_rxData[1] << 8 );
		tmp_rpm = tmp_rpm + (CAN_rxData[0] << 0); // read page 17-----------------------------
		right_actual_rpm = tmp_rpm/1000;

		int32_t temp_pos = CAN_rxData[7] << 24;
		temp_pos = temp_pos + (CAN_rxData[6] << 16);
		temp_pos = temp_pos + (CAN_rxData[5] << 8 );
		temp_pos = temp_pos+ (CAN_rxData[4] << 0);
		right_actual_position = temp_pos;
		#endif
	}
	
	else {
	
		/* 0x581 Success */
		if( CAN_rxData[0] == RECEIVE_SUCCESS ) 
		{
			#ifdef CAN_DEBUG
			HAL_GPIO_TogglePin(ORANGE_LED_GPIO_Port, ORANGE_LED_Pin);
			#endif
			//printf("MOTOR DRIVER RESPONSE : OK!\r\n");
			
		}
		
		/* Manually get RPM */
		#ifndef USE_PDO
		else if ( CAN_rxData[0] == RECEIVE_TWO_BYTE )
		{
			if( CAN_rxData[1]==ACTUAL_SPEED_RPM_1Byte && CAN_rxData[2]==ACTUAL_SPEED_RPM_2Byte && CAN_rxData[3]==ACTUAL_SPEED_RPM_3Byte )
			{
				int16_t temp = (  CAN_rxData[5]<<8 ) + (CAN_rxData[4]<<0);
				right_actual_rpm = temp;
				
				//Trigger for Left Actual
				#ifdef CAN_DEBUG
				HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
				#endif
				getActualRpmLeft(&hcan1);
			}
		}
		#endif
		/* Error */
		else if ( CAN_rxData[0] == RECEIVE_ERROR ) 
		{ 
			CAN_Error_Handler(); 
			//printf("MOTOR DRIVER RESPONSE : Error!\r\n");
		} 
	}
}
	void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{ /* Left */
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &rxHeader, CAN_rxData);
	
	if( rxHeader.StdId == 0x182) 
	{
		#ifdef USE_PDO
		int32_t tmp_rpm = CAN_rxData[3] << 24;
		tmp_rpm = tmp_rpm + (CAN_rxData[2] << 16);
		tmp_rpm = tmp_rpm + (CAN_rxData[1] << 8 );
		tmp_rpm = tmp_rpm + (CAN_rxData[0] << 0); // read page 17-----------------------------
		left_actual_rpm = (tmp_rpm/1000)*-1;
		
		
		int32_t temp_pos = CAN_rxData[7] << 24;
		temp_pos = temp_pos + (CAN_rxData[6] << 16);
		temp_pos = temp_pos + (CAN_rxData[5] << 8 );
		temp_pos = temp_pos+ (CAN_rxData[4] << 0);
		left_actual_position = temp_pos * -1;
		#endif
	}
	
	else {
		/* Success */
		if( CAN_rxData[0] == RECEIVE_SUCCESS ) 
		{
			#ifdef CAN_DEBUG
			HAL_GPIO_TogglePin(ORANGE_LED_GPIO_Port, ORANGE_LED_Pin);
			#endif
			//printf("MOTOR DRIVER RESPONSE : OK!\r\n");
			
		}
		
		/* Manually get RPM */
		#ifndef USE_PDO
		else if ( CAN_rxData[0] == RECEIVE_TWO_BYTE )
		{
			if( CAN_rxData[1]==ACTUAL_SPEED_RPM_1Byte && CAN_rxData[2]==ACTUAL_SPEED_RPM_2Byte && CAN_rxData[3]==ACTUAL_SPEED_RPM_3Byte )
			{
				int16_t temp = (  CAN_rxData[5]<<8 ) + (CAN_rxData[4]<<0);
				left_actual_rpm = temp * -1;
			}
		}
		#endif
		/* Error */
		else if ( CAN_rxData[0] == RECEIVE_ERROR ) 
		{ 
			CAN_Error_Handler(); 
			//printf("MOTOR DRIVER RESPONSE : Error!\r\n");
		} 

	}
	
}
#endif

#ifdef COMMUNICATION_METHOD_USB
	void USB_RECEIVE_CALLBACK(uint8_t *buf, uint32_t len)
{    /* assume 30 Bytes */
	// update right_desire_rpm, left_desire_rpm and estop_leds
	//decodeBuffer( buf, &receive_data);
	char * buffer = (char *) buf;
	char *pend; char *pend1; char *pend2; char *pend3;char *pend4;
	char *pend5; char *pend6; char *pend7;char *pend8;char *pend9;

		int16_t rar =  strtol(buffer, &pend, 10);
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

/* YOU SHOULD CKECK CHECKSUM && SHOULD UPDATE STRUCTURE ( LEDs ... ) */
	if( ((rdr+ldr)&0xff) != checksum)
	{
		right_desire_rpm = 0;
		left_desire_rpm = 0;
		#ifdef ROM_SWV_DEBUG
			printf("checksum mismatch Error!");
		#endif
		return;
	}
	right_desire_rpm = rdr;
	left_desire_rpm  = ldr;

	#ifdef ROM_SWV_DEBUG
		//printf("%s\r\n", buf);
		//printf("rar: %d\r\n", receive_data.right_actual_rpm);
		//printf("lar: %d\r\n", receive_data.left_actual_rpm);
		//printf("rec: %ld\r\n", receive_data.right_encoder_count);
		//printf("lec: %ld\r\n", receive_data.left_encoder_count);
		printf(" rdr : %d\r\n", rdr);
		printf(" ldr : %d\r\n", ldr);
		//printf("free: %d\r\n", receive_data.free);
		//printf("e123: %d\r\n", receive_data.e1234567);
		//printf("volt: %d\r\n", receive_data.volt);
		//printf("ampere: %d\r\n", (int)receive_data.ampere);
		printf(" checksum: %d\r\n", checksum);

	#endif
}
	void __ROM_USB_TRANSMIT(void)
{
	//calculate_crc
	encodeBuffer(&transmit_data.right_actual_rpm, &transmit_data.left_actual_rpm,
			&transmit_data.right_encoder_count, &transmit_data.left_encoder_count,
			&transmit_data.free, &transmit_data.e1234567,
			&transmit_data.volt, &transmit_data.ampere,
			transmit_data.buffer );

    CDC_Transmit_FS(transmit_data.buffer, 26);
}
#elif defined(COMMUNICATION_METHOD_UART)
	void __ROM_UART3_TRANSMIT(void)
{
	//calculate_crc
	encodeBuffer(&transmit_data.right_actual_rpm, &transmit_data.left_actual_rpm,
			&transmit_data.right_encoder_count, &transmit_data.left_encoder_count,
			&transmit_data.free, &transmit_data.e1234567,
			&transmit_data.volt, &transmit_data.ampere,
			transmit_data.buffer );

	//HAL_UART_Transmit_IT(p_huart2,uart2_tx_data, 10);
	HAL_UART_Transmit_IT(&huart3,transmit_data.buffer, 26);

	#ifdef UART_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif
}
	// Function to Receive UART3 Data
	/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// _data to zero
	memset(_data, 0, sizeof(_data));

	// usb မှာလိုပဲ transmit လုပ်ရင် string of byte array နဲ့ ပို့ပြီး
	// receive လုပ်တဲ့ အခါ string of char array ဖြစ်ပါတယ်။
	memcpy(_data, uart3_rx_data, UART_RX_BUFFER_SIZE*8);
	//char * buffer = (char *) buf;
		char *pend; char *pend1; char *pend2; char *pend3;char *pend4;
		char *pend5; char *pend6; char *pend7;char *pend8;char *pend9;

	// string or not
	int16_t rar =  strtol(_data, &pend, 10);
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

		// if _data[0] == 601
		checkByteRight(_data);
		right_actual_rpm = (array_[7]<<8)+array_[8];

	HAL_UART_Receive_DMA(huart, uart3_rx_data, 26);

	#ifdef UART_DEBUG
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	#endif

	return;
}*/
	void ROM_UART3_Error_Handler(void);
#endif
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
  // variables တွေကို 0 နဲ့ assign လုပ်တယ်။
  ROM_variables_init();

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /*GREEN(PD12) ORANGE(PD12) RED(PD12) BLUE(PD12) Led pins များကို output push pull,
  no pull up assign လုပ်တယ်။ အဲ့ကောင် တွေ ကို Debug လုပ်ဖို့ သုံးပါတယ်။
  Estop pin(PA0) ကို Externel interrupt Line 0 မှာ ချိတ်တယ်။ */
  MX_GPIO_Init();

  // UART2 MOTOR DRIVER RX အတွက်
  MX_DMA_Init();

  // TIM9 ကို counter mode အဖြစ် သုံးထားတယ်။ သူ့ ကို main loop အဖြစ် သုံးမယ်။
  MX_TIM9_Init();

  // PA2 မှာ Battery voltage တိုင်းဖို့ အတွက် IN2 သုံးထားတယ်။ Interrupt သုံးထားတယ်။ ADC ကို Timer2 နဲ့ trigger လုပ်မယ်။
  MX_ADC1_Init();

  MX_CAN1_Init();

  // ADC ကို Trigger ပစ် ဖို့ ဖြစ်ပါတယ်။  APB1 bus ပေါ် က timer 2 ကို 1 second တခါ timer trigger output ပစ်ပါတယ်။
  MX_TIM2_Init();

   #ifdef COMMUNICATION_METHOD_USB
    // usb connection လုပ်ဖို့ အတွက် ဖြစ်တယ်။
    MX_USB_DEVICE_Init();
   #endif

  // timer 3 ကို 1us နဲ့ 65535 အမြင့် ဆုံး count ထားထားတယ်။ delay ဆောက် ဖို့ ဖြစ်တယ်။
  // timer.c မှာ delay_us() နဲ့ micro second ထည့်ပြီး အသုံးပြု နိုင်ပါသည်။
  MX_TIM3_Init();

  // MOTOR DRIVER အတွက်
	#ifdef MOTOR_DRIVER_UART
  	  MX_USART2_UART_Init();
	#endif

  // COMMUNICATION
	#ifdef COMMUNICATION_METHOD_UART
  	  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	#endif

  // delay ဆောက် ဖို့ အတွက် timer ကို interrupt mode ကို စတင်ပေး တယ်။
  HAL_TIM_Base_Start(&htim3);

  // CAN Motor Driver အတွက် လိုအပ်သည် များ ပြင်ဆင်ရန် data sheet ဖတ်ပါ။
	#ifdef MOTOR_DRIVER_CAN
  	  ___ROM_LSDB_PREPARE(&hcan1);
	#endif
  // main loop အတွက် timer ကို interrupt mode ကို စတင်ပေး တယ်။
  // TIM1_BRK_TIM9_IRQHandler() ကို ( 10ms(100Hz) | 50ms(20Hz) | 100ms(10Hz) ခေါ် ပါမယ်။
  HAL_TIM_Base_Start_IT(&htim9);

  //
  //HAL_UART_Receive_DMA(&huart3, uart3_rx_data, 42);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	#ifdef ROM_SWV_DEBUG
	  //printf("Hello world\r\n");
	  //printf("%d\r\n", 100);
	  //printf("%.2f", 3.1415);
	  //HAL_Delay(1000);
	#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
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
void ROM_UART3_Error_Handler(void)
{
	/* Need to add Software EStop & Hardware Estop */

		#ifdef UART_DEBUG
		HAL_GPIO_WritePin(GPIOD, BLUE_LED_Pin | GREEN_LED_Pin |RED_LED_Pin | ORANGE_LED_Pin, GPIO_PIN_SET);

		#endif
}
void CAN_Error_Handler(void)
{	
	// CAN ERROR ဖြစ် ရင် LED 4 လုံး TOGGLE ဖြစ် မယ်။
	// Need to add Software EStop & Hardware Estop
	clearMotors(&hcan1);
	disableMotors(&hcan1);
	
	while(1) 
	{
		#ifdef CAN_DEBUG
		HAL_GPIO_WritePin(GPIOD, BLUE_LED_Pin | GREEN_LED_Pin |RED_LED_Pin | ORANGE_LED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOD, BLUE_LED_Pin | GREEN_LED_Pin |RED_LED_Pin | ORANGE_LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);
		#endif
	}
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM9->SR & TIM_SR_UIF)
	{
		estop();
		led();
		volt_ampere();

		/* CAN BUS DEBUG LED AND RPM TESTING PURPOSE */
		counts++; 
		if(counts > 50 )
		{   // ( 10 | 50 | 100 )ms * 50 တခါ led toggle ဖြစ် ဖို့ ပါ။
		    // 10Hz ဆိုရင် 5 second တခါ , 20Hz ဆိုရင် 2.5 second တခါ , 100Hz ဆိုရင် .5 second တခါ
		    // CAN BUS LED တွေ TOGGLE ဖြစ် ပါမယ်။
			#ifdef CAN_DEBUG
			HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin); 
			#endif
			
		counts = 0; 
		}
		
		// PDO မသုံးဘူးဆိုရင် Rpm right ကို motor driver ဆီ request လုပ်မှာ ဖြစ် ပါတယ်။
		// FIFO0(Right) Line 133 မှာ right actual rpm ကို ရတဲ့ အခါ Left rpm ကို request ထပ်လုပ်ပါမယ်။
		#ifndef USE_PDO
			getActualRpmRight(&hcan1); // This will Trigger to Left
			//delay_us(200);
		#endif
		
		// rom_communicate structure ကို update လုပ်မယ်။
		structure_update();


		// ပြီးရင်တော့ desire rpm တွေကို request လုပ်ပါမယ်။
		#ifdef MOTOR_DRIVER_CAN
			setTargetVelocityRpmRight(&hcan1, right_desire_rpm);
			//delay_us(500);
			setTargetVelocityRpmLeft(&hcan1, left_desire_rpm);
			//delay_us(500);
		#endif
		#ifdef COMMUNICATION_METHOD_USB
			__ROM_USB_TRANSMIT();
		#elif defined(COMMUNICATION_METHOD_UART)
			__ROM_UART3_TRANSMIT();
		#endif
		
		// Flag clear
		TIM9->SR &= ~ TIM_SR_UIF;
	}
	// နောက်ထပ် update even အတွက်ပါ။
	HAL_TIM_IRQHandler(&htim9);
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
	/* Need to add Software EStop & Hardware Estop */
	
	clearMotors(&hcan1);
	disableMotors(&hcan1);
	
	//EmergencyMode(&hcan1, EMERGENCY_STOP_DISABLE);
	
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
