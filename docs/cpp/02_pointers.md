## Pointers

Pointers are variables that store the memory address of another variable. They are just integer values that represent a location in memory where data is stored. Pointers are declared using the asterisk (*) symbol. They have nothing to do with data types. A pointer for any data type is an integer value that holds a memory address.

```cpp
void* ptr = 0; // 0 is not a valid memory address. we cannot read or write to it.
void* ptr = NULL; // NULL is the same as 0.

int var = 8;
int* varPtr = &var; // & is the address-of operator. it returns the memory address of the variable.
```

Since pointers can have any type, why dont we use void pointer all the time? The reason is that when we dereference a pointer (access the value at the memory address it points to), the compiler needs to know the data type of the value stored at that address to interpret it correctly. If we use a void pointer, the compiler does not know what type of data is stored at that address, and we cannot dereference it directly without casting it to the appropriate type first.

```cpp
int var = 8;
void* ptr = &var; // void pointer
*ptr = 10; // the compilator cannot write the value 10 to a variable of unknown type. this line will cause a compilation error.
```

So `*ptr` is essentially dereferencing the pointer to access the value at the memory address it points to. But since `ptr` is a void pointer, the compiler does not know what type of data is stored at that address, and it cannot perform the dereference operation directly.

Another cool thing we can do with pointers is allocate memory dynamically on the heap using the `new` keyword. This allows us to create variables and data structures at runtime, rather than at compile time.

```cpp
char* buffer = new char[8]; // allocate 8 bytes on the heap
memset(buffer, 10, 8); // initialize the memory to zero
```

Here we create a char pointer which by default is one byte in size. Then we allocate 8 bytes on the heap using the `new` keyword and assign the memory address of the first byte to the `buffer` pointer. Finally, we use the `memset` function to initialize the allocated memory to 10 so every byte in the allocated memory will have the value 10.

We can also have pointers to pointers:

```cpp
char** ptrToPtr = &buffer; // pointer to pointer
```