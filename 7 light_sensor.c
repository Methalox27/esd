// I2C1_SCL = PB8  (D15)
// I2C1_SDA = PB9  (D14)
// Connectivity -> I2C1 -> I2C

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t i2c_buf[2];      // Buffer to hold raw data from sensor
float lux = 0;           // Resulting light value
HAL_StatusTypeDef ret;   // To check if I2C commands succeed

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
    /* USER CODE END WHILE */
  	  i2c_buf[0] = 0x10;
	  ret = HAL_I2C_Master_Transmit(&hi2c1, (0x23 << 1), i2c_buf, 1, 100);

	  if (ret != HAL_OK) {
		  // Error: Check your wiring or pull-up resistors!
	  } else {
		  // Wait for sensor to finish measuring (typically 180ms)
		  HAL_Delay(200);

		  // 3. Read 2 bytes of data back
		  ret = HAL_I2C_Master_Receive(&hi2c1, (0x23 << 1), i2c_buf, 2, 100);

		  if (ret == HAL_OK) {
			  // 4. Convert 2 bytes into a single value
			  // Formula: (High Byte << 8) | Low Byte
			  uint16_t raw_val = (i2c_buf[0] << 8) | i2c_buf[1];
			  lux = raw_val / 1.2; // Standard BH1750 conversion
		  }
	  }

	  HAL_Delay(500); // Wait half a second before next reading
	  /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
