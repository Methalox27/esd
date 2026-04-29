// PA0 = ADC1_IN0  (A0 pin) . under analog -> adc1 select IN0
// Continuous Conversion Mode  = Enabled
// Rank -> Sampling time = 54 cycles

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint32_t adc_val = 0;
char msg[20]; // Buffer to hold the string for UART
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
 
  /* USER CODE BEGIN 2 */
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
    {
        // 1. Start the ADC for a fresh sample
        HAL_ADC_Start(&hadc1);

        // 2. Wait for the conversion to finish (10ms timeout)
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            // 3. Get the raw value (0 - 4095)
            adc_val = HAL_ADC_GetValue(&hadc1);

        }

        // 7. Stop the ADC to clear flags for the next iteration
        HAL_ADC_Stop(&hadc1);

        // 8. Small delay to keep the Serial Monitor readable
        HAL_Delay(50);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}
