// I2C1_SCL = PB8  (D15)
// I2C1_SDA = PB9  (D14)
// Connectivity -> I2C1 -> I2C

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t buf[2]; 
float lux = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN WHILE */
while (1)
{
    // 1. Send "One-Time High-Res" command (0x20)
    buf[0] = 0x20;
    HAL_I2C_Master_Transmit(&hi2c1, 0x46, buf, 1, 100); 

    // 2. Wait for sensor to calculate
    HAL_Delay(150); 

    // 3. Read the 2 bytes back
    HAL_I2C_Master_Receive(&hi2c1, 0x46, buf, 2, 100);

    // 4. Combine bytes and convert to lux
    lux = ((buf[0] << 8) | buf[1]) / 1.2; 
    
    HAL_Delay(500);
}
  /* USER CODE END 3 */
}
