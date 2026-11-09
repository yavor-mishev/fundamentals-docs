# Destructuring, Modules & Error Handling

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
