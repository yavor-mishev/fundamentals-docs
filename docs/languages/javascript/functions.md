# Functions, Closures & `this`

## Functions

### Function Declaration

```javascript
function greet(name) {
    return `Hello, ${name}!`;
}
```

### Function Expression

```javascript
const greet = function(name) {
    return `Hello, ${name}!`;
};
```

### Arrow Functions

```javascript
const greet = (name) => `Hello, ${name}!`;
const add = (a, b) => a + b;
const square = x => x * x; // Single parameter, no parentheses

// Arrow functions don't have their own 'this'
```

### Default Parameters

```javascript
function greet(name = 'Guest') {
    return `Hello, ${name}!`;
}
```

### Rest Parameters

```javascript
function sum(...numbers) {
    return numbers.reduce((acc, num) => acc + num, 0);
}
sum(1, 2, 3, 4); // 10
```

### Spread Operator

```javascript
const arr1 = [1, 2, 3];
const arr2 = [4, 5, 6];
const combined = [...arr1, ...arr2];

const obj1 = { a: 1, b: 2 };
const obj2 = { c: 3, d: 4 };
const merged = { ...obj1, ...obj2 };
```

## Closures

A closure is a function that has access to its outer function's scope even after the outer function has returned:

```javascript
function outer() {
    const outerVar = 'I am from outer';
    
    function inner() {
        console.log(outerVar); // Can access outerVar
    }
    
    return inner;
}

const innerFunc = outer();
innerFunc(); // "I am from outer"

// Practical example: Data privacy
function counter() {
    let count = 0;
    
    return {
        increment: () => ++count,
        decrement: () => --count,
        getCount: () => count
    };
}

const myCounter = counter();
myCounter.increment(); // 1
myCounter.increment(); // 2
myCounter.getCount();  // 2
// count is private and cannot be accessed directly
```

## this Keyword

The value of `this` depends on how a function is called:

```javascript
// Global context
console.log(this); // window (browser) or global (Node.js)

// Object method
const obj = {
    name: 'John',
    greet: function() {
        console.log(this.name); // 'John'
    }
};
obj.greet();

// Regular function
function show() {
    console.log(this); // window (non-strict) or undefined (strict)
}

// Arrow function (lexical this)
const obj2 = {
    name: 'Jane',
    greet: function() {
        const arrow = () => {
            console.log(this.name); // 'Jane' (inherits from greet)
        };
        arrow();
    }
};

// Explicit binding
function greet() {
    console.log(this.name);
}
const person = { name: 'John' };
greet.call(person);   // 'John'
greet.apply(person);  // 'John'
const boundGreet = greet.bind(person);
boundGreet();         // 'John'

// Constructor function
function Person(name) {
    this.name = name; // 'this' refers to new instance
}
const john = new Person('John');
```
