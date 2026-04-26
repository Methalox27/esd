while (1) 
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
  delay(500);

  //or
  // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);
  // delay(500);
  // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);
  // delay(500);
}
