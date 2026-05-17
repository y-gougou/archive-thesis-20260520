
#ifndef __MOTOR_H
#define __MOTOR_H

#include "system.h"

#define PWM_PORTA GPIOC			 
#define PWM_PIN_A GPIO_Pin_9
#define PWMA 	  TIM8->CCR4	 

#define IN1_PORTA GPIOB			 
#define IN1_PIN_A GPIO_Pin_13 
#define AIN1 	  PBout(13)		 

#define IN2_PORTA GPIOB			 
#define IN2_PIN_A GPIO_Pin_12 
#define AIN2 	  PBout(12)		 

#define PWM_PORTB GPIOC			 
#define PWM_PIN_B GPIO_Pin_8 
#define PWMB 	  TIM8->CCR3	 

#define IN1_PORTB GPIOC			 
#define IN1_PIN_B GPIO_Pin_0 
#define BIN1 	  PCout(0)		 

#define IN2_PORTB GPIOB			 
#define IN2_PIN_B GPIO_Pin_14 
#define BIN2 	  PBout(14)		 

#define PWM_PORTC GPIOC			 
#define PWM_PIN_C GPIO_Pin_7 
#define PWMC 	  TIM8->CCR2	 

#define IN1_PORTC GPIOD			  
#define IN1_PIN_C GPIO_Pin_10	
#define CIN1 	  PDout(10)		  

#define IN2_PORTC GPIOD			 
#define IN2_PIN_C GPIO_Pin_12 
#define CIN2 	  PDout(12)		 

#define PWM_PORTD GPIOC			 
#define PWM_PIN_D GPIO_Pin_6 
#define PWMD 	  TIM8->CCR1	 

#define IN1_PORTD GPIOC			  
#define IN1_PIN_D GPIO_Pin_12	
#define DIN1 	  PCout(12)		  

#define IN2_PORTD GPIOA			  
#define IN2_PIN_D GPIO_Pin_8	
#define DIN2 	  PAout(8)		  

#define EN     PEin(4)  
#define Servo_PWM  TIM9->CCR1
#define SERVO_INIT 1500  

void Enable_Pin(void);
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
void Servo_PWM_Init(u16 arr,u16 psc);
#endif
