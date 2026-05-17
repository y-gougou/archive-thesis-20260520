

#include "system.h"

#define START_TASK_PRIO	1

#define START_STK_SIZE 	256

TaskHandle_t StartTask_Handler;

void start_task(void *pvParameters);

int main(void)
{
    systemInit(); 

    
    xTaskCreate((TaskFunction_t )start_task,            
                (const char*    )"start_task",          
                (uint16_t       )START_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )START_TASK_PRIO,       
                (TaskHandle_t*  )&StartTask_Handler);   
    vTaskStartScheduler();  
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); 

    
    xTaskCreate(Balance_task,  "Balance_task",  BALANCE_STK_SIZE,  NULL, BALANCE_TASK_PRIO,  NULL);	
    xTaskCreate(MPU6050_task,  "MPU6050_task",  MPU6050_STK_SIZE,  NULL, MPU6050_TASK_PRIO,  NULL);	
    xTaskCreate(show_task,     "show_task",     SHOW_STK_SIZE,     NULL, SHOW_TASK_PRIO,     NULL); 
    xTaskCreate(led_task,      "led_task",      LED_STK_SIZE,      NULL, LED_TASK_PRIO,      NULL);	
    xTaskCreate(pstwo_task,    "PSTWO_task",    PS2_STK_SIZE,      NULL, PS2_TASK_PRIO,      NULL);	
    xTaskCreate(data_task,     "DATA_task",     DATA_STK_SIZE,     NULL, DATA_TASK_PRIO,     NULL);	

    vTaskDelete(StartTask_Handler); 

    taskEXIT_CRITICAL();            
}

