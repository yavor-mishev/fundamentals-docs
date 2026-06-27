## References

References are used to reference already existing variables. They cannot be initialized to `null` like pointers and they cannot be changed to reference another variable after they have been initialized. References are declared using the ampersand **&** symbol.

```cpp
int a = 8;
int& ref = a; // ref is a reference to a
```

We have essentially created an alias for the variable `a`. Any changes made to `ref` will also affect `a`, and vice versa. Thats why we cannot say `ref` is an actual variable, because it does not have its own memory address. When we compile the code the compiler will replace all instances of `ref` with `a`.

Now to the spicy stuff... have a look at this code snippet:

```cpp
void Increment(int value) {
    value++;
}
int main() {
    int a = 8;
    Increment(a);
    std::cout << a << std::endl; // Output: 8
}
```

Here we are passing the variable `a` by value to the `Increment` function. This means that we have basically passed the value `5` to the function and any changes made to the `value` parameter inside the function will not affect the original variable `a`. So the output of this code will be `8`.

We now know that we can easily fix this by using pointers becaus pointers point to an actual memory address of a variable. We can pass a pointer to the variable `a` to the `Increment` function and dereference it inside the function to modify the original variable in memory. Of course make sure to first dereference the pointer before incrementing it.

```cpp
void Increment(int* value) {
    (*value)++;
}
int main() {
    int a = 8;
    Increment(&a);
    std::cout << a << std::endl; // Output: 9
}
```
Ok but this section is about references... we can achieve the same result using references with less syntax clutter:

```cpp
void Increment(int& value) {
    value++;
}
int main() {
    int a = 8;
    Increment(a);
}
```

This works because `value` is a reference to the variable passed to the function(in this case `a`). Any changes made to `value` inside the function will directly affect the original variable `a`. So the output of this code will be `9`.