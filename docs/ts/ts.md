# TypeScript

TypeScript is a statically typed superset of JavaScript that adds optional types, interfaces, and other features to enhance code quality and maintainability. It compiles down to plain JavaScript, making it compatible with any environment that supports JavaScript.

```typescript
const age: number = 25;
const name: string = "Alice";
const isStudent: boolean = true;
const isUndefined: undefined = undefined;
const isNull: null = null;
```

```javascript
const age = 25;
const name = "Alice";
const isStudent = true;
const isUndefined = undefined;
const isNull = null;
```

## Type inference

TypeScript has a powerful type inference system that automatically infers types based on the assigned values. This means that you don't always have to explicitly declare types, as TypeScript can often determine them for you. In fact its considered best practice to let TypeScript infer types whenever possible, as it leads to cleaner and more maintainable code. This means less code for you to write and read, while still benefiting from type safety, code looks like JS in most cases, its safer because you as a dev can mix things up.

```typescript
const age: number = 25; // Explicit type annotation
const name = "Alice"; // TypeScript infers the type as string
```

## Why use TypeScript?

TypeScript is a superset of JavaScript, which means that all JS code is valid TS code and all TS code is not necessarily valid JS code. TypeScript adds several features that enhance the development experience:
- Catches a ton of bugs and errors at compile time
- Makes your code more readable and maintainable
- Makes it easier to refactor and scale your codebase

## The TypeScript Compiler

TSC is the TypeScript compiler that:
1. takes your code
2. ensures its valid
3. compiles it into plain JavaScript code

The TS compiler is writen in TS although on the 11-th of March, 2025 Microsoft announced plans to [port the TypeScript compiler to Go](https://devblogs.microsoft.com/typescript/typescript-native-port/) for improved performance (10x).

## Any

The `any` type is a special type in TypeScript that allows you to opt-out of type checking for a particular variable. When a variable is declared with the `any` type, it can hold values of any type, and TypeScript will not perform any type checking on it. This can be useful in certain situations where you need to work with dynamic data or when migrating existing JavaScript code to TypeScript.

```typescript
let dynamicValue: any = 'Hello';
```

## Function Type Syntax

One of the most useful scenarios for TypeScript is defining function types. This allows you to specify the types of parameters and the return type of a function, providing better type safety and code clarity.

```typescript
function createmessage(name: string, a: number, b: number): string {
    return `${name} scored ${a + b}`;
}
```

The `: type` after each parameter specifies that parameter's type, and the `: type` after all the parameters specifies the return type.

Just as we have type inference for variable and parameters in the case of functions, TypeScript can also infer the return type of a function based on its implementation. This means that you don't always have to explicitly declare the return type, as TypeScript can often determine it for you.

```typescript
function createmessage(name: string, a: number, b: number) {
    return `${name} scored ${a + b}`;
}
```

We can also make a function type:

```typescript
function add(a: number, b: number): number {
    return a + b;
}

function multiply(a: number, b: number): number {
    return a * b;
}

function createMessage(name: string, score: (a: number, b: number) => number): string {
    return `${name} scored ${score(5, 10)}`;
}

console.log(createMessage('Alice', add)); // Alice scored 15
console.log(createMessage('Bob', multiply)); // Bob scored 50
```

### Function Types Aliases

You can also define function types as variable types. This is useful when you have the same scenario as in the previous example, but you want to reuse the function type in multiple places. If you were to stick to the previous approach, you would have to repeat the function type definition every time you want to use it. With an alias, you can define the function type once and reuse it wherever needed.
```typescript
type MyFunction = (a: number, b: number) => number;

function createMessage(name: string, score: MyFunction): string {
    return `${name} scored ${score(5, 10)}`;
}
```

## Union Types

Union types allow a variable to hold values of multiple types. You can define a union type using the pipe (`|`) symbol to separate the different types.

```typescript
let userId: string | number;
userId = 'abc123'; // valid
userId = 456; // also valid
```