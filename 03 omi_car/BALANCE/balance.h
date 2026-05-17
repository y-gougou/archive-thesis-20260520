#ifndef __BALANCE_H
#define __BALANCE_H			  	 
#include "sys.h"
#include "system.h"
#define BALANCE_TASK_PRIO		4     
#define BALANCE_STK_SIZE 		512   

#define X_PARAMETER    (sqrt(3)/2.f)               
#define Y_PARAMETER    (0.5f)    
#define L_PARAMETER    (1.0f)

extern int A,B,C,DD;
extern u8 command_lost_count;
void Balance_task(void *pvParameters);
void Limit_Pwm(int amplitude);
float target_limit_float(float insert,float low,float high);
int target_limit_int(int insert,int low,int high);
u8 Turn_Off( int voltage);
u32 myabs(long int a);
float float_abs(float insert);
int Incremental_PI_A (float Encoder,float Target);
int Incremental_PI_B (float Encoder,float Target);
int Incremental_PI_C (float Encoder,float Target);
int Incremental_PI_D (float Encoder,float Target);

void Get_RC(void);
void PS2_control(void);
void Remote_Control(void);
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d);
void Drive_Motor(float Vx,float Vy,float Vz);
void Key(void);
void Get_Velocity_Form_Encoder(void);
void robot_mode_check(void);

int Smooth_steering(int currentPWM, int targetPWM, float step);
int Mean_Filter(int data);
void Smooth_control(float vx,float vy,float vz);
void robot_selfcheck(void);
float Normalize_Angle(float angle);
void Angle_PID_Reset(void);
float Limit_Heading_Correction(float correction, float vx, float vy);
float Angle_PID(float Current_Angle, float Target);
#endif  

