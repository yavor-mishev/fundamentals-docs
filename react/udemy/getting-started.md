# React

React is a popular JavaScript library for building user interfaces, particularly single-page applications. It allows developers to create reusable UI components and manage the state of their applications efficiently.

React is a declarative, component-based library that focuses on the view layer of an application. It enables developers to build complex UIs by breaking them down into smaller, manageable components. The idea is that we descrive what we want the UI to look like, and React takes care of updating the DOM to match that description. In contrast, with vanilla JS we have to tell the browser step by step what to do (imperative programming).

**declarative** - define the goal, not the steps to get there
**imperative** - define the steps, not the goal

```jsx
// Declarative approach
let content;
if (user.isLoggedIn) {
  content = <button>Continue to dashboard</button>;
} else {
  content = <button>Log in</button>;
}

return content;
```

```jsx
// Imperative approach
let content;
if (user.isLoggedIn) {
  button.textContent = 'Continue';
} else {
  button.textContent = 'Log in';
}

document.body.append(button);
```

### Getting Started with React

To write raw React code, you need to set up a development environment.The reason for this is because when developing with react you write code in JSX (JavaScript XML) which is a syntax extension for JavaScript that allows you to write HTML-like code within your JavaScript files. Browsers do not understand JSX natively, so we need a build tool to transpile JSX into regular JavaScript that browsers can execute. An example of such a build tool is **Vite**, which is a fast build tool that provides a development server, handles the transpilation of JSX code and gives us a lot of other features to make development easier like HMR (Hot Module Replacement), build optimizations, and more.

To get started with React using Vite, follow these steps:
1. **Install Node.js**: Make sure you have Node.js installed on your machine. You can download it from [nodejs.org](https://nodejs.org/).
2. **Create a new Vite project**: Open your terminal and run the following command:
   ```bash
   npm create vite@latest my-react-app -- --template react
   ```
   This command creates a new Vite project named `my-react-app` using the React template.