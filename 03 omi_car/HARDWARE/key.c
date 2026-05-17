#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = KEY_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
} 

u8 click(void)
{
	
	
	static u8 flag_key=1;
	
	if(flag_key&&KEY==0)
	{
	 flag_key=0; 
	 return 1;	
	}
	else if(1==KEY)			
		flag_key=1;
	return 0; 
}

void Delay_ms(void)
{
   int ii,i;    
   for(ii=0;ii<50;ii++)
   {
	   for(i=0;i<50;i++);
	 }	
}

u8 click_N_Double (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	
	  if(KEY==0)  Forever_count++;   
    else        Forever_count=0;
	
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2; 
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1; 
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}

u8 click_N_Double_MPU6050 (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	
	  if(KEY==0)  Forever_count++;  
    else        Forever_count=0;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2; 
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1; 
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}

u8 Long_Press(void)
{
	static u16 Long_Press_count,Long_Press;

	if(Long_Press==0&&KEY==0)  Long_Press_count++; 
	else                       Long_Press_count=0;

	if(Long_Press_count>15)	
	{
		Long_Press=1;	
		Long_Press_count=0;
		return 1;
	}				
	 if(Long_Press==1) 
	{
			Long_Press=0;
	}
	return 0;
}

u8 KEY_Scan(u16 Frequency,u16 filter_times)
{
    static u16 time_core;
    static u16 long_press_time;
    static u8 press_flag=0;
    static u8 check_once=0;
    static u16 delay_mini_1;
    static u16 delay_mini_2;
	
    float Count_time = (((float)(1.0f/(float)Frequency))*1000.0f);

    if(check_once)
    {
        press_flag=0;
        time_core=0;
        long_press_time=0;
        delay_mini_1=0;
        delay_mini_2=0;
    }
    if(check_once&&KEY==1) check_once=0; 

    if(KEY==0&&check_once==0)
    {
        press_flag=1;
		
        if(++delay_mini_1>filter_times)
        {
            delay_mini_1=0;
            long_press_time++;		
        }
    }

    if(long_press_time>(u16)(600.0f/Count_time))
    {	
        check_once=1;
        return long_click; 
    }

    
    if(press_flag&&KEY==1)
    {
        if(++delay_mini_2>filter_times)
        {
            delay_mini_2=0;
            time_core++; 
        }
    }		
	
    if(press_flag&&(time_core>(u16)(50.0f/Count_time)&&time_core<(u16)(500.0f/Count_time)))
    {
        if(KEY==0) 
        {
            check_once=1;
            return double_click; 
        }
    }
    else if(press_flag&&time_core>(u16)(500.0f/Count_time))
    {
        check_once=1;
        return single_click; 
    }

    return key_stateless;
}
