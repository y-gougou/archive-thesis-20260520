#include "timer.h"

u8 TIM1CH1_CAPTURE_STA = 0;	
u16 TIM1CH1_CAPTURE_UPVAL;
u16 TIM1CH1_CAPTURE_DOWNVAL;

u8 TIM1CH2_CAPTURE_STA = 0;		
u16 TIM1CH2_CAPTURE_UPVAL;
u16 TIM1CH2_CAPTURE_DOWNVAL;

u8 TIM1CH3_CAPTURE_STA = 0;		
u16 TIM1CH3_CAPTURE_UPVAL;
u16 TIM1CH3_CAPTURE_DOWNVAL;

u8 TIM1CH4_CAPTURE_STA = 0;			
u16 TIM1CH4_CAPTURE_UPVAL;
u16 TIM1CH4_CAPTURE_DOWNVAL;

u32 TIM1_T1;
u32 TIM1_T2;
u32 TIM1_T3;
u32 TIM1_T4;

int Remoter_Ch1=1500,Remoter_Ch2=1500,Remoter_Ch3=1500,Remoter_Ch4=1500;

int L_Remoter_Ch1=1500,L_Remoter_Ch2=1500,L_Remoter_Ch3=1500,L_Remoter_Ch4=1500;  

 
void TIM1_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
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
  
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;	  
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

	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 
	
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	   
	
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  
	TIM_ICInit(TIM1, &TIM_ICInitStructure);

  
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn; 
  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	
	
	NVIC_Init(&NVIC_InitStructure);   
	
  
  
	TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,	ENABLE);   
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 	
	
	TIM_Cmd(TIM1, ENABLE); 		
}

 
void TIM1_CC_IRQHandler(void)
{
	static u8 ch1_filter_times=0,ch2_filter_times=0,ch3_filter_times=0,ch4_filter_times=0;
	
	
	
  if(Remoter_Ch2>1600&&Remote_ON_Flag==0&&Deviation_Count>=CONTROL_DELAY)
  {
		
		
		Remote_ON_Flag=1;
	  APP_ON_Flag=0;
		PS2_ON_Flag=0;
		CAN_ON_Flag=0;
		Usart_ON_Flag=0; 
	}
	 
	
	if ((TIM1CH1_CAPTURE_STA & 0X80) == 0) 			
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) 
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC1); 
			if (TIM1CH1_CAPTURE_STA & 0X40)	
			{
				TIM1CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM1); 
				if (TIM1CH1_CAPTURE_DOWNVAL < TIM1CH1_CAPTURE_UPVAL)
				{
					TIM1_T1 = 9999;
				}
				else
					TIM1_T1 = 0;
				Remoter_Ch1 = TIM1CH1_CAPTURE_DOWNVAL - TIM1CH1_CAPTURE_UPVAL + TIM1_T1;	
				if(abs(Remoter_Ch1-L_Remoter_Ch1)>500)
				{
					ch1_filter_times++;
					if( ch1_filter_times<=5 ) Remoter_Ch1=L_Remoter_Ch1; 
					else ch1_filter_times=0;
				}
				else
				{
					ch1_filter_times=0;
				}
				
				L_Remoter_Ch1=Remoter_Ch1;
				
				TIM1CH1_CAPTURE_STA = 0; 
				TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Rising); 
			}
			else 
			{
				
				
				TIM1CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM1); 
				TIM1CH1_CAPTURE_STA |= 0X40; 
				TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Falling); 
			}
		}
	}
  
	if ((TIM1CH2_CAPTURE_STA & 0X80) == 0)		
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)	
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC2); 
			if (TIM1CH2_CAPTURE_STA & 0X40)	
			{
				TIM1CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM1); 
				if (TIM1CH2_CAPTURE_DOWNVAL < TIM1CH2_CAPTURE_UPVAL)
				{
					TIM1_T2 = 9999;
				}
				else
					TIM1_T2 = 0;
				Remoter_Ch2 = TIM1CH2_CAPTURE_DOWNVAL - TIM1CH2_CAPTURE_UPVAL + TIM1_T2; 
				if(abs(Remoter_Ch2-L_Remoter_Ch2)>500)
				{
					ch2_filter_times++;
					if( ch2_filter_times<=5 ) Remoter_Ch2=L_Remoter_Ch2; 
					else ch2_filter_times=0;
				}
				else
				{
					ch2_filter_times=0;
				}
				
				L_Remoter_Ch2=Remoter_Ch2;
				
				TIM1CH2_CAPTURE_STA = 0; 
				TIM_OC2PolarityConfig(TIM1, TIM_ICPolarity_Rising); 
			}
			else 
			{
				
				
				TIM1CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM1); 
				TIM1CH2_CAPTURE_STA |= 0X40; 
				TIM_OC2PolarityConfig(TIM1, TIM_ICPolarity_Falling); 
			}
		}
	}
  
	if ((TIM1CH3_CAPTURE_STA & 0X80) == 0)			
	{
		if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)	
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_CC3); 
			if (TIM1CH3_CAPTURE_STA & 0X40)	
			{
				TIM1CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM1); 
				if (TIM1CH3_CAPTURE_DOWNVAL < TIM1CH3_CAPTURE_UPVAL)
				{
					TIM1_T3 = 9999;
				}
				else
					TIM1_T3 = 0;
				Remoter_Ch3 = TIM1CH3_CAPTURE_DOWNVAL - TIM1CH3_CAPTURE_UPVAL + TIM1_T3; 
				if(abs(Remoter_Ch3-L_Remoter_Ch3)>500)
				{
					ch3_filter_times++;
					if( ch3_filter_times<=5 ) Remoter_Ch3=L_Remoter_Ch3; 
					else ch3_filter_times=0;
				}
				else
				{
					ch3_filter_times=0;
				}
				L_Remoter_Ch3=Remoter_Ch3;	
				TIM1CH3_CAPTURE_STA = 0; 
				TIM_OC3PolarityConfig(TIM1, TIM_ICPolarity_Rising); 
			}
			else 
			{
				
				
				TIM1CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM1); 
				TIM1CH3_CAPTURE_STA |= 0X40; 
				TIM_OC3PolarityConfig(TIM1, TIM_ICPolarity_Falling); 
			}
		}
	}

		
		if ((TIM1CH4_CAPTURE_STA & 0X80) == 0)		
		{
			if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)	
			{
				TIM_ClearITPendingBit(TIM1, TIM_IT_CC4); 
				if (TIM1CH4_CAPTURE_STA & 0X40)	
				{
					TIM1CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM1); 
					if (TIM1CH4_CAPTURE_DOWNVAL < TIM1CH4_CAPTURE_UPVAL)
					{
						TIM1_T4 = 9999;
					}
					else
						TIM1_T4 = 0;
					Remoter_Ch4 = TIM1CH4_CAPTURE_DOWNVAL - TIM1CH4_CAPTURE_UPVAL + TIM1_T4; 
					if(abs(Remoter_Ch4-L_Remoter_Ch4)>500)
					{
						ch4_filter_times++;
						if( ch4_filter_times<=5 ) Remoter_Ch4=L_Remoter_Ch4; 
						else ch4_filter_times=0;
					}
					else
					{
						ch4_filter_times=0;
					}
					
					L_Remoter_Ch4=Remoter_Ch4;				
					TIM1CH4_CAPTURE_STA = 0; 
					TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Rising); 
				}
				else 
				{
					
				  
					TIM1CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM1); 
					TIM1CH4_CAPTURE_STA |= 0X40; 
					TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Falling); 
				}
			}
		}
}

void TIM1_UP_TIM10_IRQHandler(void) 
{ 
	
	
  TIM1->SR&=~(1<<0);	    
}

