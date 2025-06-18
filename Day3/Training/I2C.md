# I2C Communication: A Classroom Talk

Welcome! Let's learn another language for our microcontroller, called **I2C**. This language is very useful because it allows our microcontroller to talk to many devices at the same time, using only two wires!

## What is I2C?

Imagine a classroom.
*   There is one **Teacher**.
*   There are many **Students**.

The Teacher can talk to any student. The students usually only talk when the teacher asks them to.

In I2C, it is the same.
*   There is one **Master** device (the Teacher). Our microcontroller will be the master.
*   There can be many **Slave** devices (the Students). These can be sensors, memory chips, etc.

## The Two Wires of I2C

The whole conversation in the classroom happens over just two wires:
*   **SCL (Serial Clock):** This is the **rhythm** of the conversation. The Master (the teacher) creates a clock signal on this wire. It's like the teacher clapping hands to keep everyone in sync. All data is sent and received on the beat of this clock.
*   **SDA (Serial Data):** This is the **voice** of the conversation. The actual data (the message) travels on this wire.

## How does the Master talk to one Slave?

The classroom is full of students. How does the teacher talk to only one student, for example, "Ali"? The teacher calls Ali's name.

In I2C, every slave device has a unique **7-bit address**. It's like a name.

The I2C conversation works like this:
1.  **START Condition:** The Master (teacher) shouts "Listen everyone, I am starting a new conversation!". This is the **START** condition. All slaves on the bus become alert.
2.  **Address Frame:** The Master then sends the 7-bit **address** of the slave it wants to talk to. It also sends one more bit (the R/W bit) to tell the slave if it wants to **Write** (send data to the slave) or **Read** (get data from the slave).
3.  **ACK/NACK:** The slave with that address responds with an "Acknowledge" (**ACK**) bit. It's like the student "Ali" raising his hand and saying "Yes, teacher, I am here!". All other slaves ignore the rest of the conversation.
4.  **Data Frames:** Now, the Master and the chosen Slave can exchange data, byte by byte. After each byte, the receiver gives an **ACK** to say "I got the byte, thank you!".
5.  **STOP Condition:** When the conversation is finished, the Master shouts "Okay, conversation over!". This is the **STOP** condition. The bus is now free for a new conversation.

![I2C Transaction](https://i.imgur.com/Y3Ea3s5.png)

I2C is a bit more complex than UART, but it is very powerful for building systems with many parts.

## Configuring I2C on the STM32

1.  **Enable the I2C clock:** Enable the clock for the I2C peripheral you want to use (e.g., `I2C1`, `I2C2`).
2.  **Configure the GPIO pins:** Configure the SDA and SCL pins for the I2C peripheral.
3.  **Configure the I2C parameters:** Set the clock speed and addressing mode.
4.  **Enable the I2C:** Enable the I2C peripheral.

## Sending and Receiving Data

*   **Sending Data:** To send data, write the data to the `TXDR` (Transmit Data Register) of the I2C peripheral.
*   **Receiving Data:** To receive data, read the data from the `RXDR` (Receive Data Register) of the I2C peripheral.

## Example Code (Register-Level)

```c
// Configure and enable I2C1
// ...

// Send a byte to a slave device
I2C1->CR2 = (SLAVE_ADDRESS << 1) | (1 << 16); // Set slave address and number of bytes
I2C1->CR2 |= (1 << 13); // Generate start condition
while (!(I2C1->ISR & (1 << 1))); // Wait for TXIS flag
I2C1->TXDR = 0x55; // Send data
while (!(I2C1->ISR & (1 << 6))); // Wait for TC flag
I2C1->CR2 |= (1 << 14); // Generate stop condition
```
