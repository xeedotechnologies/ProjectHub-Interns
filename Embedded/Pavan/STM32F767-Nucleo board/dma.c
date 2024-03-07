#include "main.h"

DMA_HandleTypeDef hdma_memtomem_dma2_stream0;

void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_DMA_Init(void);

void DmaXferCompleteCallback(DMA_HandleTypeDef *hdma);	// Data Transfer Complete callback
static char Source[]={'P', 'A', 'V', 'A', 'N', 'S', '0', '2', '2', '8', '0'};
static char Dest[20];

int main(void)
{
  MPU_Config();
  HAL_Init();
  SystemClock_Config();
  MX_DMA_Init();
  hdma_memtomem_dma2_stream0.XferCpltCallback = &DmaXferCompleteCallback;
  HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0,(uint32_t)Source,(uint32_t)Dest,sizeof(Source));
  while (1)
  {
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_DMA_Init(void)
{

  __HAL_RCC_DMA2_CLK_ENABLE();
  hdma_memtomem_dma2_stream0.Instance = DMA2_Stream0;
  hdma_memtomem_dma2_stream0.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream0.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream0.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_memtomem_dma2_stream0.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_memtomem_dma2_stream0.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream0.Init.Priority = DMA_PRIORITY_LOW;
  hdma_memtomem_dma2_stream0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_memtomem_dma2_stream0.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream0.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream0) != HAL_OK)
  {
    Error_Handler( );
  }

  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

void DmaXferCompleteCallback(DMA_HandleTypeDef *hdma)
{
	__NOP();
}

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  HAL_MPU_Disable();

  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
