In order to tackle a framework like React, it's important to have a solid understanding of JavaScript fundamentals. If you feel like you need a refresher on JavaScript before diving into React, consider reviewing the following key concepts:

- where JS can be executed (browser, server, etc.)
- adding JS code to a webpage and how it differs in React
- React projects use a build process
- "import" and "export" statements
- variables and values
- operators
- functions and parameters
- arrow functions
- objects and classes
- arrays and array methods
- destructuring
- the spread operator
- control structures (if/else, switch, loops)
- manipulating the DOM with vanilla JS (not with React)
- using functions as values (callbacks, higher-order functions)
- defining functions inside other functions (closures)
- reference vs primitive values

## Where JS can be executed (browser, server, etc.)

JS was originally created to be executed in the browser with the sole foal to maka webpages interactive. Over time, JS has evolved and can now be executed in various environments, including server-side environments like Node.js, mobile applications using frameworks like React Native, and even desktop applications with Electron.

## Adding JS code to a webpage and how it differs in React

Two main options: between <script> tags or via <script> import

```html
<script>
	console.log("Hello, world!");
</script>
```

```html
<script src="app.js"></script>
```

Using the second option is more common in React projects, where you typically have a build process that bundles your JavaScript code and its dependencies into a single file that can be included in your HTML. Moreover its much more maintainable for larger projects.

You can also add additional attributes to the script tag, like "type" or "defer".

- "defer" makes sure the script is executed after the HTML is fully parsed. This ensures that if your script does any DOM manipulation, the elements are already available/rendered.
- "type" can be used to specify the type of script. For example, in React projects, you might see `type="module"` which indicates that the script is a JavaScript module, allowing you to use **import** and **export** statements.

Now in the context of React you will never be adding JS code directly to a webpage like this. Instead, you will be using a build process (like Create React App, Vite, or Next.js) that handles bundling and serving your React application. Its the process that takes care of this for you.

## React build process

React projects use a build process for these two main reasons:

1. raw unprocesed React code womt execute in the browser. JSX is not a default JS feature
2. the code you write will not be optimized for production use. The build process optimizes the code for performance, reducing file sizes and improving load times (e.g. not minified code, unoptimized assets, etc.).

The code you write is not the code that gets executed in the browser. React uses a build process that typically involves tools like Babel and Webpack (or alternatives like Vite) to transform your modern JavaScript and JSX code into a format that browsers can understand. This process includes:

- Transpiling JSX into regular JavaScript
- Converting modern JavaScript (ES6+) into a version compatible with older browsers
- Bundling multiple files into a single or few files for efficient loading
- etc.

## "import" and "export" statements

This JS syntax allows us to gain access to code from other files and share code between files. This is essential in React projects where components are typically organized into separate files for better maintainability and reusability.

```javascript
// utils.js
export function add(a, b) {
	return a + b;
}

// app.js
import { add } from "./utils.js";
console.log(add(2, 3)); // Outputs: 5
```

You can also create a default export in a file, which allows you to export a single value or function as the main export of that file. You can only have one default export perf file but you can have multiple named exports.

```javascript
// math.js
export default function multiply(a, b) {
	return a * b;
}

// app.js
import multiply from "./math.js";
console.log(multiply(2, 3)); // Outputs: 6
```

## Variables and values

We can create values when we need them:

```javascript
console.log(42); // Outputs: 42
```

or store them in variables for later use:

```javascript
const answer = 42;
console.log(answer); // Outputs: 42
```

We can create variables using the let or const keywords. The main difference is that variables declared with const cannot be reassigned, while those declared with let can be reassigned.

```javascript
let count = 0;
count = count + 1; // This is valid

const pi = 3.14;
pi = 3.14159; // This will throw an error
```

## Operators

Operators are special symbols that perform operations on values and variables. Common operators include: +, -, \*, / for arithmetic operations, and ===, !==, <, > for comparisons.

## Functions and parameters

The idea of a function is to encapsulate a piece of code that can be reused multiple times. Functions can take inputs, called parameters, and can return an output.

```javascript
function greet(name) {
	return `Hello, ${name}!`;
}
console.log(greet("Alice")); // Outputs: Hello, Alice!
```

We can also assign default values for our parameters:

```javascript
function greet(name = "Guest") {
	return `Hello, ${name}!`;
}
console.log(greet()); // Outputs: Hello, Guest!
```

## Arrow functions

In js we can define anonymous function using the standard function syntax:

```javascript
function (a, b) {
  return a + b;
}
```

````

With arrow functions, we can write the same function in a more concise way:

```javascript
(a, b) => {
  return a + b;
}
````
