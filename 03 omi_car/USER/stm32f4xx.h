

 

    
#ifndef __STM32F4xx_H
#define __STM32F4xx_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

  

#if !defined (STM32F40_41xxx) && !defined (STM32F427_437xx) && !defined (STM32F429_439xx) && !defined (STM32F401xx) && !defined (STM32F411xE)
     

    

    

        

        
#endif

#ifdef STM32F40XX
  #define STM32F40_41xxx
#endif 

#ifdef STM32F427X
  #define STM32F427_437xx
#endif 

#if !defined (STM32F40_41xxx) && !defined (STM32F427_437xx) && !defined (STM32F429_439xx) && !defined (STM32F401xx) && !defined (STM32F411xE)
 #error "Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif

#if !defined  (USE_STDPERIPH_DRIVER)

  
#endif 

           

#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)8000000) 
  
#endif 

#if !defined  (HSE_STARTUP_TIMEOUT) 
  #define HSE_STARTUP_TIMEOUT    ((uint16_t)0x05000)   
#endif    

#if !defined  (HSI_VALUE)   
  #define HSI_VALUE    ((uint32_t)16000000) 
#endif    

#define __STM32F4XX_STDPERIPH_VERSION_MAIN   (0x01) 
#define __STM32F4XX_STDPERIPH_VERSION_SUB1   (0x04) 
#define __STM32F4XX_STDPERIPH_VERSION_SUB2   (0x00) 
#define __STM32F4XX_STDPERIPH_VERSION_RC     (0x00)  
#define __STM32F4XX_STDPERIPH_VERSION        ((__STM32F4XX_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_RC))
                                             

#define __CM4_REV                 0x0001  
#define __MPU_PRESENT             1       
#define __NVIC_PRIO_BITS          4       
#define __Vendor_SysTickConfig    0       
#define __FPU_PRESENT             1       
#define __FPU_USED                1

typedef enum IRQn
{

  NonMaskableInt_IRQn         = -14,    
  MemoryManagement_IRQn       = -12,    
  BusFault_IRQn               = -11,    
  UsageFault_IRQn             = -10,    
  SVCall_IRQn                 = -5,     
  DebugMonitor_IRQn           = -4,     
  PendSV_IRQn                 = -2,     
  SysTick_IRQn                = -1,     

  WWDG_IRQn                   = 0,      
  PVD_IRQn                    = 1,      
  TAMP_STAMP_IRQn             = 2,      
  RTC_WKUP_IRQn               = 3,      
  FLASH_IRQn                  = 4,      
  RCC_IRQn                    = 5,      
  EXTI0_IRQn                  = 6,      
  EXTI1_IRQn                  = 7,      
  EXTI2_IRQn                  = 8,      
  EXTI3_IRQn                  = 9,      
  EXTI4_IRQn                  = 10,     
  DMA1_Stream0_IRQn           = 11,     
  DMA1_Stream1_IRQn           = 12,     
  DMA1_Stream2_IRQn           = 13,     
  DMA1_Stream3_IRQn           = 14,     
  DMA1_Stream4_IRQn           = 15,     
  DMA1_Stream5_IRQn           = 16,     
  DMA1_Stream6_IRQn           = 17,     
  ADC_IRQn                    = 18,     

#if defined (STM32F40_41xxx)
  CAN1_TX_IRQn                = 19,     
  CAN1_RX0_IRQn               = 20,     
  CAN1_RX1_IRQn               = 21,     
  CAN1_SCE_IRQn               = 22,     
  EXTI9_5_IRQn                = 23,     
  TIM1_BRK_TIM9_IRQn          = 24,     
  TIM1_UP_TIM10_IRQn          = 25,     
  TIM1_TRG_COM_TIM11_IRQn     = 26,     
  TIM1_CC_IRQn                = 27,     
  TIM2_IRQn                   = 28,     
  TIM3_IRQn                   = 29,     
  TIM4_IRQn                   = 30,     
  I2C1_EV_IRQn                = 31,     
  I2C1_ER_IRQn                = 32,     
  I2C2_EV_IRQn                = 33,     
  I2C2_ER_IRQn                = 34,     
  SPI1_IRQn                   = 35,     
  SPI2_IRQn                   = 36,     
  USART1_IRQn                 = 37,     
  USART2_IRQn                 = 38,     
  USART3_IRQn                 = 39,     
  EXTI15_10_IRQn              = 40,     
  RTC_Alarm_IRQn              = 41,     
  OTG_FS_WKUP_IRQn            = 42,     
  TIM8_BRK_TIM12_IRQn         = 43,     
  TIM8_UP_TIM13_IRQn          = 44,     
  TIM8_TRG_COM_TIM14_IRQn     = 45,     
  TIM8_CC_IRQn                = 46,     
  DMA1_Stream7_IRQn           = 47,     
  FSMC_IRQn                   = 48,     
  SDIO_IRQn                   = 49,     
  TIM5_IRQn                   = 50,     
  SPI3_IRQn                   = 51,     
  UART4_IRQn                  = 52,     
  UART5_IRQn                  = 53,     
  TIM6_DAC_IRQn               = 54,     
  TIM7_IRQn                   = 55,     
  DMA2_Stream0_IRQn           = 56,     
  DMA2_Stream1_IRQn           = 57,     
  DMA2_Stream2_IRQn           = 58,     
  DMA2_Stream3_IRQn           = 59,     
  DMA2_Stream4_IRQn           = 60,     
  ETH_IRQn                    = 61,     
  ETH_WKUP_IRQn               = 62,     
  CAN2_TX_IRQn                = 63,     
  CAN2_RX0_IRQn               = 64,     
  CAN2_RX1_IRQn               = 65,     
  CAN2_SCE_IRQn               = 66,     
  OTG_FS_IRQn                 = 67,     
  DMA2_Stream5_IRQn           = 68,     
  DMA2_Stream6_IRQn           = 69,     
  DMA2_Stream7_IRQn           = 70,     
  USART6_IRQn                 = 71,     
  I2C3_EV_IRQn                = 72,     
  I2C3_ER_IRQn                = 73,     
  OTG_HS_EP1_OUT_IRQn         = 74,     
  OTG_HS_EP1_IN_IRQn          = 75,     
  OTG_HS_WKUP_IRQn            = 76,     
  OTG_HS_IRQn                 = 77,     
  DCMI_IRQn                   = 78,     
  CRYP_IRQn                   = 79,     
  HASH_RNG_IRQn               = 80,     
  FPU_IRQn                    = 81      
#endif 

#if defined (STM32F427_437xx)
  CAN1_TX_IRQn                = 19,     
  CAN1_RX0_IRQn               = 20,     
  CAN1_RX1_IRQn               = 21,     
  CAN1_SCE_IRQn               = 22,     
  EXTI9_5_IRQn                = 23,     
  TIM1_BRK_TIM9_IRQn          = 24,     
  TIM1_UP_TIM10_IRQn          = 25,     
  TIM1_TRG_COM_TIM11_IRQn     = 26,     
  TIM1_CC_IRQn                = 27,     
  TIM2_IRQn                   = 28,     
  TIM3_IRQn                   = 29,     
  TIM4_IRQn                   = 30,     
  I2C1_EV_IRQn                = 31,     
  I2C1_ER_IRQn                = 32,     
  I2C2_EV_IRQn                = 33,     
  I2C2_ER_IRQn                = 34,       
  SPI1_IRQn                   = 35,     
  SPI2_IRQn                   = 36,     
  USART1_IRQn                 = 37,     
  USART2_IRQn                 = 38,     
  USART3_IRQn                 = 39,     
  EXTI15_10_IRQn              = 40,     
  RTC_Alarm_IRQn              = 41,     
  OTG_FS_WKUP_IRQn            = 42,         
  TIM8_BRK_TIM12_IRQn         = 43,     
  TIM8_UP_TIM13_IRQn          = 44,     
  TIM8_TRG_COM_TIM14_IRQn     = 45,     
  TIM8_CC_IRQn                = 46,     
  DMA1_Stream7_IRQn           = 47,     
  FMC_IRQn                    = 48,     
  SDIO_IRQn                   = 49,     
  TIM5_IRQn                   = 50,     
  SPI3_IRQn                   = 51,     
  UART4_IRQn                  = 52,     
  UART5_IRQn                  = 53,     
  TIM6_DAC_IRQn               = 54,     
  TIM7_IRQn                   = 55,     
  DMA2_Stream0_IRQn           = 56,     
  DMA2_Stream1_IRQn           = 57,     
  DMA2_Stream2_IRQn           = 58,     
  DMA2_Stream3_IRQn           = 59,     
  DMA2_Stream4_IRQn           = 60,     
  ETH_IRQn                    = 61,     
  ETH_WKUP_IRQn               = 62,     
  CAN2_TX_IRQn                = 63,     
  CAN2_RX0_IRQn               = 64,     
  CAN2_RX1_IRQn               = 65,     
  CAN2_SCE_IRQn               = 66,     
  OTG_FS_IRQn                 = 67,     
  DMA2_Stream5_IRQn           = 68,     
  DMA2_Stream6_IRQn           = 69,     
  DMA2_Stream7_IRQn           = 70,     
  USART6_IRQn                 = 71,     
  I2C3_EV_IRQn                = 72,     
  I2C3_ER_IRQn                = 73,     
  OTG_HS_EP1_OUT_IRQn         = 74,     
  OTG_HS_EP1_IN_IRQn          = 75,     
  OTG_HS_WKUP_IRQn            = 76,     
  OTG_HS_IRQn                 = 77,     
  DCMI_IRQn                   = 78,     
  CRYP_IRQn                   = 79,     
  HASH_RNG_IRQn               = 80,     
  FPU_IRQn                    = 81,     
  UART7_IRQn                  = 82,     
  UART8_IRQn                  = 83,     
  SPI4_IRQn                   = 84,     
  SPI5_IRQn                   = 85,     
  SPI6_IRQn                   = 86,     
  SAI1_IRQn                   = 87,     
  DMA2D_IRQn                  = 90         
#endif 
    
#if defined (STM32F429_439xx)
  CAN1_TX_IRQn                = 19,     
  CAN1_RX0_IRQn               = 20,     
  CAN1_RX1_IRQn               = 21,     
  CAN1_SCE_IRQn               = 22,     
  EXTI9_5_IRQn                = 23,     
  TIM1_BRK_TIM9_IRQn          = 24,     
  TIM1_UP_TIM10_IRQn          = 25,     
  TIM1_TRG_COM_TIM11_IRQn     = 26,     
  TIM1_CC_IRQn                = 27,     
  TIM2_IRQn                   = 28,     
  TIM3_IRQn                   = 29,     
  TIM4_IRQn                   = 30,     
  I2C1_EV_IRQn                = 31,     
  I2C1_ER_IRQn                = 32,     
  I2C2_EV_IRQn                = 33,     
  I2C2_ER_IRQn                = 34,       
  SPI1_IRQn                   = 35,     
  SPI2_IRQn                   = 36,     
  USART1_IRQn                 = 37,     
  USART2_IRQn                 = 38,     
  USART3_IRQn                 = 39,     
  EXTI15_10_IRQn              = 40,     
  RTC_Alarm_IRQn              = 41,     
  OTG_FS_WKUP_IRQn            = 42,         
  TIM8_BRK_TIM12_IRQn         = 43,     
  TIM8_UP_TIM13_IRQn          = 44,     
  TIM8_TRG_COM_TIM14_IRQn     = 45,     
  TIM8_CC_IRQn                = 46,     
  DMA1_Stream7_IRQn           = 47,     
  FMC_IRQn                    = 48,     
  SDIO_IRQn                   = 49,     
  TIM5_IRQn                   = 50,     
  SPI3_IRQn                   = 51,     
  UART4_IRQn                  = 52,     
  UART5_IRQn                  = 53,     
  TIM6_DAC_IRQn               = 54,     
  TIM7_IRQn                   = 55,     
  DMA2_Stream0_IRQn           = 56,     
  DMA2_Stream1_IRQn           = 57,     
  DMA2_Stream2_IRQn           = 58,     
  DMA2_Stream3_IRQn           = 59,     
  DMA2_Stream4_IRQn           = 60,     
  ETH_IRQn                    = 61,     
  ETH_WKUP_IRQn               = 62,     
  CAN2_TX_IRQn                = 63,     
  CAN2_RX0_IRQn               = 64,     
  CAN2_RX1_IRQn               = 65,     
  CAN2_SCE_IRQn               = 66,     
  OTG_FS_IRQn                 = 67,     
  DMA2_Stream5_IRQn           = 68,     
  DMA2_Stream6_IRQn           = 69,     
  DMA2_Stream7_IRQn           = 70,     
  USART6_IRQn                 = 71,     
  I2C3_EV_IRQn                = 72,     
  I2C3_ER_IRQn                = 73,     
  OTG_HS_EP1_OUT_IRQn         = 74,     
  OTG_HS_EP1_IN_IRQn          = 75,     
  OTG_HS_WKUP_IRQn            = 76,     
  OTG_HS_IRQn                 = 77,     
  DCMI_IRQn                   = 78,     
  CRYP_IRQn                   = 79,     
  HASH_RNG_IRQn               = 80,     
  FPU_IRQn                    = 81,     
  UART7_IRQn                  = 82,     
  UART8_IRQn                  = 83,     
  SPI4_IRQn                   = 84,     
  SPI5_IRQn                   = 85,     
  SPI6_IRQn                   = 86,     
  SAI1_IRQn                   = 87,     
  LTDC_IRQn                   = 88,     
  LTDC_ER_IRQn                = 89,     
  DMA2D_IRQn                  = 90      
#endif 
   
#if defined (STM32F401xx) || defined (STM32F411xE)
  EXTI9_5_IRQn                = 23,     
  TIM1_BRK_TIM9_IRQn          = 24,     
  TIM1_UP_TIM10_IRQn          = 25,     
  TIM1_TRG_COM_TIM11_IRQn     = 26,     
  TIM1_CC_IRQn                = 27,     
  TIM2_IRQn                   = 28,     
  TIM3_IRQn                   = 29,     
  TIM4_IRQn                   = 30,     
  I2C1_EV_IRQn                = 31,     
  I2C1_ER_IRQn                = 32,     
  I2C2_EV_IRQn                = 33,     
  I2C2_ER_IRQn                = 34,     
  SPI1_IRQn                   = 35,     
  SPI2_IRQn                   = 36,     
  USART1_IRQn                 = 37,     
  USART2_IRQn                 = 38,     
  EXTI15_10_IRQn              = 40,     
  RTC_Alarm_IRQn              = 41,     
  OTG_FS_WKUP_IRQn            = 42,     
  DMA1_Stream7_IRQn           = 47,     
  SDIO_IRQn                   = 49,     
  TIM5_IRQn                   = 50,     
  SPI3_IRQn                   = 51,     
  DMA2_Stream0_IRQn           = 56,     
  DMA2_Stream1_IRQn           = 57,     
  DMA2_Stream2_IRQn           = 58,     
  DMA2_Stream3_IRQn           = 59,     
  DMA2_Stream4_IRQn           = 60,     
  OTG_FS_IRQn                 = 67,     
  DMA2_Stream5_IRQn           = 68,     
  DMA2_Stream6_IRQn           = 69,     
  DMA2_Stream7_IRQn           = 70,     
  USART6_IRQn                 = 71,     
  I2C3_EV_IRQn                = 72,     
  I2C3_ER_IRQn                = 73,     
  FPU_IRQn                    = 81,      
#if defined (STM32F401xx)
  SPI4_IRQn                   = 84       
#endif 
#if defined (STM32F411xE)
  SPI4_IRQn                   = 84,     
  SPI5_IRQn                   = 85      
#endif 
#endif 

} IRQn_Type;

#include "core_cm4.h"             
#include "system_stm32f4xx.h"
#include <stdint.h>
#include "arm_math.h"

  

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;   

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16;  
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8;   

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16;  
typedef __I uint8_t vuc8;   

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

   

typedef struct
{
  __IO uint32_t SR;     
  __IO uint32_t CR1;          
  __IO uint32_t CR2;    
  __IO uint32_t SMPR1;  
  __IO uint32_t SMPR2;  
  __IO uint32_t JOFR1;  
  __IO uint32_t JOFR2;  
  __IO uint32_t JOFR3;  
  __IO uint32_t JOFR4;  
  __IO uint32_t HTR;    
  __IO uint32_t LTR;    
  __IO uint32_t SQR1;   
  __IO uint32_t SQR2;   
  __IO uint32_t SQR3;   
  __IO uint32_t JSQR;   
  __IO uint32_t JDR1;   
  __IO uint32_t JDR2;   
  __IO uint32_t JDR3;   
  __IO uint32_t JDR4;   
  __IO uint32_t DR;     
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;    
  __IO uint32_t CCR;    
  __IO uint32_t CDR;    

} ADC_Common_TypeDef;

typedef struct
{
  __IO uint32_t TIR;  
  __IO uint32_t TDTR; 
  __IO uint32_t TDLR; 
  __IO uint32_t TDHR; 
} CAN_TxMailBox_TypeDef;

  
typedef struct
{
  __IO uint32_t RIR;  
  __IO uint32_t RDTR; 
  __IO uint32_t RDLR; 
  __IO uint32_t RDHR; 
} CAN_FIFOMailBox_TypeDef;

  
typedef struct
{
  __IO uint32_t FR1; 
  __IO uint32_t FR2; 
} CAN_FilterRegister_TypeDef;

  
typedef struct
{
  __IO uint32_t              MCR;                 
  __IO uint32_t              MSR;                 
  __IO uint32_t              TSR;                 
  __IO uint32_t              RF0R;                
  __IO uint32_t              RF1R;                
  __IO uint32_t              IER;                 
  __IO uint32_t              ESR;                 
  __IO uint32_t              BTR;                 
  uint32_t                   RESERVED0[88];       
  CAN_TxMailBox_TypeDef      sTxMailBox[3];       
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];     
  uint32_t                   RESERVED1[12];       
  __IO uint32_t              FMR;                 
  __IO uint32_t              FM1R;                
  uint32_t                   RESERVED2;           
  __IO uint32_t              FS1R;                
  uint32_t                   RESERVED3;           
  __IO uint32_t              FFA1R;               
  uint32_t                   RESERVED4;           
  __IO uint32_t              FA1R;                
  uint32_t                   RESERVED5[8];         
  CAN_FilterRegister_TypeDef sFilterRegister[28]; 
} CAN_TypeDef;

typedef struct
{
  __IO uint32_t DR;         
  __IO uint8_t  IDR;        
  uint8_t       RESERVED0;  
  uint16_t      RESERVED1;  
  __IO uint32_t CR;         
} CRC_TypeDef;

typedef struct
{
  __IO uint32_t CR;       
  __IO uint32_t SWTRIGR;  
  __IO uint32_t DHR12R1;  
  __IO uint32_t DHR12L1;  
  __IO uint32_t DHR8R1;   
  __IO uint32_t DHR12R2;  
  __IO uint32_t DHR12L2;  
  __IO uint32_t DHR8R2;   
  __IO uint32_t DHR12RD;  
  __IO uint32_t DHR12LD;  
  __IO uint32_t DHR8RD;   
  __IO uint32_t DOR1;     
  __IO uint32_t DOR2;     
  __IO uint32_t SR;       
} DAC_TypeDef;

typedef struct
{
  __IO uint32_t IDCODE;  
  __IO uint32_t CR;      
  __IO uint32_t APB1FZ;  
  __IO uint32_t APB2FZ;  
}DBGMCU_TypeDef;

typedef struct
{
  __IO uint32_t CR;       
  __IO uint32_t SR;       
  __IO uint32_t RISR;     
  __IO uint32_t IER;      
  __IO uint32_t MISR;     
  __IO uint32_t ICR;      
  __IO uint32_t ESCR;     
  __IO uint32_t ESUR;     
  __IO uint32_t CWSTRTR;  
  __IO uint32_t CWSIZER;  
  __IO uint32_t DR;       
} DCMI_TypeDef;

typedef struct
{
  __IO uint32_t CR;     
  __IO uint32_t NDTR;   
  __IO uint32_t PAR;    
  __IO uint32_t M0AR;   
  __IO uint32_t M1AR;   
  __IO uint32_t FCR;    
} DMA_Stream_TypeDef;

typedef struct
{
  __IO uint32_t LISR;   
  __IO uint32_t HISR;   
  __IO uint32_t LIFCR;  
  __IO uint32_t HIFCR;  
} DMA_TypeDef;
 

typedef struct
{
  __IO uint32_t CR;            
  __IO uint32_t ISR;           
  __IO uint32_t IFCR;          
  __IO uint32_t FGMAR;         
  __IO uint32_t FGOR;          
  __IO uint32_t BGMAR;         
  __IO uint32_t BGOR;          
  __IO uint32_t FGPFCCR;       
  __IO uint32_t FGCOLR;        
  __IO uint32_t BGPFCCR;       
  __IO uint32_t BGCOLR;        
  __IO uint32_t FGCMAR;        
  __IO uint32_t BGCMAR;        
  __IO uint32_t OPFCCR;        
  __IO uint32_t OCOLR;         
  __IO uint32_t OMAR;          
  __IO uint32_t OOR;           
  __IO uint32_t NLR;           
  __IO uint32_t LWR;           
  __IO uint32_t AMTCR;         
  uint32_t      RESERVED[236]; 
  __IO uint32_t FGCLUT[256];   
  __IO uint32_t BGCLUT[256];   
} DMA2D_TypeDef;

typedef struct
{
  __IO uint32_t MACCR;
  __IO uint32_t MACFFR;
  __IO uint32_t MACHTHR;
  __IO uint32_t MACHTLR;
  __IO uint32_t MACMIIAR;
  __IO uint32_t MACMIIDR;
  __IO uint32_t MACFCR;
  __IO uint32_t MACVLANTR;             
  uint32_t      RESERVED0[2];
  __IO uint32_t MACRWUFFR;             
  __IO uint32_t MACPMTCSR;
  uint32_t      RESERVED1[2];
  __IO uint32_t MACSR;                 
  __IO uint32_t MACIMR;
  __IO uint32_t MACA0HR;
  __IO uint32_t MACA0LR;
  __IO uint32_t MACA1HR;
  __IO uint32_t MACA1LR;
  __IO uint32_t MACA2HR;
  __IO uint32_t MACA2LR;
  __IO uint32_t MACA3HR;
  __IO uint32_t MACA3LR;               
  uint32_t      RESERVED2[40];
  __IO uint32_t MMCCR;                 
  __IO uint32_t MMCRIR;
  __IO uint32_t MMCTIR;
  __IO uint32_t MMCRIMR;
  __IO uint32_t MMCTIMR;               
  uint32_t      RESERVED3[14];
  __IO uint32_t MMCTGFSCCR;            
  __IO uint32_t MMCTGFMSCCR;
  uint32_t      RESERVED4[5];
  __IO uint32_t MMCTGFCR;
  uint32_t      RESERVED5[10];
  __IO uint32_t MMCRFCECR;
  __IO uint32_t MMCRFAECR;
  uint32_t      RESERVED6[10];
  __IO uint32_t MMCRGUFCR;
  uint32_t      RESERVED7[334];
  __IO uint32_t PTPTSCR;
  __IO uint32_t PTPSSIR;
  __IO uint32_t PTPTSHR;
  __IO uint32_t PTPTSLR;
  __IO uint32_t PTPTSHUR;
  __IO uint32_t PTPTSLUR;
  __IO uint32_t PTPTSAR;
  __IO uint32_t PTPTTHR;
  __IO uint32_t PTPTTLR;
  __IO uint32_t RESERVED8;
  __IO uint32_t PTPTSSR;
  uint32_t      RESERVED9[565];
  __IO uint32_t DMABMR;
  __IO uint32_t DMATPDR;
  __IO uint32_t DMARPDR;
  __IO uint32_t DMARDLAR;
  __IO uint32_t DMATDLAR;
  __IO uint32_t DMASR;
  __IO uint32_t DMAOMR;
  __IO uint32_t DMAIER;
  __IO uint32_t DMAMFBOCR;
  __IO uint32_t DMARSWTR;
  uint32_t      RESERVED10[8];
  __IO uint32_t DMACHTDR;
  __IO uint32_t DMACHRDR;
  __IO uint32_t DMACHTBAR;
  __IO uint32_t DMACHRBAR;
} ETH_TypeDef;

typedef struct
{
  __IO uint32_t IMR;    
  __IO uint32_t EMR;    
  __IO uint32_t RTSR;   
  __IO uint32_t FTSR;   
  __IO uint32_t SWIER;  
  __IO uint32_t PR;     
} EXTI_TypeDef;

typedef struct
{
  __IO uint32_t ACR;      
  __IO uint32_t KEYR;     
  __IO uint32_t OPTKEYR;  
  __IO uint32_t SR;       
  __IO uint32_t CR;       
  __IO uint32_t OPTCR;    
  __IO uint32_t OPTCR1;   
} FLASH_TypeDef;

#if defined (STM32F40_41xxx)

typedef struct
{
  __IO uint32_t BTCR[8];       
} FSMC_Bank1_TypeDef; 

  
typedef struct
{
  __IO uint32_t BWTR[7];    
} FSMC_Bank1E_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR2;       
  __IO uint32_t SR2;        
  __IO uint32_t PMEM2;      
  __IO uint32_t PATT2;      
  uint32_t      RESERVED0;  
  __IO uint32_t ECCR2;      
} FSMC_Bank2_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR3;       
  __IO uint32_t SR3;        
  __IO uint32_t PMEM3;      
  __IO uint32_t PATT3;      
  uint32_t      RESERVED0;  
  __IO uint32_t ECCR3;      
} FSMC_Bank3_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR4;       
  __IO uint32_t SR4;        
  __IO uint32_t PMEM4;      
  __IO uint32_t PATT4;      
  __IO uint32_t PIO4;       
} FSMC_Bank4_TypeDef; 
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)

typedef struct
{
  __IO uint32_t BTCR[8];       
} FMC_Bank1_TypeDef; 

  
typedef struct
{
  __IO uint32_t BWTR[7];    
} FMC_Bank1E_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR2;       
  __IO uint32_t SR2;        
  __IO uint32_t PMEM2;      
  __IO uint32_t PATT2;      
  uint32_t      RESERVED0;  
  __IO uint32_t ECCR2;      
} FMC_Bank2_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR3;       
  __IO uint32_t SR3;        
  __IO uint32_t PMEM3;      
  __IO uint32_t PATT3;      
  uint32_t      RESERVED0;  
  __IO uint32_t ECCR3;      
} FMC_Bank3_TypeDef;

  
typedef struct
{
  __IO uint32_t PCR4;       
  __IO uint32_t SR4;        
  __IO uint32_t PMEM4;      
  __IO uint32_t PATT4;      
  __IO uint32_t PIO4;       
} FMC_Bank4_TypeDef; 

  
typedef struct
{
  __IO uint32_t SDCR[2];        
  __IO uint32_t SDTR[2];        
  __IO uint32_t SDCMR;       
  __IO uint32_t SDRTR;       
  __IO uint32_t SDSR;        
} FMC_Bank5_6_TypeDef; 
#endif 

typedef struct
{
  __IO uint32_t MODER;    
  __IO uint32_t OTYPER;   
  __IO uint32_t OSPEEDR;  
  __IO uint32_t PUPDR;    
  __IO uint32_t IDR;      
  __IO uint32_t ODR;      
  __IO uint16_t BSRRL;    
  __IO uint16_t BSRRH;    
  __IO uint32_t LCKR;     
  __IO uint32_t AFR[2];   
} GPIO_TypeDef;

  
typedef struct
{
  __IO uint32_t MEMRMP;       
  __IO uint32_t PMC;          
  __IO uint32_t EXTICR[4];    
  uint32_t      RESERVED[2];   
  __IO uint32_t CMPCR;        
} SYSCFG_TypeDef;

typedef struct
{
  __IO uint16_t CR1;        
  uint16_t      RESERVED0;  
  __IO uint16_t CR2;        
  uint16_t      RESERVED1;  
  __IO uint16_t OAR1;       
  uint16_t      RESERVED2;  
  __IO uint16_t OAR2;       
  uint16_t      RESERVED3;  
  __IO uint16_t DR;         
  uint16_t      RESERVED4;  
  __IO uint16_t SR1;        
  uint16_t      RESERVED5;  
  __IO uint16_t SR2;        
  uint16_t      RESERVED6;  
  __IO uint16_t CCR;        
  uint16_t      RESERVED7;  
  __IO uint16_t TRISE;      
  uint16_t      RESERVED8;  
  __IO uint16_t FLTR;       
  uint16_t      RESERVED9;  
} I2C_TypeDef;

typedef struct
{
  __IO uint32_t KR;   
  __IO uint32_t PR;   
  __IO uint32_t RLR;  
  __IO uint32_t SR;   
} IWDG_TypeDef;

  
typedef struct
{
  uint32_t      RESERVED0[2];  
  __IO uint32_t SSCR;          
  __IO uint32_t BPCR;          
  __IO uint32_t AWCR;          
  __IO uint32_t TWCR;          
  __IO uint32_t GCR;           
  uint32_t      RESERVED1[2];  
  __IO uint32_t SRCR;          
  uint32_t      RESERVED2[1];  
  __IO uint32_t BCCR;          
  uint32_t      RESERVED3[1];  
  __IO uint32_t IER;           
  __IO uint32_t ISR;           
  __IO uint32_t ICR;           
  __IO uint32_t LIPCR;         
  __IO uint32_t CPSR;          
  __IO uint32_t CDSR;         
} LTDC_TypeDef;  

  
typedef struct
{  
  __IO uint32_t CR;            
  __IO uint32_t WHPCR;         
  __IO uint32_t WVPCR;         
  __IO uint32_t CKCR;          
  __IO uint32_t PFCR;          
  __IO uint32_t CACR;          
  __IO uint32_t DCCR;          
  __IO uint32_t BFCR;          
  uint32_t      RESERVED0[2];  
  __IO uint32_t CFBAR;         
  __IO uint32_t CFBLR;         
  __IO uint32_t CFBLNR;        
  uint32_t      RESERVED1[3];  
  __IO uint32_t CLUTWR;         

} LTDC_Layer_TypeDef;

typedef struct
{
  __IO uint32_t CR;   
  __IO uint32_t CSR;  
} PWR_TypeDef;

typedef struct
{
  __IO uint32_t CR;            
  __IO uint32_t PLLCFGR;       
  __IO uint32_t CFGR;          
  __IO uint32_t CIR;           
  __IO uint32_t AHB1RSTR;      
  __IO uint32_t AHB2RSTR;      
  __IO uint32_t AHB3RSTR;      
  uint32_t      RESERVED0;     
  __IO uint32_t APB1RSTR;      
  __IO uint32_t APB2RSTR;      
  uint32_t      RESERVED1[2];  
  __IO uint32_t AHB1ENR;       
  __IO uint32_t AHB2ENR;       
  __IO uint32_t AHB3ENR;       
  uint32_t      RESERVED2;     
  __IO uint32_t APB1ENR;       
  __IO uint32_t APB2ENR;       
  uint32_t      RESERVED3[2];  
  __IO uint32_t AHB1LPENR;     
  __IO uint32_t AHB2LPENR;     
  __IO uint32_t AHB3LPENR;     
  uint32_t      RESERVED4;     
  __IO uint32_t APB1LPENR;     
  __IO uint32_t APB2LPENR;     
  uint32_t      RESERVED5[2];  
  __IO uint32_t BDCR;          
  __IO uint32_t CSR;           
  uint32_t      RESERVED6[2];  
  __IO uint32_t SSCGR;         
  __IO uint32_t PLLI2SCFGR;    
  __IO uint32_t PLLSAICFGR;    
  __IO uint32_t DCKCFGR;       

} RCC_TypeDef;

typedef struct
{
  __IO uint32_t TR;      
  __IO uint32_t DR;      
  __IO uint32_t CR;      
  __IO uint32_t ISR;     
  __IO uint32_t PRER;    
  __IO uint32_t WUTR;    
  __IO uint32_t CALIBR;  
  __IO uint32_t ALRMAR;  
  __IO uint32_t ALRMBR;  
  __IO uint32_t WPR;     
  __IO uint32_t SSR;     
  __IO uint32_t SHIFTR;  
  __IO uint32_t TSTR;    
  __IO uint32_t TSDR;    
  __IO uint32_t TSSSR;   
  __IO uint32_t CALR;    
  __IO uint32_t TAFCR;   
  __IO uint32_t ALRMASSR;
  __IO uint32_t ALRMBSSR;
  uint32_t RESERVED7;    
  __IO uint32_t BKP0R;   
  __IO uint32_t BKP1R;   
  __IO uint32_t BKP2R;   
  __IO uint32_t BKP3R;   
  __IO uint32_t BKP4R;   
  __IO uint32_t BKP5R;   
  __IO uint32_t BKP6R;   
  __IO uint32_t BKP7R;   
  __IO uint32_t BKP8R;   
  __IO uint32_t BKP9R;   
  __IO uint32_t BKP10R;  
  __IO uint32_t BKP11R;  
  __IO uint32_t BKP12R;  
  __IO uint32_t BKP13R;  
  __IO uint32_t BKP14R;  
  __IO uint32_t BKP15R;  
  __IO uint32_t BKP16R;  
  __IO uint32_t BKP17R;  
  __IO uint32_t BKP18R;  
  __IO uint32_t BKP19R;  
} RTC_TypeDef;

  
typedef struct
{
  __IO uint32_t GCR;      
} SAI_TypeDef;

typedef struct
{
  __IO uint32_t CR1;      
  __IO uint32_t CR2;      
  __IO uint32_t FRCR;     
  __IO uint32_t SLOTR;    
  __IO uint32_t IMR;      
  __IO uint32_t SR;       
  __IO uint32_t CLRFR;    
  __IO uint32_t DR;       
} SAI_Block_TypeDef;

typedef struct
{
  __IO uint32_t POWER;          
  __IO uint32_t CLKCR;          
  __IO uint32_t ARG;            
  __IO uint32_t CMD;            
  __I uint32_t  RESPCMD;        
  __I uint32_t  RESP1;          
  __I uint32_t  RESP2;          
  __I uint32_t  RESP3;          
  __I uint32_t  RESP4;          
  __IO uint32_t DTIMER;         
  __IO uint32_t DLEN;           
  __IO uint32_t DCTRL;          
  __I uint32_t  DCOUNT;         
  __I uint32_t  STA;            
  __IO uint32_t ICR;            
  __IO uint32_t MASK;           
  uint32_t      RESERVED0[2];   
  __I uint32_t  FIFOCNT;        
  uint32_t      RESERVED1[13];  
  __IO uint32_t FIFO;           
} SDIO_TypeDef;

typedef struct
{
  __IO uint16_t CR1;        
  uint16_t      RESERVED0;  
  __IO uint16_t CR2;        
  uint16_t      RESERVED1;  
  __IO uint16_t SR;         
  uint16_t      RESERVED2;  
  __IO uint16_t DR;         
  uint16_t      RESERVED3;  
  __IO uint16_t CRCPR;      
  uint16_t      RESERVED4;  
  __IO uint16_t RXCRCR;     
  uint16_t      RESERVED5;  
  __IO uint16_t TXCRCR;     
  uint16_t      RESERVED6;  
  __IO uint16_t I2SCFGR;    
  uint16_t      RESERVED7;  
  __IO uint16_t I2SPR;      
  uint16_t      RESERVED8;  
} SPI_TypeDef;

typedef struct
{
  __IO uint16_t CR1;         
  uint16_t      RESERVED0;   
  __IO uint16_t CR2;         
  uint16_t      RESERVED1;   
  __IO uint16_t SMCR;        
  uint16_t      RESERVED2;   
  __IO uint16_t DIER;        
  uint16_t      RESERVED3;   
  __IO uint16_t SR;          
  uint16_t      RESERVED4;   
  __IO uint16_t EGR;         
  uint16_t      RESERVED5;   
  __IO uint16_t CCMR1;       
  uint16_t      RESERVED6;   
  __IO uint16_t CCMR2;       
  uint16_t      RESERVED7;   
  __IO uint16_t CCER;        
  uint16_t      RESERVED8;   
  __IO uint32_t CNT;         
  __IO uint16_t PSC;         
  uint16_t      RESERVED9;   
  __IO uint32_t ARR;         
  __IO uint16_t RCR;         
  uint16_t      RESERVED10;  
  __IO uint32_t CCR1;        
  __IO uint32_t CCR2;        
  __IO uint32_t CCR3;        
  __IO uint32_t CCR4;        
  __IO uint16_t BDTR;        
  uint16_t      RESERVED11;  
  __IO uint16_t DCR;         
  uint16_t      RESERVED12;  
  __IO uint16_t DMAR;        
  uint16_t      RESERVED13;  
  __IO uint16_t OR;          
  uint16_t      RESERVED14;  
} TIM_TypeDef;

 
typedef struct
{
  __IO uint16_t SR;         
  uint16_t      RESERVED0;  
  __IO uint16_t DR;         
  uint16_t      RESERVED1;  
  __IO uint16_t BRR;        
  uint16_t      RESERVED2;  
  __IO uint16_t CR1;        
  uint16_t      RESERVED3;  
  __IO uint16_t CR2;        
  uint16_t      RESERVED4;  
  __IO uint16_t CR3;        
  uint16_t      RESERVED5;  
  __IO uint16_t GTPR;       
  uint16_t      RESERVED6;  
} USART_TypeDef;

typedef struct
{
  __IO uint32_t CR;   
  __IO uint32_t CFR;  
  __IO uint32_t SR;   
} WWDG_TypeDef;

typedef struct
{
  __IO uint32_t CR;         
  __IO uint32_t SR;         
  __IO uint32_t DR;         
  __IO uint32_t DOUT;       
  __IO uint32_t DMACR;      
  __IO uint32_t IMSCR;      
  __IO uint32_t RISR;       
  __IO uint32_t MISR;       
  __IO uint32_t K0LR;       
  __IO uint32_t K0RR;       
  __IO uint32_t K1LR;       
  __IO uint32_t K1RR;       
  __IO uint32_t K2LR;       
  __IO uint32_t K2RR;       
  __IO uint32_t K3LR;       
  __IO uint32_t K3RR;       
  __IO uint32_t IV0LR;      
  __IO uint32_t IV0RR;      
  __IO uint32_t IV1LR;      
  __IO uint32_t IV1RR;      
  __IO uint32_t CSGCMCCM0R; 
  __IO uint32_t CSGCMCCM1R; 
  __IO uint32_t CSGCMCCM2R; 
  __IO uint32_t CSGCMCCM3R; 
  __IO uint32_t CSGCMCCM4R; 
  __IO uint32_t CSGCMCCM5R; 
  __IO uint32_t CSGCMCCM6R; 
  __IO uint32_t CSGCMCCM7R; 
  __IO uint32_t CSGCM0R;    
  __IO uint32_t CSGCM1R;    
  __IO uint32_t CSGCM2R;    
  __IO uint32_t CSGCM3R;    
  __IO uint32_t CSGCM4R;    
  __IO uint32_t CSGCM5R;    
  __IO uint32_t CSGCM6R;    
  __IO uint32_t CSGCM7R;    
} CRYP_TypeDef;

  
typedef struct 
{
  __IO uint32_t CR;               
  __IO uint32_t DIN;              
  __IO uint32_t STR;              
  __IO uint32_t HR[5];            
  __IO uint32_t IMR;              
  __IO uint32_t SR;               
       uint32_t RESERVED[52];     
  __IO uint32_t CSR[54];          
} HASH_TypeDef;

  
typedef struct 
{
  __IO uint32_t HR[8];      
} HASH_DIGEST_TypeDef;

  
typedef struct 
{
  __IO uint32_t CR;  
  __IO uint32_t SR;  
  __IO uint32_t DR;  
} RNG_TypeDef;

  

#define FLASH_BASE            ((uint32_t)0x08000000) 
#define CCMDATARAM_BASE       ((uint32_t)0x10000000) 
#define SRAM1_BASE            ((uint32_t)0x20000000) 
#define SRAM2_BASE            ((uint32_t)0x2001C000) 
#define SRAM3_BASE            ((uint32_t)0x20020000) 
#define PERIPH_BASE           ((uint32_t)0x40000000) 
#define BKPSRAM_BASE          ((uint32_t)0x40024000) 

#if defined (STM32F40_41xxx)
#define FSMC_R_BASE           ((uint32_t)0xA0000000) 
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define FMC_R_BASE            ((uint32_t)0xA0000000) 
#endif 

#define CCMDATARAM_BB_BASE    ((uint32_t)0x12000000) 
#define SRAM1_BB_BASE         ((uint32_t)0x22000000) 
#define SRAM2_BB_BASE         ((uint32_t)0x2201C000) 
#define SRAM3_BB_BASE         ((uint32_t)0x22400000) 
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) 
#define BKPSRAM_BB_BASE       ((uint32_t)0x42024000) 

#define SRAM_BASE             SRAM1_BASE
#define SRAM_BB_BASE          SRAM1_BB_BASE

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define TIM12_BASE            (APB1PERIPH_BASE + 0x1800)
#define TIM13_BASE            (APB1PERIPH_BASE + 0x1C00)
#define TIM14_BASE            (APB1PERIPH_BASE + 0x2000)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define I2S2ext_BASE          (APB1PERIPH_BASE + 0x3400)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)
#define I2S3ext_BASE          (APB1PERIPH_BASE + 0x4000)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASE             (APB1PERIPH_BASE + 0x5C00)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE             (APB1PERIPH_BASE + 0x6800)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE              (APB1PERIPH_BASE + 0x7400)
#define UART7_BASE            (APB1PERIPH_BASE + 0x7800)
#define UART8_BASE            (APB1PERIPH_BASE + 0x7C00)

#define TIM1_BASE             (APB2PERIPH_BASE + 0x0000)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x0400)
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000)
#define USART6_BASE           (APB2PERIPH_BASE + 0x1400)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2000)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2100)
#define ADC3_BASE             (APB2PERIPH_BASE + 0x2200)
#define ADC_BASE              (APB2PERIPH_BASE + 0x2300)
#define SDIO_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define SPI4_BASE             (APB2PERIPH_BASE + 0x3400)
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00)
#define TIM9_BASE             (APB2PERIPH_BASE + 0x4000)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x4400)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x4800)
#define SPI5_BASE             (APB2PERIPH_BASE + 0x5000)
#define SPI6_BASE             (APB2PERIPH_BASE + 0x5400)
#define SAI1_BASE             (APB2PERIPH_BASE + 0x5800)
#define SAI1_Block_A_BASE     (SAI1_BASE + 0x004)
#define SAI1_Block_B_BASE     (SAI1_BASE + 0x024)
#define LTDC_BASE             (APB2PERIPH_BASE + 0x6800)
#define LTDC_Layer1_BASE      (LTDC_BASE + 0x84)
#define LTDC_Layer2_BASE      (LTDC_BASE + 0x104) 

#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE            (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE            (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE            (AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASE            (AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASE            (AHB1PERIPH_BASE + 0x2800)
#define CRC_BASE              (AHB1PERIPH_BASE + 0x3000)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x3C00)
#define DMA1_BASE             (AHB1PERIPH_BASE + 0x6000)
#define DMA1_Stream0_BASE     (DMA1_BASE + 0x010)
#define DMA1_Stream1_BASE     (DMA1_BASE + 0x028)
#define DMA1_Stream2_BASE     (DMA1_BASE + 0x040)
#define DMA1_Stream3_BASE     (DMA1_BASE + 0x058)
#define DMA1_Stream4_BASE     (DMA1_BASE + 0x070)
#define DMA1_Stream5_BASE     (DMA1_BASE + 0x088)
#define DMA1_Stream6_BASE     (DMA1_BASE + 0x0A0)
#define DMA1_Stream7_BASE     (DMA1_BASE + 0x0B8)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x6400)
#define DMA2_Stream0_BASE     (DMA2_BASE + 0x010)
#define DMA2_Stream1_BASE     (DMA2_BASE + 0x028)
#define DMA2_Stream2_BASE     (DMA2_BASE + 0x040)
#define DMA2_Stream3_BASE     (DMA2_BASE + 0x058)
#define DMA2_Stream4_BASE     (DMA2_BASE + 0x070)
#define DMA2_Stream5_BASE     (DMA2_BASE + 0x088)
#define DMA2_Stream6_BASE     (DMA2_BASE + 0x0A0)
#define DMA2_Stream7_BASE     (DMA2_BASE + 0x0B8)
#define ETH_BASE              (AHB1PERIPH_BASE + 0x8000)
#define ETH_MAC_BASE          (ETH_BASE)
#define ETH_MMC_BASE          (ETH_BASE + 0x0100)
#define ETH_PTP_BASE          (ETH_BASE + 0x0700)
#define ETH_DMA_BASE          (ETH_BASE + 0x1000)
#define DMA2D_BASE            (AHB1PERIPH_BASE + 0xB000)

#define DCMI_BASE             (AHB2PERIPH_BASE + 0x50000)
#define CRYP_BASE             (AHB2PERIPH_BASE + 0x60000)
#define HASH_BASE             (AHB2PERIPH_BASE + 0x60400)
#define HASH_DIGEST_BASE      (AHB2PERIPH_BASE + 0x60710)
#define RNG_BASE              (AHB2PERIPH_BASE + 0x60800)

#if defined (STM32F40_41xxx)

#define FSMC_Bank1_R_BASE     (FSMC_R_BASE + 0x0000)
#define FSMC_Bank1E_R_BASE    (FSMC_R_BASE + 0x0104)
#define FSMC_Bank2_R_BASE     (FSMC_R_BASE + 0x0060)
#define FSMC_Bank3_R_BASE     (FSMC_R_BASE + 0x0080)
#define FSMC_Bank4_R_BASE     (FSMC_R_BASE + 0x00A0)
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)

#define FMC_Bank1_R_BASE      (FMC_R_BASE + 0x0000)
#define FMC_Bank1E_R_BASE     (FMC_R_BASE + 0x0104)
#define FMC_Bank2_R_BASE      (FMC_R_BASE + 0x0060)
#define FMC_Bank3_R_BASE      (FMC_R_BASE + 0x0080)
#define FMC_Bank4_R_BASE      (FMC_R_BASE + 0x00A0)
#define FMC_Bank5_6_R_BASE    (FMC_R_BASE + 0x0140)
#endif 

#define DBGMCU_BASE           ((uint32_t )0xE0042000)

  

  
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM12               ((TIM_TypeDef *) TIM12_BASE)
#define TIM13               ((TIM_TypeDef *) TIM13_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define I2S2ext             ((SPI_TypeDef *) I2S2ext_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define I2S3ext             ((SPI_TypeDef *) I2S3ext_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define I2C3                ((I2C_TypeDef *) I2C3_BASE)
#define CAN1                ((CAN_TypeDef *) CAN1_BASE)
#define CAN2                ((CAN_TypeDef *) CAN2_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)
#define UART7               ((USART_TypeDef *) UART7_BASE)
#define UART8               ((USART_TypeDef *) UART8_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART6              ((USART_TypeDef *) USART6_BASE)
#define ADC                 ((ADC_Common_TypeDef *) ADC_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define ADC3                ((ADC_TypeDef *) ADC3_BASE)
#define SDIO                ((SDIO_TypeDef *) SDIO_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE) 
#define SPI4                ((SPI_TypeDef *) SPI4_BASE)
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define TIM9                ((TIM_TypeDef *) TIM9_BASE)
#define TIM10               ((TIM_TypeDef *) TIM10_BASE)
#define TIM11               ((TIM_TypeDef *) TIM11_BASE)
#define SPI5                ((SPI_TypeDef *) SPI5_BASE)
#define SPI6                ((SPI_TypeDef *) SPI6_BASE)
#define SAI1                ((SAI_TypeDef *) SAI1_BASE)
#define SAI1_Block_A        ((SAI_Block_TypeDef *)SAI1_Block_A_BASE)
#define SAI1_Block_B        ((SAI_Block_TypeDef *)SAI1_Block_B_BASE)
#define LTDC                ((LTDC_TypeDef *)LTDC_BASE)
#define LTDC_Layer1         ((LTDC_Layer_TypeDef *)LTDC_Layer1_BASE)
#define LTDC_Layer2         ((LTDC_Layer_TypeDef *)LTDC_Layer2_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ               ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK               ((GPIO_TypeDef *) GPIOK_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Stream0        ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
#define DMA1_Stream1        ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
#define DMA1_Stream2        ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
#define DMA1_Stream3        ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
#define DMA1_Stream4        ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
#define DMA1_Stream5        ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
#define DMA1_Stream6        ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
#define DMA1_Stream7        ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)
#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Stream0        ((DMA_Stream_TypeDef *) DMA2_Stream0_BASE)
#define DMA2_Stream1        ((DMA_Stream_TypeDef *) DMA2_Stream1_BASE)
#define DMA2_Stream2        ((DMA_Stream_TypeDef *) DMA2_Stream2_BASE)
#define DMA2_Stream3        ((DMA_Stream_TypeDef *) DMA2_Stream3_BASE)
#define DMA2_Stream4        ((DMA_Stream_TypeDef *) DMA2_Stream4_BASE)
#define DMA2_Stream5        ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE)
#define DMA2_Stream6        ((DMA_Stream_TypeDef *) DMA2_Stream6_BASE)
#define DMA2_Stream7        ((DMA_Stream_TypeDef *) DMA2_Stream7_BASE)
#define ETH                 ((ETH_TypeDef *) ETH_BASE)  
#define DMA2D               ((DMA2D_TypeDef *)DMA2D_BASE)
#define DCMI                ((DCMI_TypeDef *) DCMI_BASE)
#define CRYP                ((CRYP_TypeDef *) CRYP_BASE)
#define HASH                ((HASH_TypeDef *) HASH_BASE)
#define HASH_DIGEST         ((HASH_DIGEST_TypeDef *) HASH_DIGEST_BASE)
#define RNG                 ((RNG_TypeDef *) RNG_BASE)

#if defined (STM32F40_41xxx)
#define FSMC_Bank1          ((FSMC_Bank1_TypeDef *) FSMC_Bank1_R_BASE)
#define FSMC_Bank1E         ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)
#define FSMC_Bank2          ((FSMC_Bank2_TypeDef *) FSMC_Bank2_R_BASE)
#define FSMC_Bank3          ((FSMC_Bank3_TypeDef *) FSMC_Bank3_R_BASE)
#define FSMC_Bank4          ((FSMC_Bank4_TypeDef *) FSMC_Bank4_R_BASE)
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define FMC_Bank1           ((FMC_Bank1_TypeDef *) FMC_Bank1_R_BASE)
#define FMC_Bank1E          ((FMC_Bank1E_TypeDef *) FMC_Bank1E_R_BASE)
#define FMC_Bank2           ((FMC_Bank2_TypeDef *) FMC_Bank2_R_BASE)
#define FMC_Bank3           ((FMC_Bank3_TypeDef *) FMC_Bank3_R_BASE)
#define FMC_Bank4           ((FMC_Bank4_TypeDef *) FMC_Bank4_R_BASE)
#define FMC_Bank5_6         ((FMC_Bank5_6_TypeDef *) FMC_Bank5_6_R_BASE)
#endif 

#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)

  
  

    

#define  ADC_SR_AWD                          ((uint8_t)0x01)               
#define  ADC_SR_EOC                          ((uint8_t)0x02)               
#define  ADC_SR_JEOC                         ((uint8_t)0x04)               
#define  ADC_SR_JSTRT                        ((uint8_t)0x08)               
#define  ADC_SR_STRT                         ((uint8_t)0x10)               
#define  ADC_SR_OVR                          ((uint8_t)0x20)               

#define  ADC_CR1_AWDCH                       ((uint32_t)0x0000001F)        
#define  ADC_CR1_AWDCH_0                     ((uint32_t)0x00000001)        
#define  ADC_CR1_AWDCH_1                     ((uint32_t)0x00000002)        
#define  ADC_CR1_AWDCH_2                     ((uint32_t)0x00000004)        
#define  ADC_CR1_AWDCH_3                     ((uint32_t)0x00000008)        
#define  ADC_CR1_AWDCH_4                     ((uint32_t)0x00000010)        
#define  ADC_CR1_EOCIE                       ((uint32_t)0x00000020)        
#define  ADC_CR1_AWDIE                       ((uint32_t)0x00000040)        
#define  ADC_CR1_JEOCIE                      ((uint32_t)0x00000080)        
#define  ADC_CR1_SCAN                        ((uint32_t)0x00000100)        
#define  ADC_CR1_AWDSGL                      ((uint32_t)0x00000200)        
#define  ADC_CR1_JAUTO                       ((uint32_t)0x00000400)        
#define  ADC_CR1_DISCEN                      ((uint32_t)0x00000800)        
#define  ADC_CR1_JDISCEN                     ((uint32_t)0x00001000)        
#define  ADC_CR1_DISCNUM                     ((uint32_t)0x0000E000)        
#define  ADC_CR1_DISCNUM_0                   ((uint32_t)0x00002000)        
#define  ADC_CR1_DISCNUM_1                   ((uint32_t)0x00004000)        
#define  ADC_CR1_DISCNUM_2                   ((uint32_t)0x00008000)        
#define  ADC_CR1_JAWDEN                      ((uint32_t)0x00400000)        
#define  ADC_CR1_AWDEN                       ((uint32_t)0x00800000)        
#define  ADC_CR1_RES                         ((uint32_t)0x03000000)        
#define  ADC_CR1_RES_0                       ((uint32_t)0x01000000)        
#define  ADC_CR1_RES_1                       ((uint32_t)0x02000000)        
#define  ADC_CR1_OVRIE                       ((uint32_t)0x04000000)         
  

#define  ADC_CR2_ADON                        ((uint32_t)0x00000001)        
#define  ADC_CR2_CONT                        ((uint32_t)0x00000002)        
#define  ADC_CR2_DMA                         ((uint32_t)0x00000100)        
#define  ADC_CR2_DDS                         ((uint32_t)0x00000200)        
#define  ADC_CR2_EOCS                        ((uint32_t)0x00000400)        
#define  ADC_CR2_ALIGN                       ((uint32_t)0x00000800)        
#define  ADC_CR2_JEXTSEL                     ((uint32_t)0x000F0000)        
#define  ADC_CR2_JEXTSEL_0                   ((uint32_t)0x00010000)        
#define  ADC_CR2_JEXTSEL_1                   ((uint32_t)0x00020000)        
#define  ADC_CR2_JEXTSEL_2                   ((uint32_t)0x00040000)        
#define  ADC_CR2_JEXTSEL_3                   ((uint32_t)0x00080000)        
#define  ADC_CR2_JEXTEN                      ((uint32_t)0x00300000)        
#define  ADC_CR2_JEXTEN_0                    ((uint32_t)0x00100000)        
#define  ADC_CR2_JEXTEN_1                    ((uint32_t)0x00200000)        
#define  ADC_CR2_JSWSTART                    ((uint32_t)0x00400000)        
#define  ADC_CR2_EXTSEL                      ((uint32_t)0x0F000000)        
#define  ADC_CR2_EXTSEL_0                    ((uint32_t)0x01000000)        
#define  ADC_CR2_EXTSEL_1                    ((uint32_t)0x02000000)        
#define  ADC_CR2_EXTSEL_2                    ((uint32_t)0x04000000)        
#define  ADC_CR2_EXTSEL_3                    ((uint32_t)0x08000000)        
#define  ADC_CR2_EXTEN                       ((uint32_t)0x30000000)        
#define  ADC_CR2_EXTEN_0                     ((uint32_t)0x10000000)        
#define  ADC_CR2_EXTEN_1                     ((uint32_t)0x20000000)        
#define  ADC_CR2_SWSTART                     ((uint32_t)0x40000000)        

#define  ADC_SMPR1_SMP10                     ((uint32_t)0x00000007)        
#define  ADC_SMPR1_SMP10_0                   ((uint32_t)0x00000001)        
#define  ADC_SMPR1_SMP10_1                   ((uint32_t)0x00000002)        
#define  ADC_SMPR1_SMP10_2                   ((uint32_t)0x00000004)        
#define  ADC_SMPR1_SMP11                     ((uint32_t)0x00000038)        
#define  ADC_SMPR1_SMP11_0                   ((uint32_t)0x00000008)        
#define  ADC_SMPR1_SMP11_1                   ((uint32_t)0x00000010)        
#define  ADC_SMPR1_SMP11_2                   ((uint32_t)0x00000020)        
#define  ADC_SMPR1_SMP12                     ((uint32_t)0x000001C0)        
#define  ADC_SMPR1_SMP12_0                   ((uint32_t)0x00000040)        
#define  ADC_SMPR1_SMP12_1                   ((uint32_t)0x00000080)        
#define  ADC_SMPR1_SMP12_2                   ((uint32_t)0x00000100)        
#define  ADC_SMPR1_SMP13                     ((uint32_t)0x00000E00)        
#define  ADC_SMPR1_SMP13_0                   ((uint32_t)0x00000200)        
#define  ADC_SMPR1_SMP13_1                   ((uint32_t)0x00000400)        
#define  ADC_SMPR1_SMP13_2                   ((uint32_t)0x00000800)        
#define  ADC_SMPR1_SMP14                     ((uint32_t)0x00007000)        
#define  ADC_SMPR1_SMP14_0                   ((uint32_t)0x00001000)        
#define  ADC_SMPR1_SMP14_1                   ((uint32_t)0x00002000)        
#define  ADC_SMPR1_SMP14_2                   ((uint32_t)0x00004000)        
#define  ADC_SMPR1_SMP15                     ((uint32_t)0x00038000)        
#define  ADC_SMPR1_SMP15_0                   ((uint32_t)0x00008000)        
#define  ADC_SMPR1_SMP15_1                   ((uint32_t)0x00010000)        
#define  ADC_SMPR1_SMP15_2                   ((uint32_t)0x00020000)        
#define  ADC_SMPR1_SMP16                     ((uint32_t)0x001C0000)        
#define  ADC_SMPR1_SMP16_0                   ((uint32_t)0x00040000)        
#define  ADC_SMPR1_SMP16_1                   ((uint32_t)0x00080000)        
#define  ADC_SMPR1_SMP16_2                   ((uint32_t)0x00100000)        
#define  ADC_SMPR1_SMP17                     ((uint32_t)0x00E00000)        
#define  ADC_SMPR1_SMP17_0                   ((uint32_t)0x00200000)        
#define  ADC_SMPR1_SMP17_1                   ((uint32_t)0x00400000)        
#define  ADC_SMPR1_SMP17_2                   ((uint32_t)0x00800000)        
#define  ADC_SMPR1_SMP18                     ((uint32_t)0x07000000)        
#define  ADC_SMPR1_SMP18_0                   ((uint32_t)0x01000000)        
#define  ADC_SMPR1_SMP18_1                   ((uint32_t)0x02000000)        
#define  ADC_SMPR1_SMP18_2                   ((uint32_t)0x04000000)        

#define  ADC_SMPR2_SMP0                      ((uint32_t)0x00000007)        
#define  ADC_SMPR2_SMP0_0                    ((uint32_t)0x00000001)        
#define  ADC_SMPR2_SMP0_1                    ((uint32_t)0x00000002)        
#define  ADC_SMPR2_SMP0_2                    ((uint32_t)0x00000004)        
#define  ADC_SMPR2_SMP1                      ((uint32_t)0x00000038)        
#define  ADC_SMPR2_SMP1_0                    ((uint32_t)0x00000008)        
#define  ADC_SMPR2_SMP1_1                    ((uint32_t)0x00000010)        
#define  ADC_SMPR2_SMP1_2                    ((uint32_t)0x00000020)        
#define  ADC_SMPR2_SMP2                      ((uint32_t)0x000001C0)        
#define  ADC_SMPR2_SMP2_0                    ((uint32_t)0x00000040)        
#define  ADC_SMPR2_SMP2_1                    ((uint32_t)0x00000080)        
#define  ADC_SMPR2_SMP2_2                    ((uint32_t)0x00000100)        
#define  ADC_SMPR2_SMP3                      ((uint32_t)0x00000E00)        
#define  ADC_SMPR2_SMP3_0                    ((uint32_t)0x00000200)        
#define  ADC_SMPR2_SMP3_1                    ((uint32_t)0x00000400)        
#define  ADC_SMPR2_SMP3_2                    ((uint32_t)0x00000800)        
#define  ADC_SMPR2_SMP4                      ((uint32_t)0x00007000)        
#define  ADC_SMPR2_SMP4_0                    ((uint32_t)0x00001000)        
#define  ADC_SMPR2_SMP4_1                    ((uint32_t)0x00002000)        
#define  ADC_SMPR2_SMP4_2                    ((uint32_t)0x00004000)        
#define  ADC_SMPR2_SMP5                      ((uint32_t)0x00038000)        
#define  ADC_SMPR2_SMP5_0                    ((uint32_t)0x00008000)        
#define  ADC_SMPR2_SMP5_1                    ((uint32_t)0x00010000)        
#define  ADC_SMPR2_SMP5_2                    ((uint32_t)0x00020000)        
#define  ADC_SMPR2_SMP6                      ((uint32_t)0x001C0000)        
#define  ADC_SMPR2_SMP6_0                    ((uint32_t)0x00040000)        
#define  ADC_SMPR2_SMP6_1                    ((uint32_t)0x00080000)        
#define  ADC_SMPR2_SMP6_2                    ((uint32_t)0x00100000)        
#define  ADC_SMPR2_SMP7                      ((uint32_t)0x00E00000)        
#define  ADC_SMPR2_SMP7_0                    ((uint32_t)0x00200000)        
#define  ADC_SMPR2_SMP7_1                    ((uint32_t)0x00400000)        
#define  ADC_SMPR2_SMP7_2                    ((uint32_t)0x00800000)        
#define  ADC_SMPR2_SMP8                      ((uint32_t)0x07000000)        
#define  ADC_SMPR2_SMP8_0                    ((uint32_t)0x01000000)        
#define  ADC_SMPR2_SMP8_1                    ((uint32_t)0x02000000)        
#define  ADC_SMPR2_SMP8_2                    ((uint32_t)0x04000000)        
#define  ADC_SMPR2_SMP9                      ((uint32_t)0x38000000)        
#define  ADC_SMPR2_SMP9_0                    ((uint32_t)0x08000000)        
#define  ADC_SMPR2_SMP9_1                    ((uint32_t)0x10000000)        
#define  ADC_SMPR2_SMP9_2                    ((uint32_t)0x20000000)        

#define  ADC_JOFR1_JOFFSET1                  ((uint16_t)0x0FFF)            

#define  ADC_JOFR2_JOFFSET2                  ((uint16_t)0x0FFF)            

#define  ADC_JOFR3_JOFFSET3                  ((uint16_t)0x0FFF)            

#define  ADC_JOFR4_JOFFSET4                  ((uint16_t)0x0FFF)            

#define  ADC_HTR_HT                          ((uint16_t)0x0FFF)            

#define  ADC_LTR_LT                          ((uint16_t)0x0FFF)            

#define  ADC_SQR1_SQ13                       ((uint32_t)0x0000001F)        
#define  ADC_SQR1_SQ13_0                     ((uint32_t)0x00000001)        
#define  ADC_SQR1_SQ13_1                     ((uint32_t)0x00000002)        
#define  ADC_SQR1_SQ13_2                     ((uint32_t)0x00000004)        
#define  ADC_SQR1_SQ13_3                     ((uint32_t)0x00000008)        
#define  ADC_SQR1_SQ13_4                     ((uint32_t)0x00000010)        
#define  ADC_SQR1_SQ14                       ((uint32_t)0x000003E0)        
#define  ADC_SQR1_SQ14_0                     ((uint32_t)0x00000020)        
#define  ADC_SQR1_SQ14_1                     ((uint32_t)0x00000040)        
#define  ADC_SQR1_SQ14_2                     ((uint32_t)0x00000080)        
#define  ADC_SQR1_SQ14_3                     ((uint32_t)0x00000100)        
#define  ADC_SQR1_SQ14_4                     ((uint32_t)0x00000200)        
#define  ADC_SQR1_SQ15                       ((uint32_t)0x00007C00)        
#define  ADC_SQR1_SQ15_0                     ((uint32_t)0x00000400)        
#define  ADC_SQR1_SQ15_1                     ((uint32_t)0x00000800)        
#define  ADC_SQR1_SQ15_2                     ((uint32_t)0x00001000)        
#define  ADC_SQR1_SQ15_3                     ((uint32_t)0x00002000)        
#define  ADC_SQR1_SQ15_4                     ((uint32_t)0x00004000)        
#define  ADC_SQR1_SQ16                       ((uint32_t)0x000F8000)        
#define  ADC_SQR1_SQ16_0                     ((uint32_t)0x00008000)        
#define  ADC_SQR1_SQ16_1                     ((uint32_t)0x00010000)        
#define  ADC_SQR1_SQ16_2                     ((uint32_t)0x00020000)        
#define  ADC_SQR1_SQ16_3                     ((uint32_t)0x00040000)        
#define  ADC_SQR1_SQ16_4                     ((uint32_t)0x00080000)        
#define  ADC_SQR1_L                          ((uint32_t)0x00F00000)        
#define  ADC_SQR1_L_0                        ((uint32_t)0x00100000)        
#define  ADC_SQR1_L_1                        ((uint32_t)0x00200000)        
#define  ADC_SQR1_L_2                        ((uint32_t)0x00400000)        
#define  ADC_SQR1_L_3                        ((uint32_t)0x00800000)        

#define  ADC_SQR2_SQ7                        ((uint32_t)0x0000001F)        
#define  ADC_SQR2_SQ7_0                      ((uint32_t)0x00000001)        
#define  ADC_SQR2_SQ7_1                      ((uint32_t)0x00000002)        
#define  ADC_SQR2_SQ7_2                      ((uint32_t)0x00000004)        
#define  ADC_SQR2_SQ7_3                      ((uint32_t)0x00000008)        
#define  ADC_SQR2_SQ7_4                      ((uint32_t)0x00000010)        
#define  ADC_SQR2_SQ8                        ((uint32_t)0x000003E0)        
#define  ADC_SQR2_SQ8_0                      ((uint32_t)0x00000020)        
#define  ADC_SQR2_SQ8_1                      ((uint32_t)0x00000040)        
#define  ADC_SQR2_SQ8_2                      ((uint32_t)0x00000080)        
#define  ADC_SQR2_SQ8_3                      ((uint32_t)0x00000100)        
#define  ADC_SQR2_SQ8_4                      ((uint32_t)0x00000200)        
#define  ADC_SQR2_SQ9                        ((uint32_t)0x00007C00)        
#define  ADC_SQR2_SQ9_0                      ((uint32_t)0x00000400)        
#define  ADC_SQR2_SQ9_1                      ((uint32_t)0x00000800)        
#define  ADC_SQR2_SQ9_2                      ((uint32_t)0x00001000)        
#define  ADC_SQR2_SQ9_3                      ((uint32_t)0x00002000)        
#define  ADC_SQR2_SQ9_4                      ((uint32_t)0x00004000)        
#define  ADC_SQR2_SQ10                       ((uint32_t)0x000F8000)        
#define  ADC_SQR2_SQ10_0                     ((uint32_t)0x00008000)        
#define  ADC_SQR2_SQ10_1                     ((uint32_t)0x00010000)        
#define  ADC_SQR2_SQ10_2                     ((uint32_t)0x00020000)        
#define  ADC_SQR2_SQ10_3                     ((uint32_t)0x00040000)        
#define  ADC_SQR2_SQ10_4                     ((uint32_t)0x00080000)        
#define  ADC_SQR2_SQ11                       ((uint32_t)0x01F00000)        
#define  ADC_SQR2_SQ11_0                     ((uint32_t)0x00100000)        
#define  ADC_SQR2_SQ11_1                     ((uint32_t)0x00200000)        
#define  ADC_SQR2_SQ11_2                     ((uint32_t)0x00400000)        
#define  ADC_SQR2_SQ11_3                     ((uint32_t)0x00800000)        
#define  ADC_SQR2_SQ11_4                     ((uint32_t)0x01000000)        
#define  ADC_SQR2_SQ12                       ((uint32_t)0x3E000000)        
#define  ADC_SQR2_SQ12_0                     ((uint32_t)0x02000000)        
#define  ADC_SQR2_SQ12_1                     ((uint32_t)0x04000000)        
#define  ADC_SQR2_SQ12_2                     ((uint32_t)0x08000000)        
#define  ADC_SQR2_SQ12_3                     ((uint32_t)0x10000000)        
#define  ADC_SQR2_SQ12_4                     ((uint32_t)0x20000000)        

#define  ADC_SQR3_SQ1                        ((uint32_t)0x0000001F)        
#define  ADC_SQR3_SQ1_0                      ((uint32_t)0x00000001)        
#define  ADC_SQR3_SQ1_1                      ((uint32_t)0x00000002)        
#define  ADC_SQR3_SQ1_2                      ((uint32_t)0x00000004)        
#define  ADC_SQR3_SQ1_3                      ((uint32_t)0x00000008)        
#define  ADC_SQR3_SQ1_4                      ((uint32_t)0x00000010)        
#define  ADC_SQR3_SQ2                        ((uint32_t)0x000003E0)        
#define  ADC_SQR3_SQ2_0                      ((uint32_t)0x00000020)        
#define  ADC_SQR3_SQ2_1                      ((uint32_t)0x00000040)        
#define  ADC_SQR3_SQ2_2                      ((uint32_t)0x00000080)        
#define  ADC_SQR3_SQ2_3                      ((uint32_t)0x00000100)        
#define  ADC_SQR3_SQ2_4                      ((uint32_t)0x00000200)        
#define  ADC_SQR3_SQ3                        ((uint32_t)0x00007C00)        
#define  ADC_SQR3_SQ3_0                      ((uint32_t)0x00000400)        
#define  ADC_SQR3_SQ3_1                      ((uint32_t)0x00000800)        
#define  ADC_SQR3_SQ3_2                      ((uint32_t)0x00001000)        
#define  ADC_SQR3_SQ3_3                      ((uint32_t)0x00002000)        
#define  ADC_SQR3_SQ3_4                      ((uint32_t)0x00004000)        
#define  ADC_SQR3_SQ4                        ((uint32_t)0x000F8000)        
#define  ADC_SQR3_SQ4_0                      ((uint32_t)0x00008000)        
#define  ADC_SQR3_SQ4_1                      ((uint32_t)0x00010000)        
#define  ADC_SQR3_SQ4_2                      ((uint32_t)0x00020000)        
#define  ADC_SQR3_SQ4_3                      ((uint32_t)0x00040000)        
#define  ADC_SQR3_SQ4_4                      ((uint32_t)0x00080000)        
#define  ADC_SQR3_SQ5                        ((uint32_t)0x01F00000)        
#define  ADC_SQR3_SQ5_0                      ((uint32_t)0x00100000)        
#define  ADC_SQR3_SQ5_1                      ((uint32_t)0x00200000)        
#define  ADC_SQR3_SQ5_2                      ((uint32_t)0x00400000)        
#define  ADC_SQR3_SQ5_3                      ((uint32_t)0x00800000)        
#define  ADC_SQR3_SQ5_4                      ((uint32_t)0x01000000)        
#define  ADC_SQR3_SQ6                        ((uint32_t)0x3E000000)        
#define  ADC_SQR3_SQ6_0                      ((uint32_t)0x02000000)        
#define  ADC_SQR3_SQ6_1                      ((uint32_t)0x04000000)        
#define  ADC_SQR3_SQ6_2                      ((uint32_t)0x08000000)        
#define  ADC_SQR3_SQ6_3                      ((uint32_t)0x10000000)        
#define  ADC_SQR3_SQ6_4                      ((uint32_t)0x20000000)        

#define  ADC_JSQR_JSQ1                       ((uint32_t)0x0000001F)          
#define  ADC_JSQR_JSQ1_0                     ((uint32_t)0x00000001)        
#define  ADC_JSQR_JSQ1_1                     ((uint32_t)0x00000002)        
#define  ADC_JSQR_JSQ1_2                     ((uint32_t)0x00000004)        
#define  ADC_JSQR_JSQ1_3                     ((uint32_t)0x00000008)        
#define  ADC_JSQR_JSQ1_4                     ((uint32_t)0x00000010)        
#define  ADC_JSQR_JSQ2                       ((uint32_t)0x000003E0)        
#define  ADC_JSQR_JSQ2_0                     ((uint32_t)0x00000020)        
#define  ADC_JSQR_JSQ2_1                     ((uint32_t)0x00000040)        
#define  ADC_JSQR_JSQ2_2                     ((uint32_t)0x00000080)        
#define  ADC_JSQR_JSQ2_3                     ((uint32_t)0x00000100)        
#define  ADC_JSQR_JSQ2_4                     ((uint32_t)0x00000200)        
#define  ADC_JSQR_JSQ3                       ((uint32_t)0x00007C00)        
#define  ADC_JSQR_JSQ3_0                     ((uint32_t)0x00000400)        
#define  ADC_JSQR_JSQ3_1                     ((uint32_t)0x00000800)        
#define  ADC_JSQR_JSQ3_2                     ((uint32_t)0x00001000)        
#define  ADC_JSQR_JSQ3_3                     ((uint32_t)0x00002000)        
#define  ADC_JSQR_JSQ3_4                     ((uint32_t)0x00004000)        
#define  ADC_JSQR_JSQ4                       ((uint32_t)0x000F8000)        
#define  ADC_JSQR_JSQ4_0                     ((uint32_t)0x00008000)        
#define  ADC_JSQR_JSQ4_1                     ((uint32_t)0x00010000)        
#define  ADC_JSQR_JSQ4_2                     ((uint32_t)0x00020000)        
#define  ADC_JSQR_JSQ4_3                     ((uint32_t)0x00040000)        
#define  ADC_JSQR_JSQ4_4                     ((uint32_t)0x00080000)        
#define  ADC_JSQR_JL                         ((uint32_t)0x00300000)        
#define  ADC_JSQR_JL_0                       ((uint32_t)0x00100000)        
#define  ADC_JSQR_JL_1                       ((uint32_t)0x00200000)        

#define  ADC_JDR1_JDATA                      ((uint16_t)0xFFFF)            

#define  ADC_JDR2_JDATA                      ((uint16_t)0xFFFF)            

#define  ADC_JDR3_JDATA                      ((uint16_t)0xFFFF)            

#define  ADC_JDR4_JDATA                      ((uint16_t)0xFFFF)            

#define  ADC_DR_DATA                         ((uint32_t)0x0000FFFF)        
#define  ADC_DR_ADC2DATA                     ((uint32_t)0xFFFF0000)        

#define  ADC_CSR_AWD1                        ((uint32_t)0x00000001)        
#define  ADC_CSR_EOC1                        ((uint32_t)0x00000002)        
#define  ADC_CSR_JEOC1                       ((uint32_t)0x00000004)        
#define  ADC_CSR_JSTRT1                      ((uint32_t)0x00000008)        
#define  ADC_CSR_STRT1                       ((uint32_t)0x00000010)        
#define  ADC_CSR_DOVR1                       ((uint32_t)0x00000020)        
#define  ADC_CSR_AWD2                        ((uint32_t)0x00000100)        
#define  ADC_CSR_EOC2                        ((uint32_t)0x00000200)        
#define  ADC_CSR_JEOC2                       ((uint32_t)0x00000400)        
#define  ADC_CSR_JSTRT2                      ((uint32_t)0x00000800)        
#define  ADC_CSR_STRT2                       ((uint32_t)0x00001000)        
#define  ADC_CSR_DOVR2                       ((uint32_t)0x00002000)        
#define  ADC_CSR_AWD3                        ((uint32_t)0x00010000)        
#define  ADC_CSR_EOC3                        ((uint32_t)0x00020000)        
#define  ADC_CSR_JEOC3                       ((uint32_t)0x00040000)        
#define  ADC_CSR_JSTRT3                      ((uint32_t)0x00080000)        
#define  ADC_CSR_STRT3                       ((uint32_t)0x00100000)        
#define  ADC_CSR_DOVR3                       ((uint32_t)0x00200000)        

#define  ADC_CCR_MULTI                       ((uint32_t)0x0000001F)          
#define  ADC_CCR_MULTI_0                     ((uint32_t)0x00000001)        
#define  ADC_CCR_MULTI_1                     ((uint32_t)0x00000002)        
#define  ADC_CCR_MULTI_2                     ((uint32_t)0x00000004)        
#define  ADC_CCR_MULTI_3                     ((uint32_t)0x00000008)        
#define  ADC_CCR_MULTI_4                     ((uint32_t)0x00000010)        
#define  ADC_CCR_DELAY                       ((uint32_t)0x00000F00)          
#define  ADC_CCR_DELAY_0                     ((uint32_t)0x00000100)        
#define  ADC_CCR_DELAY_1                     ((uint32_t)0x00000200)        
#define  ADC_CCR_DELAY_2                     ((uint32_t)0x00000400)        
#define  ADC_CCR_DELAY_3                     ((uint32_t)0x00000800)        
#define  ADC_CCR_DDS                         ((uint32_t)0x00002000)        
#define  ADC_CCR_DMA                         ((uint32_t)0x0000C000)          
#define  ADC_CCR_DMA_0                       ((uint32_t)0x00004000)        
#define  ADC_CCR_DMA_1                       ((uint32_t)0x00008000)        
#define  ADC_CCR_ADCPRE                      ((uint32_t)0x00030000)          
#define  ADC_CCR_ADCPRE_0                    ((uint32_t)0x00010000)        
#define  ADC_CCR_ADCPRE_1                    ((uint32_t)0x00020000)        
#define  ADC_CCR_VBATE                       ((uint32_t)0x00400000)        
#define  ADC_CCR_TSVREFE                     ((uint32_t)0x00800000)        

#define  ADC_CDR_DATA1                      ((uint32_t)0x0000FFFF)         
#define  ADC_CDR_DATA2                      ((uint32_t)0xFFFF0000)         

#define  CAN_MCR_INRQ                        ((uint16_t)0x0001)            
#define  CAN_MCR_SLEEP                       ((uint16_t)0x0002)            
#define  CAN_MCR_TXFP                        ((uint16_t)0x0004)            
#define  CAN_MCR_RFLM                        ((uint16_t)0x0008)            
#define  CAN_MCR_NART                        ((uint16_t)0x0010)            
#define  CAN_MCR_AWUM                        ((uint16_t)0x0020)            
#define  CAN_MCR_ABOM                        ((uint16_t)0x0040)            
#define  CAN_MCR_TTCM                        ((uint16_t)0x0080)            
#define  CAN_MCR_RESET                       ((uint16_t)0x8000)            

#define  CAN_MSR_INAK                        ((uint16_t)0x0001)            
#define  CAN_MSR_SLAK                        ((uint16_t)0x0002)            
#define  CAN_MSR_ERRI                        ((uint16_t)0x0004)            
#define  CAN_MSR_WKUI                        ((uint16_t)0x0008)            
#define  CAN_MSR_SLAKI                       ((uint16_t)0x0010)            
#define  CAN_MSR_TXM                         ((uint16_t)0x0100)            
#define  CAN_MSR_RXM                         ((uint16_t)0x0200)            
#define  CAN_MSR_SAMP                        ((uint16_t)0x0400)            
#define  CAN_MSR_RX                          ((uint16_t)0x0800)            

#define  CAN_TSR_RQCP0                       ((uint32_t)0x00000001)        
#define  CAN_TSR_TXOK0                       ((uint32_t)0x00000002)        
#define  CAN_TSR_ALST0                       ((uint32_t)0x00000004)        
#define  CAN_TSR_TERR0                       ((uint32_t)0x00000008)        
#define  CAN_TSR_ABRQ0                       ((uint32_t)0x00000080)        
#define  CAN_TSR_RQCP1                       ((uint32_t)0x00000100)        
#define  CAN_TSR_TXOK1                       ((uint32_t)0x00000200)        
#define  CAN_TSR_ALST1                       ((uint32_t)0x00000400)        
#define  CAN_TSR_TERR1                       ((uint32_t)0x00000800)        
#define  CAN_TSR_ABRQ1                       ((uint32_t)0x00008000)        
#define  CAN_TSR_RQCP2                       ((uint32_t)0x00010000)        
#define  CAN_TSR_TXOK2                       ((uint32_t)0x00020000)        
#define  CAN_TSR_ALST2                       ((uint32_t)0x00040000)        
#define  CAN_TSR_TERR2                       ((uint32_t)0x00080000)        
#define  CAN_TSR_ABRQ2                       ((uint32_t)0x00800000)        
#define  CAN_TSR_CODE                        ((uint32_t)0x03000000)        

#define  CAN_TSR_TME                         ((uint32_t)0x1C000000)        
#define  CAN_TSR_TME0                        ((uint32_t)0x04000000)        
#define  CAN_TSR_TME1                        ((uint32_t)0x08000000)        
#define  CAN_TSR_TME2                        ((uint32_t)0x10000000)        

#define  CAN_TSR_LOW                         ((uint32_t)0xE0000000)        
#define  CAN_TSR_LOW0                        ((uint32_t)0x20000000)        
#define  CAN_TSR_LOW1                        ((uint32_t)0x40000000)        
#define  CAN_TSR_LOW2                        ((uint32_t)0x80000000)        

#define  CAN_RF0R_FMP0                       ((uint8_t)0x03)               
#define  CAN_RF0R_FULL0                      ((uint8_t)0x08)               
#define  CAN_RF0R_FOVR0                      ((uint8_t)0x10)               
#define  CAN_RF0R_RFOM0                      ((uint8_t)0x20)               

#define  CAN_RF1R_FMP1                       ((uint8_t)0x03)               
#define  CAN_RF1R_FULL1                      ((uint8_t)0x08)               
#define  CAN_RF1R_FOVR1                      ((uint8_t)0x10)               
#define  CAN_RF1R_RFOM1                      ((uint8_t)0x20)               

#define  CAN_IER_TMEIE                       ((uint32_t)0x00000001)        
#define  CAN_IER_FMPIE0                      ((uint32_t)0x00000002)        
#define  CAN_IER_FFIE0                       ((uint32_t)0x00000004)        
#define  CAN_IER_FOVIE0                      ((uint32_t)0x00000008)        
#define  CAN_IER_FMPIE1                      ((uint32_t)0x00000010)        
#define  CAN_IER_FFIE1                       ((uint32_t)0x00000020)        
#define  CAN_IER_FOVIE1                      ((uint32_t)0x00000040)        
#define  CAN_IER_EWGIE                       ((uint32_t)0x00000100)        
#define  CAN_IER_EPVIE                       ((uint32_t)0x00000200)        
#define  CAN_IER_BOFIE                       ((uint32_t)0x00000400)        
#define  CAN_IER_LECIE                       ((uint32_t)0x00000800)        
#define  CAN_IER_ERRIE                       ((uint32_t)0x00008000)        
#define  CAN_IER_WKUIE                       ((uint32_t)0x00010000)        
#define  CAN_IER_SLKIE                       ((uint32_t)0x00020000)        

#define  CAN_ESR_EWGF                        ((uint32_t)0x00000001)        
#define  CAN_ESR_EPVF                        ((uint32_t)0x00000002)        
#define  CAN_ESR_BOFF                        ((uint32_t)0x00000004)        

#define  CAN_ESR_LEC                         ((uint32_t)0x00000070)        
#define  CAN_ESR_LEC_0                       ((uint32_t)0x00000010)        
#define  CAN_ESR_LEC_1                       ((uint32_t)0x00000020)        
#define  CAN_ESR_LEC_2                       ((uint32_t)0x00000040)        

#define  CAN_ESR_TEC                         ((uint32_t)0x00FF0000)        
#define  CAN_ESR_REC                         ((uint32_t)0xFF000000)        

#define  CAN_BTR_BRP                         ((uint32_t)0x000003FF)        
#define  CAN_BTR_TS1                         ((uint32_t)0x000F0000)        
#define  CAN_BTR_TS2                         ((uint32_t)0x00700000)        
#define  CAN_BTR_SJW                         ((uint32_t)0x03000000)        
#define  CAN_BTR_LBKM                        ((uint32_t)0x40000000)        
#define  CAN_BTR_SILM                        ((uint32_t)0x80000000)        

#define  CAN_TI0R_TXRQ                       ((uint32_t)0x00000001)        
#define  CAN_TI0R_RTR                        ((uint32_t)0x00000002)        
#define  CAN_TI0R_IDE                        ((uint32_t)0x00000004)        
#define  CAN_TI0R_EXID                       ((uint32_t)0x001FFFF8)        
#define  CAN_TI0R_STID                       ((uint32_t)0xFFE00000)        

#define  CAN_TDT0R_DLC                       ((uint32_t)0x0000000F)        
#define  CAN_TDT0R_TGT                       ((uint32_t)0x00000100)        
#define  CAN_TDT0R_TIME                      ((uint32_t)0xFFFF0000)        

#define  CAN_TDL0R_DATA0                     ((uint32_t)0x000000FF)        
#define  CAN_TDL0R_DATA1                     ((uint32_t)0x0000FF00)        
#define  CAN_TDL0R_DATA2                     ((uint32_t)0x00FF0000)        
#define  CAN_TDL0R_DATA3                     ((uint32_t)0xFF000000)        

#define  CAN_TDH0R_DATA4                     ((uint32_t)0x000000FF)        
#define  CAN_TDH0R_DATA5                     ((uint32_t)0x0000FF00)        
#define  CAN_TDH0R_DATA6                     ((uint32_t)0x00FF0000)        
#define  CAN_TDH0R_DATA7                     ((uint32_t)0xFF000000)        

#define  CAN_TI1R_TXRQ                       ((uint32_t)0x00000001)        
#define  CAN_TI1R_RTR                        ((uint32_t)0x00000002)        
#define  CAN_TI1R_IDE                        ((uint32_t)0x00000004)        
#define  CAN_TI1R_EXID                       ((uint32_t)0x001FFFF8)        
#define  CAN_TI1R_STID                       ((uint32_t)0xFFE00000)        

#define  CAN_TDT1R_DLC                       ((uint32_t)0x0000000F)        
#define  CAN_TDT1R_TGT                       ((uint32_t)0x00000100)        
#define  CAN_TDT1R_TIME                      ((uint32_t)0xFFFF0000)        

#define  CAN_TDL1R_DATA0                     ((uint32_t)0x000000FF)        
#define  CAN_TDL1R_DATA1                     ((uint32_t)0x0000FF00)        
#define  CAN_TDL1R_DATA2                     ((uint32_t)0x00FF0000)        
#define  CAN_TDL1R_DATA3                     ((uint32_t)0xFF000000)        

#define  CAN_TDH1R_DATA4                     ((uint32_t)0x000000FF)        
#define  CAN_TDH1R_DATA5                     ((uint32_t)0x0000FF00)        
#define  CAN_TDH1R_DATA6                     ((uint32_t)0x00FF0000)        
#define  CAN_TDH1R_DATA7                     ((uint32_t)0xFF000000)        

#define  CAN_TI2R_TXRQ                       ((uint32_t)0x00000001)        
#define  CAN_TI2R_RTR                        ((uint32_t)0x00000002)        
#define  CAN_TI2R_IDE                        ((uint32_t)0x00000004)        
#define  CAN_TI2R_EXID                       ((uint32_t)0x001FFFF8)        
#define  CAN_TI2R_STID                       ((uint32_t)0xFFE00000)        

  
#define  CAN_TDT2R_DLC                       ((uint32_t)0x0000000F)        
#define  CAN_TDT2R_TGT                       ((uint32_t)0x00000100)        
#define  CAN_TDT2R_TIME                      ((uint32_t)0xFFFF0000)        

#define  CAN_TDL2R_DATA0                     ((uint32_t)0x000000FF)        
#define  CAN_TDL2R_DATA1                     ((uint32_t)0x0000FF00)        
#define  CAN_TDL2R_DATA2                     ((uint32_t)0x00FF0000)        
#define  CAN_TDL2R_DATA3                     ((uint32_t)0xFF000000)        

#define  CAN_TDH2R_DATA4                     ((uint32_t)0x000000FF)        
#define  CAN_TDH2R_DATA5                     ((uint32_t)0x0000FF00)        
#define  CAN_TDH2R_DATA6                     ((uint32_t)0x00FF0000)        
#define  CAN_TDH2R_DATA7                     ((uint32_t)0xFF000000)        

#define  CAN_RI0R_RTR                        ((uint32_t)0x00000002)        
#define  CAN_RI0R_IDE                        ((uint32_t)0x00000004)        
#define  CAN_RI0R_EXID                       ((uint32_t)0x001FFFF8)        
#define  CAN_RI0R_STID                       ((uint32_t)0xFFE00000)        

#define  CAN_RDT0R_DLC                       ((uint32_t)0x0000000F)        
#define  CAN_RDT0R_FMI                       ((uint32_t)0x0000FF00)        
#define  CAN_RDT0R_TIME                      ((uint32_t)0xFFFF0000)        

#define  CAN_RDL0R_DATA0                     ((uint32_t)0x000000FF)        
#define  CAN_RDL0R_DATA1                     ((uint32_t)0x0000FF00)        
#define  CAN_RDL0R_DATA2                     ((uint32_t)0x00FF0000)        
#define  CAN_RDL0R_DATA3                     ((uint32_t)0xFF000000)        

#define  CAN_RDH0R_DATA4                     ((uint32_t)0x000000FF)        
#define  CAN_RDH0R_DATA5                     ((uint32_t)0x0000FF00)        
#define  CAN_RDH0R_DATA6                     ((uint32_t)0x00FF0000)        
#define  CAN_RDH0R_DATA7                     ((uint32_t)0xFF000000)        

#define  CAN_RI1R_RTR                        ((uint32_t)0x00000002)        
#define  CAN_RI1R_IDE                        ((uint32_t)0x00000004)        
#define  CAN_RI1R_EXID                       ((uint32_t)0x001FFFF8)        
#define  CAN_RI1R_STID                       ((uint32_t)0xFFE00000)        

#define  CAN_RDT1R_DLC                       ((uint32_t)0x0000000F)        
#define  CAN_RDT1R_FMI                       ((uint32_t)0x0000FF00)        
#define  CAN_RDT1R_TIME                      ((uint32_t)0xFFFF0000)        

#define  CAN_RDL1R_DATA0                     ((uint32_t)0x000000FF)        
#define  CAN_RDL1R_DATA1                     ((uint32_t)0x0000FF00)        
#define  CAN_RDL1R_DATA2                     ((uint32_t)0x00FF0000)        
#define  CAN_RDL1R_DATA3                     ((uint32_t)0xFF000000)        

#define  CAN_RDH1R_DATA4                     ((uint32_t)0x000000FF)        
#define  CAN_RDH1R_DATA5                     ((uint32_t)0x0000FF00)        
#define  CAN_RDH1R_DATA6                     ((uint32_t)0x00FF0000)        
#define  CAN_RDH1R_DATA7                     ((uint32_t)0xFF000000)        

#define  CAN_FMR_FINIT                       ((uint8_t)0x01)               

#define  CAN_FM1R_FBM                        ((uint16_t)0x3FFF)            
#define  CAN_FM1R_FBM0                       ((uint16_t)0x0001)            
#define  CAN_FM1R_FBM1                       ((uint16_t)0x0002)            
#define  CAN_FM1R_FBM2                       ((uint16_t)0x0004)            
#define  CAN_FM1R_FBM3                       ((uint16_t)0x0008)            
#define  CAN_FM1R_FBM4                       ((uint16_t)0x0010)            
#define  CAN_FM1R_FBM5                       ((uint16_t)0x0020)            
#define  CAN_FM1R_FBM6                       ((uint16_t)0x0040)            
#define  CAN_FM1R_FBM7                       ((uint16_t)0x0080)            
#define  CAN_FM1R_FBM8                       ((uint16_t)0x0100)            
#define  CAN_FM1R_FBM9                       ((uint16_t)0x0200)            
#define  CAN_FM1R_FBM10                      ((uint16_t)0x0400)            
#define  CAN_FM1R_FBM11                      ((uint16_t)0x0800)            
#define  CAN_FM1R_FBM12                      ((uint16_t)0x1000)            
#define  CAN_FM1R_FBM13                      ((uint16_t)0x2000)            

#define  CAN_FS1R_FSC                        ((uint16_t)0x3FFF)            
#define  CAN_FS1R_FSC0                       ((uint16_t)0x0001)            
#define  CAN_FS1R_FSC1                       ((uint16_t)0x0002)            
#define  CAN_FS1R_FSC2                       ((uint16_t)0x0004)            
#define  CAN_FS1R_FSC3                       ((uint16_t)0x0008)            
#define  CAN_FS1R_FSC4                       ((uint16_t)0x0010)            
#define  CAN_FS1R_FSC5                       ((uint16_t)0x0020)            
#define  CAN_FS1R_FSC6                       ((uint16_t)0x0040)            
#define  CAN_FS1R_FSC7                       ((uint16_t)0x0080)            
#define  CAN_FS1R_FSC8                       ((uint16_t)0x0100)            
#define  CAN_FS1R_FSC9                       ((uint16_t)0x0200)            
#define  CAN_FS1R_FSC10                      ((uint16_t)0x0400)            
#define  CAN_FS1R_FSC11                      ((uint16_t)0x0800)            
#define  CAN_FS1R_FSC12                      ((uint16_t)0x1000)            
#define  CAN_FS1R_FSC13                      ((uint16_t)0x2000)            

#define  CAN_FFA1R_FFA                       ((uint16_t)0x3FFF)            
#define  CAN_FFA1R_FFA0                      ((uint16_t)0x0001)            
#define  CAN_FFA1R_FFA1                      ((uint16_t)0x0002)            
#define  CAN_FFA1R_FFA2                      ((uint16_t)0x0004)            
#define  CAN_FFA1R_FFA3                      ((uint16_t)0x0008)            
#define  CAN_FFA1R_FFA4                      ((uint16_t)0x0010)            
#define  CAN_FFA1R_FFA5                      ((uint16_t)0x0020)            
#define  CAN_FFA1R_FFA6                      ((uint16_t)0x0040)            
#define  CAN_FFA1R_FFA7                      ((uint16_t)0x0080)            
#define  CAN_FFA1R_FFA8                      ((uint16_t)0x0100)            
#define  CAN_FFA1R_FFA9                      ((uint16_t)0x0200)            
#define  CAN_FFA1R_FFA10                     ((uint16_t)0x0400)            
#define  CAN_FFA1R_FFA11                     ((uint16_t)0x0800)            
#define  CAN_FFA1R_FFA12                     ((uint16_t)0x1000)            
#define  CAN_FFA1R_FFA13                     ((uint16_t)0x2000)            

#define  CAN_FA1R_FACT                       ((uint16_t)0x3FFF)            
#define  CAN_FA1R_FACT0                      ((uint16_t)0x0001)            
#define  CAN_FA1R_FACT1                      ((uint16_t)0x0002)            
#define  CAN_FA1R_FACT2                      ((uint16_t)0x0004)            
#define  CAN_FA1R_FACT3                      ((uint16_t)0x0008)            
#define  CAN_FA1R_FACT4                      ((uint16_t)0x0010)            
#define  CAN_FA1R_FACT5                      ((uint16_t)0x0020)            
#define  CAN_FA1R_FACT6                      ((uint16_t)0x0040)            
#define  CAN_FA1R_FACT7                      ((uint16_t)0x0080)            
#define  CAN_FA1R_FACT8                      ((uint16_t)0x0100)            
#define  CAN_FA1R_FACT9                      ((uint16_t)0x0200)            
#define  CAN_FA1R_FACT10                     ((uint16_t)0x0400)            
#define  CAN_FA1R_FACT11                     ((uint16_t)0x0800)            
#define  CAN_FA1R_FACT12                     ((uint16_t)0x1000)            
#define  CAN_FA1R_FACT13                     ((uint16_t)0x2000)            

#define  CAN_F0R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F0R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F0R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F0R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F0R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F0R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F0R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F0R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F0R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F0R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F0R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F0R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F0R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F0R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F0R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F0R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F0R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F0R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F0R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F0R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F0R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F0R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F0R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F0R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F0R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F0R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F0R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F0R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F0R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F0R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F0R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F0R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F1R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F1R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F1R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F1R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F1R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F1R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F1R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F1R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F1R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F1R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F1R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F1R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F1R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F1R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F1R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F1R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F1R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F1R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F1R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F1R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F1R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F1R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F1R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F1R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F1R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F1R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F1R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F1R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F1R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F1R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F1R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F1R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F2R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F2R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F2R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F2R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F2R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F2R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F2R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F2R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F2R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F2R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F2R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F2R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F2R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F2R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F2R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F2R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F2R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F2R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F2R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F2R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F2R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F2R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F2R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F2R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F2R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F2R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F2R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F2R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F2R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F2R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F2R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F2R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F3R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F3R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F3R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F3R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F3R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F3R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F3R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F3R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F3R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F3R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F3R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F3R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F3R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F3R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F3R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F3R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F3R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F3R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F3R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F3R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F3R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F3R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F3R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F3R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F3R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F3R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F3R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F3R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F3R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F3R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F3R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F3R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F4R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F4R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F4R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F4R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F4R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F4R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F4R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F4R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F4R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F4R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F4R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F4R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F4R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F4R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F4R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F4R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F4R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F4R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F4R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F4R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F4R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F4R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F4R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F4R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F4R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F4R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F4R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F4R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F4R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F4R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F4R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F4R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F5R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F5R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F5R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F5R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F5R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F5R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F5R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F5R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F5R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F5R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F5R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F5R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F5R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F5R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F5R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F5R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F5R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F5R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F5R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F5R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F5R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F5R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F5R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F5R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F5R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F5R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F5R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F5R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F5R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F5R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F5R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F5R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F6R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F6R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F6R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F6R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F6R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F6R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F6R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F6R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F6R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F6R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F6R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F6R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F6R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F6R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F6R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F6R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F6R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F6R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F6R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F6R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F6R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F6R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F6R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F6R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F6R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F6R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F6R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F6R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F6R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F6R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F6R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F6R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F7R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F7R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F7R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F7R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F7R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F7R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F7R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F7R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F7R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F7R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F7R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F7R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F7R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F7R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F7R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F7R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F7R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F7R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F7R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F7R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F7R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F7R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F7R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F7R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F7R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F7R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F7R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F7R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F7R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F7R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F7R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F7R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F8R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F8R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F8R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F8R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F8R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F8R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F8R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F8R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F8R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F8R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F8R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F8R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F8R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F8R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F8R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F8R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F8R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F8R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F8R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F8R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F8R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F8R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F8R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F8R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F8R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F8R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F8R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F8R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F8R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F8R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F8R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F8R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F9R1_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F9R1_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F9R1_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F9R1_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F9R1_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F9R1_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F9R1_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F9R1_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F9R1_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F9R1_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F9R1_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F9R1_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F9R1_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F9R1_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F9R1_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F9R1_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F9R1_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F9R1_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F9R1_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F9R1_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F9R1_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F9R1_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F9R1_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F9R1_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F9R1_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F9R1_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F9R1_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F9R1_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F9R1_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F9R1_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F9R1_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F9R1_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F10R1_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F10R1_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F10R1_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F10R1_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F10R1_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F10R1_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F10R1_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F10R1_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F10R1_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F10R1_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F10R1_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F10R1_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F10R1_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F10R1_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F10R1_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F10R1_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F10R1_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F10R1_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F10R1_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F10R1_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F10R1_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F10R1_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F10R1_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F10R1_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F10R1_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F10R1_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F10R1_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F10R1_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F10R1_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F10R1_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F10R1_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F10R1_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F11R1_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F11R1_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F11R1_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F11R1_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F11R1_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F11R1_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F11R1_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F11R1_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F11R1_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F11R1_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F11R1_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F11R1_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F11R1_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F11R1_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F11R1_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F11R1_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F11R1_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F11R1_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F11R1_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F11R1_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F11R1_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F11R1_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F11R1_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F11R1_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F11R1_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F11R1_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F11R1_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F11R1_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F11R1_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F11R1_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F11R1_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F11R1_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F12R1_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F12R1_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F12R1_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F12R1_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F12R1_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F12R1_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F12R1_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F12R1_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F12R1_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F12R1_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F12R1_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F12R1_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F12R1_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F12R1_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F12R1_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F12R1_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F12R1_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F12R1_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F12R1_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F12R1_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F12R1_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F12R1_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F12R1_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F12R1_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F12R1_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F12R1_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F12R1_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F12R1_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F12R1_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F12R1_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F12R1_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F12R1_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F13R1_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F13R1_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F13R1_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F13R1_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F13R1_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F13R1_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F13R1_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F13R1_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F13R1_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F13R1_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F13R1_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F13R1_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F13R1_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F13R1_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F13R1_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F13R1_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F13R1_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F13R1_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F13R1_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F13R1_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F13R1_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F13R1_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F13R1_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F13R1_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F13R1_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F13R1_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F13R1_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F13R1_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F13R1_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F13R1_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F13R1_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F13R1_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F0R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F0R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F0R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F0R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F0R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F0R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F0R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F0R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F0R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F0R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F0R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F0R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F0R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F0R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F0R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F0R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F0R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F0R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F0R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F0R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F0R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F0R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F0R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F0R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F0R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F0R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F0R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F0R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F0R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F0R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F0R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F0R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F1R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F1R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F1R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F1R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F1R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F1R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F1R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F1R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F1R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F1R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F1R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F1R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F1R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F1R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F1R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F1R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F1R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F1R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F1R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F1R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F1R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F1R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F1R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F1R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F1R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F1R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F1R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F1R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F1R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F1R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F1R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F1R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F2R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F2R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F2R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F2R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F2R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F2R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F2R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F2R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F2R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F2R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F2R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F2R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F2R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F2R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F2R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F2R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F2R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F2R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F2R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F2R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F2R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F2R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F2R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F2R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F2R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F2R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F2R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F2R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F2R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F2R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F2R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F2R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F3R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F3R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F3R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F3R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F3R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F3R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F3R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F3R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F3R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F3R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F3R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F3R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F3R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F3R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F3R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F3R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F3R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F3R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F3R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F3R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F3R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F3R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F3R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F3R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F3R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F3R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F3R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F3R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F3R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F3R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F3R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F3R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F4R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F4R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F4R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F4R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F4R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F4R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F4R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F4R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F4R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F4R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F4R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F4R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F4R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F4R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F4R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F4R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F4R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F4R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F4R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F4R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F4R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F4R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F4R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F4R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F4R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F4R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F4R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F4R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F4R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F4R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F4R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F4R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F5R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F5R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F5R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F5R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F5R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F5R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F5R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F5R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F5R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F5R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F5R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F5R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F5R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F5R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F5R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F5R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F5R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F5R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F5R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F5R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F5R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F5R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F5R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F5R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F5R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F5R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F5R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F5R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F5R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F5R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F5R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F5R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F6R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F6R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F6R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F6R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F6R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F6R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F6R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F6R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F6R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F6R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F6R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F6R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F6R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F6R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F6R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F6R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F6R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F6R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F6R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F6R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F6R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F6R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F6R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F6R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F6R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F6R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F6R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F6R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F6R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F6R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F6R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F6R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F7R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F7R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F7R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F7R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F7R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F7R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F7R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F7R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F7R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F7R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F7R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F7R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F7R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F7R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F7R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F7R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F7R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F7R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F7R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F7R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F7R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F7R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F7R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F7R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F7R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F7R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F7R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F7R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F7R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F7R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F7R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F7R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F8R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F8R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F8R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F8R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F8R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F8R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F8R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F8R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F8R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F8R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F8R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F8R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F8R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F8R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F8R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F8R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F8R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F8R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F8R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F8R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F8R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F8R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F8R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F8R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F8R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F8R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F8R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F8R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F8R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F8R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F8R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F8R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F9R2_FB0                        ((uint32_t)0x00000001)        
#define  CAN_F9R2_FB1                        ((uint32_t)0x00000002)        
#define  CAN_F9R2_FB2                        ((uint32_t)0x00000004)        
#define  CAN_F9R2_FB3                        ((uint32_t)0x00000008)        
#define  CAN_F9R2_FB4                        ((uint32_t)0x00000010)        
#define  CAN_F9R2_FB5                        ((uint32_t)0x00000020)        
#define  CAN_F9R2_FB6                        ((uint32_t)0x00000040)        
#define  CAN_F9R2_FB7                        ((uint32_t)0x00000080)        
#define  CAN_F9R2_FB8                        ((uint32_t)0x00000100)        
#define  CAN_F9R2_FB9                        ((uint32_t)0x00000200)        
#define  CAN_F9R2_FB10                       ((uint32_t)0x00000400)        
#define  CAN_F9R2_FB11                       ((uint32_t)0x00000800)        
#define  CAN_F9R2_FB12                       ((uint32_t)0x00001000)        
#define  CAN_F9R2_FB13                       ((uint32_t)0x00002000)        
#define  CAN_F9R2_FB14                       ((uint32_t)0x00004000)        
#define  CAN_F9R2_FB15                       ((uint32_t)0x00008000)        
#define  CAN_F9R2_FB16                       ((uint32_t)0x00010000)        
#define  CAN_F9R2_FB17                       ((uint32_t)0x00020000)        
#define  CAN_F9R2_FB18                       ((uint32_t)0x00040000)        
#define  CAN_F9R2_FB19                       ((uint32_t)0x00080000)        
#define  CAN_F9R2_FB20                       ((uint32_t)0x00100000)        
#define  CAN_F9R2_FB21                       ((uint32_t)0x00200000)        
#define  CAN_F9R2_FB22                       ((uint32_t)0x00400000)        
#define  CAN_F9R2_FB23                       ((uint32_t)0x00800000)        
#define  CAN_F9R2_FB24                       ((uint32_t)0x01000000)        
#define  CAN_F9R2_FB25                       ((uint32_t)0x02000000)        
#define  CAN_F9R2_FB26                       ((uint32_t)0x04000000)        
#define  CAN_F9R2_FB27                       ((uint32_t)0x08000000)        
#define  CAN_F9R2_FB28                       ((uint32_t)0x10000000)        
#define  CAN_F9R2_FB29                       ((uint32_t)0x20000000)        
#define  CAN_F9R2_FB30                       ((uint32_t)0x40000000)        
#define  CAN_F9R2_FB31                       ((uint32_t)0x80000000)        

#define  CAN_F10R2_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F10R2_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F10R2_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F10R2_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F10R2_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F10R2_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F10R2_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F10R2_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F10R2_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F10R2_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F10R2_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F10R2_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F10R2_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F10R2_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F10R2_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F10R2_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F10R2_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F10R2_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F10R2_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F10R2_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F10R2_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F10R2_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F10R2_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F10R2_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F10R2_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F10R2_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F10R2_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F10R2_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F10R2_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F10R2_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F10R2_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F10R2_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F11R2_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F11R2_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F11R2_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F11R2_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F11R2_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F11R2_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F11R2_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F11R2_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F11R2_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F11R2_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F11R2_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F11R2_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F11R2_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F11R2_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F11R2_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F11R2_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F11R2_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F11R2_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F11R2_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F11R2_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F11R2_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F11R2_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F11R2_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F11R2_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F11R2_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F11R2_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F11R2_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F11R2_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F11R2_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F11R2_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F11R2_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F11R2_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F12R2_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F12R2_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F12R2_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F12R2_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F12R2_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F12R2_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F12R2_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F12R2_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F12R2_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F12R2_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F12R2_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F12R2_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F12R2_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F12R2_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F12R2_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F12R2_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F12R2_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F12R2_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F12R2_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F12R2_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F12R2_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F12R2_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F12R2_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F12R2_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F12R2_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F12R2_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F12R2_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F12R2_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F12R2_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F12R2_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F12R2_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F12R2_FB31                      ((uint32_t)0x80000000)        

#define  CAN_F13R2_FB0                       ((uint32_t)0x00000001)        
#define  CAN_F13R2_FB1                       ((uint32_t)0x00000002)        
#define  CAN_F13R2_FB2                       ((uint32_t)0x00000004)        
#define  CAN_F13R2_FB3                       ((uint32_t)0x00000008)        
#define  CAN_F13R2_FB4                       ((uint32_t)0x00000010)        
#define  CAN_F13R2_FB5                       ((uint32_t)0x00000020)        
#define  CAN_F13R2_FB6                       ((uint32_t)0x00000040)        
#define  CAN_F13R2_FB7                       ((uint32_t)0x00000080)        
#define  CAN_F13R2_FB8                       ((uint32_t)0x00000100)        
#define  CAN_F13R2_FB9                       ((uint32_t)0x00000200)        
#define  CAN_F13R2_FB10                      ((uint32_t)0x00000400)        
#define  CAN_F13R2_FB11                      ((uint32_t)0x00000800)        
#define  CAN_F13R2_FB12                      ((uint32_t)0x00001000)        
#define  CAN_F13R2_FB13                      ((uint32_t)0x00002000)        
#define  CAN_F13R2_FB14                      ((uint32_t)0x00004000)        
#define  CAN_F13R2_FB15                      ((uint32_t)0x00008000)        
#define  CAN_F13R2_FB16                      ((uint32_t)0x00010000)        
#define  CAN_F13R2_FB17                      ((uint32_t)0x00020000)        
#define  CAN_F13R2_FB18                      ((uint32_t)0x00040000)        
#define  CAN_F13R2_FB19                      ((uint32_t)0x00080000)        
#define  CAN_F13R2_FB20                      ((uint32_t)0x00100000)        
#define  CAN_F13R2_FB21                      ((uint32_t)0x00200000)        
#define  CAN_F13R2_FB22                      ((uint32_t)0x00400000)        
#define  CAN_F13R2_FB23                      ((uint32_t)0x00800000)        
#define  CAN_F13R2_FB24                      ((uint32_t)0x01000000)        
#define  CAN_F13R2_FB25                      ((uint32_t)0x02000000)        
#define  CAN_F13R2_FB26                      ((uint32_t)0x04000000)        
#define  CAN_F13R2_FB27                      ((uint32_t)0x08000000)        
#define  CAN_F13R2_FB28                      ((uint32_t)0x10000000)        
#define  CAN_F13R2_FB29                      ((uint32_t)0x20000000)        
#define  CAN_F13R2_FB30                      ((uint32_t)0x40000000)        
#define  CAN_F13R2_FB31                      ((uint32_t)0x80000000)        

#define  CRC_DR_DR                           ((uint32_t)0xFFFFFFFF) 

#define  CRC_IDR_IDR                         ((uint8_t)0xFF)        

#define  CRC_CR_RESET                        ((uint8_t)0x01)        

#define CRYP_CR_ALGODIR                      ((uint32_t)0x00000004)

#define CRYP_CR_ALGOMODE                     ((uint32_t)0x00080038)
#define CRYP_CR_ALGOMODE_0                   ((uint32_t)0x00000008)
#define CRYP_CR_ALGOMODE_1                   ((uint32_t)0x00000010)
#define CRYP_CR_ALGOMODE_2                   ((uint32_t)0x00000020)
#define CRYP_CR_ALGOMODE_TDES_ECB            ((uint32_t)0x00000000)
#define CRYP_CR_ALGOMODE_TDES_CBC            ((uint32_t)0x00000008)
#define CRYP_CR_ALGOMODE_DES_ECB             ((uint32_t)0x00000010)
#define CRYP_CR_ALGOMODE_DES_CBC             ((uint32_t)0x00000018)
#define CRYP_CR_ALGOMODE_AES_ECB             ((uint32_t)0x00000020)
#define CRYP_CR_ALGOMODE_AES_CBC             ((uint32_t)0x00000028)
#define CRYP_CR_ALGOMODE_AES_CTR             ((uint32_t)0x00000030)
#define CRYP_CR_ALGOMODE_AES_KEY             ((uint32_t)0x00000038)

#define CRYP_CR_DATATYPE                     ((uint32_t)0x000000C0)
#define CRYP_CR_DATATYPE_0                   ((uint32_t)0x00000040)
#define CRYP_CR_DATATYPE_1                   ((uint32_t)0x00000080)
#define CRYP_CR_KEYSIZE                      ((uint32_t)0x00000300)
#define CRYP_CR_KEYSIZE_0                    ((uint32_t)0x00000100)
#define CRYP_CR_KEYSIZE_1                    ((uint32_t)0x00000200)
#define CRYP_CR_FFLUSH                       ((uint32_t)0x00004000)
#define CRYP_CR_CRYPEN                       ((uint32_t)0x00008000)

#define CRYP_CR_GCM_CCMPH                    ((uint32_t)0x00030000)
#define CRYP_CR_GCM_CCMPH_0                  ((uint32_t)0x00010000)
#define CRYP_CR_GCM_CCMPH_1                  ((uint32_t)0x00020000)
#define CRYP_CR_ALGOMODE_3                   ((uint32_t)0x00080000) 

#define CRYP_SR_IFEM                         ((uint32_t)0x00000001)
#define CRYP_SR_IFNF                         ((uint32_t)0x00000002)
#define CRYP_SR_OFNE                         ((uint32_t)0x00000004)
#define CRYP_SR_OFFU                         ((uint32_t)0x00000008)
#define CRYP_SR_BUSY                         ((uint32_t)0x00000010)

#define CRYP_DMACR_DIEN                      ((uint32_t)0x00000001)
#define CRYP_DMACR_DOEN                      ((uint32_t)0x00000002)

#define CRYP_IMSCR_INIM                      ((uint32_t)0x00000001)
#define CRYP_IMSCR_OUTIM                     ((uint32_t)0x00000002)

#define CRYP_RISR_OUTRIS                     ((uint32_t)0x00000001)
#define CRYP_RISR_INRIS                      ((uint32_t)0x00000002)

#define CRYP_MISR_INMIS                      ((uint32_t)0x00000001)
#define CRYP_MISR_OUTMIS                     ((uint32_t)0x00000002)

#define  DAC_CR_EN1                          ((uint32_t)0x00000001)        
#define  DAC_CR_BOFF1                        ((uint32_t)0x00000002)        
#define  DAC_CR_TEN1                         ((uint32_t)0x00000004)        

#define  DAC_CR_TSEL1                        ((uint32_t)0x00000038)        
#define  DAC_CR_TSEL1_0                      ((uint32_t)0x00000008)        
#define  DAC_CR_TSEL1_1                      ((uint32_t)0x00000010)        
#define  DAC_CR_TSEL1_2                      ((uint32_t)0x00000020)        

#define  DAC_CR_WAVE1                        ((uint32_t)0x000000C0)        
#define  DAC_CR_WAVE1_0                      ((uint32_t)0x00000040)        
#define  DAC_CR_WAVE1_1                      ((uint32_t)0x00000080)        

#define  DAC_CR_MAMP1                        ((uint32_t)0x00000F00)        
#define  DAC_CR_MAMP1_0                      ((uint32_t)0x00000100)        
#define  DAC_CR_MAMP1_1                      ((uint32_t)0x00000200)        
#define  DAC_CR_MAMP1_2                      ((uint32_t)0x00000400)        
#define  DAC_CR_MAMP1_3                      ((uint32_t)0x00000800)        

#define  DAC_CR_DMAEN1                       ((uint32_t)0x00001000)        
#define  DAC_CR_EN2                          ((uint32_t)0x00010000)        
#define  DAC_CR_BOFF2                        ((uint32_t)0x00020000)        
#define  DAC_CR_TEN2                         ((uint32_t)0x00040000)        

#define  DAC_CR_TSEL2                        ((uint32_t)0x00380000)        
#define  DAC_CR_TSEL2_0                      ((uint32_t)0x00080000)        
#define  DAC_CR_TSEL2_1                      ((uint32_t)0x00100000)        
#define  DAC_CR_TSEL2_2                      ((uint32_t)0x00200000)        

#define  DAC_CR_WAVE2                        ((uint32_t)0x00C00000)        
#define  DAC_CR_WAVE2_0                      ((uint32_t)0x00400000)        
#define  DAC_CR_WAVE2_1                      ((uint32_t)0x00800000)        

#define  DAC_CR_MAMP2                        ((uint32_t)0x0F000000)        
#define  DAC_CR_MAMP2_0                      ((uint32_t)0x01000000)        
#define  DAC_CR_MAMP2_1                      ((uint32_t)0x02000000)        
#define  DAC_CR_MAMP2_2                      ((uint32_t)0x04000000)        
#define  DAC_CR_MAMP2_3                      ((uint32_t)0x08000000)        

#define  DAC_CR_DMAEN2                       ((uint32_t)0x10000000)        

#define  DAC_SWTRIGR_SWTRIG1                 ((uint8_t)0x01)               
#define  DAC_SWTRIGR_SWTRIG2                 ((uint8_t)0x02)               

#define  DAC_DHR12R1_DACC1DHR                ((uint16_t)0x0FFF)            

#define  DAC_DHR12L1_DACC1DHR                ((uint16_t)0xFFF0)            

#define  DAC_DHR8R1_DACC1DHR                 ((uint8_t)0xFF)               

#define  DAC_DHR12R2_DACC2DHR                ((uint16_t)0x0FFF)            

#define  DAC_DHR12L2_DACC2DHR                ((uint16_t)0xFFF0)            

#define  DAC_DHR8R2_DACC2DHR                 ((uint8_t)0xFF)               

#define  DAC_DHR12RD_DACC1DHR                ((uint32_t)0x00000FFF)        
#define  DAC_DHR12RD_DACC2DHR                ((uint32_t)0x0FFF0000)        

#define  DAC_DHR12LD_DACC1DHR                ((uint32_t)0x0000FFF0)        
#define  DAC_DHR12LD_DACC2DHR                ((uint32_t)0xFFF00000)        

#define  DAC_DHR8RD_DACC1DHR                 ((uint16_t)0x00FF)            
#define  DAC_DHR8RD_DACC2DHR                 ((uint16_t)0xFF00)            

#define  DAC_DOR1_DACC1DOR                   ((uint16_t)0x0FFF)            

#define  DAC_DOR2_DACC2DOR                   ((uint16_t)0x0FFF)            

#define  DAC_SR_DMAUDR1                      ((uint32_t)0x00002000)        
#define  DAC_SR_DMAUDR2                      ((uint32_t)0x20000000)        

#define DCMI_CR_CAPTURE                      ((uint32_t)0x00000001)
#define DCMI_CR_CM                           ((uint32_t)0x00000002)
#define DCMI_CR_CROP                         ((uint32_t)0x00000004)
#define DCMI_CR_JPEG                         ((uint32_t)0x00000008)
#define DCMI_CR_ESS                          ((uint32_t)0x00000010)
#define DCMI_CR_PCKPOL                       ((uint32_t)0x00000020)
#define DCMI_CR_HSPOL                        ((uint32_t)0x00000040)
#define DCMI_CR_VSPOL                        ((uint32_t)0x00000080)
#define DCMI_CR_FCRC_0                       ((uint32_t)0x00000100)
#define DCMI_CR_FCRC_1                       ((uint32_t)0x00000200)
#define DCMI_CR_EDM_0                        ((uint32_t)0x00000400)
#define DCMI_CR_EDM_1                        ((uint32_t)0x00000800)
#define DCMI_CR_CRE                          ((uint32_t)0x00001000)
#define DCMI_CR_ENABLE                       ((uint32_t)0x00004000)

#define DCMI_SR_HSYNC                        ((uint32_t)0x00000001)
#define DCMI_SR_VSYNC                        ((uint32_t)0x00000002)
#define DCMI_SR_FNE                          ((uint32_t)0x00000004)

#define DCMI_RISR_FRAME_RIS                  ((uint32_t)0x00000001)
#define DCMI_RISR_OVF_RIS                    ((uint32_t)0x00000002)
#define DCMI_RISR_ERR_RIS                    ((uint32_t)0x00000004)
#define DCMI_RISR_VSYNC_RIS                  ((uint32_t)0x00000008)
#define DCMI_RISR_LINE_RIS                   ((uint32_t)0x00000010)

#define DCMI_IER_FRAME_IE                    ((uint32_t)0x00000001)
#define DCMI_IER_OVF_IE                      ((uint32_t)0x00000002)
#define DCMI_IER_ERR_IE                      ((uint32_t)0x00000004)
#define DCMI_IER_VSYNC_IE                    ((uint32_t)0x00000008)
#define DCMI_IER_LINE_IE                     ((uint32_t)0x00000010)

#define DCMI_MISR_FRAME_MIS                  ((uint32_t)0x00000001)
#define DCMI_MISR_OVF_MIS                    ((uint32_t)0x00000002)
#define DCMI_MISR_ERR_MIS                    ((uint32_t)0x00000004)
#define DCMI_MISR_VSYNC_MIS                  ((uint32_t)0x00000008)
#define DCMI_MISR_LINE_MIS                   ((uint32_t)0x00000010)

#define DCMI_ICR_FRAME_ISC                   ((uint32_t)0x00000001)
#define DCMI_ICR_OVF_ISC                     ((uint32_t)0x00000002)
#define DCMI_ICR_ERR_ISC                     ((uint32_t)0x00000004)
#define DCMI_ICR_VSYNC_ISC                   ((uint32_t)0x00000008)
#define DCMI_ICR_LINE_ISC                    ((uint32_t)0x00000010)

 
#define DMA_SxCR_CHSEL                       ((uint32_t)0x0E000000)
#define DMA_SxCR_CHSEL_0                     ((uint32_t)0x02000000)
#define DMA_SxCR_CHSEL_1                     ((uint32_t)0x04000000)
#define DMA_SxCR_CHSEL_2                     ((uint32_t)0x08000000) 
#define DMA_SxCR_MBURST                      ((uint32_t)0x01800000)
#define DMA_SxCR_MBURST_0                    ((uint32_t)0x00800000)
#define DMA_SxCR_MBURST_1                    ((uint32_t)0x01000000)
#define DMA_SxCR_PBURST                      ((uint32_t)0x00600000)
#define DMA_SxCR_PBURST_0                    ((uint32_t)0x00200000)
#define DMA_SxCR_PBURST_1                    ((uint32_t)0x00400000)
#define DMA_SxCR_ACK                         ((uint32_t)0x00100000)
#define DMA_SxCR_CT                          ((uint32_t)0x00080000)  
#define DMA_SxCR_DBM                         ((uint32_t)0x00040000)
#define DMA_SxCR_PL                          ((uint32_t)0x00030000)
#define DMA_SxCR_PL_0                        ((uint32_t)0x00010000)
#define DMA_SxCR_PL_1                        ((uint32_t)0x00020000)
#define DMA_SxCR_PINCOS                      ((uint32_t)0x00008000)
#define DMA_SxCR_MSIZE                       ((uint32_t)0x00006000)
#define DMA_SxCR_MSIZE_0                     ((uint32_t)0x00002000)
#define DMA_SxCR_MSIZE_1                     ((uint32_t)0x00004000)
#define DMA_SxCR_PSIZE                       ((uint32_t)0x00001800)
#define DMA_SxCR_PSIZE_0                     ((uint32_t)0x00000800)
#define DMA_SxCR_PSIZE_1                     ((uint32_t)0x00001000)
#define DMA_SxCR_MINC                        ((uint32_t)0x00000400)
#define DMA_SxCR_PINC                        ((uint32_t)0x00000200)
#define DMA_SxCR_CIRC                        ((uint32_t)0x00000100)
#define DMA_SxCR_DIR                         ((uint32_t)0x000000C0)
#define DMA_SxCR_DIR_0                       ((uint32_t)0x00000040)
#define DMA_SxCR_DIR_1                       ((uint32_t)0x00000080)
#define DMA_SxCR_PFCTRL                      ((uint32_t)0x00000020)
#define DMA_SxCR_TCIE                        ((uint32_t)0x00000010)
#define DMA_SxCR_HTIE                        ((uint32_t)0x00000008)
#define DMA_SxCR_TEIE                        ((uint32_t)0x00000004)
#define DMA_SxCR_DMEIE                       ((uint32_t)0x00000002)
#define DMA_SxCR_EN                          ((uint32_t)0x00000001)

#define DMA_SxNDT                            ((uint32_t)0x0000FFFF)
#define DMA_SxNDT_0                          ((uint32_t)0x00000001)
#define DMA_SxNDT_1                          ((uint32_t)0x00000002)
#define DMA_SxNDT_2                          ((uint32_t)0x00000004)
#define DMA_SxNDT_3                          ((uint32_t)0x00000008)
#define DMA_SxNDT_4                          ((uint32_t)0x00000010)
#define DMA_SxNDT_5                          ((uint32_t)0x00000020)
#define DMA_SxNDT_6                          ((uint32_t)0x00000040)
#define DMA_SxNDT_7                          ((uint32_t)0x00000080)
#define DMA_SxNDT_8                          ((uint32_t)0x00000100)
#define DMA_SxNDT_9                          ((uint32_t)0x00000200)
#define DMA_SxNDT_10                         ((uint32_t)0x00000400)
#define DMA_SxNDT_11                         ((uint32_t)0x00000800)
#define DMA_SxNDT_12                         ((uint32_t)0x00001000)
#define DMA_SxNDT_13                         ((uint32_t)0x00002000)
#define DMA_SxNDT_14                         ((uint32_t)0x00004000)
#define DMA_SxNDT_15                         ((uint32_t)0x00008000)

 
#define DMA_SxFCR_FEIE                       ((uint32_t)0x00000080)
#define DMA_SxFCR_FS                         ((uint32_t)0x00000038)
#define DMA_SxFCR_FS_0                       ((uint32_t)0x00000008)
#define DMA_SxFCR_FS_1                       ((uint32_t)0x00000010)
#define DMA_SxFCR_FS_2                       ((uint32_t)0x00000020)
#define DMA_SxFCR_DMDIS                      ((uint32_t)0x00000004)
#define DMA_SxFCR_FTH                        ((uint32_t)0x00000003)
#define DMA_SxFCR_FTH_0                      ((uint32_t)0x00000001)
#define DMA_SxFCR_FTH_1                      ((uint32_t)0x00000002)

 
#define DMA_LISR_TCIF3                       ((uint32_t)0x08000000)
#define DMA_LISR_HTIF3                       ((uint32_t)0x04000000)
#define DMA_LISR_TEIF3                       ((uint32_t)0x02000000)
#define DMA_LISR_DMEIF3                      ((uint32_t)0x01000000)
#define DMA_LISR_FEIF3                       ((uint32_t)0x00400000)
#define DMA_LISR_TCIF2                       ((uint32_t)0x00200000)
#define DMA_LISR_HTIF2                       ((uint32_t)0x00100000)
#define DMA_LISR_TEIF2                       ((uint32_t)0x00080000)
#define DMA_LISR_DMEIF2                      ((uint32_t)0x00040000)
#define DMA_LISR_FEIF2                       ((uint32_t)0x00010000)
#define DMA_LISR_TCIF1                       ((uint32_t)0x00000800)
#define DMA_LISR_HTIF1                       ((uint32_t)0x00000400)
#define DMA_LISR_TEIF1                       ((uint32_t)0x00000200)
#define DMA_LISR_DMEIF1                      ((uint32_t)0x00000100)
#define DMA_LISR_FEIF1                       ((uint32_t)0x00000040)
#define DMA_LISR_TCIF0                       ((uint32_t)0x00000020)
#define DMA_LISR_HTIF0                       ((uint32_t)0x00000010)
#define DMA_LISR_TEIF0                       ((uint32_t)0x00000008)
#define DMA_LISR_DMEIF0                      ((uint32_t)0x00000004)
#define DMA_LISR_FEIF0                       ((uint32_t)0x00000001)

 
#define DMA_HISR_TCIF7                       ((uint32_t)0x08000000)
#define DMA_HISR_HTIF7                       ((uint32_t)0x04000000)
#define DMA_HISR_TEIF7                       ((uint32_t)0x02000000)
#define DMA_HISR_DMEIF7                      ((uint32_t)0x01000000)
#define DMA_HISR_FEIF7                       ((uint32_t)0x00400000)
#define DMA_HISR_TCIF6                       ((uint32_t)0x00200000)
#define DMA_HISR_HTIF6                       ((uint32_t)0x00100000)
#define DMA_HISR_TEIF6                       ((uint32_t)0x00080000)
#define DMA_HISR_DMEIF6                      ((uint32_t)0x00040000)
#define DMA_HISR_FEIF6                       ((uint32_t)0x00010000)
#define DMA_HISR_TCIF5                       ((uint32_t)0x00000800)
#define DMA_HISR_HTIF5                       ((uint32_t)0x00000400)
#define DMA_HISR_TEIF5                       ((uint32_t)0x00000200)
#define DMA_HISR_DMEIF5                      ((uint32_t)0x00000100)
#define DMA_HISR_FEIF5                       ((uint32_t)0x00000040)
#define DMA_HISR_TCIF4                       ((uint32_t)0x00000020)
#define DMA_HISR_HTIF4                       ((uint32_t)0x00000010)
#define DMA_HISR_TEIF4                       ((uint32_t)0x00000008)
#define DMA_HISR_DMEIF4                      ((uint32_t)0x00000004)
#define DMA_HISR_FEIF4                       ((uint32_t)0x00000001)

 
#define DMA_LIFCR_CTCIF3                     ((uint32_t)0x08000000)
#define DMA_LIFCR_CHTIF3                     ((uint32_t)0x04000000)
#define DMA_LIFCR_CTEIF3                     ((uint32_t)0x02000000)
#define DMA_LIFCR_CDMEIF3                    ((uint32_t)0x01000000)
#define DMA_LIFCR_CFEIF3                     ((uint32_t)0x00400000)
#define DMA_LIFCR_CTCIF2                     ((uint32_t)0x00200000)
#define DMA_LIFCR_CHTIF2                     ((uint32_t)0x00100000)
#define DMA_LIFCR_CTEIF2                     ((uint32_t)0x00080000)
#define DMA_LIFCR_CDMEIF2                    ((uint32_t)0x00040000)
#define DMA_LIFCR_CFEIF2                     ((uint32_t)0x00010000)
#define DMA_LIFCR_CTCIF1                     ((uint32_t)0x00000800)
#define DMA_LIFCR_CHTIF1                     ((uint32_t)0x00000400)
#define DMA_LIFCR_CTEIF1                     ((uint32_t)0x00000200)
#define DMA_LIFCR_CDMEIF1                    ((uint32_t)0x00000100)
#define DMA_LIFCR_CFEIF1                     ((uint32_t)0x00000040)
#define DMA_LIFCR_CTCIF0                     ((uint32_t)0x00000020)
#define DMA_LIFCR_CHTIF0                     ((uint32_t)0x00000010)
#define DMA_LIFCR_CTEIF0                     ((uint32_t)0x00000008)
#define DMA_LIFCR_CDMEIF0                    ((uint32_t)0x00000004)
#define DMA_LIFCR_CFEIF0                     ((uint32_t)0x00000001)

 
#define DMA_HIFCR_CTCIF7                     ((uint32_t)0x08000000)
#define DMA_HIFCR_CHTIF7                     ((uint32_t)0x04000000)
#define DMA_HIFCR_CTEIF7                     ((uint32_t)0x02000000)
#define DMA_HIFCR_CDMEIF7                    ((uint32_t)0x01000000)
#define DMA_HIFCR_CFEIF7                     ((uint32_t)0x00400000)
#define DMA_HIFCR_CTCIF6                     ((uint32_t)0x00200000)
#define DMA_HIFCR_CHTIF6                     ((uint32_t)0x00100000)
#define DMA_HIFCR_CTEIF6                     ((uint32_t)0x00080000)
#define DMA_HIFCR_CDMEIF6                    ((uint32_t)0x00040000)
#define DMA_HIFCR_CFEIF6                     ((uint32_t)0x00010000)
#define DMA_HIFCR_CTCIF5                     ((uint32_t)0x00000800)
#define DMA_HIFCR_CHTIF5                     ((uint32_t)0x00000400)
#define DMA_HIFCR_CTEIF5                     ((uint32_t)0x00000200)
#define DMA_HIFCR_CDMEIF5                    ((uint32_t)0x00000100)
#define DMA_HIFCR_CFEIF5                     ((uint32_t)0x00000040)
#define DMA_HIFCR_CTCIF4                     ((uint32_t)0x00000020)
#define DMA_HIFCR_CHTIF4                     ((uint32_t)0x00000010)
#define DMA_HIFCR_CTEIF4                     ((uint32_t)0x00000008)
#define DMA_HIFCR_CDMEIF4                    ((uint32_t)0x00000004)
#define DMA_HIFCR_CFEIF4                     ((uint32_t)0x00000001)

#define DMA2D_CR_START                     ((uint32_t)0x00000001)               
#define DMA2D_CR_SUSP                      ((uint32_t)0x00000002)               
#define DMA2D_CR_ABORT                     ((uint32_t)0x00000004)               
#define DMA2D_CR_TEIE                      ((uint32_t)0x00000100)               
#define DMA2D_CR_TCIE                      ((uint32_t)0x00000200)               
#define DMA2D_CR_TWIE                      ((uint32_t)0x00000400)               
#define DMA2D_CR_CAEIE                     ((uint32_t)0x00000800)               
#define DMA2D_CR_CTCIE                     ((uint32_t)0x00001000)               
#define DMA2D_CR_CEIE                      ((uint32_t)0x00002000)               
#define DMA2D_CR_MODE                      ((uint32_t)0x00030000)               

#define DMA2D_ISR_TEIF                     ((uint32_t)0x00000001)               
#define DMA2D_ISR_TCIF                     ((uint32_t)0x00000002)               
#define DMA2D_ISR_TWIF                     ((uint32_t)0x00000004)               
#define DMA2D_ISR_CAEIF                    ((uint32_t)0x00000008)               
#define DMA2D_ISR_CTCIF                    ((uint32_t)0x00000010)               
#define DMA2D_ISR_CEIF                     ((uint32_t)0x00000020)               

#define DMA2D_IFSR_CTEIF                   ((uint32_t)0x00000001)               
#define DMA2D_IFSR_CTCIF                   ((uint32_t)0x00000002)               
#define DMA2D_IFSR_CTWIF                   ((uint32_t)0x00000004)               
#define DMA2D_IFSR_CCAEIF                  ((uint32_t)0x00000008)               
#define DMA2D_IFSR_CCTCIF                  ((uint32_t)0x00000010)               
#define DMA2D_IFSR_CCEIF                   ((uint32_t)0x00000020)               

#define DMA2D_FGMAR_MA                     ((uint32_t)0xFFFFFFFF)               

#define DMA2D_FGOR_LO                      ((uint32_t)0x00003FFF)               

#define DMA2D_BGMAR_MA                     ((uint32_t)0xFFFFFFFF)               

#define DMA2D_BGOR_LO                      ((uint32_t)0x00003FFF)               

#define DMA2D_FGPFCCR_CM                   ((uint32_t)0x0000000F)               
#define DMA2D_FGPFCCR_CCM                  ((uint32_t)0x00000010)               
#define DMA2D_FGPFCCR_START                ((uint32_t)0x00000020)               
#define DMA2D_FGPFCCR_CS                   ((uint32_t)0x0000FF00)               
#define DMA2D_FGPFCCR_AM                   ((uint32_t)0x00030000)               
#define DMA2D_FGPFCCR_ALPHA                ((uint32_t)0xFF000000)               

#define DMA2D_FGCOLR_BLUE                  ((uint32_t)0x000000FF)               
#define DMA2D_FGCOLR_GREEN                 ((uint32_t)0x0000FF00)               
#define DMA2D_FGCOLR_RED                   ((uint32_t)0x00FF0000)                  

#define DMA2D_BGPFCCR_CM                   ((uint32_t)0x0000000F)               
#define DMA2D_BGPFCCR_CCM                  ((uint32_t)0x00000010)               
#define DMA2D_BGPFCCR_START                ((uint32_t)0x00000020)               
#define DMA2D_BGPFCCR_CS                   ((uint32_t)0x0000FF00)               
#define DMA2D_BGPFCCR_AM                   ((uint32_t)0x00030000)               
#define DMA2D_BGPFCCR_ALPHA                ((uint32_t)0xFF000000)               

#define DMA2D_BGCOLR_BLUE                  ((uint32_t)0x000000FF)               
#define DMA2D_BGCOLR_GREEN                 ((uint32_t)0x0000FF00)               
#define DMA2D_BGCOLR_RED                   ((uint32_t)0x00FF0000)               

#define DMA2D_FGCMAR_MA                    ((uint32_t)0xFFFFFFFF)               

#define DMA2D_BGCMAR_MA                    ((uint32_t)0xFFFFFFFF)               

#define DMA2D_OPFCCR_CM                    ((uint32_t)0x00000007)               

#define DMA2D_OCOLR_BLUE_1                 ((uint32_t)0x000000FF)               
#define DMA2D_OCOLR_GREEN_1                ((uint32_t)0x0000FF00)               
#define DMA2D_OCOLR_RED_1                  ((uint32_t)0x00FF0000)               
#define DMA2D_OCOLR_ALPHA_1                ((uint32_t)0xFF000000)               

#define DMA2D_OCOLR_BLUE_2                 ((uint32_t)0x0000001F)               
#define DMA2D_OCOLR_GREEN_2                ((uint32_t)0x000007E0)               
#define DMA2D_OCOLR_RED_2                  ((uint32_t)0x0000F800)               

#define DMA2D_OCOLR_BLUE_3                 ((uint32_t)0x0000001F)               
#define DMA2D_OCOLR_GREEN_3                ((uint32_t)0x000003E0)               
#define DMA2D_OCOLR_RED_3                  ((uint32_t)0x00007C00)               
#define DMA2D_OCOLR_ALPHA_3                ((uint32_t)0x00008000)               

#define DMA2D_OCOLR_BLUE_4                 ((uint32_t)0x0000000F)               
#define DMA2D_OCOLR_GREEN_4                ((uint32_t)0x000000F0)               
#define DMA2D_OCOLR_RED_4                  ((uint32_t)0x00000F00)               
#define DMA2D_OCOLR_ALPHA_4                ((uint32_t)0x0000F000)               

#define DMA2D_OMAR_MA                      ((uint32_t)0xFFFFFFFF)               

#define DMA2D_OOR_LO                       ((uint32_t)0x00003FFF)               

#define DMA2D_NLR_NL                       ((uint32_t)0x0000FFFF)               
#define DMA2D_NLR_PL                       ((uint32_t)0x3FFF0000)               

#define DMA2D_LWR_LW                       ((uint32_t)0x0000FFFF)               

#define DMA2D_AMTCR_EN                     ((uint32_t)0x00000001)               
#define DMA2D_AMTCR_DT                     ((uint32_t)0x0000FF00)               

                                                                     

#define  EXTI_IMR_MR0                        ((uint32_t)0x00000001)        
#define  EXTI_IMR_MR1                        ((uint32_t)0x00000002)        
#define  EXTI_IMR_MR2                        ((uint32_t)0x00000004)        
#define  EXTI_IMR_MR3                        ((uint32_t)0x00000008)        
#define  EXTI_IMR_MR4                        ((uint32_t)0x00000010)        
#define  EXTI_IMR_MR5                        ((uint32_t)0x00000020)        
#define  EXTI_IMR_MR6                        ((uint32_t)0x00000040)        
#define  EXTI_IMR_MR7                        ((uint32_t)0x00000080)        
#define  EXTI_IMR_MR8                        ((uint32_t)0x00000100)        
#define  EXTI_IMR_MR9                        ((uint32_t)0x00000200)        
#define  EXTI_IMR_MR10                       ((uint32_t)0x00000400)        
#define  EXTI_IMR_MR11                       ((uint32_t)0x00000800)        
#define  EXTI_IMR_MR12                       ((uint32_t)0x00001000)        
#define  EXTI_IMR_MR13                       ((uint32_t)0x00002000)        
#define  EXTI_IMR_MR14                       ((uint32_t)0x00004000)        
#define  EXTI_IMR_MR15                       ((uint32_t)0x00008000)        
#define  EXTI_IMR_MR16                       ((uint32_t)0x00010000)        
#define  EXTI_IMR_MR17                       ((uint32_t)0x00020000)        
#define  EXTI_IMR_MR18                       ((uint32_t)0x00040000)        
#define  EXTI_IMR_MR19                       ((uint32_t)0x00080000)        

#define  EXTI_EMR_MR0                        ((uint32_t)0x00000001)        
#define  EXTI_EMR_MR1                        ((uint32_t)0x00000002)        
#define  EXTI_EMR_MR2                        ((uint32_t)0x00000004)        
#define  EXTI_EMR_MR3                        ((uint32_t)0x00000008)        
#define  EXTI_EMR_MR4                        ((uint32_t)0x00000010)        
#define  EXTI_EMR_MR5                        ((uint32_t)0x00000020)        
#define  EXTI_EMR_MR6                        ((uint32_t)0x00000040)        
#define  EXTI_EMR_MR7                        ((uint32_t)0x00000080)        
#define  EXTI_EMR_MR8                        ((uint32_t)0x00000100)        
#define  EXTI_EMR_MR9                        ((uint32_t)0x00000200)        
#define  EXTI_EMR_MR10                       ((uint32_t)0x00000400)        
#define  EXTI_EMR_MR11                       ((uint32_t)0x00000800)        
#define  EXTI_EMR_MR12                       ((uint32_t)0x00001000)        
#define  EXTI_EMR_MR13                       ((uint32_t)0x00002000)        
#define  EXTI_EMR_MR14                       ((uint32_t)0x00004000)        
#define  EXTI_EMR_MR15                       ((uint32_t)0x00008000)        
#define  EXTI_EMR_MR16                       ((uint32_t)0x00010000)        
#define  EXTI_EMR_MR17                       ((uint32_t)0x00020000)        
#define  EXTI_EMR_MR18                       ((uint32_t)0x00040000)        
#define  EXTI_EMR_MR19                       ((uint32_t)0x00080000)        

#define  EXTI_RTSR_TR0                       ((uint32_t)0x00000001)        
#define  EXTI_RTSR_TR1                       ((uint32_t)0x00000002)        
#define  EXTI_RTSR_TR2                       ((uint32_t)0x00000004)        
#define  EXTI_RTSR_TR3                       ((uint32_t)0x00000008)        
#define  EXTI_RTSR_TR4                       ((uint32_t)0x00000010)        
#define  EXTI_RTSR_TR5                       ((uint32_t)0x00000020)        
#define  EXTI_RTSR_TR6                       ((uint32_t)0x00000040)        
#define  EXTI_RTSR_TR7                       ((uint32_t)0x00000080)        
#define  EXTI_RTSR_TR8                       ((uint32_t)0x00000100)        
#define  EXTI_RTSR_TR9                       ((uint32_t)0x00000200)        
#define  EXTI_RTSR_TR10                      ((uint32_t)0x00000400)        
#define  EXTI_RTSR_TR11                      ((uint32_t)0x00000800)        
#define  EXTI_RTSR_TR12                      ((uint32_t)0x00001000)        
#define  EXTI_RTSR_TR13                      ((uint32_t)0x00002000)        
#define  EXTI_RTSR_TR14                      ((uint32_t)0x00004000)        
#define  EXTI_RTSR_TR15                      ((uint32_t)0x00008000)        
#define  EXTI_RTSR_TR16                      ((uint32_t)0x00010000)        
#define  EXTI_RTSR_TR17                      ((uint32_t)0x00020000)        
#define  EXTI_RTSR_TR18                      ((uint32_t)0x00040000)        
#define  EXTI_RTSR_TR19                      ((uint32_t)0x00080000)        

#define  EXTI_FTSR_TR0                       ((uint32_t)0x00000001)        
#define  EXTI_FTSR_TR1                       ((uint32_t)0x00000002)        
#define  EXTI_FTSR_TR2                       ((uint32_t)0x00000004)        
#define  EXTI_FTSR_TR3                       ((uint32_t)0x00000008)        
#define  EXTI_FTSR_TR4                       ((uint32_t)0x00000010)        
#define  EXTI_FTSR_TR5                       ((uint32_t)0x00000020)        
#define  EXTI_FTSR_TR6                       ((uint32_t)0x00000040)        
#define  EXTI_FTSR_TR7                       ((uint32_t)0x00000080)        
#define  EXTI_FTSR_TR8                       ((uint32_t)0x00000100)        
#define  EXTI_FTSR_TR9                       ((uint32_t)0x00000200)        
#define  EXTI_FTSR_TR10                      ((uint32_t)0x00000400)        
#define  EXTI_FTSR_TR11                      ((uint32_t)0x00000800)        
#define  EXTI_FTSR_TR12                      ((uint32_t)0x00001000)        
#define  EXTI_FTSR_TR13                      ((uint32_t)0x00002000)        
#define  EXTI_FTSR_TR14                      ((uint32_t)0x00004000)        
#define  EXTI_FTSR_TR15                      ((uint32_t)0x00008000)        
#define  EXTI_FTSR_TR16                      ((uint32_t)0x00010000)        
#define  EXTI_FTSR_TR17                      ((uint32_t)0x00020000)        
#define  EXTI_FTSR_TR18                      ((uint32_t)0x00040000)        
#define  EXTI_FTSR_TR19                      ((uint32_t)0x00080000)        

#define  EXTI_SWIER_SWIER0                   ((uint32_t)0x00000001)        
#define  EXTI_SWIER_SWIER1                   ((uint32_t)0x00000002)        
#define  EXTI_SWIER_SWIER2                   ((uint32_t)0x00000004)        
#define  EXTI_SWIER_SWIER3                   ((uint32_t)0x00000008)        
#define  EXTI_SWIER_SWIER4                   ((uint32_t)0x00000010)        
#define  EXTI_SWIER_SWIER5                   ((uint32_t)0x00000020)        
#define  EXTI_SWIER_SWIER6                   ((uint32_t)0x00000040)        
#define  EXTI_SWIER_SWIER7                   ((uint32_t)0x00000080)        
#define  EXTI_SWIER_SWIER8                   ((uint32_t)0x00000100)        
#define  EXTI_SWIER_SWIER9                   ((uint32_t)0x00000200)        
#define  EXTI_SWIER_SWIER10                  ((uint32_t)0x00000400)        
#define  EXTI_SWIER_SWIER11                  ((uint32_t)0x00000800)        
#define  EXTI_SWIER_SWIER12                  ((uint32_t)0x00001000)        
#define  EXTI_SWIER_SWIER13                  ((uint32_t)0x00002000)        
#define  EXTI_SWIER_SWIER14                  ((uint32_t)0x00004000)        
#define  EXTI_SWIER_SWIER15                  ((uint32_t)0x00008000)        
#define  EXTI_SWIER_SWIER16                  ((uint32_t)0x00010000)        
#define  EXTI_SWIER_SWIER17                  ((uint32_t)0x00020000)        
#define  EXTI_SWIER_SWIER18                  ((uint32_t)0x00040000)        
#define  EXTI_SWIER_SWIER19                  ((uint32_t)0x00080000)        

#define  EXTI_PR_PR0                         ((uint32_t)0x00000001)        
#define  EXTI_PR_PR1                         ((uint32_t)0x00000002)        
#define  EXTI_PR_PR2                         ((uint32_t)0x00000004)        
#define  EXTI_PR_PR3                         ((uint32_t)0x00000008)        
#define  EXTI_PR_PR4                         ((uint32_t)0x00000010)        
#define  EXTI_PR_PR5                         ((uint32_t)0x00000020)        
#define  EXTI_PR_PR6                         ((uint32_t)0x00000040)        
#define  EXTI_PR_PR7                         ((uint32_t)0x00000080)        
#define  EXTI_PR_PR8                         ((uint32_t)0x00000100)        
#define  EXTI_PR_PR9                         ((uint32_t)0x00000200)        
#define  EXTI_PR_PR10                        ((uint32_t)0x00000400)        
#define  EXTI_PR_PR11                        ((uint32_t)0x00000800)        
#define  EXTI_PR_PR12                        ((uint32_t)0x00001000)        
#define  EXTI_PR_PR13                        ((uint32_t)0x00002000)        
#define  EXTI_PR_PR14                        ((uint32_t)0x00004000)        
#define  EXTI_PR_PR15                        ((uint32_t)0x00008000)        
#define  EXTI_PR_PR16                        ((uint32_t)0x00010000)        
#define  EXTI_PR_PR17                        ((uint32_t)0x00020000)        
#define  EXTI_PR_PR18                        ((uint32_t)0x00040000)        
#define  EXTI_PR_PR19                        ((uint32_t)0x00080000)        

#define FLASH_ACR_LATENCY                    ((uint32_t)0x0000000F)
#define FLASH_ACR_LATENCY_0WS                ((uint32_t)0x00000000)
#define FLASH_ACR_LATENCY_1WS                ((uint32_t)0x00000001)
#define FLASH_ACR_LATENCY_2WS                ((uint32_t)0x00000002)
#define FLASH_ACR_LATENCY_3WS                ((uint32_t)0x00000003)
#define FLASH_ACR_LATENCY_4WS                ((uint32_t)0x00000004)
#define FLASH_ACR_LATENCY_5WS                ((uint32_t)0x00000005)
#define FLASH_ACR_LATENCY_6WS                ((uint32_t)0x00000006)
#define FLASH_ACR_LATENCY_7WS                ((uint32_t)0x00000007)
#define FLASH_ACR_LATENCY_8WS                ((uint32_t)0x00000008)
#define FLASH_ACR_LATENCY_9WS                ((uint32_t)0x00000009)
#define FLASH_ACR_LATENCY_10WS               ((uint32_t)0x0000000A)
#define FLASH_ACR_LATENCY_11WS               ((uint32_t)0x0000000B)
#define FLASH_ACR_LATENCY_12WS               ((uint32_t)0x0000000C)
#define FLASH_ACR_LATENCY_13WS               ((uint32_t)0x0000000D)
#define FLASH_ACR_LATENCY_14WS               ((uint32_t)0x0000000E)
#define FLASH_ACR_LATENCY_15WS               ((uint32_t)0x0000000F)

#define FLASH_ACR_PRFTEN                     ((uint32_t)0x00000100)
#define FLASH_ACR_ICEN                       ((uint32_t)0x00000200)
#define FLASH_ACR_DCEN                       ((uint32_t)0x00000400)
#define FLASH_ACR_ICRST                      ((uint32_t)0x00000800)
#define FLASH_ACR_DCRST                      ((uint32_t)0x00001000)
#define FLASH_ACR_BYTE0_ADDRESS              ((uint32_t)0x40023C00)
#define FLASH_ACR_BYTE2_ADDRESS              ((uint32_t)0x40023C03)

#define FLASH_SR_EOP                         ((uint32_t)0x00000001)
#define FLASH_SR_SOP                         ((uint32_t)0x00000002)
#define FLASH_SR_WRPERR                      ((uint32_t)0x00000010)
#define FLASH_SR_PGAERR                      ((uint32_t)0x00000020)
#define FLASH_SR_PGPERR                      ((uint32_t)0x00000040)
#define FLASH_SR_PGSERR                      ((uint32_t)0x00000080)
#define FLASH_SR_BSY                         ((uint32_t)0x00010000)

#define FLASH_CR_PG                          ((uint32_t)0x00000001)
#define FLASH_CR_SER                         ((uint32_t)0x00000002)
#define FLASH_CR_MER                         ((uint32_t)0x00000004)
#define FLASH_CR_MER1                        FLASH_CR_MER
#define FLASH_CR_SNB                         ((uint32_t)0x000000F8)
#define FLASH_CR_SNB_0                       ((uint32_t)0x00000008)
#define FLASH_CR_SNB_1                       ((uint32_t)0x00000010)
#define FLASH_CR_SNB_2                       ((uint32_t)0x00000020)
#define FLASH_CR_SNB_3                       ((uint32_t)0x00000040)
#define FLASH_CR_SNB_4                       ((uint32_t)0x00000040)
#define FLASH_CR_PSIZE                       ((uint32_t)0x00000300)
#define FLASH_CR_PSIZE_0                     ((uint32_t)0x00000100)
#define FLASH_CR_PSIZE_1                     ((uint32_t)0x00000200)
#define FLASH_CR_MER2                        ((uint32_t)0x00008000)
#define FLASH_CR_STRT                        ((uint32_t)0x00010000)
#define FLASH_CR_EOPIE                       ((uint32_t)0x01000000)
#define FLASH_CR_LOCK                        ((uint32_t)0x80000000)

#define FLASH_OPTCR_OPTLOCK                 ((uint32_t)0x00000001)
#define FLASH_OPTCR_OPTSTRT                 ((uint32_t)0x00000002)
#define FLASH_OPTCR_BOR_LEV_0               ((uint32_t)0x00000004)
#define FLASH_OPTCR_BOR_LEV_1               ((uint32_t)0x00000008)
#define FLASH_OPTCR_BOR_LEV                 ((uint32_t)0x0000000C)
#define FLASH_OPTCR_BFB2                    ((uint32_t)0x00000010)

#define FLASH_OPTCR_WDG_SW                  ((uint32_t)0x00000020)
#define FLASH_OPTCR_nRST_STOP               ((uint32_t)0x00000040)
#define FLASH_OPTCR_nRST_STDBY              ((uint32_t)0x00000080)
#define FLASH_OPTCR_RDP                     ((uint32_t)0x0000FF00)
#define FLASH_OPTCR_RDP_0                   ((uint32_t)0x00000100)
#define FLASH_OPTCR_RDP_1                   ((uint32_t)0x00000200)
#define FLASH_OPTCR_RDP_2                   ((uint32_t)0x00000400)
#define FLASH_OPTCR_RDP_3                   ((uint32_t)0x00000800)
#define FLASH_OPTCR_RDP_4                   ((uint32_t)0x00001000)
#define FLASH_OPTCR_RDP_5                   ((uint32_t)0x00002000)
#define FLASH_OPTCR_RDP_6                   ((uint32_t)0x00004000)
#define FLASH_OPTCR_RDP_7                   ((uint32_t)0x00008000)
#define FLASH_OPTCR_nWRP                    ((uint32_t)0x0FFF0000)
#define FLASH_OPTCR_nWRP_0                  ((uint32_t)0x00010000)
#define FLASH_OPTCR_nWRP_1                  ((uint32_t)0x00020000)
#define FLASH_OPTCR_nWRP_2                  ((uint32_t)0x00040000)
#define FLASH_OPTCR_nWRP_3                  ((uint32_t)0x00080000)
#define FLASH_OPTCR_nWRP_4                  ((uint32_t)0x00100000)
#define FLASH_OPTCR_nWRP_5                  ((uint32_t)0x00200000)
#define FLASH_OPTCR_nWRP_6                  ((uint32_t)0x00400000)
#define FLASH_OPTCR_nWRP_7                  ((uint32_t)0x00800000)
#define FLASH_OPTCR_nWRP_8                  ((uint32_t)0x01000000)
#define FLASH_OPTCR_nWRP_9                  ((uint32_t)0x02000000)
#define FLASH_OPTCR_nWRP_10                 ((uint32_t)0x04000000)
#define FLASH_OPTCR_nWRP_11                 ((uint32_t)0x08000000)

#define FLASH_OPTCR_DB1M                    ((uint32_t)0x40000000) 
#define FLASH_OPTCR_SPRMOD                  ((uint32_t)0x80000000) 
                                             

#define FLASH_OPTCR1_nWRP                    ((uint32_t)0x0FFF0000)
#define FLASH_OPTCR1_nWRP_0                  ((uint32_t)0x00010000)
#define FLASH_OPTCR1_nWRP_1                  ((uint32_t)0x00020000)
#define FLASH_OPTCR1_nWRP_2                  ((uint32_t)0x00040000)
#define FLASH_OPTCR1_nWRP_3                  ((uint32_t)0x00080000)
#define FLASH_OPTCR1_nWRP_4                  ((uint32_t)0x00100000)
#define FLASH_OPTCR1_nWRP_5                  ((uint32_t)0x00200000)
#define FLASH_OPTCR1_nWRP_6                  ((uint32_t)0x00400000)
#define FLASH_OPTCR1_nWRP_7                  ((uint32_t)0x00800000)
#define FLASH_OPTCR1_nWRP_8                  ((uint32_t)0x01000000)
#define FLASH_OPTCR1_nWRP_9                  ((uint32_t)0x02000000)
#define FLASH_OPTCR1_nWRP_10                 ((uint32_t)0x04000000)
#define FLASH_OPTCR1_nWRP_11                 ((uint32_t)0x08000000)

#if defined (STM32F40_41xxx)

#define  FSMC_BCR1_MBKEN                     ((uint32_t)0x00000001)        
#define  FSMC_BCR1_MUXEN                     ((uint32_t)0x00000002)        

#define  FSMC_BCR1_MTYP                      ((uint32_t)0x0000000C)        
#define  FSMC_BCR1_MTYP_0                    ((uint32_t)0x00000004)        
#define  FSMC_BCR1_MTYP_1                    ((uint32_t)0x00000008)        

#define  FSMC_BCR1_MWID                      ((uint32_t)0x00000030)        
#define  FSMC_BCR1_MWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_BCR1_MWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_BCR1_FACCEN                    ((uint32_t)0x00000040)        
#define  FSMC_BCR1_BURSTEN                   ((uint32_t)0x00000100)        
#define  FSMC_BCR1_WAITPOL                   ((uint32_t)0x00000200)        
#define  FSMC_BCR1_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FSMC_BCR1_WAITCFG                   ((uint32_t)0x00000800)        
#define  FSMC_BCR1_WREN                      ((uint32_t)0x00001000)        
#define  FSMC_BCR1_WAITEN                    ((uint32_t)0x00002000)        
#define  FSMC_BCR1_EXTMOD                    ((uint32_t)0x00004000)        
#define  FSMC_BCR1_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FSMC_BCR1_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FSMC_BCR2_MBKEN                     ((uint32_t)0x00000001)        
#define  FSMC_BCR2_MUXEN                     ((uint32_t)0x00000002)        

#define  FSMC_BCR2_MTYP                      ((uint32_t)0x0000000C)        
#define  FSMC_BCR2_MTYP_0                    ((uint32_t)0x00000004)        
#define  FSMC_BCR2_MTYP_1                    ((uint32_t)0x00000008)        

#define  FSMC_BCR2_MWID                      ((uint32_t)0x00000030)        
#define  FSMC_BCR2_MWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_BCR2_MWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_BCR2_FACCEN                    ((uint32_t)0x00000040)        
#define  FSMC_BCR2_BURSTEN                   ((uint32_t)0x00000100)        
#define  FSMC_BCR2_WAITPOL                   ((uint32_t)0x00000200)        
#define  FSMC_BCR2_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FSMC_BCR2_WAITCFG                   ((uint32_t)0x00000800)        
#define  FSMC_BCR2_WREN                      ((uint32_t)0x00001000)        
#define  FSMC_BCR2_WAITEN                    ((uint32_t)0x00002000)        
#define  FSMC_BCR2_EXTMOD                    ((uint32_t)0x00004000)        
#define  FSMC_BCR2_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FSMC_BCR2_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FSMC_BCR3_MBKEN                     ((uint32_t)0x00000001)        
#define  FSMC_BCR3_MUXEN                     ((uint32_t)0x00000002)        

#define  FSMC_BCR3_MTYP                      ((uint32_t)0x0000000C)        
#define  FSMC_BCR3_MTYP_0                    ((uint32_t)0x00000004)        
#define  FSMC_BCR3_MTYP_1                    ((uint32_t)0x00000008)        

#define  FSMC_BCR3_MWID                      ((uint32_t)0x00000030)        
#define  FSMC_BCR3_MWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_BCR3_MWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_BCR3_FACCEN                    ((uint32_t)0x00000040)        
#define  FSMC_BCR3_BURSTEN                   ((uint32_t)0x00000100)        
#define  FSMC_BCR3_WAITPOL                   ((uint32_t)0x00000200)        
#define  FSMC_BCR3_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FSMC_BCR3_WAITCFG                   ((uint32_t)0x00000800)        
#define  FSMC_BCR3_WREN                      ((uint32_t)0x00001000)        
#define  FSMC_BCR3_WAITEN                    ((uint32_t)0x00002000)        
#define  FSMC_BCR3_EXTMOD                    ((uint32_t)0x00004000)        
#define  FSMC_BCR3_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FSMC_BCR3_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FSMC_BCR4_MBKEN                     ((uint32_t)0x00000001)        
#define  FSMC_BCR4_MUXEN                     ((uint32_t)0x00000002)        

#define  FSMC_BCR4_MTYP                      ((uint32_t)0x0000000C)        
#define  FSMC_BCR4_MTYP_0                    ((uint32_t)0x00000004)        
#define  FSMC_BCR4_MTYP_1                    ((uint32_t)0x00000008)        

#define  FSMC_BCR4_MWID                      ((uint32_t)0x00000030)        
#define  FSMC_BCR4_MWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_BCR4_MWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_BCR4_FACCEN                    ((uint32_t)0x00000040)        
#define  FSMC_BCR4_BURSTEN                   ((uint32_t)0x00000100)        
#define  FSMC_BCR4_WAITPOL                   ((uint32_t)0x00000200)        
#define  FSMC_BCR4_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FSMC_BCR4_WAITCFG                   ((uint32_t)0x00000800)        
#define  FSMC_BCR4_WREN                      ((uint32_t)0x00001000)        
#define  FSMC_BCR4_WAITEN                    ((uint32_t)0x00002000)        
#define  FSMC_BCR4_EXTMOD                    ((uint32_t)0x00004000)        
#define  FSMC_BCR4_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FSMC_BCR4_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FSMC_BTR1_ADDSET                    ((uint32_t)0x0000000F)        
#define  FSMC_BTR1_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FSMC_BTR1_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FSMC_BTR1_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FSMC_BTR1_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FSMC_BTR1_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FSMC_BTR1_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FSMC_BTR1_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FSMC_BTR1_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FSMC_BTR1_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FSMC_BTR1_DATAST                    ((uint32_t)0x0000FF00)        
#define  FSMC_BTR1_DATAST_0                  ((uint32_t)0x00000100)        
#define  FSMC_BTR1_DATAST_1                  ((uint32_t)0x00000200)        
#define  FSMC_BTR1_DATAST_2                  ((uint32_t)0x00000400)        
#define  FSMC_BTR1_DATAST_3                  ((uint32_t)0x00000800)        

#define  FSMC_BTR1_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FSMC_BTR1_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FSMC_BTR1_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FSMC_BTR1_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FSMC_BTR1_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FSMC_BTR1_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FSMC_BTR1_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FSMC_BTR1_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FSMC_BTR1_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FSMC_BTR1_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FSMC_BTR1_DATLAT                    ((uint32_t)0x0F000000)        
#define  FSMC_BTR1_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FSMC_BTR1_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FSMC_BTR1_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FSMC_BTR1_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FSMC_BTR1_ACCMOD                    ((uint32_t)0x30000000)        
#define  FSMC_BTR1_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FSMC_BTR1_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FSMC_BTR2_ADDSET                    ((uint32_t)0x0000000F)        
#define  FSMC_BTR2_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FSMC_BTR2_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FSMC_BTR2_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FSMC_BTR2_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FSMC_BTR2_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FSMC_BTR2_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FSMC_BTR2_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FSMC_BTR2_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FSMC_BTR2_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FSMC_BTR2_DATAST                    ((uint32_t)0x0000FF00)        
#define  FSMC_BTR2_DATAST_0                  ((uint32_t)0x00000100)        
#define  FSMC_BTR2_DATAST_1                  ((uint32_t)0x00000200)        
#define  FSMC_BTR2_DATAST_2                  ((uint32_t)0x00000400)        
#define  FSMC_BTR2_DATAST_3                  ((uint32_t)0x00000800)        

#define  FSMC_BTR2_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FSMC_BTR2_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FSMC_BTR2_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FSMC_BTR2_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FSMC_BTR2_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FSMC_BTR2_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FSMC_BTR2_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FSMC_BTR2_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FSMC_BTR2_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FSMC_BTR2_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FSMC_BTR2_DATLAT                    ((uint32_t)0x0F000000)        
#define  FSMC_BTR2_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FSMC_BTR2_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FSMC_BTR2_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FSMC_BTR2_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FSMC_BTR2_ACCMOD                    ((uint32_t)0x30000000)        
#define  FSMC_BTR2_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FSMC_BTR2_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FSMC_BTR3_ADDSET                    ((uint32_t)0x0000000F)        
#define  FSMC_BTR3_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FSMC_BTR3_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FSMC_BTR3_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FSMC_BTR3_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FSMC_BTR3_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FSMC_BTR3_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FSMC_BTR3_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FSMC_BTR3_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FSMC_BTR3_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FSMC_BTR3_DATAST                    ((uint32_t)0x0000FF00)        
#define  FSMC_BTR3_DATAST_0                  ((uint32_t)0x00000100)        
#define  FSMC_BTR3_DATAST_1                  ((uint32_t)0x00000200)        
#define  FSMC_BTR3_DATAST_2                  ((uint32_t)0x00000400)        
#define  FSMC_BTR3_DATAST_3                  ((uint32_t)0x00000800)        

#define  FSMC_BTR3_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FSMC_BTR3_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FSMC_BTR3_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FSMC_BTR3_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FSMC_BTR3_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FSMC_BTR3_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FSMC_BTR3_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FSMC_BTR3_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FSMC_BTR3_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FSMC_BTR3_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FSMC_BTR3_DATLAT                    ((uint32_t)0x0F000000)        
#define  FSMC_BTR3_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FSMC_BTR3_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FSMC_BTR3_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FSMC_BTR3_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FSMC_BTR3_ACCMOD                    ((uint32_t)0x30000000)        
#define  FSMC_BTR3_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FSMC_BTR3_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FSMC_BTR4_ADDSET                    ((uint32_t)0x0000000F)        
#define  FSMC_BTR4_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FSMC_BTR4_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FSMC_BTR4_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FSMC_BTR4_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FSMC_BTR4_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FSMC_BTR4_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FSMC_BTR4_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FSMC_BTR4_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FSMC_BTR4_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FSMC_BTR4_DATAST                    ((uint32_t)0x0000FF00)        
#define  FSMC_BTR4_DATAST_0                  ((uint32_t)0x00000100)        
#define  FSMC_BTR4_DATAST_1                  ((uint32_t)0x00000200)        
#define  FSMC_BTR4_DATAST_2                  ((uint32_t)0x00000400)        
#define  FSMC_BTR4_DATAST_3                  ((uint32_t)0x00000800)        

#define  FSMC_BTR4_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FSMC_BTR4_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FSMC_BTR4_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FSMC_BTR4_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FSMC_BTR4_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FSMC_BTR4_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FSMC_BTR4_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FSMC_BTR4_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FSMC_BTR4_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FSMC_BTR4_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FSMC_BTR4_DATLAT                    ((uint32_t)0x0F000000)        
#define  FSMC_BTR4_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FSMC_BTR4_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FSMC_BTR4_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FSMC_BTR4_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FSMC_BTR4_ACCMOD                    ((uint32_t)0x30000000)        
#define  FSMC_BTR4_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FSMC_BTR4_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FSMC_BWTR1_ADDSET                   ((uint32_t)0x0000000F)        
#define  FSMC_BWTR1_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FSMC_BWTR1_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FSMC_BWTR1_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FSMC_BWTR1_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FSMC_BWTR1_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FSMC_BWTR1_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FSMC_BWTR1_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FSMC_BWTR1_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FSMC_BWTR1_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FSMC_BWTR1_DATAST                   ((uint32_t)0x0000FF00)        
#define  FSMC_BWTR1_DATAST_0                 ((uint32_t)0x00000100)        
#define  FSMC_BWTR1_DATAST_1                 ((uint32_t)0x00000200)        
#define  FSMC_BWTR1_DATAST_2                 ((uint32_t)0x00000400)        
#define  FSMC_BWTR1_DATAST_3                 ((uint32_t)0x00000800)        

#define  FSMC_BWTR1_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FSMC_BWTR1_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FSMC_BWTR1_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FSMC_BWTR1_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FSMC_BWTR1_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FSMC_BWTR1_DATLAT                   ((uint32_t)0x0F000000)        
#define  FSMC_BWTR1_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FSMC_BWTR1_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FSMC_BWTR1_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FSMC_BWTR1_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FSMC_BWTR1_ACCMOD                   ((uint32_t)0x30000000)        
#define  FSMC_BWTR1_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FSMC_BWTR1_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FSMC_BWTR2_ADDSET                   ((uint32_t)0x0000000F)        
#define  FSMC_BWTR2_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FSMC_BWTR2_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FSMC_BWTR2_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FSMC_BWTR2_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FSMC_BWTR2_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FSMC_BWTR2_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FSMC_BWTR2_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FSMC_BWTR2_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FSMC_BWTR2_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FSMC_BWTR2_DATAST                   ((uint32_t)0x0000FF00)        
#define  FSMC_BWTR2_DATAST_0                 ((uint32_t)0x00000100)        
#define  FSMC_BWTR2_DATAST_1                 ((uint32_t)0x00000200)        
#define  FSMC_BWTR2_DATAST_2                 ((uint32_t)0x00000400)        
#define  FSMC_BWTR2_DATAST_3                 ((uint32_t)0x00000800)        

#define  FSMC_BWTR2_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FSMC_BWTR2_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FSMC_BWTR2_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FSMC_BWTR2_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FSMC_BWTR2_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FSMC_BWTR2_DATLAT                   ((uint32_t)0x0F000000)        
#define  FSMC_BWTR2_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FSMC_BWTR2_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FSMC_BWTR2_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FSMC_BWTR2_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FSMC_BWTR2_ACCMOD                   ((uint32_t)0x30000000)        
#define  FSMC_BWTR2_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FSMC_BWTR2_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FSMC_BWTR3_ADDSET                   ((uint32_t)0x0000000F)        
#define  FSMC_BWTR3_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FSMC_BWTR3_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FSMC_BWTR3_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FSMC_BWTR3_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FSMC_BWTR3_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FSMC_BWTR3_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FSMC_BWTR3_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FSMC_BWTR3_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FSMC_BWTR3_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FSMC_BWTR3_DATAST                   ((uint32_t)0x0000FF00)        
#define  FSMC_BWTR3_DATAST_0                 ((uint32_t)0x00000100)        
#define  FSMC_BWTR3_DATAST_1                 ((uint32_t)0x00000200)        
#define  FSMC_BWTR3_DATAST_2                 ((uint32_t)0x00000400)        
#define  FSMC_BWTR3_DATAST_3                 ((uint32_t)0x00000800)        

#define  FSMC_BWTR3_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FSMC_BWTR3_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FSMC_BWTR3_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FSMC_BWTR3_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FSMC_BWTR3_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FSMC_BWTR3_DATLAT                   ((uint32_t)0x0F000000)        
#define  FSMC_BWTR3_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FSMC_BWTR3_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FSMC_BWTR3_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FSMC_BWTR3_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FSMC_BWTR3_ACCMOD                   ((uint32_t)0x30000000)        
#define  FSMC_BWTR3_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FSMC_BWTR3_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FSMC_BWTR4_ADDSET                   ((uint32_t)0x0000000F)        
#define  FSMC_BWTR4_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FSMC_BWTR4_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FSMC_BWTR4_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FSMC_BWTR4_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FSMC_BWTR4_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FSMC_BWTR4_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FSMC_BWTR4_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FSMC_BWTR4_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FSMC_BWTR4_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FSMC_BWTR4_DATAST                   ((uint32_t)0x0000FF00)        
#define  FSMC_BWTR4_DATAST_0                 ((uint32_t)0x00000100)        
#define  FSMC_BWTR4_DATAST_1                 ((uint32_t)0x00000200)        
#define  FSMC_BWTR4_DATAST_2                 ((uint32_t)0x00000400)        
#define  FSMC_BWTR4_DATAST_3                 ((uint32_t)0x00000800)        

#define  FSMC_BWTR4_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FSMC_BWTR4_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FSMC_BWTR4_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FSMC_BWTR4_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FSMC_BWTR4_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FSMC_BWTR4_DATLAT                   ((uint32_t)0x0F000000)        
#define  FSMC_BWTR4_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FSMC_BWTR4_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FSMC_BWTR4_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FSMC_BWTR4_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FSMC_BWTR4_ACCMOD                   ((uint32_t)0x30000000)        
#define  FSMC_BWTR4_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FSMC_BWTR4_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FSMC_PCR2_PWAITEN                   ((uint32_t)0x00000002)        
#define  FSMC_PCR2_PBKEN                     ((uint32_t)0x00000004)        
#define  FSMC_PCR2_PTYP                      ((uint32_t)0x00000008)        

#define  FSMC_PCR2_PWID                      ((uint32_t)0x00000030)        
#define  FSMC_PCR2_PWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_PCR2_PWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_PCR2_ECCEN                     ((uint32_t)0x00000040)        

#define  FSMC_PCR2_TCLR                      ((uint32_t)0x00001E00)        
#define  FSMC_PCR2_TCLR_0                    ((uint32_t)0x00000200)        
#define  FSMC_PCR2_TCLR_1                    ((uint32_t)0x00000400)        
#define  FSMC_PCR2_TCLR_2                    ((uint32_t)0x00000800)        
#define  FSMC_PCR2_TCLR_3                    ((uint32_t)0x00001000)        

#define  FSMC_PCR2_TAR                       ((uint32_t)0x0001E000)        
#define  FSMC_PCR2_TAR_0                     ((uint32_t)0x00002000)        
#define  FSMC_PCR2_TAR_1                     ((uint32_t)0x00004000)        
#define  FSMC_PCR2_TAR_2                     ((uint32_t)0x00008000)        
#define  FSMC_PCR2_TAR_3                     ((uint32_t)0x00010000)        

#define  FSMC_PCR2_ECCPS                     ((uint32_t)0x000E0000)        
#define  FSMC_PCR2_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FSMC_PCR2_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FSMC_PCR2_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FSMC_PCR3_PWAITEN                   ((uint32_t)0x00000002)        
#define  FSMC_PCR3_PBKEN                     ((uint32_t)0x00000004)        
#define  FSMC_PCR3_PTYP                      ((uint32_t)0x00000008)        

#define  FSMC_PCR3_PWID                      ((uint32_t)0x00000030)        
#define  FSMC_PCR3_PWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_PCR3_PWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_PCR3_ECCEN                     ((uint32_t)0x00000040)        

#define  FSMC_PCR3_TCLR                      ((uint32_t)0x00001E00)        
#define  FSMC_PCR3_TCLR_0                    ((uint32_t)0x00000200)        
#define  FSMC_PCR3_TCLR_1                    ((uint32_t)0x00000400)        
#define  FSMC_PCR3_TCLR_2                    ((uint32_t)0x00000800)        
#define  FSMC_PCR3_TCLR_3                    ((uint32_t)0x00001000)        

#define  FSMC_PCR3_TAR                       ((uint32_t)0x0001E000)        
#define  FSMC_PCR3_TAR_0                     ((uint32_t)0x00002000)        
#define  FSMC_PCR3_TAR_1                     ((uint32_t)0x00004000)        
#define  FSMC_PCR3_TAR_2                     ((uint32_t)0x00008000)        
#define  FSMC_PCR3_TAR_3                     ((uint32_t)0x00010000)        

#define  FSMC_PCR3_ECCPS                     ((uint32_t)0x000E0000)        
#define  FSMC_PCR3_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FSMC_PCR3_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FSMC_PCR3_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FSMC_PCR4_PWAITEN                   ((uint32_t)0x00000002)        
#define  FSMC_PCR4_PBKEN                     ((uint32_t)0x00000004)        
#define  FSMC_PCR4_PTYP                      ((uint32_t)0x00000008)        

#define  FSMC_PCR4_PWID                      ((uint32_t)0x00000030)        
#define  FSMC_PCR4_PWID_0                    ((uint32_t)0x00000010)        
#define  FSMC_PCR4_PWID_1                    ((uint32_t)0x00000020)        

#define  FSMC_PCR4_ECCEN                     ((uint32_t)0x00000040)        

#define  FSMC_PCR4_TCLR                      ((uint32_t)0x00001E00)        
#define  FSMC_PCR4_TCLR_0                    ((uint32_t)0x00000200)        
#define  FSMC_PCR4_TCLR_1                    ((uint32_t)0x00000400)        
#define  FSMC_PCR4_TCLR_2                    ((uint32_t)0x00000800)        
#define  FSMC_PCR4_TCLR_3                    ((uint32_t)0x00001000)        

#define  FSMC_PCR4_TAR                       ((uint32_t)0x0001E000)        
#define  FSMC_PCR4_TAR_0                     ((uint32_t)0x00002000)        
#define  FSMC_PCR4_TAR_1                     ((uint32_t)0x00004000)        
#define  FSMC_PCR4_TAR_2                     ((uint32_t)0x00008000)        
#define  FSMC_PCR4_TAR_3                     ((uint32_t)0x00010000)        

#define  FSMC_PCR4_ECCPS                     ((uint32_t)0x000E0000)        
#define  FSMC_PCR4_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FSMC_PCR4_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FSMC_PCR4_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FSMC_SR2_IRS                        ((uint8_t)0x01)               
#define  FSMC_SR2_ILS                        ((uint8_t)0x02)               
#define  FSMC_SR2_IFS                        ((uint8_t)0x04)               
#define  FSMC_SR2_IREN                       ((uint8_t)0x08)               
#define  FSMC_SR2_ILEN                       ((uint8_t)0x10)               
#define  FSMC_SR2_IFEN                       ((uint8_t)0x20)               
#define  FSMC_SR2_FEMPT                      ((uint8_t)0x40)               

#define  FSMC_SR3_IRS                        ((uint8_t)0x01)               
#define  FSMC_SR3_ILS                        ((uint8_t)0x02)               
#define  FSMC_SR3_IFS                        ((uint8_t)0x04)               
#define  FSMC_SR3_IREN                       ((uint8_t)0x08)               
#define  FSMC_SR3_ILEN                       ((uint8_t)0x10)               
#define  FSMC_SR3_IFEN                       ((uint8_t)0x20)               
#define  FSMC_SR3_FEMPT                      ((uint8_t)0x40)               

#define  FSMC_SR4_IRS                        ((uint8_t)0x01)               
#define  FSMC_SR4_ILS                        ((uint8_t)0x02)               
#define  FSMC_SR4_IFS                        ((uint8_t)0x04)               
#define  FSMC_SR4_IREN                       ((uint8_t)0x08)               
#define  FSMC_SR4_ILEN                       ((uint8_t)0x10)               
#define  FSMC_SR4_IFEN                       ((uint8_t)0x20)               
#define  FSMC_SR4_FEMPT                      ((uint8_t)0x40)               

#define  FSMC_PMEM2_MEMSET2                  ((uint32_t)0x000000FF)        
#define  FSMC_PMEM2_MEMSET2_0                ((uint32_t)0x00000001)        
#define  FSMC_PMEM2_MEMSET2_1                ((uint32_t)0x00000002)        
#define  FSMC_PMEM2_MEMSET2_2                ((uint32_t)0x00000004)        
#define  FSMC_PMEM2_MEMSET2_3                ((uint32_t)0x00000008)        
#define  FSMC_PMEM2_MEMSET2_4                ((uint32_t)0x00000010)        
#define  FSMC_PMEM2_MEMSET2_5                ((uint32_t)0x00000020)        
#define  FSMC_PMEM2_MEMSET2_6                ((uint32_t)0x00000040)        
#define  FSMC_PMEM2_MEMSET2_7                ((uint32_t)0x00000080)        

#define  FSMC_PMEM2_MEMWAIT2                 ((uint32_t)0x0000FF00)        
#define  FSMC_PMEM2_MEMWAIT2_0               ((uint32_t)0x00000100)        
#define  FSMC_PMEM2_MEMWAIT2_1               ((uint32_t)0x00000200)        
#define  FSMC_PMEM2_MEMWAIT2_2               ((uint32_t)0x00000400)        
#define  FSMC_PMEM2_MEMWAIT2_3               ((uint32_t)0x00000800)        
#define  FSMC_PMEM2_MEMWAIT2_4               ((uint32_t)0x00001000)        
#define  FSMC_PMEM2_MEMWAIT2_5               ((uint32_t)0x00002000)        
#define  FSMC_PMEM2_MEMWAIT2_6               ((uint32_t)0x00004000)        
#define  FSMC_PMEM2_MEMWAIT2_7               ((uint32_t)0x00008000)        

#define  FSMC_PMEM2_MEMHOLD2                 ((uint32_t)0x00FF0000)        
#define  FSMC_PMEM2_MEMHOLD2_0               ((uint32_t)0x00010000)        
#define  FSMC_PMEM2_MEMHOLD2_1               ((uint32_t)0x00020000)        
#define  FSMC_PMEM2_MEMHOLD2_2               ((uint32_t)0x00040000)        
#define  FSMC_PMEM2_MEMHOLD2_3               ((uint32_t)0x00080000)        
#define  FSMC_PMEM2_MEMHOLD2_4               ((uint32_t)0x00100000)        
#define  FSMC_PMEM2_MEMHOLD2_5               ((uint32_t)0x00200000)        
#define  FSMC_PMEM2_MEMHOLD2_6               ((uint32_t)0x00400000)        
#define  FSMC_PMEM2_MEMHOLD2_7               ((uint32_t)0x00800000)        

#define  FSMC_PMEM2_MEMHIZ2                  ((uint32_t)0xFF000000)        
#define  FSMC_PMEM2_MEMHIZ2_0                ((uint32_t)0x01000000)        
#define  FSMC_PMEM2_MEMHIZ2_1                ((uint32_t)0x02000000)        
#define  FSMC_PMEM2_MEMHIZ2_2                ((uint32_t)0x04000000)        
#define  FSMC_PMEM2_MEMHIZ2_3                ((uint32_t)0x08000000)        
#define  FSMC_PMEM2_MEMHIZ2_4                ((uint32_t)0x10000000)        
#define  FSMC_PMEM2_MEMHIZ2_5                ((uint32_t)0x20000000)        
#define  FSMC_PMEM2_MEMHIZ2_6                ((uint32_t)0x40000000)        
#define  FSMC_PMEM2_MEMHIZ2_7                ((uint32_t)0x80000000)        

#define  FSMC_PMEM3_MEMSET3                  ((uint32_t)0x000000FF)        
#define  FSMC_PMEM3_MEMSET3_0                ((uint32_t)0x00000001)        
#define  FSMC_PMEM3_MEMSET3_1                ((uint32_t)0x00000002)        
#define  FSMC_PMEM3_MEMSET3_2                ((uint32_t)0x00000004)        
#define  FSMC_PMEM3_MEMSET3_3                ((uint32_t)0x00000008)        
#define  FSMC_PMEM3_MEMSET3_4                ((uint32_t)0x00000010)        
#define  FSMC_PMEM3_MEMSET3_5                ((uint32_t)0x00000020)        
#define  FSMC_PMEM3_MEMSET3_6                ((uint32_t)0x00000040)        
#define  FSMC_PMEM3_MEMSET3_7                ((uint32_t)0x00000080)        

#define  FSMC_PMEM3_MEMWAIT3                 ((uint32_t)0x0000FF00)        
#define  FSMC_PMEM3_MEMWAIT3_0               ((uint32_t)0x00000100)        
#define  FSMC_PMEM3_MEMWAIT3_1               ((uint32_t)0x00000200)        
#define  FSMC_PMEM3_MEMWAIT3_2               ((uint32_t)0x00000400)        
#define  FSMC_PMEM3_MEMWAIT3_3               ((uint32_t)0x00000800)        
#define  FSMC_PMEM3_MEMWAIT3_4               ((uint32_t)0x00001000)        
#define  FSMC_PMEM3_MEMWAIT3_5               ((uint32_t)0x00002000)        
#define  FSMC_PMEM3_MEMWAIT3_6               ((uint32_t)0x00004000)        
#define  FSMC_PMEM3_MEMWAIT3_7               ((uint32_t)0x00008000)        

#define  FSMC_PMEM3_MEMHOLD3                 ((uint32_t)0x00FF0000)        
#define  FSMC_PMEM3_MEMHOLD3_0               ((uint32_t)0x00010000)        
#define  FSMC_PMEM3_MEMHOLD3_1               ((uint32_t)0x00020000)        
#define  FSMC_PMEM3_MEMHOLD3_2               ((uint32_t)0x00040000)        
#define  FSMC_PMEM3_MEMHOLD3_3               ((uint32_t)0x00080000)        
#define  FSMC_PMEM3_MEMHOLD3_4               ((uint32_t)0x00100000)        
#define  FSMC_PMEM3_MEMHOLD3_5               ((uint32_t)0x00200000)        
#define  FSMC_PMEM3_MEMHOLD3_6               ((uint32_t)0x00400000)        
#define  FSMC_PMEM3_MEMHOLD3_7               ((uint32_t)0x00800000)        

#define  FSMC_PMEM3_MEMHIZ3                  ((uint32_t)0xFF000000)        
#define  FSMC_PMEM3_MEMHIZ3_0                ((uint32_t)0x01000000)        
#define  FSMC_PMEM3_MEMHIZ3_1                ((uint32_t)0x02000000)        
#define  FSMC_PMEM3_MEMHIZ3_2                ((uint32_t)0x04000000)        
#define  FSMC_PMEM3_MEMHIZ3_3                ((uint32_t)0x08000000)        
#define  FSMC_PMEM3_MEMHIZ3_4                ((uint32_t)0x10000000)        
#define  FSMC_PMEM3_MEMHIZ3_5                ((uint32_t)0x20000000)        
#define  FSMC_PMEM3_MEMHIZ3_6                ((uint32_t)0x40000000)        
#define  FSMC_PMEM3_MEMHIZ3_7                ((uint32_t)0x80000000)        

#define  FSMC_PMEM4_MEMSET4                  ((uint32_t)0x000000FF)        
#define  FSMC_PMEM4_MEMSET4_0                ((uint32_t)0x00000001)        
#define  FSMC_PMEM4_MEMSET4_1                ((uint32_t)0x00000002)        
#define  FSMC_PMEM4_MEMSET4_2                ((uint32_t)0x00000004)        
#define  FSMC_PMEM4_MEMSET4_3                ((uint32_t)0x00000008)        
#define  FSMC_PMEM4_MEMSET4_4                ((uint32_t)0x00000010)        
#define  FSMC_PMEM4_MEMSET4_5                ((uint32_t)0x00000020)        
#define  FSMC_PMEM4_MEMSET4_6                ((uint32_t)0x00000040)        
#define  FSMC_PMEM4_MEMSET4_7                ((uint32_t)0x00000080)        

#define  FSMC_PMEM4_MEMWAIT4                 ((uint32_t)0x0000FF00)        
#define  FSMC_PMEM4_MEMWAIT4_0               ((uint32_t)0x00000100)        
#define  FSMC_PMEM4_MEMWAIT4_1               ((uint32_t)0x00000200)        
#define  FSMC_PMEM4_MEMWAIT4_2               ((uint32_t)0x00000400)        
#define  FSMC_PMEM4_MEMWAIT4_3               ((uint32_t)0x00000800)        
#define  FSMC_PMEM4_MEMWAIT4_4               ((uint32_t)0x00001000)        
#define  FSMC_PMEM4_MEMWAIT4_5               ((uint32_t)0x00002000)        
#define  FSMC_PMEM4_MEMWAIT4_6               ((uint32_t)0x00004000)        
#define  FSMC_PMEM4_MEMWAIT4_7               ((uint32_t)0x00008000)        

#define  FSMC_PMEM4_MEMHOLD4                 ((uint32_t)0x00FF0000)        
#define  FSMC_PMEM4_MEMHOLD4_0               ((uint32_t)0x00010000)        
#define  FSMC_PMEM4_MEMHOLD4_1               ((uint32_t)0x00020000)        
#define  FSMC_PMEM4_MEMHOLD4_2               ((uint32_t)0x00040000)        
#define  FSMC_PMEM4_MEMHOLD4_3               ((uint32_t)0x00080000)        
#define  FSMC_PMEM4_MEMHOLD4_4               ((uint32_t)0x00100000)        
#define  FSMC_PMEM4_MEMHOLD4_5               ((uint32_t)0x00200000)        
#define  FSMC_PMEM4_MEMHOLD4_6               ((uint32_t)0x00400000)        
#define  FSMC_PMEM4_MEMHOLD4_7               ((uint32_t)0x00800000)        

#define  FSMC_PMEM4_MEMHIZ4                  ((uint32_t)0xFF000000)        
#define  FSMC_PMEM4_MEMHIZ4_0                ((uint32_t)0x01000000)        
#define  FSMC_PMEM4_MEMHIZ4_1                ((uint32_t)0x02000000)        
#define  FSMC_PMEM4_MEMHIZ4_2                ((uint32_t)0x04000000)        
#define  FSMC_PMEM4_MEMHIZ4_3                ((uint32_t)0x08000000)        
#define  FSMC_PMEM4_MEMHIZ4_4                ((uint32_t)0x10000000)        
#define  FSMC_PMEM4_MEMHIZ4_5                ((uint32_t)0x20000000)        
#define  FSMC_PMEM4_MEMHIZ4_6                ((uint32_t)0x40000000)        
#define  FSMC_PMEM4_MEMHIZ4_7                ((uint32_t)0x80000000)        

#define  FSMC_PATT2_ATTSET2                  ((uint32_t)0x000000FF)        
#define  FSMC_PATT2_ATTSET2_0                ((uint32_t)0x00000001)        
#define  FSMC_PATT2_ATTSET2_1                ((uint32_t)0x00000002)        
#define  FSMC_PATT2_ATTSET2_2                ((uint32_t)0x00000004)        
#define  FSMC_PATT2_ATTSET2_3                ((uint32_t)0x00000008)        
#define  FSMC_PATT2_ATTSET2_4                ((uint32_t)0x00000010)        
#define  FSMC_PATT2_ATTSET2_5                ((uint32_t)0x00000020)        
#define  FSMC_PATT2_ATTSET2_6                ((uint32_t)0x00000040)        
#define  FSMC_PATT2_ATTSET2_7                ((uint32_t)0x00000080)        

#define  FSMC_PATT2_ATTWAIT2                 ((uint32_t)0x0000FF00)        
#define  FSMC_PATT2_ATTWAIT2_0               ((uint32_t)0x00000100)        
#define  FSMC_PATT2_ATTWAIT2_1               ((uint32_t)0x00000200)        
#define  FSMC_PATT2_ATTWAIT2_2               ((uint32_t)0x00000400)        
#define  FSMC_PATT2_ATTWAIT2_3               ((uint32_t)0x00000800)        
#define  FSMC_PATT2_ATTWAIT2_4               ((uint32_t)0x00001000)        
#define  FSMC_PATT2_ATTWAIT2_5               ((uint32_t)0x00002000)        
#define  FSMC_PATT2_ATTWAIT2_6               ((uint32_t)0x00004000)        
#define  FSMC_PATT2_ATTWAIT2_7               ((uint32_t)0x00008000)        

#define  FSMC_PATT2_ATTHOLD2                 ((uint32_t)0x00FF0000)        
#define  FSMC_PATT2_ATTHOLD2_0               ((uint32_t)0x00010000)        
#define  FSMC_PATT2_ATTHOLD2_1               ((uint32_t)0x00020000)        
#define  FSMC_PATT2_ATTHOLD2_2               ((uint32_t)0x00040000)        
#define  FSMC_PATT2_ATTHOLD2_3               ((uint32_t)0x00080000)        
#define  FSMC_PATT2_ATTHOLD2_4               ((uint32_t)0x00100000)        
#define  FSMC_PATT2_ATTHOLD2_5               ((uint32_t)0x00200000)        
#define  FSMC_PATT2_ATTHOLD2_6               ((uint32_t)0x00400000)        
#define  FSMC_PATT2_ATTHOLD2_7               ((uint32_t)0x00800000)        

#define  FSMC_PATT2_ATTHIZ2                  ((uint32_t)0xFF000000)        
#define  FSMC_PATT2_ATTHIZ2_0                ((uint32_t)0x01000000)        
#define  FSMC_PATT2_ATTHIZ2_1                ((uint32_t)0x02000000)        
#define  FSMC_PATT2_ATTHIZ2_2                ((uint32_t)0x04000000)        
#define  FSMC_PATT2_ATTHIZ2_3                ((uint32_t)0x08000000)        
#define  FSMC_PATT2_ATTHIZ2_4                ((uint32_t)0x10000000)        
#define  FSMC_PATT2_ATTHIZ2_5                ((uint32_t)0x20000000)        
#define  FSMC_PATT2_ATTHIZ2_6                ((uint32_t)0x40000000)        
#define  FSMC_PATT2_ATTHIZ2_7                ((uint32_t)0x80000000)        

#define  FSMC_PATT3_ATTSET3                  ((uint32_t)0x000000FF)        
#define  FSMC_PATT3_ATTSET3_0                ((uint32_t)0x00000001)        
#define  FSMC_PATT3_ATTSET3_1                ((uint32_t)0x00000002)        
#define  FSMC_PATT3_ATTSET3_2                ((uint32_t)0x00000004)        
#define  FSMC_PATT3_ATTSET3_3                ((uint32_t)0x00000008)        
#define  FSMC_PATT3_ATTSET3_4                ((uint32_t)0x00000010)        
#define  FSMC_PATT3_ATTSET3_5                ((uint32_t)0x00000020)        
#define  FSMC_PATT3_ATTSET3_6                ((uint32_t)0x00000040)        
#define  FSMC_PATT3_ATTSET3_7                ((uint32_t)0x00000080)        

#define  FSMC_PATT3_ATTWAIT3                 ((uint32_t)0x0000FF00)        
#define  FSMC_PATT3_ATTWAIT3_0               ((uint32_t)0x00000100)        
#define  FSMC_PATT3_ATTWAIT3_1               ((uint32_t)0x00000200)        
#define  FSMC_PATT3_ATTWAIT3_2               ((uint32_t)0x00000400)        
#define  FSMC_PATT3_ATTWAIT3_3               ((uint32_t)0x00000800)        
#define  FSMC_PATT3_ATTWAIT3_4               ((uint32_t)0x00001000)        
#define  FSMC_PATT3_ATTWAIT3_5               ((uint32_t)0x00002000)        
#define  FSMC_PATT3_ATTWAIT3_6               ((uint32_t)0x00004000)        
#define  FSMC_PATT3_ATTWAIT3_7               ((uint32_t)0x00008000)        

#define  FSMC_PATT3_ATTHOLD3                 ((uint32_t)0x00FF0000)        
#define  FSMC_PATT3_ATTHOLD3_0               ((uint32_t)0x00010000)        
#define  FSMC_PATT3_ATTHOLD3_1               ((uint32_t)0x00020000)        
#define  FSMC_PATT3_ATTHOLD3_2               ((uint32_t)0x00040000)        
#define  FSMC_PATT3_ATTHOLD3_3               ((uint32_t)0x00080000)        
#define  FSMC_PATT3_ATTHOLD3_4               ((uint32_t)0x00100000)        
#define  FSMC_PATT3_ATTHOLD3_5               ((uint32_t)0x00200000)        
#define  FSMC_PATT3_ATTHOLD3_6               ((uint32_t)0x00400000)        
#define  FSMC_PATT3_ATTHOLD3_7               ((uint32_t)0x00800000)        

#define  FSMC_PATT3_ATTHIZ3                  ((uint32_t)0xFF000000)        
#define  FSMC_PATT3_ATTHIZ3_0                ((uint32_t)0x01000000)        
#define  FSMC_PATT3_ATTHIZ3_1                ((uint32_t)0x02000000)        
#define  FSMC_PATT3_ATTHIZ3_2                ((uint32_t)0x04000000)        
#define  FSMC_PATT3_ATTHIZ3_3                ((uint32_t)0x08000000)        
#define  FSMC_PATT3_ATTHIZ3_4                ((uint32_t)0x10000000)        
#define  FSMC_PATT3_ATTHIZ3_5                ((uint32_t)0x20000000)        
#define  FSMC_PATT3_ATTHIZ3_6                ((uint32_t)0x40000000)        
#define  FSMC_PATT3_ATTHIZ3_7                ((uint32_t)0x80000000)        

#define  FSMC_PATT4_ATTSET4                  ((uint32_t)0x000000FF)        
#define  FSMC_PATT4_ATTSET4_0                ((uint32_t)0x00000001)        
#define  FSMC_PATT4_ATTSET4_1                ((uint32_t)0x00000002)        
#define  FSMC_PATT4_ATTSET4_2                ((uint32_t)0x00000004)        
#define  FSMC_PATT4_ATTSET4_3                ((uint32_t)0x00000008)        
#define  FSMC_PATT4_ATTSET4_4                ((uint32_t)0x00000010)        
#define  FSMC_PATT4_ATTSET4_5                ((uint32_t)0x00000020)        
#define  FSMC_PATT4_ATTSET4_6                ((uint32_t)0x00000040)        
#define  FSMC_PATT4_ATTSET4_7                ((uint32_t)0x00000080)        

#define  FSMC_PATT4_ATTWAIT4                 ((uint32_t)0x0000FF00)        
#define  FSMC_PATT4_ATTWAIT4_0               ((uint32_t)0x00000100)        
#define  FSMC_PATT4_ATTWAIT4_1               ((uint32_t)0x00000200)        
#define  FSMC_PATT4_ATTWAIT4_2               ((uint32_t)0x00000400)        
#define  FSMC_PATT4_ATTWAIT4_3               ((uint32_t)0x00000800)        
#define  FSMC_PATT4_ATTWAIT4_4               ((uint32_t)0x00001000)        
#define  FSMC_PATT4_ATTWAIT4_5               ((uint32_t)0x00002000)        
#define  FSMC_PATT4_ATTWAIT4_6               ((uint32_t)0x00004000)        
#define  FSMC_PATT4_ATTWAIT4_7               ((uint32_t)0x00008000)        

#define  FSMC_PATT4_ATTHOLD4                 ((uint32_t)0x00FF0000)        
#define  FSMC_PATT4_ATTHOLD4_0               ((uint32_t)0x00010000)        
#define  FSMC_PATT4_ATTHOLD4_1               ((uint32_t)0x00020000)        
#define  FSMC_PATT4_ATTHOLD4_2               ((uint32_t)0x00040000)        
#define  FSMC_PATT4_ATTHOLD4_3               ((uint32_t)0x00080000)        
#define  FSMC_PATT4_ATTHOLD4_4               ((uint32_t)0x00100000)        
#define  FSMC_PATT4_ATTHOLD4_5               ((uint32_t)0x00200000)        
#define  FSMC_PATT4_ATTHOLD4_6               ((uint32_t)0x00400000)        
#define  FSMC_PATT4_ATTHOLD4_7               ((uint32_t)0x00800000)        

#define  FSMC_PATT4_ATTHIZ4                  ((uint32_t)0xFF000000)        
#define  FSMC_PATT4_ATTHIZ4_0                ((uint32_t)0x01000000)        
#define  FSMC_PATT4_ATTHIZ4_1                ((uint32_t)0x02000000)        
#define  FSMC_PATT4_ATTHIZ4_2                ((uint32_t)0x04000000)        
#define  FSMC_PATT4_ATTHIZ4_3                ((uint32_t)0x08000000)        
#define  FSMC_PATT4_ATTHIZ4_4                ((uint32_t)0x10000000)        
#define  FSMC_PATT4_ATTHIZ4_5                ((uint32_t)0x20000000)        
#define  FSMC_PATT4_ATTHIZ4_6                ((uint32_t)0x40000000)        
#define  FSMC_PATT4_ATTHIZ4_7                ((uint32_t)0x80000000)        

#define  FSMC_PIO4_IOSET4                    ((uint32_t)0x000000FF)        
#define  FSMC_PIO4_IOSET4_0                  ((uint32_t)0x00000001)        
#define  FSMC_PIO4_IOSET4_1                  ((uint32_t)0x00000002)        
#define  FSMC_PIO4_IOSET4_2                  ((uint32_t)0x00000004)        
#define  FSMC_PIO4_IOSET4_3                  ((uint32_t)0x00000008)        
#define  FSMC_PIO4_IOSET4_4                  ((uint32_t)0x00000010)        
#define  FSMC_PIO4_IOSET4_5                  ((uint32_t)0x00000020)        
#define  FSMC_PIO4_IOSET4_6                  ((uint32_t)0x00000040)        
#define  FSMC_PIO4_IOSET4_7                  ((uint32_t)0x00000080)        

#define  FSMC_PIO4_IOWAIT4                   ((uint32_t)0x0000FF00)        
#define  FSMC_PIO4_IOWAIT4_0                 ((uint32_t)0x00000100)        
#define  FSMC_PIO4_IOWAIT4_1                 ((uint32_t)0x00000200)        
#define  FSMC_PIO4_IOWAIT4_2                 ((uint32_t)0x00000400)        
#define  FSMC_PIO4_IOWAIT4_3                 ((uint32_t)0x00000800)        
#define  FSMC_PIO4_IOWAIT4_4                 ((uint32_t)0x00001000)        
#define  FSMC_PIO4_IOWAIT4_5                 ((uint32_t)0x00002000)        
#define  FSMC_PIO4_IOWAIT4_6                 ((uint32_t)0x00004000)        
#define  FSMC_PIO4_IOWAIT4_7                 ((uint32_t)0x00008000)        

#define  FSMC_PIO4_IOHOLD4                   ((uint32_t)0x00FF0000)        
#define  FSMC_PIO4_IOHOLD4_0                 ((uint32_t)0x00010000)        
#define  FSMC_PIO4_IOHOLD4_1                 ((uint32_t)0x00020000)        
#define  FSMC_PIO4_IOHOLD4_2                 ((uint32_t)0x00040000)        
#define  FSMC_PIO4_IOHOLD4_3                 ((uint32_t)0x00080000)        
#define  FSMC_PIO4_IOHOLD4_4                 ((uint32_t)0x00100000)        
#define  FSMC_PIO4_IOHOLD4_5                 ((uint32_t)0x00200000)        
#define  FSMC_PIO4_IOHOLD4_6                 ((uint32_t)0x00400000)        
#define  FSMC_PIO4_IOHOLD4_7                 ((uint32_t)0x00800000)        

#define  FSMC_PIO4_IOHIZ4                    ((uint32_t)0xFF000000)        
#define  FSMC_PIO4_IOHIZ4_0                  ((uint32_t)0x01000000)        
#define  FSMC_PIO4_IOHIZ4_1                  ((uint32_t)0x02000000)        
#define  FSMC_PIO4_IOHIZ4_2                  ((uint32_t)0x04000000)        
#define  FSMC_PIO4_IOHIZ4_3                  ((uint32_t)0x08000000)        
#define  FSMC_PIO4_IOHIZ4_4                  ((uint32_t)0x10000000)        
#define  FSMC_PIO4_IOHIZ4_5                  ((uint32_t)0x20000000)        
#define  FSMC_PIO4_IOHIZ4_6                  ((uint32_t)0x40000000)        
#define  FSMC_PIO4_IOHIZ4_7                  ((uint32_t)0x80000000)        

#define  FSMC_ECCR2_ECC2                     ((uint32_t)0xFFFFFFFF)        

#define  FSMC_ECCR3_ECC3                     ((uint32_t)0xFFFFFFFF)        
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)

#define  FMC_BCR1_MBKEN                     ((uint32_t)0x00000001)        
#define  FMC_BCR1_MUXEN                     ((uint32_t)0x00000002)        

#define  FMC_BCR1_MTYP                      ((uint32_t)0x0000000C)        
#define  FMC_BCR1_MTYP_0                    ((uint32_t)0x00000004)        
#define  FMC_BCR1_MTYP_1                    ((uint32_t)0x00000008)        

#define  FMC_BCR1_MWID                      ((uint32_t)0x00000030)        
#define  FMC_BCR1_MWID_0                    ((uint32_t)0x00000010)        
#define  FMC_BCR1_MWID_1                    ((uint32_t)0x00000020)        

#define  FMC_BCR1_FACCEN                    ((uint32_t)0x00000040)        
#define  FMC_BCR1_BURSTEN                   ((uint32_t)0x00000100)        
#define  FMC_BCR1_WAITPOL                   ((uint32_t)0x00000200)        
#define  FMC_BCR1_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FMC_BCR1_WAITCFG                   ((uint32_t)0x00000800)        
#define  FMC_BCR1_WREN                      ((uint32_t)0x00001000)        
#define  FMC_BCR1_WAITEN                    ((uint32_t)0x00002000)        
#define  FMC_BCR1_EXTMOD                    ((uint32_t)0x00004000)        
#define  FMC_BCR1_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FMC_BCR1_CBURSTRW                  ((uint32_t)0x00080000)        
#define  FMC_BCR1_CCLKEN                    ((uint32_t)0x00100000)        

#define  FMC_BCR2_MBKEN                     ((uint32_t)0x00000001)        
#define  FMC_BCR2_MUXEN                     ((uint32_t)0x00000002)        

#define  FMC_BCR2_MTYP                      ((uint32_t)0x0000000C)        
#define  FMC_BCR2_MTYP_0                    ((uint32_t)0x00000004)        
#define  FMC_BCR2_MTYP_1                    ((uint32_t)0x00000008)        

#define  FMC_BCR2_MWID                      ((uint32_t)0x00000030)        
#define  FMC_BCR2_MWID_0                    ((uint32_t)0x00000010)        
#define  FMC_BCR2_MWID_1                    ((uint32_t)0x00000020)        

#define  FMC_BCR2_FACCEN                    ((uint32_t)0x00000040)        
#define  FMC_BCR2_BURSTEN                   ((uint32_t)0x00000100)        
#define  FMC_BCR2_WAITPOL                   ((uint32_t)0x00000200)        
#define  FMC_BCR2_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FMC_BCR2_WAITCFG                   ((uint32_t)0x00000800)        
#define  FMC_BCR2_WREN                      ((uint32_t)0x00001000)        
#define  FMC_BCR2_WAITEN                    ((uint32_t)0x00002000)        
#define  FMC_BCR2_EXTMOD                    ((uint32_t)0x00004000)        
#define  FMC_BCR2_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FMC_BCR2_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FMC_BCR3_MBKEN                     ((uint32_t)0x00000001)        
#define  FMC_BCR3_MUXEN                     ((uint32_t)0x00000002)        

#define  FMC_BCR3_MTYP                      ((uint32_t)0x0000000C)        
#define  FMC_BCR3_MTYP_0                    ((uint32_t)0x00000004)        
#define  FMC_BCR3_MTYP_1                    ((uint32_t)0x00000008)        

#define  FMC_BCR3_MWID                      ((uint32_t)0x00000030)        
#define  FMC_BCR3_MWID_0                    ((uint32_t)0x00000010)        
#define  FMC_BCR3_MWID_1                    ((uint32_t)0x00000020)        

#define  FMC_BCR3_FACCEN                    ((uint32_t)0x00000040)        
#define  FMC_BCR3_BURSTEN                   ((uint32_t)0x00000100)        
#define  FMC_BCR3_WAITPOL                   ((uint32_t)0x00000200)        
#define  FMC_BCR3_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FMC_BCR3_WAITCFG                   ((uint32_t)0x00000800)        
#define  FMC_BCR3_WREN                      ((uint32_t)0x00001000)        
#define  FMC_BCR3_WAITEN                    ((uint32_t)0x00002000)        
#define  FMC_BCR3_EXTMOD                    ((uint32_t)0x00004000)        
#define  FMC_BCR3_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FMC_BCR3_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FMC_BCR4_MBKEN                     ((uint32_t)0x00000001)        
#define  FMC_BCR4_MUXEN                     ((uint32_t)0x00000002)        

#define  FMC_BCR4_MTYP                      ((uint32_t)0x0000000C)        
#define  FMC_BCR4_MTYP_0                    ((uint32_t)0x00000004)        
#define  FMC_BCR4_MTYP_1                    ((uint32_t)0x00000008)        

#define  FMC_BCR4_MWID                      ((uint32_t)0x00000030)        
#define  FMC_BCR4_MWID_0                    ((uint32_t)0x00000010)        
#define  FMC_BCR4_MWID_1                    ((uint32_t)0x00000020)        

#define  FMC_BCR4_FACCEN                    ((uint32_t)0x00000040)        
#define  FMC_BCR4_BURSTEN                   ((uint32_t)0x00000100)        
#define  FMC_BCR4_WAITPOL                   ((uint32_t)0x00000200)        
#define  FMC_BCR4_WRAPMOD                   ((uint32_t)0x00000400)        
#define  FMC_BCR4_WAITCFG                   ((uint32_t)0x00000800)        
#define  FMC_BCR4_WREN                      ((uint32_t)0x00001000)        
#define  FMC_BCR4_WAITEN                    ((uint32_t)0x00002000)        
#define  FMC_BCR4_EXTMOD                    ((uint32_t)0x00004000)        
#define  FMC_BCR4_ASYNCWAIT                 ((uint32_t)0x00008000)        
#define  FMC_BCR4_CBURSTRW                  ((uint32_t)0x00080000)        

#define  FMC_BTR1_ADDSET                    ((uint32_t)0x0000000F)        
#define  FMC_BTR1_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FMC_BTR1_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FMC_BTR1_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FMC_BTR1_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FMC_BTR1_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FMC_BTR1_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FMC_BTR1_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FMC_BTR1_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FMC_BTR1_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FMC_BTR1_DATAST                    ((uint32_t)0x0000FF00)        
#define  FMC_BTR1_DATAST_0                  ((uint32_t)0x00000100)        
#define  FMC_BTR1_DATAST_1                  ((uint32_t)0x00000200)        
#define  FMC_BTR1_DATAST_2                  ((uint32_t)0x00000400)        
#define  FMC_BTR1_DATAST_3                  ((uint32_t)0x00000800)        
#define  FMC_BTR1_DATAST_4                  ((uint32_t)0x00001000)        
#define  FMC_BTR1_DATAST_5                  ((uint32_t)0x00002000)        
#define  FMC_BTR1_DATAST_6                  ((uint32_t)0x00004000)        
#define  FMC_BTR1_DATAST_7                  ((uint32_t)0x00008000)        

#define  FMC_BTR1_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FMC_BTR1_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FMC_BTR1_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FMC_BTR1_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FMC_BTR1_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FMC_BTR1_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FMC_BTR1_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FMC_BTR1_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FMC_BTR1_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FMC_BTR1_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FMC_BTR1_DATLAT                    ((uint32_t)0x0F000000)        
#define  FMC_BTR1_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FMC_BTR1_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FMC_BTR1_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FMC_BTR1_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FMC_BTR1_ACCMOD                    ((uint32_t)0x30000000)        
#define  FMC_BTR1_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FMC_BTR1_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FMC_BTR2_ADDSET                    ((uint32_t)0x0000000F)        
#define  FMC_BTR2_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FMC_BTR2_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FMC_BTR2_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FMC_BTR2_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FMC_BTR2_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FMC_BTR2_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FMC_BTR2_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FMC_BTR2_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FMC_BTR2_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FMC_BTR2_DATAST                    ((uint32_t)0x0000FF00)        
#define  FMC_BTR2_DATAST_0                  ((uint32_t)0x00000100)        
#define  FMC_BTR2_DATAST_1                  ((uint32_t)0x00000200)        
#define  FMC_BTR2_DATAST_2                  ((uint32_t)0x00000400)        
#define  FMC_BTR2_DATAST_3                  ((uint32_t)0x00000800)        
#define  FMC_BTR2_DATAST_4                  ((uint32_t)0x00001000)        
#define  FMC_BTR2_DATAST_5                  ((uint32_t)0x00002000)        
#define  FMC_BTR2_DATAST_6                  ((uint32_t)0x00004000)        
#define  FMC_BTR2_DATAST_7                  ((uint32_t)0x00008000)        

#define  FMC_BTR2_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FMC_BTR2_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FMC_BTR2_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FMC_BTR2_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FMC_BTR2_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FMC_BTR2_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FMC_BTR2_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FMC_BTR2_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FMC_BTR2_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FMC_BTR2_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FMC_BTR2_DATLAT                    ((uint32_t)0x0F000000)        
#define  FMC_BTR2_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FMC_BTR2_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FMC_BTR2_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FMC_BTR2_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FMC_BTR2_ACCMOD                    ((uint32_t)0x30000000)        
#define  FMC_BTR2_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FMC_BTR2_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FMC_BTR3_ADDSET                    ((uint32_t)0x0000000F)        
#define  FMC_BTR3_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FMC_BTR3_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FMC_BTR3_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FMC_BTR3_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FMC_BTR3_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FMC_BTR3_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FMC_BTR3_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FMC_BTR3_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FMC_BTR3_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FMC_BTR3_DATAST                    ((uint32_t)0x0000FF00)        
#define  FMC_BTR3_DATAST_0                  ((uint32_t)0x00000100)        
#define  FMC_BTR3_DATAST_1                  ((uint32_t)0x00000200)        
#define  FMC_BTR3_DATAST_2                  ((uint32_t)0x00000400)        
#define  FMC_BTR3_DATAST_3                  ((uint32_t)0x00000800)        
#define  FMC_BTR3_DATAST_4                  ((uint32_t)0x00001000)        
#define  FMC_BTR3_DATAST_5                  ((uint32_t)0x00002000)        
#define  FMC_BTR3_DATAST_6                  ((uint32_t)0x00004000)        
#define  FMC_BTR3_DATAST_7                  ((uint32_t)0x00008000)        

#define  FMC_BTR3_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FMC_BTR3_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FMC_BTR3_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FMC_BTR3_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FMC_BTR3_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FMC_BTR3_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FMC_BTR3_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FMC_BTR3_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FMC_BTR3_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FMC_BTR3_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FMC_BTR3_DATLAT                    ((uint32_t)0x0F000000)        
#define  FMC_BTR3_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FMC_BTR3_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FMC_BTR3_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FMC_BTR3_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FMC_BTR3_ACCMOD                    ((uint32_t)0x30000000)        
#define  FMC_BTR3_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FMC_BTR3_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FMC_BTR4_ADDSET                    ((uint32_t)0x0000000F)        
#define  FMC_BTR4_ADDSET_0                  ((uint32_t)0x00000001)        
#define  FMC_BTR4_ADDSET_1                  ((uint32_t)0x00000002)        
#define  FMC_BTR4_ADDSET_2                  ((uint32_t)0x00000004)        
#define  FMC_BTR4_ADDSET_3                  ((uint32_t)0x00000008)        

#define  FMC_BTR4_ADDHLD                    ((uint32_t)0x000000F0)        
#define  FMC_BTR4_ADDHLD_0                  ((uint32_t)0x00000010)        
#define  FMC_BTR4_ADDHLD_1                  ((uint32_t)0x00000020)        
#define  FMC_BTR4_ADDHLD_2                  ((uint32_t)0x00000040)        
#define  FMC_BTR4_ADDHLD_3                  ((uint32_t)0x00000080)        

#define  FMC_BTR4_DATAST                    ((uint32_t)0x0000FF00)        
#define  FMC_BTR4_DATAST_0                  ((uint32_t)0x00000100)        
#define  FMC_BTR4_DATAST_1                  ((uint32_t)0x00000200)        
#define  FMC_BTR4_DATAST_2                  ((uint32_t)0x00000400)        
#define  FMC_BTR4_DATAST_3                  ((uint32_t)0x00000800)        
#define  FMC_BTR4_DATAST_4                  ((uint32_t)0x00001000)        
#define  FMC_BTR4_DATAST_5                  ((uint32_t)0x00002000)        
#define  FMC_BTR4_DATAST_6                  ((uint32_t)0x00004000)        
#define  FMC_BTR4_DATAST_7                  ((uint32_t)0x00008000)        

#define  FMC_BTR4_BUSTURN                   ((uint32_t)0x000F0000)        
#define  FMC_BTR4_BUSTURN_0                 ((uint32_t)0x00010000)        
#define  FMC_BTR4_BUSTURN_1                 ((uint32_t)0x00020000)        
#define  FMC_BTR4_BUSTURN_2                 ((uint32_t)0x00040000)        
#define  FMC_BTR4_BUSTURN_3                 ((uint32_t)0x00080000)        

#define  FMC_BTR4_CLKDIV                    ((uint32_t)0x00F00000)        
#define  FMC_BTR4_CLKDIV_0                  ((uint32_t)0x00100000)        
#define  FMC_BTR4_CLKDIV_1                  ((uint32_t)0x00200000)        
#define  FMC_BTR4_CLKDIV_2                  ((uint32_t)0x00400000)        
#define  FMC_BTR4_CLKDIV_3                  ((uint32_t)0x00800000)        

#define  FMC_BTR4_DATLAT                    ((uint32_t)0x0F000000)        
#define  FMC_BTR4_DATLAT_0                  ((uint32_t)0x01000000)        
#define  FMC_BTR4_DATLAT_1                  ((uint32_t)0x02000000)        
#define  FMC_BTR4_DATLAT_2                  ((uint32_t)0x04000000)        
#define  FMC_BTR4_DATLAT_3                  ((uint32_t)0x08000000)        

#define  FMC_BTR4_ACCMOD                    ((uint32_t)0x30000000)        
#define  FMC_BTR4_ACCMOD_0                  ((uint32_t)0x10000000)        
#define  FMC_BTR4_ACCMOD_1                  ((uint32_t)0x20000000)        

#define  FMC_BWTR1_ADDSET                   ((uint32_t)0x0000000F)        
#define  FMC_BWTR1_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FMC_BWTR1_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FMC_BWTR1_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FMC_BWTR1_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FMC_BWTR1_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FMC_BWTR1_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FMC_BWTR1_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FMC_BWTR1_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FMC_BWTR1_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FMC_BWTR1_DATAST                   ((uint32_t)0x0000FF00)        
#define  FMC_BWTR1_DATAST_0                 ((uint32_t)0x00000100)        
#define  FMC_BWTR1_DATAST_1                 ((uint32_t)0x00000200)        
#define  FMC_BWTR1_DATAST_2                 ((uint32_t)0x00000400)        
#define  FMC_BWTR1_DATAST_3                 ((uint32_t)0x00000800)        
#define  FMC_BWTR1_DATAST_4                 ((uint32_t)0x00001000)        
#define  FMC_BWTR1_DATAST_5                 ((uint32_t)0x00002000)        
#define  FMC_BWTR1_DATAST_6                 ((uint32_t)0x00004000)        
#define  FMC_BWTR1_DATAST_7                 ((uint32_t)0x00008000)        

#define  FMC_BWTR1_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FMC_BWTR1_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FMC_BWTR1_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FMC_BWTR1_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FMC_BWTR1_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FMC_BWTR1_DATLAT                   ((uint32_t)0x0F000000)        
#define  FMC_BWTR1_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FMC_BWTR1_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FMC_BWTR1_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FMC_BWTR1_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FMC_BWTR1_ACCMOD                   ((uint32_t)0x30000000)        
#define  FMC_BWTR1_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FMC_BWTR1_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FMC_BWTR2_ADDSET                   ((uint32_t)0x0000000F)        
#define  FMC_BWTR2_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FMC_BWTR2_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FMC_BWTR2_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FMC_BWTR2_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FMC_BWTR2_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FMC_BWTR2_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FMC_BWTR2_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FMC_BWTR2_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FMC_BWTR2_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FMC_BWTR2_DATAST                   ((uint32_t)0x0000FF00)        
#define  FMC_BWTR2_DATAST_0                 ((uint32_t)0x00000100)        
#define  FMC_BWTR2_DATAST_1                 ((uint32_t)0x00000200)        
#define  FMC_BWTR2_DATAST_2                 ((uint32_t)0x00000400)        
#define  FMC_BWTR2_DATAST_3                 ((uint32_t)0x00000800)        
#define  FMC_BWTR2_DATAST_4                 ((uint32_t)0x00001000)        
#define  FMC_BWTR2_DATAST_5                 ((uint32_t)0x00002000)        
#define  FMC_BWTR2_DATAST_6                 ((uint32_t)0x00004000)        
#define  FMC_BWTR2_DATAST_7                 ((uint32_t)0x00008000)        

#define  FMC_BWTR2_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FMC_BWTR2_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FMC_BWTR2_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FMC_BWTR2_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FMC_BWTR2_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FMC_BWTR2_DATLAT                   ((uint32_t)0x0F000000)        
#define  FMC_BWTR2_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FMC_BWTR2_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FMC_BWTR2_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FMC_BWTR2_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FMC_BWTR2_ACCMOD                   ((uint32_t)0x30000000)        
#define  FMC_BWTR2_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FMC_BWTR2_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FMC_BWTR3_ADDSET                   ((uint32_t)0x0000000F)        
#define  FMC_BWTR3_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FMC_BWTR3_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FMC_BWTR3_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FMC_BWTR3_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FMC_BWTR3_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FMC_BWTR3_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FMC_BWTR3_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FMC_BWTR3_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FMC_BWTR3_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FMC_BWTR3_DATAST                   ((uint32_t)0x0000FF00)        
#define  FMC_BWTR3_DATAST_0                 ((uint32_t)0x00000100)        
#define  FMC_BWTR3_DATAST_1                 ((uint32_t)0x00000200)        
#define  FMC_BWTR3_DATAST_2                 ((uint32_t)0x00000400)        
#define  FMC_BWTR3_DATAST_3                 ((uint32_t)0x00000800)        
#define  FMC_BWTR3_DATAST_4                 ((uint32_t)0x00001000)        
#define  FMC_BWTR3_DATAST_5                 ((uint32_t)0x00002000)        
#define  FMC_BWTR3_DATAST_6                 ((uint32_t)0x00004000)        
#define  FMC_BWTR3_DATAST_7                 ((uint32_t)0x00008000)        

#define  FMC_BWTR3_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FMC_BWTR3_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FMC_BWTR3_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FMC_BWTR3_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FMC_BWTR3_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FMC_BWTR3_DATLAT                   ((uint32_t)0x0F000000)        
#define  FMC_BWTR3_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FMC_BWTR3_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FMC_BWTR3_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FMC_BWTR3_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FMC_BWTR3_ACCMOD                   ((uint32_t)0x30000000)        
#define  FMC_BWTR3_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FMC_BWTR3_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FMC_BWTR4_ADDSET                   ((uint32_t)0x0000000F)        
#define  FMC_BWTR4_ADDSET_0                 ((uint32_t)0x00000001)        
#define  FMC_BWTR4_ADDSET_1                 ((uint32_t)0x00000002)        
#define  FMC_BWTR4_ADDSET_2                 ((uint32_t)0x00000004)        
#define  FMC_BWTR4_ADDSET_3                 ((uint32_t)0x00000008)        

#define  FMC_BWTR4_ADDHLD                   ((uint32_t)0x000000F0)        
#define  FMC_BWTR4_ADDHLD_0                 ((uint32_t)0x00000010)        
#define  FMC_BWTR4_ADDHLD_1                 ((uint32_t)0x00000020)        
#define  FMC_BWTR4_ADDHLD_2                 ((uint32_t)0x00000040)        
#define  FMC_BWTR4_ADDHLD_3                 ((uint32_t)0x00000080)        

#define  FMC_BWTR4_DATAST                   ((uint32_t)0x0000FF00)        
#define  FMC_BWTR4_DATAST_0                 ((uint32_t)0x00000100)        
#define  FMC_BWTR4_DATAST_1                 ((uint32_t)0x00000200)        
#define  FMC_BWTR4_DATAST_2                 ((uint32_t)0x00000400)        
#define  FMC_BWTR4_DATAST_3                 ((uint32_t)0x00000800)        
#define  FMC_BWTR4_DATAST_4                 ((uint32_t)0x00001000)        
#define  FMC_BWTR4_DATAST_5                 ((uint32_t)0x00002000)        
#define  FMC_BWTR4_DATAST_6                 ((uint32_t)0x00004000)        
#define  FMC_BWTR4_DATAST_7                 ((uint32_t)0x00008000)        

#define  FMC_BWTR4_CLKDIV                   ((uint32_t)0x00F00000)        
#define  FMC_BWTR4_CLKDIV_0                 ((uint32_t)0x00100000)        
#define  FMC_BWTR4_CLKDIV_1                 ((uint32_t)0x00200000)        
#define  FMC_BWTR4_CLKDIV_2                 ((uint32_t)0x00400000)        
#define  FMC_BWTR4_CLKDIV_3                 ((uint32_t)0x00800000)        

#define  FMC_BWTR4_DATLAT                   ((uint32_t)0x0F000000)        
#define  FMC_BWTR4_DATLAT_0                 ((uint32_t)0x01000000)        
#define  FMC_BWTR4_DATLAT_1                 ((uint32_t)0x02000000)        
#define  FMC_BWTR4_DATLAT_2                 ((uint32_t)0x04000000)        
#define  FMC_BWTR4_DATLAT_3                 ((uint32_t)0x08000000)        

#define  FMC_BWTR4_ACCMOD                   ((uint32_t)0x30000000)        
#define  FMC_BWTR4_ACCMOD_0                 ((uint32_t)0x10000000)        
#define  FMC_BWTR4_ACCMOD_1                 ((uint32_t)0x20000000)        

#define  FMC_PCR2_PWAITEN                   ((uint32_t)0x00000002)        
#define  FMC_PCR2_PBKEN                     ((uint32_t)0x00000004)        
#define  FMC_PCR2_PTYP                      ((uint32_t)0x00000008)        

#define  FMC_PCR2_PWID                      ((uint32_t)0x00000030)        
#define  FMC_PCR2_PWID_0                    ((uint32_t)0x00000010)        
#define  FMC_PCR2_PWID_1                    ((uint32_t)0x00000020)        

#define  FMC_PCR2_ECCEN                     ((uint32_t)0x00000040)        

#define  FMC_PCR2_TCLR                      ((uint32_t)0x00001E00)        
#define  FMC_PCR2_TCLR_0                    ((uint32_t)0x00000200)        
#define  FMC_PCR2_TCLR_1                    ((uint32_t)0x00000400)        
#define  FMC_PCR2_TCLR_2                    ((uint32_t)0x00000800)        
#define  FMC_PCR2_TCLR_3                    ((uint32_t)0x00001000)        

#define  FMC_PCR2_TAR                       ((uint32_t)0x0001E000)        
#define  FMC_PCR2_TAR_0                     ((uint32_t)0x00002000)        
#define  FMC_PCR2_TAR_1                     ((uint32_t)0x00004000)        
#define  FMC_PCR2_TAR_2                     ((uint32_t)0x00008000)        
#define  FMC_PCR2_TAR_3                     ((uint32_t)0x00010000)        

#define  FMC_PCR2_ECCPS                     ((uint32_t)0x000E0000)        
#define  FMC_PCR2_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FMC_PCR2_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FMC_PCR2_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FMC_PCR3_PWAITEN                   ((uint32_t)0x00000002)        
#define  FMC_PCR3_PBKEN                     ((uint32_t)0x00000004)        
#define  FMC_PCR3_PTYP                      ((uint32_t)0x00000008)        

#define  FMC_PCR3_PWID                      ((uint32_t)0x00000030)        
#define  FMC_PCR3_PWID_0                    ((uint32_t)0x00000010)        
#define  FMC_PCR3_PWID_1                    ((uint32_t)0x00000020)        

#define  FMC_PCR3_ECCEN                     ((uint32_t)0x00000040)        

#define  FMC_PCR3_TCLR                      ((uint32_t)0x00001E00)        
#define  FMC_PCR3_TCLR_0                    ((uint32_t)0x00000200)        
#define  FMC_PCR3_TCLR_1                    ((uint32_t)0x00000400)        
#define  FMC_PCR3_TCLR_2                    ((uint32_t)0x00000800)        
#define  FMC_PCR3_TCLR_3                    ((uint32_t)0x00001000)        

#define  FMC_PCR3_TAR                       ((uint32_t)0x0001E000)        
#define  FMC_PCR3_TAR_0                     ((uint32_t)0x00002000)        
#define  FMC_PCR3_TAR_1                     ((uint32_t)0x00004000)        
#define  FMC_PCR3_TAR_2                     ((uint32_t)0x00008000)        
#define  FMC_PCR3_TAR_3                     ((uint32_t)0x00010000)        

#define  FMC_PCR3_ECCPS                     ((uint32_t)0x000E0000)        
#define  FMC_PCR3_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FMC_PCR3_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FMC_PCR3_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FMC_PCR4_PWAITEN                   ((uint32_t)0x00000002)        
#define  FMC_PCR4_PBKEN                     ((uint32_t)0x00000004)        
#define  FMC_PCR4_PTYP                      ((uint32_t)0x00000008)        

#define  FMC_PCR4_PWID                      ((uint32_t)0x00000030)        
#define  FMC_PCR4_PWID_0                    ((uint32_t)0x00000010)        
#define  FMC_PCR4_PWID_1                    ((uint32_t)0x00000020)        

#define  FMC_PCR4_ECCEN                     ((uint32_t)0x00000040)        

#define  FMC_PCR4_TCLR                      ((uint32_t)0x00001E00)        
#define  FMC_PCR4_TCLR_0                    ((uint32_t)0x00000200)        
#define  FMC_PCR4_TCLR_1                    ((uint32_t)0x00000400)        
#define  FMC_PCR4_TCLR_2                    ((uint32_t)0x00000800)        
#define  FMC_PCR4_TCLR_3                    ((uint32_t)0x00001000)        

#define  FMC_PCR4_TAR                       ((uint32_t)0x0001E000)        
#define  FMC_PCR4_TAR_0                     ((uint32_t)0x00002000)        
#define  FMC_PCR4_TAR_1                     ((uint32_t)0x00004000)        
#define  FMC_PCR4_TAR_2                     ((uint32_t)0x00008000)        
#define  FMC_PCR4_TAR_3                     ((uint32_t)0x00010000)        

#define  FMC_PCR4_ECCPS                     ((uint32_t)0x000E0000)        
#define  FMC_PCR4_ECCPS_0                   ((uint32_t)0x00020000)        
#define  FMC_PCR4_ECCPS_1                   ((uint32_t)0x00040000)        
#define  FMC_PCR4_ECCPS_2                   ((uint32_t)0x00080000)        

#define  FMC_SR2_IRS                        ((uint8_t)0x01)               
#define  FMC_SR2_ILS                        ((uint8_t)0x02)               
#define  FMC_SR2_IFS                        ((uint8_t)0x04)               
#define  FMC_SR2_IREN                       ((uint8_t)0x08)               
#define  FMC_SR2_ILEN                       ((uint8_t)0x10)               
#define  FMC_SR2_IFEN                       ((uint8_t)0x20)               
#define  FMC_SR2_FEMPT                      ((uint8_t)0x40)               

#define  FMC_SR3_IRS                        ((uint8_t)0x01)               
#define  FMC_SR3_ILS                        ((uint8_t)0x02)               
#define  FMC_SR3_IFS                        ((uint8_t)0x04)               
#define  FMC_SR3_IREN                       ((uint8_t)0x08)               
#define  FMC_SR3_ILEN                       ((uint8_t)0x10)               
#define  FMC_SR3_IFEN                       ((uint8_t)0x20)               
#define  FMC_SR3_FEMPT                      ((uint8_t)0x40)               

#define  FMC_SR4_IRS                        ((uint8_t)0x01)               
#define  FMC_SR4_ILS                        ((uint8_t)0x02)               
#define  FMC_SR4_IFS                        ((uint8_t)0x04)               
#define  FMC_SR4_IREN                       ((uint8_t)0x08)               
#define  FMC_SR4_ILEN                       ((uint8_t)0x10)               
#define  FMC_SR4_IFEN                       ((uint8_t)0x20)               
#define  FMC_SR4_FEMPT                      ((uint8_t)0x40)               

#define  FMC_PMEM2_MEMSET2                  ((uint32_t)0x000000FF)        
#define  FMC_PMEM2_MEMSET2_0                ((uint32_t)0x00000001)        
#define  FMC_PMEM2_MEMSET2_1                ((uint32_t)0x00000002)        
#define  FMC_PMEM2_MEMSET2_2                ((uint32_t)0x00000004)        
#define  FMC_PMEM2_MEMSET2_3                ((uint32_t)0x00000008)        
#define  FMC_PMEM2_MEMSET2_4                ((uint32_t)0x00000010)        
#define  FMC_PMEM2_MEMSET2_5                ((uint32_t)0x00000020)        
#define  FMC_PMEM2_MEMSET2_6                ((uint32_t)0x00000040)        
#define  FMC_PMEM2_MEMSET2_7                ((uint32_t)0x00000080)        

#define  FMC_PMEM2_MEMWAIT2                 ((uint32_t)0x0000FF00)        
#define  FMC_PMEM2_MEMWAIT2_0               ((uint32_t)0x00000100)        
#define  FMC_PMEM2_MEMWAIT2_1               ((uint32_t)0x00000200)        
#define  FMC_PMEM2_MEMWAIT2_2               ((uint32_t)0x00000400)        
#define  FMC_PMEM2_MEMWAIT2_3               ((uint32_t)0x00000800)        
#define  FMC_PMEM2_MEMWAIT2_4               ((uint32_t)0x00001000)        
#define  FMC_PMEM2_MEMWAIT2_5               ((uint32_t)0x00002000)        
#define  FMC_PMEM2_MEMWAIT2_6               ((uint32_t)0x00004000)        
#define  FMC_PMEM2_MEMWAIT2_7               ((uint32_t)0x00008000)        

#define  FMC_PMEM2_MEMHOLD2                 ((uint32_t)0x00FF0000)        
#define  FMC_PMEM2_MEMHOLD2_0               ((uint32_t)0x00010000)        
#define  FMC_PMEM2_MEMHOLD2_1               ((uint32_t)0x00020000)        
#define  FMC_PMEM2_MEMHOLD2_2               ((uint32_t)0x00040000)        
#define  FMC_PMEM2_MEMHOLD2_3               ((uint32_t)0x00080000)        
#define  FMC_PMEM2_MEMHOLD2_4               ((uint32_t)0x00100000)        
#define  FMC_PMEM2_MEMHOLD2_5               ((uint32_t)0x00200000)        
#define  FMC_PMEM2_MEMHOLD2_6               ((uint32_t)0x00400000)        
#define  FMC_PMEM2_MEMHOLD2_7               ((uint32_t)0x00800000)        

#define  FMC_PMEM2_MEMHIZ2                  ((uint32_t)0xFF000000)        
#define  FMC_PMEM2_MEMHIZ2_0                ((uint32_t)0x01000000)        
#define  FMC_PMEM2_MEMHIZ2_1                ((uint32_t)0x02000000)        
#define  FMC_PMEM2_MEMHIZ2_2                ((uint32_t)0x04000000)        
#define  FMC_PMEM2_MEMHIZ2_3                ((uint32_t)0x08000000)        
#define  FMC_PMEM2_MEMHIZ2_4                ((uint32_t)0x10000000)        
#define  FMC_PMEM2_MEMHIZ2_5                ((uint32_t)0x20000000)        
#define  FMC_PMEM2_MEMHIZ2_6                ((uint32_t)0x40000000)        
#define  FMC_PMEM2_MEMHIZ2_7                ((uint32_t)0x80000000)        

#define  FMC_PMEM3_MEMSET3                  ((uint32_t)0x000000FF)        
#define  FMC_PMEM3_MEMSET3_0                ((uint32_t)0x00000001)        
#define  FMC_PMEM3_MEMSET3_1                ((uint32_t)0x00000002)        
#define  FMC_PMEM3_MEMSET3_2                ((uint32_t)0x00000004)        
#define  FMC_PMEM3_MEMSET3_3                ((uint32_t)0x00000008)        
#define  FMC_PMEM3_MEMSET3_4                ((uint32_t)0x00000010)        
#define  FMC_PMEM3_MEMSET3_5                ((uint32_t)0x00000020)        
#define  FMC_PMEM3_MEMSET3_6                ((uint32_t)0x00000040)        
#define  FMC_PMEM3_MEMSET3_7                ((uint32_t)0x00000080)        

#define  FMC_PMEM3_MEMWAIT3                 ((uint32_t)0x0000FF00)        
#define  FMC_PMEM3_MEMWAIT3_0               ((uint32_t)0x00000100)        
#define  FMC_PMEM3_MEMWAIT3_1               ((uint32_t)0x00000200)        
#define  FMC_PMEM3_MEMWAIT3_2               ((uint32_t)0x00000400)        
#define  FMC_PMEM3_MEMWAIT3_3               ((uint32_t)0x00000800)        
#define  FMC_PMEM3_MEMWAIT3_4               ((uint32_t)0x00001000)        
#define  FMC_PMEM3_MEMWAIT3_5               ((uint32_t)0x00002000)        
#define  FMC_PMEM3_MEMWAIT3_6               ((uint32_t)0x00004000)        
#define  FMC_PMEM3_MEMWAIT3_7               ((uint32_t)0x00008000)        

#define  FMC_PMEM3_MEMHOLD3                 ((uint32_t)0x00FF0000)        
#define  FMC_PMEM3_MEMHOLD3_0               ((uint32_t)0x00010000)        
#define  FMC_PMEM3_MEMHOLD3_1               ((uint32_t)0x00020000)        
#define  FMC_PMEM3_MEMHOLD3_2               ((uint32_t)0x00040000)        
#define  FMC_PMEM3_MEMHOLD3_3               ((uint32_t)0x00080000)        
#define  FMC_PMEM3_MEMHOLD3_4               ((uint32_t)0x00100000)        
#define  FMC_PMEM3_MEMHOLD3_5               ((uint32_t)0x00200000)        
#define  FMC_PMEM3_MEMHOLD3_6               ((uint32_t)0x00400000)        
#define  FMC_PMEM3_MEMHOLD3_7               ((uint32_t)0x00800000)        

#define  FMC_PMEM3_MEMHIZ3                  ((uint32_t)0xFF000000)        
#define  FMC_PMEM3_MEMHIZ3_0                ((uint32_t)0x01000000)        
#define  FMC_PMEM3_MEMHIZ3_1                ((uint32_t)0x02000000)        
#define  FMC_PMEM3_MEMHIZ3_2                ((uint32_t)0x04000000)        
#define  FMC_PMEM3_MEMHIZ3_3                ((uint32_t)0x08000000)        
#define  FMC_PMEM3_MEMHIZ3_4                ((uint32_t)0x10000000)        
#define  FMC_PMEM3_MEMHIZ3_5                ((uint32_t)0x20000000)        
#define  FMC_PMEM3_MEMHIZ3_6                ((uint32_t)0x40000000)        
#define  FMC_PMEM3_MEMHIZ3_7                ((uint32_t)0x80000000)        

#define  FMC_PMEM4_MEMSET4                  ((uint32_t)0x000000FF)        
#define  FMC_PMEM4_MEMSET4_0                ((uint32_t)0x00000001)        
#define  FMC_PMEM4_MEMSET4_1                ((uint32_t)0x00000002)        
#define  FMC_PMEM4_MEMSET4_2                ((uint32_t)0x00000004)        
#define  FMC_PMEM4_MEMSET4_3                ((uint32_t)0x00000008)        
#define  FMC_PMEM4_MEMSET4_4                ((uint32_t)0x00000010)        
#define  FMC_PMEM4_MEMSET4_5                ((uint32_t)0x00000020)        
#define  FMC_PMEM4_MEMSET4_6                ((uint32_t)0x00000040)        
#define  FMC_PMEM4_MEMSET4_7                ((uint32_t)0x00000080)        

#define  FMC_PMEM4_MEMWAIT4                 ((uint32_t)0x0000FF00)        
#define  FMC_PMEM4_MEMWAIT4_0               ((uint32_t)0x00000100)        
#define  FMC_PMEM4_MEMWAIT4_1               ((uint32_t)0x00000200)        
#define  FMC_PMEM4_MEMWAIT4_2               ((uint32_t)0x00000400)        
#define  FMC_PMEM4_MEMWAIT4_3               ((uint32_t)0x00000800)        
#define  FMC_PMEM4_MEMWAIT4_4               ((uint32_t)0x00001000)        
#define  FMC_PMEM4_MEMWAIT4_5               ((uint32_t)0x00002000)        
#define  FMC_PMEM4_MEMWAIT4_6               ((uint32_t)0x00004000)        
#define  FMC_PMEM4_MEMWAIT4_7               ((uint32_t)0x00008000)        

#define  FMC_PMEM4_MEMHOLD4                 ((uint32_t)0x00FF0000)        
#define  FMC_PMEM4_MEMHOLD4_0               ((uint32_t)0x00010000)        
#define  FMC_PMEM4_MEMHOLD4_1               ((uint32_t)0x00020000)        
#define  FMC_PMEM4_MEMHOLD4_2               ((uint32_t)0x00040000)        
#define  FMC_PMEM4_MEMHOLD4_3               ((uint32_t)0x00080000)        
#define  FMC_PMEM4_MEMHOLD4_4               ((uint32_t)0x00100000)        
#define  FMC_PMEM4_MEMHOLD4_5               ((uint32_t)0x00200000)        
#define  FMC_PMEM4_MEMHOLD4_6               ((uint32_t)0x00400000)        
#define  FMC_PMEM4_MEMHOLD4_7               ((uint32_t)0x00800000)        

#define  FMC_PMEM4_MEMHIZ4                  ((uint32_t)0xFF000000)        
#define  FMC_PMEM4_MEMHIZ4_0                ((uint32_t)0x01000000)        
#define  FMC_PMEM4_MEMHIZ4_1                ((uint32_t)0x02000000)        
#define  FMC_PMEM4_MEMHIZ4_2                ((uint32_t)0x04000000)        
#define  FMC_PMEM4_MEMHIZ4_3                ((uint32_t)0x08000000)        
#define  FMC_PMEM4_MEMHIZ4_4                ((uint32_t)0x10000000)        
#define  FMC_PMEM4_MEMHIZ4_5                ((uint32_t)0x20000000)        
#define  FMC_PMEM4_MEMHIZ4_6                ((uint32_t)0x40000000)        
#define  FMC_PMEM4_MEMHIZ4_7                ((uint32_t)0x80000000)        

#define  FMC_PATT2_ATTSET2                  ((uint32_t)0x000000FF)        
#define  FMC_PATT2_ATTSET2_0                ((uint32_t)0x00000001)        
#define  FMC_PATT2_ATTSET2_1                ((uint32_t)0x00000002)        
#define  FMC_PATT2_ATTSET2_2                ((uint32_t)0x00000004)        
#define  FMC_PATT2_ATTSET2_3                ((uint32_t)0x00000008)        
#define  FMC_PATT2_ATTSET2_4                ((uint32_t)0x00000010)        
#define  FMC_PATT2_ATTSET2_5                ((uint32_t)0x00000020)        
#define  FMC_PATT2_ATTSET2_6                ((uint32_t)0x00000040)        
#define  FMC_PATT2_ATTSET2_7                ((uint32_t)0x00000080)        

#define  FMC_PATT2_ATTWAIT2                 ((uint32_t)0x0000FF00)        
#define  FMC_PATT2_ATTWAIT2_0               ((uint32_t)0x00000100)        
#define  FMC_PATT2_ATTWAIT2_1               ((uint32_t)0x00000200)        
#define  FMC_PATT2_ATTWAIT2_2               ((uint32_t)0x00000400)        
#define  FMC_PATT2_ATTWAIT2_3               ((uint32_t)0x00000800)        
#define  FMC_PATT2_ATTWAIT2_4               ((uint32_t)0x00001000)        
#define  FMC_PATT2_ATTWAIT2_5               ((uint32_t)0x00002000)        
#define  FMC_PATT2_ATTWAIT2_6               ((uint32_t)0x00004000)        
#define  FMC_PATT2_ATTWAIT2_7               ((uint32_t)0x00008000)        

#define  FMC_PATT2_ATTHOLD2                 ((uint32_t)0x00FF0000)        
#define  FMC_PATT2_ATTHOLD2_0               ((uint32_t)0x00010000)        
#define  FMC_PATT2_ATTHOLD2_1               ((uint32_t)0x00020000)        
#define  FMC_PATT2_ATTHOLD2_2               ((uint32_t)0x00040000)        
#define  FMC_PATT2_ATTHOLD2_3               ((uint32_t)0x00080000)        
#define  FMC_PATT2_ATTHOLD2_4               ((uint32_t)0x00100000)        
#define  FMC_PATT2_ATTHOLD2_5               ((uint32_t)0x00200000)        
#define  FMC_PATT2_ATTHOLD2_6               ((uint32_t)0x00400000)        
#define  FMC_PATT2_ATTHOLD2_7               ((uint32_t)0x00800000)        

#define  FMC_PATT2_ATTHIZ2                  ((uint32_t)0xFF000000)        
#define  FMC_PATT2_ATTHIZ2_0                ((uint32_t)0x01000000)        
#define  FMC_PATT2_ATTHIZ2_1                ((uint32_t)0x02000000)        
#define  FMC_PATT2_ATTHIZ2_2                ((uint32_t)0x04000000)        
#define  FMC_PATT2_ATTHIZ2_3                ((uint32_t)0x08000000)        
#define  FMC_PATT2_ATTHIZ2_4                ((uint32_t)0x10000000)        
#define  FMC_PATT2_ATTHIZ2_5                ((uint32_t)0x20000000)        
#define  FMC_PATT2_ATTHIZ2_6                ((uint32_t)0x40000000)        
#define  FMC_PATT2_ATTHIZ2_7                ((uint32_t)0x80000000)        

#define  FMC_PATT3_ATTSET3                  ((uint32_t)0x000000FF)        
#define  FMC_PATT3_ATTSET3_0                ((uint32_t)0x00000001)        
#define  FMC_PATT3_ATTSET3_1                ((uint32_t)0x00000002)        
#define  FMC_PATT3_ATTSET3_2                ((uint32_t)0x00000004)        
#define  FMC_PATT3_ATTSET3_3                ((uint32_t)0x00000008)        
#define  FMC_PATT3_ATTSET3_4                ((uint32_t)0x00000010)        
#define  FMC_PATT3_ATTSET3_5                ((uint32_t)0x00000020)        
#define  FMC_PATT3_ATTSET3_6                ((uint32_t)0x00000040)        
#define  FMC_PATT3_ATTSET3_7                ((uint32_t)0x00000080)        

#define  FMC_PATT3_ATTWAIT3                 ((uint32_t)0x0000FF00)        
#define  FMC_PATT3_ATTWAIT3_0               ((uint32_t)0x00000100)        
#define  FMC_PATT3_ATTWAIT3_1               ((uint32_t)0x00000200)        
#define  FMC_PATT3_ATTWAIT3_2               ((uint32_t)0x00000400)        
#define  FMC_PATT3_ATTWAIT3_3               ((uint32_t)0x00000800)        
#define  FMC_PATT3_ATTWAIT3_4               ((uint32_t)0x00001000)        
#define  FMC_PATT3_ATTWAIT3_5               ((uint32_t)0x00002000)        
#define  FMC_PATT3_ATTWAIT3_6               ((uint32_t)0x00004000)        
#define  FMC_PATT3_ATTWAIT3_7               ((uint32_t)0x00008000)        

#define  FMC_PATT3_ATTHOLD3                 ((uint32_t)0x00FF0000)        
#define  FMC_PATT3_ATTHOLD3_0               ((uint32_t)0x00010000)        
#define  FMC_PATT3_ATTHOLD3_1               ((uint32_t)0x00020000)        
#define  FMC_PATT3_ATTHOLD3_2               ((uint32_t)0x00040000)        
#define  FMC_PATT3_ATTHOLD3_3               ((uint32_t)0x00080000)        
#define  FMC_PATT3_ATTHOLD3_4               ((uint32_t)0x00100000)        
#define  FMC_PATT3_ATTHOLD3_5               ((uint32_t)0x00200000)        
#define  FMC_PATT3_ATTHOLD3_6               ((uint32_t)0x00400000)        
#define  FMC_PATT3_ATTHOLD3_7               ((uint32_t)0x00800000)        

#define  FMC_PATT3_ATTHIZ3                  ((uint32_t)0xFF000000)        
#define  FMC_PATT3_ATTHIZ3_0                ((uint32_t)0x01000000)        
#define  FMC_PATT3_ATTHIZ3_1                ((uint32_t)0x02000000)        
#define  FMC_PATT3_ATTHIZ3_2                ((uint32_t)0x04000000)        
#define  FMC_PATT3_ATTHIZ3_3                ((uint32_t)0x08000000)        
#define  FMC_PATT3_ATTHIZ3_4                ((uint32_t)0x10000000)        
#define  FMC_PATT3_ATTHIZ3_5                ((uint32_t)0x20000000)        
#define  FMC_PATT3_ATTHIZ3_6                ((uint32_t)0x40000000)        
#define  FMC_PATT3_ATTHIZ3_7                ((uint32_t)0x80000000)        

#define  FMC_PATT4_ATTSET4                  ((uint32_t)0x000000FF)        
#define  FMC_PATT4_ATTSET4_0                ((uint32_t)0x00000001)        
#define  FMC_PATT4_ATTSET4_1                ((uint32_t)0x00000002)        
#define  FMC_PATT4_ATTSET4_2                ((uint32_t)0x00000004)        
#define  FMC_PATT4_ATTSET4_3                ((uint32_t)0x00000008)        
#define  FMC_PATT4_ATTSET4_4                ((uint32_t)0x00000010)        
#define  FMC_PATT4_ATTSET4_5                ((uint32_t)0x00000020)        
#define  FMC_PATT4_ATTSET4_6                ((uint32_t)0x00000040)        
#define  FMC_PATT4_ATTSET4_7                ((uint32_t)0x00000080)        

#define  FMC_PATT4_ATTWAIT4                 ((uint32_t)0x0000FF00)        
#define  FMC_PATT4_ATTWAIT4_0               ((uint32_t)0x00000100)        
#define  FMC_PATT4_ATTWAIT4_1               ((uint32_t)0x00000200)        
#define  FMC_PATT4_ATTWAIT4_2               ((uint32_t)0x00000400)        
#define  FMC_PATT4_ATTWAIT4_3               ((uint32_t)0x00000800)        
#define  FMC_PATT4_ATTWAIT4_4               ((uint32_t)0x00001000)        
#define  FMC_PATT4_ATTWAIT4_5               ((uint32_t)0x00002000)        
#define  FMC_PATT4_ATTWAIT4_6               ((uint32_t)0x00004000)        
#define  FMC_PATT4_ATTWAIT4_7               ((uint32_t)0x00008000)        

#define  FMC_PATT4_ATTHOLD4                 ((uint32_t)0x00FF0000)        
#define  FMC_PATT4_ATTHOLD4_0               ((uint32_t)0x00010000)        
#define  FMC_PATT4_ATTHOLD4_1               ((uint32_t)0x00020000)        
#define  FMC_PATT4_ATTHOLD4_2               ((uint32_t)0x00040000)        
#define  FMC_PATT4_ATTHOLD4_3               ((uint32_t)0x00080000)        
#define  FMC_PATT4_ATTHOLD4_4               ((uint32_t)0x00100000)        
#define  FMC_PATT4_ATTHOLD4_5               ((uint32_t)0x00200000)        
#define  FMC_PATT4_ATTHOLD4_6               ((uint32_t)0x00400000)        
#define  FMC_PATT4_ATTHOLD4_7               ((uint32_t)0x00800000)        

#define  FMC_PATT4_ATTHIZ4                  ((uint32_t)0xFF000000)        
#define  FMC_PATT4_ATTHIZ4_0                ((uint32_t)0x01000000)        
#define  FMC_PATT4_ATTHIZ4_1                ((uint32_t)0x02000000)        
#define  FMC_PATT4_ATTHIZ4_2                ((uint32_t)0x04000000)        
#define  FMC_PATT4_ATTHIZ4_3                ((uint32_t)0x08000000)        
#define  FMC_PATT4_ATTHIZ4_4                ((uint32_t)0x10000000)        
#define  FMC_PATT4_ATTHIZ4_5                ((uint32_t)0x20000000)        
#define  FMC_PATT4_ATTHIZ4_6                ((uint32_t)0x40000000)        
#define  FMC_PATT4_ATTHIZ4_7                ((uint32_t)0x80000000)        

#define  FMC_PIO4_IOSET4                    ((uint32_t)0x000000FF)        
#define  FMC_PIO4_IOSET4_0                  ((uint32_t)0x00000001)        
#define  FMC_PIO4_IOSET4_1                  ((uint32_t)0x00000002)        
#define  FMC_PIO4_IOSET4_2                  ((uint32_t)0x00000004)        
#define  FMC_PIO4_IOSET4_3                  ((uint32_t)0x00000008)        
#define  FMC_PIO4_IOSET4_4                  ((uint32_t)0x00000010)        
#define  FMC_PIO4_IOSET4_5                  ((uint32_t)0x00000020)        
#define  FMC_PIO4_IOSET4_6                  ((uint32_t)0x00000040)        
#define  FMC_PIO4_IOSET4_7                  ((uint32_t)0x00000080)        

#define  FMC_PIO4_IOWAIT4                   ((uint32_t)0x0000FF00)        
#define  FMC_PIO4_IOWAIT4_0                 ((uint32_t)0x00000100)        
#define  FMC_PIO4_IOWAIT4_1                 ((uint32_t)0x00000200)        
#define  FMC_PIO4_IOWAIT4_2                 ((uint32_t)0x00000400)        
#define  FMC_PIO4_IOWAIT4_3                 ((uint32_t)0x00000800)        
#define  FMC_PIO4_IOWAIT4_4                 ((uint32_t)0x00001000)        
#define  FMC_PIO4_IOWAIT4_5                 ((uint32_t)0x00002000)        
#define  FMC_PIO4_IOWAIT4_6                 ((uint32_t)0x00004000)        
#define  FMC_PIO4_IOWAIT4_7                 ((uint32_t)0x00008000)        

#define  FMC_PIO4_IOHOLD4                   ((uint32_t)0x00FF0000)        
#define  FMC_PIO4_IOHOLD4_0                 ((uint32_t)0x00010000)        
#define  FMC_PIO4_IOHOLD4_1                 ((uint32_t)0x00020000)        
#define  FMC_PIO4_IOHOLD4_2                 ((uint32_t)0x00040000)        
#define  FMC_PIO4_IOHOLD4_3                 ((uint32_t)0x00080000)        
#define  FMC_PIO4_IOHOLD4_4                 ((uint32_t)0x00100000)        
#define  FMC_PIO4_IOHOLD4_5                 ((uint32_t)0x00200000)        
#define  FMC_PIO4_IOHOLD4_6                 ((uint32_t)0x00400000)        
#define  FMC_PIO4_IOHOLD4_7                 ((uint32_t)0x00800000)        

#define  FMC_PIO4_IOHIZ4                    ((uint32_t)0xFF000000)        
#define  FMC_PIO4_IOHIZ4_0                  ((uint32_t)0x01000000)        
#define  FMC_PIO4_IOHIZ4_1                  ((uint32_t)0x02000000)        
#define  FMC_PIO4_IOHIZ4_2                  ((uint32_t)0x04000000)        
#define  FMC_PIO4_IOHIZ4_3                  ((uint32_t)0x08000000)        
#define  FMC_PIO4_IOHIZ4_4                  ((uint32_t)0x10000000)        
#define  FMC_PIO4_IOHIZ4_5                  ((uint32_t)0x20000000)        
#define  FMC_PIO4_IOHIZ4_6                  ((uint32_t)0x40000000)        
#define  FMC_PIO4_IOHIZ4_7                  ((uint32_t)0x80000000)        

#define  FMC_ECCR2_ECC2                     ((uint32_t)0xFFFFFFFF)        

#define  FMC_ECCR3_ECC3                     ((uint32_t)0xFFFFFFFF)        

#define  FMC_SDCR1_NC                       ((uint32_t)0x00000003)        
#define  FMC_SDCR1_NC_0                     ((uint32_t)0x00000001)        
#define  FMC_SDCR1_NC_1                     ((uint32_t)0x00000002)        

#define  FMC_SDCR1_NR                       ((uint32_t)0x0000000C)        
#define  FMC_SDCR1_NR_0                     ((uint32_t)0x00000004)        
#define  FMC_SDCR1_NR_1                     ((uint32_t)0x00000008)        

#define  FMC_SDCR1_MWID                     ((uint32_t)0x00000030)        
#define  FMC_SDCR1_MWID_0                   ((uint32_t)0x00000010)        
#define  FMC_SDCR1_MWID_1                   ((uint32_t)0x00000020)        

#define  FMC_SDCR1_NB                       ((uint32_t)0x00000040)        

#define  FMC_SDCR1_CAS                      ((uint32_t)0x00000180)        
#define  FMC_SDCR1_CAS_0                    ((uint32_t)0x00000080)        
#define  FMC_SDCR1_CAS_1                    ((uint32_t)0x00000100)        

#define  FMC_SDCR1_WP                       ((uint32_t)0x00000200)        

#define  FMC_SDCR1_SDCLK                    ((uint32_t)0x00000C00)        
#define  FMC_SDCR1_SDCLK_0                  ((uint32_t)0x00000400)        
#define  FMC_SDCR1_SDCLK_1                  ((uint32_t)0x00000800)        

#define  FMC_SDCR1_RBURST                   ((uint32_t)0x00001000)        

#define  FMC_SDCR1_RPIPE                    ((uint32_t)0x00006000)        
#define  FMC_SDCR1_RPIPE_0                  ((uint32_t)0x00002000)        
#define  FMC_SDCR1_RPIPE_1                  ((uint32_t)0x00004000)        

#define  FMC_SDCR2_NC                       ((uint32_t)0x00000003)        
#define  FMC_SDCR2_NC_0                     ((uint32_t)0x00000001)        
#define  FMC_SDCR2_NC_1                     ((uint32_t)0x00000002)        

#define  FMC_SDCR2_NR                       ((uint32_t)0x0000000C)        
#define  FMC_SDCR2_NR_0                     ((uint32_t)0x00000004)        
#define  FMC_SDCR2_NR_1                     ((uint32_t)0x00000008)        

#define  FMC_SDCR2_MWID                     ((uint32_t)0x00000030)        
#define  FMC_SDCR2_MWID_0                   ((uint32_t)0x00000010)        
#define  FMC_SDCR2_MWID_1                   ((uint32_t)0x00000020)        

#define  FMC_SDCR2_NB                       ((uint32_t)0x00000040)        

#define  FMC_SDCR2_CAS                      ((uint32_t)0x00000180)        
#define  FMC_SDCR2_CAS_0                    ((uint32_t)0x00000080)        
#define  FMC_SDCR2_CAS_1                    ((uint32_t)0x00000100)        

#define  FMC_SDCR2_WP                       ((uint32_t)0x00000200)        

#define  FMC_SDCR2_SDCLK                    ((uint32_t)0x00000C00)        
#define  FMC_SDCR2_SDCLK_0                  ((uint32_t)0x00000400)        
#define  FMC_SDCR2_SDCLK_1                  ((uint32_t)0x00000800)        

#define  FMC_SDCR2_RBURST                   ((uint32_t)0x00001000)        

#define  FMC_SDCR2_RPIPE                    ((uint32_t)0x00006000)        
#define  FMC_SDCR2_RPIPE_0                  ((uint32_t)0x00002000)        
#define  FMC_SDCR2_RPIPE_1                  ((uint32_t)0x00004000)        

#define  FMC_SDTR1_TMRD                     ((uint32_t)0x0000000F)        
#define  FMC_SDTR1_TMRD_0                   ((uint32_t)0x00000001)        
#define  FMC_SDTR1_TMRD_1                   ((uint32_t)0x00000002)        
#define  FMC_SDTR1_TMRD_2                   ((uint32_t)0x00000004)        
#define  FMC_SDTR1_TMRD_3                   ((uint32_t)0x00000008)        
                                            
#define  FMC_SDTR1_TXSR                     ((uint32_t)0x000000F0)        
#define  FMC_SDTR1_TXSR_0                   ((uint32_t)0x00000010)        
#define  FMC_SDTR1_TXSR_1                   ((uint32_t)0x00000020)        
#define  FMC_SDTR1_TXSR_2                   ((uint32_t)0x00000040)        
#define  FMC_SDTR1_TXSR_3                   ((uint32_t)0x00000080)        

#define  FMC_SDTR1_TRAS                     ((uint32_t)0x00000F00)        
#define  FMC_SDTR1_TRAS_0                   ((uint32_t)0x00000100)        
#define  FMC_SDTR1_TRAS_1                   ((uint32_t)0x00000200)        
#define  FMC_SDTR1_TRAS_2                   ((uint32_t)0x00000400)        
#define  FMC_SDTR1_TRAS_3                   ((uint32_t)0x00000800)        

#define  FMC_SDTR1_TRC                      ((uint32_t)0x0000F000)        
#define  FMC_SDTR1_TRC_0                    ((uint32_t)0x00001000)        
#define  FMC_SDTR1_TRC_1                    ((uint32_t)0x00002000)        
#define  FMC_SDTR1_TRC_2                    ((uint32_t)0x00004000)        

#define  FMC_SDTR1_TWR                      ((uint32_t)0x000F0000)        
#define  FMC_SDTR1_TWR_0                    ((uint32_t)0x00010000)        
#define  FMC_SDTR1_TWR_1                    ((uint32_t)0x00020000)        
#define  FMC_SDTR1_TWR_2                    ((uint32_t)0x00040000)        

#define  FMC_SDTR1_TRP                      ((uint32_t)0x00F00000)        
#define  FMC_SDTR1_TRP_0                    ((uint32_t)0x00100000)        
#define  FMC_SDTR1_TRP_1                    ((uint32_t)0x00200000)        
#define  FMC_SDTR1_TRP_2                    ((uint32_t)0x00400000)        

#define  FMC_SDTR1_TRCD                     ((uint32_t)0x0F000000)        
#define  FMC_SDTR1_TRCD_0                   ((uint32_t)0x01000000)        
#define  FMC_SDTR1_TRCD_1                   ((uint32_t)0x02000000)        
#define  FMC_SDTR1_TRCD_2                   ((uint32_t)0x04000000)        

#define  FMC_SDTR2_TMRD                     ((uint32_t)0x0000000F)        
#define  FMC_SDTR2_TMRD_0                   ((uint32_t)0x00000001)        
#define  FMC_SDTR2_TMRD_1                   ((uint32_t)0x00000002)        
#define  FMC_SDTR2_TMRD_2                   ((uint32_t)0x00000004)        
#define  FMC_SDTR2_TMRD_3                   ((uint32_t)0x00000008)        
                                            
#define  FMC_SDTR2_TXSR                     ((uint32_t)0x000000F0)        
#define  FMC_SDTR2_TXSR_0                   ((uint32_t)0x00000010)        
#define  FMC_SDTR2_TXSR_1                   ((uint32_t)0x00000020)        
#define  FMC_SDTR2_TXSR_2                   ((uint32_t)0x00000040)        
#define  FMC_SDTR2_TXSR_3                   ((uint32_t)0x00000080)        

#define  FMC_SDTR2_TRAS                     ((uint32_t)0x00000F00)        
#define  FMC_SDTR2_TRAS_0                   ((uint32_t)0x00000100)        
#define  FMC_SDTR2_TRAS_1                   ((uint32_t)0x00000200)        
#define  FMC_SDTR2_TRAS_2                   ((uint32_t)0x00000400)        
#define  FMC_SDTR2_TRAS_3                   ((uint32_t)0x00000800)        

#define  FMC_SDTR2_TRC                      ((uint32_t)0x0000F000)        
#define  FMC_SDTR2_TRC_0                    ((uint32_t)0x00001000)        
#define  FMC_SDTR2_TRC_1                    ((uint32_t)0x00002000)        
#define  FMC_SDTR2_TRC_2                    ((uint32_t)0x00004000)        

#define  FMC_SDTR2_TWR                      ((uint32_t)0x000F0000)        
#define  FMC_SDTR2_TWR_0                    ((uint32_t)0x00010000)        
#define  FMC_SDTR2_TWR_1                    ((uint32_t)0x00020000)        
#define  FMC_SDTR2_TWR_2                    ((uint32_t)0x00040000)        

#define  FMC_SDTR2_TRP                      ((uint32_t)0x00F00000)        
#define  FMC_SDTR2_TRP_0                    ((uint32_t)0x00100000)        
#define  FMC_SDTR2_TRP_1                    ((uint32_t)0x00200000)        
#define  FMC_SDTR2_TRP_2                    ((uint32_t)0x00400000)        

#define  FMC_SDTR2_TRCD                     ((uint32_t)0x0F000000)        
#define  FMC_SDTR2_TRCD_0                   ((uint32_t)0x01000000)        
#define  FMC_SDTR2_TRCD_1                   ((uint32_t)0x02000000)        
#define  FMC_SDTR2_TRCD_2                   ((uint32_t)0x04000000)        

#define  FMC_SDCMR_MODE                     ((uint32_t)0x00000007)        
#define  FMC_SDCMR_MODE_0                   ((uint32_t)0x00000001)        
#define  FMC_SDCMR_MODE_1                   ((uint32_t)0x00000002)        
#define  FMC_SDCMR_MODE_2                   ((uint32_t)0x00000003)        
                                            
#define  FMC_SDCMR_CTB2                     ((uint32_t)0x00000008)        

#define  FMC_SDCMR_CTB1                     ((uint32_t)0x00000010)        

#define  FMC_SDCMR_NRFS                     ((uint32_t)0x000001E0)        
#define  FMC_SDCMR_NRFS_0                   ((uint32_t)0x00000020)        
#define  FMC_SDCMR_NRFS_1                   ((uint32_t)0x00000040)        
#define  FMC_SDCMR_NRFS_2                   ((uint32_t)0x00000080)        
#define  FMC_SDCMR_NRFS_3                   ((uint32_t)0x00000100)        

#define  FMC_SDCMR_MRD                      ((uint32_t)0x003FFE00)        

#define  FMC_SDRTR_CRE                      ((uint32_t)0x00000001)        

#define  FMC_SDRTR_COUNT                    ((uint32_t)0x00003FFE)        

#define  FMC_SDRTR_REIE                     ((uint32_t)0x00004000)        

#define  FMC_SDSR_RE                        ((uint32_t)0x00000001)        

#define  FMC_SDSR_MODES1                    ((uint32_t)0x00000006)        
#define  FMC_SDSR_MODES1_0                  ((uint32_t)0x00000002)        
#define  FMC_SDSR_MODES1_1                  ((uint32_t)0x00000004)        

#define  FMC_SDSR_MODES2                    ((uint32_t)0x00000018)        
#define  FMC_SDSR_MODES2_0                  ((uint32_t)0x00000008)        
#define  FMC_SDSR_MODES2_1                  ((uint32_t)0x00000010)        

#define  FMC_SDSR_BUSY                      ((uint32_t)0x00000020)        

#endif 

#define GPIO_MODER_MODER0                    ((uint32_t)0x00000003)
#define GPIO_MODER_MODER0_0                  ((uint32_t)0x00000001)
#define GPIO_MODER_MODER0_1                  ((uint32_t)0x00000002)

#define GPIO_MODER_MODER1                    ((uint32_t)0x0000000C)
#define GPIO_MODER_MODER1_0                  ((uint32_t)0x00000004)
#define GPIO_MODER_MODER1_1                  ((uint32_t)0x00000008)

#define GPIO_MODER_MODER2                    ((uint32_t)0x00000030)
#define GPIO_MODER_MODER2_0                  ((uint32_t)0x00000010)
#define GPIO_MODER_MODER2_1                  ((uint32_t)0x00000020)

#define GPIO_MODER_MODER3                    ((uint32_t)0x000000C0)
#define GPIO_MODER_MODER3_0                  ((uint32_t)0x00000040)
#define GPIO_MODER_MODER3_1                  ((uint32_t)0x00000080)

#define GPIO_MODER_MODER4                    ((uint32_t)0x00000300)
#define GPIO_MODER_MODER4_0                  ((uint32_t)0x00000100)
#define GPIO_MODER_MODER4_1                  ((uint32_t)0x00000200)

#define GPIO_MODER_MODER5                    ((uint32_t)0x00000C00)
#define GPIO_MODER_MODER5_0                  ((uint32_t)0x00000400)
#define GPIO_MODER_MODER5_1                  ((uint32_t)0x00000800)

#define GPIO_MODER_MODER6                    ((uint32_t)0x00003000)
#define GPIO_MODER_MODER6_0                  ((uint32_t)0x00001000)
#define GPIO_MODER_MODER6_1                  ((uint32_t)0x00002000)

#define GPIO_MODER_MODER7                    ((uint32_t)0x0000C000)
#define GPIO_MODER_MODER7_0                  ((uint32_t)0x00004000)
#define GPIO_MODER_MODER7_1                  ((uint32_t)0x00008000)

#define GPIO_MODER_MODER8                    ((uint32_t)0x00030000)
#define GPIO_MODER_MODER8_0                  ((uint32_t)0x00010000)
#define GPIO_MODER_MODER8_1                  ((uint32_t)0x00020000)

#define GPIO_MODER_MODER9                    ((uint32_t)0x000C0000)
#define GPIO_MODER_MODER9_0                  ((uint32_t)0x00040000)
#define GPIO_MODER_MODER9_1                  ((uint32_t)0x00080000)

#define GPIO_MODER_MODER10                   ((uint32_t)0x00300000)
#define GPIO_MODER_MODER10_0                 ((uint32_t)0x00100000)
#define GPIO_MODER_MODER10_1                 ((uint32_t)0x00200000)

#define GPIO_MODER_MODER11                   ((uint32_t)0x00C00000)
#define GPIO_MODER_MODER11_0                 ((uint32_t)0x00400000)
#define GPIO_MODER_MODER11_1                 ((uint32_t)0x00800000)

#define GPIO_MODER_MODER12                   ((uint32_t)0x03000000)
#define GPIO_MODER_MODER12_0                 ((uint32_t)0x01000000)
#define GPIO_MODER_MODER12_1                 ((uint32_t)0x02000000)

#define GPIO_MODER_MODER13                   ((uint32_t)0x0C000000)
#define GPIO_MODER_MODER13_0                 ((uint32_t)0x04000000)
#define GPIO_MODER_MODER13_1                 ((uint32_t)0x08000000)

#define GPIO_MODER_MODER14                   ((uint32_t)0x30000000)
#define GPIO_MODER_MODER14_0                 ((uint32_t)0x10000000)
#define GPIO_MODER_MODER14_1                 ((uint32_t)0x20000000)

#define GPIO_MODER_MODER15                   ((uint32_t)0xC0000000)
#define GPIO_MODER_MODER15_0                 ((uint32_t)0x40000000)
#define GPIO_MODER_MODER15_1                 ((uint32_t)0x80000000)

#define GPIO_OTYPER_OT_0                     ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1                     ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2                     ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3                     ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4                     ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5                     ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6                     ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7                     ((uint32_t)0x00000080)
#define GPIO_OTYPER_OT_8                     ((uint32_t)0x00000100)
#define GPIO_OTYPER_OT_9                     ((uint32_t)0x00000200)
#define GPIO_OTYPER_OT_10                    ((uint32_t)0x00000400)
#define GPIO_OTYPER_OT_11                    ((uint32_t)0x00000800)
#define GPIO_OTYPER_OT_12                    ((uint32_t)0x00001000)
#define GPIO_OTYPER_OT_13                    ((uint32_t)0x00002000)
#define GPIO_OTYPER_OT_14                    ((uint32_t)0x00004000)
#define GPIO_OTYPER_OT_15                    ((uint32_t)0x00008000)

#define GPIO_OSPEEDER_OSPEEDR0               ((uint32_t)0x00000003)
#define GPIO_OSPEEDER_OSPEEDR0_0             ((uint32_t)0x00000001)
#define GPIO_OSPEEDER_OSPEEDR0_1             ((uint32_t)0x00000002)

#define GPIO_OSPEEDER_OSPEEDR1               ((uint32_t)0x0000000C)
#define GPIO_OSPEEDER_OSPEEDR1_0             ((uint32_t)0x00000004)
#define GPIO_OSPEEDER_OSPEEDR1_1             ((uint32_t)0x00000008)

#define GPIO_OSPEEDER_OSPEEDR2               ((uint32_t)0x00000030)
#define GPIO_OSPEEDER_OSPEEDR2_0             ((uint32_t)0x00000010)
#define GPIO_OSPEEDER_OSPEEDR2_1             ((uint32_t)0x00000020)

#define GPIO_OSPEEDER_OSPEEDR3               ((uint32_t)0x000000C0)
#define GPIO_OSPEEDER_OSPEEDR3_0             ((uint32_t)0x00000040)
#define GPIO_OSPEEDER_OSPEEDR3_1             ((uint32_t)0x00000080)

#define GPIO_OSPEEDER_OSPEEDR4               ((uint32_t)0x00000300)
#define GPIO_OSPEEDER_OSPEEDR4_0             ((uint32_t)0x00000100)
#define GPIO_OSPEEDER_OSPEEDR4_1             ((uint32_t)0x00000200)

#define GPIO_OSPEEDER_OSPEEDR5               ((uint32_t)0x00000C00)
#define GPIO_OSPEEDER_OSPEEDR5_0             ((uint32_t)0x00000400)
#define GPIO_OSPEEDER_OSPEEDR5_1             ((uint32_t)0x00000800)

#define GPIO_OSPEEDER_OSPEEDR6               ((uint32_t)0x00003000)
#define GPIO_OSPEEDER_OSPEEDR6_0             ((uint32_t)0x00001000)
#define GPIO_OSPEEDER_OSPEEDR6_1             ((uint32_t)0x00002000)

#define GPIO_OSPEEDER_OSPEEDR7               ((uint32_t)0x0000C000)
#define GPIO_OSPEEDER_OSPEEDR7_0             ((uint32_t)0x00004000)
#define GPIO_OSPEEDER_OSPEEDR7_1             ((uint32_t)0x00008000)

#define GPIO_OSPEEDER_OSPEEDR8               ((uint32_t)0x00030000)
#define GPIO_OSPEEDER_OSPEEDR8_0             ((uint32_t)0x00010000)
#define GPIO_OSPEEDER_OSPEEDR8_1             ((uint32_t)0x00020000)

#define GPIO_OSPEEDER_OSPEEDR9               ((uint32_t)0x000C0000)
#define GPIO_OSPEEDER_OSPEEDR9_0             ((uint32_t)0x00040000)
#define GPIO_OSPEEDER_OSPEEDR9_1             ((uint32_t)0x00080000)

#define GPIO_OSPEEDER_OSPEEDR10              ((uint32_t)0x00300000)
#define GPIO_OSPEEDER_OSPEEDR10_0            ((uint32_t)0x00100000)
#define GPIO_OSPEEDER_OSPEEDR10_1            ((uint32_t)0x00200000)

#define GPIO_OSPEEDER_OSPEEDR11              ((uint32_t)0x00C00000)
#define GPIO_OSPEEDER_OSPEEDR11_0            ((uint32_t)0x00400000)
#define GPIO_OSPEEDER_OSPEEDR11_1            ((uint32_t)0x00800000)

#define GPIO_OSPEEDER_OSPEEDR12              ((uint32_t)0x03000000)
#define GPIO_OSPEEDER_OSPEEDR12_0            ((uint32_t)0x01000000)
#define GPIO_OSPEEDER_OSPEEDR12_1            ((uint32_t)0x02000000)

#define GPIO_OSPEEDER_OSPEEDR13              ((uint32_t)0x0C000000)
#define GPIO_OSPEEDER_OSPEEDR13_0            ((uint32_t)0x04000000)
#define GPIO_OSPEEDER_OSPEEDR13_1            ((uint32_t)0x08000000)

#define GPIO_OSPEEDER_OSPEEDR14              ((uint32_t)0x30000000)
#define GPIO_OSPEEDER_OSPEEDR14_0            ((uint32_t)0x10000000)
#define GPIO_OSPEEDER_OSPEEDR14_1            ((uint32_t)0x20000000)

#define GPIO_OSPEEDER_OSPEEDR15              ((uint32_t)0xC0000000)
#define GPIO_OSPEEDER_OSPEEDR15_0            ((uint32_t)0x40000000)
#define GPIO_OSPEEDER_OSPEEDR15_1            ((uint32_t)0x80000000)

#define GPIO_PUPDR_PUPDR0                    ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPDR0_0                  ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPDR0_1                  ((uint32_t)0x00000002)

#define GPIO_PUPDR_PUPDR1                    ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPDR1_0                  ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPDR1_1                  ((uint32_t)0x00000008)

#define GPIO_PUPDR_PUPDR2                    ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPDR2_0                  ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPDR2_1                  ((uint32_t)0x00000020)

#define GPIO_PUPDR_PUPDR3                    ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPDR3_0                  ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPDR3_1                  ((uint32_t)0x00000080)

#define GPIO_PUPDR_PUPDR4                    ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPDR4_0                  ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPDR4_1                  ((uint32_t)0x00000200)

#define GPIO_PUPDR_PUPDR5                    ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPDR5_0                  ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPDR5_1                  ((uint32_t)0x00000800)

#define GPIO_PUPDR_PUPDR6                    ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPDR6_0                  ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPDR6_1                  ((uint32_t)0x00002000)

#define GPIO_PUPDR_PUPDR7                    ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPDR7_0                  ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPDR7_1                  ((uint32_t)0x00008000)

#define GPIO_PUPDR_PUPDR8                    ((uint32_t)0x00030000)
#define GPIO_PUPDR_PUPDR8_0                  ((uint32_t)0x00010000)
#define GPIO_PUPDR_PUPDR8_1                  ((uint32_t)0x00020000)

#define GPIO_PUPDR_PUPDR9                    ((uint32_t)0x000C0000)
#define GPIO_PUPDR_PUPDR9_0                  ((uint32_t)0x00040000)
#define GPIO_PUPDR_PUPDR9_1                  ((uint32_t)0x00080000)

#define GPIO_PUPDR_PUPDR10                   ((uint32_t)0x00300000)
#define GPIO_PUPDR_PUPDR10_0                 ((uint32_t)0x00100000)
#define GPIO_PUPDR_PUPDR10_1                 ((uint32_t)0x00200000)

#define GPIO_PUPDR_PUPDR11                   ((uint32_t)0x00C00000)
#define GPIO_PUPDR_PUPDR11_0                 ((uint32_t)0x00400000)
#define GPIO_PUPDR_PUPDR11_1                 ((uint32_t)0x00800000)

#define GPIO_PUPDR_PUPDR12                   ((uint32_t)0x03000000)
#define GPIO_PUPDR_PUPDR12_0                 ((uint32_t)0x01000000)
#define GPIO_PUPDR_PUPDR12_1                 ((uint32_t)0x02000000)

#define GPIO_PUPDR_PUPDR13                   ((uint32_t)0x0C000000)
#define GPIO_PUPDR_PUPDR13_0                 ((uint32_t)0x04000000)
#define GPIO_PUPDR_PUPDR13_1                 ((uint32_t)0x08000000)

#define GPIO_PUPDR_PUPDR14                   ((uint32_t)0x30000000)
#define GPIO_PUPDR_PUPDR14_0                 ((uint32_t)0x10000000)
#define GPIO_PUPDR_PUPDR14_1                 ((uint32_t)0x20000000)

#define GPIO_PUPDR_PUPDR15                   ((uint32_t)0xC0000000)
#define GPIO_PUPDR_PUPDR15_0                 ((uint32_t)0x40000000)
#define GPIO_PUPDR_PUPDR15_1                 ((uint32_t)0x80000000)

#define GPIO_IDR_IDR_0                       ((uint32_t)0x00000001)
#define GPIO_IDR_IDR_1                       ((uint32_t)0x00000002)
#define GPIO_IDR_IDR_2                       ((uint32_t)0x00000004)
#define GPIO_IDR_IDR_3                       ((uint32_t)0x00000008)
#define GPIO_IDR_IDR_4                       ((uint32_t)0x00000010)
#define GPIO_IDR_IDR_5                       ((uint32_t)0x00000020)
#define GPIO_IDR_IDR_6                       ((uint32_t)0x00000040)
#define GPIO_IDR_IDR_7                       ((uint32_t)0x00000080)
#define GPIO_IDR_IDR_8                       ((uint32_t)0x00000100)
#define GPIO_IDR_IDR_9                       ((uint32_t)0x00000200)
#define GPIO_IDR_IDR_10                      ((uint32_t)0x00000400)
#define GPIO_IDR_IDR_11                      ((uint32_t)0x00000800)
#define GPIO_IDR_IDR_12                      ((uint32_t)0x00001000)
#define GPIO_IDR_IDR_13                      ((uint32_t)0x00002000)
#define GPIO_IDR_IDR_14                      ((uint32_t)0x00004000)
#define GPIO_IDR_IDR_15                      ((uint32_t)0x00008000)

#define GPIO_OTYPER_IDR_0                    GPIO_IDR_IDR_0
#define GPIO_OTYPER_IDR_1                    GPIO_IDR_IDR_1
#define GPIO_OTYPER_IDR_2                    GPIO_IDR_IDR_2
#define GPIO_OTYPER_IDR_3                    GPIO_IDR_IDR_3
#define GPIO_OTYPER_IDR_4                    GPIO_IDR_IDR_4
#define GPIO_OTYPER_IDR_5                    GPIO_IDR_IDR_5
#define GPIO_OTYPER_IDR_6                    GPIO_IDR_IDR_6
#define GPIO_OTYPER_IDR_7                    GPIO_IDR_IDR_7
#define GPIO_OTYPER_IDR_8                    GPIO_IDR_IDR_8
#define GPIO_OTYPER_IDR_9                    GPIO_IDR_IDR_9
#define GPIO_OTYPER_IDR_10                   GPIO_IDR_IDR_10
#define GPIO_OTYPER_IDR_11                   GPIO_IDR_IDR_11
#define GPIO_OTYPER_IDR_12                   GPIO_IDR_IDR_12
#define GPIO_OTYPER_IDR_13                   GPIO_IDR_IDR_13
#define GPIO_OTYPER_IDR_14                   GPIO_IDR_IDR_14
#define GPIO_OTYPER_IDR_15                   GPIO_IDR_IDR_15

#define GPIO_ODR_ODR_0                       ((uint32_t)0x00000001)
#define GPIO_ODR_ODR_1                       ((uint32_t)0x00000002)
#define GPIO_ODR_ODR_2                       ((uint32_t)0x00000004)
#define GPIO_ODR_ODR_3                       ((uint32_t)0x00000008)
#define GPIO_ODR_ODR_4                       ((uint32_t)0x00000010)
#define GPIO_ODR_ODR_5                       ((uint32_t)0x00000020)
#define GPIO_ODR_ODR_6                       ((uint32_t)0x00000040)
#define GPIO_ODR_ODR_7                       ((uint32_t)0x00000080)
#define GPIO_ODR_ODR_8                       ((uint32_t)0x00000100)
#define GPIO_ODR_ODR_9                       ((uint32_t)0x00000200)
#define GPIO_ODR_ODR_10                      ((uint32_t)0x00000400)
#define GPIO_ODR_ODR_11                      ((uint32_t)0x00000800)
#define GPIO_ODR_ODR_12                      ((uint32_t)0x00001000)
#define GPIO_ODR_ODR_13                      ((uint32_t)0x00002000)
#define GPIO_ODR_ODR_14                      ((uint32_t)0x00004000)
#define GPIO_ODR_ODR_15                      ((uint32_t)0x00008000)

#define GPIO_OTYPER_ODR_0                    GPIO_ODR_ODR_0
#define GPIO_OTYPER_ODR_1                    GPIO_ODR_ODR_1
#define GPIO_OTYPER_ODR_2                    GPIO_ODR_ODR_2
#define GPIO_OTYPER_ODR_3                    GPIO_ODR_ODR_3
#define GPIO_OTYPER_ODR_4                    GPIO_ODR_ODR_4
#define GPIO_OTYPER_ODR_5                    GPIO_ODR_ODR_5
#define GPIO_OTYPER_ODR_6                    GPIO_ODR_ODR_6
#define GPIO_OTYPER_ODR_7                    GPIO_ODR_ODR_7
#define GPIO_OTYPER_ODR_8                    GPIO_ODR_ODR_8
#define GPIO_OTYPER_ODR_9                    GPIO_ODR_ODR_9
#define GPIO_OTYPER_ODR_10                   GPIO_ODR_ODR_10
#define GPIO_OTYPER_ODR_11                   GPIO_ODR_ODR_11
#define GPIO_OTYPER_ODR_12                   GPIO_ODR_ODR_12
#define GPIO_OTYPER_ODR_13                   GPIO_ODR_ODR_13
#define GPIO_OTYPER_ODR_14                   GPIO_ODR_ODR_14
#define GPIO_OTYPER_ODR_15                   GPIO_ODR_ODR_15

#define GPIO_BSRR_BS_0                       ((uint32_t)0x00000001)
#define GPIO_BSRR_BS_1                       ((uint32_t)0x00000002)
#define GPIO_BSRR_BS_2                       ((uint32_t)0x00000004)
#define GPIO_BSRR_BS_3                       ((uint32_t)0x00000008)
#define GPIO_BSRR_BS_4                       ((uint32_t)0x00000010)
#define GPIO_BSRR_BS_5                       ((uint32_t)0x00000020)
#define GPIO_BSRR_BS_6                       ((uint32_t)0x00000040)
#define GPIO_BSRR_BS_7                       ((uint32_t)0x00000080)
#define GPIO_BSRR_BS_8                       ((uint32_t)0x00000100)
#define GPIO_BSRR_BS_9                       ((uint32_t)0x00000200)
#define GPIO_BSRR_BS_10                      ((uint32_t)0x00000400)
#define GPIO_BSRR_BS_11                      ((uint32_t)0x00000800)
#define GPIO_BSRR_BS_12                      ((uint32_t)0x00001000)
#define GPIO_BSRR_BS_13                      ((uint32_t)0x00002000)
#define GPIO_BSRR_BS_14                      ((uint32_t)0x00004000)
#define GPIO_BSRR_BS_15                      ((uint32_t)0x00008000)
#define GPIO_BSRR_BR_0                       ((uint32_t)0x00010000)
#define GPIO_BSRR_BR_1                       ((uint32_t)0x00020000)
#define GPIO_BSRR_BR_2                       ((uint32_t)0x00040000)
#define GPIO_BSRR_BR_3                       ((uint32_t)0x00080000)
#define GPIO_BSRR_BR_4                       ((uint32_t)0x00100000)
#define GPIO_BSRR_BR_5                       ((uint32_t)0x00200000)
#define GPIO_BSRR_BR_6                       ((uint32_t)0x00400000)
#define GPIO_BSRR_BR_7                       ((uint32_t)0x00800000)
#define GPIO_BSRR_BR_8                       ((uint32_t)0x01000000)
#define GPIO_BSRR_BR_9                       ((uint32_t)0x02000000)
#define GPIO_BSRR_BR_10                      ((uint32_t)0x04000000)
#define GPIO_BSRR_BR_11                      ((uint32_t)0x08000000)
#define GPIO_BSRR_BR_12                      ((uint32_t)0x10000000)
#define GPIO_BSRR_BR_13                      ((uint32_t)0x20000000)
#define GPIO_BSRR_BR_14                      ((uint32_t)0x40000000)
#define GPIO_BSRR_BR_15                      ((uint32_t)0x80000000)

#define HASH_CR_INIT                         ((uint32_t)0x00000004)
#define HASH_CR_DMAE                         ((uint32_t)0x00000008)
#define HASH_CR_DATATYPE                     ((uint32_t)0x00000030)
#define HASH_CR_DATATYPE_0                   ((uint32_t)0x00000010)
#define HASH_CR_DATATYPE_1                   ((uint32_t)0x00000020)
#define HASH_CR_MODE                         ((uint32_t)0x00000040)
#define HASH_CR_ALGO                         ((uint32_t)0x00040080)
#define HASH_CR_ALGO_0                       ((uint32_t)0x00000080)
#define HASH_CR_ALGO_1                       ((uint32_t)0x00040000)
#define HASH_CR_NBW                          ((uint32_t)0x00000F00)
#define HASH_CR_NBW_0                        ((uint32_t)0x00000100)
#define HASH_CR_NBW_1                        ((uint32_t)0x00000200)
#define HASH_CR_NBW_2                        ((uint32_t)0x00000400)
#define HASH_CR_NBW_3                        ((uint32_t)0x00000800)
#define HASH_CR_DINNE                        ((uint32_t)0x00001000)
#define HASH_CR_MDMAT                        ((uint32_t)0x00002000)
#define HASH_CR_LKEY                         ((uint32_t)0x00010000)

#define HASH_STR_NBW                         ((uint32_t)0x0000001F)
#define HASH_STR_NBW_0                       ((uint32_t)0x00000001)
#define HASH_STR_NBW_1                       ((uint32_t)0x00000002)
#define HASH_STR_NBW_2                       ((uint32_t)0x00000004)
#define HASH_STR_NBW_3                       ((uint32_t)0x00000008)
#define HASH_STR_NBW_4                       ((uint32_t)0x00000010)
#define HASH_STR_DCAL                        ((uint32_t)0x00000100)

#define HASH_IMR_DINIM                       ((uint32_t)0x00000001)
#define HASH_IMR_DCIM                        ((uint32_t)0x00000002)

#define HASH_SR_DINIS                        ((uint32_t)0x00000001)
#define HASH_SR_DCIS                         ((uint32_t)0x00000002)
#define HASH_SR_DMAS                         ((uint32_t)0x00000004)
#define HASH_SR_BUSY                         ((uint32_t)0x00000008)

#define  I2C_CR1_PE                          ((uint16_t)0x0001)            
#define  I2C_CR1_SMBUS                       ((uint16_t)0x0002)            
#define  I2C_CR1_SMBTYPE                     ((uint16_t)0x0008)            
#define  I2C_CR1_ENARP                       ((uint16_t)0x0010)            
#define  I2C_CR1_ENPEC                       ((uint16_t)0x0020)            
#define  I2C_CR1_ENGC                        ((uint16_t)0x0040)            
#define  I2C_CR1_NOSTRETCH                   ((uint16_t)0x0080)            
#define  I2C_CR1_START                       ((uint16_t)0x0100)            
#define  I2C_CR1_STOP                        ((uint16_t)0x0200)            
#define  I2C_CR1_ACK                         ((uint16_t)0x0400)            
#define  I2C_CR1_POS                         ((uint16_t)0x0800)            
#define  I2C_CR1_PEC                         ((uint16_t)0x1000)            
#define  I2C_CR1_ALERT                       ((uint16_t)0x2000)            
#define  I2C_CR1_SWRST                       ((uint16_t)0x8000)            

#define  I2C_CR2_FREQ                        ((uint16_t)0x003F)            
#define  I2C_CR2_FREQ_0                      ((uint16_t)0x0001)            
#define  I2C_CR2_FREQ_1                      ((uint16_t)0x0002)            
#define  I2C_CR2_FREQ_2                      ((uint16_t)0x0004)            
#define  I2C_CR2_FREQ_3                      ((uint16_t)0x0008)            
#define  I2C_CR2_FREQ_4                      ((uint16_t)0x0010)            
#define  I2C_CR2_FREQ_5                      ((uint16_t)0x0020)            

#define  I2C_CR2_ITERREN                     ((uint16_t)0x0100)            
#define  I2C_CR2_ITEVTEN                     ((uint16_t)0x0200)            
#define  I2C_CR2_ITBUFEN                     ((uint16_t)0x0400)            
#define  I2C_CR2_DMAEN                       ((uint16_t)0x0800)            
#define  I2C_CR2_LAST                        ((uint16_t)0x1000)            

#define  I2C_OAR1_ADD1_7                     ((uint16_t)0x00FE)            
#define  I2C_OAR1_ADD8_9                     ((uint16_t)0x0300)            

#define  I2C_OAR1_ADD0                       ((uint16_t)0x0001)            
#define  I2C_OAR1_ADD1                       ((uint16_t)0x0002)            
#define  I2C_OAR1_ADD2                       ((uint16_t)0x0004)            
#define  I2C_OAR1_ADD3                       ((uint16_t)0x0008)            
#define  I2C_OAR1_ADD4                       ((uint16_t)0x0010)            
#define  I2C_OAR1_ADD5                       ((uint16_t)0x0020)            
#define  I2C_OAR1_ADD6                       ((uint16_t)0x0040)            
#define  I2C_OAR1_ADD7                       ((uint16_t)0x0080)            
#define  I2C_OAR1_ADD8                       ((uint16_t)0x0100)            
#define  I2C_OAR1_ADD9                       ((uint16_t)0x0200)            

#define  I2C_OAR1_ADDMODE                    ((uint16_t)0x8000)            

#define  I2C_OAR2_ENDUAL                     ((uint8_t)0x01)               
#define  I2C_OAR2_ADD2                       ((uint8_t)0xFE)               

#define  I2C_DR_DR                           ((uint8_t)0xFF)               

#define  I2C_SR1_SB                          ((uint16_t)0x0001)            
#define  I2C_SR1_ADDR                        ((uint16_t)0x0002)            
#define  I2C_SR1_BTF                         ((uint16_t)0x0004)            
#define  I2C_SR1_ADD10                       ((uint16_t)0x0008)            
#define  I2C_SR1_STOPF                       ((uint16_t)0x0010)            
#define  I2C_SR1_RXNE                        ((uint16_t)0x0040)            
#define  I2C_SR1_TXE                         ((uint16_t)0x0080)            
#define  I2C_SR1_BERR                        ((uint16_t)0x0100)            
#define  I2C_SR1_ARLO                        ((uint16_t)0x0200)            
#define  I2C_SR1_AF                          ((uint16_t)0x0400)            
#define  I2C_SR1_OVR                         ((uint16_t)0x0800)            
#define  I2C_SR1_PECERR                      ((uint16_t)0x1000)            
#define  I2C_SR1_TIMEOUT                     ((uint16_t)0x4000)            
#define  I2C_SR1_SMBALERT                    ((uint16_t)0x8000)            

#define  I2C_SR2_MSL                         ((uint16_t)0x0001)            
#define  I2C_SR2_BUSY                        ((uint16_t)0x0002)            
#define  I2C_SR2_TRA                         ((uint16_t)0x0004)            
#define  I2C_SR2_GENCALL                     ((uint16_t)0x0010)            
#define  I2C_SR2_SMBDEFAULT                  ((uint16_t)0x0020)            
#define  I2C_SR2_SMBHOST                     ((uint16_t)0x0040)            
#define  I2C_SR2_DUALF                       ((uint16_t)0x0080)            
#define  I2C_SR2_PEC                         ((uint16_t)0xFF00)            

#define  I2C_CCR_CCR                         ((uint16_t)0x0FFF)            
#define  I2C_CCR_DUTY                        ((uint16_t)0x4000)            
#define  I2C_CCR_FS                          ((uint16_t)0x8000)            

#define  I2C_TRISE_TRISE                     ((uint8_t)0x3F)               

#define  I2C_FLTR_DNF                     ((uint8_t)0x0F)                  
#define  I2C_FLTR_ANOFF                   ((uint8_t)0x10)                  

#define  IWDG_KR_KEY                         ((uint16_t)0xFFFF)            

#define  IWDG_PR_PR                          ((uint8_t)0x07)               
#define  IWDG_PR_PR_0                        ((uint8_t)0x01)               
#define  IWDG_PR_PR_1                        ((uint8_t)0x02)               
#define  IWDG_PR_PR_2                        ((uint8_t)0x04)               

#define  IWDG_RLR_RL                         ((uint16_t)0x0FFF)            

#define  IWDG_SR_PVU                         ((uint8_t)0x01)               
#define  IWDG_SR_RVU                         ((uint8_t)0x02)               

#define LTDC_SSCR_VSH                       ((uint32_t)0x000007FF)              
#define LTDC_SSCR_HSW                       ((uint32_t)0x0FFF0000)              

#define LTDC_BPCR_AVBP                      ((uint32_t)0x000007FF)              
#define LTDC_BPCR_AHBP                      ((uint32_t)0x0FFF0000)              

#define LTDC_AWCR_AAH                       ((uint32_t)0x000007FF)              
#define LTDC_AWCR_AAW                       ((uint32_t)0x0FFF0000)              

#define LTDC_TWCR_TOTALH                    ((uint32_t)0x000007FF)              
#define LTDC_TWCR_TOTALW                    ((uint32_t)0x0FFF0000)              

#define LTDC_GCR_LTDCEN                     ((uint32_t)0x00000001)              
#define LTDC_GCR_DBW                        ((uint32_t)0x00000070)              
#define LTDC_GCR_DGW                        ((uint32_t)0x00000700)              
#define LTDC_GCR_DRW                        ((uint32_t)0x00007000)              
#define LTDC_GCR_DTEN                       ((uint32_t)0x00010000)              
#define LTDC_GCR_PCPOL                      ((uint32_t)0x10000000)              
#define LTDC_GCR_DEPOL                      ((uint32_t)0x20000000)              
#define LTDC_GCR_VSPOL                      ((uint32_t)0x40000000)              
#define LTDC_GCR_HSPOL                      ((uint32_t)0x80000000)              

#define LTDC_SRCR_IMR                      ((uint32_t)0x00000001)               
#define LTDC_SRCR_VBR                      ((uint32_t)0x00000002)               

#define LTDC_BCCR_BCBLUE                    ((uint32_t)0x000000FF)              
#define LTDC_BCCR_BCGREEN                   ((uint32_t)0x0000FF00)              
#define LTDC_BCCR_BCRED                     ((uint32_t)0x00FF0000)              

#define LTDC_IER_LIE                        ((uint32_t)0x00000001)              
#define LTDC_IER_FUIE                       ((uint32_t)0x00000002)              
#define LTDC_IER_TERRIE                     ((uint32_t)0x00000004)              
#define LTDC_IER_RRIE                       ((uint32_t)0x00000008)              

#define LTDC_ISR_LIF                        ((uint32_t)0x00000001)              
#define LTDC_ISR_FUIF                       ((uint32_t)0x00000002)              
#define LTDC_ISR_TERRIF                     ((uint32_t)0x00000004)              
#define LTDC_ISR_RRIF                       ((uint32_t)0x00000008)              

#define LTDC_ICR_CLIF                       ((uint32_t)0x00000001)              
#define LTDC_ICR_CFUIF                      ((uint32_t)0x00000002)              
#define LTDC_ICR_CTERRIF                    ((uint32_t)0x00000004)              
#define LTDC_ICR_CRRIF                      ((uint32_t)0x00000008)              

#define LTDC_LIPCR_LIPOS                    ((uint32_t)0x000007FF)              

#define LTDC_CPSR_CYPOS                     ((uint32_t)0x0000FFFF)              
#define LTDC_CPSR_CXPOS                     ((uint32_t)0xFFFF0000)              

#define LTDC_CDSR_VDES                      ((uint32_t)0x00000001)              
#define LTDC_CDSR_HDES                      ((uint32_t)0x00000002)              
#define LTDC_CDSR_VSYNCS                    ((uint32_t)0x00000004)              
#define LTDC_CDSR_HSYNCS                    ((uint32_t)0x00000008)              

#define LTDC_LxCR_LEN                       ((uint32_t)0x00000001)              
#define LTDC_LxCR_COLKEN                    ((uint32_t)0x00000002)              
#define LTDC_LxCR_CLUTEN                    ((uint32_t)0x00000010)              

#define LTDC_LxWHPCR_WHSTPOS                ((uint32_t)0x00000FFF)              
#define LTDC_LxWHPCR_WHSPPOS                ((uint32_t)0xFFFF0000)              

#define LTDC_LxWVPCR_WVSTPOS                ((uint32_t)0x00000FFF)              
#define LTDC_LxWVPCR_WVSPPOS                ((uint32_t)0xFFFF0000)              

#define LTDC_LxCKCR_CKBLUE                  ((uint32_t)0x000000FF)              
#define LTDC_LxCKCR_CKGREEN                 ((uint32_t)0x0000FF00)              
#define LTDC_LxCKCR_CKRED                   ((uint32_t)0x00FF0000)              

#define LTDC_LxPFCR_PF                      ((uint32_t)0x00000007)              

#define LTDC_LxCACR_CONSTA                  ((uint32_t)0x000000FF)              

#define LTDC_LxDCCR_DCBLUE                  ((uint32_t)0x000000FF)              
#define LTDC_LxDCCR_DCGREEN                 ((uint32_t)0x0000FF00)              
#define LTDC_LxDCCR_DCRED                   ((uint32_t)0x00FF0000)              
#define LTDC_LxDCCR_DCALPHA                 ((uint32_t)0xFF000000)              
                                

#define LTDC_LxBFCR_BF2                     ((uint32_t)0x00000007)              
#define LTDC_LxBFCR_BF1                     ((uint32_t)0x00000700)              

#define LTDC_LxCFBAR_CFBADD                 ((uint32_t)0xFFFFFFFF)              

#define LTDC_LxCFBLR_CFBLL                  ((uint32_t)0x00001FFF)              
#define LTDC_LxCFBLR_CFBP                   ((uint32_t)0x1FFF0000)              

#define LTDC_LxCFBLNR_CFBLNBR               ((uint32_t)0x000007FF)              

#define LTDC_LxCLUTWR_BLUE                  ((uint32_t)0x000000FF)              
#define LTDC_LxCLUTWR_GREEN                 ((uint32_t)0x0000FF00)              
#define LTDC_LxCLUTWR_RED                   ((uint32_t)0x00FF0000)              
#define LTDC_LxCLUTWR_CLUTADD               ((uint32_t)0xFF000000)              

#define  PWR_CR_LPDS                         ((uint32_t)0x00000001)     
#define  PWR_CR_PDDS                         ((uint32_t)0x00000002)     
#define  PWR_CR_CWUF                         ((uint32_t)0x00000004)     
#define  PWR_CR_CSBF                         ((uint32_t)0x00000008)     
#define  PWR_CR_PVDE                         ((uint32_t)0x00000010)     

#define  PWR_CR_PLS                          ((uint32_t)0x000000E0)     
#define  PWR_CR_PLS_0                        ((uint32_t)0x00000020)     
#define  PWR_CR_PLS_1                        ((uint32_t)0x00000040)     
#define  PWR_CR_PLS_2                        ((uint32_t)0x00000080)     

#define  PWR_CR_PLS_LEV0                     ((uint32_t)0x00000000)     
#define  PWR_CR_PLS_LEV1                     ((uint32_t)0x00000020)     
#define  PWR_CR_PLS_LEV2                     ((uint32_t)0x00000040)     
#define  PWR_CR_PLS_LEV3                     ((uint32_t)0x00000060)     
#define  PWR_CR_PLS_LEV4                     ((uint32_t)0x00000080)     
#define  PWR_CR_PLS_LEV5                     ((uint32_t)0x000000A0)     
#define  PWR_CR_PLS_LEV6                     ((uint32_t)0x000000C0)     
#define  PWR_CR_PLS_LEV7                     ((uint32_t)0x000000E0)     

#define  PWR_CR_DBP                          ((uint32_t)0x00000100)     
#define  PWR_CR_FPDS                         ((uint32_t)0x00000200)     
#define  PWR_CR_LPUDS                        ((uint32_t)0x00000400)     
#define  PWR_CR_MRUDS                        ((uint32_t)0x00000800)     
#define  PWR_CR_LPLVDS                       ((uint32_t)0x00000400)     
#define  PWR_CR_MRLVDS                       ((uint32_t)0x00000800)     

#define  PWR_CR_ADCDC1                       ((uint32_t)0x00002000)      

#define  PWR_CR_VOS                          ((uint32_t)0x0000C000)     
#define  PWR_CR_VOS_0                        ((uint32_t)0x00004000)     
#define  PWR_CR_VOS_1                        ((uint32_t)0x00008000)     

#define  PWR_CR_ODEN                         ((uint32_t)0x00010000)     
#define  PWR_CR_ODSWEN                       ((uint32_t)0x00020000)     
#define  PWR_CR_UDEN                         ((uint32_t)0x000C0000)     
#define  PWR_CR_UDEN_0                       ((uint32_t)0x00040000)     
#define  PWR_CR_UDEN_1                       ((uint32_t)0x00080000)     

#define  PWR_CR_FMSSR                        ((uint32_t)0x00100000)     
#define  PWR_CR_FISSR                        ((uint32_t)0x00200000)     

#define  PWR_CR_PMODE                        PWR_CR_VOS

#define  PWR_CSR_WUF                         ((uint32_t)0x00000001)     
#define  PWR_CSR_SBF                         ((uint32_t)0x00000002)     
#define  PWR_CSR_PVDO                        ((uint32_t)0x00000004)     
#define  PWR_CSR_BRR                         ((uint32_t)0x00000008)     
#define  PWR_CSR_EWUP                        ((uint32_t)0x00000100)     
#define  PWR_CSR_BRE                         ((uint32_t)0x00000200)     
#define  PWR_CSR_VOSRDY                      ((uint32_t)0x00004000)     
#define  PWR_CSR_ODRDY                       ((uint32_t)0x00010000)     
#define  PWR_CSR_ODSWRDY                     ((uint32_t)0x00020000)     
#define  PWR_CSR_UDSWRDY                     ((uint32_t)0x000C0000)     

#define  PWR_CSR_REGRDY                      PWR_CSR_VOSRDY

#define  RCC_CR_HSION                        ((uint32_t)0x00000001)
#define  RCC_CR_HSIRDY                       ((uint32_t)0x00000002)

#define  RCC_CR_HSITRIM                      ((uint32_t)0x000000F8)
#define  RCC_CR_HSITRIM_0                    ((uint32_t)0x00000008)
#define  RCC_CR_HSITRIM_1                    ((uint32_t)0x00000010)
#define  RCC_CR_HSITRIM_2                    ((uint32_t)0x00000020)
#define  RCC_CR_HSITRIM_3                    ((uint32_t)0x00000040)
#define  RCC_CR_HSITRIM_4                    ((uint32_t)0x00000080)

#define  RCC_CR_HSICAL                       ((uint32_t)0x0000FF00)
#define  RCC_CR_HSICAL_0                     ((uint32_t)0x00000100)
#define  RCC_CR_HSICAL_1                     ((uint32_t)0x00000200)
#define  RCC_CR_HSICAL_2                     ((uint32_t)0x00000400)
#define  RCC_CR_HSICAL_3                     ((uint32_t)0x00000800)
#define  RCC_CR_HSICAL_4                     ((uint32_t)0x00001000)
#define  RCC_CR_HSICAL_5                     ((uint32_t)0x00002000)
#define  RCC_CR_HSICAL_6                     ((uint32_t)0x00004000)
#define  RCC_CR_HSICAL_7                     ((uint32_t)0x00008000)

#define  RCC_CR_HSEON                        ((uint32_t)0x00010000)
#define  RCC_CR_HSERDY                       ((uint32_t)0x00020000)
#define  RCC_CR_HSEBYP                       ((uint32_t)0x00040000)
#define  RCC_CR_CSSON                        ((uint32_t)0x00080000)
#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)
#define  RCC_CR_PLLI2SON                     ((uint32_t)0x04000000)
#define  RCC_CR_PLLI2SRDY                    ((uint32_t)0x08000000)
#define  RCC_CR_PLLSAION                     ((uint32_t)0x10000000)
#define  RCC_CR_PLLSAIRDY                    ((uint32_t)0x20000000)

#define  RCC_PLLCFGR_PLLM                    ((uint32_t)0x0000003F)
#define  RCC_PLLCFGR_PLLM_0                  ((uint32_t)0x00000001)
#define  RCC_PLLCFGR_PLLM_1                  ((uint32_t)0x00000002)
#define  RCC_PLLCFGR_PLLM_2                  ((uint32_t)0x00000004)
#define  RCC_PLLCFGR_PLLM_3                  ((uint32_t)0x00000008)
#define  RCC_PLLCFGR_PLLM_4                  ((uint32_t)0x00000010)
#define  RCC_PLLCFGR_PLLM_5                  ((uint32_t)0x00000020)

#define  RCC_PLLCFGR_PLLN                     ((uint32_t)0x00007FC0)
#define  RCC_PLLCFGR_PLLN_0                   ((uint32_t)0x00000040)
#define  RCC_PLLCFGR_PLLN_1                   ((uint32_t)0x00000080)
#define  RCC_PLLCFGR_PLLN_2                   ((uint32_t)0x00000100)
#define  RCC_PLLCFGR_PLLN_3                   ((uint32_t)0x00000200)
#define  RCC_PLLCFGR_PLLN_4                   ((uint32_t)0x00000400)
#define  RCC_PLLCFGR_PLLN_5                   ((uint32_t)0x00000800)
#define  RCC_PLLCFGR_PLLN_6                   ((uint32_t)0x00001000)
#define  RCC_PLLCFGR_PLLN_7                   ((uint32_t)0x00002000)
#define  RCC_PLLCFGR_PLLN_8                   ((uint32_t)0x00004000)

#define  RCC_PLLCFGR_PLLP                    ((uint32_t)0x00030000)
#define  RCC_PLLCFGR_PLLP_0                  ((uint32_t)0x00010000)
#define  RCC_PLLCFGR_PLLP_1                  ((uint32_t)0x00020000)

#define  RCC_PLLCFGR_PLLSRC                  ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSE              ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSI              ((uint32_t)0x00000000)

#define  RCC_PLLCFGR_PLLQ                    ((uint32_t)0x0F000000)
#define  RCC_PLLCFGR_PLLQ_0                  ((uint32_t)0x01000000)
#define  RCC_PLLCFGR_PLLQ_1                  ((uint32_t)0x02000000)
#define  RCC_PLLCFGR_PLLQ_2                  ((uint32_t)0x04000000)
#define  RCC_PLLCFGR_PLLQ_3                  ((uint32_t)0x08000000)

#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        
#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        
#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        

#define  RCC_CFGR_SW_HSI                     ((uint32_t)0x00000000)        
#define  RCC_CFGR_SW_HSE                     ((uint32_t)0x00000001)        
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)        

#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        
#define  RCC_CFGR_SWS_0                      ((uint32_t)0x00000004)        
#define  RCC_CFGR_SWS_1                      ((uint32_t)0x00000008)        

#define  RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000000)        
#define  RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000004)        
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)        

#define  RCC_CFGR_HPRE                       ((uint32_t)0x000000F0)        
#define  RCC_CFGR_HPRE_0                     ((uint32_t)0x00000010)        
#define  RCC_CFGR_HPRE_1                     ((uint32_t)0x00000020)        
#define  RCC_CFGR_HPRE_2                     ((uint32_t)0x00000040)        
#define  RCC_CFGR_HPRE_3                     ((uint32_t)0x00000080)        

#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        

#define  RCC_CFGR_PPRE1                      ((uint32_t)0x00001C00)        
#define  RCC_CFGR_PPRE1_0                    ((uint32_t)0x00000400)        
#define  RCC_CFGR_PPRE1_1                    ((uint32_t)0x00000800)        
#define  RCC_CFGR_PPRE1_2                    ((uint32_t)0x00001000)        

#define  RCC_CFGR_PPRE1_DIV1                 ((uint32_t)0x00000000)        
#define  RCC_CFGR_PPRE1_DIV2                 ((uint32_t)0x00001000)        
#define  RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00001400)        
#define  RCC_CFGR_PPRE1_DIV8                 ((uint32_t)0x00001800)        
#define  RCC_CFGR_PPRE1_DIV16                ((uint32_t)0x00001C00)        

#define  RCC_CFGR_PPRE2                      ((uint32_t)0x0000E000)        
#define  RCC_CFGR_PPRE2_0                    ((uint32_t)0x00002000)        
#define  RCC_CFGR_PPRE2_1                    ((uint32_t)0x00004000)        
#define  RCC_CFGR_PPRE2_2                    ((uint32_t)0x00008000)        

#define  RCC_CFGR_PPRE2_DIV1                 ((uint32_t)0x00000000)        
#define  RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00008000)        
#define  RCC_CFGR_PPRE2_DIV4                 ((uint32_t)0x0000A000)        
#define  RCC_CFGR_PPRE2_DIV8                 ((uint32_t)0x0000C000)        
#define  RCC_CFGR_PPRE2_DIV16                ((uint32_t)0x0000E000)        

#define  RCC_CFGR_RTCPRE                     ((uint32_t)0x001F0000)
#define  RCC_CFGR_RTCPRE_0                   ((uint32_t)0x00010000)
#define  RCC_CFGR_RTCPRE_1                   ((uint32_t)0x00020000)
#define  RCC_CFGR_RTCPRE_2                   ((uint32_t)0x00040000)
#define  RCC_CFGR_RTCPRE_3                   ((uint32_t)0x00080000)
#define  RCC_CFGR_RTCPRE_4                   ((uint32_t)0x00100000)

#define  RCC_CFGR_MCO1                       ((uint32_t)0x00600000)
#define  RCC_CFGR_MCO1_0                     ((uint32_t)0x00200000)
#define  RCC_CFGR_MCO1_1                     ((uint32_t)0x00400000)

#define  RCC_CFGR_I2SSRC                     ((uint32_t)0x00800000)

#define  RCC_CFGR_MCO1PRE                    ((uint32_t)0x07000000)
#define  RCC_CFGR_MCO1PRE_0                  ((uint32_t)0x01000000)
#define  RCC_CFGR_MCO1PRE_1                  ((uint32_t)0x02000000)
#define  RCC_CFGR_MCO1PRE_2                  ((uint32_t)0x04000000)

#define  RCC_CFGR_MCO2PRE                    ((uint32_t)0x38000000)
#define  RCC_CFGR_MCO2PRE_0                  ((uint32_t)0x08000000)
#define  RCC_CFGR_MCO2PRE_1                  ((uint32_t)0x10000000)
#define  RCC_CFGR_MCO2PRE_2                  ((uint32_t)0x20000000)

#define  RCC_CFGR_MCO2                       ((uint32_t)0xC0000000)
#define  RCC_CFGR_MCO2_0                     ((uint32_t)0x40000000)
#define  RCC_CFGR_MCO2_1                     ((uint32_t)0x80000000)

#define  RCC_CIR_LSIRDYF                     ((uint32_t)0x00000001)
#define  RCC_CIR_LSERDYF                     ((uint32_t)0x00000002)
#define  RCC_CIR_HSIRDYF                     ((uint32_t)0x00000004)
#define  RCC_CIR_HSERDYF                     ((uint32_t)0x00000008)
#define  RCC_CIR_PLLRDYF                     ((uint32_t)0x00000010)
#define  RCC_CIR_PLLI2SRDYF                  ((uint32_t)0x00000020)
#define  RCC_CIR_PLLSAIRDYF                  ((uint32_t)0x00000040)
#define  RCC_CIR_CSSF                        ((uint32_t)0x00000080)
#define  RCC_CIR_LSIRDYIE                    ((uint32_t)0x00000100)
#define  RCC_CIR_LSERDYIE                    ((uint32_t)0x00000200)
#define  RCC_CIR_HSIRDYIE                    ((uint32_t)0x00000400)
#define  RCC_CIR_HSERDYIE                    ((uint32_t)0x00000800)
#define  RCC_CIR_PLLRDYIE                    ((uint32_t)0x00001000)
#define  RCC_CIR_PLLI2SRDYIE                 ((uint32_t)0x00002000)
#define  RCC_CIR_PLLSAIRDYIE                 ((uint32_t)0x00004000)
#define  RCC_CIR_LSIRDYC                     ((uint32_t)0x00010000)
#define  RCC_CIR_LSERDYC                     ((uint32_t)0x00020000)
#define  RCC_CIR_HSIRDYC                     ((uint32_t)0x00040000)
#define  RCC_CIR_HSERDYC                     ((uint32_t)0x00080000)
#define  RCC_CIR_PLLRDYC                     ((uint32_t)0x00100000)
#define  RCC_CIR_PLLI2SRDYC                  ((uint32_t)0x00200000)
#define  RCC_CIR_PLLSAIRDYC                  ((uint32_t)0x00400000)
#define  RCC_CIR_CSSC                        ((uint32_t)0x00800000)

#define  RCC_AHB1RSTR_GPIOARST               ((uint32_t)0x00000001)
#define  RCC_AHB1RSTR_GPIOBRST               ((uint32_t)0x00000002)
#define  RCC_AHB1RSTR_GPIOCRST               ((uint32_t)0x00000004)
#define  RCC_AHB1RSTR_GPIODRST               ((uint32_t)0x00000008)
#define  RCC_AHB1RSTR_GPIOERST               ((uint32_t)0x00000010)
#define  RCC_AHB1RSTR_GPIOFRST               ((uint32_t)0x00000020)
#define  RCC_AHB1RSTR_GPIOGRST               ((uint32_t)0x00000040)
#define  RCC_AHB1RSTR_GPIOHRST               ((uint32_t)0x00000080)
#define  RCC_AHB1RSTR_GPIOIRST               ((uint32_t)0x00000100)
#define  RCC_AHB1RSTR_GPIOJRST               ((uint32_t)0x00000200)
#define  RCC_AHB1RSTR_GPIOKRST               ((uint32_t)0x00000400)
#define  RCC_AHB1RSTR_CRCRST                 ((uint32_t)0x00001000)
#define  RCC_AHB1RSTR_DMA1RST                ((uint32_t)0x00200000)
#define  RCC_AHB1RSTR_DMA2RST                ((uint32_t)0x00400000)
#define  RCC_AHB1RSTR_DMA2DRST               ((uint32_t)0x00800000)
#define  RCC_AHB1RSTR_ETHMACRST              ((uint32_t)0x02000000)
#define  RCC_AHB1RSTR_OTGHRST                ((uint32_t)0x10000000)

#define  RCC_AHB2RSTR_DCMIRST                ((uint32_t)0x00000001)
#define  RCC_AHB2RSTR_CRYPRST                ((uint32_t)0x00000010)
#define  RCC_AHB2RSTR_HASHRST                ((uint32_t)0x00000020)
 
 #define  RCC_AHB2RSTR_HSAHRST                RCC_AHB2RSTR_HASHRST
#define  RCC_AHB2RSTR_RNGRST                 ((uint32_t)0x00000040)
#define  RCC_AHB2RSTR_OTGFSRST               ((uint32_t)0x00000080)

#if defined(STM32F40_41xxx)
#define  RCC_AHB3RSTR_FSMCRST                ((uint32_t)0x00000001)
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define  RCC_AHB3RSTR_FMCRST                ((uint32_t)0x00000001)
#endif 

#define  RCC_APB1RSTR_TIM2RST                ((uint32_t)0x00000001)
#define  RCC_APB1RSTR_TIM3RST                ((uint32_t)0x00000002)
#define  RCC_APB1RSTR_TIM4RST                ((uint32_t)0x00000004)
#define  RCC_APB1RSTR_TIM5RST                ((uint32_t)0x00000008)
#define  RCC_APB1RSTR_TIM6RST                ((uint32_t)0x00000010)
#define  RCC_APB1RSTR_TIM7RST                ((uint32_t)0x00000020)
#define  RCC_APB1RSTR_TIM12RST               ((uint32_t)0x00000040)
#define  RCC_APB1RSTR_TIM13RST               ((uint32_t)0x00000080)
#define  RCC_APB1RSTR_TIM14RST               ((uint32_t)0x00000100)
#define  RCC_APB1RSTR_WWDGRST                ((uint32_t)0x00000800)
#define  RCC_APB1RSTR_SPI2RST                ((uint32_t)0x00004000)
#define  RCC_APB1RSTR_SPI3RST                ((uint32_t)0x00008000)
#define  RCC_APB1RSTR_USART2RST              ((uint32_t)0x00020000)
#define  RCC_APB1RSTR_USART3RST              ((uint32_t)0x00040000)
#define  RCC_APB1RSTR_UART4RST               ((uint32_t)0x00080000)
#define  RCC_APB1RSTR_UART5RST               ((uint32_t)0x00100000)
#define  RCC_APB1RSTR_I2C1RST                ((uint32_t)0x00200000)
#define  RCC_APB1RSTR_I2C2RST                ((uint32_t)0x00400000)
#define  RCC_APB1RSTR_I2C3RST                ((uint32_t)0x00800000)
#define  RCC_APB1RSTR_CAN1RST                ((uint32_t)0x02000000)
#define  RCC_APB1RSTR_CAN2RST                ((uint32_t)0x04000000)
#define  RCC_APB1RSTR_PWRRST                 ((uint32_t)0x10000000)
#define  RCC_APB1RSTR_DACRST                 ((uint32_t)0x20000000)
#define  RCC_APB1RSTR_UART7RST               ((uint32_t)0x40000000)
#define  RCC_APB1RSTR_UART8RST               ((uint32_t)0x80000000)

#define  RCC_APB2RSTR_TIM1RST                ((uint32_t)0x00000001)
#define  RCC_APB2RSTR_TIM8RST                ((uint32_t)0x00000002)
#define  RCC_APB2RSTR_USART1RST              ((uint32_t)0x00000010)
#define  RCC_APB2RSTR_USART6RST              ((uint32_t)0x00000020)
#define  RCC_APB2RSTR_ADCRST                 ((uint32_t)0x00000100)
#define  RCC_APB2RSTR_SDIORST                ((uint32_t)0x00000800)
#define  RCC_APB2RSTR_SPI1RST                ((uint32_t)0x00001000)
#define  RCC_APB2RSTR_SPI4RST                ((uint32_t)0x00002000)
#define  RCC_APB2RSTR_SYSCFGRST              ((uint32_t)0x00004000)
#define  RCC_APB2RSTR_TIM9RST                ((uint32_t)0x00010000)
#define  RCC_APB2RSTR_TIM10RST               ((uint32_t)0x00020000)
#define  RCC_APB2RSTR_TIM11RST               ((uint32_t)0x00040000)
#define  RCC_APB2RSTR_SPI5RST                ((uint32_t)0x00100000)
#define  RCC_APB2RSTR_SPI6RST                ((uint32_t)0x00200000)
#define  RCC_APB2RSTR_SAI1RST                ((uint32_t)0x00400000)
#define  RCC_APB2RSTR_LTDCRST                ((uint32_t)0x04000000)

#define  RCC_APB2RSTR_SPI1                   RCC_APB2RSTR_SPI1RST

#define  RCC_AHB1ENR_GPIOAEN                 ((uint32_t)0x00000001)
#define  RCC_AHB1ENR_GPIOBEN                 ((uint32_t)0x00000002)
#define  RCC_AHB1ENR_GPIOCEN                 ((uint32_t)0x00000004)
#define  RCC_AHB1ENR_GPIODEN                 ((uint32_t)0x00000008)
#define  RCC_AHB1ENR_GPIOEEN                 ((uint32_t)0x00000010)
#define  RCC_AHB1ENR_GPIOFEN                 ((uint32_t)0x00000020)
#define  RCC_AHB1ENR_GPIOGEN                 ((uint32_t)0x00000040)
#define  RCC_AHB1ENR_GPIOHEN                 ((uint32_t)0x00000080)
#define  RCC_AHB1ENR_GPIOIEN                 ((uint32_t)0x00000100)
#define  RCC_AHB1ENR_GPIOJEN                 ((uint32_t)0x00000200)
#define  RCC_AHB1ENR_GPIOKEN                 ((uint32_t)0x00000400)
#define  RCC_AHB1ENR_CRCEN                   ((uint32_t)0x00001000)
#define  RCC_AHB1ENR_BKPSRAMEN               ((uint32_t)0x00040000)
#define  RCC_AHB1ENR_CCMDATARAMEN            ((uint32_t)0x00100000)
#define  RCC_AHB1ENR_DMA1EN                  ((uint32_t)0x00200000)
#define  RCC_AHB1ENR_DMA2EN                  ((uint32_t)0x00400000)
#define  RCC_AHB1ENR_DMA2DEN                 ((uint32_t)0x00800000)
#define  RCC_AHB1ENR_ETHMACEN                ((uint32_t)0x02000000)
#define  RCC_AHB1ENR_ETHMACTXEN              ((uint32_t)0x04000000)
#define  RCC_AHB1ENR_ETHMACRXEN              ((uint32_t)0x08000000)
#define  RCC_AHB1ENR_ETHMACPTPEN             ((uint32_t)0x10000000)
#define  RCC_AHB1ENR_OTGHSEN                 ((uint32_t)0x20000000)
#define  RCC_AHB1ENR_OTGHSULPIEN             ((uint32_t)0x40000000)

#define  RCC_AHB2ENR_DCMIEN                  ((uint32_t)0x00000001)
#define  RCC_AHB2ENR_CRYPEN                  ((uint32_t)0x00000010)
#define  RCC_AHB2ENR_HASHEN                  ((uint32_t)0x00000020)
#define  RCC_AHB2ENR_RNGEN                   ((uint32_t)0x00000040)
#define  RCC_AHB2ENR_OTGFSEN                 ((uint32_t)0x00000080)

#if defined(STM32F40_41xxx)
#define  RCC_AHB3ENR_FSMCEN                  ((uint32_t)0x00000001)
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define  RCC_AHB3ENR_FMCEN                  ((uint32_t)0x00000001)
#endif 

#define  RCC_APB1ENR_TIM2EN                  ((uint32_t)0x00000001)
#define  RCC_APB1ENR_TIM3EN                  ((uint32_t)0x00000002)
#define  RCC_APB1ENR_TIM4EN                  ((uint32_t)0x00000004)
#define  RCC_APB1ENR_TIM5EN                  ((uint32_t)0x00000008)
#define  RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)
#define  RCC_APB1ENR_TIM7EN                  ((uint32_t)0x00000020)
#define  RCC_APB1ENR_TIM12EN                 ((uint32_t)0x00000040)
#define  RCC_APB1ENR_TIM13EN                 ((uint32_t)0x00000080)
#define  RCC_APB1ENR_TIM14EN                 ((uint32_t)0x00000100)
#define  RCC_APB1ENR_WWDGEN                  ((uint32_t)0x00000800)
#define  RCC_APB1ENR_SPI2EN                  ((uint32_t)0x00004000)
#define  RCC_APB1ENR_SPI3EN                  ((uint32_t)0x00008000)
#define  RCC_APB1ENR_USART2EN                ((uint32_t)0x00020000)
#define  RCC_APB1ENR_USART3EN                ((uint32_t)0x00040000)
#define  RCC_APB1ENR_UART4EN                 ((uint32_t)0x00080000)
#define  RCC_APB1ENR_UART5EN                 ((uint32_t)0x00100000)
#define  RCC_APB1ENR_I2C1EN                  ((uint32_t)0x00200000)
#define  RCC_APB1ENR_I2C2EN                  ((uint32_t)0x00400000)
#define  RCC_APB1ENR_I2C3EN                  ((uint32_t)0x00800000)
#define  RCC_APB1ENR_CAN1EN                  ((uint32_t)0x02000000)
#define  RCC_APB1ENR_CAN2EN                  ((uint32_t)0x04000000)
#define  RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)
#define  RCC_APB1ENR_DACEN                   ((uint32_t)0x20000000)
#define  RCC_APB1ENR_UART7EN                 ((uint32_t)0x40000000)
#define  RCC_APB1ENR_UART8EN                 ((uint32_t)0x80000000)

#define  RCC_APB2ENR_TIM1EN                  ((uint32_t)0x00000001)
#define  RCC_APB2ENR_TIM8EN                  ((uint32_t)0x00000002)
#define  RCC_APB2ENR_USART1EN                ((uint32_t)0x00000010)
#define  RCC_APB2ENR_USART6EN                ((uint32_t)0x00000020)
#define  RCC_APB2ENR_ADC1EN                  ((uint32_t)0x00000100)
#define  RCC_APB2ENR_ADC2EN                  ((uint32_t)0x00000200)
#define  RCC_APB2ENR_ADC3EN                  ((uint32_t)0x00000400)
#define  RCC_APB2ENR_SDIOEN                  ((uint32_t)0x00000800)
#define  RCC_APB2ENR_SPI1EN                  ((uint32_t)0x00001000)
#define  RCC_APB2ENR_SPI4EN                  ((uint32_t)0x00002000)
#define  RCC_APB2ENR_SYSCFGEN                ((uint32_t)0x00004000)
#define  RCC_APB2ENR_TIM9EN                  ((uint32_t)0x00010000)
#define  RCC_APB2ENR_TIM10EN                 ((uint32_t)0x00020000)
#define  RCC_APB2ENR_TIM11EN                 ((uint32_t)0x00040000)
#define  RCC_APB2ENR_SPI5EN                  ((uint32_t)0x00100000)
#define  RCC_APB2ENR_SPI6EN                  ((uint32_t)0x00200000)
#define  RCC_APB2ENR_SAI1EN                  ((uint32_t)0x00400000)
#define  RCC_APB2ENR_LTDCEN                  ((uint32_t)0x04000000)

#define  RCC_AHB1LPENR_GPIOALPEN             ((uint32_t)0x00000001)
#define  RCC_AHB1LPENR_GPIOBLPEN             ((uint32_t)0x00000002)
#define  RCC_AHB1LPENR_GPIOCLPEN             ((uint32_t)0x00000004)
#define  RCC_AHB1LPENR_GPIODLPEN             ((uint32_t)0x00000008)
#define  RCC_AHB1LPENR_GPIOELPEN             ((uint32_t)0x00000010)
#define  RCC_AHB1LPENR_GPIOFLPEN             ((uint32_t)0x00000020)
#define  RCC_AHB1LPENR_GPIOGLPEN             ((uint32_t)0x00000040)
#define  RCC_AHB1LPENR_GPIOHLPEN             ((uint32_t)0x00000080)
#define  RCC_AHB1LPENR_GPIOILPEN             ((uint32_t)0x00000100)
#define  RCC_AHB1LPENR_GPIOJLPEN             ((uint32_t)0x00000200)
#define  RCC_AHB1LPENR_GPIOKLPEN             ((uint32_t)0x00000400)
#define  RCC_AHB1LPENR_CRCLPEN               ((uint32_t)0x00001000)
#define  RCC_AHB1LPENR_FLITFLPEN             ((uint32_t)0x00008000)
#define  RCC_AHB1LPENR_SRAM1LPEN             ((uint32_t)0x00010000)
#define  RCC_AHB1LPENR_SRAM2LPEN             ((uint32_t)0x00020000)
#define  RCC_AHB1LPENR_BKPSRAMLPEN           ((uint32_t)0x00040000)
#define  RCC_AHB1LPENR_SRAM3LPEN             ((uint32_t)0x00080000)
#define  RCC_AHB1LPENR_DMA1LPEN              ((uint32_t)0x00200000)
#define  RCC_AHB1LPENR_DMA2LPEN              ((uint32_t)0x00400000)
#define  RCC_AHB1LPENR_DMA2DLPEN             ((uint32_t)0x00800000)
#define  RCC_AHB1LPENR_ETHMACLPEN            ((uint32_t)0x02000000)
#define  RCC_AHB1LPENR_ETHMACTXLPEN          ((uint32_t)0x04000000)
#define  RCC_AHB1LPENR_ETHMACRXLPEN          ((uint32_t)0x08000000)
#define  RCC_AHB1LPENR_ETHMACPTPLPEN         ((uint32_t)0x10000000)
#define  RCC_AHB1LPENR_OTGHSLPEN             ((uint32_t)0x20000000)
#define  RCC_AHB1LPENR_OTGHSULPILPEN         ((uint32_t)0x40000000)

#define  RCC_AHB2LPENR_DCMILPEN              ((uint32_t)0x00000001)
#define  RCC_AHB2LPENR_CRYPLPEN              ((uint32_t)0x00000010)
#define  RCC_AHB2LPENR_HASHLPEN              ((uint32_t)0x00000020)
#define  RCC_AHB2LPENR_RNGLPEN               ((uint32_t)0x00000040)
#define  RCC_AHB2LPENR_OTGFSLPEN             ((uint32_t)0x00000080)

#if defined(STM32F40_41xxx)
#define  RCC_AHB3LPENR_FSMCLPEN              ((uint32_t)0x00000001)
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define  RCC_AHB3LPENR_FMCLPEN              ((uint32_t)0x00000001)
#endif 

#define  RCC_APB1LPENR_TIM2LPEN              ((uint32_t)0x00000001)
#define  RCC_APB1LPENR_TIM3LPEN              ((uint32_t)0x00000002)
#define  RCC_APB1LPENR_TIM4LPEN              ((uint32_t)0x00000004)
#define  RCC_APB1LPENR_TIM5LPEN              ((uint32_t)0x00000008)
#define  RCC_APB1LPENR_TIM6LPEN              ((uint32_t)0x00000010)
#define  RCC_APB1LPENR_TIM7LPEN              ((uint32_t)0x00000020)
#define  RCC_APB1LPENR_TIM12LPEN             ((uint32_t)0x00000040)
#define  RCC_APB1LPENR_TIM13LPEN             ((uint32_t)0x00000080)
#define  RCC_APB1LPENR_TIM14LPEN             ((uint32_t)0x00000100)
#define  RCC_APB1LPENR_WWDGLPEN              ((uint32_t)0x00000800)
#define  RCC_APB1LPENR_SPI2LPEN              ((uint32_t)0x00004000)
#define  RCC_APB1LPENR_SPI3LPEN              ((uint32_t)0x00008000)
#define  RCC_APB1LPENR_USART2LPEN            ((uint32_t)0x00020000)
#define  RCC_APB1LPENR_USART3LPEN            ((uint32_t)0x00040000)
#define  RCC_APB1LPENR_UART4LPEN             ((uint32_t)0x00080000)
#define  RCC_APB1LPENR_UART5LPEN             ((uint32_t)0x00100000)
#define  RCC_APB1LPENR_I2C1LPEN              ((uint32_t)0x00200000)
#define  RCC_APB1LPENR_I2C2LPEN              ((uint32_t)0x00400000)
#define  RCC_APB1LPENR_I2C3LPEN              ((uint32_t)0x00800000)
#define  RCC_APB1LPENR_CAN1LPEN              ((uint32_t)0x02000000)
#define  RCC_APB1LPENR_CAN2LPEN              ((uint32_t)0x04000000)
#define  RCC_APB1LPENR_PWRLPEN               ((uint32_t)0x10000000)
#define  RCC_APB1LPENR_DACLPEN               ((uint32_t)0x20000000)
#define  RCC_APB1LPENR_UART7LPEN             ((uint32_t)0x40000000)
#define  RCC_APB1LPENR_UART8LPEN             ((uint32_t)0x80000000)

#define  RCC_APB2LPENR_TIM1LPEN              ((uint32_t)0x00000001)
#define  RCC_APB2LPENR_TIM8LPEN              ((uint32_t)0x00000002)
#define  RCC_APB2LPENR_USART1LPEN            ((uint32_t)0x00000010)
#define  RCC_APB2LPENR_USART6LPEN            ((uint32_t)0x00000020)
#define  RCC_APB2LPENR_ADC1LPEN              ((uint32_t)0x00000100)
#define  RCC_APB2LPENR_ADC2PEN               ((uint32_t)0x00000200)
#define  RCC_APB2LPENR_ADC3LPEN              ((uint32_t)0x00000400)
#define  RCC_APB2LPENR_SDIOLPEN              ((uint32_t)0x00000800)
#define  RCC_APB2LPENR_SPI1LPEN              ((uint32_t)0x00001000)
#define  RCC_APB2LPENR_SPI4LPEN              ((uint32_t)0x00002000)
#define  RCC_APB2LPENR_SYSCFGLPEN            ((uint32_t)0x00004000)
#define  RCC_APB2LPENR_TIM9LPEN              ((uint32_t)0x00010000)
#define  RCC_APB2LPENR_TIM10LPEN             ((uint32_t)0x00020000)
#define  RCC_APB2LPENR_TIM11LPEN             ((uint32_t)0x00040000)
#define  RCC_APB2LPENR_SPI5LPEN              ((uint32_t)0x00100000)
#define  RCC_APB2LPENR_SPI6LPEN              ((uint32_t)0x00200000)
#define  RCC_APB2LPENR_SAI1LPEN              ((uint32_t)0x00400000)
#define  RCC_APB2LPENR_LTDCLPEN              ((uint32_t)0x04000000)

#define  RCC_BDCR_LSEON                      ((uint32_t)0x00000001)
#define  RCC_BDCR_LSERDY                     ((uint32_t)0x00000002)
#define  RCC_BDCR_LSEBYP                     ((uint32_t)0x00000004)
#define  RCC_BDCR_LSEMOD                     ((uint32_t)0x00000008)

#define  RCC_BDCR_RTCSEL                    ((uint32_t)0x00000300)
#define  RCC_BDCR_RTCSEL_0                  ((uint32_t)0x00000100)
#define  RCC_BDCR_RTCSEL_1                  ((uint32_t)0x00000200)

#define  RCC_BDCR_RTCEN                      ((uint32_t)0x00008000)
#define  RCC_BDCR_BDRST                      ((uint32_t)0x00010000)

#define  RCC_CSR_LSION                       ((uint32_t)0x00000001)
#define  RCC_CSR_LSIRDY                      ((uint32_t)0x00000002)
#define  RCC_CSR_RMVF                        ((uint32_t)0x01000000)
#define  RCC_CSR_BORRSTF                     ((uint32_t)0x02000000)
#define  RCC_CSR_PADRSTF                     ((uint32_t)0x04000000)
#define  RCC_CSR_PORRSTF                     ((uint32_t)0x08000000)
#define  RCC_CSR_SFTRSTF                     ((uint32_t)0x10000000)
#define  RCC_CSR_WDGRSTF                     ((uint32_t)0x20000000)
#define  RCC_CSR_WWDGRSTF                    ((uint32_t)0x40000000)
#define  RCC_CSR_LPWRRSTF                    ((uint32_t)0x80000000)

#define  RCC_SSCGR_MODPER                    ((uint32_t)0x00001FFF)
#define  RCC_SSCGR_INCSTEP                   ((uint32_t)0x0FFFE000)
#define  RCC_SSCGR_SPREADSEL                 ((uint32_t)0x40000000)
#define  RCC_SSCGR_SSCGEN                    ((uint32_t)0x80000000)

#define  RCC_PLLI2SCFGR_PLLI2SM              ((uint32_t)0x0000003F)
#define  RCC_PLLI2SCFGR_PLLI2SM_0            ((uint32_t)0x00000001)
#define  RCC_PLLI2SCFGR_PLLI2SM_1            ((uint32_t)0x00000002)
#define  RCC_PLLI2SCFGR_PLLI2SM_2            ((uint32_t)0x00000004)
#define  RCC_PLLI2SCFGR_PLLI2SM_3            ((uint32_t)0x00000008)
#define  RCC_PLLI2SCFGR_PLLI2SM_4            ((uint32_t)0x00000010)
#define  RCC_PLLI2SCFGR_PLLI2SM_5            ((uint32_t)0x00000020)

#define  RCC_PLLI2SCFGR_PLLI2SN              ((uint32_t)0x00007FC0)
#define  RCC_PLLI2SCFGR_PLLI2SQ              ((uint32_t)0x0F000000)
#define  RCC_PLLI2SCFGR_PLLI2SR              ((uint32_t)0x70000000)

#define  RCC_PLLSAICFGR_PLLI2SN              ((uint32_t)0x00007FC0)
#define  RCC_PLLSAICFGR_PLLI2SQ              ((uint32_t)0x0F000000)
#define  RCC_PLLSAICFGR_PLLI2SR              ((uint32_t)0x70000000)

#define  RCC_DCKCFGR_PLLI2SDIVQ              ((uint32_t)0x0000001F)
#define  RCC_DCKCFGR_PLLSAIDIVQ              ((uint32_t)0x00001F00)
#define  RCC_DCKCFGR_PLLSAIDIVR              ((uint32_t)0x00030000)
#define  RCC_DCKCFGR_SAI1ASRC                ((uint32_t)0x00300000)
#define  RCC_DCKCFGR_SAI1BSRC                ((uint32_t)0x00C00000)
#define  RCC_DCKCFGR_TIMPRE                  ((uint32_t)0x01000000)

#define RNG_CR_RNGEN                         ((uint32_t)0x00000004)
#define RNG_CR_IE                            ((uint32_t)0x00000008)

#define RNG_SR_DRDY                          ((uint32_t)0x00000001)
#define RNG_SR_CECS                          ((uint32_t)0x00000002)
#define RNG_SR_SECS                          ((uint32_t)0x00000004)
#define RNG_SR_CEIS                          ((uint32_t)0x00000020)
#define RNG_SR_SEIS                          ((uint32_t)0x00000040)

#define RTC_TR_PM                            ((uint32_t)0x00400000)
#define RTC_TR_HT                            ((uint32_t)0x00300000)
#define RTC_TR_HT_0                          ((uint32_t)0x00100000)
#define RTC_TR_HT_1                          ((uint32_t)0x00200000)
#define RTC_TR_HU                            ((uint32_t)0x000F0000)
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)
#define RTC_TR_MNT                           ((uint32_t)0x00007000)
#define RTC_TR_MNT_0                         ((uint32_t)0x00001000)
#define RTC_TR_MNT_1                         ((uint32_t)0x00002000)
#define RTC_TR_MNT_2                         ((uint32_t)0x00004000)
#define RTC_TR_MNU                           ((uint32_t)0x00000F00)
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)
#define RTC_TR_ST                            ((uint32_t)0x00000070)
#define RTC_TR_ST_0                          ((uint32_t)0x00000010)
#define RTC_TR_ST_1                          ((uint32_t)0x00000020)
#define RTC_TR_ST_2                          ((uint32_t)0x00000040)
#define RTC_TR_SU                            ((uint32_t)0x0000000F)
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)

#define RTC_DR_YT                            ((uint32_t)0x00F00000)
#define RTC_DR_YT_0                          ((uint32_t)0x00100000)
#define RTC_DR_YT_1                          ((uint32_t)0x00200000)
#define RTC_DR_YT_2                          ((uint32_t)0x00400000)
#define RTC_DR_YT_3                          ((uint32_t)0x00800000)
#define RTC_DR_YU                            ((uint32_t)0x000F0000)
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)
#define RTC_DR_WDU                           ((uint32_t)0x0000E000)
#define RTC_DR_WDU_0                         ((uint32_t)0x00002000)
#define RTC_DR_WDU_1                         ((uint32_t)0x00004000)
#define RTC_DR_WDU_2                         ((uint32_t)0x00008000)
#define RTC_DR_MT                            ((uint32_t)0x00001000)
#define RTC_DR_MU                            ((uint32_t)0x00000F00)
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)
#define RTC_DR_DT                            ((uint32_t)0x00000030)
#define RTC_DR_DT_0                          ((uint32_t)0x00000010)
#define RTC_DR_DT_1                          ((uint32_t)0x00000020)
#define RTC_DR_DU                            ((uint32_t)0x0000000F)
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)

#define RTC_CR_COE                           ((uint32_t)0x00800000)
#define RTC_CR_OSEL                          ((uint32_t)0x00600000)
#define RTC_CR_OSEL_0                        ((uint32_t)0x00200000)
#define RTC_CR_OSEL_1                        ((uint32_t)0x00400000)
#define RTC_CR_POL                           ((uint32_t)0x00100000)
#define RTC_CR_COSEL                         ((uint32_t)0x00080000)
#define RTC_CR_BCK                           ((uint32_t)0x00040000)
#define RTC_CR_SUB1H                         ((uint32_t)0x00020000)
#define RTC_CR_ADD1H                         ((uint32_t)0x00010000)
#define RTC_CR_TSIE                          ((uint32_t)0x00008000)
#define RTC_CR_WUTIE                         ((uint32_t)0x00004000)
#define RTC_CR_ALRBIE                        ((uint32_t)0x00002000)
#define RTC_CR_ALRAIE                        ((uint32_t)0x00001000)
#define RTC_CR_TSE                           ((uint32_t)0x00000800)
#define RTC_CR_WUTE                          ((uint32_t)0x00000400)
#define RTC_CR_ALRBE                         ((uint32_t)0x00000200)
#define RTC_CR_ALRAE                         ((uint32_t)0x00000100)
#define RTC_CR_DCE                           ((uint32_t)0x00000080)
#define RTC_CR_FMT                           ((uint32_t)0x00000040)
#define RTC_CR_BYPSHAD                       ((uint32_t)0x00000020)
#define RTC_CR_REFCKON                       ((uint32_t)0x00000010)
#define RTC_CR_TSEDGE                        ((uint32_t)0x00000008)
#define RTC_CR_WUCKSEL                       ((uint32_t)0x00000007)
#define RTC_CR_WUCKSEL_0                     ((uint32_t)0x00000001)
#define RTC_CR_WUCKSEL_1                     ((uint32_t)0x00000002)
#define RTC_CR_WUCKSEL_2                     ((uint32_t)0x00000004)

#define RTC_ISR_RECALPF                      ((uint32_t)0x00010000)
#define RTC_ISR_TAMP1F                       ((uint32_t)0x00002000)
#define RTC_ISR_TSOVF                        ((uint32_t)0x00001000)
#define RTC_ISR_TSF                          ((uint32_t)0x00000800)
#define RTC_ISR_WUTF                         ((uint32_t)0x00000400)
#define RTC_ISR_ALRBF                        ((uint32_t)0x00000200)
#define RTC_ISR_ALRAF                        ((uint32_t)0x00000100)
#define RTC_ISR_INIT                         ((uint32_t)0x00000080)
#define RTC_ISR_INITF                        ((uint32_t)0x00000040)
#define RTC_ISR_RSF                          ((uint32_t)0x00000020)
#define RTC_ISR_INITS                        ((uint32_t)0x00000010)
#define RTC_ISR_SHPF                         ((uint32_t)0x00000008)
#define RTC_ISR_WUTWF                        ((uint32_t)0x00000004)
#define RTC_ISR_ALRBWF                       ((uint32_t)0x00000002)
#define RTC_ISR_ALRAWF                       ((uint32_t)0x00000001)

#define RTC_PRER_PREDIV_A                    ((uint32_t)0x007F0000)
#define RTC_PRER_PREDIV_S                    ((uint32_t)0x00001FFF)

#define RTC_WUTR_WUT                         ((uint32_t)0x0000FFFF)

#define RTC_CALIBR_DCS                       ((uint32_t)0x00000080)
#define RTC_CALIBR_DC                        ((uint32_t)0x0000001F)

#define RTC_ALRMAR_MSK4                      ((uint32_t)0x80000000)
#define RTC_ALRMAR_WDSEL                     ((uint32_t)0x40000000)
#define RTC_ALRMAR_DT                        ((uint32_t)0x30000000)
#define RTC_ALRMAR_DT_0                      ((uint32_t)0x10000000)
#define RTC_ALRMAR_DT_1                      ((uint32_t)0x20000000)
#define RTC_ALRMAR_DU                        ((uint32_t)0x0F000000)
#define RTC_ALRMAR_DU_0                      ((uint32_t)0x01000000)
#define RTC_ALRMAR_DU_1                      ((uint32_t)0x02000000)
#define RTC_ALRMAR_DU_2                      ((uint32_t)0x04000000)
#define RTC_ALRMAR_DU_3                      ((uint32_t)0x08000000)
#define RTC_ALRMAR_MSK3                      ((uint32_t)0x00800000)
#define RTC_ALRMAR_PM                        ((uint32_t)0x00400000)
#define RTC_ALRMAR_HT                        ((uint32_t)0x00300000)
#define RTC_ALRMAR_HT_0                      ((uint32_t)0x00100000)
#define RTC_ALRMAR_HT_1                      ((uint32_t)0x00200000)
#define RTC_ALRMAR_HU                        ((uint32_t)0x000F0000)
#define RTC_ALRMAR_HU_0                      ((uint32_t)0x00010000)
#define RTC_ALRMAR_HU_1                      ((uint32_t)0x00020000)
#define RTC_ALRMAR_HU_2                      ((uint32_t)0x00040000)
#define RTC_ALRMAR_HU_3                      ((uint32_t)0x00080000)
#define RTC_ALRMAR_MSK2                      ((uint32_t)0x00008000)
#define RTC_ALRMAR_MNT                       ((uint32_t)0x00007000)
#define RTC_ALRMAR_MNT_0                     ((uint32_t)0x00001000)
#define RTC_ALRMAR_MNT_1                     ((uint32_t)0x00002000)
#define RTC_ALRMAR_MNT_2                     ((uint32_t)0x00004000)
#define RTC_ALRMAR_MNU                       ((uint32_t)0x00000F00)
#define RTC_ALRMAR_MNU_0                     ((uint32_t)0x00000100)
#define RTC_ALRMAR_MNU_1                     ((uint32_t)0x00000200)
#define RTC_ALRMAR_MNU_2                     ((uint32_t)0x00000400)
#define RTC_ALRMAR_MNU_3                     ((uint32_t)0x00000800)
#define RTC_ALRMAR_MSK1                      ((uint32_t)0x00000080)
#define RTC_ALRMAR_ST                        ((uint32_t)0x00000070)
#define RTC_ALRMAR_ST_0                      ((uint32_t)0x00000010)
#define RTC_ALRMAR_ST_1                      ((uint32_t)0x00000020)
#define RTC_ALRMAR_ST_2                      ((uint32_t)0x00000040)
#define RTC_ALRMAR_SU                        ((uint32_t)0x0000000F)
#define RTC_ALRMAR_SU_0                      ((uint32_t)0x00000001)
#define RTC_ALRMAR_SU_1                      ((uint32_t)0x00000002)
#define RTC_ALRMAR_SU_2                      ((uint32_t)0x00000004)
#define RTC_ALRMAR_SU_3                      ((uint32_t)0x00000008)

#define RTC_ALRMBR_MSK4                      ((uint32_t)0x80000000)
#define RTC_ALRMBR_WDSEL                     ((uint32_t)0x40000000)
#define RTC_ALRMBR_DT                        ((uint32_t)0x30000000)
#define RTC_ALRMBR_DT_0                      ((uint32_t)0x10000000)
#define RTC_ALRMBR_DT_1                      ((uint32_t)0x20000000)
#define RTC_ALRMBR_DU                        ((uint32_t)0x0F000000)
#define RTC_ALRMBR_DU_0                      ((uint32_t)0x01000000)
#define RTC_ALRMBR_DU_1                      ((uint32_t)0x02000000)
#define RTC_ALRMBR_DU_2                      ((uint32_t)0x04000000)
#define RTC_ALRMBR_DU_3                      ((uint32_t)0x08000000)
#define RTC_ALRMBR_MSK3                      ((uint32_t)0x00800000)
#define RTC_ALRMBR_PM                        ((uint32_t)0x00400000)
#define RTC_ALRMBR_HT                        ((uint32_t)0x00300000)
#define RTC_ALRMBR_HT_0                      ((uint32_t)0x00100000)
#define RTC_ALRMBR_HT_1                      ((uint32_t)0x00200000)
#define RTC_ALRMBR_HU                        ((uint32_t)0x000F0000)
#define RTC_ALRMBR_HU_0                      ((uint32_t)0x00010000)
#define RTC_ALRMBR_HU_1                      ((uint32_t)0x00020000)
#define RTC_ALRMBR_HU_2                      ((uint32_t)0x00040000)
#define RTC_ALRMBR_HU_3                      ((uint32_t)0x00080000)
#define RTC_ALRMBR_MSK2                      ((uint32_t)0x00008000)
#define RTC_ALRMBR_MNT                       ((uint32_t)0x00007000)
#define RTC_ALRMBR_MNT_0                     ((uint32_t)0x00001000)
#define RTC_ALRMBR_MNT_1                     ((uint32_t)0x00002000)
#define RTC_ALRMBR_MNT_2                     ((uint32_t)0x00004000)
#define RTC_ALRMBR_MNU                       ((uint32_t)0x00000F00)
#define RTC_ALRMBR_MNU_0                     ((uint32_t)0x00000100)
#define RTC_ALRMBR_MNU_1                     ((uint32_t)0x00000200)
#define RTC_ALRMBR_MNU_2                     ((uint32_t)0x00000400)
#define RTC_ALRMBR_MNU_3                     ((uint32_t)0x00000800)
#define RTC_ALRMBR_MSK1                      ((uint32_t)0x00000080)
#define RTC_ALRMBR_ST                        ((uint32_t)0x00000070)
#define RTC_ALRMBR_ST_0                      ((uint32_t)0x00000010)
#define RTC_ALRMBR_ST_1                      ((uint32_t)0x00000020)
#define RTC_ALRMBR_ST_2                      ((uint32_t)0x00000040)
#define RTC_ALRMBR_SU                        ((uint32_t)0x0000000F)
#define RTC_ALRMBR_SU_0                      ((uint32_t)0x00000001)
#define RTC_ALRMBR_SU_1                      ((uint32_t)0x00000002)
#define RTC_ALRMBR_SU_2                      ((uint32_t)0x00000004)
#define RTC_ALRMBR_SU_3                      ((uint32_t)0x00000008)

#define RTC_WPR_KEY                          ((uint32_t)0x000000FF)

#define RTC_SSR_SS                           ((uint32_t)0x0000FFFF)

#define RTC_SHIFTR_SUBFS                     ((uint32_t)0x00007FFF)
#define RTC_SHIFTR_ADD1S                     ((uint32_t)0x80000000)

#define RTC_TSTR_PM                          ((uint32_t)0x00400000)
#define RTC_TSTR_HT                          ((uint32_t)0x00300000)
#define RTC_TSTR_HT_0                        ((uint32_t)0x00100000)
#define RTC_TSTR_HT_1                        ((uint32_t)0x00200000)
#define RTC_TSTR_HU                          ((uint32_t)0x000F0000)
#define RTC_TSTR_HU_0                        ((uint32_t)0x00010000)
#define RTC_TSTR_HU_1                        ((uint32_t)0x00020000)
#define RTC_TSTR_HU_2                        ((uint32_t)0x00040000)
#define RTC_TSTR_HU_3                        ((uint32_t)0x00080000)
#define RTC_TSTR_MNT                         ((uint32_t)0x00007000)
#define RTC_TSTR_MNT_0                       ((uint32_t)0x00001000)
#define RTC_TSTR_MNT_1                       ((uint32_t)0x00002000)
#define RTC_TSTR_MNT_2                       ((uint32_t)0x00004000)
#define RTC_TSTR_MNU                         ((uint32_t)0x00000F00)
#define RTC_TSTR_MNU_0                       ((uint32_t)0x00000100)
#define RTC_TSTR_MNU_1                       ((uint32_t)0x00000200)
#define RTC_TSTR_MNU_2                       ((uint32_t)0x00000400)
#define RTC_TSTR_MNU_3                       ((uint32_t)0x00000800)
#define RTC_TSTR_ST                          ((uint32_t)0x00000070)
#define RTC_TSTR_ST_0                        ((uint32_t)0x00000010)
#define RTC_TSTR_ST_1                        ((uint32_t)0x00000020)
#define RTC_TSTR_ST_2                        ((uint32_t)0x00000040)
#define RTC_TSTR_SU                          ((uint32_t)0x0000000F)
#define RTC_TSTR_SU_0                        ((uint32_t)0x00000001)
#define RTC_TSTR_SU_1                        ((uint32_t)0x00000002)
#define RTC_TSTR_SU_2                        ((uint32_t)0x00000004)
#define RTC_TSTR_SU_3                        ((uint32_t)0x00000008)

#define RTC_TSDR_WDU                         ((uint32_t)0x0000E000)
#define RTC_TSDR_WDU_0                       ((uint32_t)0x00002000)
#define RTC_TSDR_WDU_1                       ((uint32_t)0x00004000)
#define RTC_TSDR_WDU_2                       ((uint32_t)0x00008000)
#define RTC_TSDR_MT                          ((uint32_t)0x00001000)
#define RTC_TSDR_MU                          ((uint32_t)0x00000F00)
#define RTC_TSDR_MU_0                        ((uint32_t)0x00000100)
#define RTC_TSDR_MU_1                        ((uint32_t)0x00000200)
#define RTC_TSDR_MU_2                        ((uint32_t)0x00000400)
#define RTC_TSDR_MU_3                        ((uint32_t)0x00000800)
#define RTC_TSDR_DT                          ((uint32_t)0x00000030)
#define RTC_TSDR_DT_0                        ((uint32_t)0x00000010)
#define RTC_TSDR_DT_1                        ((uint32_t)0x00000020)
#define RTC_TSDR_DU                          ((uint32_t)0x0000000F)
#define RTC_TSDR_DU_0                        ((uint32_t)0x00000001)
#define RTC_TSDR_DU_1                        ((uint32_t)0x00000002)
#define RTC_TSDR_DU_2                        ((uint32_t)0x00000004)
#define RTC_TSDR_DU_3                        ((uint32_t)0x00000008)

#define RTC_TSSSR_SS                         ((uint32_t)0x0000FFFF)

#define RTC_CALR_CALP                        ((uint32_t)0x00008000)
#define RTC_CALR_CALW8                       ((uint32_t)0x00004000)
#define RTC_CALR_CALW16                      ((uint32_t)0x00002000)
#define RTC_CALR_CALM                        ((uint32_t)0x000001FF)
#define RTC_CALR_CALM_0                      ((uint32_t)0x00000001)
#define RTC_CALR_CALM_1                      ((uint32_t)0x00000002)
#define RTC_CALR_CALM_2                      ((uint32_t)0x00000004)
#define RTC_CALR_CALM_3                      ((uint32_t)0x00000008)
#define RTC_CALR_CALM_4                      ((uint32_t)0x00000010)
#define RTC_CALR_CALM_5                      ((uint32_t)0x00000020)
#define RTC_CALR_CALM_6                      ((uint32_t)0x00000040)
#define RTC_CALR_CALM_7                      ((uint32_t)0x00000080)
#define RTC_CALR_CALM_8                      ((uint32_t)0x00000100)

#define RTC_TAFCR_ALARMOUTTYPE               ((uint32_t)0x00040000)
#define RTC_TAFCR_TSINSEL                    ((uint32_t)0x00020000)
#define RTC_TAFCR_TAMPINSEL                  ((uint32_t)0x00010000)
#define RTC_TAFCR_TAMPPUDIS                  ((uint32_t)0x00008000)
#define RTC_TAFCR_TAMPPRCH                   ((uint32_t)0x00006000)
#define RTC_TAFCR_TAMPPRCH_0                 ((uint32_t)0x00002000)
#define RTC_TAFCR_TAMPPRCH_1                 ((uint32_t)0x00004000)
#define RTC_TAFCR_TAMPFLT                    ((uint32_t)0x00001800)
#define RTC_TAFCR_TAMPFLT_0                  ((uint32_t)0x00000800)
#define RTC_TAFCR_TAMPFLT_1                  ((uint32_t)0x00001000)
#define RTC_TAFCR_TAMPFREQ                   ((uint32_t)0x00000700)
#define RTC_TAFCR_TAMPFREQ_0                 ((uint32_t)0x00000100)
#define RTC_TAFCR_TAMPFREQ_1                 ((uint32_t)0x00000200)
#define RTC_TAFCR_TAMPFREQ_2                 ((uint32_t)0x00000400)
#define RTC_TAFCR_TAMPTS                     ((uint32_t)0x00000080)
#define RTC_TAFCR_TAMPIE                     ((uint32_t)0x00000004)
#define RTC_TAFCR_TAMP1TRG                   ((uint32_t)0x00000002)
#define RTC_TAFCR_TAMP1E                     ((uint32_t)0x00000001)

#define RTC_ALRMASSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMASSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMASSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMASSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMASSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMASSR_SS                      ((uint32_t)0x00007FFF)

#define RTC_ALRMBSSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMBSSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMBSSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMBSSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMBSSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMBSSR_SS                      ((uint32_t)0x00007FFF)

#define RTC_BKP0R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP1R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP2R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP3R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP4R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP5R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP6R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP7R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP8R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP9R                            ((uint32_t)0xFFFFFFFF)

#define RTC_BKP10R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP11R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP12R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP13R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP14R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP15R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP16R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP17R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP18R                           ((uint32_t)0xFFFFFFFF)

#define RTC_BKP19R                           ((uint32_t)0xFFFFFFFF)

#define  SAI_GCR_SYNCIN                  ((uint32_t)0x00000003)        
#define  SAI_GCR_SYNCIN_0                ((uint32_t)0x00000001)        
#define  SAI_GCR_SYNCIN_1                ((uint32_t)0x00000002)        

#define  SAI_GCR_SYNCOUT                 ((uint32_t)0x00000030)        
#define  SAI_GCR_SYNCOUT_0               ((uint32_t)0x00000010)        
#define  SAI_GCR_SYNCOUT_1               ((uint32_t)0x00000020)        

#define  SAI_xCR1_MODE                    ((uint32_t)0x00000003)        
#define  SAI_xCR1_MODE_0                  ((uint32_t)0x00000001)        
#define  SAI_xCR1_MODE_1                  ((uint32_t)0x00000002)        

#define  SAI_xCR1_PRTCFG                  ((uint32_t)0x0000000C)        
#define  SAI_xCR1_PRTCFG_0                ((uint32_t)0x00000004)        
#define  SAI_xCR1_PRTCFG_1                ((uint32_t)0x00000008)        

#define  SAI_xCR1_DS                      ((uint32_t)0x000000E0)        
#define  SAI_xCR1_DS_0                    ((uint32_t)0x00000020)        
#define  SAI_xCR1_DS_1                    ((uint32_t)0x00000040)        
#define  SAI_xCR1_DS_2                    ((uint32_t)0x00000080)        

#define  SAI_xCR1_LSBFIRST                ((uint32_t)0x00000100)        
#define  SAI_xCR1_CKSTR                   ((uint32_t)0x00000200)        

#define  SAI_xCR1_SYNCEN                  ((uint32_t)0x00000C00)        
#define  SAI_xCR1_SYNCEN_0                ((uint32_t)0x00000400)        
#define  SAI_xCR1_SYNCEN_1                ((uint32_t)0x00000800)        

#define  SAI_xCR1_MONO                    ((uint32_t)0x00001000)        
#define  SAI_xCR1_OUTDRIV                 ((uint32_t)0x00002000)        
#define  SAI_xCR1_SAIEN                   ((uint32_t)0x00010000)        
#define  SAI_xCR1_DMAEN                   ((uint32_t)0x00020000)        
#define  SAI_xCR1_NODIV                   ((uint32_t)0x00080000)        

#define  SAI_xCR1_MCKDIV                  ((uint32_t)0x00780000)        
#define  SAI_xCR1_MCKDIV_0                ((uint32_t)0x00080000)        
#define  SAI_xCR1_MCKDIV_1                ((uint32_t)0x00100000)        
#define  SAI_xCR1_MCKDIV_2                ((uint32_t)0x00200000)        
#define  SAI_xCR1_MCKDIV_3                ((uint32_t)0x00400000)        

#define  SAI_xCR2_FTH                     ((uint32_t)0x00000003)        
#define  SAI_xCR2_FTH_0                   ((uint32_t)0x00000001)        
#define  SAI_xCR2_FTH_1                   ((uint32_t)0x00000002)        

#define  SAI_xCR2_FFLUSH                  ((uint32_t)0x00000008)        
#define  SAI_xCR2_TRIS                    ((uint32_t)0x00000010)        
#define  SAI_xCR2_MUTE                    ((uint32_t)0x00000020)        
#define  SAI_xCR2_MUTEVAL                 ((uint32_t)0x00000040)        

#define  SAI_xCR2_MUTECNT                  ((uint32_t)0x00001F80)       
#define  SAI_xCR2_MUTECNT_0               ((uint32_t)0x00000080)        
#define  SAI_xCR2_MUTECNT_1               ((uint32_t)0x00000100)        
#define  SAI_xCR2_MUTECNT_2               ((uint32_t)0x00000200)        
#define  SAI_xCR2_MUTECNT_3               ((uint32_t)0x00000400)        
#define  SAI_xCR2_MUTECNT_4               ((uint32_t)0x00000800)        
#define  SAI_xCR2_MUTECNT_5               ((uint32_t)0x00001000)        

#define  SAI_xCR2_CPL                     ((uint32_t)0x00080000)        

#define  SAI_xCR2_COMP                    ((uint32_t)0x0000C000)        
#define  SAI_xCR2_COMP_0                  ((uint32_t)0x00004000)        
#define  SAI_xCR2_COMP_1                  ((uint32_t)0x00008000)        

#define  SAI_xFRCR_FRL                    ((uint32_t)0x000000FF)        
#define  SAI_xFRCR_FRL_0                  ((uint32_t)0x00000001)        
#define  SAI_xFRCR_FRL_1                  ((uint32_t)0x00000002)        
#define  SAI_xFRCR_FRL_2                  ((uint32_t)0x00000004)        
#define  SAI_xFRCR_FRL_3                  ((uint32_t)0x00000008)        
#define  SAI_xFRCR_FRL_4                  ((uint32_t)0x00000010)        
#define  SAI_xFRCR_FRL_5                  ((uint32_t)0x00000020)        
#define  SAI_xFRCR_FRL_6                  ((uint32_t)0x00000040)        
#define  SAI_xFRCR_FRL_7                  ((uint32_t)0x00000080)        

#define  SAI_xFRCR_FSALL                  ((uint32_t)0x00007F00)        
#define  SAI_xFRCR_FSALL_0                ((uint32_t)0x00000100)        
#define  SAI_xFRCR_FSALL_1                ((uint32_t)0x00000200)        
#define  SAI_xFRCR_FSALL_2                ((uint32_t)0x00000400)        
#define  SAI_xFRCR_FSALL_3                ((uint32_t)0x00000800)        
#define  SAI_xFRCR_FSALL_4                ((uint32_t)0x00001000)        
#define  SAI_xFRCR_FSALL_5                ((uint32_t)0x00002000)        
#define  SAI_xFRCR_FSALL_6                ((uint32_t)0x00004000)        

#define  SAI_xFRCR_FSDEF                  ((uint32_t)0x00010000)        
#define  SAI_xFRCR_FSPO                   ((uint32_t)0x00020000)        
#define  SAI_xFRCR_FSOFF                  ((uint32_t)0x00040000)        

#define  SAI_xSLOTR_FBOFF                 ((uint32_t)0x0000001F)        
#define  SAI_xSLOTR_FBOFF_0               ((uint32_t)0x00000001)        
#define  SAI_xSLOTR_FBOFF_1               ((uint32_t)0x00000002)        
#define  SAI_xSLOTR_FBOFF_2               ((uint32_t)0x00000004)        
#define  SAI_xSLOTR_FBOFF_3               ((uint32_t)0x00000008)        
#define  SAI_xSLOTR_FBOFF_4               ((uint32_t)0x00000010)        
                                     
#define  SAI_xSLOTR_SLOTSZ                ((uint32_t)0x000000C0)        
#define  SAI_xSLOTR_SLOTSZ_0              ((uint32_t)0x00000040)        
#define  SAI_xSLOTR_SLOTSZ_1              ((uint32_t)0x00000080)        

#define  SAI_xSLOTR_NBSLOT                ((uint32_t)0x00000F00)        
#define  SAI_xSLOTR_NBSLOT_0              ((uint32_t)0x00000100)        
#define  SAI_xSLOTR_NBSLOT_1              ((uint32_t)0x00000200)        
#define  SAI_xSLOTR_NBSLOT_2              ((uint32_t)0x00000400)        
#define  SAI_xSLOTR_NBSLOT_3              ((uint32_t)0x00000800)        

#define  SAI_xSLOTR_SLOTEN                ((uint32_t)0xFFFF0000)        

#define  SAI_xIMR_OVRUDRIE                ((uint32_t)0x00000001)        
#define  SAI_xIMR_MUTEDETIE               ((uint32_t)0x00000002)        
#define  SAI_xIMR_WCKCFGIE                ((uint32_t)0x00000004)        
#define  SAI_xIMR_FREQIE                  ((uint32_t)0x00000008)        
#define  SAI_xIMR_CNRDYIE                 ((uint32_t)0x00000010)        
#define  SAI_xIMR_AFSDETIE                ((uint32_t)0x00000020)        
#define  SAI_xIMR_LFSDETIE                ((uint32_t)0x00000040)        

#define  SAI_xSR_OVRUDR                   ((uint32_t)0x00000001)         
#define  SAI_xSR_MUTEDET                  ((uint32_t)0x00000002)         
#define  SAI_xSR_WCKCFG                   ((uint32_t)0x00000004)         
#define  SAI_xSR_FREQ                     ((uint32_t)0x00000008)         
#define  SAI_xSR_CNRDY                    ((uint32_t)0x00000010)         
#define  SAI_xSR_AFSDET                   ((uint32_t)0x00000020)         
#define  SAI_xSR_LFSDET                   ((uint32_t)0x00000040)         

#define  SAI_xSR_FLVL                     ((uint32_t)0x00070000)         
#define  SAI_xSR_FLVL_0                   ((uint32_t)0x00010000)         
#define  SAI_xSR_FLVL_1                   ((uint32_t)0x00020000)         
#define  SAI_xSR_FLVL_2                   ((uint32_t)0x00030000)         

#define  SAI_xCLRFR_COVRUDR               ((uint32_t)0x00000001)        
#define  SAI_xCLRFR_CMUTEDET              ((uint32_t)0x00000002)        
#define  SAI_xCLRFR_CWCKCFG               ((uint32_t)0x00000004)        
#define  SAI_xCLRFR_CFREQ                 ((uint32_t)0x00000008)        
#define  SAI_xCLRFR_CCNRDY                ((uint32_t)0x00000010)        
#define  SAI_xCLRFR_CAFSDET               ((uint32_t)0x00000020)        
#define  SAI_xCLRFR_CLFSDET               ((uint32_t)0x00000040)        

#define  SAI_xDR_DATA                     ((uint32_t)0xFFFFFFFF)        

#define  SDIO_POWER_PWRCTRL                  ((uint8_t)0x03)               
#define  SDIO_POWER_PWRCTRL_0                ((uint8_t)0x01)               
#define  SDIO_POWER_PWRCTRL_1                ((uint8_t)0x02)               

#define  SDIO_CLKCR_CLKDIV                   ((uint16_t)0x00FF)            
#define  SDIO_CLKCR_CLKEN                    ((uint16_t)0x0100)            
#define  SDIO_CLKCR_PWRSAV                   ((uint16_t)0x0200)            
#define  SDIO_CLKCR_BYPASS                   ((uint16_t)0x0400)            

#define  SDIO_CLKCR_WIDBUS                   ((uint16_t)0x1800)            
#define  SDIO_CLKCR_WIDBUS_0                 ((uint16_t)0x0800)            
#define  SDIO_CLKCR_WIDBUS_1                 ((uint16_t)0x1000)            

#define  SDIO_CLKCR_NEGEDGE                  ((uint16_t)0x2000)            
#define  SDIO_CLKCR_HWFC_EN                  ((uint16_t)0x4000)            

#define  SDIO_ARG_CMDARG                     ((uint32_t)0xFFFFFFFF)            

#define  SDIO_CMD_CMDINDEX                   ((uint16_t)0x003F)            

#define  SDIO_CMD_WAITRESP                   ((uint16_t)0x00C0)            
#define  SDIO_CMD_WAITRESP_0                 ((uint16_t)0x0040)            
#define  SDIO_CMD_WAITRESP_1                 ((uint16_t)0x0080)            

#define  SDIO_CMD_WAITINT                    ((uint16_t)0x0100)            
#define  SDIO_CMD_WAITPEND                   ((uint16_t)0x0200)            
#define  SDIO_CMD_CPSMEN                     ((uint16_t)0x0400)            
#define  SDIO_CMD_SDIOSUSPEND                ((uint16_t)0x0800)            
#define  SDIO_CMD_ENCMDCOMPL                 ((uint16_t)0x1000)            
#define  SDIO_CMD_NIEN                       ((uint16_t)0x2000)            
#define  SDIO_CMD_CEATACMD                   ((uint16_t)0x4000)            

#define  SDIO_RESPCMD_RESPCMD                ((uint8_t)0x3F)               

#define  SDIO_RESP0_CARDSTATUS0              ((uint32_t)0xFFFFFFFF)        

#define  SDIO_RESP1_CARDSTATUS1              ((uint32_t)0xFFFFFFFF)        

#define  SDIO_RESP2_CARDSTATUS2              ((uint32_t)0xFFFFFFFF)        

#define  SDIO_RESP3_CARDSTATUS3              ((uint32_t)0xFFFFFFFF)        

#define  SDIO_RESP4_CARDSTATUS4              ((uint32_t)0xFFFFFFFF)        

#define  SDIO_DTIMER_DATATIME                ((uint32_t)0xFFFFFFFF)        

#define  SDIO_DLEN_DATALENGTH                ((uint32_t)0x01FFFFFF)        

#define  SDIO_DCTRL_DTEN                     ((uint16_t)0x0001)            
#define  SDIO_DCTRL_DTDIR                    ((uint16_t)0x0002)            
#define  SDIO_DCTRL_DTMODE                   ((uint16_t)0x0004)            
#define  SDIO_DCTRL_DMAEN                    ((uint16_t)0x0008)            

#define  SDIO_DCTRL_DBLOCKSIZE               ((uint16_t)0x00F0)            
#define  SDIO_DCTRL_DBLOCKSIZE_0             ((uint16_t)0x0010)            
#define  SDIO_DCTRL_DBLOCKSIZE_1             ((uint16_t)0x0020)            
#define  SDIO_DCTRL_DBLOCKSIZE_2             ((uint16_t)0x0040)            
#define  SDIO_DCTRL_DBLOCKSIZE_3             ((uint16_t)0x0080)            

#define  SDIO_DCTRL_RWSTART                  ((uint16_t)0x0100)            
#define  SDIO_DCTRL_RWSTOP                   ((uint16_t)0x0200)            
#define  SDIO_DCTRL_RWMOD                    ((uint16_t)0x0400)            
#define  SDIO_DCTRL_SDIOEN                   ((uint16_t)0x0800)            

#define  SDIO_DCOUNT_DATACOUNT               ((uint32_t)0x01FFFFFF)        

#define  SDIO_STA_CCRCFAIL                   ((uint32_t)0x00000001)        
#define  SDIO_STA_DCRCFAIL                   ((uint32_t)0x00000002)        
#define  SDIO_STA_CTIMEOUT                   ((uint32_t)0x00000004)        
#define  SDIO_STA_DTIMEOUT                   ((uint32_t)0x00000008)        
#define  SDIO_STA_TXUNDERR                   ((uint32_t)0x00000010)        
#define  SDIO_STA_RXOVERR                    ((uint32_t)0x00000020)        
#define  SDIO_STA_CMDREND                    ((uint32_t)0x00000040)        
#define  SDIO_STA_CMDSENT                    ((uint32_t)0x00000080)        
#define  SDIO_STA_DATAEND                    ((uint32_t)0x00000100)        
#define  SDIO_STA_STBITERR                   ((uint32_t)0x00000200)        
#define  SDIO_STA_DBCKEND                    ((uint32_t)0x00000400)        
#define  SDIO_STA_CMDACT                     ((uint32_t)0x00000800)        
#define  SDIO_STA_TXACT                      ((uint32_t)0x00001000)        
#define  SDIO_STA_RXACT                      ((uint32_t)0x00002000)        
#define  SDIO_STA_TXFIFOHE                   ((uint32_t)0x00004000)        
#define  SDIO_STA_RXFIFOHF                   ((uint32_t)0x00008000)        
#define  SDIO_STA_TXFIFOF                    ((uint32_t)0x00010000)        
#define  SDIO_STA_RXFIFOF                    ((uint32_t)0x00020000)        
#define  SDIO_STA_TXFIFOE                    ((uint32_t)0x00040000)        
#define  SDIO_STA_RXFIFOE                    ((uint32_t)0x00080000)        
#define  SDIO_STA_TXDAVL                     ((uint32_t)0x00100000)        
#define  SDIO_STA_RXDAVL                     ((uint32_t)0x00200000)        
#define  SDIO_STA_SDIOIT                     ((uint32_t)0x00400000)        
#define  SDIO_STA_CEATAEND                   ((uint32_t)0x00800000)        

#define  SDIO_ICR_CCRCFAILC                  ((uint32_t)0x00000001)        
#define  SDIO_ICR_DCRCFAILC                  ((uint32_t)0x00000002)        
#define  SDIO_ICR_CTIMEOUTC                  ((uint32_t)0x00000004)        
#define  SDIO_ICR_DTIMEOUTC                  ((uint32_t)0x00000008)        
#define  SDIO_ICR_TXUNDERRC                  ((uint32_t)0x00000010)        
#define  SDIO_ICR_RXOVERRC                   ((uint32_t)0x00000020)        
#define  SDIO_ICR_CMDRENDC                   ((uint32_t)0x00000040)        
#define  SDIO_ICR_CMDSENTC                   ((uint32_t)0x00000080)        
#define  SDIO_ICR_DATAENDC                   ((uint32_t)0x00000100)        
#define  SDIO_ICR_STBITERRC                  ((uint32_t)0x00000200)        
#define  SDIO_ICR_DBCKENDC                   ((uint32_t)0x00000400)        
#define  SDIO_ICR_SDIOITC                    ((uint32_t)0x00400000)        
#define  SDIO_ICR_CEATAENDC                  ((uint32_t)0x00800000)        

#define  SDIO_MASK_CCRCFAILIE                ((uint32_t)0x00000001)        
#define  SDIO_MASK_DCRCFAILIE                ((uint32_t)0x00000002)        
#define  SDIO_MASK_CTIMEOUTIE                ((uint32_t)0x00000004)        
#define  SDIO_MASK_DTIMEOUTIE                ((uint32_t)0x00000008)        
#define  SDIO_MASK_TXUNDERRIE                ((uint32_t)0x00000010)        
#define  SDIO_MASK_RXOVERRIE                 ((uint32_t)0x00000020)        
#define  SDIO_MASK_CMDRENDIE                 ((uint32_t)0x00000040)        
#define  SDIO_MASK_CMDSENTIE                 ((uint32_t)0x00000080)        
#define  SDIO_MASK_DATAENDIE                 ((uint32_t)0x00000100)        
#define  SDIO_MASK_STBITERRIE                ((uint32_t)0x00000200)        
#define  SDIO_MASK_DBCKENDIE                 ((uint32_t)0x00000400)        
#define  SDIO_MASK_CMDACTIE                  ((uint32_t)0x00000800)        
#define  SDIO_MASK_TXACTIE                   ((uint32_t)0x00001000)        
#define  SDIO_MASK_RXACTIE                   ((uint32_t)0x00002000)        
#define  SDIO_MASK_TXFIFOHEIE                ((uint32_t)0x00004000)        
#define  SDIO_MASK_RXFIFOHFIE                ((uint32_t)0x00008000)        
#define  SDIO_MASK_TXFIFOFIE                 ((uint32_t)0x00010000)        
#define  SDIO_MASK_RXFIFOFIE                 ((uint32_t)0x00020000)        
#define  SDIO_MASK_TXFIFOEIE                 ((uint32_t)0x00040000)        
#define  SDIO_MASK_RXFIFOEIE                 ((uint32_t)0x00080000)        
#define  SDIO_MASK_TXDAVLIE                  ((uint32_t)0x00100000)        
#define  SDIO_MASK_RXDAVLIE                  ((uint32_t)0x00200000)        
#define  SDIO_MASK_SDIOITIE                  ((uint32_t)0x00400000)        
#define  SDIO_MASK_CEATAENDIE                ((uint32_t)0x00800000)        

#define  SDIO_FIFOCNT_FIFOCOUNT              ((uint32_t)0x00FFFFFF)        

#define  SDIO_FIFO_FIFODATA                  ((uint32_t)0xFFFFFFFF)        

#define  SPI_CR1_CPHA                        ((uint16_t)0x0001)            
#define  SPI_CR1_CPOL                        ((uint16_t)0x0002)            
#define  SPI_CR1_MSTR                        ((uint16_t)0x0004)            

#define  SPI_CR1_BR                          ((uint16_t)0x0038)            
#define  SPI_CR1_BR_0                        ((uint16_t)0x0008)            
#define  SPI_CR1_BR_1                        ((uint16_t)0x0010)            
#define  SPI_CR1_BR_2                        ((uint16_t)0x0020)            

#define  SPI_CR1_SPE                         ((uint16_t)0x0040)            
#define  SPI_CR1_LSBFIRST                    ((uint16_t)0x0080)            
#define  SPI_CR1_SSI                         ((uint16_t)0x0100)            
#define  SPI_CR1_SSM                         ((uint16_t)0x0200)            
#define  SPI_CR1_RXONLY                      ((uint16_t)0x0400)            
#define  SPI_CR1_DFF                         ((uint16_t)0x0800)            
#define  SPI_CR1_CRCNEXT                     ((uint16_t)0x1000)            
#define  SPI_CR1_CRCEN                       ((uint16_t)0x2000)            
#define  SPI_CR1_BIDIOE                      ((uint16_t)0x4000)            
#define  SPI_CR1_BIDIMODE                    ((uint16_t)0x8000)            

#define  SPI_CR2_RXDMAEN                     ((uint8_t)0x01)               
#define  SPI_CR2_TXDMAEN                     ((uint8_t)0x02)               
#define  SPI_CR2_SSOE                        ((uint8_t)0x04)               
#define  SPI_CR2_ERRIE                       ((uint8_t)0x20)               
#define  SPI_CR2_RXNEIE                      ((uint8_t)0x40)               
#define  SPI_CR2_TXEIE                       ((uint8_t)0x80)               

#define  SPI_SR_RXNE                         ((uint8_t)0x01)               
#define  SPI_SR_TXE                          ((uint8_t)0x02)               
#define  SPI_SR_CHSIDE                       ((uint8_t)0x04)               
#define  SPI_SR_UDR                          ((uint8_t)0x08)               
#define  SPI_SR_CRCERR                       ((uint8_t)0x10)               
#define  SPI_SR_MODF                         ((uint8_t)0x20)               
#define  SPI_SR_OVR                          ((uint8_t)0x40)               
#define  SPI_SR_BSY                          ((uint8_t)0x80)               

#define  SPI_DR_DR                           ((uint16_t)0xFFFF)            

#define  SPI_CRCPR_CRCPOLY                   ((uint16_t)0xFFFF)            

#define  SPI_RXCRCR_RXCRC                    ((uint16_t)0xFFFF)            

#define  SPI_TXCRCR_TXCRC                    ((uint16_t)0xFFFF)            

#define  SPI_I2SCFGR_CHLEN                   ((uint16_t)0x0001)            

#define  SPI_I2SCFGR_DATLEN                  ((uint16_t)0x0006)            
#define  SPI_I2SCFGR_DATLEN_0                ((uint16_t)0x0002)            
#define  SPI_I2SCFGR_DATLEN_1                ((uint16_t)0x0004)            

#define  SPI_I2SCFGR_CKPOL                   ((uint16_t)0x0008)            

#define  SPI_I2SCFGR_I2SSTD                  ((uint16_t)0x0030)            
#define  SPI_I2SCFGR_I2SSTD_0                ((uint16_t)0x0010)            
#define  SPI_I2SCFGR_I2SSTD_1                ((uint16_t)0x0020)            

#define  SPI_I2SCFGR_PCMSYNC                 ((uint16_t)0x0080)            

#define  SPI_I2SCFGR_I2SCFG                  ((uint16_t)0x0300)            
#define  SPI_I2SCFGR_I2SCFG_0                ((uint16_t)0x0100)            
#define  SPI_I2SCFGR_I2SCFG_1                ((uint16_t)0x0200)            

#define  SPI_I2SCFGR_I2SE                    ((uint16_t)0x0400)            
#define  SPI_I2SCFGR_I2SMOD                  ((uint16_t)0x0800)            

#define  SPI_I2SPR_I2SDIV                    ((uint16_t)0x00FF)            
#define  SPI_I2SPR_ODD                       ((uint16_t)0x0100)            
#define  SPI_I2SPR_MCKOE                     ((uint16_t)0x0200)            

  
#define SYSCFG_MEMRMP_MEM_MODE          ((uint32_t)0x00000007) 
#define SYSCFG_MEMRMP_MEM_MODE_0        ((uint32_t)0x00000001) 
#define SYSCFG_MEMRMP_MEM_MODE_1        ((uint32_t)0x00000002) 
#define SYSCFG_MEMRMP_MEM_MODE_2        ((uint32_t)0x00000004) 

#define SYSCFG_MEMRMP_FB_MODE           ((uint32_t)0x00000100) 

#define SYSCFG_MEMRMP_SWP_FMC           ((uint32_t)0x00000C00) 
#define SYSCFG_MEMRMP_SWP_FMC_0         ((uint32_t)0x00000400) 
#define SYSCFG_MEMRMP_SWP_FMC_1         ((uint32_t)0x00000800) 

#define SYSCFG_PMC_ADCxDC2              ((uint32_t)0x00070000) 
#define SYSCFG_PMC_ADC1DC2              ((uint32_t)0x00010000) 
#define SYSCFG_PMC_ADC2DC2              ((uint32_t)0x00020000) 
#define SYSCFG_PMC_ADC3DC2              ((uint32_t)0x00040000) 

#define SYSCFG_PMC_MII_RMII_SEL         ((uint32_t)0x00800000) 

#define SYSCFG_PMC_MII_RMII             SYSCFG_PMC_MII_RMII_SEL

#define SYSCFG_EXTICR1_EXTI0            ((uint16_t)0x000F) 
#define SYSCFG_EXTICR1_EXTI1            ((uint16_t)0x00F0) 
#define SYSCFG_EXTICR1_EXTI2            ((uint16_t)0x0F00) 
#define SYSCFG_EXTICR1_EXTI3            ((uint16_t)0xF000) 

 
#define SYSCFG_EXTICR1_EXTI0_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR1_EXTI0_PB         ((uint16_t)0x0001) 
#define SYSCFG_EXTICR1_EXTI0_PC         ((uint16_t)0x0002) 
#define SYSCFG_EXTICR1_EXTI0_PD         ((uint16_t)0x0003) 
#define SYSCFG_EXTICR1_EXTI0_PE         ((uint16_t)0x0004) 
#define SYSCFG_EXTICR1_EXTI0_PF         ((uint16_t)0x0005) 
#define SYSCFG_EXTICR1_EXTI0_PG         ((uint16_t)0x0006) 
#define SYSCFG_EXTICR1_EXTI0_PH         ((uint16_t)0x0007) 
#define SYSCFG_EXTICR1_EXTI0_PI         ((uint16_t)0x0008) 
#define SYSCFG_EXTICR1_EXTI0_PJ         ((uint16_t)0x0009) 
#define SYSCFG_EXTICR1_EXTI0_PK         ((uint16_t)0x000A) 

 
#define SYSCFG_EXTICR1_EXTI1_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR1_EXTI1_PB         ((uint16_t)0x0010) 
#define SYSCFG_EXTICR1_EXTI1_PC         ((uint16_t)0x0020) 
#define SYSCFG_EXTICR1_EXTI1_PD         ((uint16_t)0x0030) 
#define SYSCFG_EXTICR1_EXTI1_PE         ((uint16_t)0x0040) 
#define SYSCFG_EXTICR1_EXTI1_PF         ((uint16_t)0x0050) 
#define SYSCFG_EXTICR1_EXTI1_PG         ((uint16_t)0x0060) 
#define SYSCFG_EXTICR1_EXTI1_PH         ((uint16_t)0x0070) 
#define SYSCFG_EXTICR1_EXTI1_PI         ((uint16_t)0x0080) 
#define SYSCFG_EXTICR1_EXTI1_PJ         ((uint16_t)0x0090) 
#define SYSCFG_EXTICR1_EXTI1_PK         ((uint16_t)0x00A0) 

 
#define SYSCFG_EXTICR1_EXTI2_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR1_EXTI2_PB         ((uint16_t)0x0100) 
#define SYSCFG_EXTICR1_EXTI2_PC         ((uint16_t)0x0200) 
#define SYSCFG_EXTICR1_EXTI2_PD         ((uint16_t)0x0300) 
#define SYSCFG_EXTICR1_EXTI2_PE         ((uint16_t)0x0400) 
#define SYSCFG_EXTICR1_EXTI2_PF         ((uint16_t)0x0500) 
#define SYSCFG_EXTICR1_EXTI2_PG         ((uint16_t)0x0600) 
#define SYSCFG_EXTICR1_EXTI2_PH         ((uint16_t)0x0700) 
#define SYSCFG_EXTICR1_EXTI2_PI         ((uint16_t)0x0800) 
#define SYSCFG_EXTICR1_EXTI2_PJ         ((uint16_t)0x0900) 
#define SYSCFG_EXTICR1_EXTI2_PK         ((uint16_t)0x0A00) 

 
#define SYSCFG_EXTICR1_EXTI3_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR1_EXTI3_PB         ((uint16_t)0x1000) 
#define SYSCFG_EXTICR1_EXTI3_PC         ((uint16_t)0x2000) 
#define SYSCFG_EXTICR1_EXTI3_PD         ((uint16_t)0x3000) 
#define SYSCFG_EXTICR1_EXTI3_PE         ((uint16_t)0x4000) 
#define SYSCFG_EXTICR1_EXTI3_PF         ((uint16_t)0x5000) 
#define SYSCFG_EXTICR1_EXTI3_PG         ((uint16_t)0x6000) 
#define SYSCFG_EXTICR1_EXTI3_PH         ((uint16_t)0x7000) 
#define SYSCFG_EXTICR1_EXTI3_PI         ((uint16_t)0x8000) 
#define SYSCFG_EXTICR1_EXTI3_PJ         ((uint16_t)0x9000) 
#define SYSCFG_EXTICR1_EXTI3_PK         ((uint16_t)0xA000) 

#define SYSCFG_EXTICR2_EXTI4            ((uint16_t)0x000F) 
#define SYSCFG_EXTICR2_EXTI5            ((uint16_t)0x00F0) 
#define SYSCFG_EXTICR2_EXTI6            ((uint16_t)0x0F00) 
#define SYSCFG_EXTICR2_EXTI7            ((uint16_t)0xF000) 

 
#define SYSCFG_EXTICR2_EXTI4_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR2_EXTI4_PB         ((uint16_t)0x0001) 
#define SYSCFG_EXTICR2_EXTI4_PC         ((uint16_t)0x0002) 
#define SYSCFG_EXTICR2_EXTI4_PD         ((uint16_t)0x0003) 
#define SYSCFG_EXTICR2_EXTI4_PE         ((uint16_t)0x0004) 
#define SYSCFG_EXTICR2_EXTI4_PF         ((uint16_t)0x0005) 
#define SYSCFG_EXTICR2_EXTI4_PG         ((uint16_t)0x0006) 
#define SYSCFG_EXTICR2_EXTI4_PH         ((uint16_t)0x0007) 
#define SYSCFG_EXTICR2_EXTI4_PI         ((uint16_t)0x0008) 
#define SYSCFG_EXTICR2_EXTI4_PJ         ((uint16_t)0x0009) 
#define SYSCFG_EXTICR2_EXTI4_PK         ((uint16_t)0x000A) 

 
#define SYSCFG_EXTICR2_EXTI5_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR2_EXTI5_PB         ((uint16_t)0x0010) 
#define SYSCFG_EXTICR2_EXTI5_PC         ((uint16_t)0x0020) 
#define SYSCFG_EXTICR2_EXTI5_PD         ((uint16_t)0x0030) 
#define SYSCFG_EXTICR2_EXTI5_PE         ((uint16_t)0x0040) 
#define SYSCFG_EXTICR2_EXTI5_PF         ((uint16_t)0x0050) 
#define SYSCFG_EXTICR2_EXTI5_PG         ((uint16_t)0x0060) 
#define SYSCFG_EXTICR2_EXTI5_PH         ((uint16_t)0x0070) 
#define SYSCFG_EXTICR2_EXTI5_PI         ((uint16_t)0x0080) 
#define SYSCFG_EXTICR2_EXTI5_PJ         ((uint16_t)0x0090) 
#define SYSCFG_EXTICR2_EXTI5_PK         ((uint16_t)0x00A0) 

 
#define SYSCFG_EXTICR2_EXTI6_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR2_EXTI6_PB         ((uint16_t)0x0100) 
#define SYSCFG_EXTICR2_EXTI6_PC         ((uint16_t)0x0200) 
#define SYSCFG_EXTICR2_EXTI6_PD         ((uint16_t)0x0300) 
#define SYSCFG_EXTICR2_EXTI6_PE         ((uint16_t)0x0400) 
#define SYSCFG_EXTICR2_EXTI6_PF         ((uint16_t)0x0500) 
#define SYSCFG_EXTICR2_EXTI6_PG         ((uint16_t)0x0600) 
#define SYSCFG_EXTICR2_EXTI6_PH         ((uint16_t)0x0700) 
#define SYSCFG_EXTICR2_EXTI6_PI         ((uint16_t)0x0800) 
#define SYSCFG_EXTICR2_EXTI6_PJ         ((uint16_t)0x0900) 
#define SYSCFG_EXTICR2_EXTI6_PK         ((uint16_t)0x0A00) 

 
#define SYSCFG_EXTICR2_EXTI7_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR2_EXTI7_PB         ((uint16_t)0x1000) 
#define SYSCFG_EXTICR2_EXTI7_PC         ((uint16_t)0x2000) 
#define SYSCFG_EXTICR2_EXTI7_PD         ((uint16_t)0x3000) 
#define SYSCFG_EXTICR2_EXTI7_PE         ((uint16_t)0x4000) 
#define SYSCFG_EXTICR2_EXTI7_PF         ((uint16_t)0x5000) 
#define SYSCFG_EXTICR2_EXTI7_PG         ((uint16_t)0x6000) 
#define SYSCFG_EXTICR2_EXTI7_PH         ((uint16_t)0x7000) 
#define SYSCFG_EXTICR2_EXTI7_PI         ((uint16_t)0x8000) 
#define SYSCFG_EXTICR2_EXTI7_PJ         ((uint16_t)0x9000) 
#define SYSCFG_EXTICR2_EXTI7_PK         ((uint16_t)0xA000) 

#define SYSCFG_EXTICR3_EXTI8            ((uint16_t)0x000F) 
#define SYSCFG_EXTICR3_EXTI9            ((uint16_t)0x00F0) 
#define SYSCFG_EXTICR3_EXTI10           ((uint16_t)0x0F00) 
#define SYSCFG_EXTICR3_EXTI11           ((uint16_t)0xF000) 
           

 
#define SYSCFG_EXTICR3_EXTI8_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR3_EXTI8_PB         ((uint16_t)0x0001) 
#define SYSCFG_EXTICR3_EXTI8_PC         ((uint16_t)0x0002) 
#define SYSCFG_EXTICR3_EXTI8_PD         ((uint16_t)0x0003) 
#define SYSCFG_EXTICR3_EXTI8_PE         ((uint16_t)0x0004) 
#define SYSCFG_EXTICR3_EXTI8_PF         ((uint16_t)0x0005) 
#define SYSCFG_EXTICR3_EXTI8_PG         ((uint16_t)0x0006) 
#define SYSCFG_EXTICR3_EXTI8_PH         ((uint16_t)0x0007) 
#define SYSCFG_EXTICR3_EXTI8_PI         ((uint16_t)0x0008) 
#define SYSCFG_EXTICR3_EXTI8_PJ         ((uint16_t)0x0009) 

 
#define SYSCFG_EXTICR3_EXTI9_PA         ((uint16_t)0x0000) 
#define SYSCFG_EXTICR3_EXTI9_PB         ((uint16_t)0x0010) 
#define SYSCFG_EXTICR3_EXTI9_PC         ((uint16_t)0x0020) 
#define SYSCFG_EXTICR3_EXTI9_PD         ((uint16_t)0x0030) 
#define SYSCFG_EXTICR3_EXTI9_PE         ((uint16_t)0x0040) 
#define SYSCFG_EXTICR3_EXTI9_PF         ((uint16_t)0x0050) 
#define SYSCFG_EXTICR3_EXTI9_PG         ((uint16_t)0x0060) 
#define SYSCFG_EXTICR3_EXTI9_PH         ((uint16_t)0x0070) 
#define SYSCFG_EXTICR3_EXTI9_PI         ((uint16_t)0x0080) 
#define SYSCFG_EXTICR3_EXTI9_PJ         ((uint16_t)0x0090) 

 
#define SYSCFG_EXTICR3_EXTI10_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR3_EXTI10_PB        ((uint16_t)0x0100) 
#define SYSCFG_EXTICR3_EXTI10_PC        ((uint16_t)0x0200) 
#define SYSCFG_EXTICR3_EXTI10_PD        ((uint16_t)0x0300) 
#define SYSCFG_EXTICR3_EXTI10_PE        ((uint16_t)0x0400) 
#define SYSCFG_EXTICR3_EXTI10_PF        ((uint16_t)0x0500) 
#define SYSCFG_EXTICR3_EXTI10_PG        ((uint16_t)0x0600) 
#define SYSCFG_EXTICR3_EXTI10_PH        ((uint16_t)0x0700) 
#define SYSCFG_EXTICR3_EXTI10_PI        ((uint16_t)0x0800) 
#define SYSCFG_EXTICR3_EXTI10_PJ        ((uint16_t)0x0900) 

 
#define SYSCFG_EXTICR3_EXTI11_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR3_EXTI11_PB        ((uint16_t)0x1000) 
#define SYSCFG_EXTICR3_EXTI11_PC        ((uint16_t)0x2000) 
#define SYSCFG_EXTICR3_EXTI11_PD        ((uint16_t)0x3000) 
#define SYSCFG_EXTICR3_EXTI11_PE        ((uint16_t)0x4000) 
#define SYSCFG_EXTICR3_EXTI11_PF        ((uint16_t)0x5000) 
#define SYSCFG_EXTICR3_EXTI11_PG        ((uint16_t)0x6000) 
#define SYSCFG_EXTICR3_EXTI11_PH        ((uint16_t)0x7000) 
#define SYSCFG_EXTICR3_EXTI11_PI        ((uint16_t)0x8000) 
#define SYSCFG_EXTICR3_EXTI11_PJ        ((uint16_t)0x9000) 

#define SYSCFG_EXTICR4_EXTI12           ((uint16_t)0x000F) 
#define SYSCFG_EXTICR4_EXTI13           ((uint16_t)0x00F0) 
#define SYSCFG_EXTICR4_EXTI14           ((uint16_t)0x0F00) 
#define SYSCFG_EXTICR4_EXTI15           ((uint16_t)0xF000) 

 
#define SYSCFG_EXTICR4_EXTI12_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR4_EXTI12_PB        ((uint16_t)0x0001) 
#define SYSCFG_EXTICR4_EXTI12_PC        ((uint16_t)0x0002) 
#define SYSCFG_EXTICR4_EXTI12_PD        ((uint16_t)0x0003) 
#define SYSCFG_EXTICR4_EXTI12_PE        ((uint16_t)0x0004) 
#define SYSCFG_EXTICR4_EXTI12_PF        ((uint16_t)0x0005) 
#define SYSCFG_EXTICR4_EXTI12_PG        ((uint16_t)0x0006) 
#define SYSCFG_EXTICR4_EXTI12_PH        ((uint16_t)0x0007) 
#define SYSCFG_EXTICR4_EXTI12_PI        ((uint16_t)0x0008) 
#define SYSCFG_EXTICR4_EXTI12_PJ        ((uint16_t)0x0009) 

 
#define SYSCFG_EXTICR4_EXTI13_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR4_EXTI13_PB        ((uint16_t)0x0010) 
#define SYSCFG_EXTICR4_EXTI13_PC        ((uint16_t)0x0020) 
#define SYSCFG_EXTICR4_EXTI13_PD        ((uint16_t)0x0030) 
#define SYSCFG_EXTICR4_EXTI13_PE        ((uint16_t)0x0040) 
#define SYSCFG_EXTICR4_EXTI13_PF        ((uint16_t)0x0050) 
#define SYSCFG_EXTICR4_EXTI13_PG        ((uint16_t)0x0060) 
#define SYSCFG_EXTICR4_EXTI13_PH        ((uint16_t)0x0070) 
#define SYSCFG_EXTICR4_EXTI13_PI        ((uint16_t)0x0008) 
#define SYSCFG_EXTICR4_EXTI13_PJ        ((uint16_t)0x0009) 

 
#define SYSCFG_EXTICR4_EXTI14_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR4_EXTI14_PB        ((uint16_t)0x0100) 
#define SYSCFG_EXTICR4_EXTI14_PC        ((uint16_t)0x0200) 
#define SYSCFG_EXTICR4_EXTI14_PD        ((uint16_t)0x0300) 
#define SYSCFG_EXTICR4_EXTI14_PE        ((uint16_t)0x0400) 
#define SYSCFG_EXTICR4_EXTI14_PF        ((uint16_t)0x0500) 
#define SYSCFG_EXTICR4_EXTI14_PG        ((uint16_t)0x0600) 
#define SYSCFG_EXTICR4_EXTI14_PH        ((uint16_t)0x0700) 
#define SYSCFG_EXTICR4_EXTI14_PI        ((uint16_t)0x0800) 
#define SYSCFG_EXTICR4_EXTI14_PJ        ((uint16_t)0x0900) 

 
#define SYSCFG_EXTICR4_EXTI15_PA        ((uint16_t)0x0000) 
#define SYSCFG_EXTICR4_EXTI15_PB        ((uint16_t)0x1000) 
#define SYSCFG_EXTICR4_EXTI15_PC        ((uint16_t)0x2000) 
#define SYSCFG_EXTICR4_EXTI15_PD        ((uint16_t)0x3000) 
#define SYSCFG_EXTICR4_EXTI15_PE        ((uint16_t)0x4000) 
#define SYSCFG_EXTICR4_EXTI15_PF        ((uint16_t)0x5000) 
#define SYSCFG_EXTICR4_EXTI15_PG        ((uint16_t)0x6000) 
#define SYSCFG_EXTICR4_EXTI15_PH        ((uint16_t)0x7000) 
#define SYSCFG_EXTICR4_EXTI15_PI        ((uint16_t)0x8000) 
#define SYSCFG_EXTICR4_EXTI15_PJ        ((uint16_t)0x9000) 

  
#define SYSCFG_CMPCR_CMP_PD             ((uint32_t)0x00000001) 
#define SYSCFG_CMPCR_READY              ((uint32_t)0x00000100) 

#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            

#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            

#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            

#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            

#define  TIM_CR2_CCPC                        ((uint16_t)0x0001)            
#define  TIM_CR2_CCUS                        ((uint16_t)0x0004)            
#define  TIM_CR2_CCDS                        ((uint16_t)0x0008)            

#define  TIM_CR2_MMS                         ((uint16_t)0x0070)            
#define  TIM_CR2_MMS_0                       ((uint16_t)0x0010)            
#define  TIM_CR2_MMS_1                       ((uint16_t)0x0020)            
#define  TIM_CR2_MMS_2                       ((uint16_t)0x0040)            

#define  TIM_CR2_TI1S                        ((uint16_t)0x0080)            
#define  TIM_CR2_OIS1                        ((uint16_t)0x0100)            
#define  TIM_CR2_OIS1N                       ((uint16_t)0x0200)            
#define  TIM_CR2_OIS2                        ((uint16_t)0x0400)            
#define  TIM_CR2_OIS2N                       ((uint16_t)0x0800)            
#define  TIM_CR2_OIS3                        ((uint16_t)0x1000)            
#define  TIM_CR2_OIS3N                       ((uint16_t)0x2000)            
#define  TIM_CR2_OIS4                        ((uint16_t)0x4000)            

#define  TIM_SMCR_SMS                        ((uint16_t)0x0007)            
#define  TIM_SMCR_SMS_0                      ((uint16_t)0x0001)            
#define  TIM_SMCR_SMS_1                      ((uint16_t)0x0002)            
#define  TIM_SMCR_SMS_2                      ((uint16_t)0x0004)            

#define  TIM_SMCR_TS                         ((uint16_t)0x0070)            
#define  TIM_SMCR_TS_0                       ((uint16_t)0x0010)            
#define  TIM_SMCR_TS_1                       ((uint16_t)0x0020)            
#define  TIM_SMCR_TS_2                       ((uint16_t)0x0040)            

#define  TIM_SMCR_MSM                        ((uint16_t)0x0080)            

#define  TIM_SMCR_ETF                        ((uint16_t)0x0F00)            
#define  TIM_SMCR_ETF_0                      ((uint16_t)0x0100)            
#define  TIM_SMCR_ETF_1                      ((uint16_t)0x0200)            
#define  TIM_SMCR_ETF_2                      ((uint16_t)0x0400)            
#define  TIM_SMCR_ETF_3                      ((uint16_t)0x0800)            

#define  TIM_SMCR_ETPS                       ((uint16_t)0x3000)            
#define  TIM_SMCR_ETPS_0                     ((uint16_t)0x1000)            
#define  TIM_SMCR_ETPS_1                     ((uint16_t)0x2000)            

#define  TIM_SMCR_ECE                        ((uint16_t)0x4000)            
#define  TIM_SMCR_ETP                        ((uint16_t)0x8000)            

#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            

#define  TIM_SR_UIF                          ((uint16_t)0x0001)            
#define  TIM_SR_CC1IF                        ((uint16_t)0x0002)            
#define  TIM_SR_CC2IF                        ((uint16_t)0x0004)            
#define  TIM_SR_CC3IF                        ((uint16_t)0x0008)            
#define  TIM_SR_CC4IF                        ((uint16_t)0x0010)            
#define  TIM_SR_COMIF                        ((uint16_t)0x0020)            
#define  TIM_SR_TIF                          ((uint16_t)0x0040)            
#define  TIM_SR_BIF                          ((uint16_t)0x0080)            
#define  TIM_SR_CC1OF                        ((uint16_t)0x0200)            
#define  TIM_SR_CC2OF                        ((uint16_t)0x0400)            
#define  TIM_SR_CC3OF                        ((uint16_t)0x0800)            
#define  TIM_SR_CC4OF                        ((uint16_t)0x1000)            

#define  TIM_EGR_UG                          ((uint8_t)0x01)               
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               
#define  TIM_EGR_TG                          ((uint8_t)0x40)               
#define  TIM_EGR_BG                          ((uint8_t)0x80)               

#define  TIM_CCMR1_CC1S                      ((uint16_t)0x0003)            
#define  TIM_CCMR1_CC1S_0                    ((uint16_t)0x0001)            
#define  TIM_CCMR1_CC1S_1                    ((uint16_t)0x0002)            

#define  TIM_CCMR1_OC1FE                     ((uint16_t)0x0004)            
#define  TIM_CCMR1_OC1PE                     ((uint16_t)0x0008)            

#define  TIM_CCMR1_OC1M                      ((uint16_t)0x0070)            
#define  TIM_CCMR1_OC1M_0                    ((uint16_t)0x0010)            
#define  TIM_CCMR1_OC1M_1                    ((uint16_t)0x0020)            
#define  TIM_CCMR1_OC1M_2                    ((uint16_t)0x0040)            

#define  TIM_CCMR1_OC1CE                     ((uint16_t)0x0080)            

#define  TIM_CCMR1_CC2S                      ((uint16_t)0x0300)            
#define  TIM_CCMR1_CC2S_0                    ((uint16_t)0x0100)            
#define  TIM_CCMR1_CC2S_1                    ((uint16_t)0x0200)            

#define  TIM_CCMR1_OC2FE                     ((uint16_t)0x0400)            
#define  TIM_CCMR1_OC2PE                     ((uint16_t)0x0800)            

#define  TIM_CCMR1_OC2M                      ((uint16_t)0x7000)            
#define  TIM_CCMR1_OC2M_0                    ((uint16_t)0x1000)            
#define  TIM_CCMR1_OC2M_1                    ((uint16_t)0x2000)            
#define  TIM_CCMR1_OC2M_2                    ((uint16_t)0x4000)            

#define  TIM_CCMR1_OC2CE                     ((uint16_t)0x8000)            

#define  TIM_CCMR1_IC1PSC                    ((uint16_t)0x000C)            
#define  TIM_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            
#define  TIM_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            

#define  TIM_CCMR1_IC1F                      ((uint16_t)0x00F0)            
#define  TIM_CCMR1_IC1F_0                    ((uint16_t)0x0010)            
#define  TIM_CCMR1_IC1F_1                    ((uint16_t)0x0020)            
#define  TIM_CCMR1_IC1F_2                    ((uint16_t)0x0040)            
#define  TIM_CCMR1_IC1F_3                    ((uint16_t)0x0080)            

#define  TIM_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            
#define  TIM_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            
#define  TIM_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            

#define  TIM_CCMR1_IC2F                      ((uint16_t)0xF000)            
#define  TIM_CCMR1_IC2F_0                    ((uint16_t)0x1000)            
#define  TIM_CCMR1_IC2F_1                    ((uint16_t)0x2000)            
#define  TIM_CCMR1_IC2F_2                    ((uint16_t)0x4000)            
#define  TIM_CCMR1_IC2F_3                    ((uint16_t)0x8000)            

#define  TIM_CCMR2_CC3S                      ((uint16_t)0x0003)            
#define  TIM_CCMR2_CC3S_0                    ((uint16_t)0x0001)            
#define  TIM_CCMR2_CC3S_1                    ((uint16_t)0x0002)            

#define  TIM_CCMR2_OC3FE                     ((uint16_t)0x0004)            
#define  TIM_CCMR2_OC3PE                     ((uint16_t)0x0008)            

#define  TIM_CCMR2_OC3M                      ((uint16_t)0x0070)            
#define  TIM_CCMR2_OC3M_0                    ((uint16_t)0x0010)            
#define  TIM_CCMR2_OC3M_1                    ((uint16_t)0x0020)            
#define  TIM_CCMR2_OC3M_2                    ((uint16_t)0x0040)            

#define  TIM_CCMR2_OC3CE                     ((uint16_t)0x0080)            

#define  TIM_CCMR2_CC4S                      ((uint16_t)0x0300)            
#define  TIM_CCMR2_CC4S_0                    ((uint16_t)0x0100)            
#define  TIM_CCMR2_CC4S_1                    ((uint16_t)0x0200)            

#define  TIM_CCMR2_OC4FE                     ((uint16_t)0x0400)            
#define  TIM_CCMR2_OC4PE                     ((uint16_t)0x0800)            

#define  TIM_CCMR2_OC4M                      ((uint16_t)0x7000)            
#define  TIM_CCMR2_OC4M_0                    ((uint16_t)0x1000)            
#define  TIM_CCMR2_OC4M_1                    ((uint16_t)0x2000)            
#define  TIM_CCMR2_OC4M_2                    ((uint16_t)0x4000)            

#define  TIM_CCMR2_OC4CE                     ((uint16_t)0x8000)            

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x000C)            
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            

#define  TIM_CCMR2_IC3F                      ((uint16_t)0x00F0)            
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x0010)            
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x0020)            
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x0040)            
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x0080)            

#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            

#define  TIM_CCMR2_IC4F                      ((uint16_t)0xF000)            
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x1000)            
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x2000)            
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x4000)            
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x8000)            

#define  TIM_CCER_CC1E                       ((uint16_t)0x0001)            
#define  TIM_CCER_CC1P                       ((uint16_t)0x0002)            
#define  TIM_CCER_CC1NE                      ((uint16_t)0x0004)            
#define  TIM_CCER_CC1NP                      ((uint16_t)0x0008)            
#define  TIM_CCER_CC2E                       ((uint16_t)0x0010)            
#define  TIM_CCER_CC2P                       ((uint16_t)0x0020)            
#define  TIM_CCER_CC2NE                      ((uint16_t)0x0040)            
#define  TIM_CCER_CC2NP                      ((uint16_t)0x0080)            
#define  TIM_CCER_CC3E                       ((uint16_t)0x0100)            
#define  TIM_CCER_CC3P                       ((uint16_t)0x0200)            
#define  TIM_CCER_CC3NE                      ((uint16_t)0x0400)            
#define  TIM_CCER_CC3NP                      ((uint16_t)0x0800)            
#define  TIM_CCER_CC4E                       ((uint16_t)0x1000)            
#define  TIM_CCER_CC4P                       ((uint16_t)0x2000)            
#define  TIM_CCER_CC4NP                      ((uint16_t)0x8000)            

#define  TIM_CNT_CNT                         ((uint16_t)0xFFFF)            

#define  TIM_PSC_PSC                         ((uint16_t)0xFFFF)            

#define  TIM_ARR_ARR                         ((uint16_t)0xFFFF)            

#define  TIM_RCR_REP                         ((uint8_t)0xFF)               

#define  TIM_CCR1_CCR1                       ((uint16_t)0xFFFF)            

#define  TIM_CCR2_CCR2                       ((uint16_t)0xFFFF)            

#define  TIM_CCR3_CCR3                       ((uint16_t)0xFFFF)            

#define  TIM_CCR4_CCR4                       ((uint16_t)0xFFFF)            

#define  TIM_BDTR_DTG                        ((uint16_t)0x00FF)            
#define  TIM_BDTR_DTG_0                      ((uint16_t)0x0001)            
#define  TIM_BDTR_DTG_1                      ((uint16_t)0x0002)            
#define  TIM_BDTR_DTG_2                      ((uint16_t)0x0004)            
#define  TIM_BDTR_DTG_3                      ((uint16_t)0x0008)            
#define  TIM_BDTR_DTG_4                      ((uint16_t)0x0010)            
#define  TIM_BDTR_DTG_5                      ((uint16_t)0x0020)            
#define  TIM_BDTR_DTG_6                      ((uint16_t)0x0040)            
#define  TIM_BDTR_DTG_7                      ((uint16_t)0x0080)            

#define  TIM_BDTR_LOCK                       ((uint16_t)0x0300)            
#define  TIM_BDTR_LOCK_0                     ((uint16_t)0x0100)            
#define  TIM_BDTR_LOCK_1                     ((uint16_t)0x0200)            

#define  TIM_BDTR_OSSI                       ((uint16_t)0x0400)            
#define  TIM_BDTR_OSSR                       ((uint16_t)0x0800)            
#define  TIM_BDTR_BKE                        ((uint16_t)0x1000)            
#define  TIM_BDTR_BKP                        ((uint16_t)0x2000)            
#define  TIM_BDTR_AOE                        ((uint16_t)0x4000)            
#define  TIM_BDTR_MOE                        ((uint16_t)0x8000)            

#define  TIM_DCR_DBA                         ((uint16_t)0x001F)            
#define  TIM_DCR_DBA_0                       ((uint16_t)0x0001)            
#define  TIM_DCR_DBA_1                       ((uint16_t)0x0002)            
#define  TIM_DCR_DBA_2                       ((uint16_t)0x0004)            
#define  TIM_DCR_DBA_3                       ((uint16_t)0x0008)            
#define  TIM_DCR_DBA_4                       ((uint16_t)0x0010)            

#define  TIM_DCR_DBL                         ((uint16_t)0x1F00)            
#define  TIM_DCR_DBL_0                       ((uint16_t)0x0100)            
#define  TIM_DCR_DBL_1                       ((uint16_t)0x0200)            
#define  TIM_DCR_DBL_2                       ((uint16_t)0x0400)            
#define  TIM_DCR_DBL_3                       ((uint16_t)0x0800)            
#define  TIM_DCR_DBL_4                       ((uint16_t)0x1000)            

#define  TIM_DMAR_DMAB                       ((uint16_t)0xFFFF)            

#define TIM_OR_TI4_RMP                       ((uint16_t)0x00C0)            
#define TIM_OR_TI4_RMP_0                     ((uint16_t)0x0040)            
#define TIM_OR_TI4_RMP_1                     ((uint16_t)0x0080)            
#define TIM_OR_ITR1_RMP                      ((uint16_t)0x0C00)            
#define TIM_OR_ITR1_RMP_0                    ((uint16_t)0x0400)            
#define TIM_OR_ITR1_RMP_1                    ((uint16_t)0x0800)            

#define  USART_SR_PE                         ((uint16_t)0x0001)            
#define  USART_SR_FE                         ((uint16_t)0x0002)            
#define  USART_SR_NE                         ((uint16_t)0x0004)            
#define  USART_SR_ORE                        ((uint16_t)0x0008)            
#define  USART_SR_IDLE                       ((uint16_t)0x0010)            
#define  USART_SR_RXNE                       ((uint16_t)0x0020)            
#define  USART_SR_TC                         ((uint16_t)0x0040)            
#define  USART_SR_TXE                        ((uint16_t)0x0080)            
#define  USART_SR_LBD                        ((uint16_t)0x0100)            
#define  USART_SR_CTS                        ((uint16_t)0x0200)            

#define  USART_DR_DR                         ((uint16_t)0x01FF)            

#define  USART_BRR_DIV_Fraction              ((uint16_t)0x000F)            
#define  USART_BRR_DIV_Mantissa              ((uint16_t)0xFFF0)            

#define  USART_CR1_SBK                       ((uint16_t)0x0001)            
#define  USART_CR1_RWU                       ((uint16_t)0x0002)            
#define  USART_CR1_RE                        ((uint16_t)0x0004)            
#define  USART_CR1_TE                        ((uint16_t)0x0008)            
#define  USART_CR1_IDLEIE                    ((uint16_t)0x0010)            
#define  USART_CR1_RXNEIE                    ((uint16_t)0x0020)            
#define  USART_CR1_TCIE                      ((uint16_t)0x0040)            
#define  USART_CR1_TXEIE                     ((uint16_t)0x0080)            
#define  USART_CR1_PEIE                      ((uint16_t)0x0100)            
#define  USART_CR1_PS                        ((uint16_t)0x0200)            
#define  USART_CR1_PCE                       ((uint16_t)0x0400)            
#define  USART_CR1_WAKE                      ((uint16_t)0x0800)            
#define  USART_CR1_M                         ((uint16_t)0x1000)            
#define  USART_CR1_UE                        ((uint16_t)0x2000)            
#define  USART_CR1_OVER8                     ((uint16_t)0x8000)            

#define  USART_CR2_ADD                       ((uint16_t)0x000F)            
#define  USART_CR2_LBDL                      ((uint16_t)0x0020)            
#define  USART_CR2_LBDIE                     ((uint16_t)0x0040)            
#define  USART_CR2_LBCL                      ((uint16_t)0x0100)            
#define  USART_CR2_CPHA                      ((uint16_t)0x0200)            
#define  USART_CR2_CPOL                      ((uint16_t)0x0400)            
#define  USART_CR2_CLKEN                     ((uint16_t)0x0800)            

#define  USART_CR2_STOP                      ((uint16_t)0x3000)            
#define  USART_CR2_STOP_0                    ((uint16_t)0x1000)            
#define  USART_CR2_STOP_1                    ((uint16_t)0x2000)            

#define  USART_CR2_LINEN                     ((uint16_t)0x4000)            

#define  USART_CR3_EIE                       ((uint16_t)0x0001)            
#define  USART_CR3_IREN                      ((uint16_t)0x0002)            
#define  USART_CR3_IRLP                      ((uint16_t)0x0004)            
#define  USART_CR3_HDSEL                     ((uint16_t)0x0008)            
#define  USART_CR3_NACK                      ((uint16_t)0x0010)            
#define  USART_CR3_SCEN                      ((uint16_t)0x0020)            
#define  USART_CR3_DMAR                      ((uint16_t)0x0040)            
#define  USART_CR3_DMAT                      ((uint16_t)0x0080)            
#define  USART_CR3_RTSE                      ((uint16_t)0x0100)            
#define  USART_CR3_CTSE                      ((uint16_t)0x0200)            
#define  USART_CR3_CTSIE                     ((uint16_t)0x0400)            
#define  USART_CR3_ONEBIT                    ((uint16_t)0x0800)            

#define  USART_GTPR_PSC                      ((uint16_t)0x00FF)            
#define  USART_GTPR_PSC_0                    ((uint16_t)0x0001)            
#define  USART_GTPR_PSC_1                    ((uint16_t)0x0002)            
#define  USART_GTPR_PSC_2                    ((uint16_t)0x0004)            
#define  USART_GTPR_PSC_3                    ((uint16_t)0x0008)            
#define  USART_GTPR_PSC_4                    ((uint16_t)0x0010)            
#define  USART_GTPR_PSC_5                    ((uint16_t)0x0020)            
#define  USART_GTPR_PSC_6                    ((uint16_t)0x0040)            
#define  USART_GTPR_PSC_7                    ((uint16_t)0x0080)            

#define  USART_GTPR_GT                       ((uint16_t)0xFF00)            

#define  WWDG_CR_T                           ((uint8_t)0x7F)               
#define  WWDG_CR_T0                          ((uint8_t)0x01)               
#define  WWDG_CR_T1                          ((uint8_t)0x02)               
#define  WWDG_CR_T2                          ((uint8_t)0x04)               
#define  WWDG_CR_T3                          ((uint8_t)0x08)               
#define  WWDG_CR_T4                          ((uint8_t)0x10)               
#define  WWDG_CR_T5                          ((uint8_t)0x20)               
#define  WWDG_CR_T6                          ((uint8_t)0x40)               

#define  WWDG_CR_WDGA                        ((uint8_t)0x80)               

#define  WWDG_CFR_W                          ((uint16_t)0x007F)            
#define  WWDG_CFR_W0                         ((uint16_t)0x0001)            
#define  WWDG_CFR_W1                         ((uint16_t)0x0002)            
#define  WWDG_CFR_W2                         ((uint16_t)0x0004)            
#define  WWDG_CFR_W3                         ((uint16_t)0x0008)            
#define  WWDG_CFR_W4                         ((uint16_t)0x0010)            
#define  WWDG_CFR_W5                         ((uint16_t)0x0020)            
#define  WWDG_CFR_W6                         ((uint16_t)0x0040)            

#define  WWDG_CFR_WDGTB                      ((uint16_t)0x0180)            
#define  WWDG_CFR_WDGTB0                     ((uint16_t)0x0080)            
#define  WWDG_CFR_WDGTB1                     ((uint16_t)0x0100)            

#define  WWDG_CFR_EWI                        ((uint16_t)0x0200)            

#define  WWDG_SR_EWIF                        ((uint8_t)0x01)               

#define  DBGMCU_IDCODE_DEV_ID                ((uint32_t)0x00000FFF)
#define  DBGMCU_IDCODE_REV_ID                ((uint32_t)0xFFFF0000)

#define  DBGMCU_CR_DBG_SLEEP                 ((uint32_t)0x00000001)
#define  DBGMCU_CR_DBG_STOP                  ((uint32_t)0x00000002)
#define  DBGMCU_CR_DBG_STANDBY               ((uint32_t)0x00000004)
#define  DBGMCU_CR_TRACE_IOEN                ((uint32_t)0x00000020)

#define  DBGMCU_CR_TRACE_MODE                ((uint32_t)0x000000C0)
#define  DBGMCU_CR_TRACE_MODE_0              ((uint32_t)0x00000040)
#define  DBGMCU_CR_TRACE_MODE_1              ((uint32_t)0x00000080)

#define  DBGMCU_APB1_FZ_DBG_TIM2_STOP            ((uint32_t)0x00000001)
#define  DBGMCU_APB1_FZ_DBG_TIM3_STOP            ((uint32_t)0x00000002)
#define  DBGMCU_APB1_FZ_DBG_TIM4_STOP            ((uint32_t)0x00000004)
#define  DBGMCU_APB1_FZ_DBG_TIM5_STOP            ((uint32_t)0x00000008)
#define  DBGMCU_APB1_FZ_DBG_TIM6_STOP            ((uint32_t)0x00000010)
#define  DBGMCU_APB1_FZ_DBG_TIM7_STOP            ((uint32_t)0x00000020)
#define  DBGMCU_APB1_FZ_DBG_TIM12_STOP           ((uint32_t)0x00000040)
#define  DBGMCU_APB1_FZ_DBG_TIM13_STOP           ((uint32_t)0x00000080)
#define  DBGMCU_APB1_FZ_DBG_TIM14_STOP           ((uint32_t)0x00000100)
#define  DBGMCU_APB1_FZ_DBG_RTC_STOP             ((uint32_t)0x00000400)
#define  DBGMCU_APB1_FZ_DBG_WWDG_STOP            ((uint32_t)0x00000800)
#define  DBGMCU_APB1_FZ_DBG_IWDG_STOP            ((uint32_t)0x00001000)
#define  DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT   ((uint32_t)0x00200000)
#define  DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT   ((uint32_t)0x00400000)
#define  DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT   ((uint32_t)0x00800000)
#define  DBGMCU_APB1_FZ_DBG_CAN1_STOP            ((uint32_t)0x02000000)
#define  DBGMCU_APB1_FZ_DBG_CAN2_STOP            ((uint32_t)0x04000000)

#define  DBGMCU_APB1_FZ_DBG_IWDEG_STOP           DBGMCU_APB1_FZ_DBG_IWDG_STOP

#define  DBGMCU_APB1_FZ_DBG_TIM1_STOP        ((uint32_t)0x00000001)
#define  DBGMCU_APB1_FZ_DBG_TIM8_STOP        ((uint32_t)0x00000002)
#define  DBGMCU_APB1_FZ_DBG_TIM9_STOP        ((uint32_t)0x00010000)
#define  DBGMCU_APB1_FZ_DBG_TIM10_STOP       ((uint32_t)0x00020000)
#define  DBGMCU_APB1_FZ_DBG_TIM11_STOP       ((uint32_t)0x00040000)

#define ETH_MACCR_WD      ((uint32_t)0x00800000)  
#define ETH_MACCR_JD      ((uint32_t)0x00400000)  
#define ETH_MACCR_IFG     ((uint32_t)0x000E0000)  
#define ETH_MACCR_IFG_96Bit     ((uint32_t)0x00000000)  
  #define ETH_MACCR_IFG_88Bit     ((uint32_t)0x00020000)  
  #define ETH_MACCR_IFG_80Bit     ((uint32_t)0x00040000)  
  #define ETH_MACCR_IFG_72Bit     ((uint32_t)0x00060000)  
  #define ETH_MACCR_IFG_64Bit     ((uint32_t)0x00080000)          
  #define ETH_MACCR_IFG_56Bit     ((uint32_t)0x000A0000)  
  #define ETH_MACCR_IFG_48Bit     ((uint32_t)0x000C0000)  
  #define ETH_MACCR_IFG_40Bit     ((uint32_t)0x000E0000)                
#define ETH_MACCR_CSD     ((uint32_t)0x00010000)  
#define ETH_MACCR_FES     ((uint32_t)0x00004000)  
#define ETH_MACCR_ROD     ((uint32_t)0x00002000)  
#define ETH_MACCR_LM      ((uint32_t)0x00001000)  
#define ETH_MACCR_DM      ((uint32_t)0x00000800)  
#define ETH_MACCR_IPCO    ((uint32_t)0x00000400)  
#define ETH_MACCR_RD      ((uint32_t)0x00000200)  
#define ETH_MACCR_APCS    ((uint32_t)0x00000080)  
#define ETH_MACCR_BL      ((uint32_t)0x00000060)  

  #define ETH_MACCR_BL_10    ((uint32_t)0x00000000)  
  #define ETH_MACCR_BL_8     ((uint32_t)0x00000020)  
  #define ETH_MACCR_BL_4     ((uint32_t)0x00000040)  
  #define ETH_MACCR_BL_1     ((uint32_t)0x00000060)   
#define ETH_MACCR_DC      ((uint32_t)0x00000010)  
#define ETH_MACCR_TE      ((uint32_t)0x00000008)  
#define ETH_MACCR_RE      ((uint32_t)0x00000004)  

#define ETH_MACFFR_RA     ((uint32_t)0x80000000)   
#define ETH_MACFFR_HPF    ((uint32_t)0x00000400)   
#define ETH_MACFFR_SAF    ((uint32_t)0x00000200)   
#define ETH_MACFFR_SAIF   ((uint32_t)0x00000100)   
#define ETH_MACFFR_PCF    ((uint32_t)0x000000C0)  
  #define ETH_MACFFR_PCF_BlockAll                ((uint32_t)0x00000040)  
  #define ETH_MACFFR_PCF_ForwardAll              ((uint32_t)0x00000080)  
  #define ETH_MACFFR_PCF_ForwardPassedAddrFilter ((uint32_t)0x000000C0)   
#define ETH_MACFFR_BFD    ((uint32_t)0x00000020)   
#define ETH_MACFFR_PAM    ((uint32_t)0x00000010)   
#define ETH_MACFFR_DAIF   ((uint32_t)0x00000008)   
#define ETH_MACFFR_HM     ((uint32_t)0x00000004)   
#define ETH_MACFFR_HU     ((uint32_t)0x00000002)  
#define ETH_MACFFR_PM     ((uint32_t)0x00000001)  

#define ETH_MACHTHR_HTH   ((uint32_t)0xFFFFFFFF)  

#define ETH_MACHTLR_HTL   ((uint32_t)0xFFFFFFFF)  

#define ETH_MACMIIAR_PA   ((uint32_t)0x0000F800)   
#define ETH_MACMIIAR_MR   ((uint32_t)0x000007C0)   
#define ETH_MACMIIAR_CR   ((uint32_t)0x0000001C)   
  #define ETH_MACMIIAR_CR_Div42   ((uint32_t)0x00000000)  
  #define ETH_MACMIIAR_CR_Div62   ((uint32_t)0x00000004)  
  #define ETH_MACMIIAR_CR_Div16   ((uint32_t)0x00000008)  
  #define ETH_MACMIIAR_CR_Div26   ((uint32_t)0x0000000C)  
  #define ETH_MACMIIAR_CR_Div102  ((uint32_t)0x00000010)    
#define ETH_MACMIIAR_MW   ((uint32_t)0x00000002)   
#define ETH_MACMIIAR_MB   ((uint32_t)0x00000001)   
  

#define ETH_MACMIIDR_MD   ((uint32_t)0x0000FFFF)  

#define ETH_MACFCR_PT     ((uint32_t)0xFFFF0000)  
#define ETH_MACFCR_ZQPD   ((uint32_t)0x00000080)  
#define ETH_MACFCR_PLT    ((uint32_t)0x00000030)  
  #define ETH_MACFCR_PLT_Minus4   ((uint32_t)0x00000000)  
  #define ETH_MACFCR_PLT_Minus28  ((uint32_t)0x00000010)  
  #define ETH_MACFCR_PLT_Minus144 ((uint32_t)0x00000020)  
  #define ETH_MACFCR_PLT_Minus256 ((uint32_t)0x00000030)        
#define ETH_MACFCR_UPFD   ((uint32_t)0x00000008)  
#define ETH_MACFCR_RFCE   ((uint32_t)0x00000004)  
#define ETH_MACFCR_TFCE   ((uint32_t)0x00000002)  
#define ETH_MACFCR_FCBBPA ((uint32_t)0x00000001)  

#define ETH_MACVLANTR_VLANTC ((uint32_t)0x00010000)  
#define ETH_MACVLANTR_VLANTI ((uint32_t)0x0000FFFF)  

 
#define ETH_MACRWUFFR_D   ((uint32_t)0xFFFFFFFF)  

 
#define ETH_MACPMTCSR_WFFRPR ((uint32_t)0x80000000)  
#define ETH_MACPMTCSR_GU     ((uint32_t)0x00000200)  
#define ETH_MACPMTCSR_WFR    ((uint32_t)0x00000040)  
#define ETH_MACPMTCSR_MPR    ((uint32_t)0x00000020)  
#define ETH_MACPMTCSR_WFE    ((uint32_t)0x00000004)  
#define ETH_MACPMTCSR_MPE    ((uint32_t)0x00000002)  
#define ETH_MACPMTCSR_PD     ((uint32_t)0x00000001)  

#define ETH_MACSR_TSTS      ((uint32_t)0x00000200)  
#define ETH_MACSR_MMCTS     ((uint32_t)0x00000040)  
#define ETH_MACSR_MMMCRS    ((uint32_t)0x00000020)  
#define ETH_MACSR_MMCS      ((uint32_t)0x00000010)  
#define ETH_MACSR_PMTS      ((uint32_t)0x00000008)  

#define ETH_MACIMR_TSTIM     ((uint32_t)0x00000200)  
#define ETH_MACIMR_PMTIM     ((uint32_t)0x00000008)  

#define ETH_MACA0HR_MACA0H   ((uint32_t)0x0000FFFF)  

#define ETH_MACA0LR_MACA0L   ((uint32_t)0xFFFFFFFF)  

#define ETH_MACA1HR_AE       ((uint32_t)0x80000000)  
#define ETH_MACA1HR_SA       ((uint32_t)0x40000000)  
#define ETH_MACA1HR_MBC      ((uint32_t)0x3F000000)  
  #define ETH_MACA1HR_MBC_HBits15_8    ((uint32_t)0x20000000)  
  #define ETH_MACA1HR_MBC_HBits7_0     ((uint32_t)0x10000000)  
  #define ETH_MACA1HR_MBC_LBits31_24   ((uint32_t)0x08000000)  
  #define ETH_MACA1HR_MBC_LBits23_16   ((uint32_t)0x04000000)  
  #define ETH_MACA1HR_MBC_LBits15_8    ((uint32_t)0x02000000)  
  #define ETH_MACA1HR_MBC_LBits7_0     ((uint32_t)0x01000000)   
#define ETH_MACA1HR_MACA1H   ((uint32_t)0x0000FFFF)  

#define ETH_MACA1LR_MACA1L   ((uint32_t)0xFFFFFFFF)  

#define ETH_MACA2HR_AE       ((uint32_t)0x80000000)  
#define ETH_MACA2HR_SA       ((uint32_t)0x40000000)  
#define ETH_MACA2HR_MBC      ((uint32_t)0x3F000000)  
  #define ETH_MACA2HR_MBC_HBits15_8    ((uint32_t)0x20000000)  
  #define ETH_MACA2HR_MBC_HBits7_0     ((uint32_t)0x10000000)  
  #define ETH_MACA2HR_MBC_LBits31_24   ((uint32_t)0x08000000)  
  #define ETH_MACA2HR_MBC_LBits23_16   ((uint32_t)0x04000000)  
  #define ETH_MACA2HR_MBC_LBits15_8    ((uint32_t)0x02000000)  
  #define ETH_MACA2HR_MBC_LBits7_0     ((uint32_t)0x01000000)  
#define ETH_MACA2HR_MACA2H   ((uint32_t)0x0000FFFF)  

#define ETH_MACA2LR_MACA2L   ((uint32_t)0xFFFFFFFF)  

#define ETH_MACA3HR_AE       ((uint32_t)0x80000000)  
#define ETH_MACA3HR_SA       ((uint32_t)0x40000000)  
#define ETH_MACA3HR_MBC      ((uint32_t)0x3F000000)  
  #define ETH_MACA3HR_MBC_HBits15_8    ((uint32_t)0x20000000)  
  #define ETH_MACA3HR_MBC_HBits7_0     ((uint32_t)0x10000000)  
  #define ETH_MACA3HR_MBC_LBits31_24   ((uint32_t)0x08000000)  
  #define ETH_MACA3HR_MBC_LBits23_16   ((uint32_t)0x04000000)  
  #define ETH_MACA3HR_MBC_LBits15_8    ((uint32_t)0x02000000)  
  #define ETH_MACA3HR_MBC_LBits7_0     ((uint32_t)0x01000000)  
#define ETH_MACA3HR_MACA3H   ((uint32_t)0x0000FFFF)  

#define ETH_MACA3LR_MACA3L   ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCCR_MCFHP      ((uint32_t)0x00000020)  
#define ETH_MMCCR_MCP        ((uint32_t)0x00000010)  
#define ETH_MMCCR_MCF        ((uint32_t)0x00000008)  
#define ETH_MMCCR_ROR        ((uint32_t)0x00000004)  
#define ETH_MMCCR_CSR        ((uint32_t)0x00000002)  
#define ETH_MMCCR_CR         ((uint32_t)0x00000001)  

#define ETH_MMCRIR_RGUFS     ((uint32_t)0x00020000)  
#define ETH_MMCRIR_RFAES     ((uint32_t)0x00000040)  
#define ETH_MMCRIR_RFCES     ((uint32_t)0x00000020)  

#define ETH_MMCTIR_TGFS      ((uint32_t)0x00200000)  
#define ETH_MMCTIR_TGFMSCS   ((uint32_t)0x00008000)  
#define ETH_MMCTIR_TGFSCS    ((uint32_t)0x00004000)  

#define ETH_MMCRIMR_RGUFM    ((uint32_t)0x00020000)  
#define ETH_MMCRIMR_RFAEM    ((uint32_t)0x00000040)  
#define ETH_MMCRIMR_RFCEM    ((uint32_t)0x00000020)  

#define ETH_MMCTIMR_TGFM     ((uint32_t)0x00200000)  
#define ETH_MMCTIMR_TGFMSCM  ((uint32_t)0x00008000)  
#define ETH_MMCTIMR_TGFSCM   ((uint32_t)0x00004000)  

#define ETH_MMCTGFSCCR_TGFSCC     ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCTGFMSCCR_TGFMSCC   ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCTGFCR_TGFC    ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCRFCECR_RFCEC  ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCRFAECR_RFAEC  ((uint32_t)0xFFFFFFFF)  

#define ETH_MMCRGUFCR_RGUFC  ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTSCR_TSCNT       ((uint32_t)0x00030000)  
#define ETH_PTPTSSR_TSSMRME     ((uint32_t)0x00008000)  
#define ETH_PTPTSSR_TSSEME      ((uint32_t)0x00004000)  
#define ETH_PTPTSSR_TSSIPV4FE   ((uint32_t)0x00002000)  
#define ETH_PTPTSSR_TSSIPV6FE   ((uint32_t)0x00001000)  
#define ETH_PTPTSSR_TSSPTPOEFE  ((uint32_t)0x00000800)  
#define ETH_PTPTSSR_TSPTPPSV2E  ((uint32_t)0x00000400)  
#define ETH_PTPTSSR_TSSSR       ((uint32_t)0x00000200)  
#define ETH_PTPTSSR_TSSARFE     ((uint32_t)0x00000100)  

#define ETH_PTPTSCR_TSARU    ((uint32_t)0x00000020)  
#define ETH_PTPTSCR_TSITE    ((uint32_t)0x00000010)  
#define ETH_PTPTSCR_TSSTU    ((uint32_t)0x00000008)  
#define ETH_PTPTSCR_TSSTI    ((uint32_t)0x00000004)  
#define ETH_PTPTSCR_TSFCU    ((uint32_t)0x00000002)  
#define ETH_PTPTSCR_TSE      ((uint32_t)0x00000001)  

#define ETH_PTPSSIR_STSSI    ((uint32_t)0x000000FF)  

#define ETH_PTPTSHR_STS      ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTSLR_STPNS    ((uint32_t)0x80000000)  
#define ETH_PTPTSLR_STSS     ((uint32_t)0x7FFFFFFF)  

#define ETH_PTPTSHUR_TSUS    ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTSLUR_TSUPNS  ((uint32_t)0x80000000)  
#define ETH_PTPTSLUR_TSUSS   ((uint32_t)0x7FFFFFFF)  

#define ETH_PTPTSAR_TSA      ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTTHR_TTSH     ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTTLR_TTSL     ((uint32_t)0xFFFFFFFF)  

#define ETH_PTPTSSR_TSTTR    ((uint32_t)0x00000020)  
#define ETH_PTPTSSR_TSSO     ((uint32_t)0x00000010)  

#define ETH_DMABMR_AAB       ((uint32_t)0x02000000)  
#define ETH_DMABMR_FPM        ((uint32_t)0x01000000)  
#define ETH_DMABMR_USP       ((uint32_t)0x00800000)  
#define ETH_DMABMR_RDP       ((uint32_t)0x007E0000)  
  #define ETH_DMABMR_RDP_1Beat    ((uint32_t)0x00020000)  
  #define ETH_DMABMR_RDP_2Beat    ((uint32_t)0x00040000)  
  #define ETH_DMABMR_RDP_4Beat    ((uint32_t)0x00080000)  
  #define ETH_DMABMR_RDP_8Beat    ((uint32_t)0x00100000)  
  #define ETH_DMABMR_RDP_16Beat   ((uint32_t)0x00200000)  
  #define ETH_DMABMR_RDP_32Beat   ((uint32_t)0x00400000)                  
  #define ETH_DMABMR_RDP_4xPBL_4Beat   ((uint32_t)0x01020000)  
  #define ETH_DMABMR_RDP_4xPBL_8Beat   ((uint32_t)0x01040000)  
  #define ETH_DMABMR_RDP_4xPBL_16Beat  ((uint32_t)0x01080000)  
  #define ETH_DMABMR_RDP_4xPBL_32Beat  ((uint32_t)0x01100000)  
  #define ETH_DMABMR_RDP_4xPBL_64Beat  ((uint32_t)0x01200000)  
  #define ETH_DMABMR_RDP_4xPBL_128Beat ((uint32_t)0x01400000)    
#define ETH_DMABMR_FB        ((uint32_t)0x00010000)  
#define ETH_DMABMR_RTPR      ((uint32_t)0x0000C000)  
  #define ETH_DMABMR_RTPR_1_1     ((uint32_t)0x00000000)  
  #define ETH_DMABMR_RTPR_2_1     ((uint32_t)0x00004000)  
  #define ETH_DMABMR_RTPR_3_1     ((uint32_t)0x00008000)  
  #define ETH_DMABMR_RTPR_4_1     ((uint32_t)0x0000C000)    
#define ETH_DMABMR_PBL    ((uint32_t)0x00003F00)  
  #define ETH_DMABMR_PBL_1Beat    ((uint32_t)0x00000100)  
  #define ETH_DMABMR_PBL_2Beat    ((uint32_t)0x00000200)  
  #define ETH_DMABMR_PBL_4Beat    ((uint32_t)0x00000400)  
  #define ETH_DMABMR_PBL_8Beat    ((uint32_t)0x00000800)  
  #define ETH_DMABMR_PBL_16Beat   ((uint32_t)0x00001000)  
  #define ETH_DMABMR_PBL_32Beat   ((uint32_t)0x00002000)                  
  #define ETH_DMABMR_PBL_4xPBL_4Beat   ((uint32_t)0x01000100)  
  #define ETH_DMABMR_PBL_4xPBL_8Beat   ((uint32_t)0x01000200)  
  #define ETH_DMABMR_PBL_4xPBL_16Beat  ((uint32_t)0x01000400)  
  #define ETH_DMABMR_PBL_4xPBL_32Beat  ((uint32_t)0x01000800)  
  #define ETH_DMABMR_PBL_4xPBL_64Beat  ((uint32_t)0x01001000)  
  #define ETH_DMABMR_PBL_4xPBL_128Beat ((uint32_t)0x01002000)  
#define ETH_DMABMR_EDE       ((uint32_t)0x00000080)  
#define ETH_DMABMR_DSL       ((uint32_t)0x0000007C)  
#define ETH_DMABMR_DA        ((uint32_t)0x00000002)  
#define ETH_DMABMR_SR        ((uint32_t)0x00000001)  

#define ETH_DMATPDR_TPD      ((uint32_t)0xFFFFFFFF)  

#define ETH_DMARPDR_RPD      ((uint32_t)0xFFFFFFFF)  

#define ETH_DMARDLAR_SRL     ((uint32_t)0xFFFFFFFF)  

#define ETH_DMATDLAR_STL     ((uint32_t)0xFFFFFFFF)  

#define ETH_DMASR_TSTS       ((uint32_t)0x20000000)  
#define ETH_DMASR_PMTS       ((uint32_t)0x10000000)  
#define ETH_DMASR_MMCS       ((uint32_t)0x08000000)  
#define ETH_DMASR_EBS        ((uint32_t)0x03800000)  
  
  #define ETH_DMASR_EBS_DescAccess      ((uint32_t)0x02000000)  
  #define ETH_DMASR_EBS_ReadTransf      ((uint32_t)0x01000000)  
  #define ETH_DMASR_EBS_DataTransfTx    ((uint32_t)0x00800000)  
#define ETH_DMASR_TPS         ((uint32_t)0x00700000)  
  #define ETH_DMASR_TPS_Stopped         ((uint32_t)0x00000000)  
  #define ETH_DMASR_TPS_Fetching        ((uint32_t)0x00100000)  
  #define ETH_DMASR_TPS_Waiting         ((uint32_t)0x00200000)  
  #define ETH_DMASR_TPS_Reading         ((uint32_t)0x00300000)  
  #define ETH_DMASR_TPS_Suspended       ((uint32_t)0x00600000)  
  #define ETH_DMASR_TPS_Closing         ((uint32_t)0x00700000)  
#define ETH_DMASR_RPS         ((uint32_t)0x000E0000)  
  #define ETH_DMASR_RPS_Stopped         ((uint32_t)0x00000000)  
  #define ETH_DMASR_RPS_Fetching        ((uint32_t)0x00020000)  
  #define ETH_DMASR_RPS_Waiting         ((uint32_t)0x00060000)  
  #define ETH_DMASR_RPS_Suspended       ((uint32_t)0x00080000)  
  #define ETH_DMASR_RPS_Closing         ((uint32_t)0x000A0000)  
  #define ETH_DMASR_RPS_Queuing         ((uint32_t)0x000E0000)  
#define ETH_DMASR_NIS        ((uint32_t)0x00010000)  
#define ETH_DMASR_AIS        ((uint32_t)0x00008000)  
#define ETH_DMASR_ERS        ((uint32_t)0x00004000)  
#define ETH_DMASR_FBES       ((uint32_t)0x00002000)  
#define ETH_DMASR_ETS        ((uint32_t)0x00000400)  
#define ETH_DMASR_RWTS       ((uint32_t)0x00000200)  
#define ETH_DMASR_RPSS       ((uint32_t)0x00000100)  
#define ETH_DMASR_RBUS       ((uint32_t)0x00000080)  
#define ETH_DMASR_RS         ((uint32_t)0x00000040)  
#define ETH_DMASR_TUS        ((uint32_t)0x00000020)  
#define ETH_DMASR_ROS        ((uint32_t)0x00000010)  
#define ETH_DMASR_TJTS       ((uint32_t)0x00000008)  
#define ETH_DMASR_TBUS       ((uint32_t)0x00000004)  
#define ETH_DMASR_TPSS       ((uint32_t)0x00000002)  
#define ETH_DMASR_TS         ((uint32_t)0x00000001)  

#define ETH_DMAOMR_DTCEFD    ((uint32_t)0x04000000)  
#define ETH_DMAOMR_RSF       ((uint32_t)0x02000000)  
#define ETH_DMAOMR_DFRF      ((uint32_t)0x01000000)  
#define ETH_DMAOMR_TSF       ((uint32_t)0x00200000)  
#define ETH_DMAOMR_FTF       ((uint32_t)0x00100000)  
#define ETH_DMAOMR_TTC       ((uint32_t)0x0001C000)  
  #define ETH_DMAOMR_TTC_64Bytes       ((uint32_t)0x00000000)  
  #define ETH_DMAOMR_TTC_128Bytes      ((uint32_t)0x00004000)  
  #define ETH_DMAOMR_TTC_192Bytes      ((uint32_t)0x00008000)  
  #define ETH_DMAOMR_TTC_256Bytes      ((uint32_t)0x0000C000)  
  #define ETH_DMAOMR_TTC_40Bytes       ((uint32_t)0x00010000)  
  #define ETH_DMAOMR_TTC_32Bytes       ((uint32_t)0x00014000)  
  #define ETH_DMAOMR_TTC_24Bytes       ((uint32_t)0x00018000)  
  #define ETH_DMAOMR_TTC_16Bytes       ((uint32_t)0x0001C000)  
#define ETH_DMAOMR_ST        ((uint32_t)0x00002000)  
#define ETH_DMAOMR_FEF       ((uint32_t)0x00000080)  
#define ETH_DMAOMR_FUGF      ((uint32_t)0x00000040)  
#define ETH_DMAOMR_RTC       ((uint32_t)0x00000018)  
  #define ETH_DMAOMR_RTC_64Bytes       ((uint32_t)0x00000000)  
  #define ETH_DMAOMR_RTC_32Bytes       ((uint32_t)0x00000008)  
  #define ETH_DMAOMR_RTC_96Bytes       ((uint32_t)0x00000010)  
  #define ETH_DMAOMR_RTC_128Bytes      ((uint32_t)0x00000018)  
#define ETH_DMAOMR_OSF       ((uint32_t)0x00000004)  
#define ETH_DMAOMR_SR        ((uint32_t)0x00000002)  

#define ETH_DMAIER_NISE      ((uint32_t)0x00010000)  
#define ETH_DMAIER_AISE      ((uint32_t)0x00008000)  
#define ETH_DMAIER_ERIE      ((uint32_t)0x00004000)  
#define ETH_DMAIER_FBEIE     ((uint32_t)0x00002000)  
#define ETH_DMAIER_ETIE      ((uint32_t)0x00000400)  
#define ETH_DMAIER_RWTIE     ((uint32_t)0x00000200)  
#define ETH_DMAIER_RPSIE     ((uint32_t)0x00000100)  
#define ETH_DMAIER_RBUIE     ((uint32_t)0x00000080)  
#define ETH_DMAIER_RIE       ((uint32_t)0x00000040)  
#define ETH_DMAIER_TUIE      ((uint32_t)0x00000020)  
#define ETH_DMAIER_ROIE      ((uint32_t)0x00000010)  
#define ETH_DMAIER_TJTIE     ((uint32_t)0x00000008)  
#define ETH_DMAIER_TBUIE     ((uint32_t)0x00000004)  
#define ETH_DMAIER_TPSIE     ((uint32_t)0x00000002)  
#define ETH_DMAIER_TIE       ((uint32_t)0x00000001)  

#define ETH_DMAMFBOCR_OFOC   ((uint32_t)0x10000000)  
#define ETH_DMAMFBOCR_MFA    ((uint32_t)0x0FFE0000)  
#define ETH_DMAMFBOCR_OMFC   ((uint32_t)0x00010000)  
#define ETH_DMAMFBOCR_MFC    ((uint32_t)0x0000FFFF)  

#define ETH_DMACHTDR_HTDAP   ((uint32_t)0xFFFFFFFF)  

#define ETH_DMACHRDR_HRDAP   ((uint32_t)0xFFFFFFFF)  

#define ETH_DMACHTBAR_HTBAP  ((uint32_t)0xFFFFFFFF)  

#define ETH_DMACHRBAR_HRBAP  ((uint32_t)0xFFFFFFFF)  

 

 

#ifdef USE_STDPERIPH_DRIVER
  #include "stm32f4xx_conf.h"
#endif 

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#ifdef __cplusplus
}
#endif 

#endif 

  

