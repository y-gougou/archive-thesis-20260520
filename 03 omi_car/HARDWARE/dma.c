#include "dma.h"
#include "sys.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN2;

void MYDMA_Init2(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	
  DMA_DeInit(DMA_CHx);	
	DMA1_MEM_LEN2=cndtr;		
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  
	DMA_InitStructure.DMA_BufferSize = cndtr;  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
	DMA_Init(DMA_CHx, &DMA_InitStructure);  
} 

void MYDMA_Enable2(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  
 	DMA_SetCurrDataCounter(DMA1_Channel7,DMA1_MEM_LEN2);
 	DMA_Cmd(DMA_CHx, ENABLE);  
}	  

void DMA_printf(const char *format,...)
{
	u32 length;
	va_list args;
	
	va_start(args, format);
	length = vsnprintf((char*)t2xbuf, sizeof(t2xbuf), (char*)format, args);
    va_end(args);
	USART_SendBuffer((const char*)t2xbuf,length);
}

u32 USART_SendBuffer(const char* buffer, u32 length)
{
	if( (buffer==NULL) || (length==0) )
	{
		return 0;
	}
 
	DMA_Cmd(DMA1_Channel7, DISABLE); 
	DMA_SetCurrDataCounter(DMA1_Channel7, length);
	DMA_Cmd(DMA1_Channel7, ENABLE); 
	while(1)
	{
		if(DMA_GetITStatus(DMA1_IT_TC7)!=RESET)	
		{
			DMA_ClearFlag(DMA1_IT_TC7);
			break;
		}
	}
	return length;
}
