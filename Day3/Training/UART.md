# UART Communication: A Simple Chat

Hello! Today we will learn how our microcontroller can talk to our computer. It uses a language called **UART**.

## What is UART?

Imagine you are talking to your friend using two tin cans and a string.
*   You have one string to talk through.
*   Your friend has one string to talk back.

UART is very similar. It uses two wires:
*   **TX (Transmit):** The microcontroller uses this wire to **send** messages.
*   **RX (Receive):** The microcontroller uses this wire to **get** messages.

This is a **serial** communication. It means the data (the bits) are sent one by one in a series, like people waiting in a line.

## The Rules of the UART Chat

For a good chat, you need rules. UART has rules too.

1.  **The Speed (Baud Rate):** Both devices must agree on how fast they will talk. This speed is called the **Baud Rate** (e.g., 9600 bits per second). If the speeds are different, the message will be nonsense.

2.  **The Structure of a Message:** Each small piece of data sent is called a **frame**. A frame has a clear structure:
    *   **Start Bit:** The sender sends a **Start Bit**. This is like saying "Hello, I'm starting to talk!". It is always a 0.
    *   **Data Bits:** After the start bit, the sender sends the actual data (usually 8 bits, which is 1 byte). This is your message.
    *   **Stop Bit:** After the data, the sender sends a **Stop Bit**. This is like saying "I'm done talking for now." It is always a 1.

![UART Frame](https://i.imgur.com/7g5wZ3o.png)

## Why "Asynchronous"?

You see the "A" in UART is for **Asynchronous**. It means "no clock".

What does this mean? The sender and receiver do not share a clock signal. The sender does not tell the receiver exactly when to read the bits.

Instead, the receiver listens for the **Start Bit**. When it sees a Start Bit, it starts its own internal timer to read the following data bits at the correct time, based on the agreed **Baud Rate**.

This makes UART simple. It only needs two wires.

In our lab, we will use UART to send "Hello, World!" from our board to a terminal on our computer.
