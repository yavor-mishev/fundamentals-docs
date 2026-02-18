# React Essentials

React is a powerful JavaScript library for building user interfaces. To effectively use React, it's important to understand its core concepts, including components, JSX, and state management. To compare it with vanilla JS we can think of them like this: with vanilla JS we manipulate the DOM directly, while with React we describe what the UI should look like and let React handle the DOM updates. These two approaches are known as **imperative** programming (vanilla JS) and **declarative** programming (React).

## Components

Components are the building blocks of a React application. They are reusable pieces of UI that can be composed together to create complex user interfaces. Components can be defined as functions or classes, but functional components are more common in modern React development.

```jsx
function Header() {
	return <h1>Welcome to My React App</h1>;
}
```

The idea behaind components is to break down the UI into smaller, manageable pieces that can be developed, tested, and maintained independently. Each component can have its own state and props (properties) that allow it to manage its own data and behavior.

### Dynamic content

One of the most important ideas behind creating dynamic web applications is to, well... create dynamic content. One of the simplest ways to achiev this in React is to include JavaScript expressions inside JSX using curly braces `{}`.

```jsx
function Greeting() {
	const name = "Alice";
	return <h1>Hello, {name}!</h1>;
}
```

You can imagine these curly braces as a way to "escape" from the HTML-like syntax of JSX back into regular JavaScript. This allows you to include variables, function calls, and any other JavaScript expressions directly within your JSX code.

This syntax can also be used when setting up attributes for HTML elements in JSX. Say you want to set the `src` attribute of an `img` element dynamically. Of course you can add it directly as a string, but this approach is not recommended since this path might get lost in the build process or you might want to change it later on. So thge best way to di it is to import the image and set the `src` attribute using curly braces:

```jsx
import profilePic from "./profile.jpg";

function Profile() {
	return <img src={profilePic} alt="Profile Picture" />;
}
```

### Props

Props allow us to pass data from a parent component to a child component. They are similar to function arguments and enable components to be more dynamic and reusable.

```jsx
function Greeting(props) {
	return <h1>Hello, {props.name}!</h1>;
}
```

By default, every component in React can receive a single argument called `props`, which is an object containing all the properties passed to that component. You can then access these properties using dot notation, like `props.name` in the example above.

When using the `Greeting` component, you can pass different names as props:

```jsx
<Greeting name="Alice" />
<Greeting name="Bob" />
```

Its very common to use destructuring to extract specific props directly in the function signature. And in general destructuring is a widely used technique in modern JavaScript to make code cleaner and more readable. Here's how you can do it:

```jsx
function Greeting({ name, age }) {
	return (
		<h1>
			Hello, my name is {name}! I am {age} years old
		</h1>
	);
}
```

## JSX

JSX (JavaScript XML) is a syntax extension for JavaScript that allows you to write HTML-like code within your JavaScript files. It makes it easier to create and visualize the structure of your UI components. Its important to remember that you are not obliged to use JSX in React, but its highly recommended as it improves code readability and developer experience. React components can be written using plain JS as well, but JSX is the preferred way.
