#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"

u8 OLED_GRAM[128][8];	 

void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    
		OLED_WR_Byte (0x00,OLED_CMD);      
		OLED_WR_Byte (0x10,OLED_CMD);      
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}

  
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_RS_Set();
	else 
	  OLED_RS_Clr();		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_RS_Set();   	  
} 

  
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  
	OLED_WR_Byte(0XAF,OLED_CMD);  
}

  
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD);  
	OLED_WR_Byte(0XAE,OLED_CMD);  
}	

  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram(); 
}

 
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' '; 
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  
		else temp=oled_asc2_1608[chr][t];		      
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 

void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,12,1);	 
        x+=8;
        p++;
    }  
}	 

	    
void OLED_Init(void)
{ 	
  GPIO_InitTypeDef GPIO_InitStructure;
	
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD  , ENABLE);  

	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_2MHz;  
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);				      

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR  , ENABLE);    
	
  
	PWR_BackupAccessCmd(ENABLE);
	
	
	RCC_LSEConfig(RCC_LSE_OFF);
	
	
	PWR_BackupAccessCmd(DISABLE);

	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
				  
	OLED_WR_Byte(0xAE,OLED_CMD); 
	OLED_WR_Byte(0xD5,OLED_CMD); 
	OLED_WR_Byte(80,OLED_CMD);   
	OLED_WR_Byte(0xA8,OLED_CMD); 
	OLED_WR_Byte(0X3F,OLED_CMD); 
	OLED_WR_Byte(0xD3,OLED_CMD); 
	OLED_WR_Byte(0X00,OLED_CMD); 

	OLED_WR_Byte(0x40,OLED_CMD); 
													
	OLED_WR_Byte(0x8D,OLED_CMD); 
	OLED_WR_Byte(0x14,OLED_CMD); 
	OLED_WR_Byte(0x20,OLED_CMD); 
	OLED_WR_Byte(0x02,OLED_CMD); 
	OLED_WR_Byte(0xA1,OLED_CMD); 
	OLED_WR_Byte(0xC0,OLED_CMD); 
	OLED_WR_Byte(0xDA,OLED_CMD); 
	OLED_WR_Byte(0x12,OLED_CMD); 
	 
	OLED_WR_Byte(0x81,OLED_CMD); 
	OLED_WR_Byte(0xEF,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); 
	OLED_WR_Byte(0xf1,OLED_CMD); 
	OLED_WR_Byte(0xDB,OLED_CMD); 
	OLED_WR_Byte(0x30,OLED_CMD); 

	OLED_WR_Byte(0xA4,OLED_CMD); 
	OLED_WR_Byte(0xA6,OLED_CMD); 
	OLED_WR_Byte(0xAF,OLED_CMD); 
	OLED_Clear();
}  

	    
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 font_width,u8 font_height)
{     			    
	 u8 t, i;
   for(i=0;i<(font_height/8);i++)	
	                                
	 {
			OLED_Set_Pos(x,y+i);	
			for(t=0;t<font_width;t++)		
		                              
			{	
					OLED_WR_Byte(Hzk16[(font_height/8)*no+i][t],OLED_DATA);
			}		
	 }
}	 

	  
void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 	
	 OLED_WR_Byte(0xb0+y,OLED_CMD);
	 OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	 OLED_WR_Byte((x&0x0f),OLED_CMD); 
} 

int* FenJie_float(const float fudian)
{
	static int tmp[3];
	float temp;
	temp = fudian;
	if(temp<0) temp = -temp,tmp[2]=-1;
	else tmp[2]=1;
	
	tmp[0] = (int)temp; 			
	tmp[1] = (temp - tmp[0])*1000;  
	return tmp;
}

void oled_showfloat(const float needtoshow,u8 show_x,u8 show_y,u8 zs_num,u8 xs_num)
{
	static int* p;
	p = FenJie_float(needtoshow);
	
	if(p[2]>0) OLED_ShowChar(show_x,show_y,'+',12,1);	 
	else OLED_ShowChar(show_x,show_y,'-',12,1); 		 
	
	OLED_ShowNumber(show_x+8,show_y,p[0],zs_num,12); 
	
	OLED_ShowChar(show_x+6+8*zs_num,show_y,'.',12,1);
	
	if(p[1]<100)
	{	
		if(xs_num==3)
		{
			OLED_ShowNumber(show_x+12+8*zs_num,show_y,0,1,12);	 
			if(p[1]>=10)		
				OLED_ShowNumber(show_x+18+8*zs_num,show_y,p[1],2,12);	 
			else
				OLED_ShowNumber(show_x+18+8*zs_num,show_y,0,1,12), 
				OLED_ShowNumber(show_x+24+8*zs_num,show_y,p[1],1,12);
		}
		else
		{
			if(p[1]>=0&&p[1]<100)
				OLED_ShowNumber(show_x+12+8*zs_num,show_y,0,1,12);	 
				OLED_ShowNumber(show_x+18+8*zs_num,show_y,p[1]/10,1,12);
		}
	}
	else
	{
		if(xs_num==3)
		{
			OLED_ShowNumber(show_x+12+8*zs_num,show_y,p[1],3,12);
		}	
		else
			OLED_ShowNumber(show_x+12+8*zs_num,show_y,p[1]/10,2,12);
	}
}

