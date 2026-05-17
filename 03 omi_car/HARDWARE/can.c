#include "can.h"
#include "system.h"

u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	u16 i=0;
 	if(tsjw==0||tbs2==0||tbs1==0||brp==0)return 1;
	tsjw-=1; 
	tbs2-=1;
	tbs1-=1;
	brp-=1;

	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); 

	CAN1->MCR=0x0000;	
	CAN1->MCR|=1<<0;	
	while((CAN1->MSR&1<<0)==0)
	{
		i++;
		if(i>100)return 2; 
	}
	
	
	CAN1->MCR|=0<<7;
  
	
	CAN1->MCR|=0<<6;	
	
  
	CAN1->MCR|=0<<5;
	
  
	CAN1->MCR|=1<<4;
	
  
	CAN1->MCR|=0<<3;
	
  
	CAN1->MCR|=0<<2;
  
  
	CAN1->BTR=0x00000000; 
	
	
	CAN1->BTR|=mode<<30;
  
	
	CAN1->BTR|=tsjw<<24; 
  
	
	CAN1->BTR|=tbs2<<20; 
	
  
	CAN1->BTR|=tbs1<<16;
	
  
	CAN1->BTR|=brp<<0;  
  
  
	CAN1->MCR&=~(1<<0);	  
	while((CAN1->MSR&1<<0)==1)
	{
		i++;
		if(i>0XFFF0)return 3; 
	}
	
	
	

  CAN_FilterInitStructure.CAN_FilterNumber=1;
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

#if CAN1_RX0_INT_ENABLE
  
	
	
	CAN1->IER|=1<<1;			
	
	
	
  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	
	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  
	
	NVIC_Init(&NVIC_InitStructure);	

  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
#endif
	return 0;
}   

u8 CAN1_Tx_Msg(u32 id,u8 ide,u8 rtr,u8 len,u8 *dat)
{	   
	u8 mbox;	  
	if(CAN1->TSR&(1<<26))mbox=0;		  
	else if(CAN1->TSR&(1<<27))mbox=1;	
	else if(CAN1->TSR&(1<<28))mbox=2;	
	else return 0XFF;					        
	
	CAN1->sTxMailBox[mbox].TIR=0; 
	if(ide==0) 
	{
		id&=0x7ff; 
		id<<=21;		  
	}else	
	{
		id&=0X1FFFFFFF; 
		id<<=3;									   
	}
	CAN1->sTxMailBox[mbox].TIR|=id;		 
	CAN1->sTxMailBox[mbox].TIR|=ide<<2;	  
	CAN1->sTxMailBox[mbox].TIR|=rtr<<1;
	len&=0X0F; 
	CAN1->sTxMailBox[mbox].TDTR&=~(0X0000000F);
	CAN1->sTxMailBox[mbox].TDTR|=len;	
	
	
	CAN1->sTxMailBox[mbox].TDHR=(((u32)dat[7]<<24)|
								((u32)dat[6]<<16)|
 								((u32)dat[5]<<8)|
								((u32)dat[4]));
	CAN1->sTxMailBox[mbox].TDLR=(((u32)dat[3]<<24)|
								((u32)dat[2]<<16)|
 								((u32)dat[1]<<8)|
								((u32)dat[0]));
	CAN1->sTxMailBox[mbox].TIR|=1<<0; 
	return mbox;
}

u8 CAN1_Tx_Staus(u8 mbox)
{	
	u8 sta=0;					    
	switch (mbox)
	{
		case 0: 
			sta |= CAN1->TSR&(1<<0);			   
			sta |= CAN1->TSR&(1<<1);			   
			sta |=((CAN1->TSR&(1<<26))>>24); 
			break;
		case 1: 
			sta |= CAN1->TSR&(1<<8)>>8;		   
			sta |= CAN1->TSR&(1<<9)>>8;		   
			sta |=((CAN1->TSR&(1<<27))>>25); 
			break;
		case 2: 
			sta |= CAN1->TSR&(1<<16)>>16;	   
			sta |= CAN1->TSR&(1<<17)>>16;	   
			sta |=((CAN1->TSR&(1<<28))>>26); 
			break;
		default:
			sta=0X05; 
		break;
	}
	return sta;
} 

u8 CAN1_Msg_Pend(u8 fifox)
{
	if(fifox==0)return CAN1->RF0R&0x03; 
	else if(fifox==1)return CAN1->RF1R&0x03; 
	else return 0;
}

void CAN1_Rx_Msg(u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat)
{	   
	*ide=CAN1->sFIFOMailBox[fifox].RIR&0x04; 
 	if(*ide==0) 
	{
		*id=CAN1->sFIFOMailBox[fifox].RIR>>21;
	}else	     
	{
		*id=CAN1->sFIFOMailBox[fifox].RIR>>3;
	}
	*rtr=CAN1->sFIFOMailBox[fifox].RIR&0x02;	
	*len=CAN1->sFIFOMailBox[fifox].RDTR&0x0F; 
 	
	
	dat[0]=CAN1->sFIFOMailBox[fifox].RDLR&0XFF;
	dat[1]=(CAN1->sFIFOMailBox[fifox].RDLR>>8)&0XFF;
	dat[2]=(CAN1->sFIFOMailBox[fifox].RDLR>>16)&0XFF;
	dat[3]=(CAN1->sFIFOMailBox[fifox].RDLR>>24)&0XFF;    
	dat[4]=CAN1->sFIFOMailBox[fifox].RDHR&0XFF;
	dat[5]=(CAN1->sFIFOMailBox[fifox].RDHR>>8)&0XFF;
	dat[6]=(CAN1->sFIFOMailBox[fifox].RDHR>>16)&0XFF;
	dat[7]=(CAN1->sFIFOMailBox[fifox].RDHR>>24)&0XFF;    
  if(fifox==0)CAN1->RF0R|=0X20;      
	else if(fifox==1)CAN1->RF1R|=0X20; 
}

#if CAN1_RX0_INT_ENABLE	
void CAN1_RX0_IRQHandler(void)
{
	u32 id;
	u8 ide,rtr,len;     

	u8 temp_rxbuf[8];
  
	
	
 	CAN1_Rx_Msg(0,&id,&ide,&rtr,&len,temp_rxbuf);
	
	
	if(id==0x12345678)
	{
		u8 check=0;
		u8 i;
    for(i=0; i<8; i++)
    {
    
    }
		if( check==8 ) Get_Charging_HardWare=1;
	}
	
	
	
	else if(id==0x181)
	{
		CAN_ON_Flag=1,PS2_ON_Flag=0,APP_ON_Flag=0,Remote_ON_Flag=0,Usart_ON_Flag=0;
		command_lost_count=0;
		
		
		Move_X=((float)((short)((temp_rxbuf[0]<<8)+(temp_rxbuf[1]))))/1000; 
		Move_Y=((float)((short)((temp_rxbuf[2]<<8)+(temp_rxbuf[3]))))/1000;
		Move_Z=((float)((short)((temp_rxbuf[4]<<8)+(temp_rxbuf[5]))))/1000;
	}
	
	else if(id==0x182)
	{
		charger_check=0;
		
		
		Recharge_Red_Move_X=((float)((short)((temp_rxbuf[0]<<8)+(temp_rxbuf[1]))))/1000; 
		Recharge_Red_Move_Y=((float)((short)((temp_rxbuf[2]<<8)+(temp_rxbuf[3]))))/1000;
		Recharge_Red_Move_Z=((float)((short)((temp_rxbuf[4]<<8)+(temp_rxbuf[5]))))/1000;
		
		Charging=temp_rxbuf[6]&1;		
		L_A = (temp_rxbuf[6]>>5)&0x01;
		L_B = (temp_rxbuf[6]>>4)&0x01;
		R_B = (temp_rxbuf[6]>>3)&0x01;
		R_A = (temp_rxbuf[6]>>2)&0x01;
		RED_STATE = L_A + L_B + R_B + R_A;
		
		if(RED_STATE==0) Recharge_Red_Move_X = Recharge_Red_Move_Y = Recharge_Red_Move_Z = 0;
		if( Charging==1) Recharge_Red_Move_X = Recharge_Red_Move_Y = Recharge_Red_Move_Z = 0;
		
		
		if(temp_rxbuf[7]>128)Charging_Current=-(256-temp_rxbuf[7])*30;
		else Charging_Current=(temp_rxbuf[7]*30);
	}
	
}
#endif

u8 CAN1_Send_Msg(u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;	  	 						       
  mbox=CAN1_Tx_Msg(0X601,0,0,len,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; 
	if(i>=0XFFF)return 1; 
	return 0;	
}

u8 CAN1_Receive_Msg(u8 *buf)
{		   		   
	u32 id;
	u8 ide,rtr,len; 
	if(CAN1_Msg_Pend(0)==0)return 0;			   
  	CAN1_Rx_Msg(0,&id,&ide,&rtr,&len,buf); 
    if(id!=0x12||ide!=0||rtr!=0)len=0;		 
	return len;	
}

u8 CAN1_Send_MsgTEST(u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;	  	 						       
    mbox=CAN1_Tx_Msg(0X701,0,0,len,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; 
	if(i>=0XFFF)return 1;	
	return 0;	
}

u8 CAN1_Send_Num(u32 id,u8* msg)
{
	u8 mbox;
	u16 i=0;	  	 						       
  mbox=CAN1_Tx_Msg(id,0,0,8,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; 
	if(i>=0XFFF)return 1;	
	return 0;
}

u8 CAN1_Send_EXTid_Num(u32 id,u8* msg)
{
	u8 mbox;
	u16 i=0;	  	 						       
	mbox=CAN1_Tx_Msg(id,1,0,8,msg);   
	while((CAN1_Tx_Staus(mbox)!=0X07)&&(i<0XFFF))i++; 
	if(i>=0XFFF)return 1;	
	return 0;
}
