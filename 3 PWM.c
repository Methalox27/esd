// PA5 -> TIM2_CH1
// Timers -> Tim2 -> Clock Source = Internal Clock, Channel 1 = PWM Generation CH1
// Under configurations, Prescalar = 83, Counter Period = 500, Auto Reload Period = Enabled

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN 0 */
void led_set_brightness(uint32_t level){
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, level);
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
 
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      // Increase brightness
      for(int i = 0; i < 500; i++)
      {
          led_set_brightness(i);
          HAL_Delay(2); // Fixed: lowercase 'elay'
      }

      // Decrease brightness
      for(int i = 500; i > 0; i--)
      {
          led_set_brightness(i);
          HAL_Delay(2);
      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
