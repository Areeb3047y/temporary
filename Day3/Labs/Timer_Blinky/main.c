
#include "main.h"

/*
 * This lab demonstrates how to use a hardware timer to blink an LED.
 * A timer interrupt is configured to fire every 1 second.
 * Inside the timer's interrupt service routine (ISR), the LED is toggled.
 * This is a much more efficient way to create delays than using software loops.
 */

// Function to initialize the GPIO for the LED
void GPIO_Init(void) {
    // Enable the clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA5 as output
    GPIOA->MODER |= GPIO_MODER_MODER5_0;
    GPIOA->MODER &= ~GPIO_MODER_MODER5_1;
}

// Function to initialize the Timer
void TIM2_Init(void) {
    // Enable the clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Set the prescaler and auto-reload register to get a 1-second interrupt
    // The formula is: Update_Event = Clock / ((Prescaler + 1) * (AutoReloadRegister + 1))
    // For a 16MHz clock, we can use a prescaler of 15999 and an ARR of 999
    TIM2->PSC = 15999;
    TIM2->ARR = 999;

    // Enable the update interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Enable the TIM2 interrupt in the NVIC
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Timer interrupt handler
void TIM2_IRQHandler(void) {
    // Check if the update interrupt flag is set
    if (TIM2->SR & TIM_SR_UIF) {
        // Clear the interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;

        // Toggle the LED
        GPIOA->ODR ^= GPIO_ODR_OD5;
    }
}

int main(void) {
    // Initialize the system
    HAL_Init();
    SystemClock_Config();

    // Initialize the GPIO and Timer
    GPIO_Init();
    TIM2_Init();

    while (1) {
        // The main loop is empty because the LED is toggled in the timer interrupt
    }
}

