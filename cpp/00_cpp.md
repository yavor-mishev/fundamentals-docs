# C++

## How C++ Works

C++ is a compiled language. This means that whatever code we write in C++ needs to be compiled into machine code before it can be executed by the computer. The compilation process is handled by a program called a **compiler**, which translates the high-level C++ code into low-level machine code that the computer's processor can understand.

hello.cpp -> Compiler -> hello binary (machine code)

When we run the compiled binary, the operating system loads it into memory and the processor executes the machine code instructions.

The binary can be a library or an executable program. Libraries contain reusable code that can be linked to other programs, while executables are standalone programs that can be run directly by the operating system.

### Disection of a C++ Program

Let's take a look at a simple C++ program:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

- `#include <iostream>`: everything that starts with `#` is a *preprocessor directive*. This line tells the preprocessor to include the contents of the `iostream` header file, which contains declarations for input and output functions.
- `int main() { ... }`: This is the main function where the execution of the program begins. The `int` before `main` indicates that this function returns an integer value.
- `std::cout << "Hello, World!" << std::endl;`: This line is a statement that outputs the text "Hello, World!" to the console. `std::cout` is the standard output stream in C++, and `<<` is the stream insertion operator used to send data to the output stream. `std::endl` is used to insert a newline character and flush the output buffer.
- `return 0;`: This line indicates that the program has completed successfully. Returning 0 from the `main` function is a convention that signifies successful execution.

## C++ Compiler

For this documentation, I have followed a very well presented [YT video by Ryan Baker](https://www.youtube.com/watch?v=-oYG-_cyAsI). There is also a link to his [notes](https://github.com/rybkr/Intro-to-Modern-Cxx/blob/main/chapters/build-process/build/build-process.pdf) in the video description which you should check out.

For the .cpp file to be converted to machine code it needs to go through the compiler which has three main steps: **preprocessor**, **compiler**, **linker**.

### The Preprocessor

The preprocessor's job is to handle and resolve all preprocessor directives in the source code before the actual compilation begins. It processes directives such as `#include`, `#define`, and conditional compilation directives like `#if`, `#ifdef`, and `#ifndef`.

- `#define`: used to define macros.

The basic idea is that the preprocessor performs a simple text substitution before the compilation phase. For example, if we have a macro defined as `#define PI 3.14`, every occurrence of `PI` in the code will be replaced with `3.14` by the preprocessor.

```cpp
#define PI 3.14;
int main() {
    float area = PI * 5 * 5; // will be replaced with 3.14 * 5 * 5
}
```

In some documentation you might encounter something like this: "The `#define` directive is used to define **constants**". This is not etirely accurate because I can do this:

```cpp
#define PI 3.14;
#define PI 4;
```

You can also define macros with parameters:

```cpp
#define SQUARE(x) x * x
int main() {
    int result = SQUARE(5); // will be replaced with 5 * 5
}
```

This can lead to many unexpected behaviors if not used carefully. Lets look at the same example but with a different value for x:

```cpp
#define SQUARE(x) x * x
int main() {
    int result = SQUARE(3 + 3); // will be replaced with 3 + 3 * 3 + 3 = 15
}
```

The preprocessor doesnt take into account operator precedence when substituting macros. To avoid this kind of issue, its a good practice to enclose macro parameters in parentheses:

```cpp
#define SQUARE(x) ((x) * (x))
int main() {
    int result = SQUARE(3 + 3); // will be replaced with ((3 + 3) * (3 + 3)) = 36
}
```

Here is an example of using macros where we cannot control the result of the substitution. We would expect the result to be 36 but instead we get 42 or 49 or... you get the idea. The result often depends on the compiler optimizations and other factors:

```cpp
#define SQUARE(x) ((x) * (x))
int main() {
    int a = 5;
    int result = SQUARE(++a); // will be replaced with ((++a) * (++a))
    // The value of 'a' is incremented twice, leading to unexpected behavior.
}
```

As a **rule of thumb**, avoid using macros when possible. Instead, prefer using `const` variables or `inline` functions which provide type safety and better scoping. Remember that the preprocessor is stupid and the compiler is smart. Leave the complex stuff to the compiler. The compiler can optimize your code, catch potential bugs, and provide better error messages.

Lastly we can `#define` macros without values to use them as flags for conditional compilation. We'll see an example of this when we discuss the `#if` directive. 

- `#undef`: used to undefine a macro.

```cpp
#define PI 3.14;
double circumference = 2 * PI * radius;

#undef PI
double area = PI * radius * radius; // Error: 'PI' is not defined
```

- `#include`: used to include the contents of a file into the current file (copy/paste).

The `#include` directive is used to include the contents of one file into another file during the preprocessing phase. This is commonly used to include header files that contain declarations for functions, classes, and other constructs that we want to use in our code. It can be thought of as the **copy-and-paste** directive, where the preprocessor searches for the specified file and copies its contents into the current file at the location of the `#include` directive.

There are two ways to use the `#include` directive: angle brackets `< >` and double quotes `" "`. The difference between the two is where the preprocessor looks for the specified file.

```cpp
#include <filename> // searches in system directories
#include "filename" // searches in the current directory first, then system directories
```

Here is an example of using the `#include` directive:

```cpp
// x.cpp
int x = 500;

// main.cpp
#include <iostream>
#include "x.cpp" // includes the contents of x.cpp here

int main() {
    std::cout << x << std::endl; // Output: 500
}
```

This example is the same as:

```cpp
// main.cpp
#include <iostream>
int x = 500;

int main() {
    std::cout << x << std::endl;
}
```

- header files `.h`: commonly used in C++ to organize code, especially in larger projects.

The primary role is to declare the interface of a module or library, allowing for separation between the declaration of functionality and its implementation.

```cpp
// myLib.h
void greet();// declare the function greet()
```

The implemetation of this function would typically e placed in the corresponding source file `myLib.cpp`:

```cpp
// myLib.cpp
#include <iostream>
#include "myLib.h"

void greet() {
    std::cout << "Hello from MyLib" << std::endl;
}
```

```cpp
#include "myLib.h"

int main() {
    greet();
}
```

- conditional compilation `#if` `#ifdef`: used to include or exclude parts of the code based on a condition.

The most simple way to use conditional compilation is with the `#if` directive:

```cpp
#define DEBUG 1
#if DEBUG
    std::cout << "Debug mode is enabled." << std::endl;
#endif
```

You can also use `#elif` and `#else` directives to create more complex conditional structures.

A very common case for conditional compilation is **include guards** to prevent multiple inclusions of the same header file in a translation unit. This is typically done using the `#ifndef` and `#define` directives.

#### What is a translation unit?

The translation unit is the result of the preprocessing phase for a single source file. It includes the contents of the source file along with all the header files that were included via `#include` directives. This means that each translation unit is valid C++ code that can be compiled independently.

We can view the result of the preprocessing phase by using the `-E` flag with the compiler. For example, running `clang++ -E main.cpp -o main.i` will output the preprocessed code to a file named `main.i`.

If you are using Visual Studio, you can generate the preprocessed output by going to the projects properties, navigating to `C/C++` -> `Preprocessor`, and setting the `Preprocess to a File` option to `Yes (/P)`. This will create a `.i` file containing the preprocessed code when you build the project. Then just right-click your main.cpp file in the sln explorer and click Compile (or CTRL + F7) to generate the preprocessed file. The result will be in the directory of your project under `Debug`.

When you open the file you will see that all the `#include` directives have been replaced with the actual contents of the included files, and all macros have been expanded. Even for a simple program that outputs "Hello, World!" the preprocessed file will be huge because it includes all the standard library headers (`#include <iostream>`). At the end of the file you will find your original code.

### The Compiler

The compilation phase parses the result of the preprocessing phase (translation unit) into an **object file**.

An object file contains machine code that is not yet linked to other object files or libraries. It also contains metadata such as symbol tables and relocation information that the linker will use to combine multiple object files into a single executable or library.

There are 6 main steps in the compilation phase:

1. **Lexical Analysis**: The compiler reads the source code and breaks it down into **tokens**, which are the smallest units of meaning in the code (keywords, identifiers, operators, etc.). For example the code:

```cpp
int y = x + 5;
```

could be broken into the following tokens:

```cpp
[int] [y] [=] [x] [+] [5] [;]
```

At this stage the compiler detects tokenization errors such as invalid characters or malformed tokens.

2. **Syntax Analysis**: The compiler checks the tokens against the grammar rules of C++ to ensure that the code is syntactically correct. It builds a parse tree or abstract syntax tree (AST) that represents the structure of the code. For example, it checks if statements are properly formed and if parentheses are balanced.

```cpp
int y = x + 5; // valid syntax
int y = x + ; // invalid syntax (missing operand)
int y x + 5; // invalid syntax (missing '=' operator)
int 5 + x = y; // same  tokens but invalid syntax (left-hand side must be a variable)
```

3. **Semantic Analysis**: The compiler checks the AST for semantic errors, such as type mismatches, undeclared variables, and incorrect function calls. It ensures that the code adheres to the rules of C++ semantics.

```cpp
int y = "hello"; // semantic error: cannot assign a string to an int
float z = 3.14;
int result = y + z; // semantic error: cannot add int and float without casting
```

4. **Intermediate Code generation**: At this point the compiler has confirmed that your code is syntactically and semantically correct. It now generates an **intermediate representation (IR)** of your code which is independent of the target machine architecture. This makes the code easier to optimize and and facilitates porting the program to different platforms.

5. **Code Optimization**: The compiler applies various optimization techniques to improve the performance, efficiency and size of the intermediate code. This can include eliminating redundant calculations, inlining functions, and optimizing loops. Here are some optimization examples:

- **Constant Folding**: The compiler evaluates constant expressions at compile time rather than runtime.

```cpp
int weeks = 365 / 7; // constant folding: evaluates to 52 at compile time
```
```cpp
int weeks = 52; // more efficient
```

This optimization eliminates the need for division at runtime.

- **Loop Hoisting**: The compiler moves calculations that produce the same result on each iteration of a loop outside the loop.

```cpp
for (int i = 0; i < 1000; i++) {
    int k = expensiceComputation(); // this computation is the same for every iteration
    // do something with k
}
```
```cpp
int k = expensiceComputation(); // hoisted outside the loop
for (int i = 0; i < 1000; i++) {
    // do something with k
}
```

- **Dead Code Elimination**: The compiler removes code that is never executed or whose results are never used.

```cpp
void foo() {
    //...
    return;
    // unreachable code...
    int x = 5; // dead code
}
```

- **Common Expression Removal**: The compiler identifies expressions that are computed multiple times and stores the result in a temporary variable to avoid redundant calculations.

```cpp
int a = x * y;
int b = x * y * z;
```
Optimized to:
```cpp
int a = x * y;
int b = a * z;
```

**Note**: These optimizations are just examples, and the actual optimizations performed by a compiler can be much more complex and varied depending on the specific compiler and optimization settings used. And the other thing you need to remember is to not sacrifice code readability for micro-optimizations. Always prioritize writing clear and maintainable code first, and let the compiler handle the optimizations. The compiler will always be better than you at optimizing code!

6. **Code Generation**: Finally, the compiler translates the optimized intermediate code into machine code specific to the target architecture. This machine code is then packaged into an object file (`.o` or `.obj`), which contains the binary instructions that can be executed by the computer's processor.

#### Compiler Output

The compiler produces an **object file**. This object file contains machine code that the processor can understand but it is not yet a complete executable program. The object file may contain references to functions and variables that are defined in other object files or libraries. These references need to be resolved during the linking phase.

We can instruct the compiler to generate an object file to the point before the linking phase by using the `-c` flag. For example, running `clang++ -c main.cpp -o main.o` will compile the `main.cpp` file into an object file named `main.o` without linking it.

### The Linker

The linker is the final stage of the build precess. The linker is responsible for combining multiple object files into a single executable program. Here is an example of how the linker works:

```cpp
// foo.h
#ifndef FOO_H_INCLUDED
#define FOO_H_INCLUDED

void foo();

#endif // FOO_H_INCLUDED
```
```cpp
// foo.cpp
#include <iostream>
#include "foo.h"

void foo() {
    std::cout << "fooing..." << std::endl;
}
```
```cpp
// proj.cpp
#include "foo.h"

int main() {
    foo();
}
```

In this example if we were to compile just the `proj.cpp` file (`clang++ proj.cpp`) we would get a linking error because the linker cannot find the implementation of the `foo()` function. To fix this we need to compile both `foo.cpp` and `proj.cpp` (`clang++ proj.cpp foo.cpp`) which would create an object file for each and link them successfuly resulting in the final executable.