#include "control.h"	
#include "filter.h"	
  

u8 Flag_Target,Flag_Change;                             
u8 temp1;                                               
float Voltage_Count,Voltage_All; 											  
float Gyro_K=0.004;     				  											
int j;
#define a_PARAMETER          (0.275f)   
#define T 0.320f    
#define L 0.315f    
#define K 570.8f

void Kinematic_Analysis(float Vy,float angle)
{
        Target_A   = Vy*(1+T*tan(angle)/2/L);
        Target_B   = Vy*(1-T*tan(angle)/2/L);
	      Servo=SERVO_INIT-angle*K;
}

int EXTI15_10_IRQHandler(void) 
{    
	 if(INT==0)		
	{     
		  EXTI->PR=1<<15;                                                      
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     
			 }
		  if(Flag_Target==1)                                                  
			{
					if(Usart_Flag==0&&PS2_ON_Flag==0&&Usart_ON_Flag==1)  memcpy(rxbuf,Urxbuf,8*sizeof(u8));	
					Read_DMP();                                                           
			  	Key();
			    return 0;	                                               
			}                                                                     	 
			UA_Encoder=Read_Encoder(2);                                          
			Encoder_A=UA_Encoder/25;
			Position_A+=Encoder_A;                                                 
			UB_Encoder=-Read_Encoder(3);                                          
			Encoder_B=UB_Encoder/25;
			Position_B+=Encoder_B;                                                 
	  	Read_DMP();                                                            	
  		Led_Flash(100);                                                       	 
			Voltage_All+=Get_battery_volt();                                      	 
			if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;
		  if(PS2_KEY==4)PS2_ON_Flag=1,CAN_ON_Flag=0,Usart_ON_Flag=0;									
		  if(CAN_ON_Flag==1||Usart_ON_Flag==1||PS2_ON_Flag==1) CAN_N_Usart_Control();    
			if(RC_Velocity>0&&RC_Velocity<15)  RC_Velocity=15;                   
			if(Turn_Off(Voltage)==0)               
			 { 			 	
				 if(CAN_ON_Flag==0&&Usart_ON_Flag==0&&PS2_ON_Flag==0)      Get_RC(Run_Flag);
				 Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         
				 Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         
				 Xianfu_Pwm(6900);                     
				 Set_Pwm(-Motor_A,-Motor_B,Servo);     
			 }
			 else	Set_Pwm(0,0,SERVO_INIT);    
	 }
	 return 0;	 
} 

void Set_Pwm(int motor_a,int motor_b,int servo)
{
	  
   	if(motor_a<0)			INA2=1,			INA1=0;
			else 	          INA2=0,			INA1=1;
		PWMA=myabs(motor_a);
	
		if(motor_b<0)			INB2=1,			INB1=0;
		else 	            INB2=0,			INB1=1;
		PWMB=myabs(motor_b);
	    SERVO=servo;
	
}

void Xianfu_Pwm(int amplitude)
{	
    if(Motor_A<-amplitude) Motor_A=-amplitude;	
		if(Motor_A>amplitude)  Motor_A=amplitude;	
	  if(Motor_B<-amplitude) Motor_B=-amplitude;	
		if(Motor_B>amplitude)  Motor_B=amplitude;
    if (Servo>1930)	 Servo=1930;

}

void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D)
{	
    if(Motor_A<-amplitude_A) Motor_A=-amplitude_A;	
		if(Motor_A>amplitude_A)  Motor_A=amplitude_A;	  
	  if(Motor_B<-amplitude_B) Motor_B=-amplitude_B;	
		if(Motor_B>amplitude_B)  Motor_B=amplitude_B;		
}

void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(100); 
	if(tmp==2)Flag_Show=!Flag_Show;
}

u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<1110)
			{	                                                
      temp=1;      
      PWMA=0;
      PWMB=0;					
      }
			else
      temp=0;
      return temp;			
}

u32 myabs(long int a)
{ 		   
	  u32 temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   
	 return Pwm;                         
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   
	 return Pwm;                         
}

void Get_RC(u8 mode)
{

	  if(mode==0)
		{	
				 switch(Flag_Direction)   
				 { 
				 case 1:      Move_Y=RC_Velocity;  	 	 Angle=0;        break;
				 case 2:      Move_Y=RC_Velocity;  	 	 Angle=PI/4;   	 break;
				 case 3:      Move_Y=0;      				 	 Angle=0;   	   break;
				 case 4:      Move_Y=-RC_Velocity;  	 Angle=-PI/4;    break;
				 case 5:      Move_Y=-RC_Velocity;  	 Angle=0;        break;
				 case 6:      Move_Y=-RC_Velocity;  	 Angle=PI/4;     break;
				 case 7:      Move_Y=0;     	 			 	 Angle=0;        break;
				 case 8:      Move_Y=+RC_Velocity; 	 	 Angle=-PI/4;    break; 
				 default:     Move_Y=0;                Angle=0;        break;
			 } 

	 }
		 Kinematic_Analysis(Move_Y,Angle);
}

void CAN_N_Usart_Control(void)
{

			int RX,LY;
		  int Yuzhi=20;
			if(CAN_ON_Flag==1||Usart_ON_Flag==1) 
			{

			 if(rxbuf[1]==0)Move_Y=rxbuf[0]; 
			 else           Move_Y=-rxbuf[0]; 
			 Angle=(rxbuf[2]-90)*PI/180;   
			}
			else if (PS2_ON_Flag==1)
	    {
	     RX=PS2_RX-128;
			 LY=PS2_LY-128;
			 if(RX>-Yuzhi&&RX<Yuzhi)RX=0; 
			 if(LY>-Yuzhi&&LY<Yuzhi)LY=0;
		   Angle= RX*PI/4/120;
		   Move_Y=-LY/2.84;	 
		  
	    }
			Kinematic_Analysis(Move_Y,Angle);
}
