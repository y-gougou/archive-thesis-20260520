/**
 ******************************************************************************
 * @file           : current_filter.h
 * @brief          : 电流滤波器接口 (EMA + 移动平均)
 * @author         : 4CH-Current Project
 ******************************************************************************
 */

#ifndef __CURRENT_FILTER_H
#define __CURRENT_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "current_types.h"

/**
 * @brief 初始化滤波器
 * @param ctx 滤波器上下文指针
 */
void filter_init(filter_context_t *ctx);

/**
 * @brief 添加采样值到滤波器
 * @param ctx 滤波器上下文指针
 * @param sample 新的采样值
 */
void filter_add_sample(filter_context_t *ctx, float sample);

/**
 * @brief 获取滤波后的平均值
 * @param ctx 滤波器上下文指针
 * @return 平均值
 */
float filter_get_average(filter_context_t *ctx);

/**
 * @brief 重置滤波器
 * @param ctx 滤波器上下文指针
 */
void filter_reset(filter_context_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* __CURRENT_FILTER_H */
