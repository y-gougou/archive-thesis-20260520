/**
 ******************************************************************************
 * @file           : current_types.h
 * @brief          : 电流采集系统类型定义和常量
 * @author         : 4CH-Current Project
 ******************************************************************************
 */

#ifndef __CURRENT_TYPES_H
#define __CURRENT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* ========================================================================== */
/*                          常量定义                                          */
/* ========================================================================== */

/** ADC通道数量 */
#define CHANNEL_COUNT               4

/** 有效UART通道数量 (M1端口无输出, 仅使用M2/M3/M4) */
#define UART_CHANNEL_COUNT          3

/** ADC最大值 (12位ADC) */
#define ADC_MAX_VALUE               4095.0f

/** ADC参考电压 (V) */
#define ADC_REF_VOLTAGE             3.3f

/** INA282放大器参考电压 (V) */
#define INA_REF_VOLTAGE             1.65f

/** INA282放大器增益 */
#define INA_GAIN                    50.0f

/** 采样电阻值 (Ohm) */
#define SHUNT_RESISTOR              0.005f

/** 滤波器窗口大小 (越大越平滑) */
#define FILTER_WINDOW_SIZE          16

/** OLED更新间隔 (ms) */
#define OLED_UPDATE_INTERVAL_MS     1000

/** UART发送间隔 (ms) */
#define UART_SEND_INTERVAL_MS       10

/** Runtime OLED display refresh. Disable for high-rate data collection. */
#define OLED_RUNTIME_DISPLAY_ENABLE 1

/** Send current frames on USART1 in addition to USART2. Disable to avoid extra blocking. */
#define UART_SEND_USART1_ENABLE     1

/** Include a monotonically increasing sequence id in text current frames. */
#define UART_TEXT_FRAME_WITH_SEQ    0

/** Use latest DMA ADC buffer at UART send time instead of processing every DMA interrupt. */
#define PROCESS_ADC_ON_UART_SEND    0

/* ========================================================================== */
/*                          校准补偿参数                                       */
/* ========================================================================== */
/*
 * 校准公式: 真实电流 = 测量电流 * GAIN + OFFSET
 * 
 * 调整方法:
 * 1. 用万用表测量真实电流 I_real
 * 2. 记录OLED显示的电流 I_measured
 * 3. 如果显示值偏大: 减小GAIN 或 增加负OFFSET
 * 4. 如果显示值偏小: 增大GAIN 或 增加正OFFSET
 * 5. OFFSET用于校正零点漂移 (无电流时应显示0)
 * 6. GAIN用于校正比例误差
 */

/** 通道0 (PA0/M1) 增益补偿 */
#define CAL_CH0_GAIN                1.0f
/** 通道0 (PA0/M1) 偏移补偿 (A) */
#define CAL_CH0_OFFSET              0.0f

/** 通道1 (PA1/M2) 增益补偿 */
#define CAL_CH1_GAIN                1.0f
/** 通道1 (PA1/M2) 偏移补偿 (A) */
#define CAL_CH1_OFFSET              0.0f

/** 通道2 (PA4/M3) 增益补偿 */
#define CAL_CH2_GAIN                1.0f
/** 通道2 (PA4/M3) 偏移补偿 (A) */
#define CAL_CH2_OFFSET              0.0f

/** 通道3 (PA5/M4) 增益补偿 */
#define CAL_CH3_GAIN                1.0f
/** 通道3 (PA5/M4) 偏移补偿 (A) */
#define CAL_CH3_OFFSET              0.0f

/* ========================================================================== */
/*                          类型定义                                          */
/* ========================================================================== */

/**
 * @brief 通道索引枚举
 */
typedef enum {
    CHANNEL_0 = 0,  /**< PA0 - 电机1 */
    CHANNEL_1 = 1,  /**< PA1 - 电机2 */
    CHANNEL_2 = 2,  /**< PA4 - 电机3 */
    CHANNEL_3 = 3   /**< PA5 - 电机4 */
} channel_index_e;

/**
 * @brief 滤波器上下文结构体
 */
typedef struct {
    float buffer[FILTER_WINDOW_SIZE];   /**< 采样缓冲区 */
    uint16_t write_index;               /**< 写入索引 */
    uint16_t sample_count;              /**< 已采样数量 */
    float sum;                          /**< 累计和 */
    bool initialized;                   /**< 初始化标志 */
} filter_context_t;

/**
 * @brief 电流测量数据结构体
 */
typedef struct {
    float current_amps[CHANNEL_COUNT];  /**< 各通道电流值 (A) */
    uint16_t raw_adc[CHANNEL_COUNT];    /**< 原始ADC值 */
    uint32_t timestamp_ms;              /**< 时间戳 */
} current_data_t;

#ifdef __cplusplus
}
#endif

#endif /* __CURRENT_TYPES_H */
