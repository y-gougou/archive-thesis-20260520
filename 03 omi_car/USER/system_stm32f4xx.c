

  
  

#include "stm32f4xx.h"

     
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)

#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)

#endif  

#if defined (STM32F411xE)    

#if defined (USE_HSE_BYPASS)     
#define HSE_BYPASS_INPUT_FREQUENCY   8000000
#endif     
#endif 
    

#define VECT_TAB_OFFSET  0x00 

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx)

#define PLL_M      8
#else 
#if defined (USE_HSE_BYPASS)
#define PLL_M      8    
#else    
#define PLL_M      16
#endif 
#endif   

#define PLL_Q      7

#if defined (STM32F40_41xxx)
#define PLL_N      336

#define PLL_P      2
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
#define PLL_N      360

#define PLL_P      2
#endif 

#if defined (STM32F401xx)
#define PLL_N      336

#define PLL_P      4
#endif 

#if defined (STM32F411xE)
#define PLL_N      400

#define PLL_P      4   
#endif 

#if defined (STM32F40_41xxx)
  uint32_t SystemCoreClock = 168000000;
#endif 

#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
  uint32_t SystemCoreClock = 180000000;
#endif 

#if defined (STM32F401xx)
  uint32_t SystemCoreClock = 84000000;
#endif 

#if defined (STM32F411xE)
  uint32_t SystemCoreClock = 100000000;
#endif 

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

static void SetSysClock(void);

#if defined (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM)
static void SystemInit_ExtMemCtl(void); 
#endif 

void SystemInit(void)
{
  
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
  #endif
  
  
  RCC->CR |= (uint32_t)0x00000001;

  
  RCC->CFGR = 0x00000000;

  
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  
  RCC->PLLCFGR = 0x24003010;

  
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  
  RCC->CIR = 0x00000000;

#if defined (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl(); 
#endif 
         
  

  SetSysClock();

  
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; 
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
#endif
}

void SystemCoreClockUpdate(void)
{
  uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
  
  
  tmp = RCC->CFGR & RCC_CFGR_SWS;

  switch (tmp)
  {
    case 0x00:  
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04:  
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08:  
       

    
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx)
      if (pllsource != 0)
      {
        
        pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
      }
      else
      {
        
        pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
      }
#elif defined (STM32F411xE)
#if defined (USE_HSE_BYPASS)
      if (pllsource != 0)
      {
        
        pllvco = (HSE_BYPASS_INPUT_FREQUENCY / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
      }  
#else  
      if (pllsource == 0)
      {
        
        pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
      }  
#endif   
#endif   
      pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
      SystemCoreClock = pllvco/pllp;      
      break;
    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
  
  
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  
  SystemCoreClock >>= tmp;
}

static void SetSysClock(void)
{
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx)

  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)      
    
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    
    
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
#endif 

#if defined (STM32F401xx)
    
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
    
    
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
#endif 
   
    
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    
    RCC->CR |= RCC_CR_PLLON;

    
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
   
#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
    
    PWR->CR |= PWR_CR_ODEN;
    while((PWR->CSR & PWR_CSR_ODRDY) == 0)
    {
    }
    PWR->CR |= PWR_CR_ODSWEN;
    while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
    {
    }      
    
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
#endif 

#if defined (STM32F40_41xxx)     
    
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
#endif 

#if defined (STM32F401xx)
    
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;
#endif 

    
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  { 

  }
#elif defined (STM32F411xE)
#if defined (USE_HSE_BYPASS) 

  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  
  RCC->CR |= ((uint32_t)RCC_CR_HSEON | RCC_CR_HSEBYP);
 
  
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
    
    
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);
    
    
    RCC->CR |= RCC_CR_PLLON;

    
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

    
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  { 

  }
#else 
  
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_VOS;
  
  
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
  
  
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
  
  
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
  
  
  RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (PLL_Q << 24); 
  
  
  RCC->CR |= RCC_CR_PLLON;
  
  
  while((RCC->CR & RCC_CR_PLLRDY) == 0)
  {
  }
  
  
  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;
  
  
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  
  
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
  {
  }
#endif   
#endif   
}

 
#ifdef DATA_IN_ExtSRAM

void SystemInit_ExtMemCtl(void)
{

   
  RCC->AHB1ENR   |= 0x00000078;
  
  
  GPIOD->AFR[0]  = 0x00cc00cc;
  GPIOD->AFR[1]  = 0xcccccccc;
    
  GPIOD->MODER   = 0xaaaa0a0a;
    
  GPIOD->OSPEEDR = 0xffff0f0f;
    
  GPIOD->OTYPER  = 0x00000000;
   
  GPIOD->PUPDR   = 0x00000000;

  
  GPIOE->AFR[0]  = 0xcccccccc;
  GPIOE->AFR[1]  = 0xcccccccc;
   
  GPIOE->MODER   = 0xaaaaaaaa;
   
  GPIOE->OSPEEDR = 0xffffffff;
    
  GPIOE->OTYPER  = 0x00000000;
   
  GPIOE->PUPDR   = 0x00000000;

  
  GPIOF->AFR[0]  = 0x00cccccc;
  GPIOF->AFR[1]  = 0xcccc0000;
     
  GPIOF->MODER   = 0xaa000aaa;
   
  GPIOF->OSPEEDR = 0xff000fff;
    
  GPIOF->OTYPER  = 0x00000000;
   
  GPIOF->PUPDR   = 0x00000000;

  
  GPIOG->AFR[0]  = 0x00cccccc;
  GPIOG->AFR[1]  = 0x000000c0;
   
  GPIOG->MODER   = 0x00080aaa;
   
  GPIOG->OSPEEDR = 0x000c0fff;
    
  GPIOG->OTYPER  = 0x00000000;
   
  GPIOG->PUPDR   = 0x00000000;
  

  
  RCC->AHB3ENR         |= 0x00000001;
  
#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
  
  FMC_Bank1->BTCR[2]  = 0x00001011;
  FMC_Bank1->BTCR[3]  = 0x00000201;
  FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif  

#if defined (STM32F40_41xxx)
  
  FSMC_Bank1->BTCR[2]  = 0x00001011;
  FSMC_Bank1->BTCR[3]  = 0x00000201;
  FSMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif  

  
}
#endif 
  
#ifdef DATA_IN_ExtSDRAM

void SystemInit_ExtMemCtl(void)
{
  register uint32_t tmpreg = 0, timeout = 0xFFFF;
  register uint32_t index;

  

  RCC->AHB1ENR |= 0x000001FC;
  
  
  GPIOC->AFR[0]  = 0x0000000c;
  GPIOC->AFR[1]  = 0x00007700;
    
  GPIOC->MODER   = 0x00a00002;
    
  GPIOC->OSPEEDR = 0x00a00002;
    
  GPIOC->OTYPER  = 0x00000000;
   
  GPIOC->PUPDR   = 0x00500000;
  
  
  GPIOD->AFR[0]  = 0x000000CC;
  GPIOD->AFR[1]  = 0xCC000CCC;
    
  GPIOD->MODER   = 0xA02A000A;
    
  GPIOD->OSPEEDR = 0xA02A000A;
    
  GPIOD->OTYPER  = 0x00000000;
   
  GPIOD->PUPDR   = 0x00000000;

  
  GPIOE->AFR[0]  = 0xC00000CC;
  GPIOE->AFR[1]  = 0xCCCCCCCC;
   
  GPIOE->MODER   = 0xAAAA800A;
   
  GPIOE->OSPEEDR = 0xAAAA800A;
    
  GPIOE->OTYPER  = 0x00000000;
   
  GPIOE->PUPDR   = 0x00000000;

  
  GPIOF->AFR[0]  = 0xcccccccc;
  GPIOF->AFR[1]  = 0xcccccccc;
     
  GPIOF->MODER   = 0xAA800AAA;
   
  GPIOF->OSPEEDR = 0xAA800AAA;
    
  GPIOF->OTYPER  = 0x00000000;
   
  GPIOF->PUPDR   = 0x00000000;

  
  GPIOG->AFR[0]  = 0xcccccccc;
  GPIOG->AFR[1]  = 0xcccccccc;
   
  GPIOG->MODER   = 0xaaaaaaaa;
   
  GPIOG->OSPEEDR = 0xaaaaaaaa;
    
  GPIOG->OTYPER  = 0x00000000;
   
  GPIOG->PUPDR   = 0x00000000;
  
  
  GPIOH->AFR[0]  = 0x00C0CC00;
  GPIOH->AFR[1]  = 0xCCCCCCCC;
   
  GPIOH->MODER   = 0xAAAA08A0;
   
  GPIOH->OSPEEDR = 0xAAAA08A0;
    
  GPIOH->OTYPER  = 0x00000000;
   
  GPIOH->PUPDR   = 0x00000000;
  
  
  GPIOI->AFR[0]  = 0xCCCCCCCC;
  GPIOI->AFR[1]  = 0x00000CC0;
   
  GPIOI->MODER   = 0x0028AAAA;
   
  GPIOI->OSPEEDR = 0x0028AAAA;
    
  GPIOI->OTYPER  = 0x00000000;
   
  GPIOI->PUPDR   = 0x00000000;
  

  
  RCC->AHB3ENR |= 0x00000001;
  
  
  FMC_Bank5_6->SDCR[0] = 0x000039D0;
  FMC_Bank5_6->SDTR[0] = 0x01115351;      
  
  
  
  FMC_Bank5_6->SDCMR = 0x00000011; 
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  while((tmpreg != 0) & (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
  
  
  for (index = 0; index<1000; index++);
  
  
  FMC_Bank5_6->SDCMR = 0x00000012;           
  timeout = 0xFFFF;
  while((tmpreg != 0) & (timeout-- > 0))
  {
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
  
  
  FMC_Bank5_6->SDCMR = 0x00000073;
  timeout = 0xFFFF;
  while((tmpreg != 0) & (timeout-- > 0))
  {
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
 
  
  FMC_Bank5_6->SDCMR = 0x00046014;
  timeout = 0xFFFF;
  while((tmpreg != 0) & (timeout-- > 0))
  {
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  } 
  
  
  tmpreg = FMC_Bank5_6->SDRTR;
  FMC_Bank5_6->SDRTR = (tmpreg | (0x0000027C<<1));
  
  
  tmpreg = FMC_Bank5_6->SDCR[0]; 
  FMC_Bank5_6->SDCR[0] = (tmpreg & 0xFFFFFDFF);
  

  
}
#endif 

  

    

