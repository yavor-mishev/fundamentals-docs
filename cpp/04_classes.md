# C/C++ Classes

To put it simply, a class is a user-defined data type that allows you to group related variables (attributes) and functions (methods) together. Classes are the foundation of object-oriented programming (OOP) in C++. OOP as a programming paradigm focuses on using objects to represent real-world entities and concepts. Languages like Java and C# more or less enforce OOP principles, while C++ provides the flexibility to use both procedural and object-oriented programming styles. C for instance does not support classes or OOP concepts. Its important to remember that there isnt anything inherently "better" about OOP or procedural programming, they are just different approaches to solving problems and organizing code. Depending on the project requirements, one approach may be more suitable than the other. And also classes dont give you some magical superpowers or functionality that you cant achieve with procedural programming, they are just a different way to structure and organize your code. You can accomplish the same results by using or omitting classes, its just a matter of preference and design choices.

Creating a class Player is essentially creating a new data type that can hold multiple pieces of information about a player, such as their position (x, y) and speed. Here's a simple example of how to define and use a class in C++:

```cpp
class Player {
    int x, y;
    int speed;
};
```

In this example, we define a class named `Player` with three attributes: `x`, `y`, and `speed`. These attributes are private by default, meaning they cannot be accessed directly from outside the class, only from methods within the class. To alter the visibility of these attributes, we can use access specifiers like `public`, `private`, and `protected`. Here is an example of setting them to public so we can access them from the main function:

```cpp
class Player {
public:
    int x, y;
    int speed;
};

int main() {
    Player player;
    player.x = 10;
    player.y = 20;
    player.speed = 5;
}
```

We can create a Move function that updates the player's position based on their speed.

```cpp
class Player {
public:
    int x, y;
    int speed;
};

void Move(Player& player, int xa, int ya) {
    player.x += xa * player.speed;
    player.y += ya * player.speed;
}

int main() {
    Player player;
    player.x = 10;
    player.y = 20;
    player.speed = 5;

    Move(player, 1, 0); // Move right
}
```

This is OK, but a more idiomatic way to do this in C++ is to define the Move function as a method inside the Player class itself. This way we dont need to reference the player object as a parameter, since the method will have access to the instance's attributes directly and the method call syntax is cleaner. Notice im now refering to the function as a method since its part of the class and we can access it using the dot operator on the instance:

```cpp
class Player {
public:
    int x, y;
    int speed;

    void Move(int xa, int ya) {
        x += xa * speed;
        y += ya * speed;
    }
};

int main() {
    Player player;
    player.x = 10;
    player.y = 20;
    player.speed = 5;

    player.Move(1, 0); // Move right
}
```

## Structures vs Classes

The only difference between a struct and a class is visibility. When creating a class the default visibility of its members (attributes and methods) is private, while for a struct the default visibility is public. Other than that, structs and classes are functionally equivalent in C++. In practice, structs are often used for simple data structures that primarily hold data without much behavior, while classes are used for more complex entities that encapsulate both data and behavior. However, this is just a convention and not a strict rule.

To make something public in a class, we would need to use the public access specifier like so:

```cpp
class Player {
public: 
    int x, y;
    int speed;
};
```

to make something private in a struct, we would need to use the private access specifier like so:

```cpp
struct Player {
private:
    int x, y;
    int speed;
};
```

Thats it!

## Creating a Class

Lets create a more complete Log class.

//TODO: Add Log class example