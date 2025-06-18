"""#include "stm32f7xx.h" // For STM32F7 Discovery
// #include "stm32f1xx.h" // For Bluepill

// This function is called by the startup code
void SystemInit(void)
{
    // Enable FPU
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
}

int main(void)
{
    // This code is for the STM32F7 Discovery board (LED on PI1)
    #if defined(STM32F767xx)
        // Enable the clock for GPIOI
        // The GPIOI peripheral is connected to the AHB1 bus.
        // The bit for GPIOI is 8 in the RCC_AHB1ENR register.
        // We set this bit to 1 to enable the clock.
        RCC->AHB1ENR |= (1 << 8);

        // Configure PI1 as a general-purpose output
        // The mode of the GPIO pin is configured in the MODER register.
        // Each pin has 2 bits in this register.
        // 00: Input (reset state)
        // 01: General purpose output mode
        // 10: Alternate function mode
        // 11: Analog mode
        // We want to set PI1 to output mode, so we need to set bits 3:2 to 01.
        GPIOI->MODER |= (1 << 2);

        while (1)
        {
            // Toggle the LED
            // The ODR (Output Data Register) is used to write data to the GPIO pins.
            // Each bit in this register corresponds to a pin.
            // We can toggle the LED by XORing the corresponding bit in the ODR.
            GPIOI->ODR ^= (1 << 1);

            // Delay
            for (volatile int i = 0; i < 1000000; i++);
        }
    #endif

    // This code is for the Bluepill board (LED on PC13)
    #if defined(STM32F103xB)
        // Enable the clock for GPIOC
        // The GPIOC peripheral is connected to the APB2 bus.
        // The bit for GPIOC is 4 in the RCC_APB2ENR register.
        RCC->APB2ENR |= (1 << 4);

        // Configure PC13 as a general-purpose output
        // In the STM32F1 series, the configuration is done in the CRH (for pins 8-15) or CRL (for pins 0-7) registers.
        // Each pin has 4 bits in these registers.
        // We need to configure PC13, so we use the CRH register.
        // The bits for PC13 are 23:20.
        // We set them to 0011 for general-purpose output push-pull, max speed 50MHz.
        GPIOC->CRH &= ~(0b1111 << 20); // Clear the bits for PC13
        GPIOC->CRH |= (0b0011 << 20);  // Set the bits for PC13

        while (1)
        {
            // Toggle the LED
            GPIOC->ODR ^= (1 << 13);

            // Delay
            for (volatile int i = 0; i < 100000; i++);
        }
    #endif
}
""
