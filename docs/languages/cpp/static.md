# The static Keyword

In C++, the `static` keyword can be used in two primary contexts: within classes and for variables with static storage duration.

1. **Static Variables outside of Classes**: When you declare a variable as `static` outside of any class or function, it means that the variable is accessible only within the translation unit (usually the source file) where it is defined. This limits the variable's scope to that file, preventing name conflicts with variables of the same name in other files. For instance if we had the same function or variable declared in two separate files, if we compled our project the linker would throw an error since it wouldnt know which one to link to. Making a variable or function static in this context avoids that issue.

```cpp
// file1.cpp
static int counter = 0; // This counter is only accessible within file1.cpp
void IncrementCounter() {
    counter++;
}

// file2.cpp
int counter = 0; // This counter is a different variable, accessible globally
```

2. **Static Members in Classes**: When you declare a member of a class as `static`, it means that the member belongs to the class itself rather than to any specific instance of the class. This means that all instances of the class share the same static member. Static members can be useful for keeping track of information that is common to all instances, such as a count of how many objects of that class have been created.

```cpp
class Player {
public:
    static int playerCount; // Static member to keep track of the number of Player instances

    Player() {
        playerCount++; // Increment the count when a new Player is created
    }
};

int Player::playerCount = 0; // Initialize the static member outside the class
int main() {
    Player p1;
    Player p2;
    Player p3;

    // Access the static member using the class name
    std::cout << "Number of players: " << Player::playerCount << std::endl; // Outputs: Number of players: 3
}
```