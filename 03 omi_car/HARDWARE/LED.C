#include "led.h"

int Led_Count=500; 

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  LED_R_PIN|LED_G_PIN|LED_B_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
    Buzzer=0;
	GPIO_SetBits(GPIOD,LED_R_PIN);
	GPIO_SetBits(GPIOD,LED_G_PIN);
	GPIO_SetBits(GPIOD,LED_B_PIN);
}

void Buzzer_Init(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  Buzzer_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
    Buzzer=0;
}

void led_task(void *pvParameters)
{
    while(1)
    {
		static u8 led_state=0;
		
		led_state = !led_state;
		
		if( Allow_Recharge )
		{
			if( Charging )LED_Purple(led_state);
			else LED_Yellow(led_state);
		}
		else
			LED_Red(led_state);
			
		vTaskDelay(Led_Count); 
    }
}  

void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED_R=0;
	  else		if(++temp==time)	LED_R=~LED_R,temp=0;
}

