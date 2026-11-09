# MVVM (Model-View-ViewModel)

## What is MVVM?

**MVVM (Model-View-ViewModel)** is a software design pattern that helps developers separate the **Model** (data) from the **View** (user interface), with a **ViewModel** acting as an intermediary that handles the presentation logic and data binding.

### The Three Components

```
┌─────────┐         ┌──────────────┐         ┌──────┐
│  Model  │ ◄────── │  ViewModel   │ ◄────── │ View │
│  (Data) │         │ (Logic/State)│         │ (UI) │
└─────────┘         └──────────────┘         └──────┘
```

1. **Model**: Your raw data (objects, arrays, business entities)
2. **ViewModel**: An observable representation of your data that the View binds to
3. **View**: The HTML/UI that displays the data and captures user interactions

### Why Use MVVM?

- **Separation of Concerns**: Business logic is separated from UI code
- **Automatic Synchronization**: Changes in the ViewModel automatically update the View, and vice versa
- **Testability**: ViewModels can be tested without the UI
- **Maintainability**: Easier to modify UI or business logic independently
- **Declarative Binding**: Less imperative DOM manipulation code

---

## Core Concepts

### Observable Objects

The key to MVVM is **observability**. An observable object tracks changes to its properties and notifies subscribers (like the View) when those properties change.

#### Without Observables (Traditional Approach)
```javascript
// Manual DOM manipulation
var user = { name: "John" };
document.getElementById("userName").textContent = user.name;

// When updating, you must manually update both the model and the DOM
user.name = "Jane";
document.getElementById("userName").textContent = user.name; // Manual update required
```

#### With Observables (MVVM Approach)
```javascript
// Automatic synchronization
var viewModel = kendo.observable({
    name: "John"
});

kendo.bind($("#view"), viewModel);

// When updating, only change the ViewModel - the View updates automatically
viewModel.set("name", "Jane"); // UI updates automatically!
```

### Data Binding

Data binding is the mechanism that connects the View to the ViewModel. When you declare a binding in your HTML using `data-bind` attributes, you create a two-way connection:

- **View → ViewModel**: User interactions update the ViewModel
- **ViewModel → View**: ViewModel changes update the UI

---

## Simple Examples

### Example 1: Basic Text Binding

The simplest MVVM example - displaying and editing a value.

```html
<!DOCTYPE html>
<html>
<head>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://kendo.cdn.telerik.com/2023.3.1010/js/kendo.all.min.js"></script>
</head>
<body>
    <div id="view">
        <h2>Hello, <span data-bind="text: name"></span>!</h2>
        <input data-bind="value: name" placeholder="Enter your name" />
    </div>

    <script>
        // Step 1: Create the ViewModel
        var viewModel = kendo.observable({
            name: "John Doe"
        });

        // Step 2: Bind the View to the ViewModel
        kendo.bind($("#view"), viewModel);
    </script>
</body>
</html>
```

**What happens:**
- The `<span>` displays the value of `viewModel.name`
- The `<input>` is bound to `viewModel.name`
- When you type in the input, the span updates automatically
- If you change `viewModel.name` from code, both the span and input update

### Example 2: Click Event Binding

Handling user interactions through the ViewModel.

```html
<div id="view">
    <p>Count: <span data-bind="text: count"></span></p>
    <button data-bind="click: increment">Increment</button>
    <button data-bind="click: reset">Reset</button>
</div>

<script>
    var viewModel = kendo.observable({
        count: 0,
        
        increment: function() {
            // Use get() and set() methods for observability
            var currentCount = this.get("count");
            this.set("count", currentCount + 1);
        },
        
        reset: function() {
            this.set("count", 0);
        }
    });

    kendo.bind($("#view"), viewModel);
</script>
```

### Example 3: Conditional Visibility

Showing/hiding elements based on ViewModel state.

```html
<div id="view">
    <input type="checkbox" data-bind="checked: showDetails" /> Show Details
    
    <div data-bind="visible: showDetails">
        <h3>Detailed Information</h3>
        <p>This content is only visible when the checkbox is checked.</p>
    </div>
    
    <div data-bind="invisible: showDetails">
        <p>Check the box to see more details.</p>
    </div>
</div>

<script>
    var viewModel = kendo.observable({
        showDetails: false
    });

    kendo.bind($("#view"), viewModel);
</script>
```

### Example 4: Computed Properties (Dependent Methods)

Creating derived values that automatically update when their dependencies change.

```html
<div id="view">
    <p>First Name: <input data-bind="value: firstName" /></p>
    <p>Last Name: <input data-bind="value: lastName" /></p>
    <h2>Full Name: <span data-bind="text: fullName"></span></h2>
</div>

<script>
    var viewModel = kendo.observable({
        firstName: "John",
        lastName: "Doe",
        
        // Computed property - automatically updates when firstName or lastName changes
        fullName: function() {
            // IMPORTANT: Must use this.get() to track dependencies
            return this.get("firstName") + " " + this.get("lastName");
        }
    });

    kendo.bind($("#view"), viewModel);
</script>
```

**Critical Note**: Always use `this.get("propertyName")` inside computed functions, not direct property access (`this.propertyName`). Only `get()` tracks dependencies and triggers updates.

### Example 5: Working with Collections

Binding to arrays and displaying lists.

```html
<div id="view">
    <ul data-bind="source: products" data-template="product-template"></ul>
    <button data-bind="click: addProduct">Add Product</button>
</div>

<script id="product-template" type="text/x-kendo-template">
    <li>#= name # - $#= price #</li>
</script>

<script>
    var viewModel = kendo.observable({
        products: [
            { name: "Coffee", price: 5.50 },
            { name: "Tea", price: 4.00 },
            { name: "Juice", price: 6.00 }
        ],
        
        addProduct: function() {
            // Add to observable array
            this.products.push({
                name: "New Product",
                price: 10.00
            });
        }
    });

    kendo.bind($("#view"), viewModel);
</script>
```

---

## Kendo UI MVVM

How the pattern is implemented in Kendo UI:

- [Kendo UI MVVM & Data Bindings](kendo-mvvm.md)
- [Kendo UI Widgets & Advanced Patterns](kendo-widgets.md)
- [Kendo MVVM Best Practices](kendo-best-practices.md)
