#include "balance.h"

int robot_mode_check_flag=0;
int A=1,B=1,C=1,DD=1; 
int Time_count=0; 
u8 command_lost_count=0;

u8 start_check_flag = 0;
u8 wait_clear_times = 0;
u8 start_clear = 0;     
u8 clear_done_once = 0; 
u16 clear_again_times = 0;
float debug_show_diff = 0;
void auto_pwm_clear(void);
volatile u8 clear_state = 0x00;

int check_a,check_b,check_c,check_d;
float v_checka;
u8 check_end=0;

void Drive_Motor(float Vx,float Vy,float Vz)
{
    static float amplitude=3.5; 
    
    Vx=target_limit_float(Vx,-amplitude,amplitude);
    Vy=target_limit_float(Vy,-amplitude,amplitude);
    Vz=target_limit_float(Vz,-amplitude,amplitude);
	
	if(Allow_Recharge==0)
		Smooth_control(Vx,Vy,Vz); 
	else
		smooth_control.VX = Vx,
		smooth_control.VY = Vy,
		smooth_control.VZ = Vz;

    
    
    Vx=smooth_control.VX;
    Vy=smooth_control.VY;
    Vz=smooth_control.VZ;

#if Mec 

    
    MOTOR_A.Target = +Vy+Vx-Vz*(Wheel_axlespacing+Wheel_spacing);
    MOTOR_B.Target = -Vy+Vx-Vz*(Wheel_axlespacing+Wheel_spacing);
    MOTOR_C.Target = +Vy+Vx+Vz*(Wheel_axlespacing+Wheel_spacing);
    MOTOR_D.Target = -Vy+Vx+Vz*(Wheel_axlespacing+Wheel_spacing);

    
    MOTOR_A.Target=target_limit_float(MOTOR_A.Target,-amplitude,amplitude);
    MOTOR_B.Target=target_limit_float(MOTOR_B.Target,-amplitude,amplitude);
    MOTOR_C.Target=target_limit_float(MOTOR_C.Target,-amplitude,amplitude);
    MOTOR_D.Target=target_limit_float(MOTOR_D.Target,-amplitude,amplitude);

#elif Omni 

    
    MOTOR_A.Target =  Vy + Omni_turn_radiaus*Vz;
    MOTOR_B.Target = -X_PARAMETER*Vx - Y_PARAMETER*Vy + Omni_turn_radiaus*Vz;
    MOTOR_C.Target = +X_PARAMETER*Vx - Y_PARAMETER*Vy + Omni_turn_radiaus*Vz;

    
    MOTOR_A.Target=target_limit_float(MOTOR_A.Target,-amplitude,amplitude);
    MOTOR_B.Target=target_limit_float(MOTOR_B.Target,-amplitude,amplitude);
    MOTOR_C.Target=target_limit_float(MOTOR_C.Target,-amplitude,amplitude);
    MOTOR_D.Target=0;	

    if(Fault_Enable && Fault_Type == DRIVE_ABNORMAL_FAULT)
    {
        if(Fault_Wheel_Mask & FAULT_WHEEL_A) MOTOR_A.Target = MOTOR_A.Target * Fault_Alpha_A;
        if(Fault_Wheel_Mask & FAULT_WHEEL_B) MOTOR_B.Target = MOTOR_B.Target * Fault_Alpha_B;
        if(Fault_Wheel_Mask & FAULT_WHEEL_C) MOTOR_C.Target = MOTOR_C.Target * Fault_Alpha_C;
    }

#endif
}

void Balance_task(void *pvParameters)
{
    u32 lastWakeTime = getSysTickCnt();
    float encoder_yaw_rate, gyro_z_rate, corrected_Vz;
    u8 startup_ready = 0;

    while(1)
    {
        
        
        vTaskDelayUntil(&lastWakeTime, F2T(RATE_100_HZ));

        
        
        if(Time_count<3000)Time_count++;

        
        
        
        Get_Velocity_Form_Encoder();

        
        encoder_yaw_rate = (MOTOR_A.Encoder + MOTOR_B.Encoder + MOTOR_C.Encoder) / 3.0f / Omni_turn_radiaus * 180.0f / PI;

        
        gyro_z_rate = gyro[2] / 32768.0f * 500.0f;

        
        Yaw_Kalman_Filter(encoder_yaw_rate, gyro_z_rate);
        if(External_Heading_Enable && External_Heading_Valid && (Time_count - External_Heading_Last_Tick) < 200)
        {
            Current_Angle = Normalize_Angle(External_Heading_Angle);
        }
        else
        {
            Current_Angle = Normalize_Angle(yaw_angle - Yaw_Zero_Offset);
        }

        if(Set_Current_Angle_Zero_Flag)
        {
            Yaw_Zero_Offset = yaw_angle;
            External_Heading_Angle = 0.0f;
            External_Heading_Valid = 0;
            Current_Angle = 0.0f;
            Target_Angle = 0.0f;
            Angle_PID_Output = 0.0f;
            Angle_Control_Enable = 1;
            Manual_Turn_Active = 0;
            Set_Current_Angle_Zero_Flag = 0;
            Angle_PID_Reset();
        }

		if( Allow_Recharge==1 )
			if( Get_Charging_HardWare==0 ) Allow_Recharge=0,Find_Charging_HardWare();
		
		
		
		if(Time_count>CONTROL_DELAY+230&&startup_ready) 
		{
			if(Allow_Recharge==0&&(CAN_ON_Flag==1||Usart_ON_Flag==1))
			{
				if(command_lost_count<RATE_100_HZ+1) command_lost_count++;
				if(command_lost_count>RATE_100_HZ)
				{
					Move_X=0;
					Move_Y=0;
					Move_Z=0;
					Angle_PID_Output=0;
					Target_Angle=Current_Angle;
                    Angle_Control_Enable=1;
                    Manual_Turn_Active=0;
                    Angle_PID_Reset();
				}
			}
			if(Get_Charging_HardWare==1)
			{   
				charger_check++;
				if( charger_check>RATE_100_HZ) charger_check=RATE_100_HZ+1,Allow_Recharge=0,RED_STATE=0,Recharge_Red_Move_X = 0,Recharge_Red_Move_Y = 0,Recharge_Red_Move_Z = 0;
			}
			
            if(Allow_Recharge==1)
            {
                if      (nav_walk==1 && RED_STATE==0) Drive_Motor(Recharge_UP_Move_X,0,Recharge_UP_Move_Z);
                else if (RED_STATE!=0) nav_walk = 0,Drive_Motor(Recharge_Red_Move_X,0,Recharge_Red_Move_Z);
                if (nav_walk==0&&RED_STATE==0) Drive_Motor(0,0,0);
            }
            else
            {
                if      (APP_ON_Flag)      Get_RC();
                else if (Remote_ON_Flag)   Remote_Control();
                else if (PS2_ON_Flag)      PS2_control();
                else
                {
                    if(float_abs(Move_Z)>0.01f)
                    {
                        Manual_Turn_Active = 1;
                        Angle_PID_Output = 0;
                        Target_Angle = Current_Angle;
                        Angle_PID_Reset();
                        Drive_Motor(Move_X, Move_Y, Move_Z);
                    }
                    else
                    {
                        Move_Z = 0;
                        if(float_abs(smooth_control.VZ)<0.01f) smooth_control.VZ = 0;
                        if(Manual_Turn_Active)
                        {
                            Target_Angle = Current_Angle;
                            Manual_Turn_Active = 0;
                            Angle_Control_Enable = 1;
                            Angle_PID_Reset();
                        }
                        if(Angle_Control_Enable)
                        {
                            Angle_PID_Output = Angle_PID(Current_Angle, Target_Angle);
                            corrected_Vz = Limit_Heading_Correction(Angle_PID_Output, Move_X, Move_Y);
                        }
                        else
                        {
                            Angle_PID_Output = 0;
                            corrected_Vz = 0;
                        }
                        Drive_Motor(Move_X, Move_Y, corrected_Vz);
                    }
                }
            }
        }

        Key();
		
        
        
		robot_selfcheck();  
        if(CONTROL_DELAY<Time_count && Time_count<CONTROL_DELAY+200) 
        {
			Drive_Motor(0.1f,0,0);
            robot_mode_check(); 
        }
        else if(CONTROL_DELAY+200<Time_count && Time_count<CONTROL_DELAY+230) 
		{
			if(check_end==0)
			{
				check_end=1;
				Angle_PID_Output=0;
				Target_Angle=Current_Angle;
                Angle_Control_Enable=1;
                Manual_Turn_Active=0;
                Angle_PID_Reset();
			}
			Drive_Motor(0,0,0); 
		}
		else if(Time_count>=CONTROL_DELAY+230&&startup_ready==0)
		{
			Move_X=0;
			Move_Y=0;
			Move_Z=0;
			smooth_control.VX=0;
			smooth_control.VY=0;
			smooth_control.VZ=0;
			Angle_PID_Output=0;
            Yaw_Zero_Offset=yaw_angle;
            External_Heading_Angle = 0.0f;
            External_Heading_Valid = 0;
            Current_Angle=0.0f;
			Target_Angle=0.0f;
            Angle_Control_Enable=1;
            Manual_Turn_Active=0;
            Angle_PID_Reset();
			startup_ready=1;
			Drive_Motor(0,0,0);
		}
		
        
        
        
        if((Turn_Off(Voltage)==0&&robot_mode_check_flag==0)||(Allow_Recharge&&EN&&!Flag_Stop))
        {
            
            
            
            MOTOR_A.Motor_Pwm=Incremental_PI_A(MOTOR_A.Encoder, MOTOR_A.Target);
            MOTOR_B.Motor_Pwm=Incremental_PI_B(MOTOR_B.Encoder, MOTOR_B.Target);
            MOTOR_C.Motor_Pwm=Incremental_PI_C(MOTOR_C.Encoder, MOTOR_C.Target);
            MOTOR_D.Motor_Pwm=0;
			
			
			auto_pwm_clear();

#if Mec
            
            
            if (Car_Mode==0)  Set_Pwm( MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==1)	 Set_Pwm( MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==2)  Set_Pwm( MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==3)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==4)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==5)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==6)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==7)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==8)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==9)	 Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    
            else if (Car_Mode==10) Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,-MOTOR_D.Motor_Pwm);    

#elif Omni
            
            
            if (Car_Mode==0)                                Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm,0); 
            else if (Car_Mode==1||Car_Mode==2)             Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm,0); 
            else if (Car_Mode==3)	                        Set_Pwm(-MOTOR_A.Motor_Pwm,-MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm,0); 
            else if (Car_Mode==4||Car_Mode==5||Car_Mode==6)	Set_Pwm( MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm,-MOTOR_C.Motor_Pwm,0); 
#endif

        }
        
        
        else	Set_Pwm(0,0,0,0);

    }
}

void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
    
    
    if(motor_a>0)			AIN1=0,		AIN2=1;
    else 	            AIN1=1,		AIN2=0;
    
    
    TIM_SetCompare4(TIM8,myabs(motor_a*A));

    if(motor_b>0)			BIN1=0,		BIN2=1;
    else 	            BIN1=1,			BIN2=0;
    
    
    TIM_SetCompare3(TIM8,myabs(motor_b*B));

    
    
    if(motor_c>0)			CIN2=0,		CIN1=1;
    else 	            CIN2=1,			CIN1=0;
    
    
    TIM_SetCompare2(TIM8,myabs(motor_c*C));

    if(motor_d>0)			DIN2=0,		DIN1=1;
    else 	           DIN2=1,			DIN1=0;
    
    
    TIM_SetCompare1(TIM8,myabs(motor_d*DD));
}

void Limit_Pwm(int amplitude)
{
    MOTOR_A.Motor_Pwm=target_limit_float(MOTOR_A.Motor_Pwm,-amplitude,amplitude);
    MOTOR_B.Motor_Pwm=target_limit_float(MOTOR_B.Motor_Pwm,-amplitude,amplitude);
    MOTOR_C.Motor_Pwm=target_limit_float(MOTOR_C.Motor_Pwm,-amplitude,amplitude);
    MOTOR_D.Motor_Pwm=target_limit_float(MOTOR_D.Motor_Pwm,-amplitude,amplitude);
}

float target_limit_float(float insert,float low,float high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;
}
int target_limit_int(int insert,int low,int high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;
}

u8 Turn_Off( int voltage)
{
    u8 temp;
    
    if(voltage<20||EN==0||Flag_Stop==1)
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

float float_abs(float insert)
{
    if(insert>=0) return insert;
    else return -insert;
}

u32 int_abs(int a)
{
	u32 temp;
	if(a<0) temp=-a;
	else temp = a;
	return temp;
}

int Incremental_PI_A (float Encoder,float Target)
{
    static float Bias,Pwm,Last_bias;
    Bias=Target-Encoder; 
    Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
    if(Pwm>16800)Pwm=16800;
    if(Pwm<-16800)Pwm=-16800;
    Last_bias=Bias; 
	
	
	if( start_clear ) 
	{
		
		if(Pwm>0) Pwm--;
		if(Pwm<0) Pwm++;
		
		
		if( Pwm<2.0f&&Pwm>-2.0f ) Pwm=0,clear_state |= 1<<0;
		else clear_state &= ~(1<<0);
	}
	
    return Pwm;
}
int Incremental_PI_B (float Encoder,float Target)
{
    static float Bias,Pwm,Last_bias;
    Bias=Target-Encoder; 
    Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
    if(Pwm>16800)Pwm=16800;
    if(Pwm<-16800)Pwm=-16800;
    Last_bias=Bias; 
	
	if( start_clear ) 
	{
		if(Pwm>0) Pwm--;
		if(Pwm<0) Pwm++;
		
		if( Pwm<2.0f&&Pwm>-2.0f ) Pwm=0,clear_state |= 1<<1;
		else clear_state &= ~(1<<1);
	}
	
    return Pwm;
}
int Incremental_PI_C (float Encoder,float Target)
{
    static float Bias,Pwm,Last_bias;
    Bias=Target-Encoder; 
    Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
    if(Pwm>16800)Pwm=16800;
    if(Pwm<-16800)Pwm=-16800;
    Last_bias=Bias; 
	
	if( start_clear ) 
	{
		if(Pwm>0) Pwm--;
		if(Pwm<0) Pwm++;
		
		if( Pwm<2.0f&&Pwm>-2.0f ) Pwm=0,clear_state |= 1<<2;
		else clear_state &= ~(1<<2);
		
		
		if( (clear_state&0xff)==0x07 ) start_clear = 0,clear_done_once=1,clear_state=0;
	}
	
    return Pwm;
}
int Incremental_PI_D (float Encoder,float Target)
{
    static float Bias,Pwm,Last_bias;
    Bias=Target-Encoder; 
    Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
    if(Pwm>16800)Pwm=16800;
    if(Pwm<-16800)Pwm=-16800;
    Last_bias=Bias; 
    return Pwm;
}

static float Angle_PID_Last_Bias = 0.0f;
static float Angle_PID_Integral = 0.0f;

float Normalize_Angle(float angle)
{
    while(angle >= 180.0f) angle -= 360.0f;
    while(angle < -180.0f) angle += 360.0f;
    return angle;
}

void Angle_PID_Reset(void)
{
    Angle_PID_Last_Bias = 0.0f;
    Angle_PID_Integral = 0.0f;
}

float Limit_Heading_Correction(float correction, float vx, float vy)
{
    float limit = 0.70f;

    if(float_abs(vx) > 0.03f || float_abs(vy) > 0.03f)
    {
        limit = 0.35f;
    }

    if(correction > limit) correction = limit;
    if(correction < -limit) correction = -limit;

    return correction;
}
float Angle_PID(float Current_Angle, float Target)
{
    float Bias, Pwm, derivative;

    Bias = Normalize_Angle(Target - Current_Angle);
    if(float_abs(Bias) < 0.3f)
    {
        Angle_PID_Reset();
        return 0;
    }

    Angle_PID_Integral += Bias;
    if(Angle_PID_Integral > 300.0f) Angle_PID_Integral = 300.0f;
    if(Angle_PID_Integral < -300.0f) Angle_PID_Integral = -300.0f;

    derivative = Bias - Angle_PID_Last_Bias;
    Pwm = Angle_KP * Bias + Angle_KI * Angle_PID_Integral + Angle_KD * derivative;

    if(Pwm > 1.0f) Pwm = 1.0f;
    if(Pwm < -1.0f) Pwm = -1.0f;

    Angle_PID_Last_Bias = Bias;
    return Pwm;
}

void Get_RC(void)
{
    u8 Flag_Move=1;

    switch(Flag_Direction) 
    {
    case 1:
        Move_X=RC_Velocity;
        Move_Y=0;
        Flag_Move=1;
        break;
    case 2:
        Move_X=RC_Velocity;
        Move_Y=-RC_Velocity;
        Flag_Move=1;
        break;
    case 3:
        Move_X=0;
        Move_Y=-RC_Velocity;
        Flag_Move=1;
        break;
    case 4:
        Move_X=-RC_Velocity;
        Move_Y=-RC_Velocity;
        Flag_Move=1;
        break;
    case 5:
        Move_X=-RC_Velocity;
        Move_Y=0;
        Flag_Move=1;
        break;
    case 6:
        Move_X=-RC_Velocity;
        Move_Y=RC_Velocity;
        Flag_Move=1;
        break;
    case 7:
        Move_X=0;
        Move_Y=RC_Velocity;
        Flag_Move=1;
        break;
    case 8:
        Move_X=RC_Velocity;
        Move_Y=RC_Velocity;
        Flag_Move=1;
        break;
    default:
        Move_X=0;
        Move_Y=0;
        Flag_Move=0;
        break;
    }
    if(Flag_Move==0)
    {
        
        
        if     (Flag_Left ==1)  Move_Z= PI/2*(RC_Velocity/500); 
        else if(Flag_Right==1)  Move_Z=-PI/2*(RC_Velocity/500); 
        else 		               Move_Z=0;                       
    }

    
    
    Move_X=Move_X/1000;
    Move_Y=Move_Y/1000;
    Move_Z=Move_Z;

    if(float_abs(Move_Z)>0.01f)
    {
        Manual_Turn_Active=1;
        Angle_PID_Output=0;
        Target_Angle=Current_Angle;
        Angle_PID_Reset();
    }
    else
    {
        Move_Z=0;
        if(Manual_Turn_Active)
        {
            Target_Angle=Current_Angle;
            Manual_Turn_Active=0;
            Angle_Control_Enable=1;
            Angle_PID_Reset();
        }
        if(Angle_Control_Enable) Angle_PID_Output=Angle_PID(Current_Angle,Target_Angle);
        else Angle_PID_Output=0;
        Move_Z=Limit_Heading_Correction(Angle_PID_Output, Move_X, Move_Y);
    }

    
    
    Drive_Motor(Move_X,Move_Y,Move_Z);
}

void PS2_control(void)
{
    int LX,LY,RY;
    int Threshold=15; 

    
    
    LY=-(PS2_LX-128);
    LX=-(PS2_LY-128);
    RY=-(PS2_RX-128);

    
    if(LX>-Threshold&&LX<Threshold)LX=0;
    if(LY>-Threshold&&LY<Threshold)LY=0;
    if(RY>-Threshold&&RY<Threshold)RY=0;
    if(LX==0) Move_X=Move_X/1.2f;
    if(RY==0) Move_Z=Move_Z/1.2f;

    if (PS2_KEY==11)		RC_Velocity+=5;  
    else if(PS2_KEY==9)	RC_Velocity-=5;  

    if(RC_Velocity<0)   RC_Velocity=0;

    
    
    Move_X=LX;
    Move_Y=LY;
    Move_Z=RY;
    Move_X=Move_X*RC_Velocity/128;
    Move_Y=Move_Y*RC_Velocity/128;
    Move_Z=Move_Z*(PI/4)*(RC_Velocity/500)/128;

    
    
    Move_X=Move_X/1000;
    Move_Y=Move_Y/1000;

    if(float_abs(Move_Z)>0.01f)
    {
        Manual_Turn_Active=1;
        Angle_PID_Output=0;
        Target_Angle=Current_Angle;
        Angle_PID_Reset();
    }
    else
    {
        Move_Z=0;
        if(Manual_Turn_Active)
        {
            Target_Angle=Current_Angle;
            Manual_Turn_Active=0;
            Angle_Control_Enable=1;
            Angle_PID_Reset();
        }
        if(Angle_Control_Enable) Angle_PID_Output=Angle_PID(Current_Angle,Target_Angle);
        else Angle_PID_Output=0;
        Move_Z=Limit_Heading_Correction(Angle_PID_Output, Move_X, Move_Y);
    }

    
    
    Drive_Motor(Move_X,Move_Y,Move_Z);
}

void Remote_Control(void)
{
    
    
    static u8 thrice=100;
    int Threshold=100;

    
    int LX,LY,RY,RX,Remote_RCvelocity; 
    static float Target_LX,Target_LY,Target_RY;
    Remoter_Ch1=target_limit_int(Remoter_Ch1,1000,2000);
    Remoter_Ch2=target_limit_int(Remoter_Ch2,1000,2000);
    Remoter_Ch3=target_limit_int(Remoter_Ch3,1000,2000);
    Remoter_Ch4=target_limit_int(Remoter_Ch4,1000,2000);

    
    
    LX=Remoter_Ch2-1500;

    
    
    LY=Remoter_Ch4-1500;

    
    
    RX=Remoter_Ch3-1500;		

    
    
    RY=Remoter_Ch1-1500;

    if(LX>-Threshold&&LX<Threshold)LX=0;
    if(LY>-Threshold&&LY<Threshold)LY=0;
    if(RY>-Threshold&&RY<Threshold)RY=0;

    if(LX==0) Target_LX=Target_LX/1.2f;
    if(LY==0) Target_LY=Target_LY/1.2f;
    if(RY==0) Target_RY=Target_RY/1.2f;

    
    Remote_RCvelocity=RC_Velocity+RX;
    if(Remote_RCvelocity<0)Remote_RCvelocity=0;

    
    
    Move_X= LX;
    Move_Y=-LY;
    Move_Z=-RY;
    Move_X= Move_X*Remote_RCvelocity/500; 
    Move_Y= Move_Y*Remote_RCvelocity/500;
    Move_Z= Move_Z*(PI/4)*(Remote_RCvelocity/500)/500;  

    
    
    Move_X=Move_X/1000;
    Move_Y=Move_Y/1000;

    
    
    if(thrice>0) Move_X=0,Move_Z=0,thrice--;

    if(float_abs(Move_Z)>0.01f)
    {
        Manual_Turn_Active=1;
        Angle_PID_Output=0;
        Target_Angle=Current_Angle;
        Angle_PID_Reset();
    }
    else
    {
        Move_Z=0;
        if(Manual_Turn_Active)
        {
            Target_Angle=Current_Angle;
            Manual_Turn_Active=0;
            Angle_Control_Enable=1;
            Angle_PID_Reset();
        }
        if(Angle_Control_Enable) Angle_PID_Output=Angle_PID(Current_Angle,Target_Angle);
        else Angle_PID_Output=0;
        Move_Z=Limit_Heading_Correction(Angle_PID_Output, Move_X, Move_Y);
    }

    
    
    Drive_Motor(Move_X,Move_Y,Move_Z);
}

void Key(void)
{
    u8 tmp;
    
    tmp=KEY_Scan(RATE_100_HZ,0);

    
    if(tmp==single_click)
	{
		Allow_Recharge=!Allow_Recharge;
		memcpy(Deviation_gyro,Original_gyro,sizeof(gyro)),memcpy(Deviation_accel,Original_accel,sizeof(accel));
	}		

    
    else if(tmp==double_click) memcpy(Deviation_gyro,Original_gyro,sizeof(gyro)),memcpy(Deviation_accel,Original_accel,sizeof(accel));

    
    else if(tmp==long_click)
    {
        oled_refresh_flag=1;
        oled_page++;
        if(oled_page>OLED_MAX_Page-1) oled_page=0;
    }
}

void Get_Velocity_Form_Encoder(void)
{
    
    
    float Encoder_A_pr,Encoder_B_pr,Encoder_C_pr,Encoder_D_pr; 
    
    
#if Mec
    Encoder_A_pr= Read_Encoder(2);
    Encoder_B_pr= Read_Encoder(3);
    Encoder_C_pr=-Read_Encoder(4);
    Encoder_D_pr=-Read_Encoder(5);
#elif Omni
    Encoder_A_pr=-Read_Encoder(2);
    Encoder_B_pr=-Read_Encoder(3);
    Encoder_C_pr=-Read_Encoder(4);
	v_checka = Encoder_A_pr;
#endif

	
	if( check_end==0 )
	{
		check_a+=Encoder_A_pr;
		check_b+=Encoder_B_pr;
		check_c+=Encoder_C_pr;
		check_d=0;
	}
	
    
    
    MOTOR_A.Encoder= Encoder_A_pr*CONTROL_FREQUENCY*Wheel_perimeter/Encoder_precision;
    MOTOR_B.Encoder= Encoder_B_pr*CONTROL_FREQUENCY*Wheel_perimeter/Encoder_precision;
    MOTOR_C.Encoder= Encoder_C_pr*CONTROL_FREQUENCY*Wheel_perimeter/Encoder_precision;
    MOTOR_D.Encoder= Encoder_D_pr*CONTROL_FREQUENCY*Wheel_perimeter/Encoder_precision;
}

void Smooth_control(float vx,float vy,float vz)
{
	float step=0.02; 
	
	
	if(vx>smooth_control.VX)
	{
		smooth_control.VX+=step;
		if(smooth_control.VX>vx) smooth_control.VX=vx;
	}
	else if (vx<smooth_control.VX)
	{
		smooth_control.VX-=step;
		if(smooth_control.VX<vx) smooth_control.VX=vx;
	}
	else
		 smooth_control.VX =vx;
	
	
	if(vy>smooth_control.VY)
	{
		smooth_control.VY+=step;
		if(smooth_control.VY>vy) smooth_control.VY=vy;
	}
	else if (vy<smooth_control.VY)
	{
		smooth_control.VY-=step;
		if(smooth_control.VY<vy) smooth_control.VY=vy;
	}
	else
		 smooth_control.VY =vy;
	
	
	if(vz>smooth_control.VZ)
	{
		smooth_control.VZ+=step;
		if(smooth_control.VZ>vz) smooth_control.VZ=vz;
	}
	else if (vz<smooth_control.VZ)
	{
		smooth_control.VZ-=step;
		if(smooth_control.VZ<vz) smooth_control.VZ=vz;
	}
	else
		 smooth_control.VZ =vz;
	
	
	if(vx==0&&smooth_control.VX<0.05f&&smooth_control.VX>-0.05f) smooth_control.VX=0;
	if(vy==0&&smooth_control.VY<0.05f&&smooth_control.VY>-0.05f) smooth_control.VY=0;
	if(vz==0&&smooth_control.VZ<0.05f&&smooth_control.VZ>-0.05f) smooth_control.VZ=0;
}

void robot_mode_check(void)
{
	#define ERROR_PWM 8000 
	static u8 once=1;
	if( once ) check_a=0,check_b=0,check_c=0,check_d=0,once=0;
	
	if( EN==1 && robot_mode_check_flag==0) 
	{	
		if( check_a>Encoder_precision/2 || check_a<-Encoder_precision/2 ) robot_mode_check_flag=1,LED_G=0;
		
		
		if( check_b>3000 || check_c<-3000 ) robot_mode_check_flag=1,LED_G=0;
		
		
		if(float_abs(MOTOR_B.Motor_Pwm)>5500 && check_b>-500) robot_mode_check_flag=1,LED_B=0;	
		if(float_abs(MOTOR_C.Motor_Pwm)>5500 && check_c< 500) robot_mode_check_flag=1,LED_B=0;

		
		if( float_abs(MOTOR_A.Motor_Pwm)>ERROR_PWM||float_abs(MOTOR_B.Motor_Pwm)>ERROR_PWM||\
			 float_abs(MOTOR_C.Motor_Pwm)>ERROR_PWM)
		{
			robot_mode_check_flag = 1;
			LED_B=1,LED_G=1;
		}
		
	}
}

void robot_selfcheck(void)
{
	if( smooth_control.VY==0&&smooth_control.VZ==0 )
	{
		if( float_abs(MOTOR_A.Motor_Pwm)>8000 && v_checka>=-10&&v_checka<=10 )
		{
			robot_mode_check_flag=1;
		}
	}
}

void auto_pwm_clear(void)
{
	
	float y_accle = (float)(accel[1]/1671.84f);
	float z_accle = (float)(accel[2]/1671.84f);
	float diff;
	
	
	if( y_accle > 0 ) diff  = z_accle - y_accle;
	else diff  = z_accle + y_accle;
	

	
	
	if( smooth_control.VX !=0.0f || smooth_control.VZ != 0.0f || smooth_control.VY != 0.0f ) 
	{
		start_check_flag = 1;
		wait_clear_times = 0;
		start_clear = 0;     
			
		
		clear_done_once = 0;
		clear_again_times=0;
	}
	else 
	{
		if( start_check_flag==1 )
		{
			wait_clear_times++;
			if( wait_clear_times >= 250 )
			{
				
				if( diff > 8.8f )	start_clear = 1,clear_state = 0;
				else clear_done_once = 1;
				
				start_check_flag = 0;
			}
		}
		else
		{
			wait_clear_times = 0;
		}
	}

	
	if( clear_done_once )
	{
		
		if( diff > 8.8f )
		{
			
			if( int_abs(MOTOR_A.Motor_Pwm)>300 || int_abs(MOTOR_B.Motor_Pwm)>300 || int_abs(MOTOR_C.Motor_Pwm)>300 || int_abs(MOTOR_D.Motor_Pwm)>300 )
			{
				clear_again_times++;
				if( clear_again_times>1000 )
				{
					clear_done_once = 0;
					start_clear = 1;
					clear_state = 0;
				}
			}
			else
			{
				clear_again_times = 0;
			}
		}
		else
		{
			clear_again_times = 0;
		}

	}
}

