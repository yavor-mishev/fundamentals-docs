# jQuery Fundamentals

Here we'll cover the basics of jQuery and how it is used in Kendo UI. It's essential to understand these concepts as they form the foundation for working with Kendo UI components.

I'll leave a link to the jQuery API documentation here but you can find links to the specific topics in every chapter by clicking on the topic titles. The API documentation is a great resource for understanding the methods and properties available in jQuery.

- [jQuery API Documentation](https://api.jquery.com/)

## Topics Covered

- [What is jQuery?](#what-is-jquery)
- [jQuery syntax](#jquery-syntax)
- What's the `$`?
- The jQuery object
- [Selectors and DOM traversal](#selectors-and-dom-traversal)
- [Core jQuery methods](#core-jquery-methods)
- [DOM manipulation](#dom-manipulation)
- [Events](#events)
- [Event delegation](#event-delegation)
- The `this` keyword in jQuery
- Chaining methods
- AJAX with jQuery
- [jQuery plugins](#jquery-plugins)

## [What is jQuery?](https://learn.jquery.com/about-jquery/)

jQuery is a fast, small, and feature-rich JavaScript library. It simplifies HTML document traversal and manipulation, event handling, and animation, making it easier to develop interactive web applications. jQuery is essentially a wrapper around JavaScript that provides a more convenient API for common tasks like selecting elements, handling events, and making AJAX requests.

```javascript
// Example of using jQuery to select an element and change its text
$(document).ready(function () {
  $('#myElement').text('Hello, jQuery!');
});
```

## [jQuery Syntax](https://learn.jquery.com/about-jquery/how-jquery-works/)

jQuery uses a simple syntax that allows you to select elements and perform actions on them. The basic syntax is:

```javascript
$(selector).action('parameters');
```

Where `selector` is a string that represents a CSS selector (id, class, element, or even more sophisticated selectors) and identifies the HTML elements you want to select, and `action` is a jQuery method that performs an operation on those elements. We'll talk about jQuery methods later.

It's important to include all of your code inside a `$(document).ready()` function to ensure that the DOM is fully loaded before your code runs. This prevents errors that occur when trying to manipulate elements that are not yet available in the DOM. An example of this can be seen in the code snippet above and you will definitely see it further down in the documentation as well.
You can also use the shorthand version of the command like this:

```javascript
$(function () {
  $('#myElement').text('Hello, jQuery!');
});
```

## What's the `$`?

The `$` is a shorthand alias for the [`jQuery()` function](https://api.jquery.com/jQuery/). It is used to access jQuery's functionality and is commonly used to select elements and perform actions on them. `$()` and `jQuery()` are equivalent, so you can use either one interchangeably.

## The jQuery Object

When you use the `$()` function to select elements, it returns a `jQuery object`. This object is a collection of DOM elements that match the specified selector (this could be one or more DOM elements or 0 if none match the specified CSS selector). The jQuery object provides various methods for manipulating the selected elements, handling events, and performing animations.

```
// HTML
<button>Save</button>
<button>Export</button>

// JavaScript
let buttons = $('button'); // Select all button elements

// eq() method to get the button at a specific index
let firstButton = buttons.eq(0); // get first button

// get() method to get the raw DOM element at a specific index
let firstButtonEl = buttons.get(0);
firstButtonEl = buttons[0];
```

Its important to remember that jQuery objects are not equal even is they contain the same element(s). For example:

```javascript
let $firstButton = $('button').eq(0);
let $anotherFirstButton = $('button').eq(0);

alert($firstButton === $anotherFirstButton); // false
```
(Dont pay too much attention to the `$` in the variable names, its just a convention to indicate that these variables hold jQuery objects)

But their underlying DOM elements are equal:

```javascript
let firstButtonEl = $('button').eq(0).get(0);
let anotherFirstButtonEl = $('button').eq(0).get(0);
alert(firstButtonEl === anotherFirstButtonEl); // true
```

### jQuery objects are not "live"
A jQuery object is a snapshot of the DOM at the time it was created. If the DOM changes after the jQuery object is created, the jQuery object will not automatically reflect those changes. You would need to create a new jQuery object to get the updated elements.

## Selectors and DOM Traversal

### [Selectors](https://learn.jquery.com/using-jquery-core/selecting-elements/)

jQuery provides a powerful set of selectors that allow you to select elements based on their id, class, tag name, attributes, and more. Here are some common selectors:

```javascript
// Select by id
$('#myId');

// Select by class
$('.myClass');

// Select by tag name
$('div');

// Select by attribute
$("[data-attribute='value']");

// Select all paragraphs
$('p');

// Select all elements with a specific attribute
$("[data-role='widget']");

// Select all elements that are children of a specific element
$('#parent > .child');

// Select all elements that match a specific CSS selector
$('.myClass .nestedElement');
```

> Just remember that jQuery selectors are based on CSS selectors, so you can use any valid CSS selector to select elements. If you dont feel fully comfortable with CSS selectors: <br> > [w3schools](https://www.w3schools.com/cssref/css_selectors.php) <br> > [MDN Web Docs](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Selectors) <br> > [CSS Tricks](https://css-tricks.com/css-selectors/) <br>

### [DOM Traversal](https://learn.jquery.com/using-jquery-core/traversing/)

Here I'll just mention that jQuery provides methods for traversing the DOM, allowing you to navigate through elements **in relation to each other**. For example, you can use methods like `.parent()`, `.children()`, `.siblings()`, and `.find()` to navigate the DOM tree. For more details and examples check the documentation linked in the title.

## jQuery Methods

jQuery provides a wide range of methods for manipulating the DOM, handling events, and performing animations. Here are some of the most commonly used methods:

```javascript
// DOM Manipulation
$('#myElement').text('New Text'); // Change text
$('#myElement').css('color', 'red'); // Change CSS
$('#myElement').append('<p>New Paragraph</p>'); // Add new element

// Event Handling
$('#myButton').click(function () {
  alert('Button clicked!');
});

// AJAX
$.ajax({
  url: 'https://api.example.com/data',
  method: 'GET',
  success: function (data) {
    console.log(data);
  },
});
```

### [DOM Manipulation](https://learn.jquery.com/using-jquery-core/manipulating-elements/)

- [API Documentation](https://api.jquery.com/category/manipulation/)

All of the methods in this section and in the documentation manipulate the DOM in some manner. Some of them simply change one of the attributes of an element, while others set an element’s style properties. For the full list of methods and their descriptions, refer to the API documentation linked above.

```javascript
// Change text
$('#myElement').text('New Text');

// Change CSS
$('#myElement').css('color', 'red');

// Add new element
$('#myElement').append('<p>New Paragraph</p>');

// Remove element
$('#myElement').remove();

// Replace element
$('#myElement').replaceWith('<div>New Element</div>');

// Get HTML content
$('#myElement').html();

// Set HTML content
$('#myElement').html('<p>New HTML Content</p>');

// Get or set attributes
$('#myElement').attr('data-role', 'widget'); // Set attribute
$('#myElement').attr('data-role'); // Get attribute

// Get or set data attributes
$('#myElement').data('key', 'value'); // Set data attribute
$('#myElement').data('key'); // Get data attribute

// Add or remove classes
$('#myElement').addClass('newClass'); // Add class
$('#myElement').removeClass('oldClass'); // Remove class

// Toggle class
$('#myElement').toggleClass('active');

// Clone element
var clonedElement = $('#myElement').clone();

// Wrap element
$('#myElement').wrap('<div class="wrapper"></div>');
```

> **Note:** jQuery methods typically return a jQuery object, allowing for method chaining. For example, you can do `$('#myElement').addClass('newClass').css('color', 'red');` to add a class and change the color on one line.

> **Note:** Some methods, like `text()`, `html()`, and `css()`, can be used to get or set values. If you provide a value as an argument, it sets the value; if you invoke the method without arguments, it retrieves the current value.

### [Events](https://learn.jquery.com/events/introduction-to-events/)

- [API Documentation](https://api.jquery.com/category/events/)

Events are probably one of the most important aspects of jQuery and web development in general. JavaScript is an event-driven language, meaning that it responds to user interactions like clicks, key presses, and form submissions. jQuery simplifies event handling by providing methods to attach event listeners to elements.
Down bellow are some common event methods but do check the API documentation for a full list of events and their descriptions.

```javascript
// Click event
$('#myButton').click(function () {
  alert('Button clicked!');
});

// Mouseover event
$('#myElement').mouseover(function () {
  $(this).css('background-color', 'yellow');
});

// Mouseout event
$('#myElement').mouseout(function () {
  $(this).css('background-color', '');
});

// Keydown event
$(document).keydown(function (event) {
  console.log('Key pressed:', event.key);
});

// Form submit event
$('#myForm').submit(function (event) {
  event.preventDefault(); // Prevent default form submission
  alert('Form submitted!');
});

// Change event for input fields
$('#myInput').change(function () {
  console.log('Input changed:', $(this).val());
});

// Focus event
$('#myInput').focus(function () {
  $(this).css('border', '2px solid blue');
});

// Blur event
$('#myInput').blur(function () {
  $(this).css('border', '');
});
```

> **Note:** As of jQuery 3.0, the `.on()` method is the preferred way to attach event handlers. It allows for more flexibility and supports [event delegation](#event-delegation). All other event methods (like `.click()`, `.mouseover()`, etc.) are shorthand for `.on()` and are called **convenience methods**. For example, you can use:

```javascript
$('#myElement').on('click', function () {
  alert('Element clicked!');
});
```

The main takeaway here is that every event method boils down to the `.on()` method. So you can use it for all events. More on the `on()` method [here](https://api.jquery.com/on/#on-events-selector-data-handler).

#### [Event Delegation](https://learn.jquery.com/events/event-delegation/)

Event delegation allows us to attach a single event listener, to a parent element, that will fire for all descendants matching a selector, whether those descendants exist now or are added in the future.

I suggest you read the [Event Delegation](https://learn.jquery.com/events/event-delegation/) article in the jQuery documentation for a more detailed explanation and examples.

## jQuery Plugins

There is a very well written article about jQuery plugins in the official documentation that I suggest you read: [jQuery Plugins](https://learn.jquery.com/plugins/basic-plugin-creation/). There you will see how a plugin is created and why we would want to use them.

Kendo widgets are jQuery plugins. You can initialize a Kendo widget on a jQuery object like this:

```javascript
$('#myElement').kendoButton({
  text: 'Click Me',
  click: function () {
    alert('Button clicked!');
  },
});
```

In the article above the code snippet you will see that for more complex plugins we have the option to pass options to the plugin during initialization. This is exactly what we do when initializing Kendo widgets. The object we pass to the widget contains configuration options and event handlers.