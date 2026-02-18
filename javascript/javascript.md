# JavaScript Fundamentals

## Variables: var, let, and const

### var
- **Function-scoped** or globally-scoped
- Can be re-declared and updated
- Hoisted to the top of their scope (initialized as `undefined`)
- Creates a property on the global object when declared globally

```javascript
var x = 10;
var x = 20; // No error - can be re-declared
x = 30;     // Can be updated

function example() {
    console.log(y); // undefined (hoisted)
    var y = 5;
}
```

### let
- **Block-scoped** (limited to the block `{}` where it's declared)
- Cannot be re-declared in the same scope
- Can be updated
- Hoisted but not initialized (Temporal Dead Zone)

```javascript
let a = 10;
// let a = 20; // Error - cannot re-declare
a = 30;        // Can be updated

if (true) {
    let b = 5;
}
// console.log(b); // Error - b is not defined (block-scoped)
```

### const
- **Block-scoped**
- Cannot be re-declared or updated
- Must be initialized at declaration
- For objects and arrays, the reference is constant but contents can be modified

```javascript
const PI = 3.14159;
// PI = 3.14; // Error - cannot reassign

const obj = { name: 'John' };
obj.name = 'Jane';  // OK - modifying property
obj.age = 30;       // OK - adding property
// obj = {};        // Error - cannot reassign reference

const arr = [1, 2, 3];
arr.push(4);        // OK - modifying contents
// arr = [];        // Error - cannot reassign reference
```

## Hoisting

Hoisting is JavaScript's behavior of moving declarations to the top of their scope during compilation. Well technically nothing is moved, but the memory space for variables and functions is allocated before code execution. This happens during the compilation phase and every variable and function declaration is processed before any code is executed.

### Variable Hoisting

```javascript
console.log(x); // undefined
var x = 5;

// Interpreted as:
// var x;
// console.log(x); // undefined
// x = 5;

console.log(y); // ReferenceError: Cannot access 'y' before initialization
let y = 10;
```

### Function Hoisting

```javascript
// Function declarations are fully hoisted
greet(); // "Hello!" - works

function greet() {
    console.log("Hello!");
}

// Function expressions are not hoisted
sayHi(); // TypeError: sayHi is not a function

var sayHi = function() {
    console.log("Hi!");
};
```

### Temporal Dead Zone (TDZ)

The period between entering scope and variable initialization where `let` and `const` cannot be accessed:

```javascript
{
    // TDZ starts
    console.log(x); // ReferenceError
    // TDZ ends
    let x = 10;
}
```

## Data Types

JavaScript has 8 data types:

### Primitive Types (7)
1. **String** - text data
2. **Number** - integers and floating-point numbers
3. **BigInt** - integers larger than Number can hold
4. **Boolean** - `true` or `false`
5. **Undefined** - variable declared but not assigned
6. **Null** - intentional absence of value
7. **Symbol** - unique and immutable identifier

### Object Type (1)
8. **Object** - collections of key-value pairs (includes arrays, functions, dates, etc.)

```javascript
// Primitives
let str = "Hello";
let num = 42;
let bigInt = 1234567890123456789012345678901234567890n;
let bool = true;
let undef = undefined;
let nul = null;
let sym = Symbol('unique');

// Objects
let obj = { name: 'John', age: 30 };
let arr = [1, 2, 3];
let func = function() {};
let date = new Date();
```

### Type Checking

```javascript
typeof "Hello"      // "string"
typeof 42           // "number"
typeof true         // "boolean"
typeof undefined    // "undefined"
typeof Symbol()     // "symbol"
typeof {}           // "object"
typeof []           // "object" (arrays are objects)
typeof null         // "object" (historical bug)
typeof function(){} // "function"

// Better way to check for null
value === null      // true if null

// Check if array
Array.isArray([])   // true
```

## Type Coercion

JavaScript automatically converts values between types:

```javascript
// Implicit coercion
"5" + 3        // "53" (number to string)
"5" - 3        // 2 (string to number)
"5" * "2"      // 10 (strings to numbers)
true + 1       // 2 (boolean to number)
false + 1      // 1

// Falsy values (coerce to false)
Boolean(0)           // false
Boolean("")          // false
Boolean(null)        // false
Boolean(undefined)   // false
Boolean(NaN)         // false
Boolean(false)       // false

// Truthy values (everything else)
Boolean(1)           // true
Boolean("0")         // true
Boolean({})          // true
Boolean([])          // true
```

### Equality Operators

```javascript
// == (loose equality - with type coercion)
5 == "5"       // true
0 == false     // true
null == undefined // true

// === (strict equality - no type coercion)
5 === "5"      // false
0 === false    // false
null === undefined // false

// Always prefer ===
```

## Prototypes and Inheritance

Every JavaScript object has a prototype. The prototype is also an object that the current object inherits from.

### Prototype Chain

```javascript
function Person(name) {
    this.name = name;
}

Person.prototype.greet = function() {
    console.log(`Hello, I'm ${this.name}`);
};

const john = new Person('John');
john.greet(); // "Hello, I'm John"

// Prototype chain
console.log(john.__proto__ === Person.prototype);           // true
console.log(Person.prototype.__proto__ === Object.prototype); // true
console.log(Object.prototype.__proto__);                      // null
```

### Object.create()

```javascript
const animal = {
    makeSound: function() {
        console.log('Some sound');
    }
};

const dog = Object.create(animal);
dog.bark = function() {
    console.log('Woof!');
};

dog.bark();       // "Woof!"
dog.makeSound();  // "Some sound" (inherited)
```

### ES6 Classes (Syntactic Sugar over Prototypes)

```javascript
class Animal {
    constructor(name) {
        this.name = name;
    }
    
    speak() {
        console.log(`${this.name} makes a sound`);
    }
}

class Dog extends Animal {
    constructor(name, breed) {
        super(name);
        this.breed = breed;
    }
    
    speak() {
        console.log(`${this.name} barks`);
    }
}

const dog = new Dog('Rex', 'Labrador');
dog.speak(); // "Rex barks"
```

## Data Structures

### Arrays

```javascript
// Creating arrays
const arr1 = [1, 2, 3];
const arr2 = new Array(1, 2, 3);
const arr3 = Array.of(1, 2, 3);

// Common methods
arr1.push(4);           // Add to end
arr1.pop();             // Remove from end
arr1.unshift(0);        // Add to beginning
arr1.shift();           // Remove from beginning

// Iteration
arr1.forEach(item => console.log(item));
arr1.map(item => item * 2);
arr1.filter(item => item > 2);
arr1.reduce((acc, item) => acc + item, 0);

// Other useful methods
arr1.find(item => item === 2);
arr1.findIndex(item => item === 2);
arr1.includes(2);
arr1.some(item => item > 2);
arr1.every(item => item > 0);
arr1.slice(1, 3);
arr1.splice(1, 2, 'a', 'b');
```

### Objects

```javascript
// Creating objects
const obj1 = { name: 'John', age: 30 };
const obj2 = new Object();
const obj3 = Object.create(null);

// Accessing properties
obj1.name;          // Dot notation
obj1['name'];       // Bracket notation

// Adding/Modifying properties
obj1.email = 'john@example.com';
obj1['phone'] = '555-1234';

// Deleting properties
delete obj1.email;

// Object methods
Object.keys(obj1);       // ['name', 'age']
Object.values(obj1);     // ['John', 30]
Object.entries(obj1);    // [['name', 'John'], ['age', 30]]
Object.assign({}, obj1); // Shallow copy
Object.freeze(obj1);     // Make immutable
Object.seal(obj1);       // Prevent adding/removing properties

// Destructuring
const { name, age } = obj1;

// Spread operator
const obj4 = { ...obj1, city: 'NYC' };
```

### Maps

Ordered key-value pairs where keys can be any type:

```javascript
const map = new Map();

// Setting values
map.set('name', 'John');
map.set(1, 'number key');
map.set(true, 'boolean key');

// Getting values
map.get('name');        // 'John'

// Other methods
map.has('name');        // true
map.delete('name');     // true
map.size;               // 2
map.clear();            // removes all

// Iteration
map.forEach((value, key) => {
    console.log(`${key}: ${value}`);
});

for (let [key, value] of map) {
    console.log(`${key}: ${value}`);
}
```

### Sets

Collection of unique values:

```javascript
const set = new Set([1, 2, 3, 3, 4]); // {1, 2, 3, 4}

// Adding values
set.add(5);
set.add(5);  // Duplicate ignored

// Checking values
set.has(3);  // true

// Removing values
set.delete(3);
set.clear(); // removes all

// Size
set.size;    // 4

// Iteration
set.forEach(value => console.log(value));
for (let value of set) {
    console.log(value);
}

// Convert to array
const arr = [...set];
const arr2 = Array.from(set);
```

### WeakMap and WeakSet

Similar to Map and Set but with weak references (can be garbage collected):

```javascript
// WeakMap - keys must be objects
const weakMap = new WeakMap();
let obj = { id: 1 };
weakMap.set(obj, 'data');
obj = null; // Object can now be garbage collected

// WeakSet - values must be objects
const weakSet = new WeakSet();
let obj2 = { id: 2 };
weakSet.add(obj2);
obj2 = null; // Object can now be garbage collected
```

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

## Asynchronous JavaScript

### Callbacks

```javascript
function fetchData(callback) {
    setTimeout(() => {
        callback('Data received');
    }, 1000);
}

fetchData((data) => {
    console.log(data);
});
```

### Promises

```javascript
const promise = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve('Success!');
        // or reject('Error!');
    }, 1000);
});

promise
    .then(result => console.log(result))
    .catch(error => console.error(error))
    .finally(() => console.log('Cleanup'));

// Promise methods
Promise.all([promise1, promise2]);      // Wait for all
Promise.race([promise1, promise2]);     // First to settle
Promise.allSettled([promise1, promise2]); // Wait for all to settle
Promise.any([promise1, promise2]);      // First to fulfill
```

### Async/Await

```javascript
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Error:', error);
    }
}

// Async functions always return a Promise
fetchData().then(data => console.log(data));
```

## Destructuring

### Array Destructuring

```javascript
const arr = [1, 2, 3, 4, 5];
const [first, second, ...rest] = arr;
// first = 1, second = 2, rest = [3, 4, 5]

// Skipping elements
const [a, , c] = arr;
// a = 1, c = 3

// Default values
const [x, y, z = 0] = [1, 2];
// x = 1, y = 2, z = 0
```

### Object Destructuring

```javascript
const person = { name: 'John', age: 30, city: 'NYC' };
const { name, age, country = 'USA' } = person;
// name = 'John', age = 30, country = 'USA'

// Renaming variables
const { name: fullName, age: years } = person;
// fullName = 'John', years = 30

// Nested destructuring
const user = {
    id: 1,
    info: { name: 'John', email: 'john@example.com' }
};
const { info: { name, email } } = user;
```

## Template Literals

```javascript
const name = 'John';
const age = 30;

// String interpolation
const greeting = `Hello, ${name}!`;

// Multi-line strings
const message = `
    This is a
    multi-line
    string.
`;

// Expression evaluation
const result = `5 + 3 = ${5 + 3}`;

// Tagged templates
function highlight(strings, ...values) {
    return strings.reduce((result, str, i) => {
        return result + str + (values[i] ? `<mark>${values[i]}</mark>` : '');
    }, '');
}

const output = highlight`Name: ${name}, Age: ${age}`;
```

## Modules

### ES6 Modules (ESM)

```javascript
// export.js
export const PI = 3.14159;
export function add(a, b) {
    return a + b;
}
export default class Calculator {
    // ...
}

// import.js
import Calculator, { PI, add } from './export.js';
import * as math from './export.js';
import { add as sum } from './export.js'; // Rename import
```

### CommonJS (Node.js)

```javascript
// export.js
const PI = 3.14159;
function add(a, b) {
    return a + b;
}
module.exports = { PI, add };

// import.js
const { PI, add } = require('./export.js');
```

## Error Handling

```javascript
// try-catch
try {
    const result = riskyOperation();
} catch (error) {
    console.error('Error:', error.message);
} finally {
    console.log('Cleanup');
}

// Throwing errors
throw new Error('Something went wrong');
throw new TypeError('Invalid type');
throw new ReferenceError('Variable not found');

// Custom errors
class CustomError extends Error {
    constructor(message) {
        super(message);
        this.name = 'CustomError';
    }
}

throw new CustomError('Custom error occurred');
```

## Strict Mode

```javascript
'use strict';

// Prevents common mistakes:
// - Using undeclared variables
// - Deleting variables/functions
// - Duplicating parameter names
// - Using reserved keywords
// - etc.

x = 10; // ReferenceError in strict mode
```

## Operators

### Nullish Coalescing (??)

```javascript
const value = null ?? 'default';     // 'default'
const value2 = undefined ?? 'default'; // 'default'
const value3 = 0 ?? 'default';       // 0 (not null/undefined)
const value4 = '' ?? 'default';      // '' (not null/undefined)
```

### Optional Chaining (?.)

```javascript
const user = {
    name: 'John',
    address: {
        city: 'NYC'
    }
};

const city = user?.address?.city;     // 'NYC'
const zip = user?.address?.zip;       // undefined (no error)
const method = user?.someMethod?.();  // undefined (no error)
const arr = user?.hobbies?.[0];      // undefined (no error)
```

### Logical Assignment Operators

```javascript
// OR assignment (||=)
let x = null;
x ||= 10;  // x = 10 (assigns if x is falsy)

// AND assignment (&&=)
let y = 5;
y &&= 10;  // y = 10 (assigns if y is truthy)

// Nullish assignment (??=)
let z = null;
z ??= 10;  // z = 10 (assigns if z is null/undefined)
```
