#include "encoder.h"

void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);  
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2);   
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);   
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
  
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}

void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);   
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);   
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
  
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);  
	
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE); 
}

void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);   

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); 
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

void Encoder_Init_TIM5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM5,0);
  TIM_Cmd(TIM5, ENABLE); 
}

int Read_Encoder(u8 TIMX)
{
 int Encoder_TIM;    
 switch(TIMX)
 {
	case 2:  Encoder_TIM= (short)TIM2 -> CNT;   TIM2 -> CNT=0;  break;
	case 3:  Encoder_TIM= (short)TIM3 -> CNT;   TIM3 -> CNT=0;  break;
	case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;	
	case 5:  Encoder_TIM= (short)TIM5 -> CNT;   TIM5 -> CNT=0;  break;	
	default: Encoder_TIM=0;
 }
	return Encoder_TIM;
}

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001) 
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0); 
}

void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001) 
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0); 
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001) 
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0); 
}

void TIM5_IRQHandler(void)
{ 		    		  			    
	if(TIM5->SR&0X0001) 
	{    				   				     	    	
	}				   
	TIM5->SR&=~(1<<0); 
}
