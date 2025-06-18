<!-- 
theme: uncover
class:
 - lead
 - invert
-->

# **Embedded Systems Workshop**
## A 3-Day Journey into the World of Microcontrollers

---

# **Welcome!**

*   Welcome, students, to our 3-day workshop!
*   We will learn about **embedded systems**.
*   Think of an embedded system as a small computer, a "brain," inside a machine like a microwave or a car.
*   Our goal is to learn how to program the "brain" - the **microcontroller**.

---

# **Our Workshop Tools**

*   **Hardware:**
    *   STM32F4 Discovery Board **OR**
    *   STM32 Bluepill Board
*   **Software:**
    *   STM32CubeIDE (Our development environment)
    *   The C Programming Language
    *   Git & GitHub (Our code "time machine")

---

<!-- 
class:
 - lead
 - invert
-->

# **Day 1: The Tools for Our Workshop**

---

# **Module 1: Git & GitHub**

## Your Code's Magic Time Machine

---

# **What is the Problem?**

*   Imagine you are writing a story.
*   You write Chapter 1. You save it.
*   You write Chapter 2. You save it, and the old Chapter 1 is gone.
*   Now, you want to see the old Chapter 1. But you can't. It is lost.
*   This is a big problem for programmers.

---

# **Git & GitHub is the Solution!**

*   **Git** is a tool on your computer. It's a "save" button with a memory. When you save, it remembers the old version. You can go back in time to any saved version.

*   **GitHub** is a website. It's like cloud storage for your Git projects. You can upload your saved versions to GitHub.

---

# **Why use Git & GitHub?**

1.  **Backup:** Your code is safe, even if your computer breaks.
2.  **Time Travel:** You can go back to any previous version of your code.
3.  **Teamwork:** You can share your code with friends and work together easily.

---

# **Basic Git Commands (Simple Words)**

*   `git clone`: **Copy** a project from GitHub to your computer.
*   `git add`: **Choose** which files you want to save in the next version.
*   `git commit`: **Save** the chosen files. You must write a message to remember what you changed.
*   `git push`: **Upload** your saved changes from your computer to GitHub.
*   `git pull`: **Download** the latest changes from GitHub to your computer.

---

# **Lab 1: Git Practice**

## Let's use our new "time machine"!

---

## **Lab 1: Objectives**

*   Clone a repository from GitHub.
*   Create a new branch to work on.
*   Create a new file and make changes.
*   Commit (save) and push (upload) your changes.
*   Create a pull request (ask to merge your changes).

---

## **Lab 1: Instructions**

1.  **Clone the workshop repository:**
    ```bash
    git clone <repository_url>
    ```
2.  **Create a new branch:**
    ```bash
    git checkout -b my-first-branch
    ```
3.  **Create a new file:**
    *   Create a file named `hello.txt`.
    *   Write "Hello, World!" inside it.
4.  **Add and commit the file:**
    ```bash
    git add hello.txt
    git commit -m "Add hello.txt"
    ```
5.  **Push the changes:**
    ```bash
    git push origin my-first-branch
    ```
6.  **Create a pull request on GitHub.**

---

# **Module 2: The C Language**

## The Language of Embedded Systems

---

# **Why Do We Use the C Language?**

*   **It's Fast and Efficient:** C code runs very fast and uses very little memory. This is very important for small microcontrollers.
*   **It's Close to the Hardware:** C allows us to talk almost directly to the parts of the microcontroller. It's like knowing the secret language of the machine.

---

# **Bit Manipulation**

## The Art of Flipping Switches

---

## **The Idea of Bits**

*   Inside the microcontroller, there are thousands of tiny switches, called **bits**.
*   A bit can be **ON (1)** or **OFF (0)**.
*   To make the microcontroller do anything, we need to flip these switches. This is called **bit manipulation**.

![Switches](https://i.imgur.com/OaJ4d6u.png)

---

## **Setting a Bit (Turn a switch ON)**

*   We use the `|` (OR) operator.
*   `(1 << n)` creates a number that has only the nth bit set to 1.
*   **Example:** We want to turn ON the 3rd switch (bit index 2).
    ```c
    // Before: num = 0b00000101 (5)
    num |= (1 << 2); 
    // After:  num = 0b00001101 (13)
    ```
*   This turns ON the target bit and leaves all other bits unchanged.

---

## **Clearing a Bit (Turn a switch OFF)**

*   We use the `&` (AND) and `~` (NOT) operators.
*   `~(1 << n)` creates a number where only the nth bit is 0.
*   **Example:** We want to turn OFF the 2nd switch (bit index 1).
    ```c
    // Before: num = 0b00001110 (14)
    num &= ~(1 << 1);
    // After:  num = 0b00001100 (12)
    ```
*   This turns OFF the target bit and leaves all other bits unchanged.

---

## **Toggling a Bit (Flip a switch)**

*   If the switch is ON, it becomes OFF. If it's OFF, it becomes ON.
*   We use the `^` (XOR) operator.
*   **Example:** We want to flip the 1st switch (bit index 0).
    ```c
    // Before: num = 0b00001011 (11)
    num ^= (1 << 0);
    // After:  num = 0b00001010 (10)
    ```
*   This is perfect for making an LED blink!

---

## **Checking a Bit (Is the switch ON?)**

*   We use the `&` (AND) operator to check the state of a single bit.
*   **Example:** We want to check if the 4th switch (bit index 3) is ON.
    ```c
    unsigned char num = 0b00011000; // 24
    if (num & (1 << 3)) {
        // This code will run because the bit is ON.
    }
    ```
*   This is very useful for checking status flags from hardware.

---

## **The `volatile` Keyword**

*   **The Problem:** The compiler is smart and likes to optimize code. It might assume a variable's value doesn't change if it doesn't see your code changing it.
*   But in embedded systems, the **hardware** can change a variable's value (e.g., a status register).
*   **The Solution:** The `volatile` keyword is a message to the compiler. It says: "Hey compiler, be careful! This variable can change at any time. Do not optimize it."
*   We **always** use `volatile` when we create a pointer to a hardware register.
    ```c
    volatile uint32_t *my_register = (uint32_t *)0x40020000;
    ```

---

<!-- 
class:
 - lead
 - invert
-->

# **Day 2: Making Our Microcontroller Work**

---

# **Module 3: The "Blinky" Project**

## The "Hello, World!" of Embedded Systems

---

# **How a Microcontroller Wakes Up**

1.  **Reset:** The microcontroller wakes up when power is applied. It starts executing code from a specific memory address called the "Reset Handler".
2.  **Startup Code:** This is a small piece of code (usually in Assembly language) that runs first. It prepares the system.
3.  **System Initialization:** The startup code calls a function, often `SystemInit`, which sets up the **system clock**. The clock is like the heartbeat of the microcontroller; it controls how fast it runs.
4.  **Jump to `main()`:** After setup, the startup code calls our `main()` function. This is where our own C code begins!

---

# **Part 1: Blinky with HAL**

## The Easy Way

---

## **What is HAL?**

*   HAL means **H**ardware **A**bstraction **L**ayer.
*   **Analogy:** Think of HAL as a helpful translator.
    *   **You (The Programmer):** You say a simple command: "LED, please turn on."
    *   **HAL (The Translator):** The HAL takes your simple command and translates it into the complex, secret language that the microcontroller's hardware understands.
*   Using HAL is easy and fast for beginners.

---

## **Steps in STM32CubeIDE**

1.  Create a New STM32 Project.
2.  Select your board.
3.  Use the graphical tool to configure the system.
    *   Enable the external clock (HSE).
    *   Configure the system clock speed.
    *   Set the LED pin to be a `GPIO_Output`.
4.  Generate the code.
5.  Write your application logic in `main.c`.

---

## **Lab 2: Blinky with HAL**

## Let's blink an LED the easy way!

---

## **Lab 2: Objectives**

*   Create a new project in STM32CubeIDE.
*   Configure the clock and GPIO pin using the graphical interface.
*   Write the C code to blink the LED using HAL functions.
*   Build and run the project on your board.

---

## **Lab 2: Code Walkthrough**

*   We will look at the `main.c` file generated by STM32CubeIDE.
*   The important part is the `while(1)` loop.

```c
/* Inside main() */

while (1)
{
  /* This function toggles the state of the pin.
   * If it's ON, it becomes OFF. If OFF, it becomes ON.
   * For STM32F4 Discovery, the LED is on GPIOI, Pin 1.
   * For Bluepill, the LED is on GPIOC, Pin 13.
   */
  HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1); 

  /* This function creates a delay.
   * HAL_Delay(1000) waits for 1000 milliseconds (1 second).
   */
  HAL_Delay(1000);
}
```

---

# **Part 2: Blinky with Registers**

## The Professional Way

---

## **Why Use Registers?**

*   The HAL is easy, but it hides the details. It's a "black box".
*   To become experts, we need to learn the microcontroller's secret language ourselves. This language involves **registers**.
*   **Benefits:**
    *   You understand exactly what the hardware is doing.
    *   Your code can be smaller and faster.
    *   You have complete control.

---

## **What are Registers?**

*   **Analogy:** Think of the microcontroller as a big control room with many control panels.
*   Each control panel is a **Register**. A register is just a memory location inside the MCU.
*   The switches and lights on the panel are the **Bits** of the register.
*   To make the machine work, we need to flip the right switches (bits) on the right panels (registers).

---

## **The Reference Manual: Our Map**

*   **Question:** How do we know which switch does what?
*   **Answer:** We use the **Reference Manual**.
*   This is a big PDF book from the company that made the microcontroller (STMicroelectronics).
*   It is the complete guide to all the registers. It is our map to the control room.

![Reference Manual](https://i.imgur.com/wN5wZ6k.png)

---

## **Blinking with Registers: 3 Steps**

1.  **Enable Clock (Give Power)**
2.  **Set Pin Mode (Set Direction)**
3.  **Toggle Output (Flip the Switch)**

---

## **Step 1: Enable Clock**

*   The microcontroller has many parts (GPIO, UART, etc.). To save power, they are all OFF by default. We must give power to the part we want to use.
*   **Find the Register:** In the Reference Manual, we find the `RCC` (Reset and Clock Control) section. The `RCC_AHB1ENR` register is the power switch for many GPIO ports.
*   **Find the Bit:** We see that `GPIOI` (the port with our LED) is controlled by **bit 8**.
*   **Write the Code:**
    ```c
    // RCC is a pointer to the RCC registers' base address.
    // AHB1ENR is the specific register we want.
    // We use the OR operator to set bit 8 to 1.
    RCC->AHB1ENR |= (1 << 8); // Turn on power for GPIOI
    ```

---

## **Step 2: Configure Pin Mode**

*   Now that GPIO Port I has power, we must tell pin 1 that it will be an **output** pin.
*   **Find the Register:** In the Reference Manual, we find the `GPIO` section. The `GPIOx_MODER` (Mode Register) sets the mode for each pin.
*   **Find the Bits:** For each pin, there are 2 bits in this register. For pin 1, we need to control bits 3 and 2. To set it to output, we need the pattern `01`.
*   **Write the Code:**
    ```c
    // We want to set bit 2 to 1 and leave bit 3 as 0.
    // This gives us the '01' pattern for output mode.
    GPIOI->MODER |= (1 << 2);
    ```

---

## **Step 3: Toggle the LED**

*   Finally, to turn the LED on or off, we write to the `GPIOx_ODR` (Output Data Register).
*   **Find the Register:** The `ODR` directly controls the output state of the pins. Writing a 1 to a bit makes the pin HIGH (voltage ON). Writing a 0 makes it LOW (voltage OFF).
*   **Find the Bit:** Our LED is on pin 1. So we need to control **bit 1** of the `ODR`.
*   **Write the Code:** We use the XOR `^` operator to toggle the bit.
    ```c
    // This flips the state of bit 1 in the ODR register.
    GPIOI->ODR ^= (1 << 1);
    ```

---

## **Lab 3: Blinky with Registers**

## Let's program like the pros!

---

## **Lab 3: Objectives**

*   Create a new, empty STM32 project.
*   Write C code to blink the LED by directly manipulating register values.
*   Use the Reference Manual to understand the registers being used.
*   Build and run the project.

---

## **Lab 3: Code Walkthrough**

```c
#include "stm32f4xx.h"

int main(void)
{
    // Step 1: Enable the clock for GPIOI
    // The bit for GPIOI is 8 in the RCC_AHB1ENR register.
    RCC->AHB1ENR |= (1 << 8);

    // Step 2: Configure PI1 as a general-purpose output
    // Set bits 3:2 to 01 in the GPIOI_MODER register.
    GPIOI->MODER |= (1 << 2);

    while (1)
    {
        // Step 3: Toggle the LED
        // Toggle bit 1 in the GPIOI_ODR register.
        GPIOI->ODR ^= (1 << 1);

        // A simple software delay
        for (volatile int i = 0; i < 1000000; i++);
    }
}
```

---

<!-- 
class:
 - lead
 - invert
-->

# **Day 3: Teaching Our MCU to Talk**

---

# **Module 4: UART Communication**

## A Simple, One-to-One Chat

---

## **What is UART?**

*   **U**niversal **A**synchronous **R**eceiver-**T**ransmitter.
*   **Analogy:** Talking to a friend using two tin cans and a string. One string is for you to talk, one is for them to talk back.
*   It's a **serial** communication protocol. Bits are sent one by one in a series.
*   It uses two wires:
    *   **TX (Transmit):** The microcontroller uses this wire to **send** messages.
    *   **RX (Receive):** The microcontroller uses this wire to **get** messages.

---

## **The Rules of the UART Chat**

1.  **The Speed (Baud Rate):** Both devices must agree on how fast they will talk (e.g., 9600 bits per second). If the speeds are different, the message will be nonsense.
2.  **The Structure of a Message (Frame):**
    *   **Start Bit:** The sender sends a **Start Bit** (always a 0) to say "Hello, I'm starting to talk!".
    *   **Data Bits:** The sender sends the actual data (usually 8 bits).
    *   **Stop Bit:** The sender sends a **Stop Bit** (always a 1) to say "I'm done talking for now."

---

## **A UART Frame**

![UART Frame](https://i.imgur.com/7g5wZ3o.png)

---

## **Why "Asynchronous"?**

*   The "A" in UART stands for **Asynchronous**, which means "no shared clock".
*   The sender and receiver do not share a clock signal to synchronize.
*   Instead, the receiver listens for the **Start Bit**. When it sees one, it starts its own internal timer to read the following data bits at the correct time, based on the agreed **Baud Rate**.
*   This makes UART simple, only needing two wires.

---

## **Lab 4: UART Communication**

## Let's send "Hello, World!" to our computer.

---

## **Lab 4: Objectives**

*   Configure the UART peripheral and its GPIO pins using registers.
*   Set the correct baud rate.
*   Write C functions to send and receive characters over UART.
*   Use a terminal program on the computer to see the messages.

---

## **Lab 4: Code Walkthrough**

```c
void UART_SendChar(char c)
{
    // To send data, we write it to the Transmit Data Register (TDR).
    // But first, we must wait for the register to be empty.
    // We check the TXE (Transmit data register Empty) flag in the ISR (Interrupt and Status Register).
    // The loop will wait here until TXE becomes 1.
    while (!(USART1->ISR & (1 << 7)));

    // Now that the register is empty, we can send our character.
    USART1->TDR = c;
}

char UART_ReceiveChar(void)
{
    // To receive data, we read it from the Receive Data Register (RDR).
    // But first, we must wait for data to arrive.
    // We check the RXNE (Read data register Not Empty) flag in the ISR.
    // The loop will wait here until RXNE becomes 1.
    while (!(USART1->ISR & (1 << 5)));

    // Now that there is data, we can read and return it.
    return USART1->RDR;
}
```

---

# **Module 5: I2C Communication**

## A Group Chat for Multiple Devices

---

## **What is I2C?**

*   **I**nter-**I**ntegrated **C**ircuit.
*   It's a protocol that allows one master device to talk to many slave devices using only two wires.
*   **Analogy:** A classroom.
    *   There is one **Teacher (Master)**. Our microcontroller.
    *   There are many **Students (Slaves)**. These can be sensors, memory chips, etc.

---

## **The Two Wires of I2C**

*   The whole conversation happens over just two wires:
    *   **SCL (Serial Clock):** This is the **rhythm** of the conversation. The Master creates a clock signal on this wire, like a teacher clapping hands to keep everyone in sync.
    *   **SDA (Serial Data):** This is the **voice** of the conversation. The actual data travels on this wire.
*   This is a **Synchronous** protocol because of the shared SCL line.

---

## **How I2C Works: Addressing**

*   How does the teacher talk to only one student? By calling their name.
*   In I2C, every slave device has a unique **7-bit address**. It's like a name.
*   When the master wants to talk to a slave, it first sends the slave's address onto the data bus.
*   Only the slave with the matching address will respond. All other slaves will ignore the conversation.

---

## **An I2C Transaction**

1.  **START Condition:** The Master begins the conversation.
2.  **Address Frame:** The Master sends the 7-bit **address** of the slave, plus a Read/Write bit.
3.  **ACK:** The addressed slave responds with an "Acknowledge" (**ACK**) bit, saying "I'm here!".
4.  **Data Frames:** The Master and Slave exchange data bytes. The receiver sends an **ACK** after each byte.
5.  **STOP Condition:** The Master ends the conversation.

---

## **An I2C Transaction (Diagram)**

![I2C Transaction](https://i.imgur.com/Y3Ea3s5.png)

---

## **Lab 5: I2C Communication**

## Let's talk to an external sensor or chip.

---

## **Lab 5: Objectives**

*   Connect an I2C slave device to your STM32 board.
*   Configure the I2C peripheral and its GPIO pins using registers.
*   Write C functions to handle an I2C transaction (Start, Stop, Address, Write, Read).
*   Read data from the slave device.

---

## **Lab 5: Code Walkthrough**

```c
void I2C_Start(void)
{
    // To generate a START condition, we set the START bit
    // in the I2C Control Register 2 (CR2).
    I2C1->CR2 |= (1 << 13); 
    // Then we must wait for the hardware to confirm it's done.
    // This is more complex than UART and involves checking status flags.
}

void I2C_Write(uint8_t data)
{
    // We wait for the Transmit buffer to be empty (TXIS flag).
    while (!(I2C1->ISR & (1 << 1)));
    // Then we write our data to the Transmit Data Register (TXDR).
    I2C1->TXDR = data;
}
```
*Note: Full I2C register-level code is complex and requires careful reading of the reference manual for the status flags.*

---

<!-- 
class:
 - lead
 - invert
-->

# **Workshop Summary & Thank You!**

---

# **Congratulations!**

**In these 3 days, you have learned:**

*   How to manage your code with **Git and GitHub**.
*   The fundamentals of **C programming** for embedded systems, especially **bit manipulation**.
*   How a microcontroller works from the inside.
*   How to control hardware using both high-level **HAL** and low-level **Registers**.
*   How to communicate with the outside world using **UART** and **I2C**.

---

# **Thank You!**

## Questions?
