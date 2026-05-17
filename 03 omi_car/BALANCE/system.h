#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "FreeRTOSConfig.h"

#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "balance.h"
#include "led.h"
#include "oled.h"
#include "usart.h"
#include "usartx.h"
#include "adc.h"
#include "can.h"
#include "motor.h"
#include "timer.h"
#include "encoder.h"
#include "show.h"								   
#include "pstwo.h"
#include "key.h"
#include "robot_select_init.h"
#include "I2C.h"
#include "HubDriver.h"
#include "HubDriverCan.h"
#include "MPU6050.h"
#include "AutoRecharge.h"
#include "filter.h"

#define Omni 1
#define Mec  0

typedef struct  
{
	float Encoder;     
	float Encoder_Rpm;   
	float Control_Rpm;   
	float Motor_Pwm;   
	float Target;      
	float Velocity_KP; 
	float	Velocity_KI; 
}Motor_parameter;

typedef struct  
{
	float VX;
	float VY;
	float VZ;
}Smooth_Control;

extern u8 Flag_Stop, Last_Flag_Stop;

extern int Divisor_Mode;   
extern u8 Car_Mode;
extern float RC_Velocity;
extern float Move_X,Move_Y,Move_Z; 
extern u8 Fault_Enable;
extern u8 Fault_Type;
extern u8 Fault_Wheel_Mask;
extern float Fault_Alpha_A, Fault_Alpha_B, Fault_Alpha_C;
extern float Velocity_KP,Velocity_KI;	
extern Smooth_Control smooth_control;
extern Motor_parameter MOTOR_A,MOTOR_B,MOTOR_C,MOTOR_D;
extern float Encoder_precision;
extern float Wheel_perimeter; 
extern float Wheel_spacing; 
extern float Wheel_axlespacing; 
extern float Omni_turn_radiaus; 
extern u8 PS2_ON_Flag, APP_ON_Flag, Remote_ON_Flag, CAN_ON_Flag, Usart_ON_Flag;   
extern u8 Flag_Left, Flag_Right, Flag_Direction, Turn_Flag; 
extern u8 PID_Send; 
extern float PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;
extern int robot_mode_check_flag;

extern u8 Get_Charging_HardWare;
extern u8  charger_check;
void Find_Charging_HardWare(void);

extern float Target_Angle;      
extern float Current_Angle;     
extern float Yaw_Zero_Offset;   
extern float Angle_KP;          
extern float Angle_KI;          
extern float Angle_KD;          
extern float Angle_PID_Output;  
extern u8 Angle_Control_Enable;
extern u8 Manual_Turn_Active;
extern u8 Set_Current_Angle_Zero_Flag;
extern u8 External_Heading_Enable;
extern u8 External_Heading_Valid;
extern float External_Heading_Angle;
extern u32 External_Heading_Last_Tick;

void systemInit(void);

 

#define CONTROL_DELAY		750

#define CAR_NUMBER    7      
#define RATE_1_HZ		  1
#define RATE_5_HZ		  5
#define RATE_10_HZ		10
#define RATE_20_HZ		20
#define RATE_25_HZ		25
#define RATE_50_HZ		50
#define RATE_100_HZ		100
#define RATE_200_HZ 	200
#define RATE_250_HZ 	250
#define RATE_500_HZ 	500
#define RATE_1000_HZ 	1000
 

#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stdarg.h"
#endif 
