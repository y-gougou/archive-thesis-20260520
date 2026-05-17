#include "robot_select_init.h"

Robot_Parament_InitTypeDef  Robot_Parament; 

void Robot_Select(void)
{
	
  
	Divisor_Mode=4096/CAR_NUMBER+5;
	Car_Mode=(int) ((Get_adc_Average(CAR_MODE_ADC,10))/Divisor_Mode); 
  if(Car_Mode>10)Car_Mode=10;
	#if Mec
	{	
		if (Car_Mode==0)  Robot_Init(SENIOR_MEC_BS_wheelspacing, SENIOR_MEC_BS_axlespacing, MD36N_27, Photoelectric_500, Mecanum_100); 
		if (Car_Mode==1)  Robot_Init(SENIOR_MEC_BS_wheelspacing, SENIOR_MEC_BS_axlespacing, MD36N_27, Photoelectric_500, Mecanum_100); 
		
		if (Car_Mode==2)  Robot_Init(SENIOR_MEC_DL_wheelspacing, SENIOR_MEC_DL_axlespacing, MD36N_27, Photoelectric_500, Mecanum_152); 
		if (Car_Mode==3)  Robot_Init(TOP_MEC_BS_wheelspacing,    TOP_MEC_BS_axlespacing,    MD60N_18, Photoelectric_500, Mecanum_152); 
		
		if (Car_Mode==4)  Robot_Init(TOP_MEC_BS_wheelspacing,    TOP_MEC_BS_axlespacing,    MD60N_47, Photoelectric_500, Mecanum_152); 
		
		if (Car_Mode==5)  Robot_Init(TOP_MEC_DL_wheelspacing,    TOP_MEC_DL_axlespacing,    MD60N_18, Photoelectric_500, Mecanum_152); 
		if (Car_Mode==6)  Robot_Init(TOP_MEC_DL_wheelspacing,    TOP_MEC_DL_axlespacing,    MD60N_47, Photoelectric_500, Mecanum_152); 
		
		if (Car_Mode==7)  Robot_Init(FLAGSHIP_MEC_BS_wheelspacing,    FLAGSHIP_MEC_BS_axlespacing,    MD60N_18, Photoelectric_500, Mecanum_152); 
		if (Car_Mode==8)  Robot_Init(FLAGSHIP_MEC_BS_wheelspacing,    FLAGSHIP_MEC_BS_axlespacing,    MD60N_47, Photoelectric_500, Mecanum_152); 
		
		if (Car_Mode==9)   Robot_Init(FLAGSHIP_MEC_DL_wheelspacing,FLAGSHIP_MEC_DL_axlespacing,MD60N_18, Photoelectric_500, Mecanum_152); 
		if (Car_Mode==10)  Robot_Init(FLAGSHIP_MEC_DL_wheelspacing,FLAGSHIP_MEC_DL_axlespacing,MD60N_47, Photoelectric_500, Mecanum_152); 
	}
	#elif Omni
	{
		if (Car_Mode==0)  Robot_Init(Omni_Turn_Radiaus_164, MD36N_5_18, Photoelectric_500, FullDirecion_75); 
		if (Car_Mode==1)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_27,   Photoelectric_500, FullDirecion_127);
		if (Car_Mode==2)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_27,   Photoelectric_500, FullDirecion_127);
		if (Car_Mode==3)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_51,   Photoelectric_500, FullDirecion_127);

		if (Car_Mode==4)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Photoelectric_500, FullDirecion_127);
		if (Car_Mode==5)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Photoelectric_500, FullDirecion_152);
		if (Car_Mode==6)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Photoelectric_500, FullDirecion_203);
	}
	#endif
}

#if Mec

void Robot_Init(float wheelspacing,float axlespacing,int gearratio,int Accuracy,float tyre_diameter) 
{
  Robot_Parament.WheelSpacing=wheelspacing;   
	Robot_Parament.AxleSpacing=axlespacing;     
  Robot_Parament.GearRatio=gearratio;         
  Robot_Parament.EncoderAccuracy=Accuracy;    
  Robot_Parament.WheelDiameter=tyre_diameter; 
	
	
	
	Encoder_precision=EncoderMultiples*Robot_Parament.EncoderAccuracy*Robot_Parament.GearRatio;
	
	Wheel_perimeter=Robot_Parament.WheelDiameter*PI; 
	
  Wheel_spacing=Robot_Parament.WheelSpacing;  
 
	Wheel_axlespacing=Robot_Parament.AxleSpacing;    
}

#elif Omni

void Robot_Init(float omni_turn_radiaus,int gearratio,int Accuracy,float tyre_diameter)
{
	
  
  Robot_Parament.OmniTurnRadiaus=omni_turn_radiaus;
	
	
  Robot_Parament.GearRatio=gearratio;
	
  
  Robot_Parament.EncoderAccuracy=Accuracy;
	
  
  Robot_Parament.WheelDiameter=tyre_diameter;
	
	
	
	Encoder_precision=EncoderMultiples*Robot_Parament.EncoderAccuracy*Robot_Parament.GearRatio;
	
  
	Wheel_perimeter=Robot_Parament.WheelDiameter*PI;
	
  
  Omni_turn_radiaus=Robot_Parament.OmniTurnRadiaus;
}

#endif

