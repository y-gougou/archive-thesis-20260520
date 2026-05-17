/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "current_types.h"
#include "current_filter.h"
#include "uart_protocol.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>
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

/* USER CODE BEGIN PV */

/** ADC数据就绪标志 (由DMA中断设置) */
volatile uint8_t g_adc_data_ready = 0;

/** ADC原始数据缓冲区 (DMA目标) */
volatile uint16_t g_adc_raw_buffer[CHANNEL_COUNT];

/** 滤波后的电流值 */
float g_current_values[CHANNEL_COUNT] = {0};

/** 各通道滤波器 */
filter_context_t g_filters[CHANNEL_COUNT];

/** 时间戳 */
uint32_t g_last_oled_update = 0;
uint32_t g_last_uart_send = 0;
uint32_t g_last_heartbeat = 0;

/** 串口接收字节 */
uint8_t g_uart_rx_byte = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void process_adc_data(void);
static void update_oled_display(void);
static void send_uart_data(void);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  
  /* 初始化滤波器 */
  for (int i = 0; i < CHANNEL_COUNT; i++) {
      filter_init(&g_filters[i]);
  }
  
  /* 初始化OLED */
  oled_init();
  oled_cls();
  oled_show_string(0, 0, "4CH-Current", 1);
  oled_show_string(0, 2, "System Ready", 1);
  HAL_Delay(1000);
  oled_cls();
  
  /* 启动ADC DMA连续采集 */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_adc_raw_buffer, CHANNEL_COUNT);
  
  /* 启动串口接收中断 (每次接收1字节) */
  extern uint8_t g_uart_rx_byte;
  HAL_UART_Receive_IT(&huart2, &g_uart_rx_byte, 1);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint32_t now = HAL_GetTick();
    
    /* 处理ADC数据 */
#if !PROCESS_ADC_ON_UART_SEND
    if (g_adc_data_ready) {
        g_adc_data_ready = 0;
        process_adc_data();
    }
#endif
    
    /* 更新OLED显示 */
#if OLED_RUNTIME_DISPLAY_ENABLE
    if (now - g_last_oled_update >= OLED_UPDATE_INTERVAL_MS) {
        g_last_oled_update = now;
        update_oled_display();
    }
#endif
    
    /* 发送UART数据 */
    if (now - g_last_uart_send >= UART_SEND_INTERVAL_MS) {
        g_last_uart_send = now;
        send_uart_data();
    }
    
    /* 心跳灯 (500ms 翻转一次) */
    if (now - g_last_heartbeat >= 500) {
        g_last_heartbeat = now;
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
    
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
 * @brief 处理ADC数据
 * 
 * 将原始ADC值转换为电流值，进行滤波和校准补偿
 */
static void process_adc_data(void)
{
    /* 校准参数数组 */
    static const float cal_gain[CHANNEL_COUNT] = {
        CAL_CH0_GAIN, CAL_CH1_GAIN, CAL_CH2_GAIN, CAL_CH3_GAIN
    };
    static const float cal_offset[CHANNEL_COUNT] = {
        CAL_CH0_OFFSET, CAL_CH1_OFFSET, CAL_CH2_OFFSET, CAL_CH3_OFFSET
    };
    
    for (int i = 0; i < CHANNEL_COUNT; i++) {
        /* ADC值转电压 */
        float voltage = ((float)g_adc_raw_buffer[i] / ADC_MAX_VALUE) * ADC_REF_VOLTAGE;
        
        /* 电压转电流 (INA282公式: I = (Vout - Vref) / (Gain * Rshunt)) */
        float current = (voltage - INA_REF_VOLTAGE) / (INA_GAIN * SHUNT_RESISTOR);
        
        /* 应用校准补偿: 真实电流 = 测量电流 * gain + offset */
        float calibrated = current * cal_gain[i] + cal_offset[i];
        
        /* 添加到滤波器 */
        filter_add_sample(&g_filters[i], calibrated);
        
        /* 获取滤波后的值 */
        g_current_values[i] = filter_get_average(&g_filters[i]);
    }
}

/**
 * @brief 更新OLED显示
 */
static void update_oled_display(void)
{
    char buf[20];
    
    snprintf(buf, sizeof(buf), "M1: %.2f A  ", g_current_values[0]);
    oled_show_string(0, 0, buf, 1);
    
    snprintf(buf, sizeof(buf), "M2: %.2f A  ", g_current_values[1]);
    oled_show_string(0, 2, buf, 1);
    
    snprintf(buf, sizeof(buf), "M3: %.2f A  ", g_current_values[2]);
    oled_show_string(0, 4, buf, 1);
    
    snprintf(buf, sizeof(buf), "M4: %.2f A  ", g_current_values[3]);
    oled_show_string(0, 6, buf, 1);
}

/**
 * @brief 发送UART数据
 * 
 * 使用自定义二进制协议发送电流数据
 */
static void send_uart_data(void)
{
#if PROCESS_ADC_ON_UART_SEND
    process_adc_data();
#endif
    protocol_send_current_data();
}

/**
 * @brief ADC DMA完成回调
 * 
 * 由HAL库在DMA传输完成时调用
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
#if !PROCESS_ADC_ON_UART_SEND
    if (hadc->Instance == ADC1) {
        g_adc_data_ready = 1;
    }
#else
    (void)hadc;
#endif
}

/**
 * @brief 串口接收完成回调
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {
        /* 解析接收到的字节 */
        protocol_parse_byte(g_uart_rx_byte);
        
        /* 重新开启接收中断 */
        HAL_UART_Receive_IT(&huart2, &g_uart_rx_byte, 1);
    }
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
#ifdef USE_FULL_ASSERT
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
