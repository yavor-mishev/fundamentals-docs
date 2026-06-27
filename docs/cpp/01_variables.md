# Variables and Data Types

We use variables to store data in our programs. When we create a variable it will be stored in one of two places: the **stack** or the **heap**, but we will dive deeper into these two later on. For now remember that variables occupy memory.
In C/C++ we are given some **primitive** data types. These primitive data types form the building blocks of any kind of data that we store in our program. Each of these types has a specific purpose, but as you will see in this part and furthur down the road, you dont necessarilly need to use them with that purpose in mind. The core difference between these data types is the size/amount of memory they occupy in your memory.


Each variable has the following characteristics:
- type: defines the kind of data the variable can hold (e.g., integer, floating-point, character, etc.).
- name / identifier: a unique name used to reference the variable in the code.
- address in memory: the location in memory where the variable's value is stored.
- value: the actual data stored in the variable.

### Declaring variables
To declare a variable in C/C++, we need to specify the data type followed by the variable identifier:
```cpp
int count; // integer variable named 'count'
```

### Defining variables
The definition of a variable consists of the declaration and the initialization:
```cpp
int count = 10; // integer value named 'count' initialized to 10
int positiveNumber = (number > 0);
double surface = 4.50 * 3;
```

Types are important in C++ because they determine what are the valid arithmetic operations that can be performed on the variable and what are the valid values that can be stored in it.

## Data Types

### Integer - 4 Bytes

```cpp
int variable = 8; // ~ -2b -> 2b
```

The range that this integer variable can handle derives directly from its size in memory. 4 Bytes are 32 bits, and with 32 bits we can represent 2^32 different values. Since integers can be both positive and negative, half of these values are used for negative numbers and half for positive numbers. This means that the range of a standard integer variable is from **-2,147,483,648 to 2,147,483,647**. Because the integer variable we declared up top is signed by default, it can contain both negative and positive values. For this to be possible one of 32 bits is used to represent the sign of the number (positive or negative). This leaves us with 31 bits to represent the actual value of the integer hence the range from -2,147,483,648 to 2,147,483,647 (2^31 = 2,147,483,648).

If we dont care for the negative values we can use an **unsigned integer**. This way all 32 bits are used to represent positive values only, which doubles the maximum value we can store in the variable.

```cpp
unsigned int variable = 8; // ~ 0 -> 4b
```

### Char - 1 Byte

Traditionally used to store single characters, the `char` data type in C++ is essentially a small integer type that occupies 1 byte (8 bits) of memory. This means it can represent 256 different values (2^8 = 256). The range of a signed `char` is typically from -128 to 127, while an unsigned `char` can hold values from 0 to 255.

```cpp
char letter = 'A'; // can also be used as small integer
```

Its important to note that if we store an integer in a `char` variable in the range 0-127, it will correspond to the ASCII values of characters. For example, the integer value 65 corresponds to the character 'A' in the ASCII table. This also means that we can assign characters to other integer values and vice versa. The difference is how the compiler imnterprets these values. if we assigne the number 65 to a short variable it will be treated as the number 65, but if we assign it to a char variable it will be treated as the character 'A'.

### Short - 2 Bytes

### Long - 4 Bytes (or 8 Bytes)

### Long Long - 8 Bytes

### Float - 4 Bytes

When we need to store decimal numbers (numbers with a fractional part), we use floating-point types. The `float` data type is a single-precision 32-bit IEEE 754 floating point. It can represent a wide range of values, but with limited precision (about 7 decimal digits).

```cpp
float pi = 3.14f; // 'f' suffix indicates a float literal otherwise it's treated as double
```
    
### Double - 8 Bytes

### Boolean - 1 Byte

0 means false, any non-zero value means true.

```cpp
bool isTrue = true;
bool isFalse = false;
bool fromInt = (5 > 3); // evaluates to true
```

You might wonder why we use 8 whole bits to represent a value that really only needs 1 bit. The reason for this is that most computer architectures are optimized to handle data in chunks of bytes (8 bits) or larger. Using a full byte for a boolean value simplifies memory alignment and access, making operations on boolean variables more efficient. But that isnt to say that we cannot store 8 boolean values in a single byte using bit manipulation techniques.

### The sizeof Operator

The `sizeof` operator in C++ is used to determine the size, in bytes, of a data type or a variable. This is particularly useful when dealing with different data types and ensuring that we allocate the correct amount of memory.

```cpp
#include <iostream>

int main() {
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of float: " << sizeof(float) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of bool: " << sizeof(bool) << " bytes" << std::endl;
    return 0;
}
```

## Arithmetic Operators

C++ provides a variety of arithmetic operators to perform mathematical operations on variables. Here are the basic arithmetic operators:
- unary: `+` (positive), `-` (negative)
- binary: `+` (addition), `-` (subtraction), `*` (multiplication), `/` (division), `%` (modulus)

```cpp
int a = 13, b = 5;
int sum = a + b;        // Addition: 18
int difference = a - b; // Subtraction: 8
int product = a * b;    // Multiplication: 65
int quotient = a / b;   // Division: 2
int remainder = a % b;  // Modulus: 3
int negativeA = -a;     // Unary Negation: -13

int a = -13, b = 5;
int quotient = a / b;   // Division: -2
int remainder = a % b;  // Modulus: -3

int a = -13, b = -5;
int quotient = a / b;   // Division: 2
int remainder = a % b;  // Modulus: -3
```