/**
 ******************************************************************************
 * @file           : current_filter.c
 * @brief          : 电流滤波器实现 (双重滤波: EMA + 移动平均)
 * @author         : 4CH-Current Project
 * 
 * 使用两级滤波:
 * 1. 指数移动平均 (EMA) - 快速响应，平滑高频噪声
 * 2. 移动平均 - 进一步平滑输出
 ******************************************************************************
 */

#include "current_filter.h"
#include <string.h>

/** EMA平滑系数 (0.01~0.1: 越小越平滑，响应越慢) */
#define EMA_ALPHA       0.02f

/** 1 - EMA_ALPHA (预计算优化) */
#define EMA_BETA        (1.0f - EMA_ALPHA)

/**
 * @brief 初始化滤波器
 */
void filter_init(filter_context_t *ctx)
{
    if (ctx == NULL) {
        return;
    }
    
    memset(ctx->buffer, 0, sizeof(ctx->buffer));
    ctx->write_index = 0;
    ctx->sample_count = 0;
    ctx->sum = 0.0f;
    ctx->initialized = false;  // 首次采样时设置初始值
}

/**
 * @brief 添加采样值到滤波器
 * 
 * 第一级: EMA滤波
 * 第二级: 移动平均滤波
 */
void filter_add_sample(filter_context_t *ctx, float sample)
{
    if (ctx == NULL) {
        return;
    }
    
    float ema_output;
    
    /* 第一级: EMA滤波 */
    if (!ctx->initialized) {
        /* 首次采样，直接使用输入值作为初始值 */
        ema_output = sample;
        ctx->initialized = true;
    } else {
        /* EMA公式: output = alpha * input + (1 - alpha) * last_output */
        /* 使用buffer[0]存储上一次EMA输出 */
        float last_ema = ctx->buffer[0];
        ema_output = EMA_ALPHA * sample + EMA_BETA * last_ema;
    }
    
    /* 保存EMA输出用于下次计算 */
    ctx->buffer[0] = ema_output;
    
    /* 第二级: 移动平均滤波 (使用buffer[1]到buffer[FILTER_WINDOW_SIZE-1]) */
    uint16_t ma_start = 1;
    uint16_t ma_size = FILTER_WINDOW_SIZE - 1;
    uint16_t ma_index = ma_start + ((ctx->write_index) % ma_size);
    
    /* 如果缓冲区已满，减去最旧的值 */
    if (ctx->sample_count >= ma_size) {
        ctx->sum -= ctx->buffer[ma_index];
    } else {
        ctx->sample_count++;
    }
    
    /* 添加EMA输出到移动平均缓冲区 */
    ctx->buffer[ma_index] = ema_output;
    ctx->sum += ema_output;
    
    /* 更新写入索引 */
    ctx->write_index = (ctx->write_index + 1) % ma_size;
}

/**
 * @brief 获取滤波后的平均值
 */
float filter_get_average(filter_context_t *ctx)
{
    if (ctx == NULL || !ctx->initialized || ctx->sample_count == 0) {
        return 0.0f;
    }
    
    return ctx->sum / (float)ctx->sample_count;
}

/**
 * @brief 重置滤波器
 */
void filter_reset(filter_context_t *ctx)
{
    filter_init(ctx);
}
