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

---

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
