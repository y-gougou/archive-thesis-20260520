#ifndef __FILTER_H
#define __FILTER_H
#include "system.h"
  

extern float angle, angle_dot; 	
extern float yaw_angle, yaw_angle_dot; 	
void Kalman_Filter(float Accel,float Gyro);		
void Yijielvbo(float angle_m, float gyro_m);
void Yaw_Kalman_Filter(float Encoder_Yaw, float Gyro_Z);
#endif
