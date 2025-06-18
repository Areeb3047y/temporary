# C Programming Refresher

Welcome to our C language refresher! C is a powerful language. We use it to talk to the "brain" of our board, the microcontroller. Let's review some important ideas in C.

## Data Types

*   **Integer Types:** `char`, `short`, `int`, `long`, `long long`
*   **Unsigned Integer Types:** `unsigned char`, `unsigned short`, `unsigned int`, `unsigned long`, `unsigned long long`
*   **Floating-Point Types:** `float`, `double`, `long double`

## Variables

Variables are used to store data. In C, you must declare a variable before using it.

```c
int my_variable = 10;
```

## Operators

*   **Arithmetic Operators:** `+`, `-`, `*`, `/`, `%`
*   **Bitwise Operators:** `&` (AND), `|` (OR), `^` (XOR), `~` (NOT), `<<` (left shift), `>>` (right shift)
*   **Logical Operators:** `&&` (logical AND), `||` (logical OR), `!` (logical NOT)

## Control Structures

*   **`if-else` statements:**

```c
if (condition) {
    // code to execute if condition is true
} else {
    // code to execute if condition is false
}
```

*   **`for` loops:**

```c
for (int i = 0; i < 10; i++) {
    // code to execute 10 times
}
```

*   **`while` loops:**

```c
while (condition) {
    // code to execute as long as condition is true
}
```

## Functions

Functions are blocks of code that perform a specific task.

```c
int add(int a, int b) {
    return a + b;
}
```

## Pointers

Pointers are variables that store the memory address of another variable.

```c
int my_variable = 10;
int *my_pointer = &my_variable;
```

## Structures

Structures are used to group related data together.

```c
struct Point {
    int x;
    int y;
};

struct Point p1 = {10, 20};
```

## Bit Manipulation: The Art of Flipping Switches

Inside the microcontroller, there are thousands of tiny switches, called **bits**. A bit can be ON (1) or OFF (0). To make the microcontroller do anything, we need to flip these switches. This is called **bit manipulation**.

Let's learn some tricks to flip these switches.

### Setting a Bit (Turning a switch ON)

We use the `|` (OR) operator. `(1 << N)` creates a number with only the Nth bit as 1.

*Example:* We want to turn ON the 3rd switch (bit 2).
`REGISTER |= (1 << 2);`  // This turns ON the 3rd switch, and leaves others as they were.

### Clearing a Bit (Turning a switch OFF)

We use the `&` (AND) and `~` (NOT) operators. `~(1 << N)` creates a number with only the Nth bit as 0.

*Example:* We want to turn OFF the 5th switch (bit 4).
`REGISTER &= ~(1 << 4);` // This turns OFF the 5th switch, and leaves others as they were.

### Toggling a Bit (Flipping a switch)

If the switch is ON, it becomes OFF. If it's OFF, it becomes ON. We use the `^` (XOR) operator.

*Example:* We want to flip the 1st switch (bit 0).
`REGISTER ^= (1 << 0);` // This flips the 1st switch.

### Checking a Bit (Is the switch ON?)

We use the `&` (AND) operator to check the state of a switch.

*Example:* We want to check if the 7th switch (bit 6) is ON.
`if (REGISTER & (1 << 6)) { ... }` // The code inside the if() will run only if the 7th switch is ON.

## Volatile Keyword: "This Can Change!"

Sometimes, a value in memory can change unexpectedly. For example, a register's value can be changed by the hardware.

The `volatile` keyword is a message to the compiler. It says: "Hey compiler, be careful! This variable can change at any time. Don't try to be too smart and optimize it."

We use `volatile` when we declare a pointer to a register. This makes sure our code always works correctly.

*Example:*
`volatile uint32_t *my_register = (uint32_t *)0x40020000;`
