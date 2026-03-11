/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body (HC-SR04 on PA8 and PB10)
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h> // Needed for sprintf

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint32_t pMillis;
uint32_t Value1 = 0;
uint32_t Value2 = 0;
float Distance = 0;  // cm
char msg[50];        // Buffer to hold the text string
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim2); // MUST BE HERE TO START THE TIMER!
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      // 0. Explicitly clear the Trig pin (PA8) and let it stabilize
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
      HAL_Delay(1);

      // 1. Force Trig LOW for 2us
      __HAL_TIM_SET_COUNTER(&htim2, 0);
      while (__HAL_TIM_GET_COUNTER(&htim2) < 2);

      // 2. Send 10us HIGH pulse to TRIG (PA8)
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
      __HAL_TIM_SET_COUNTER(&htim2, 0);
      while (__HAL_TIM_GET_COUNTER(&htim2) < 10);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

      // 3. Wait for ECHO (PB10) to go HIGH with timeout
      __HAL_TIM_SET_COUNTER(&htim2, 0);
      while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET) {
          if (__HAL_TIM_GET_COUNTER(&htim2) > 20000) break;
      }

      // 4. Measure ECHO (PB10) pulse duration with timeout
      __HAL_TIM_SET_COUNTER(&htim2, 0); // Reset timer to 0!
      while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET) {
          if (__HAL_TIM_GET_COUNTER(&htim2) > 30000) break;
      }
      Value2 = __HAL_TIM_GET_COUNTER(&htim2); // Value2 is now the total duration in us

      // 5. Calculate Distance
      // Only calculate if we didn't hit the 30,000us timeout
      if (Value2 < 30000) {
          // Using 0.01715 (which is 0.0343 / 2)
          Distance = (float)Value2 * 0.01715f;
      } else {
          Distance = 0;
      }

      // 6. Print to Serial Monitor
      // Casting float to int so standard %d works properly
      int len = sprintf(msg, "Distance: %d cm\r\n", (int)Distance);
      HAL_UART_Transmit(&huart2, (uint8_t*)msg, len, HAL_MAX_DELAY);

      // 7. Wait 100ms before next ping to prevent echo overlap
      HAL_Delay(100);
  }
  /* USER CODE END 3 */
}
