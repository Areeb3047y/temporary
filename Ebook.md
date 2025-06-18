# Embedded Systems Workshop: A Beginner's Guide

Welcome, students! This book is your guide for our 3-day workshop. We will learn about embedded systems. Think of an embedded system as a small computer inside a machine, like the one in a microwave or a washing machine. Our goal is to learn how to program a special chip, the "brain" of these systems, called a microcontroller.

We will use the STM32F7 Discovery or Bluepill board. These boards have an STM32 microcontroller. We will write code in the C language to make it do things, like blinking a light or talking to other devices.

Don't worry if things seem new or difficult. We will go step-by-step, using simple words and many examples. Let's start our journey!

## Day 1: The Tools for Our Workshop

Today, we will get our tools ready. We need two main tools: a way to save our work (Git/GitHub) and a programming language (C).

### What is GitHub? And Why Do We Need It?

Imagine you are drawing a picture. You make a mistake, but you have already saved the file. You cannot go back. This is a problem.

Or, imagine you and your friend are working on the same drawing. You both make changes. It can get very confusing.

GitHub is like a magic time machine for our code.
*   It saves every version of our work.
*   If we make a mistake, we can go back to an older version.
*   It helps us work together without confusion.

In our first lesson, we will learn how to use this "time machine".

[Let's learn about GitHub](./Day1/Training/GitHub_Basics.md)

### Why Do We Use the C Language?

There are many programming languages, like Python or Java. But for embedded systems, C is very special. Why?

*   **It's Fast and Efficient:** C code runs very fast and uses very little memory. This is important for small microcontrollers.
*   **It's Close to the Hardware:** C allows us to talk almost directly to the parts of the microcontroller. Think of it like knowing the secret language of the machine.

We will quickly review the C language, focusing on the parts we need for our workshop.

[Let's refresh our C knowledge](./Day1/Training/C_Refresher.md)

### Lab 1: Let's Practice with GitHub

Now, let's use our new "time machine". In this lab, you will practice the basic commands of Git.

[Time for our first lab](./Day1/Labs/Lab1_Git_Practice/README.md)

## Day 2: Making Our Microcontroller Work

Today, we will bring our microcontroller to life! We will make an LED (a small light) on our board blink.

### How a Microcontroller Wakes Up

What happens when you give power to the microcontroller? It's like a person waking up and getting ready for the day.

1.  **Reset:** The microcontroller wakes up. It starts from a special place in its memory, called the "Reset Handler".
2.  **System Initialization:** It then runs a special function, `SystemInit`. This function sets up the "clock". The clock is like the heartbeat of the microcontroller. It decides how fast the microcontroller works.
3.  **Jump to `main`:** After setting up, it calls our `main()` function. This is where our own code begins!

This whole process is written in a special file called the **startup file** (`.s` extension). We will look at this file.

### Blinky with HAL: The Easy Way

"HAL" means Hardware Abstraction Layer. Think of HAL as a helpful translator.

*   **You (The Programmer):** You want to turn on an LED. You say a simple command in English: "LED, please turn on."
*   **HAL (The Translator):** The HAL takes your simple command and translates it into the complex, secret language that the microcontroller understands.

Using HAL is easy and fast. We will first blink our LED using the HAL.

[Let's blink an LED with HAL](./Day2/Training/Blinky_HAL.md)

[Lab: Blinky with HAL](./Day2/Labs/Blinky_HAL/README.md)

### Blinky with Registers: The Professional Way

The HAL is easy, but it hides many details. To become experts, we need to learn the microcontroller's secret language ourselves. This language involves "registers".

What are registers? Think of the microcontroller as a big control room with many switches and buttons. Each switch or button is a **register**. To make something happen, we need to turn the right switches ON or OFF.

To know which switch does what, we need the **Reference Manual**. This book is the user guide for our microcontroller. It tells us about every register.

In this part, we will blink the LED by directly controlling the registers. It's more work, but you will understand everything much better.

[Let's become experts and use registers](./Day2/Training/Blinky_Register_Level.md)

[Lab: Blinky with Registers](./Day2/Labs/Blinky_Register_Level/README.md)

## Day 3: Teaching Our Microcontroller to Talk

Today, we will teach our microcontroller how to talk to other devices. We will learn two languages: UART and I2C.

### UART: A Simple Conversation

UART means Universal Asynchronous Receiver-Transmitter. It's a way for two devices to talk to each other.

Imagine two people talking on the phone.
*   One person talks, the other listens.
*   UART uses two wires: one for sending data (TX - Transmit) and one for receiving data (RX - Receive).

How do they understand each other without getting confused? They follow rules.
*   **Start Bit:** One device says "I am starting to talk now." This is the Start Bit.
*   **Data Bits:** Then it sends the message, bit by bit.
*   **Stop Bit:** Finally, it says "I have finished talking." This is the Stop Bit.
*   **Baud Rate:** This is the speed of the conversation. Both devices must agree to talk at the same speed.

We will learn how to use UART to send "Hello, World!" from our board to the computer.

[Let's learn the UART language](./Day3/Training/UART.md)

[Lab: Talking with UART](./Day3/Labs/UART/README.md)

### I2C: A Classroom Conversation

I2C means Inter-Integrated Circuit. It's another way for devices to talk. But I2C is special because many devices can be on the same "bus" (the same wires).

Imagine a teacher (the **Master**) in a classroom with many students (the **Slaves**).
*   The teacher wants to talk to one student. The teacher calls the student's name. In I2C, this is the **Address**. Every slave device has a unique address.
*   They use two wires for the conversation:
    *   **SDA (Serial Data):** This is for the actual message, the words.
    *   **SCL (Serial Clock):** This is for the rhythm of the conversation. The master creates a clock signal to keep everyone in sync.

I2C is very useful for connecting sensors, memory chips, and other devices to our microcontroller.

[Let's learn the I2C language](./Day3/Training/I2C.md)

[Lab: Talking with I2C](./Day3/Labs/I2C/README.md)

### Bonus: Why Timers are Better for Blinking

Remember how we made the LED blink on Day 2? We used a `for` loop to create a delay. This works, but it has a big problem: while the microcontroller is counting in the loop, it cannot do anything else. It's like a person counting sheep to fall asleep - they can't have a conversation at the same time.

A **hardware timer** is a much smarter way to create a delay. It's like setting an alarm clock.

*   You tell the timer: "Please wake me up after 1 second."
*   The timer starts counting in the background.
*   Meanwhile, the main part of your program (the `main` loop) is free to do other things.
*   When 1 second has passed, the timer "rings the bell". This is called an **interrupt**.
*   When the interrupt happens, the microcontroller stops what it's doing, quickly does a small task (like toggling the LED), and then goes back to its main work.

This way, the microcontroller is much more efficient. It's not stuck in a useless counting loop.

[Lab: Blinking with a Timer](./Day3/Labs/Timer_Blinky/README.md)
