/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "string.h"
#include <math.h>
//#include "arm_math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define interval 0.5 //the time interval per sample
//#define ARM_MATH_CM4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2S_HandleTypeDef hi2s2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2S2_Init(void);
/* USER CODE BEGIN PFP */
void toStr(uint16_t d, char* str);
void getStr(int32_t d, char* str);
double dailyDose(int32_t p);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t buffer[64];
uint8_t *data;
/*
	  HAL_GPIO_TogglePin (GPIOA, LED_Pin);
	  while(count){
		  volatile HAL_StatusTypeDef result = HAL_I2S_Receive(&hi2s2, data_in, 2, 100);
		  if (result == HAL_OK) {
			  if(data_in[1]==0||data_in[0]>=16384) continue;
			  current = data_in[0]+(data_in[1]>>7);
			  samples[--count] = current;
		  }
	  }
	  for (int i=0; i<n; i++){
		  davg += samples[i]/n; //average
	  }
	  avg = (int32_t) davg;
	  for (int i=0; i<n; i++){
		  samples[i] -= avg;
		  if(min>samples[i]) min = samples[i];
		  if(max<samples[i]) max = samples[i];
	  }
	  count = n;
	  peak = max-min;
	  max = 0;
	  min = 100000;
	  getStr(peak, s); //2072.43028737 -- 90 dB right shifted by 7
	  davg = 0;
	  data = s;
	  CDC_Transmit_FS(data, strlen(data));
	  HAL_Delay(500);
*/
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
  MX_I2S2_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  uint16_t data_in[2];
  uint16_t n = 1024; //number of samples, keep at power of 2 for FFT
  int32_t current;
  uint16_t count = n;
  int32_t avg = 0; //running average of the sampled data
//  int32_t min_avg = -1; //keeps track of the lowest average so far -- DC offset
  char s[13]; //store string output
  float davg=0;
  double dd = 0; //keep track of daily dose
  int reached = 0;
  int32_t max = 0;
  int32_t min = 100000;
  int32_t peak;
  int32_t samples[1024];
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_TogglePin (GPIOA, LED_Pin);
	  while(count){
		  volatile HAL_StatusTypeDef result = HAL_I2S_Receive(&hi2s2, data_in, 2, 100);
		  if (result == HAL_OK) {
			  if(data_in[1]==0||data_in[0]>=16384) continue;
			  current = data_in[0]+(data_in[1]>>7);
			  samples[--count] = current;
		  }
	  }
	  for (int i=0; i<n; i++){
		  davg += samples[i]/n; //average
	  }
	  avg = (int32_t) davg;
	  for (int i=0; i<n; i++){
		  samples[i] -= avg;
		  if(min>samples[i]) min = samples[i];
		  if(max<samples[i]) max = samples[i];
	  }
	  count = n;
	  peak = max-min;
	  max = 0;
	  min = 100000;
	  getStr(peak, s); //2072.43028737 -- 90 dB right shifted by 7
	  davg = 0;
	  data = s;
	  if(peak>2072) HAL_GPIO_WritePin(GPIOA, LEDINST_Pin, GPIO_PIN_SET); //If over given value, means >90 dB, set warning
	  else HAL_GPIO_WritePin(GPIOA, LEDINST_Pin, GPIO_PIN_RESET);
	  dd += dailyDose(peak);
	  if(dd>=1&&reached==0){
		  HAL_GPIO_TogglePin(GPIOA, LEDINT_Pin); //If we've reached daily dose
		  reached = 1; //Making sure we don't keep toggling pin
	  }
	  CDC_Transmit_FS(data, strlen(data));
	  HAL_Delay(500);
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
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
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_16K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */

  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|LEDINST_Pin|LEDINT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin LEDINST_Pin LEDINT_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LEDINST_Pin|LEDINT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void toStr(uint16_t d, char* str){ //converting int16_t to decimal -- assuming positive, which isn't always true
	str[4]=d%10+'0';
	d/=10;
	str[3]=d%10+'0';
	d/=10;
	str[2]=d%10+'0';
	d/=10;
	str[1]=d%10+'0';
	d/=10;
	str[0]=d%10+'0';
}

void getStr(int32_t d, char* str){ //assume str's length is at least 10
	uint8_t count = 13;
	while(count){
		str[--count] = d%10+'0'; //there's an easier way to do this, but don't want to waste memory
		d/=10;
	}
	str[0] = ',';
}

double dailyDose(int32_t p){ //adapted from my python code
	double arg = (double) (p)/ 2072; //Using current definition of 90 dB, may change later -- make into a macro
	arg = 10*log(p)/log(10); // to compute dB version of p using 90 dB as a reference
	arg = pow(2, -arg/5);
	double t = 8*60*60*arg; //defining the resulting exposure time period
	return interval/t; //finally, return how much this exposure contributed to the daily dose based on
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