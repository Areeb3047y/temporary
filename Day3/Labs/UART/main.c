"""#include "stm32f7xx.h" // For STM32F7 Discovery
// #include "stm32f1xx.h" // For Bluepill

void UART_Init(void)
{
    // This code is for the STM32F7 Discovery board (USART1 on PA9/PA10)
    #if defined(STM32F767xx)
        // Enable the clock for GPIOA and USART1
        RCC->AHB1ENR |= (1 << 0);  // GPIOA
        RCC->APB2ENR |= (1 << 4);  // USART1

        // Configure PA9 (TX) and PA10 (RX) as alternate function
        GPIOA->MODER |= (0b10 << 18) | (0b10 << 20);
        GPIOA->AFR[1] |= (7 << 4) | (7 << 8); // AF7 for USART1

        // Configure USART1
        // Baud rate = 9600
        // APB2 clock = 108 MHz
        // BRR = 108,000,000 / 9600 = 11250
        USART1->BRR = 11250;
        USART1->CR1 |= (1 << 3) | (1 << 2) | (1 << 13); // TE, RE, UE
    #endif

    // This code is for the Bluepill board (USART1 on PA9/PA10)
    #if defined(STM32F103xB)
        // Enable the clock for GPIOA and USART1
        RCC->APB2ENR |= (1 << 2) | (1 << 14); // GPIOA and USART1

        // Configure PA9 (TX) as alternate function push-pull
        GPIOA->CRH &= ~(0b1111 << 4);
        GPIOA->CRH |= (0b1011 << 4);

        // Configure PA10 (RX) as input floating
        GPIOA->CRH &= ~(0b1111 << 8);
        GPIOA->CRH |= (0b0100 << 8);

        // Configure USART1
        // Baud rate = 9600
        // APB2 clock = 72 MHz
        // BRR = 72,000,000 / 9600 = 7500
        USART1->BRR = 7500;
        USART1->CR1 |= (1 << 3) | (1 << 2) | (1 << 13); // TE, RE, UE
    #endif
}

void UART_SendChar(char c)
{
    // Wait for the transmit data register to be empty
    while (!(USART1->ISR & (1 << 7)));
    // Send the character
    USART1->TDR = c;
}

char UART_ReceiveChar(void)
{
    // Wait for the receive data register to be not empty
    while (!(USART1->ISR & (1 << 5)));
    // Return the received character
    return USART1->RDR;
}

void UART_SendString(char *s)
{
    while (*s)
    {
        UART_SendChar(*s++);
    }
}

int main(void)
{
    UART_Init();
    UART_SendString("Hello, World!
");

    while (1)
    {
        char c = UART_ReceiveChar();
        UART_SendChar(c);
    }
}
""
