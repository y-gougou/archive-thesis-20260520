#include "usartx.h"
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;
SEND_AutoCharge_DATA Send_AutoCharge_Data;
extern int Time_count;

float Fault_Alpha_transition(u8 High,u8 Low)
{
    short transition;
    transition=((High<<8)+Low);
    if(transition < 0) transition = 0;
    if(transition > 1000) transition = 1000;
    return transition / 1000.0f;
}

void Apply_Fault_Config(void)
{
    Fault_Type = Receive_Data.buffer[2];
    Fault_Enable = Receive_Data.buffer[3] ? 1 : 0;
    Fault_Wheel_Mask = Receive_Data.buffer[4] & (FAULT_WHEEL_A | FAULT_WHEEL_B | FAULT_WHEEL_C);
    Fault_Alpha_A = Fault_Alpha_transition(Receive_Data.buffer[5], Receive_Data.buffer[6]);
    Fault_Alpha_B = Fault_Alpha_transition(Receive_Data.buffer[7], Receive_Data.buffer[8]);
    Fault_Alpha_C = Fault_Alpha_transition(Receive_Data.buffer[9], Receive_Data.buffer[10]);

    if(!Fault_Enable || Fault_Type != DRIVE_ABNORMAL_FAULT)
    {
        Fault_Enable = 0;
        Fault_Wheel_Mask = 0;
        Fault_Alpha_A = 1.0f;
        Fault_Alpha_B = 1.0f;
        Fault_Alpha_C = 1.0f;
    }
}

void data_task(void *pvParameters)
{
	 u32 lastWakeTime = getSysTickCnt();
	
   while(1)
    {	
			
			
			vTaskDelayUntil(&lastWakeTime, F2T(RATE_20_HZ));
			
			
			data_transition(); 
			
			
			USART1_SEND(); 
			USART3_SEND();     
				CAN_SEND();        

		}
}

void data_transition(void)
{
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER; 
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL;     
	
	
	
	
	#if Mec
	Motion_analysis_transformation(MOTOR_A.Encoder,MOTOR_B.Encoder,MOTOR_C.Encoder,MOTOR_D.Encoder); 
	#elif Omni
	Motion_analysis_transformation(MOTOR_A.Encoder,MOTOR_B.Encoder,MOTOR_C.Encoder); 
	#endif

	Send_Data.Sensor_Str.Wheel_Speed_A = (short)(MOTOR_A.Encoder * 1000);
	Send_Data.Sensor_Str.Wheel_Speed_B = (short)(MOTOR_B.Encoder * 1000);
	Send_Data.Sensor_Str.Wheel_Speed_C = (short)(MOTOR_C.Encoder * 1000);
	
	
	Send_Data.Sensor_Str.Accelerometer.X_data= accel[1]; 
	Send_Data.Sensor_Str.Accelerometer.Y_data=-accel[0]; 
	Send_Data.Sensor_Str.Accelerometer.Z_data= accel[2]; 
	
	
	Send_Data.Sensor_Str.Gyroscope.X_data= gyro[1]; 
	Send_Data.Sensor_Str.Gyroscope.Y_data=-gyro[0]; 
	if(Flag_Stop==0) 
		
	  
		Send_Data.Sensor_Str.Gyroscope.Z_data=gyro[2];  
	else  
		
    
		Send_Data.Sensor_Str.Gyroscope.Z_data=0;  
	
	
	
	Send_Data.Sensor_Str.Power_Voltage = Voltage*1000; 
	
	Send_Data.buffer[0]=Send_Data.Sensor_Str.Frame_Header; 
  Send_Data.buffer[1]=Flag_Stop; 
	
	
	
	Send_Data.buffer[2]=Send_Data.Sensor_Str.X_speed >>8; 
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed ;    
	Send_Data.buffer[4]=Send_Data.Sensor_Str.Y_speed>>8;  
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed;     
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Z_speed >>8; 
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed ;    
	
	
	
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Accelerometer.X_data>>8; 
	Send_Data.buffer[9]=Send_Data.Sensor_Str.Accelerometer.X_data;   
	Send_Data.buffer[10]=Send_Data.Sensor_Str.Accelerometer.Y_data>>8;
	Send_Data.buffer[11]=Send_Data.Sensor_Str.Accelerometer.Y_data;
	Send_Data.buffer[12]=Send_Data.Sensor_Str.Accelerometer.Z_data>>8;
	Send_Data.buffer[13]=Send_Data.Sensor_Str.Accelerometer.Z_data;
	
	
	
	Send_Data.buffer[14]=Send_Data.Sensor_Str.Gyroscope.X_data>>8;
	Send_Data.buffer[15]=Send_Data.Sensor_Str.Gyroscope.X_data;
	Send_Data.buffer[16]=Send_Data.Sensor_Str.Gyroscope.Y_data>>8;
	Send_Data.buffer[17]=Send_Data.Sensor_Str.Gyroscope.Y_data;
	Send_Data.buffer[18]=Send_Data.Sensor_Str.Gyroscope.Z_data>>8;
	Send_Data.buffer[19]=Send_Data.Sensor_Str.Gyroscope.Z_data;
	
	
	
	Send_Data.buffer[20]=Send_Data.Sensor_Str.Power_Voltage >>8; 
	Send_Data.buffer[21]=Send_Data.Sensor_Str.Power_Voltage; 

	Send_Data.buffer[22]=Send_Data.Sensor_Str.Wheel_Speed_A >>8;
	Send_Data.buffer[23]=Send_Data.Sensor_Str.Wheel_Speed_A;
	Send_Data.buffer[24]=Send_Data.Sensor_Str.Wheel_Speed_B >>8;
	Send_Data.buffer[25]=Send_Data.Sensor_Str.Wheel_Speed_B;
	Send_Data.buffer[26]=Send_Data.Sensor_Str.Wheel_Speed_C >>8;
	Send_Data.buffer[27]=Send_Data.Sensor_Str.Wheel_Speed_C;

	Send_Data.buffer[28]=Check_Sum(28,1);
	
	Send_Data.buffer[29]=Send_Data.Sensor_Str.Frame_Tail;

	
	Send_AutoCharge_Data.AutoCharge_Str.Frame_Header = AutoCharge_HEADER;   
	Send_AutoCharge_Data.AutoCharge_Str.Frame_Tail = AutoCharge_TAIL;		
	Send_AutoCharge_Data.AutoCharge_Str.Charging_Current = (short)Charging_Current;
	
	Send_AutoCharge_Data.AutoCharge_Str.RED = RED_STATE; 
	Send_AutoCharge_Data.AutoCharge_Str.Charging = Charging; 

	Send_AutoCharge_Data.buffer[0] = Send_AutoCharge_Data.AutoCharge_Str.Frame_Header;		
	Send_AutoCharge_Data.buffer[1] = Send_AutoCharge_Data.AutoCharge_Str.Charging_Current>>8;
	Send_AutoCharge_Data.buffer[2] = Send_AutoCharge_Data.AutoCharge_Str.Charging_Current;	
	Send_AutoCharge_Data.buffer[3] = Send_AutoCharge_Data.AutoCharge_Str.RED;				
	Send_AutoCharge_Data.buffer[4] = Send_AutoCharge_Data.AutoCharge_Str.Charging;			
	Send_AutoCharge_Data.buffer[5] = Allow_Recharge;										
	Send_AutoCharge_Data.buffer[6] = Check_Sum_AutoCharge(6,1);								
	Send_AutoCharge_Data.buffer[7] = Send_AutoCharge_Data.AutoCharge_Str.Frame_Tail;		
	
	
}

void USART1_SEND(void)
{
  unsigned char i = 0;	
	
	for(i=0; i<SEND_DATA_SIZE; i++)
	{
		usart1_send(Send_Data.buffer[i]);
	}	 
	if(Get_Charging_HardWare==1)
	{
		
		for(i=0; i<8; i++)
		{
			usart1_send(Send_AutoCharge_Data.buffer[i]);
		}	
	}	
}

void USART3_SEND(void)
{
  unsigned char i = 0;	
	for(i=0; i<SEND_DATA_SIZE; i++)
	{
		usart3_send(Send_Data.buffer[i]);
	}	 
	if(Get_Charging_HardWare==1)
	{
		
		for(i=0; i<8; i++)
		{
			usart3_send(Send_AutoCharge_Data.buffer[i]);
		}	
	}
}

void CAN_SEND(void) 
{
	u8 CAN_SENT[8],i;
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i];
	}
	CAN1_Send_Num(0x101,CAN_SENT);
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i+8];
	}
	CAN1_Send_Num(0x102,CAN_SENT);
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i+16];
	}
	CAN1_Send_Num(0x103,CAN_SENT);

	for(i=0;i<6;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i+24];
	}
	CAN_SENT[6]=0;
	CAN_SENT[7]=0;
	CAN1_Send_Num(0x104,CAN_SENT);
	
	
	if(Get_Charging_HardWare) CAN_Send_AutoRecharge();
}

void uart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10 ,GPIO_AF_USART1);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            
	GPIO_Init(GPIOA, &GPIO_InitStructure);  		          
	
  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  
	
	NVIC_Init(&NVIC_InitStructure);	
	
  
	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART1, &USART_InitStructure); 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	USART_Cmd(USART1, ENABLE);                     
}

void uart4_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11 ,GPIO_AF_UART4);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            
	GPIO_Init(GPIOC, &GPIO_InitStructure);  		          
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
	
	NVIC_Init(&NVIC_InitStructure);	
	
	
	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART4, &USART_InitStructure);      
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); 
	USART_Cmd(UART4, ENABLE);                     
}

void uart3_init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            
	GPIO_Init(GPIOB, &GPIO_InitStructure);  		          
	
  
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  
	
	NVIC_Init(&NVIC_InitStructure);
	
  
	USART_InitStructure.USART_BaudRate = bound; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART3, &USART_InitStructure);      
	
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 
  USART_Cmd(USART3, ENABLE);                     
}

int USART1_IRQHandler(void)
{	
	static u8 Count=0;
	u8 Usart_Receive;
	short angle_raw;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		Usart_Receive = USART_ReceiveData(USART1);
		if(Time_count<CONTROL_DELAY)
			
		  
			return 0;	
		
		
		
    Receive_Data.buffer[Count]=Usart_Receive;
		
		
		
		if(Usart_Receive == FRAME_HEADER||Count>0) 
			Count++; 
		else 
			Count=0;
		
		if (Count == 13) 
		{   
				Count=0; 
				if(Receive_Data.buffer[12] == FRAME_TAIL) 
				{
					
					
					if(Receive_Data.buffer[11] ==Check_Sum(11,0))
				  {		
						
						
						PS2_ON_Flag=0;
						Remote_ON_Flag=0;
						APP_ON_Flag=0;
						CAN_ON_Flag=0;
						Allow_Recharge=0;
						Usart_ON_Flag=1;
					    command_lost_count=0;
						
						
						
						Move_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Move_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Move_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);
						
						
						if(Receive_Data.buffer[2]==1)
						{
							angle_raw = (Receive_Data.buffer[9]<<8) + Receive_Data.buffer[10];
							Target_Angle = Normalize_Angle(angle_raw / 10.0f);
							Angle_Control_Enable = 1;
						}
						else if(Receive_Data.buffer[2]==2)
						{
							Set_Current_Angle_Zero_Flag = 1;
							Angle_Control_Enable = 1;
						}
				  }
			}
		}
	} 
  return 0;
}

int UART4_IRQHandler(void)
{	
	int Usart_Receive;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 
	{	      
		static u8 Flag_PID,i,j,Receive[50],Last_Usart_Receive;
		static float Data;
				
		Usart_Receive=UART4->DR; 

		if( AT_Command_Capture(Usart_Receive) ) return 0;
		_System_Reset_(Usart_Receive);
		
		if(Deviation_Count<CONTROL_DELAY)
			
		  
		  return 0;	

		if(Usart_Receive==0x41&&Last_Usart_Receive==0x41&&APP_ON_Flag==0)
			
		  
			
		  
			PS2_ON_Flag=0,Remote_ON_Flag=0,APP_ON_Flag=1,CAN_ON_Flag=0,Usart_ON_Flag=0;
    Last_Usart_Receive=Usart_Receive;			
	  
		if(Usart_Receive==0x4B) 
			
		  
			Turn_Flag=1;  
	  else	if(Usart_Receive==0x49||Usart_Receive==0x4A) 
      
			
			Turn_Flag=0;	
		
		if(Turn_Flag==0) 
		{
			
			
			if(Usart_Receive>=0x41&&Usart_Receive<=0x48)  
			{	
				Flag_Direction=Usart_Receive-0x40;
			}
			else	if(Usart_Receive<=8)   
			{			
				Flag_Direction=Usart_Receive;
			}	
			else  Flag_Direction=0;
		}
		else if(Turn_Flag==1)
		{
			
			
			if     (Usart_Receive==0x43) Flag_Left=0,Flag_Right=1; 
			else if(Usart_Receive==0x47) Flag_Left=1,Flag_Right=0; 
			else                         Flag_Left=0,Flag_Right=0;
			if     (Usart_Receive==0x41||Usart_Receive==0x45) Flag_Direction=Usart_Receive-0x40;
			else  Flag_Direction=0;
		}
		if(Usart_Receive==0x58)  RC_Velocity=RC_Velocity+100; 
		if(Usart_Receive==0x59)  RC_Velocity=RC_Velocity-100; 
	  
	 
	 
	 if(Usart_Receive==0x7B) Flag_PID=1;   
	 if(Usart_Receive==0x7D) Flag_PID=2;   

	 if( Usart_Receive=='b' ) Allow_Recharge = !Allow_Recharge;
		
	 if(Flag_PID==1) 
	 {
		Receive[i]=Usart_Receive;
		i++;
	 }
	 if(Flag_PID==2) 
	 {
			if(Receive[3]==0x50) 	 PID_Send=1;
			else  if(Receive[1]!=0x23) 
      {								
				for(j=i;j>=4;j--)
				{
					Data+=(Receive[j-1]-48)*pow(10,i-j);
				}
				switch(Receive[1])
				 {
					 case 0x30:  RC_Velocity=Data;break;
					 case 0x31:  Velocity_KP=Data;break;
					 case 0x32:  Velocity_KI=Data;break;
					 case 0x33:  Angle_KP=Data;break;  
					 case 0x34:  Angle_KI=Data;break;  
					 case 0x35:  Angle_KD=Data;break;  
					 case 0x36:  break;
					 case 0x37:  break;
					 case 0x38:  break; 	
				 }
      }		
      
      
			Flag_PID=0;
			i=0;
			j=0;
			Data=0;
			memset(Receive, 0, sizeof(u8)*50); 
	 }
   if(RC_Velocity<0)   RC_Velocity=0; 	 
  }
  return 0;	
}

int USART3_IRQHandler(void)
{	
	static u8 Count=0;
	u8 Usart_Receive;
	short angle_raw;

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		Usart_Receive = USART_ReceiveData(USART3);
		if(Time_count<CONTROL_DELAY)
			
		  
		  return 0;	
		
		
		
    Receive_Data.buffer[Count]=Usart_Receive;
		
		
		
		if(Usart_Receive == FRAME_HEADER||Count>0) 
			Count++; 
		else 
			Count=0;
		
		if (Count == 13) 
		{   
				Count=0; 
				if(Receive_Data.buffer[12] == FRAME_TAIL) 
				{
					
					
					if(Receive_Data.buffer[11] ==Check_Sum(11,0))	 
				  {		
					command_lost_count=0; 
					if(Receive_Data.buffer[1]==0)
					{
						Allow_Recharge=0; 
						
						
						
						PS2_ON_Flag=0;
						Remote_ON_Flag=0;
						APP_ON_Flag=0;
						CAN_ON_Flag=0;
						Usart_ON_Flag=1;
										
						
						
						Move_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Move_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Move_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);
						
										
										if(Receive_Data.buffer[2] != 3)
										{
											Move_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
											Move_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
											Move_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);
										}
										if(Receive_Data.buffer[2]==1)
										{
											angle_raw = (Receive_Data.buffer[9]<<8) + Receive_Data.buffer[10];
											Target_Angle = Normalize_Angle(angle_raw / 10.0f);
											Angle_Control_Enable = 1;
										}
										else if(Receive_Data.buffer[2]==2)
										{
											Set_Current_Angle_Zero_Flag = 1;
											Angle_Control_Enable = 1;
										}
										else if(Receive_Data.buffer[2]==3)
										{
											angle_raw = (Receive_Data.buffer[9]<<8) + Receive_Data.buffer[10];
											External_Heading_Angle = Normalize_Angle(angle_raw / 10.0f);
											External_Heading_Valid = 1;
											External_Heading_Last_Tick = Time_count;
											External_Heading_Enable = 1;
										}
					}
					else if( Receive_Data.buffer[1]==FAULT_CONFIG_MODE )
					{
						Apply_Fault_Config();
					}
					else if( Receive_Data.buffer[1]==1 || Receive_Data.buffer[1]==2 )
					{					
						Allow_Recharge=1; 
						if(Receive_Data.buffer[1]==1 && RED_STATE==0) nav_walk=1; 
						
						
						
						Recharge_UP_Move_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Recharge_UP_Move_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Recharge_UP_Move_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);	
					}
					else if( Receive_Data.buffer[1]==3 )
					{
						
						
						Red_Docker_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Red_Docker_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Red_Docker_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);	
					}
				  }
			}
		}
	} 
return 0;	
}

float XYZ_Target_Speed_transition(u8 High,u8 Low)
{
	
	
	short transition; 
	
	
	
	transition=((High<<8)+Low); 
	return 
		transition/1000+(transition%1000)*0.001; 
}

#if Mec
void Motion_analysis_transformation(float Encoder_A,float Encoder_B,float Encoder_C,float Encoder_D)
{
	Send_Data.Sensor_Str.X_speed = ((Encoder_A+Encoder_B+Encoder_C+Encoder_D)/4)*1000; 
	Send_Data.Sensor_Str.Y_speed = ((Encoder_A-Encoder_B+Encoder_C-Encoder_D)/4)*1000; 
	Send_Data.Sensor_Str.Z_speed = ((-Encoder_A-Encoder_B+Encoder_C+Encoder_D)/4/(Wheel_axlespacing+Wheel_spacing))*1000;
}
#elif Omni
void Motion_analysis_transformation(float Encoder_A,float Encoder_B,float Encoder_C)
{
	Send_Data.Sensor_Str.X_speed = ((Encoder_C-Encoder_B)/2/X_PARAMETER)*1000;
	Send_Data.Sensor_Str.Y_speed = ((Encoder_A*2-Encoder_B-Encoder_C)/3)*1000; 
	Send_Data.Sensor_Str.Z_speed = ((Encoder_A+Encoder_B+Encoder_C)/3/Omni_turn_radiaus)*1000;
}
#endif

void usart1_send(u8 data)
{
	USART1->DR = data;
	while((USART1->SR&0x40)==0);	
}

void usart4_send(u8 data)
{
	UART4->DR = data;
	while((UART4->SR&0x40)==0);	
}

void usart3_send(u8 data)
{
	USART3->DR = data;
	while((USART3->SR&0x40)==0);	
}

u8 Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	
	
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_Data.buffer[k];
	}
	
	
	
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}

u8 Check_Sum_AutoCharge(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	
	
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_AutoCharge_Data.buffer[k];
	}
	
	return check_sum;	
}

u8 AT_Command_Capture(u8 uart_recv)
{

	static u8 pointer = 0; 
	static u8 bt_line = 0; 
	static u8 disconnect = 0;
	static u8 connect = 0;
	
	
	static char* BlueTooth_Disconnect[3]={"+DISC:SUCCESS\r\n","+READY\r\n","+PAIRABLE\r\n"};
	
	
	static char* BlueTooth_Connect[2]={"+CONNECTING<<00:00:00:00:00:00\r\n","+CONNECTED\r\n"};

	
	if(uart_recv=='+') 
	{
		bt_line++,pointer=0; 
		disconnect++,connect++;
		return 1;
	}

	if(bt_line!=0) 
	{	
		pointer++;

		
		if(uart_recv == BlueTooth_Disconnect[bt_line-1][pointer])
		{
			disconnect++;
			if(disconnect==34) disconnect=0,connect=0,bt_line=0,pointer=0;
			return 1;
		}			

		
		else if(uart_recv == BlueTooth_Connect[bt_line-1][pointer] || (bt_line==1&&connect>=13) )
		{		
			connect++;
			if(connect==44) connect=0,disconnect=0,bt_line=0,pointer=0;		
			return 1;
		}	

		
		else
		{
			disconnect = 0;
			connect = 0;
			bt_line = 0;		
			pointer = 0;
			return 0;
		}			
	}
	
	return 0;
}

void _System_Reset_(u8 uart_recv)
{
	static u8 res_buf[5];
	static u8 res_count=0;
	
	res_buf[res_count]=uart_recv;
	
	if( uart_recv=='r'||res_count>0 )
		res_count++;
	else
		res_count = 0;
	
	if(res_count==5)
	{
		res_count = 0;
		
		if( res_buf[0]=='r'&&res_buf[1]=='e'&&res_buf[2]=='s'&&res_buf[3]=='e'&&res_buf[4]=='t' )
		{
			NVIC_SystemReset();
		}
	}
}
