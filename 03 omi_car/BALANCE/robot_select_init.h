#ifndef __ROBOTSELECTINIT_H
#define __ROBOTSELECTINIT_H
#include "sys.h"
#include "system.h"

typedef struct  
{
  float WheelSpacing;      
  float AxleSpacing;       
  int   GearRatio;         
  int   EncoderAccuracy;   
  float WheelDiameter;     
  float OmniTurnRadiaus;   
}Robot_Parament_InitTypeDef;

#define SENIOR_MEC_BS_wheelspacing 0.176 
#define SENIOR_MEC_DL_wheelspacing 0.247 
#define TOP_MEC_BS_wheelspacing    0.311
#define TOP_MEC_DL_wheelspacing    0.295
#define FLAGSHIP_MEC_DL_wheelspacing  0.285
#define FLAGSHIP_MEC_BS_wheelspacing  0.292
#define TOP_MEC_DL_wheelspacing_Customized    0.446 
#define Senior_MEC_DL_wheelspacing_Customized 0.3   

#define SENIOR_MEC_BS_axlespacing 0.156
#define SENIOR_MEC_DL_axlespacing 0.214 
#define TOP_MEC_BS_axlespacing    0.308
#define TOP_MEC_DL_axlespacing    0.201
#define FLAGSHIP_MEC_DL_axlespacing 0.178
#define FLAGSHIP_MEC_BS_axlespacing 0.178
#define TOP_MEC_DL_axlespacing_Customized     0.401 
#define Senior_MEC_DL_axlespacing_Customized  0.24  

#define   MD36N_5_18  5.18f
#define   MD36N_27    27
#define   MD36N_51    51
#define   MD36N_71    71
#define   MD60N_18    18
#define   MD60N_47    47

#define		Photoelectric_500 500
#define	  Hall_13 					13

#define		Mecanum_60  0.060
#define		Mecanum_75  0.075
#define		Mecanum_100 0.100
#define		Mecanum_127 0.127
#define		Mecanum_152 0.152
 

#define	  FullDirecion_75  0.075
#define	  FullDirecion_127 0.127
#define	  FullDirecion_152 0.152
#define	  FullDirecion_203 0.203
#define	  FullDirecion_217 0.217

#define   Omni_Turn_Radiaus_164 0.164
#define   Omni_Turn_Radiaus_180 0.160 
#define   Omni_Turn_Radiaus_290 0.280 

#define   EncoderMultiples 4

#define CONTROL_FREQUENCY 100

void Robot_Select(void);
#if Mec
void Robot_Init(float wheelspacing, float axlespacing, int gearratio, int Accuracy, float tyre_diameter);
#elif Omni
void Robot_Init(float omni_turn_radiaus, int gearratio, int Accuracy, float tyre_diameter);
#endif

#endif
