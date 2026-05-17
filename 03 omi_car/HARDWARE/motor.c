#include "motor.h"

void MiniBalance_Motor_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13 |GPIO_Pin_14);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_12 );
	GPIO_ResetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_12);
			
}

void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
	GPIO_Init(GPIOC,&GPIO_InitStructure);              
	
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	
	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 1; 
	
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 

  
  
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  
  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	
  
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
	
	
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  

  
  
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
	
			 TIM8->CCR1=0;	
	 TIM8->CCR2=0;	
	 TIM8->CCR3=0;	
	 TIM8->CCR4=0;
	
	
	
	TIM_Cmd(TIM8, ENABLE);  
} 

void Enable_Pin(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
} 

void Servo_PWM_Init(u16 arr,u16 psc)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;           
	TIM_ICInitTypeDef TIM_ICInitStructure;         
	TIM_OCInitTypeDef  TIM_OCInitStructure;        
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(GPIOE,&GPIO_InitStructure); 

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);

	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 
  
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	
  
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 
	
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;   
	
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  
	
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	
	
  
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	
	
	TIM_OCInitStructure.TIM_Pulse = 0; 
  
  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   
	
	
  
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
	
	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	

  
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn; 
  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	
	
	NVIC_Init(&NVIC_InitStructure);   

  
  
	
  
  
	TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,	ENABLE);   
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 	
	
	TIM_Cmd(TIM1, ENABLE); 		 

  
	
	TIM1->CCR4=1500;
}
