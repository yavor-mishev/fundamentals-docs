# Prototypal Inheritance

## Objects in JS

In JavaScript, everything is an object. This includes not only the objects you create, but also functions, arrays, and even primitive types like strings and numbers. When you create a variable, you're actually creating a reference to an object in memory. For example:

```javascript
var myObject = {
  name: 'John',
  age: 30,
  greet: function () {
    console.log('Hello, my name is ' + this.name);
  },
};
```

This `myObject` variable is a reference to an object that has properties (`name`, `age`) and methods (`greet`). You can access these properties and methods using dot notation or bracket notation:

```javascript
console.log(myObject.name); // "John"
myObject.greet(); // "Hello, my name is John"
```

### Ways to create objects

There are several ways to create objects in JavaScript:

1. **Object Literal Notation** <br>
   This is the most common way to create an object, as shown above.

   ```javascript
   var person = {
     name: 'Alice',
     age: 25,
   };
   ```

---

2. **Constructor Functions** <br>
   You can define a function that acts as a constructor for creating objects. When you call this function with the `new` keyword, it creates a new object and sets its prototype to the constructor's prototype.

   ```javascript
   function Person(name, age) {
     this.name = name;
     this.age = age;
   }
   var john = new Person('John', 30);
   ```

   ***

   The `prototype` property (a plain JS object) can be accessed only through the constructor function. It allows you to add methods and properties that will be shared among all instances created by that constructor.

   ```javascript
   function Person(name, age) {
     this.name = name;
     this.age = age;
   }

   Person.prototype.greet = function () {
     console.log('Hello, my name is ' + this.name);
   };
   var john = new Person('John', 30);
   var polly = new Person('Polly', 25);

   john.greet(); // "Hello, my name is John"
   polly.greet(); // "Hello, my name is Polly"
   ```

   ***

   If you add a property to an instance with the same name as a property on the prototype, it will override the prototype property and set an own property on the instance. This is known as **shadowing**:

   ```javascript
   john.name = 'Johnny';
   console.log(john.name); // "Johnny"
   console.log(polly.name); // "Polly"
   ```

---

3. **Object.create()** <br>
   This method creates a new object with the specified prototype object and properties. It allows you to create an object that inherits from another object.

   ```javascript
   var animal = {
     makeSound: function () {
       console.log('Animal sound');
     },
   };
   var dog = Object.create(animal);
   dog.makeSound(); // "Animal sound"
   ```

---

4. **ES6 Classes** <br>
   Introduced in ECMAScript 2015, classes provide a more structured way to create objects and handle inheritance.

   ```javascript
   class Animal {
     makeSound() {
       console.log('Animal sound');
     }
   }
   class Dog extends Animal {
     makeSound() {
       console.log('Woof!');
     }
   }
   var myDog = new Dog();
   myDog.makeSound(); // "Woof!"
   ```

---

This is the essence of how JavaScript handles objects. They are dynamic, meaning you can add, modify, or delete properties and methods at any time. You might notice that the second option is the one I have added to the most and thats not a coincidence. Despite what method you use to create objects in JavaScript, they all end up using constructor functions and prototypes under the hood. This is the core of JavaScript's prototypal inheritance system.

---

## Prototypal Inheritance

The whole JavaScript language is built on the concept of **prototypical (or prototypal) inheritance**. This means that objects can inherit properties and methods from other objects. This is a fundamental concept in JavaScript and is used extensively in Kendo UI.

The idea of prototypical inheritance is that every object can be a prototype for another object. Note that I said **object**. For instance:

```javascript
const car = {
  brand: 'Skoda',
  model: 'Kodiaq',
  year: 2020,
  drive: function () {
    console.log('The Kodiaq goes vroom vroom!');
  },
};
```

This `car` object can be used as a prototype for another object using `Object.create()`. For example, we can create a `myCar` object that inherits from `car`:

```javascript
const myCar = Object.create(car);
```

If you were to log `myCar` to the console, you would see that it's just an empty object. However, it has access to the properties and methods of the `car` object:

```javascript
console.log(myCar.brand); // "Skoda"
console.log(myCar.model); // "Kodiaq"
console.log(myCar.year); // 2020
myCar.drive(); // "The Kodiaq goes vroom vroom!"
```

This is possible because the prototype of `myCar` is `car`. When you try to access a property or method on `myCar`, JavaScript first looks for it on `myCar` itself. If it doesn't find it there, it looks up the prototype chain to `car`. Even in the DevTools console, when you log `myCar`, if you open up the dropdown, you'll see the `[[Prototype]]: Object` property, which tells you that `myCar` is inheriting from somewhere. Once you open it, you'll see the `car` props and methods `brand`, `model`, `year`, and `drive()`.

![Alt text](../media/Screenshot%202025-08-05%20180639.png)

Now we can add and modify properties on `myCar` without affecting the `car` object:

```javascript
myCar.color = 'blue';
console.log(myCar.color); // "blue"
console.log(car.color); // undefined
```
