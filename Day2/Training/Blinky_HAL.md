# Creating a Blinky Project with HAL

This guide will walk you through the process of creating a simple "Blinky" project for the STM32F7 Discovery or Bluepill board using the STM32CubeIDE and the HAL (Hardware Abstraction Layer).

## 1. Create a New Project in STM32CubeIDE

1.  Open STM32CubeIDE and go to **File > New > STM32 Project**.
2.  Select your target board (STM32F7 Discovery or Bluepill).
3.  Enter a project name (e.g., `Blinky_HAL`) and click **Finish**.

## 2. Configure the Clock

1.  In the **Pinout & Configuration** view, go to the **System Core** tab and select **RCC**.
2.  In the **HSE** (High-Speed External) dropdown, select **Crystal/Ceramic Resonator**.
3.  Go to the **Clock Configuration** tab and set the **HCLK** (AHB Clock) to the maximum frequency for your board.

## 3. Configure the LED Pin

1.  Go back to the **Pinout & Configuration** view.
2.  Find the pin connected to the user LED on your board (e.g., PI1 for the STM32F7 Discovery, PC13 for the Bluepill).
3.  Click on the pin and select **GPIO_Output**.

## 4. Generate the Code

1.  Go to **Project > Generate Code**.

## 5. Write the Blinky Code

1.  Open the `main.c` file.
2.  Inside the `while(1)` loop, add the following code:

```c
/* USER CODE BEGIN WHILE */
while (1)
{
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1); // For STM32F7 Discovery
  // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // For Bluepill
  HAL_Delay(1000);
}
/* USER CODE END 3 */
```

## 6. Build and Run the Project

1.  Go to **Project > Build All**.
2.  Go to **Run > Debug**.
3.  Click the **Resume** button to start the program.

You should now see the user LED on your board blinking.
