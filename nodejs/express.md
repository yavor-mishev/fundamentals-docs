# [Express](https://www.npmjs.com/package/express)

Express is a minimal and flexible Node.js web application framework that provides a robust set of features for web and mobile applications. It is widely used for building web servers and APIs.

To use Express in your Node.js project, you first need to install it via npm:

```bash
npm install express
```

Once installed, you can create an Express application by requiring the module and calling the `express()` function:

```javascript
const express = require('express');
const app = express();
```

Now this `app` object has methods for routing HTTP requests, configuring middleware, rendering HTML views, and registering a template engine. For example, you can define routes for different HTTP methods like GET, POST, PUT, and DELETE:

```javascript
app.get();
app.post();
app.put();
app.delete();
```

- `app.get(path, callback)`: the callback (also known as route handler) is invoked when an HTTP GET request is made to the specified path. The callback function receives the request and response objects as arguments. The request object has some useful properties that give us information about the incoming HTTP request. There is no need to memorize all of them, as you can always refer to the [official documentation](https://expressjs.com/en/4x/api.html#req).

## Nodemon

Nodemon is a utility that automatically restarts your Node.js application whenever it detects file changes in the directory. This is particularly useful during development, as it saves you from having to manually stop and restart your server every time you make a change to your code.

If you have been following some tutorial or even this documentation and have tried some of the code examples, you have probably notice that you need to stop and restart the server manually each time you make a change so that change can take effect.

For this reason I recommend you use Nodemone. You can install it globally on your machine using npm:

```bash
npm install -g nodemon
```
Then, instead of starting your application with the `node` command, you can use `nodemon` followed by your entry file:

```bash
nodemon <your-entry-file>
```

if you have installed nodemon locally in your project, you can use `npx` to run it without installing it globally:

```bash
npx nodemon <your-entry-file>
```

## Environment Variables

Environment variables are a way to store configuration settings outside of your code. This is useful for settings that may change between different environments (development, testing, production) or for sensitive information like API keys and database credentials.

One common use of environment variables in Express applications is to define the port number on which the server should listen. Instead of hardcoding the port number in your code, you can use an environment variable to make it configurable.

```javascript
const port = process.env.PORT || 3000;
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
```

You can also set environment variables directly in the command line before starting your application. For example if you'r using a Mac or are running a bash terminal on your windows machine, you can set the `PORT` variable like this:

```bash
export PORT=5000
export PORT=5000 && nodemon app.js
```

## Route Parameters

If we wanted to get a certain course, we could define a route with a route parameter like this:

```javascript
app.get('/api/courses/:id', (req, res) => {
  res.send(req.params.id);
});
```

Instead of `id` you can use any name you want for the route parameter but it is common practice to use names that reflect the data being accessed. In this case, `id` is appropriate because it represents the unique identifier of a course.

### Query String Parameters

Used for additional filtering and sorting options to the request. They are appended to the URL after a question mark (`?`) and are typically in key-value pairs separated by ampersands (`&`).

```javascript
app.get('/api/courses/:id', (req, res) => {
  res.send(req.query);
});
```

## Handling GET Requests

- `app.get(path, callback)`: the callback (also known as route handler) is invoked when an HTTP GET request is made to the specified path. The callback function receives the request and response objects as arguments. The request object has some useful properties that give us information about the incoming HTTP request. There is no need to memorize all of them, as you can always refer to the [official documentation](https://expressjs.com/en/4x/api.html#req).

If there is no route that matches the requested URL, Express will automatically send a 404 Not Found response to the client or we can define our own custom 404 handler like this:

```javascript
app.get('/api/courses/:id', (req, res) => {
  const course = courses.find(c => c.id === parseInt(req.params.id));
  if(!course) res.status(404).send('The course with the given ID was not found!');
  res.send(course);
});
```

## Handling POST Requests

```javascript
app.use(express.json()); // Middleware to parse JSON bodies

app.post('/api/courses', (req, res) => {
  const course = {
    id: courses.length + 1,
    name: req.body.name
  };
  courses.push(course);
  res.send(course);
});
```

## Input Validation

NEVER trust user input. Always validate the data sent by the client before processing it. You can use libraries like [Joi](https://www.npmjs.com/package/joi) to define validation schemas and validate incoming data.

For some simple validation without any external libraries, you can do something like this:

```javascript
app.post('/api/courses', (req, res) => {
  if(!req.body.name || req.body.name.length < 3) {
    res.status(400).send('Name is required and should be minimum 3 characters.');
    return;
  }

  const course = {
    id: courses.length + 1,
    name: req.body.name
  };
  courses.push(course);
  res.send(course);
});
```

Error code 400 indicates a bad request from the client.

For more advanced validation and more complex objects, consider using something like Joi:

```javascript
app.post('/api/courses', (req, res) => {
  const schema = {
    name: Joi.string().min(3).required();
  };
  const result = Joi.validate(req.body, schema);
  if (result.error) return res.status(400).send(result.error.details[0].message);

  const course = {
    id: courses.length + 1,
    name: req.body.name
  };
  courses.push(course);
  res.send(course);
});
```

- first define a schema. This is where you define what the data should look like
- handle errors appropriately by sending a 400 Bad Request response with a descriptive error message if the validation fails

## Handling PUT Requests

```javascript
app.put('/api/courses/:id', (req, res) => {
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if (!course) res.status(404).send(result.error.details[0].message);

    const { error } = Joi.validate(req.body); // object destructuring
    if (error) return res.status(400).send(error.details[0].message);
    
    course.name = req.body.name;
    res.send(course);
});

// Extracted validation function
function validateCourse(course) {
  const schema = {
      name: Joi.string().min(3).required()
  };
  return Joi.validate(course, schema);
}
```

## Handling DELETE Requests

```javascript
app.delete('/api/courses/:id', (req, res) => {
    const course = courses.find(c => c.id === parseInt(req.params.id));
    if (!course) return res.status(404).send("The course with the given ID was not found.");
    const index = courses.inddexOf(course);
    courses.splice(index, 1);
    res.send(course);
});
```
## Summary

Express is a powerful and flexible web framework for Node.js that simplifies the process of building web applications and APIs. It provides a robust set of features for routing, middleware, and handling HTTP requests and responses. By using Express, developers can create scalable and maintainable web applications with ease. It is widely adopted in the Node.js community and has a large ecosystem of plugins and extensions that enhance its functionality.

## Middleware

Middleware functions are functions that have access to the request object (`req`), the response object (`res`), and the next middleware function in the application’s request-response cycle. Middleware can execute code, make changes to the request and response objects, end the request-response cycle, and call the next middleware function.

Request -> [Middleware 1] -> [Middleware 2] -> ... -> [Route Handler] -> Response

It is common to use third-party middleware for tasks such as logging, authentication, and error handling. Some popular middleware packages include `morgan` for logging HTTP requests, `body-parser` for parsing request bodies, and `cors` for enabling Cross-Origin Resource Sharing.

You can also create your own custom middleware functions to handle specific tasks in your application.

Its best practice to organize your middleware functions in separate files or modules to keep your codebase clean and maintainable.

```javascript
// looger.js
function log(req, res, next) {
  console.log(`${req.method} ${req.url}`);
  next();
}

module.exports = log;
```

```javascript
// index.js

const express = require('express');
const app = express();
const logger = require('./logger');
app.use(logger);
```

Its the use() method that adds the middleware to the application. The order in which you add middleware matters, as it determines the sequence in which they are executed.

Two of the functions used in the previos examples where midleware functions: `express.json()` and `route()`. The `express.json()` function is a built-in middleware function in Express that parses incoming JSON requests and puts the parsed data in `req.body`. The `app.use()` function is used to mount middleware functions at a specified path. So in our previos examples, we used `app.use(express.json())` to add the JSON parsing middleware to our application and then we used the route handlers which are also middleware functions to handle specific HTTP requests.