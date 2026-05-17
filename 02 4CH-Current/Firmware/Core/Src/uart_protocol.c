/**
 ******************************************************************************
 * @file           : uart_protocol.c
 * @brief          : 串口通信协议实现 (支持自定义二进制协议和FireWater文本协议)
 * @author         : 4CH-Current Project
 ******************************************************************************
 */

#include "uart_protocol.h"
#include "usart.h"
#include "current_types.h"
#include <string.h>
#include <stdio.h>

/* ========================================================================== */
/*                          外部变量声明                                       */
/* ========================================================================== */

extern float g_current_values[CHANNEL_COUNT];
extern volatile uint16_t g_adc_raw_buffer[CHANNEL_COUNT];

/* ========================================================================== */
/*                          二进制协议实现 (Type 0)                           */
/* ========================================================================== */
#if (UART_PROTOCOL_TYPE == 0)

/** 发送缓冲区 */
static uint8_t tx_buffer[PROTO_MAX_FRAME_LEN];

/**
 * @brief 计算校验和 (XOR)
 */
uint8_t protocol_calc_checksum(uint8_t cmd, const uint8_t *data, uint8_t len)
{
    uint8_t checksum = cmd ^ len;

    for (uint8_t i = 0; i < len; i++) {
        checksum ^= data[i];
    }

    return checksum;
}

/**
 * @brief 构建并发送数据帧
 */
void protocol_send_frame(uint8_t cmd, const void *data, uint8_t len)
{
    uint8_t idx = 0;

    /* 帧头 */
    tx_buffer[idx++] = PROTO_HEADER_1;
    tx_buffer[idx++] = PROTO_HEADER_2;

    /* 命令码 */
    tx_buffer[idx++] = cmd;

    /* 数据长度 */
    tx_buffer[idx++] = len;

    /* 数据区 */
    if (len > 0 && data != NULL) {
        memcpy(&tx_buffer[idx], data, len);
        idx += len;
    }

    /* 校验和 */
    tx_buffer[idx++] = protocol_calc_checksum(cmd, (const uint8_t *)data, len);

    /* 帧尾 */
    tx_buffer[idx++] = PROTO_TAIL_1;
    tx_buffer[idx++] = PROTO_TAIL_2;

    /* 发送 */
    HAL_UART_Transmit(&huart2, tx_buffer, idx, 100);
    HAL_UART_Transmit(&huart1, tx_buffer, idx, 100);
}

/**
 * @brief 发送电流数据 (仅3个有效通道: M2/M3/M4)
 *
 * 数据区格式 (12字节):
 * | CH1电流(M2) | CH2电流(M3) | CH3电流(M4) |
 */
void protocol_send_current_data(void)
{
    current_packet_t packet;

    /* 仅发送有效通道: g_current_values[1]=M2, [2]=M3, [3]=M4 */
    packet.ch0_current = g_current_values[1];  /* M2 */
    packet.ch1_current = g_current_values[2];  /* M3 */
    packet.ch2_current = g_current_values[3];  /* M4 */

    protocol_send_frame(CMD_REPORT_CURRENT, &packet, sizeof(packet));
}

/**
 * @brief 发送原始ADC数据
 */
void protocol_send_raw_adc(void)
{
    raw_adc_packet_t packet;

    packet.ch0_adc = g_adc_raw_buffer[0];
    packet.ch1_adc = g_adc_raw_buffer[1];
    packet.ch2_adc = g_adc_raw_buffer[2];
    packet.ch3_adc = g_adc_raw_buffer[3];

    protocol_send_frame(CMD_QUERY_RAW_ADC, &packet, sizeof(packet));
}

/**
 * @brief 发送版本信息
 */
static void send_version(void)
{
    version_packet_t ver;
    ver.major = 1;
    ver.minor = 0;
    ver.patch = 0;
    ver.reserved = 0;

    protocol_send_frame(CMD_QUERY_VERSION, &ver, sizeof(ver));
}

/**
 * @brief 发送应答
 */
static void send_ack(uint8_t original_cmd, uint8_t status)
{
    ack_packet_t ack;
    ack.original_cmd = original_cmd;
    ack.status = status;

    protocol_send_frame(CMD_ACK, &ack, sizeof(ack));
}

/**
 * @brief 处理接收到的帧
 */
void protocol_process_frame(const protocol_frame_t *frame)
{
    if (frame == NULL) {
        return;
    }

    switch (frame->cmd) {
        case CMD_QUERY_CURRENT:
            protocol_send_current_data();
            break;

        case CMD_QUERY_RAW_ADC:
            protocol_send_raw_adc();
            break;

        case CMD_QUERY_VERSION:
            send_version();
            break;

        case CMD_RESET:
            send_ack(CMD_RESET, 0x00);
            HAL_Delay(100);
            NVIC_SystemReset();
            break;

        default:
            send_ack(frame->cmd, 0x01);  /* 未知命令 */
            break;
    }
}

/**
 * @brief 协议解析状态机
 *
 * @param byte 接收到的字节
 */
void protocol_parse_byte(uint8_t byte)
{
    static enum {
        STATE_IDLE,
        STATE_HEADER2,
        STATE_CMD,
        STATE_LEN,
        STATE_DATA,
        STATE_CHECKSUM,
        STATE_TAIL1,
        STATE_TAIL2
    } state = STATE_IDLE;

    static protocol_frame_t rx_frame;
    static uint8_t data_idx = 0;

    switch (state) {
        case STATE_IDLE:
            if (byte == PROTO_HEADER_1) state = STATE_HEADER2;
            break;

        case STATE_HEADER2:
            if (byte == PROTO_HEADER_2) state = STATE_CMD;
            else state = STATE_IDLE;
            break;

        case STATE_CMD:
            rx_frame.cmd = byte;
            state = STATE_LEN;
            break;

        case STATE_LEN:
            rx_frame.len = (byte > PROTO_MAX_DATA_LEN) ? PROTO_MAX_DATA_LEN : byte;
            data_idx = 0;
            if (rx_frame.len > 0) state = STATE_DATA;
            else state = STATE_CHECKSUM;
            break;

        case STATE_DATA:
            rx_frame.data[data_idx++] = byte;
            if (data_idx >= rx_frame.len) state = STATE_CHECKSUM;
            break;

        case STATE_CHECKSUM:
            rx_frame.checksum = byte;
            state = STATE_TAIL1;
            break;

        case STATE_TAIL1:
            if (byte == PROTO_TAIL_1) state = STATE_TAIL2;
            else state = STATE_IDLE;
            break;

        case STATE_TAIL2:
            if (byte == PROTO_TAIL_2) {
                /* 校验 CRC */
                uint8_t cal_crc = protocol_calc_checksum(rx_frame.cmd, rx_frame.data, rx_frame.len);
                if (cal_crc == rx_frame.checksum) {
                    protocol_process_frame(&rx_frame);
                }
            }
            state = STATE_IDLE;
            break;

        default:
            state = STATE_IDLE;
            break;
    }
}

/* ========================================================================== */
/*                          FireWater 协议实现 (Type 1)                       */
/* ========================================================================== */
#elif (UART_PROTOCOL_TYPE == 1)

static uint32_t s_current_seq = 0;

/**
 * @brief 发送电流数据 (统一简单文本协议)
 *
 * 格式: "$CURRENT,ch0,ch1,ch2*XX\r\n"
 * 例如: "$CURRENT,1.2345,-0.1845,0.2500*2F\r\n"
 *
 * 注意: 仅包含3个有效通道 (M2/M3/M4), M1(PA0)无输出已移除
 * 校验和XX: 从$到*的所有ASCII字符的异或值
 */
void protocol_send_current_data(void)
{
    char buf[96];
#if UART_TEXT_FRAME_WITH_SEQ
    uint32_t seq = s_current_seq++;

    /* 格式: $CURRENT,ch0,ch1,ch2*XX\r\n (仅3通道M2/M3/M4) */
    int len = snprintf(buf, sizeof(buf), "$CURRENT,%lu,%.4f,%.4f,%.4f*",
                       (unsigned long)seq,
                       g_current_values[1],  /* M2 */
                       g_current_values[2],  /* M3 */
                       g_current_values[3]); /* M4 */
#else
    int len = snprintf(buf, sizeof(buf), "$CURRENT,%.4f,%.4f,%.4f*",
                       g_current_values[1],  /* M2 */
                       g_current_values[2],  /* M3 */
                       g_current_values[3]); /* M4 */
#endif

    /* 计算校验和 (从$到*之前所有字符的异或，不含*) */
    uint8_t checksum = 0;
    for (int i = 0; i < len - 1; i++) {
        checksum ^= (uint8_t)buf[i];
    }

    /* 完成帧: 添加校验和和回车换行 */
    len += snprintf(buf + len, sizeof(buf) - len, "%02X\r\n", checksum);

    if (len > 0) {
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, 100);
#if UART_SEND_USART1_ENABLE
        HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 100);
#endif
    }
}

/* 以下函数在文本协议下为空实现或简化实现 */
void protocol_send_raw_adc(void) {}
void protocol_parse_byte(uint8_t byte) { (void)byte; }
uint8_t protocol_calc_checksum(uint8_t cmd, const uint8_t *data, uint8_t len) { return 0; }
void protocol_send_frame(uint8_t cmd, const void *data, uint8_t len) { (void)cmd; (void)data; (void)len; }
void protocol_process_frame(const protocol_frame_t *frame) { (void)frame; }

#endif
