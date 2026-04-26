while (1) 
{
  //There's another line here
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, SET);
  delay(500);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, RESET);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, SET);
  delay(500);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, RESET);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, SET);
  delay(500);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, RESET);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, SET);
  delay(1000);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, RESET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, RESET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, RESET);
}
