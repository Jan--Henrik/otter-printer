#include "main.h"
#include "usb_device.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim2_ch1;
DMA_HandleTypeDef hdma_tim2_ch4;
DMA_HandleTypeDef hdma_tim2_ch3;

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;
DMA_HandleTypeDef hdma_tim2_uev;

uint16_t PER = 300;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
void transmit_error_handler(DMA_HandleTypeDef * hdma);
void data_tramsmitted_handler(DMA_HandleTypeDef * hdma);
void dma_init();

void dfu_otter_bootloader(void)
{
  *((unsigned long *)0x20003FF0) = 0xDEADBEEF;
  NVIC_SystemReset();
}

#define data_len 112
uint16_t my_data_buf[data_len];

uint16_t my_data_buf_fire[8];

void dataTransmittedHandler0(DMA_HandleTypeDef *hdma) {
  HAL_GPIO_WritePin(GPIOB, LED_STATUS_Pin, 0);
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}
void dataTransmittedHandler1(DMA_HandleTypeDef *hdma) {
  HAL_GPIO_WritePin(GPIOB, LED_POWER_Pin, 0);
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
}
void dataTransmittedHandler2(DMA_HandleTypeDef *hdma) {
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_USB_DEVICE_Init();

  if (HAL_GPIO_ReadPin(GPIOB, BUTTON_Pin)) {
    dfu_otter_bootloader();
  }

  HAL_GPIO_WritePin(GPIOB, LED_POWER_Pin, 1);

  memset(my_data_buf, 0xFF, data_len);
  for (uint16_t i = 0; i < data_len - 1; i += 8) {
    my_data_buf[i]      = 0xFF01;
    my_data_buf[i + 1]  = 0xFF80;
    my_data_buf[i + 2]  = 0xFF01;
    my_data_buf[i + 3]  = 0xFF04;
    my_data_buf[i + 4]  = 0xFF01;
    my_data_buf[i + 5]  = 0xFF08;
    my_data_buf[i + 6]  = 0xFF01;
    my_data_buf[i + 7]  = 0xFF40;
  }

  memset(my_data_buf, 0x00, 8);
  my_data_buf_fire[0] = 0x0002;
  my_data_buf_fire[1] = 0x0002;
  my_data_buf_fire[2] = 0x0000;
  my_data_buf_fire[3] = 0x0000;
  my_data_buf_fire[4] = 0x0001;
  my_data_buf_fire[5] = 0x0001;
  my_data_buf_fire[6] = 0x0000;
  my_data_buf_fire[7] = 0x0000;


  htim2.hdma[TIM_DMA_ID_CC1]->XferCpltCallback = dataTransmittedHandler0;
  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);

  htim2.hdma[TIM_DMA_ID_CC3]->XferCpltCallback = dataTransmittedHandler1;
  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC3);

  htim2.hdma[TIM_DMA_ID_CC4]->XferCpltCallback = dataTransmittedHandler2;
  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC4);

  startDMA();

  while (1)
  {
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOB, LED_STATUS_Pin, 1);
    HAL_GPIO_WritePin(GPIOB, LED_POWER_Pin, 1);
    startDMA();
  }
}
void startDMA() {


  if (HAL_DMA_GetState(htim2.hdma[TIM_DMA_ID_CC1]) == HAL_DMA_STATE_BUSY) {
    return;
  }
  if (HAL_DMA_GetState(htim2.hdma[TIM_DMA_ID_CC3]) == HAL_DMA_STATE_BUSY) {
    return;
  }
  if (HAL_DMA_GetState(htim2.hdma[TIM_DMA_ID_CC4]) == HAL_DMA_STATE_BUSY) {
    return;
  }


  HAL_DMA_Start_IT(htim2.hdma[TIM_DMA_ID_CC1], (uint32_t)my_data_buf, (uint32_t)&GPIOA->ODR, data_len);
  HAL_DMA_Start_IT(htim2.hdma[TIM_DMA_ID_CC3], (uint32_t)my_data_buf_fire, (uint32_t)&GPIOB->ODR, 8);
  HAL_DMA_Start_IT(htim2.hdma[TIM_DMA_ID_CC4], (uint32_t)my_data_buf, (uint32_t)&GPIOC->ODR, data_len);

  TIM2->CNT = 0u;

  if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

}

static void MX_TIM1_Init(void)
{

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  HAL_TIM_Encoder_Init(&htim1, &sConfig);
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);
  

}

static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC1 = {0};
  TIM_OC_InitTypeDef sConfigOC4 = {0};
  TIM_OC_InitTypeDef sConfigOC3 = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = PER;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&htim2);
  
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
 
  HAL_TIM_PWM_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigOC1.OCMode = TIM_OCMODE_PWM1;
  sConfigOC1.Pulse = PER / 3;
  sConfigOC1.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC1, TIM_CHANNEL_1);
 
  sConfigOC4.OCMode = TIM_OCMODE_PWM1;
  sConfigOC4.Pulse = (PER / 3) * 2;
  sConfigOC4.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC4.OCFastMode = TIM_OCFAST_DISABLE;
 HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC4, TIM_CHANNEL_4);

  sConfigOC3.OCMode = TIM_OCMODE_PWM1;
  sConfigOC3.Pulse = PER / 3;
  sConfigOC3.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC3.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC3, TIM_CHANNEL_3);
}

static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&huart3);
}

static void MX_DMA_Init(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOC, D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOA, DCLCK_Pin | S5_Pin | S2_Pin | S3_Pin
                    | S4_Pin | S1_Pin | LED_STATUSA15_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, LED_STATUS_Pin | LED_POWER_Pin | CSYNC_Pin  | F3_Pin | F5_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = D1_Pin | D2_Pin | D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DCLCK_Pin | S5_Pin | S2_Pin | S3_Pin
                        | S4_Pin | S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = INT_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT_IN_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =  F3_Pin | F5_Pin | LED_STATUS_Pin | LED_POWER_Pin | CSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = INDEX_Pin | BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ANALOG_INPUT3_Pin | ANALOG_INPUT2_Pin | ANALOG_INPUT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void Error_Handler(void)
{

}