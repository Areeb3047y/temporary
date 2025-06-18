
# Lab: Blinking an LED with a Timer

## Objective

- Learn how to use a hardware timer to create a precise delay.
- Blink an LED at a 1-second interval using a timer interrupt.
- Understand the difference between using a timer and a software delay loop.

## Instructions

1.  **Create a new project in STM32CubeIDE.**
2.  **Configure the Timer:**
    *   Enable a general-purpose timer (e.g., TIM2).
    *   Set the prescaler and auto-reload register (ARR) to get a 1-second interrupt.
    *   Enable the timer interrupt in the NVIC settings.
3.  **Configure the GPIO for the LED.**
4.  **Generate the code.**
5.  **In `main.c`, start the timer in interrupt mode.**
6.  **Implement the timer interrupt callback function.** This function will be called every time the timer overflows (in this case, every 1 second).
7.  **Inside the callback function, toggle the LED.**
8.  **Build and flash the code to your board.**

## Challenge

- Modify the timer settings to make the LED blink every 200 milliseconds.
