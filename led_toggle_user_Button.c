//PA5 -> GPIO_Output
//PC13 -> GPIO_Input

while (1)
  {
    // Check if the button is pressed (State goes to RESET/LOW)
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) 
    {
      // Toggle the inbuilt LED
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); 
      
      // A small delay for "debouncing" so it doesn't toggle multiple times per press
      HAL_Delay(250); 
    }
  }
