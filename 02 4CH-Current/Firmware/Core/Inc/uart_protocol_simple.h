/**
 ******************************************************************************
 * @file           : uart_protocol_simple.h
 * @brief          : 简化CSV文本协议头文件
 * @author         : 4CH-Current Project
 ******************************************************************************
 */

#ifndef __UART_PROTOCOL_SIMPLE_H
#define __UART_PROTOCOL_SIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 使用简化CSV协议发送电流数据
 *
 * 格式: $CH,ch0,ch1,ch2,ch3\r\n
 */
void protocol_send_current_data_simple(void);

/**
 * @brief 使用CSV协议发送原始ADC数据
 *
 * 格式: $RA,adc0,adc1,adc2,adc3\r\n
 */
void protocol_send_raw_adc_simple(void);

#ifdef __cplusplus
}
#endif

#endif /* __UART_PROTOCOL_SIMPLE_H */
