#ifndef __USRATX_H
#define __USRATX_H 

#include "stdio.h"
#include "sys.h"
#include "system.h"

#define DATA_STK_SIZE   512 
#define DATA_TASK_PRIO  4

#define FRAME_HEADER      0X7B 
#define FRAME_TAIL        0X7D 
#define SEND_DATA_SIZE    30
#define RECEIVE_DATA_SIZE 13

#define FAULT_CONFIG_MODE 4
#define DRIVE_ABNORMAL_FAULT 1
#define FAULT_WHEEL_A 0x01
#define FAULT_WHEEL_B 0x02
#define FAULT_WHEEL_C 0x04

#define AutoCharge_HEADER      0X7C 
#define AutoCharge_TAIL        0X7F 
#define AutoCharge_DATA_SIZE    8

typedef struct __Mpu6050_Data_ 
{
	short X_data; 
	short Y_data; 
	short Z_data; 
}Mpu6050_Data;

typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; 
		short X_speed;	            
		short Y_speed;              
		short Z_speed;              
		short Power_Voltage;        
		short Wheel_Speed_A;
		short Wheel_Speed_B;
		short Wheel_Speed_C;
		Mpu6050_Data Accelerometer; 
		Mpu6050_Data Gyroscope;     
		unsigned char Frame_Tail;
	}Sensor_Str;
}SEND_DATA;

typedef struct _SEND_AutoCharge_DATA_  
{
	unsigned char buffer[AutoCharge_DATA_SIZE];
	struct _AutoCharge_Str_
	{
		unsigned char Frame_Header; 
		short Charging_Current;	    
		unsigned char RED;          
		unsigned char Charging;     
		unsigned char yuliu;		
		unsigned char Frame_Tail;   
	}AutoCharge_Str;
}SEND_AutoCharge_DATA;

typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; 
		float X_speed;	            
		float Y_speed;              
		float Z_speed;              
		unsigned char Frame_Tail;   
	}Control_Str;
}RECEIVE_DATA;

void data_task(void *pvParameters);
void data_transition(void);
void USART1_SEND(void);
void USART3_SEND(void);
void CAN_SEND(void);
void uart1_init(u32 bound);
void uart4_init(u32 bound);
void uart3_init(u32 bound);
int USART1_IRQHandler(void);
int UART4_IRQHandler(void);
int USART3_IRQHandler(void);

float XYZ_Target_Speed_transition(u8 High,u8 Low);
float Fault_Alpha_transition(u8 High,u8 Low);
void Apply_Fault_Config(void);
void usart1_send(u8 data);
void usart4_send(u8 data);
void usart3_send(u8 data);
u8 Check_Sum(unsigned char Count_Number,unsigned char Mode);
u8 Check_Sum_AutoCharge(unsigned char Count_Number,unsigned char Mode);
u8 AT_Command_Capture(u8 uart_recv);
void _System_Reset_(u8 uart_recv);

#if Mec
void Motion_analysis_transformation(float Encoder_A,float Encoder_B,float Encoder_C,float Encoder_D);
#elif Omni
void Motion_analysis_transformation(float Encoder_A,float Encoder_B,float Encoder_C);
#endif

#endif
