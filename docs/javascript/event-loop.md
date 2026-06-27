# Event Loop

JavaScript is a single threaded language, meaning it can only execute one piece of code at a time. However, it uses an event loop to handle asynchronous operations, allowing it to perform non-blocking tasks.

## Synchronous Programming
In synchronous programming, tasks are executed one after another. Each task must complete before the next one starts. This can lead to blocking behavior, where long-running tasks prevent other code from executing.

The following code snippet demonstrates synchronous behavior:

```javascript
function getPizza(){
    return "🍕";
}

const pizza = getPizza();
console.log(pizza);
```

resources:
- [ColorCode](https://www.youtube.com/watch?v=okkHnAo8GmE)

Call Stack: Last In First Out (LIFO)
Task Queue: First In First Out (FIFO). Stores async callbacks ahead of Call Stack.
Microtask Queue: Higher priority than Task Queue. Used for promises and mutation observers.
Event Loop: Continuously checks if the Call Stack is empty. If it is, it processes the next task from the Task Queue or Microtask Queue.
