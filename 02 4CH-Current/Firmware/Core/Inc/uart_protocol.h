/**
 ******************************************************************************
 * @file           : uart_protocol.h
 * @brief          : 串口通信协议定义
 * @author         : 4CH-Current Project
 *
 * 协议格式:
 * | 帧头(2B) | 命令(1B) | 长度(1B) | 数据(NB) | 校验(1B) | 帧尾(2B) |
 * |  AA 55   |   CMD    |   LEN    |   DATA   |   CRC    |  0D 0A   |
 *
 * 校验算法: 异或和 (XOR) - 从CMD到DATA的所有字节异或
 ******************************************************************************
 */

#ifndef __UART_PROTOCOL_H
#define __UART_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                          协议选择宏定义                                     */
/* ========================================================================== */

/**
 * 协议类型定义:
 * 0: 自定义二进制协议 (Custom Binary Protocol) - 支持双向交互, 安全可靠
 * 1: FireWater 协议 (Text CSV Protocol) - 兼容 FireWater/VOFA+ 等可视化上位机
 */
#define UART_PROTOCOL_TYPE          1

#include <stdint.h>
#include <stdbool.h>
#include "current_types.h"

/* ========================================================================== */
/*                          协议常量定义                                       */
/* ========================================================================== */

/** 帧头 */
#define PROTO_HEADER_1          0xAA
#define PROTO_HEADER_2          0x55

/** 帧尾 */
#define PROTO_TAIL_1            0x0D  /* '\r' */
#define PROTO_TAIL_2            0x0A  /* '\n' */

/** 最大数据长度 */
#define PROTO_MAX_DATA_LEN      32

/** 完整帧最大长度 = 帧头(2) + 命令(1) + 长度(1) + 数据(32) + 校验(1) + 帧尾(2) */
#define PROTO_MAX_FRAME_LEN     (2 + 1 + 1 + PROTO_MAX_DATA_LEN + 1 + 2)

/* ========================================================================== */
/*                          命令码定义                                         */
/* ========================================================================== */

/**
 * 命令码列表
 *
 * 0x01-0x1F: 查询命令 (下位机→上位机)
 * 0x20-0x3F: 设置命令 (上位机→下位机)
 * 0x80-0x9F: 主动上报 (下位机→上位机)
 * 0xF0-0xFF: 系统命令
 */
typedef enum {
    /* 查询命令 */
    CMD_QUERY_CURRENT       = 0x01,  /**< 查询电流数据 */
    CMD_QUERY_RAW_ADC       = 0x02,  /**< 查询原始ADC值 */
    CMD_QUERY_CALIBRATION   = 0x03,  /**< 查询校准参数 */
    CMD_QUERY_VERSION       = 0x04,  /**< 查询固件版本 */

    /* 设置命令 */
    CMD_SET_CALIBRATION     = 0x20,  /**< 设置校准参数 */
    CMD_SET_SAMPLE_RATE     = 0x21,  /**< 设置采样率 */
    CMD_SET_FILTER          = 0x22,  /**< 设置滤波参数 */

    /* 主动上报 */
    CMD_REPORT_CURRENT      = 0x80,  /**< 主动上报电流数据 */
    CMD_REPORT_ERROR        = 0x81,  /**< 上报错误信息 */

    /* 系统命令 */
    CMD_ACK                 = 0xF0,  /**< 应答 */
    CMD_NACK                = 0xF1,  /**< 否定应答 */
    CMD_RESET               = 0xFF   /**< 复位 */
} protocol_cmd_e;

/* ========================================================================== */
/*                          数据包结构定义                                     */
/* ========================================================================== */

/**
 * @brief 电流数据包 (CMD_REPORT_CURRENT / CMD_QUERY_CURRENT响应)
 *
 * 数据区格式 (12字节): 仅包含3个有效通道 (M2/M3/M4)
 * | CH1电流(4B) | CH2电流(4B) | CH3电流(4B) |
 *
 * 注意: M1 (通道0/PA0) 无输出, 已移除
 * 电流值: float类型, 单位: 安培(A)
 */
#pragma pack(push, 1)
typedef struct {
    float ch0_current;      /**< 通道1电流 M2 (A) */
    float ch1_current;      /**< 通道2电流 M3 (A) */
    float ch2_current;      /**< 通道3电流 M4 (A) */
} current_packet_t;
#pragma pack(pop)

/**
 * @brief 原始ADC数据包 (CMD_QUERY_RAW_ADC响应)
 *
 * 数据区格式 (8字节):
 * | CH0_ADC(2B) | CH1_ADC(2B) | CH2_ADC(2B) | CH3_ADC(2B) |
 */
#pragma pack(push, 1)
typedef struct {
    uint16_t ch0_adc;       /**< 通道0 ADC值 (0-4095) */
    uint16_t ch1_adc;       /**< 通道1 ADC值 (0-4095) */
    uint16_t ch2_adc;       /**< 通道2 ADC值 (0-4095) */
    uint16_t ch3_adc;       /**< 通道3 ADC值 (0-4095) */
} raw_adc_packet_t;
#pragma pack(pop)

/**
 * @brief 校准参数包 (CMD_QUERY_CALIBRATION / CMD_SET_CALIBRATION)
 *
 * 数据区格式 (33字节):
 * | 通道(1B) | GAIN(4B*4) | OFFSET(4B*4) |
 */
#pragma pack(push, 1)
typedef struct {
    uint8_t channel;        /**< 通道号 (0-3, 0xFF=所有通道) */
    float gain[4];          /**< 增益参数 */
    float offset[4];        /**< 偏移参数 (A) */
} calibration_packet_t;
#pragma pack(pop)

/**
 * @brief 版本信息包 (CMD_QUERY_VERSION响应)
 */
#pragma pack(push, 1)
typedef struct {
    uint8_t major;          /**< 主版本号 */
    uint8_t minor;          /**< 次版本号 */
    uint8_t patch;          /**< 补丁号 */
    uint8_t reserved;       /**< 保留 */
} version_packet_t;
#pragma pack(pop)

/**
 * @brief 应答包 (CMD_ACK / CMD_NACK)
 */
#pragma pack(push, 1)
typedef struct {
    uint8_t original_cmd;   /**< 原始命令码 */
    uint8_t status;         /**< 状态码: 0=成功, 其他=错误码 */
} ack_packet_t;
#pragma pack(pop)

/* ========================================================================== */
/*                          协议帧结构                                         */
/* ========================================================================== */

/**
 * @brief 协议帧结构
 */
typedef struct {
    uint8_t header[2];              /**< 帧头 [0xAA, 0x55] */
    uint8_t cmd;                    /**< 命令码 */
    uint8_t len;                    /**< 数据长度 */
    uint8_t data[PROTO_MAX_DATA_LEN]; /**< 数据区 */
    uint8_t checksum;               /**< 校验和 */
    uint8_t tail[2];                /**< 帧尾 [0x0D, 0x0A] */
} protocol_frame_t;

/* ========================================================================== */
/*                          函数接口                                           */
/* ========================================================================== */

/**
 * @brief 计算校验和 (XOR)
 * @param cmd 命令码
 * @param data 数据指针
 * @param len 数据长度
 * @return 校验和
 */
uint8_t protocol_calc_checksum(uint8_t cmd, const uint8_t *data, uint8_t len);

/**
 * @brief 构建并发送数据帧
 * @param cmd 命令码
 * @param data 数据指针
 * @param len 数据长度
 */
void protocol_send_frame(uint8_t cmd, const void *data, uint8_t len);

/**
 * @brief 发送电流数据 (仅包含3个有效通道: M2/M3/M4)
 */
void protocol_send_current_data(void);

/**
 * @brief 发送原始ADC数据
 */
void protocol_send_raw_adc(void);

/**
 * @brief 处理接收到的帧
 * @param frame 帧指针
 */
void protocol_process_frame(const protocol_frame_t *frame);

/**
 * @brief 协议解析状态机
 * @param byte 接收到的字节
 */
void protocol_parse_byte(uint8_t byte);

#ifdef __cplusplus
}
#endif

#endif /* __UART_PROTOCOL_H */
