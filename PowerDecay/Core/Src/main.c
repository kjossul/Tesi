/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_x-cube-ai.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "usbd_cdc_if.h"
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "dnn.h"
#include "dnn_data.h"
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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

CRC_HandleTypeDef hcrc;

DAC_HandleTypeDef hdac1;

DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel5;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel7;

SMBUS_HandleTypeDef hsmbus2;
I2C_HandleTypeDef hi2c3;
I2C_HandleTypeDef hi2c4;

LTDC_HandleTypeDef hltdc;

RTC_HandleTypeDef hrtc;

SAI_HandleTypeDef hsai_BlockA1;
SAI_HandleTypeDef hsai_BlockB1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_DAC1_Init(void);
static void MX_DFSDM1_Init(void);
static void MX_I2C2_SMBUS_Init(void);
static void MX_I2C3_Init(void);
static void MX_I2C4_Init(void);
static void MX_LTDC_Init(void);
static void MX_RTC_Init(void);
static void MX_SAI1_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM5_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_CRC_Init(void);
static void MX_TIM16_Init(void);
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
	 char buf[128];
	  int buf_len = 0;
	  ai_error ai_err;
	  ai_i32 nbatch;
	  uint32_t timestamp;
	  float y_val;
	  int x_counter = 0;
	  float x_points[1728] = {-0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.71000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.69000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.66000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.59000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.47000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.42000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.38000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.33000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.30000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.26000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.31000,  -0.75000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.20000,  -0.73000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.15000,  -0.73000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.37000,  -0.71000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.32000,  -0.52000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.08000,  -0.21000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.25000,  -0.12000,  -1.00000,   1.00000,  -0.11000,  -1.41000,   0.07000,   0.03000,   0.71000,   1.22000,  -0.11000,  -1.41000,   0.26000,   0.10000,   1.37000,  -0.37000,  -0.11000,  -1.41000,   0.33000,   0.14000,   0.00000,  -1.41000,  -0.11000,  -1.41000,   0.39000,   0.19000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,   0.45000,   0.24000,  -0.71000,   1.22000,  -0.11000,  -1.41000,   0.50000,   0.30000,   1.00000,   1.00000,  -0.11000,  -1.41000,   0.56000,   0.34000,   1.22000,  -0.71000,  -0.11000,  -1.41000,   0.61000,   0.41000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,   0.65000,   0.50000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,   0.69000,   0.60000,  -0.37000,   1.37000,  -0.11000,  -1.41000,   0.73000,   0.68000,   1.22000,   0.71000,  -0.11000,  -1.41000,   0.78000,   0.75000,   1.00000,  -1.00000,  -0.11000,  -1.41000,   0.83000,   0.87000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,   0.87000,   0.95000,  -1.37000,   0.37000,  -0.11000,  -1.41000,   0.92000,   0.99000,  -0.00000,   1.41000,  -0.11000,  -1.41000,   0.96000,   1.03000,   1.37000,   0.37000,  -0.11000,  -1.41000,   1.01000,   1.07000,   0.71000,  -1.22000,  -0.11000,  -1.41000,   1.04000,   1.11000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,   1.09000,   1.14000,  -1.22000,   0.71000,  -0.11000,  -1.41000,   1.12000,   1.18000,   0.37000,   1.37000,  -0.11000,  -1.41000,   1.16000,   1.21000,   1.41000,   0.00000,  -0.11000,  -1.41000,   1.19000,   1.24000,   0.37000,  -1.37000,  -0.11000,  -1.41000,   1.23000,   1.26000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,   1.26000,   1.28000,  -1.00000,   1.00000,  -0.11000,  -1.41000,   1.29000,   1.30000,   0.71000,   1.22000,  -0.11000,  -1.41000,   1.33000,   1.33000,   1.37000,  -0.37000,  -0.11000,  -1.41000,   1.36000,   1.36000,   0.00000,  -1.41000,  -0.11000,  -1.41000,   1.37000,   1.38000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,   1.38000,   1.40000,  -0.71000,   1.22000,  -0.11000,  -1.41000,   1.39000,   1.41000,   1.00000,   1.00000,  -0.11000,  -1.41000,   1.42000,   1.43000,   1.22000,  -0.71000,  -0.11000,  -1.41000,   1.45000,   1.44000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,   1.48000,   1.46000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,   1.51000,   1.47000,  -0.37000,   1.37000,  -0.11000,  -1.41000,   1.53000,   1.49000,   1.22000,   0.71000,  -0.11000,  -1.41000,   1.55000,   1.50000,   1.00000,  -1.00000,  -0.11000,  -1.41000,   1.57000,   1.50000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,   1.58000,   1.51000,  -1.37000,   0.37000,  -0.11000,  -1.41000,   1.59000,   1.52000,  -0.00000,   1.41000,  -0.11000,  -1.41000,   1.60000,   1.53000,   1.37000,   0.37000,  -0.11000,  -1.41000,   1.60000,   1.52000,   0.71000,  -1.22000,  -0.11000,  -1.41000,   1.61000,   1.52000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,   1.61000,   1.53000,  -1.22000,   0.71000,  -0.11000,  -1.41000,   1.61000,   1.53000,   0.37000,   1.37000,  -0.11000,  -1.41000,   1.62000,   1.52000,   1.41000,   0.00000,  -0.11000,  -1.41000,   1.61000,   1.51000,   0.37000,  -1.37000,  -0.11000,  -1.41000,   1.61000,   1.51000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,   1.59000,   1.51000,  -1.00000,   1.00000,  -0.11000,  -1.41000,   1.59000,   1.49000,   0.71000,   1.22000,  -0.11000,  -1.41000,   1.58000,   1.48000,   1.37000,  -0.37000,  -0.11000,  -1.41000,   1.57000,   1.46000,   0.00000,  -1.41000,  -0.11000,  -1.41000,   1.57000,   1.44000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,   1.56000,   1.43000,  -0.71000,   1.22000,  -0.11000,  -1.41000,   1.56000,   1.42000,   1.00000,   1.00000,  -0.11000,  -1.41000,   1.54000,   1.41000,   1.22000,  -0.71000,  -0.11000,  -1.41000,   1.54000,   1.38000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,   1.53000,   1.36000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,   1.50000,   1.34000,  -0.37000,   1.37000,  -0.11000,  -1.41000,   1.47000,   1.32000,   1.22000,   0.71000,  -0.11000,  -1.41000,   1.45000,   1.30000,   1.00000,  -1.00000,  -0.11000,  -1.41000,   1.43000,   1.28000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,   1.40000,   1.24000,  -1.37000,   0.37000,  -0.11000,  -1.41000,   1.37000,   1.21000,  -0.00000,   1.41000,  -0.11000,  -1.41000,   1.35000,   1.19000,   1.37000,   0.37000,  -0.11000,  -1.41000,   1.32000,   1.16000,   0.71000,  -1.22000,  -0.11000,  -1.41000,   1.29000,   1.12000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,   1.27000,   1.09000,  -1.22000,   0.71000,  -0.11000,  -1.41000,   1.23000,   1.06000,   0.37000,   1.37000,  -0.11000,  -1.41000,   1.19000,   1.02000,   1.41000,   0.00000,  -0.11000,  -1.41000,   1.17000,   1.00000,   0.37000,  -1.37000,  -0.11000,  -1.41000,   1.12000,   0.95000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,   1.07000,   0.90000,  -1.00000,   1.00000,  -0.11000,  -1.41000,   1.04000,   0.87000,   0.71000,   1.22000,  -0.11000,  -1.41000,   1.04000,   0.84000,   1.37000,  -0.37000,  -0.11000,  -1.41000,   1.03000,   0.80000,   0.00000,  -1.41000,  -0.11000,  -1.41000,   0.99000,   0.75000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,   0.95000,   0.71000,  -0.71000,   1.22000,  -0.11000,  -1.41000,   0.91000,   0.66000,   1.00000,   1.00000,  -0.11000,  -1.41000,   0.88000,   0.62000,   1.22000,  -0.71000,  -0.11000,  -1.41000,   0.84000,   0.57000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,   0.78000,   0.52000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,   0.74000,   0.47000,  -0.37000,   1.37000,  -0.11000,  -1.41000,   0.69000,   0.43000,   1.22000,   0.71000,  -0.11000,  -1.41000,   0.64000,   0.37000,   1.00000,  -1.00000,  -0.11000,  -1.41000,   0.59000,   0.32000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,   0.55000,   0.26000,  -1.37000,   0.37000,  -0.11000,  -1.41000,   0.49000,   0.21000,  -0.00000,   1.41000,  -0.11000,  -1.41000,   0.44000,   0.16000,   1.37000,   0.37000,  -0.11000,  -1.41000,   0.39000,   0.10000,   0.71000,  -1.22000,  -0.11000,  -1.41000,   0.34000,   0.05000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,   0.28000,  -0.00000,  -1.22000,   0.71000,  -0.11000,  -1.41000,   0.23000,  -0.06000,   0.37000,   1.37000,  -0.11000,  -1.41000,   0.17000,  -0.11000,   1.41000,   0.00000,  -0.11000,  -1.41000,   0.11000,  -0.17000,   0.37000,  -1.37000,  -0.11000,  -1.41000,   0.05000,  -0.22000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.01000,  -0.27000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.07000,  -0.32000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.12000,  -0.36000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.18000,  -0.41000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.24000,  -0.47000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.30000,  -0.59000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.46000,  -0.64000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.55000,  -0.70000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.62000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.60000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.66000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.68000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.69000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.70000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.70000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.71000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.72000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.00000,   1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,   0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.41000,   0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   0.00000,  -1.41000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,  -0.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,   1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,   1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,  -0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,  -1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.41000,  -0.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.37000,   1.37000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.22000,   0.71000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,   1.00000,  -1.00000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -0.71000,  -1.22000,  -0.11000,  -1.41000,  -0.73000,  -0.76000,  -1.37000,   0.37000,  -0.11000,  -1.41000};
	  // Chunk of memory used to hold intermediate values for neural network
	  AI_ALIGNED(4) ai_u8 activations[AI_DNN_DATA_ACTIVATIONS_SIZE];

	  // Buffers used to store input and output tensors
	  AI_ALIGNED(4) ai_i8 in_data[AI_DNN_IN_1_SIZE_BYTES];
	  AI_ALIGNED(4) ai_i8 out_data[AI_DNN_OUT_1_SIZE_BYTES];

	  // Pointer to our model
	  ai_handle dnn = AI_HANDLE_NULL;

	  // Initialize wrapper structs that hold pointers to data and info about the
	  // data (tensor height, width, channels)
	  ai_buffer ai_input[AI_DNN_IN_NUM] = AI_DNN_IN;
	  ai_buffer ai_output[AI_DNN_OUT_NUM] = AI_DNN_OUT;

	  // Set working memory and get weights/biases from model
	  ai_network_params ai_params = {
	    AI_DNN_DATA_WEIGHTS(ai_dnn_data_weights_get()),
	    AI_DNN_DATA_ACTIVATIONS(activations)
	  };

	  // Set pointers wrapper structs to our data buffers
	  ai_input[0].n_batches = 1;
	  ai_input[0].data = AI_HANDLE_PTR(in_data);
	  ai_output[0].n_batches = 1;
	  ai_output[0].data = AI_HANDLE_PTR(out_data);
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
  MX_ADC1_Init();
  MX_DAC1_Init();
  MX_DFSDM1_Init();
  MX_I2C2_SMBUS_Init();
  MX_I2C3_Init();
  MX_I2C4_Init();
  MX_LTDC_Init();
  MX_RTC_Init();
  MX_SAI1_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_CRC_Init();
  MX_USB_DEVICE_Init();
  MX_TIM16_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
  // Start timer/counter
    HAL_TIM_Base_Start(&htim16);

    // Greetings!
    buf_len = sprintf(buf, "STM32 X-Cube-AI test\r\n");
    CDC_Transmit_FS((uint8_t *)buf, buf_len);
    // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);

    // Create instance of neural network
    ai_err = ai_dnn_create(&dnn, AI_DNN_DATA_CONFIG);
    if (ai_err.type != AI_ERROR_NONE)
    {
      buf_len = sprintf(buf, "Error: could not create NN instance\r\n");
      CDC_Transmit_FS((uint8_t *)buf, buf_len);
      // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
      while(1);
    }

    // Initialize neural network
    if (!ai_dnn_init(dnn, &ai_params))
    {
      buf_len = sprintf(buf, "Error: could not initialize NN\r\n");
      CDC_Transmit_FS((uint8_t *)buf, buf_len);
      // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
      while(1);
    }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	    // Get current timestamp
	    timestamp = htim16.Instance->CNT;
	    // Fill input buffer (use test value)
	    for (uint32_t i = 0; i < AI_DNN_IN_1_SIZE; i++)
	    {
	      ((ai_float *)in_data)[i] = (ai_float)x_points[x_counter];
	      if (++x_counter >= 1728) {
	    	  x_counter = 0;
	      }
	    }

	    // Perform inference
	    nbatch = ai_dnn_run(dnn, &ai_input[0], &ai_output[0]);
	    // Print output of neural network along with inference time (microseconds)
	    if (nbatch != 1) {
	      buf_len = sprintf(buf, "Error: could not run inference\r\n");
	      // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
	      CDC_Transmit_FS((uint8_t *)buf, buf_len);
	    }

	    // Read output (predicted y) of neural network
	    y_val = ((float *)out_data)[0];

	    // Print output of neural network along with inference time (microseconds)
	    buf_len = sprintf(buf,
	                      "prediction (h = %d) = %f | Duration: %lu\r\n",
	                      x_counter / (12 * 6), y_val,
	                      htim16.Instance->CNT - timestamp);
	    // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
	    CDC_Transmit_FS((uint8_t *)buf, buf_len);
	    // Wait before doing it again
	    HAL_Delay(500);
    /* USER CODE END WHILE */

  MX_X_CUBE_AI_Process();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_SAI1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_I2C3
                              |RCC_PERIPHCLK_I2C4|RCC_PERIPHCLK_DFSDM1
                              |RCC_PERIPHCLK_USB|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_LTDC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInit.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLLSAI2_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI2.PLLSAI2M = 2;
  PeriphClkInit.PLLSAI2.PLLSAI2N = 8;
  PeriphClkInit.PLLSAI2.PLLSAI2P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2ClockOut = RCC_PLLSAI2_LTDCCLK;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 5;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 96;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV25;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV4;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV4;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK|RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_DISABLE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief DFSDM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DFSDM1_Init(void)
{

  /* USER CODE BEGIN DFSDM1_Init 0 */

  /* USER CODE END DFSDM1_Init 0 */

  /* USER CODE BEGIN DFSDM1_Init 1 */

  /* USER CODE END DFSDM1_Init 1 */
  hdfsdm1_filter0.Instance = DFSDM1_Filter0;
  hdfsdm1_filter0.Init.RegularParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.RegularParam.FastMode = DISABLE;
  hdfsdm1_filter0.Init.RegularParam.DmaMode = DISABLE;
  hdfsdm1_filter0.Init.FilterParam.SincOrder = DFSDM_FILTER_FASTSINC_ORDER;
  hdfsdm1_filter0.Init.FilterParam.Oversampling = 1;
  hdfsdm1_filter0.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel5.Instance = DFSDM1_Channel5;
  hdfsdm1_channel5.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel5.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
  hdfsdm1_channel5.Init.OutputClock.Divider = 2;
  hdfsdm1_channel5.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel5.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel5.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel5.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel5.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel5.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel5.Init.Awd.Oversampling = 1;
  hdfsdm1_channel5.Init.Offset = 0;
  hdfsdm1_channel5.Init.RightBitShift = 0x00;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel5) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel7.Instance = DFSDM1_Channel7;
  hdfsdm1_channel7.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel7.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
  hdfsdm1_channel7.Init.OutputClock.Divider = 2;
  hdfsdm1_channel7.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel7.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel7.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel7.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel7.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel7.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel7.Init.Awd.Oversampling = 1;
  hdfsdm1_channel7.Init.Offset = 0;
  hdfsdm1_channel7.Init.RightBitShift = 0x00;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel7) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_5, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DFSDM1_Init 2 */

  /* USER CODE END DFSDM1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_SMBUS_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hsmbus2.Instance = I2C2;
  hsmbus2.Init.Timing = 0x307075B1;
  hsmbus2.Init.AnalogFilter = SMBUS_ANALOGFILTER_ENABLE;
  hsmbus2.Init.OwnAddress1 = 2;
  hsmbus2.Init.AddressingMode = SMBUS_ADDRESSINGMODE_7BIT;
  hsmbus2.Init.DualAddressMode = SMBUS_DUALADDRESS_DISABLE;
  hsmbus2.Init.OwnAddress2 = 0;
  hsmbus2.Init.OwnAddress2Masks = SMBUS_OA2_NOMASK;
  hsmbus2.Init.GeneralCallMode = SMBUS_GENERALCALL_DISABLE;
  hsmbus2.Init.NoStretchMode = SMBUS_NOSTRETCH_DISABLE;
  hsmbus2.Init.PacketErrorCheckMode = SMBUS_PEC_DISABLE;
  hsmbus2.Init.PeripheralMode = SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE;
  hsmbus2.Init.SMBusTimeout = 0x000085B8;
  if (HAL_SMBUS_Init(&hsmbus2) != HAL_OK)
  {
    Error_Handler();
  }
  /** configuration Alert Mode
  */
  if (HAL_SMBUS_EnableAlert_IT(&hsmbus2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x307075B1;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief I2C4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C4_Init(void)
{

  /* USER CODE BEGIN I2C4_Init 0 */

  /* USER CODE END I2C4_Init 0 */

  /* USER CODE BEGIN I2C4_Init 1 */

  /* USER CODE END I2C4_Init 1 */
  hi2c4.Instance = I2C4;
  hi2c4.Init.Timing = 0x307075B1;
  hi2c4.Init.OwnAddress1 = 0;
  hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c4.Init.OwnAddress2 = 0;
  hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C4_Init 2 */

  /* USER CODE END I2C4_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 1;
  hltdc.Init.AccumulatedVBP = 1;
  hltdc.Init.AccumulatedActiveW = 801;
  hltdc.Init.AccumulatedActiveH = 481;
  hltdc.Init.TotalWidth = 802;
  hltdc.Init.TotalHeigh = 482;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 0;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 0;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 0;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 0;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_LTDC_SetPitch(&hltdc, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_LTDC_SetPitch(&hltdc, 0, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TamperTypeDef sTamper = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the RTC Tamper 1
  */
  sTamper.Tamper = RTC_TAMPER_1;
  sTamper.Trigger = RTC_TAMPERTRIGGER_RISINGEDGE;
  sTamper.NoErase = RTC_TAMPER_ERASE_BACKUP_ENABLE;
  sTamper.MaskFlag = RTC_TAMPERMASK_FLAG_DISABLE;
  sTamper.Filter = RTC_TAMPERFILTER_DISABLE;
  sTamper.SamplingFrequency = RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768;
  sTamper.PrechargeDuration = RTC_TAMPERPRECHARGEDURATION_1RTCCLK;
  sTamper.TamperPullUp = RTC_TAMPER_PULLUP_ENABLE;
  sTamper.TimeStampOnTamperDetection = RTC_TIMESTAMPONTAMPERDETECTION_ENABLE;
  if (HAL_RTCEx_SetTamper(&hrtc, &sTamper) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SAI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SAI1_Init(void)
{

  /* USER CODE BEGIN SAI1_Init 0 */

  /* USER CODE END SAI1_Init 0 */

  /* USER CODE BEGIN SAI1_Init 1 */

  /* USER CODE END SAI1_Init 1 */
  hsai_BlockA1.Instance = SAI1_Block_A;
  hsai_BlockA1.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_TX;
  hsai_BlockA1.Init.DataSize = SAI_DATASIZE_8;
  hsai_BlockA1.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockA1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
  hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
  hsai_BlockA1.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
  hsai_BlockA1.Init.MckOverSampling = SAI_MCK_OVERSAMPLING_DISABLE;
  hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_192K;
  hsai_BlockA1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockA1.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockA1.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  hsai_BlockA1.Init.PdmInit.Activation = DISABLE;
  hsai_BlockA1.Init.PdmInit.MicPairsNbr = 0;
  hsai_BlockA1.Init.PdmInit.ClockEnable = SAI_PDM_CLOCK1_ENABLE;
  hsai_BlockA1.FrameInit.FrameLength = 8;
  hsai_BlockA1.FrameInit.ActiveFrameLength = 1;
  hsai_BlockA1.FrameInit.FSDefinition = SAI_FS_STARTFRAME;
  hsai_BlockA1.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockA1.FrameInit.FSOffset = SAI_FS_FIRSTBIT;
  hsai_BlockA1.SlotInit.FirstBitOffset = 0;
  hsai_BlockA1.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
  hsai_BlockA1.SlotInit.SlotNumber = 1;
  hsai_BlockA1.SlotInit.SlotActive = 0x00000000;
  if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
  {
    Error_Handler();
  }
  hsai_BlockB1.Instance = SAI1_Block_B;
  hsai_BlockB1.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockB1.Init.AudioMode = SAI_MODESLAVE_RX;
  hsai_BlockB1.Init.DataSize = SAI_DATASIZE_8;
  hsai_BlockB1.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockB1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
  hsai_BlockB1.Init.Synchro = SAI_SYNCHRONOUS;
  hsai_BlockB1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
  hsai_BlockB1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockB1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockB1.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockB1.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockB1.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  hsai_BlockB1.Init.PdmInit.Activation = DISABLE;
  hsai_BlockB1.Init.PdmInit.MicPairsNbr = 0;
  hsai_BlockB1.Init.PdmInit.ClockEnable = SAI_PDM_CLOCK1_ENABLE;
  hsai_BlockB1.FrameInit.FrameLength = 8;
  hsai_BlockB1.FrameInit.ActiveFrameLength = 1;
  hsai_BlockB1.FrameInit.FSDefinition = SAI_FS_STARTFRAME;
  hsai_BlockB1.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockB1.FrameInit.FSOffset = SAI_FS_FIRSTBIT;
  hsai_BlockB1.SlotInit.FirstBitOffset = 0;
  hsai_BlockB1.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
  hsai_BlockB1.SlotInit.SlotNumber = 1;
  hsai_BlockB1.SlotInit.SlotActive = 0x00000000;
  if (HAL_SAI_Init(&hsai_BlockB1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAI1_Init 2 */

  /* USER CODE END SAI1_Init 2 */

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
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
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
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim5, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_FORCED_ACTIVE;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 120-1;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 65535;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_RTS;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED1_Pin|DCDC_2_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED2_Pin|WIFI_WAKEUP_Pin|CS_DH_Pin|EX_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BLE_RST_GPIO_Port, BLE_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, CS_WIFI_Pin|C_EN_Pin|CS_ADWB_Pin|STSAFE_RESET_Pin
                          |WIFI_BOOT0_Pin|CS_DHC_Pin|SEL3_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, BLE_SPI_CS_Pin|SEL1_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI2_MOSI_p2_Pin|PB11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BOOT0_PE0_Pin BLE_TEST8_Pin */
  GPIO_InitStruct.Pin = BOOT0_PE0_Pin|BLE_TEST8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB9_Pin PB8_Pin PB14_Pin CHRGB0_Pin */
  GPIO_InitStruct.Pin = PB9_Pin|PB8_Pin|PB14_Pin|CHRGB0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT0_PE0H3_Pin */
  GPIO_InitStruct.Pin = BOOT0_PE0H3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT0_PE0H3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SDMMC_D3_Pin SDMMC_D2_Pin SDMMC_D1_Pin SDMMC_CK_Pin
                           SDMMC_D0_Pin */
  GPIO_InitStruct.Pin = SDMMC_D3_Pin|SDMMC_D2_Pin|SDMMC_D1_Pin|SDMMC_CK_Pin
                          |SDMMC_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BLE_TEST9_Pin WIFI_DRDY_Pin INT1_DHC_Pin INT_STT_Pin
                           INT1_ADWB_Pin */
  GPIO_InitStruct.Pin = BLE_TEST9_Pin|WIFI_DRDY_Pin|INT1_DHC_Pin|INT_STT_Pin
                          |INT1_ADWB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin DCDC_2_EN_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|DCDC_2_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin WIFI_WAKEUP_Pin CS_DH_Pin EX_RESET_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|WIFI_WAKEUP_Pin|CS_DH_Pin|EX_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10_Pin PA9_Pin PA0_Pin PA1_Pin */
  GPIO_InitStruct.Pin = PA10_Pin|PA9_Pin|PA0_Pin|PA1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PG12_Pin PG10_Pin PG9_Pin */
  GPIO_InitStruct.Pin = PG12_Pin|PG10_Pin|PG9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : SDMMC_CMD_Pin */
  GPIO_InitStruct.Pin = SDMMC_CMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(SDMMC_CMD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BLE_RST_Pin */
  GPIO_InitStruct.Pin = BLE_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BLE_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : WIFI_RST_Pin */
  GPIO_InitStruct.Pin = WIFI_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(WIFI_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_WIFI_Pin C_EN_Pin CS_ADWB_Pin STSAFE_RESET_Pin
                           WIFI_BOOT0_Pin CS_DHC_Pin SEL3_4_Pin */
  GPIO_InitStruct.Pin = CS_WIFI_Pin|C_EN_Pin|CS_ADWB_Pin|STSAFE_RESET_Pin
                          |WIFI_BOOT0_Pin|CS_DHC_Pin|SEL3_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : INT2_DHC_Pin PGOOD_Pin INT_M_Pin */
  GPIO_InitStruct.Pin = INT2_DHC_Pin|PGOOD_Pin|INT_M_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : BLE_SPI_CS_Pin SEL1_2_Pin */
  GPIO_InitStruct.Pin = BLE_SPI_CS_Pin|SEL1_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : INT_HTS_Pin BLE_INT_Pin */
  GPIO_InitStruct.Pin = INT_HTS_Pin|BLE_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : INT2_ADWB_Pin SD_DETECT_Pin */
  GPIO_InitStruct.Pin = INT2_ADWB_Pin|SD_DETECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CHRG_Pin */
  GPIO_InitStruct.Pin = CHRG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CHRG_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_PWR_Pin */
  GPIO_InitStruct.Pin = BUTTON_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_PWR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI2_MOSI_p2_Pin PB11_Pin */
  GPIO_InitStruct.Pin = SPI2_MOSI_p2_Pin|PB11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : INT2_DH_Pin */
  GPIO_InitStruct.Pin = INT2_DH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT2_DH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PE12_Pin */
  GPIO_InitStruct.Pin = PE12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PE12_GPIO_Port, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
