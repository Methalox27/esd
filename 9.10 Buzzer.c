// PB4 -> GPIO_Output

while (1) 
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
  HAL_Delay(500);

  //or
  // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);
  // HAL_Delay(500);
  // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);
  // HAL_Delay(500);
}
