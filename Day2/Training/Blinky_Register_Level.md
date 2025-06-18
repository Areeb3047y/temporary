# Blinky with Register-Level Programming

Welcome to the expert level! Now, we will talk to the microcontroller in its own language. We will not use the HAL (the translator). We will directly control the hardware by writing to **registers**.

## What are Registers?

Think of the microcontroller as a big machine with many control panels. Each panel has switches and lights.
*   A **register** is like one of these control panels.
*   The **bits** in the register are the switches (0 or 1).

To make the machine work, we need to flip the right switches on the right panels.

## The Reference Manual: Our Map

How do we know which switch does what? We use the **Reference Manual**. This is a big book from the company that made the microcontroller (STMicroelectronics). It is the complete guide to all the registers. It is our map.

For our Blinky project, we need to do two things:
1.  Give power to the GPIO section.
2.  Set the GPIO pin as an output.

Let's see how to do this.

### 1. Setting up the Clock (Giving Power)

The microcontroller has many parts (GPIO, UART, I2C, etc.). To save power, they are all OFF by default. We need to give power to the part we want to use. This is called **enabling the clock**.

*   **Find the Register:** We look in the Reference Manual. We find the `RCC` (Reset and Clock Control) section. Inside it, we find the `RCC_AHB1ENR` register. This register is the power switch for many GPIO sections.
*   **Find the Bit:** We see that `GPIOI` (the section with our LED) is controlled by bit number 8.
*   **Write the Code:** To turn it ON, we set bit 8 to 1.
    ```c
    // For STM32F7 Discovery (LED on Port I)
    RCC->AHB1ENR |= (1 << 8); // Turn on power for GPIOI
    ```

### 2. Configuring the GPIO Pin (Setting the Direction)

Now that GPIOI has power, we need to tell pin number 1 that it will be an **output** pin. It will send signals out (to the LED).

*   **Find the Register:** We look in the Reference Manual for the `GPIO` section. We find the `GPIOx_MODER` (Mode Register). This register sets the mode for each pin (input, output, etc.).
*   **Find the Bit:** For each pin, there are 2 bits in this register. For pin 1, we need to control bits 3 and 2. To make it an output, we need to set these bits to `01`.
*   **Write the Code:**
    ```c
    // Set pin 1 of GPIOI to output mode
    GPIOI->MODER |= (1 << 2);
    ```
    (This sets bit 2 to 1 and leaves bit 3 as 0, so we get `01`).

### 3. Blinking the LED (Controlling the Output)

Finally, to turn the LED on or off, we write to the `GPIOx_ODR` (Output Data Register).

*   **Find the Register:** The `ODR` register directly controls the pins. If we write a 1 to a bit, the pin goes HIGH (voltage ON). If we write a 0, it goes LOW (voltage OFF).
*   **Find the Bit:** Our LED is on pin 1. So we need to control bit 1 of the `ODR`.
*   **Write the Code:** We can **toggle** the bit using the XOR `^` operator. This will flip the LED state in a loop.
    ```c
    // Toggle pin 1 of GPIOI
    GPIOI->ODR ^= (1 << 1);
    ```

By using registers, we have full control and a deep understanding of the hardware. You are now programming like a professional!
