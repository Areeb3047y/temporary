"""#include "stm32f7xx.h" // For STM32F7 Discovery
// #include "stm32f1xx.h" // For Bluepill

#define SLAVE_ADDRESS 0x68 // Example address for a DS3231 RTC

void I2C_Init(void)
{
    // This code is for the STM32F7 Discovery board (I2C1 on PB8/PB9)
    #if defined(STM32F767xx)
        // Enable the clock for GPIOB and I2C1
        RCC->AHB1ENR |= (1 << 1);  // GPIOB
        RCC->APB1ENR |= (1 << 21); // I2C1

        // Configure PB8 (SCL) and PB9 (SDA) as alternate function open-drain
        GPIOB->MODER |= (0b10 << 16) | (0b10 << 18);
        GPIOB->OTYPER |= (1 << 8) | (1 << 9);
        GPIOB->AFR[1] |= (4 << 0) | (4 << 4); // AF4 for I2C1

        // Configure I2C1
        I2C1->CR1 &= ~(1 << 0); // Disable I2C1
        I2C1->TIMINGR = 0x40912732; // 100 kHz at 216 MHz
        I2C1->CR1 |= (1 << 0); // Enable I2C1
    #endif

    // This code is for the Bluepill board (I2C1 on PB6/PB7)
    #if defined(STM32F103xB)
        // Enable the clock for GPIOB and I2C1
        RCC->APB2ENR |= (1 << 3);  // GPIOB
        RCC->APB1ENR |= (1 << 21); // I2C1

        // Configure PB6 (SCL) and PB7 (SDA) as alternate function open-drain
        GPIOB->CRL &= ~(0b11111111 << 24);
        GPIOB->CRL |= (0b11111111 << 24);

        // Configure I2C1
        I2C1->CR1 &= ~(1 << 0); // Disable I2C1
        I2C1->CR2 |= 36; // 36 MHz
        I2C1->CCR = 180; // 100 kHz
        I2C1->TRISE = 37;
        I2C1->CR1 |= (1 << 0); // Enable I2C1
    #endif
}

void I2C_Start(void)
{
    I2C1->CR1 |= (1 << 8); // Generate start condition
    while (!(I2C1->SR1 & (1 << 0))); // Wait for start condition to be generated
}

void I2C_Stop(void)
{
    I2C1->CR1 |= (1 << 9); // Generate stop condition
}

void I2C_Address(uint8_t address)
{
    I2C1->DR = address;
    while (!(I2C1->SR1 & (1 << 1))); // Wait for address to be sent
    (void)I2C1->SR1;
    (void)I2C1->SR2;
}

void I2C_Write(uint8_t data)
{
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1 << 7))); // Wait for data to be transmitted
}

uint8_t I2C_Read(void)
{
    while (!(I2C1->SR1 & (1 << 6))); // Wait for data to be received
    return I2C1->DR;
}

int main(void)
{
    I2C_Init();
    I2C_Start();
    I2C_Address(SLAVE_ADDRESS << 1); // Write address
    I2C_Write(0x00); // Register address
    I2C_Stop();

    I2C_Start();
    I2C_Address((SLAVE_ADDRESS << 1) | 1); // Read address
    uint8_t seconds = I2C_Read();
    I2C_Stop();

    while (1)
    {
    }
}
""
