

#include "system.h"

u8 Flag_Stop=0, Last_Flag_Stop=1;   

int Divisor_Mode;

u8 Car_Mode=0; 

int Servo;  

float RC_Velocity=500; 

float Move_X, Move_Y, Move_Z;   

u8 Fault_Enable=0;
u8 Fault_Type=0;
u8 Fault_Wheel_Mask=0;
float Fault_Alpha_A=1.0f;
float Fault_Alpha_B=1.0f;
float Fault_Alpha_C=1.0f;

float Velocity_KP=300,Velocity_KI=300;  

Smooth_Control smooth_control;  

Motor_parameter MOTOR_A,MOTOR_B,MOTOR_C,MOTOR_D;  

float Encoder_precision; 

float Wheel_perimeter; 

float Wheel_spacing; 

float Wheel_axlespacing; 

float Omni_turn_radiaus; 

u8 PS2_ON_Flag=0, APP_ON_Flag=0, Remote_ON_Flag=0, CAN_ON_Flag=0, Usart_ON_Flag=0; 

u8 Flag_Left, Flag_Right, Flag_Direction=0, Turn_Flag; 

u8 PID_Send; 

float PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; 

u8 Get_Charging_HardWare=0;
u8 charger_check=0;

float Target_Angle=0.0f;      
float Current_Angle=0.0f;     
float Yaw_Zero_Offset=0.0f;   
float Angle_KP=0.05f;        
float Angle_KI=0.0f;          
float Angle_KD=1.80f;        
float Angle_PID_Output=0.0f;  
u8 Angle_Control_Enable=1;    
u8 Manual_Turn_Active=0;      
u8 Set_Current_Angle_Zero_Flag=0; 
u8 External_Heading_Enable=1;
u8 External_Heading_Valid=0;
float External_Heading_Angle=0.0f;
u32 External_Heading_Last_Tick=0;

void systemInit(void)
{       
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	
	
	delay_init(168);			                                            
	
	
	
	LED_Init();                     
	    
  
  
	Buzzer_Init();  
	
	
	
	Enable_Pin();

  
  
	OLED_Init();     
	
	
	
	KEY_Init();	
	
	
	
	
	uart1_init(115200);	  
	
	
	
	
	uart4_init(9600);  
	
	
	
	
	uart3_init(115200);

  
  
	CAN1_Mode_Init(1,7,6,3,0);      
	
	
	
	
 	Adc_Init();  
  
  
  
	Robot_Select();                 
	             
	
	
	Encoder_Init_TIM2(); 
	
  
	Encoder_Init_TIM3(); 
  
  
	Encoder_Init_TIM4();
	
  
	Encoder_Init_TIM5();  
	
	
	
	
	MiniBalance_Motor_Init();  

  
  
	MiniBalance_PWM_Init(16799,0);  

  
  
	I2C_GPIOInit();

  
	
  
	MPU6050_initialize();
	
	
	
		TIM1_Cap_Init(9999,168-1);  
	
	
	PS2_Init();
	
	
  
	PS2_SetInit();		 

	
	base_vol = Get_battery_volt();
	
	
	delay_ms(100);
	Find_Charging_HardWare();
	
}

void Find_Charging_HardWare(void)
{
	u8 tmpdata[8]={1,1,1,1,1,1,1,1};
	CAN1_Send_EXTid_Num(0x12345678,tmpdata);
}
