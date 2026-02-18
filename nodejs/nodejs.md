# NodeJS

Creator - Ryan Dahl

NodeJS is a C++ program that wraps the **Chrome v8 engine** and makes it possible to run JavaScript outside of the browser. That makes NodeJS essentially a runtime enviroment for running JavaScript outside a web browser. _Before Node we could only run JS in the browser._

We use Node often to create back-end services (a.k.a API's - **A**pplication **P**rogramming **I**nterface).

Node also provides certain objects that we can use but they differ greatly from the objects we have access to from the browser. In the browser we have access to the `window` object, `document` object that we use to manipulate the DOM etc.

Node gives us objects that help us work with the **file system (fs)**, listen for **requests (http)** on a given port, etc.

# Global object

The `global` object in NodeJS is the equivilent of the `window` object in the browser. However there are some differences between the two.

## `window`

- represents the global object in a browser enviroment. All the variables and functions that are defined globally can be accessed through the `window` object.

  ```javascript
  window.console.log("Hello!");
  // or simply
  console.log();
  // The browser engine will prefix this with the window object.
  let name = "Dancho";
  window.name;
  function sayHello(name) {
    console.log(`Hello, ${name}!`);
  }
  window.sayHello("Yavor"); // Hello, Yavor!
  ```

## `global`

- globally pre-defined functions and variables are accessible through the global object.

  ```javascript
  global.console.log(`Hello world!`);
  // or simply
  console.log(`Hello world`);
  ```

- but for varaibles and functions that are defined by us the behavior is not the same. They are not added to the global object, hence we cannot access them through `global`.

  ```javascript
  let name = "Goergi";
  console.log(global.name); // undefined
  ```

  Variables and functions are only scoped to the file in which they were declared. This is due to the [node modular system](#modules).

  It is possible to add members (variables and functions) to the `global` object but it is not recommended.

  ```javascript
  // not recommended
  global.name = "Peter";
  console.log(name);
  ```

# Modules

Every file in NodeJS is considered a separate node module. Every variable and function defined in a node module is encapsulated (scoped, pravate) within that module and are not accessible outside it. In order to use a member outside of their module you would need to **explicitly export** them (make them public).

> **Note:** Every NodeJS project has a 'main' module. You can think of it as an entry point to the project just like we have a `main()` function in C++.

## The module object

Every node module in NodeJS has its own **module** object which contains metadata for the current file: id, exports, parent, filename, etc. This **module** object is not globally defined hence is not accessible from the **global** object.

It might seem as if it is a member of the **global** object because we dont need to use a prefix before it but this is because it is one of the arguments to the **IIFE** (**I**mmediatly **I**nvoked **F**unction **E**xpression) that encapsuates the whole code of every node module under the hood. More on this [later](#module-wrapper-function).

## Creating and exporting a node module

Creating a node module in NodeJS is as simple as creating a new .js file. Like I mentioned above: every .js file in a Node project is essentially a node module.

After you have defined a couple of variables and functions you might wonder how you can expose them to the outside world (other node modules). In the **module** object of every node module you have an empty **exports** object. Simply add the functions and variable that you would like to expose to that object:

```javascript
// logger.js
let url = "http://mylogger.io/log";

function log(message) {
  // Send an HTTP request
  console.log(message);
}

module.exports.log = log; // just like adding a method to a JS object
```

Everything added to the **exports** object will be available outside the node module. Of course you can rename these variables and functions to be whatever you like.

```javascript
let name = "Nicole";
module.exports.fistName = name;
```

Now when you `console.log(module)` you will see that we have populated the **exports** object.

```bash
exports {
   log: [Function: log],
   firstName: 'Nicole',
}
```

If you dont want export a single function within an object just assign the function to the **exports** object. Now **exports** is not an object that contains ther function `log()` but rather just the function `log()` itself.

```javascript
// logger.js
module.exports = log;

// app.js
const logger = require("./logger.js");
loggers("Hello from logger.js!"); // now logger is just a fuinction and not an object
```

Leaving the **exports** object an actual object is useful when we want to export multiple members.

## Loading a module

Loading `logger.js` into another node module (`app.js`) is as simple as this one line of code:

```javascript
// app.js
require("./logger.js");
```

The `require()` function returns the object (**exports**) that is exported from the target node module. Now we can assign this object function to a variable.

```javascript
// app.js
const logger = require("./logger.js");
console.log(logger); // { log: [Function: log] }
logger.log("Hello from logger.js!"); // Hello from logger.js!
```

It is best practice when assigning the `require()` function to a variable, that variable to be a constant. The idea behind this is to not overwrite the value of the **logger** variable down the road.

```javascript
let logger = require("./logger.js");
logger = 1;
logger.log(`Hello from logger.js!`); // TypeError: logger.log is not a function.
```

The same but with a constant

```javascript
const logger = require("./logger.js");
logger = 1;
logger.log(`Hello from logger.js!`); // TypeError: Assignment to constant variable.
```

> Tip: there are tools that check your JavaScript code for errors like that: [**JSHint**](https://jshint.com/docs/)

## Module wrapper function

The code in a node module does not run directly. It is wrapped in an **I**mmediatly **I**nvoked **F**unction **E**xpression (IIFE).

```javascript
(function (exports, require, module, __filename, __dirname) {
  /*node module code here*/
});
```

Now you can see why **require()** and **module** look like they are 'globally' accessible. You can also see the **exports** object there. This means that we can also use it as if it was 'globally' accessible.

```javascript
module.exports.log = log;
// or simply
exports.log = log;
```

The only quirk to this approach is that you cannot do what we did earlier when we assigned our function directly to the **exports** object. This is because just **exports** is a reference to **module.exports**.

```javascript
module.exports.log = log; // OK
exports.log = log; // OK
exports = log; // Not OK
```

- **\_\_filename** - returns the full path of the node module.
- **\_\_dirname** - returns the path up until the node module.

## Node built-in modules

[API Documentation](https://nodejs.org/docs/latest/api/)

- [File System](#file-system)
- HTTP - used to make web servers that listen for HTTP requests
- [OS](#os)
- [Path](#path)
- Process
- Query String
- Stream
- etc.

### [Path](https://nodejs.org/docs/latest/api/path.html)

The `node:path` module provides utilities for working with file and directory paths. It can be accessed using:

```javascript
const path = require("path");
```

Example:

```javascript
// app.js
const path = require("path");

let pathObj = path.parse(__filename);
console.log(pathObj);
/*
{
  root: '/',
  dir: '/home/yavor.Documents/Dev/repositories/docs/fundamentals/projects/node-web-server',
  base: 'app.js',
  ext: '.js',
  name: 'app',
}
*/
```

### [HTTP](https://nodejs.org/docs/latest/api/http.html)

The `node:http` module helps us for instance to create a server amd make it listen to a specific port. It can be accessed using:

```javascript
const http = require("http");
```

Important methods:
- `createServer([options], requestListener)` - creates an HTTP server that listens for requests on a given port.

```javascript
  const http = require("http");

  const server = http.createServer();

  server.on("connection", (socket) => {
    console.log("New connection on", socket);
  });

  server.listen(3000);
  console.log("Listening on port 3000...");
```

This approach is very low level. With the built in HTTP module you can also handle requests and responses.

```javascript
  const http = require("http");

  const server = http.createServer((req, res) => {
    if (req.url === "/") {
      /* handle request for root URL */
      res.write("Hello world");
    }
    if (req.url === "/courses") {
      /* handle request for /courses URL */
      res.write("This is the courses page");
    }
  });
```

In real world applications you would use a framework like [Express](./express.md) that is built on top of the HTTP module and makes it easier to work with. Imagine having to handle all the different HTTP methods (GET, POST, PUT, DELETE, etc.) and status codes on your own. Not to mention if you had 100's of different routes to handle you would need 100's of `if` statements.

- `listen(port, [hostname], [backlog], [callback])` - binds and listens for connections on the specified host and port.

```javascript
  server.listen(3000);
  console.log("Listening on port 3000...");
```

### [OS](https://nodejs.org/docs/latest/api/os.html)

The `node:os` module provides operating system related utility methods and properties. It can be accessed using:

```javascript
const os = require("os");
```

Example:

```javascript
const os = require("os");

let totalMemory = os.totalmem();
let freeMemory = os.freemem();

console.log(`Free memory: ${freeMemory} \n Total memory: ${totalMemory}.`);
```

### [File System](https://nodejs.org/docs/latest/api/fs.html)

The `node:fs` module enables interacting with the file system in a way modeled on standard POSIX functions.

```javascript
const fs = require("fs");
```

> Important: Every (or most) methods of the FS Node module have a Sync (synchronus) and an Async (asyncronus) version. You'll be using mostly the Async (non-blocking) version. The other important difference between both is that the async versions of these methods require a second parameter: a callback function.

- `readdir()` - returns an array with all the files in the current directory

  - sync version

  ```javascript
  const files = fs.readdirSync("./");
  console.log(`Files: ${files}`); // Files: app.js,docs.md,logger.js,package.json,server.js
  ```

  - async version

  ```javascript
  fs.readdir("./", function (err, files) {
    if (err) console.log(err);
    else console.log(`Files: ${files}`);
  });
  ```

  ```javascript
  // with an intetional error
  fs.readdir("$", function (err, files) {
    if (err) console.log(err);
    else console.log(`Files: ${files}`);
  });
  // [Error: ENOENT: no such file or directory, scandir '$']...
  ```

### [Events](https://nodejs.org/api/events.html)

Much of the NodeJS core API is built around an idiomatic asynchronous event-driven architecture in which certain kinds of objects (called **emitters**) emit named events that cause Function objects (**listeners**) to be called.

Unlike the built-in node modules we have looked at up until now, the `require('events')` function does'nt return an object. It returns a class.

```javascript
const EventEmitter = require("events"); // class
const emitter = new EventEmitter(); // instance of the class (object)
```

**EventEmitter** is just one of the classes the event node module provides.

Now we can access all the members of the class via the `emitter` object. We have access to a few methods but you will be using mostly two of them: `emit()` and `addListener()` / `on()`

- `emit(eventName, args)` - used to raise an event

> Note: this is the equivilent to the `trigger()` method in jQuery.

```javascript
const EventEmitter = require("events");
const emitter = new EventEmitter();

// Raise an event
emitter.emit("messageLogged");
```

- `addListener(eventname, callback)` / `on(eventName, callback)`

> Note: I'll be using `on()` from now on because of the jQuery connection.

```javascript
const EventEmitter = require("events");
const emitter = new EventEmitter();

// Register a listener
emitter.on("messageLogged", function (e) {
  /* execte this callback function anytime the event is fired */
});

// Raise an event
emitter.emit("messageLogged");
```

#### Extending the EventEmitter class

In the real world it's quite rare that you will be working with the **EventEmitter** like this. instead you will want to create a class that has all the functionality of the **EventEmitter** class and add your own functionalities to it. This is called _extending_ a class.

Lets say we have the following setup:

```javascript
// app.js - entry point to our project
const EventEmitter = require("events");
const emitter = new EventEmitter();

// Register a listener
emitter.on("messageLogged", function (e) {
  console.log(`Listener called: ${e}`);
});

// Raise an event
emitter.emit("messageLogged");
```

```javascript
// logger.js
let url = "http://mylogger.io/log";

function log(message) {
  // Sent an HTTP request
  console.log(message);
}

module.exports = log;
```

In this situation we would want to raise an event in the `log()` function in the `logger.js` node module (not in `app.js`) and setup a listener in the `app.js` node module. For this to happen:

1. **First** we would need to create an **emitter** object so we can use the `emit()` method:

```javascript
// logger.js
const EventEmitter = require("events");
const emitter = new EventEmitter();

let url = "http://mylogger.io/log";

function log(message) {
  console.log(message);

  // Raise an event
  emiiter.emit("messageLogged", { id: 1, url: "http://" });
}

module.exports = log;
```

2. **Second** we would need to load the `logger.js` node module in `app.js` and call the `log()` function:

```javascript
// app.js
const EventEmitter = require("events");
const emitter = new EventEmitter();

// Register a listener
emitter.on("messageLogged", function (e) {
  console.log(`Listener called: ${e}`);
});

const log = require("./logger.js");
log("message");
```

Now if we run **node app.js** in the terminal we will see the result of the `log()` function but wont get the result of the callback function in the event listener. Why? We are creating an **emitter** object both in `app.js` and `logger.js`. These two _instances_ of the same class are two separate objects and have nothing to do with eachother. One is just emitting an event the other is just listening for one.

The correct way to implement this logic is to have one emitter that emits and listend for an event:

```javascript
// logger.js
const EventEmitter = require("events");

let url = "http://mylogger.io/log";

class Logger extends EventEmitter {
  log(message) {
    // Send an HTTP request
    console.log(message);

    // Raise an event
    this.emit("messageLogged", { id: 1, url: "http://mylogger.io/log" });
  }
}

module.exports = Logger;
```

```javascript
// app.js
const EventEmitter = require("events");
const Logger = require("./logger.js");
const logger = new Logger();

logger.on("messageLogged", function (e) {
  console.log("Listener called", e);
});

logger.log("message");
```

We are creating a new class `Logger` that **extends** the **EventEmitter** class. The **extends** keyword is available as of ES6. Now this class `Logger` has all the functionality of the **EventEmitter** class plus the `log()` method (when a function is a class member we call it a method).

Then in `app.js` we create a `logger` object from the `Logger` class and both emit and listen for the same event.

Running the node comand now will give us the following result:

```bash
message
Listener called: { id: 1, url: 'http://mulogger.io/log'}
```
