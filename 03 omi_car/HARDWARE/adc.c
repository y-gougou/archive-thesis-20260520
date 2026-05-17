#include "adc.h"

float Voltage,Voltage_Count,Voltage_All; 
const float Revise=1.0;

void  Adc_Init(void)
{  
		GPIO_InitTypeDef       GPIO_InitStructure;
		ADC_CommonInitTypeDef ADC_CommonInitStructure;
		ADC_InitTypeDef       ADC_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	

		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
		ADC_CommonInit(&ADC_CommonInitStructure);

		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfConversion = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
		ADC_Cmd(ADC1, ENABLE);
}		

u16 Get_Adc(u8 ch)   
{
	
	
	
	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );
  
  
	ADC_SoftwareStartConv(ADC1);
	
  
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	
	
	return ADC_GetConversionValue(ADC1);	
}

u16 Get_adc_Average(u8 chn, u8 times)
{
  u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(chn);
		delay_ms(5);
	}
	return temp_val/times;
}

float Get_battery_volt(void)   
{  
	float Volt;
	
	
	
	Volt=Get_Adc(Battery_Ch)*3.24*11.0*Revise/1.0/4096;	
	return Volt;
}

