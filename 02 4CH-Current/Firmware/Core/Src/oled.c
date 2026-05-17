#include "oledfont.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>

// OLED 显示屏的 I2C 地址定义
#define OLED_ADD 0x78 
#define OLED_ADDRESS  0x78 // OLED 地址（设备 I2C 地址）

/**
  * @brief  oled_cmd：发送命令到OLED显示屏 
  * @param  i2c_cmd: 发送给 OLED 的命令数据
  * @retval None
  */
static void oled_cmd(uint8_t i2c_cmd)
{
    uint8_t *cmd;
    cmd = &i2c_cmd;
    HAL_I2C_Mem_Write(&hi2c1, OLED_ADD, 0x00, 
                      I2C_MEMADD_SIZE_8BIT, cmd, 1,
                      100);
}

/**
  * @brief  oled_data：发送数据到 OLED 显示屏 
  * @param  i2c_data: 发送到 OLED 的数据
  * @retval None
  */
static void oled_data(uint8_t i2c_data)
{
    uint8_t *data;
    data = &i2c_data;
    HAL_I2C_Mem_Write(&hi2c1, OLED_ADD, 0x40, 
                      I2C_MEMADD_SIZE_8BIT, data, 1,
                      100);
}

/**
  * @brief  oled_setPos：设置 OLED 显示的起始位置 
  * @param  x: 水平位置 (0~127)
  * @param  y: 垂直位置 (0~7)
  * @retval None
  */
static void oled_setPos(uint8_t x, uint8_t y) 
{
    oled_cmd(0xb0 + y);    // 设置页地址
    oled_cmd(((x & 0xf0) >> 4) | 0x10);  // 设置列高地址
    oled_cmd((x & 0x0f) | 0x01);  // 设置列低地址
}

/**
  * @brief  oled_full：填充屏幕 
  * @param  data: 要填充的单个数据字节（通常为 0x00 或 0xFF）
  * @retval None
  */
void oled_full(uint8_t data)
{
    uint8_t m, n;
    for(m = 0; m < 8; m++)  // 遍历 8 页
    {
        oled_cmd(0xb0 + m);  // 设置页地址
        oled_cmd(0x00);      // 设置低列地址
        oled_cmd(0x10);      // 设置高列地址
        for(n = 0; n < 128; n++)  // 遍历 128 列
        {
            oled_data(data);  // 填充数据
        }
    }
} 

/**
  * @brief  oled_cls：清空屏幕
  * @param  None
  * @retval None
  */
void oled_cls(void)
{
    oled_full(0x00);  // 以 0x00 填充屏幕，清空显示
}

/**
  * @brief  oled_on：打开 OLED 屏幕
  * @param  None
  * @retval None
  */
void oled_on(void)
{
    oled_cmd(0X8D);  // 设置电荷泵
    oled_cmd(0X14);  // 打开电荷泵
    oled_cmd(0XAF);  // 打开 OLED 显示
}

/**
  * @brief  oled_off：关闭 OLED 屏幕
  * @param  None
  * @retval None
  */
void oled_off(void)
{
    oled_cmd(0X8D);  // 设置电荷泵
    oled_cmd(0X10);  // 关闭电荷泵
    oled_cmd(0XAE);  // 关闭 OLED 显示
}

/**
  * @brief  oled_init：初始化 OLED 显示屏
  * @param  None
  * @retval None
  */
void oled_init(void)
{
    HAL_Delay(100);  // 延迟等待 OLED 启动

    // 初始化 OLED 控制命令
    oled_cmd(0xAE); // 关闭显示
    oled_cmd(0x20); // 设置内存寻址模式
    oled_cmd(0x10); // 水平寻址模式
    oled_cmd(0xb0); // 设置页起始地址
    oled_cmd(0xc8); // 设置 COM 输出扫描方向
    oled_cmd(0x00); // 设置列起始地址
    oled_cmd(0x10); // 设置列高地址
    oled_cmd(0x40); // 设置起始行地址
    oled_cmd(0x81); // 设置对比度
    oled_cmd(0xff); // 最大对比度
    oled_cmd(0xa1); // 设置段重映射
    oled_cmd(0xa6); // 正常显示模式
    oled_cmd(0xa8); // 设置多路复用比例
    oled_cmd(0x3F); // 设置 64 行
    oled_cmd(0xa4); // 设置输出跟随 RAM 内容
    oled_cmd(0xd3); // 设置显示偏移
    oled_cmd(0x00); // 无偏移
    oled_cmd(0xd5); // 设置显示时钟
    oled_cmd(0xf0); // 设置时钟分频
    oled_cmd(0xd9); // 设置预充电周期
    oled_cmd(0x22); // 设置周期
    oled_cmd(0xda); // 设置 COM 引脚硬件配置
    oled_cmd(0x12); // 配置硬件
    oled_cmd(0xdb); // 设置 VCOMH 电压
    oled_cmd(0x20); // 设置电压（0x20 对应 0.77Vcc）
    oled_cmd(0x8d); // 启用 DC-DC 转换器
    oled_cmd(0x14); // 启用
    oled_cmd(0xaf); // 打开 OLED 显示面板
    
    oled_full(0x00); // 清空屏幕
}

/**
  * @brief  oled_display_char：显示字符
  * @param  x, y: 位置坐标（0~127, 0~7）
  * @param  chr: 要显示的字符
  * @param  Char_Size: 字符大小（8x6 或 8x16）
  * @retval None
  */
void oled_display_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{       
    unsigned char c = 0, i = 0;    
    c = chr - ' ';  // 获取字符的索引
    if(x > 128 - 1) {x = 0; y = y + 2;}  // 超过显示范围时，换行显示
    if(Char_Size == 16)
    {
        oled_setPos(x, y);    
        for(i = 0; i < 8; i++) {
            oled_data(F8X16[c * 16 + i]);  // 16x8 字体显示
        }
        oled_setPos(x, y + 1);
        for(i = 0; i < 8; i++) {
            oled_data(F8X16[c * 16 + i + 8]);  // 显示第二行
        }
    }
    else 
    {    
        oled_setPos(x, y);
        for(i = 0; i < 6; i++) {
            oled_data(F6x8[c][i]);  // 6x8 字体显示
        }
    }
}

/**
  * @brief  oled_show_string：显示字符串
  * @param  x, y: 显示位置（0~127, 0~7）
  * @param  ch[]: 要显示的字符串
  * @param  TextSize: 字符大小（1：6x8，2：8x16）
  * @retval None
  */
void oled_show_string(uint8_t x, uint8_t y, char ch[], uint8_t TextSize)
{
    uint8_t c = 0, i = 0, j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 126)
                {
                    x = 0;
                    y++;
                }
                oled_setPos(x, y);
                for(i = 0; i < 6; i++)
                    oled_data(F6x8[c][i]);
                x += 6;
                j++;
            }
        } break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                oled_setPos(x, y);
                for(i = 0; i < 8; i++)
                    oled_data(F8X16[c * 16 + i]);
                oled_setPos(x, y + 1);
                for(i = 0; i < 8; i++)
                    oled_data(F8X16[c * 16 + i + 8]);
                x += 8;
                j++;
            }
        } break;
    }
}

/**
  * @brief  oled_showNum：显示数字
  * @param  x, y: 显示位置（0~127, 0~7）
  * @param  num: 要显示的数字
  * @param  len: 数字长度
  * @param  size1: 字符大小（12/16/24）
  * @retval None
  */

// 计算 m^n
uint32_t oled_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

void oled_showNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1)
{
    uint8_t t, temp;
    for(t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if(temp == 0)
        {
            oled_display_char(x + (size1 / 2) * t, y, '0', size1);
        }
        else 
        {
            oled_display_char(x + (size1 / 2) * t, y, temp + '0', size1);
        }
    }
}


