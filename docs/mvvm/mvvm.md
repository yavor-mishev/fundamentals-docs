# MVVM (Model-View-ViewModel)

## Table of Contents
1. [What is MVVM?](#what-is-mvvm)
2. [Core Concepts](#core-concepts)
3. [Simple Examples](#simple-examples)
4. [Kendo UI MVVM Implementation](#kendo-ui-mvvm-implementation)
5. [Data Bindings](#data-bindings)
6. [Working with Kendo UI Widgets](#working-with-kendo-ui-widgets)
7. [Advanced Patterns](#advanced-patterns)
8. [Best Practices](#best-practices)

---

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

## Kendo UI MVVM Implementation

Kendo UI provides a complete MVVM framework that seamlessly integrates with its widgets. The core of this implementation is the `kendo.data.ObservableObject` class.

### Creating Observable Objects

There are two ways to create observable objects in Kendo UI:

```javascript
// Method 1: Using kendo.observable() - Recommended
var viewModel1 = kendo.observable({
    field1: "value1",
    field2: "value2"
});

// Method 2: Using new kendo.data.ObservableObject()
var viewModel2 = new kendo.data.ObservableObject({
    field1: "value1",
    field2: "value2"
});

// Both produce the same result
```

**Best Practice**: Always use `kendo.observable()` even if you plan to use the ViewModel immediately. This ensures proper change tracking.

### Getting and Setting Values

Observable objects use `get()` and `set()` methods instead of direct property access to maintain change tracking.

```javascript
var viewModel = kendo.observable({
    name: "John Doe",
    age: 30,
    person: {
        address: "123 Main St"
    }
});

// Getting values
var name = viewModel.get("name");           // "John Doe"
var age = viewModel.get("age");             // 30
var address = viewModel.get("person.address"); // Nested property

// Setting values
viewModel.set("name", "Jane Doe");          // Updates and notifies bindings
viewModel.set("age", 31);
viewModel.set("person.address", "456 Oak Ave"); // Nested property
```

### Observable Arrays

Arrays in Kendo UI observables have special methods for change tracking:

```javascript
var viewModel = kendo.observable({
    items: ["Apple", "Banana", "Cherry"]
});

// Array methods that trigger updates
viewModel.items.push("Date");           // Add to end
viewModel.items.pop();                  // Remove from end
viewModel.items.unshift("Apricot");     // Add to beginning
viewModel.items.shift();                // Remove from beginning
viewModel.items.splice(1, 1, "Blueberry"); // Replace/insert

// Get array length
var count = viewModel.items.length;
```

### Handling Events

Observable objects raise a `change` event when their properties are modified:

```javascript
var viewModel = kendo.observable({
    name: "John"
});

// Subscribe to changes
viewModel.bind("change", function(e) {
    console.log("Changed field:", e.field);
    console.log("New value:", this.get(e.field));
});

viewModel.set("name", "Jane"); 
// Console: "Changed field: name"
// Console: "New value: Jane"
```

---

## Data Bindings

Kendo UI MVVM supports a wide variety of bindings through the `data-bind` attribute. Here are the most commonly used bindings:

### Value Binding

Binds form element values to ViewModel properties (two-way binding).

```html
<div id="view">
    <!-- Input field -->
    <input data-bind="value: userName" />
    
    <!-- Textarea -->
    <textarea data-bind="value: description"></textarea>
    
    <!-- Select dropdown with predefined options -->
    <select data-bind="value: selectedColor">
        <option value="red">Red</option>
        <option value="green">Green</option>
        <option value="blue">Blue</option>
    </select>
    
    <!-- Update on keyup instead of change (blur) -->
    <input data-bind="value: searchText" data-value-update="keyup" />
</div>

<script>
    var viewModel = kendo.observable({
        userName: "JohnDoe",
        description: "Enter description here...",
        selectedColor: "green",
        searchText: ""
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Text and HTML Bindings

Display values in non-form elements.

```html
<div id="view">
    <!-- Text binding (escaped HTML) -->
    <span data-bind="text: userName"></span>
    
    <!-- HTML binding (renders HTML) -->
    <div data-bind="html: richContent"></div>
</div>

<script>
    var viewModel = kendo.observable({
        userName: "John Doe",
        richContent: "<strong>Bold</strong> and <em>italic</em> text"
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Attribute Binding

Set HTML attributes dynamically.

```html
<div id="view">
    <img data-bind="attr: { src: imageUrl, alt: imageDescription }" />
    <a data-bind="attr: { href: linkUrl, title: linkTitle }">Click here</a>
</div>

<script>
    var viewModel = kendo.observable({
        imageUrl: "https://example.com/logo.png",
        imageDescription: "Company Logo",
        linkUrl: "https://example.com",
        linkTitle: "Visit our website"
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Visibility Bindings

Show or hide elements based on conditions.

```html
<div id="view">
    <input type="checkbox" data-bind="checked: isAdmin" /> Administrator
    
    <!-- Shown when isAdmin is true -->
    <div data-bind="visible: isAdmin">
        <h3>Admin Panel</h3>
        <button>Delete Users</button>
    </div>
    
    <!-- Shown when isAdmin is false -->
    <div data-bind="invisible: isAdmin">
        <p>You need administrator privileges to access this area.</p>
    </div>
</div>

<script>
    var viewModel = kendo.observable({
        isAdmin: false
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Enabled/Disabled Bindings

Enable or disable form elements.

```html
<div id="view">
    <input type="checkbox" data-bind="checked: agreedToTerms" /> I agree to the terms
    
    <!-- Enabled only when checkbox is checked -->
    <button data-bind="enabled: agreedToTerms">Submit</button>
    
    <!-- Disabled when checkbox is checked -->
    <button data-bind="disabled: agreedToTerms">Cancel</button>
</div>

<script>
    var viewModel = kendo.observable({
        agreedToTerms: false
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### CSS and Style Bindings

Dynamically set CSS classes and inline styles.

```html
<style>
    .highlighted { background-color: yellow; }
    .error { color: red; font-weight: bold; }
</style>

<div id="view">
    <!-- CSS class binding -->
    <div data-bind="css: { highlighted: isHighlighted, error: hasError }">
        This text changes style based on ViewModel state
    </div>
    
    <!-- Inline style binding -->
    <div data-bind="style: { color: textColor, fontSize: fontSize }">
        Styled dynamically
    </div>
    
    <input type="checkbox" data-bind="checked: isHighlighted" /> Highlight
    <input type="checkbox" data-bind="checked: hasError" /> Show Error
</div>

<script>
    var viewModel = kendo.observable({
        isHighlighted: false,
        hasError: false,
        textColor: "blue",
        fontSize: "16px"
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Event Bindings

Bind DOM events to ViewModel methods.

```html
<div id="view">
    <button data-bind="click: handleClick">Click Me</button>
    
    <!-- Multiple events -->
    <input data-bind="events: { 
        focus: onFocus, 
        blur: onBlur,
        keypress: onKeyPress 
    }" />
    
    <p data-bind="text: message"></p>
</div>

<script>
    var viewModel = kendo.observable({
        message: "",
        
        handleClick: function(e) {
            this.set("message", "Button clicked!");
            // e.preventDefault(); - if needed
        },
        
        onFocus: function() {
            this.set("message", "Input focused");
        },
        
        onBlur: function() {
            this.set("message", "Input lost focus");
        },
        
        onKeyPress: function(e) {
            this.set("message", "Key pressed: " + e.key);
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Source Binding

Populate elements from arrays (used with templates).

```html
<div id="view">
    <select data-bind="source: colors, value: selectedColor" 
            data-text-field="name" 
            data-value-field="id">
    </select>
    
    <ul data-bind="source: products" data-template="product-template"></ul>
</div>

<script id="product-template" type="text/x-kendo-template">
    <li>
        <strong>#= name #</strong>: $#= price.toFixed(2) #
    </li>
</script>

<script>
    var viewModel = kendo.observable({
        selectedColor: 2,
        colors: [
            { id: 1, name: "Red" },
            { id: 2, name: "Green" },
            { id: 3, name: "Blue" }
        ],
        products: [
            { name: "Coffee", price: 5.50 },
            { name: "Tea", price: 4.00 },
            { name: "Juice", price: 6.00 }
        ]
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

---

## Working with Kendo UI Widgets

One of the most powerful features of Kendo UI MVVM is how seamlessly it integrates with Kendo UI widgets. You can bind widgets to your ViewModel just like regular HTML elements.

### Widget Initialization via MVVM

Instead of using the traditional jQuery plugin syntax, you can initialize Kendo UI widgets declaratively using `data-role` and `data-bind`.

#### Traditional Approach (jQuery Plugin)
```javascript
$("#myDropDown").kendoDropDownList({
    dataSource: products,
    dataTextField: "name",
    dataValueField: "id",
    value: selectedProductId
});
```

#### MVVM Approach (Declarative)
```html
<select data-role="dropdownlist"
        data-text-field="name"
        data-value-field="id"
        data-bind="source: products, value: selectedProductId">
</select>
```

### Example 1: DropDownList with MVVM

```html
<div id="view">
    <h3>Select a Product</h3>
    
    <select data-role="dropdownlist"
            data-text-field="name"
            data-value-field="id"
            data-value-primitive="true"
            data-option-label="Select a product..."
            data-bind="source: products, value: selectedProductId">
    </select>
    
    <p data-bind="visible: selectedProductId">
        Selected Product ID: <span data-bind="text: selectedProductId"></span>
    </p>
</div>

<script>
    var viewModel = kendo.observable({
        selectedProductId: null,
        products: [
            { id: 1, name: "Coffee" },
            { id: 2, name: "Tea" },
            { id: 3, name: "Juice" },
            { id: 4, name: "Water" }
        ]
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

**Key Points:**
- `data-role="dropdownlist"` tells Kendo to initialize a DropDownList widget
- `data-text-field` specifies which property to display
- `data-value-field` specifies which property to use as the value
- `data-value-primitive="true"` makes the bound value the primitive ID instead of the whole object
- `data-bind="source: ..."` binds the widget's data source to a ViewModel array
- `data-bind="value: ..."` creates two-way binding with the selected value

### Example 2: Grid with MVVM

The Grid widget is one of the most complex components, and MVVM makes it much easier to manage.

```html
<div id="view">
    <div data-role="grid"
         data-bind="source: products"
         data-columns='[
             { field: "name", title: "Product Name" },
             { field: "category", title: "Category" },
             { field: "price", title: "Price", format: "{0:c}" },
             { field: "inStock", title: "In Stock", template: "#= inStock ? \"Yes\" : \"No\" #" }
         ]'
         data-editable="true"
         data-toolbar='["create", "save", "cancel"]'>
    </div>
</div>

<script>
    var viewModel = kendo.observable({
        products: new kendo.data.DataSource({
            data: [
                { id: 1, name: "Coffee", category: "Beverages", price: 5.50, inStock: true },
                { id: 2, name: "Tea", category: "Beverages", price: 4.00, inStock: true },
                { id: 3, name: "Juice", category: "Beverages", price: 6.00, inStock: false }
            ],
            schema: {
                model: {
                    id: "id",
                    fields: {
                        id: { type: "number", editable: false },
                        name: { type: "string", validation: { required: true } },
                        category: { type: "string" },
                        price: { type: "number", validation: { required: true, min: 0 } },
                        inStock: { type: "boolean" }
                    }
                }
            }
        })
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Example 3: DatePicker with MVVM

```html
<div id="view">
    <h3>Select a Date</h3>
    
    <input data-role="datepicker"
           data-bind="value: selectedDate"
           data-format="yyyy-MM-dd"
           data-min="minDate"
           data-max="maxDate" />
    
    <p data-bind="visible: selectedDate">
        You selected: <span data-bind="text: formattedDate"></span>
    </p>
</div>

<script>
    var viewModel = kendo.observable({
        selectedDate: new Date(),
        minDate: new Date(2020, 0, 1),
        maxDate: new Date(2025, 11, 31),
        
        formattedDate: function() {
            var date = this.get("selectedDate");
            if (date) {
                return kendo.toString(date, "MMMM dd, yyyy");
            }
            return "";
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Example 4: NumericTextBox with MVVM

```html
<div id="view">
    <h3>Enter Quantity</h3>
    
    <input data-role="numerictextbox"
           data-bind="value: quantity"
           data-min="0"
           data-max="100"
           data-step="1"
           data-format="n0"
           data-decimals="0" />
    
    <p>Total Price: <span data-bind="text: totalPrice"></span></p>
</div>

<script>
    var viewModel = kendo.observable({
        quantity: 1,
        pricePerUnit: 10,
        
        totalPrice: function() {
            var qty = this.get("quantity") || 0;
            var price = this.get("pricePerUnit");
            return "$" + (qty * price).toFixed(2);
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Example 5: Binding to Widget Events

You can also bind to widget-specific events using the `events` binding.

```html
<div id="view">
    <input data-role="autocomplete"
           data-bind="value: searchText, 
                      source: suggestions,
                      events: { 
                          change: onSearchChange,
                          select: onSuggestionSelected
                      }" />
    
    <p data-bind="text: statusMessage"></p>
</div>

<script>
    var viewModel = kendo.observable({
        searchText: "",
        suggestions: ["Apple", "Banana", "Cherry", "Date", "Elderberry"],
        statusMessage: "Start typing to search...",
        
        onSearchChange: function(e) {
            var value = e.sender.value();
            this.set("statusMessage", "You typed: " + value);
        },
        
        onSuggestionSelected: function(e) {
            var item = e.dataItem;
            this.set("statusMessage", "You selected: " + item);
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Working with DataSource

Kendo UI widgets often work with `kendo.data.DataSource`, which is itself observable and integrates perfectly with MVVM.

```html
<div id="view">
    <div data-role="grid"
         data-bind="source: dataSource"
         data-columns='[
             { field: "name" },
             { field: "age" },
             { command: ["edit", "destroy"] }
         ]'
         data-editable="inline"
         data-toolbar='["create"]'>
    </div>
    
    <p>Total Records: <span data-bind="text: totalRecords"></span></p>
</div>

<script>
    var viewModel = kendo.observable({
        dataSource: new kendo.data.DataSource({
            data: [
                { id: 1, name: "John", age: 30 },
                { id: 2, name: "Jane", age: 25 },
                { id: 3, name: "Bob", age: 35 }
            ],
            schema: {
                model: {
                    id: "id",
                    fields: {
                        id: { type: "number", editable: false },
                        name: { type: "string" },
                        age: { type: "number" }
                    }
                }
            }
        }),
        
        totalRecords: function() {
            return this.get("dataSource").total();
        }
    });
    
    // Update total count when data changes
    viewModel.dataSource.bind("change", function() {
        viewModel.trigger("change", { field: "totalRecords" });
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

---

## Advanced Patterns

### Nested ViewModels

For complex applications, you can nest ViewModels to organize your code better.

```html
<div id="view">
    <h2>User Profile</h2>
    
    <div>
        <label>Name:</label>
        <input data-bind="value: user.name" />
    </div>
    
    <div>
        <label>Email:</label>
        <input data-bind="value: user.email" />
    </div>
    
    <h3>Address</h3>
    <div>
        <label>Street:</label>
        <input data-bind="value: user.address.street" />
    </div>
    
    <div>
        <label>City:</label>
        <input data-bind="value: user.address.city" />
    </div>
    
    <p>Full Address: <span data-bind="text: user.fullAddress"></span></p>
</div>

<script>
    var viewModel = kendo.observable({
        user: {
            name: "John Doe",
            email: "john@example.com",
            address: {
                street: "123 Main St",
                city: "Springfield",
                
                // Computed property in nested object
                fullAddress: function() {
                    return this.get("street") + ", " + this.get("city");
                }
            }
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Binding Scope and Context

When working with templates and nested structures, understanding binding context is crucial.

```html
<div id="view">
    <ul data-bind="source: categories" data-template="category-template"></ul>
</div>

<script id="category-template" type="text/x-kendo-template">
    <li>
        <strong>#= name #</strong>
        <ul data-bind="source: products" data-template="product-template"></ul>
    </li>
</script>

<script id="product-template" type="text/x-kendo-template">
    <li>#= name # - $#= price #</li>
</script>

<script>
    var viewModel = kendo.observable({
        categories: [
            {
                name: "Beverages",
                products: [
                    { name: "Coffee", price: 5.50 },
                    { name: "Tea", price: 4.00 }
                ]
            },
            {
                name: "Snacks",
                products: [
                    { name: "Chips", price: 3.00 },
                    { name: "Cookies", price: 4.50 }
                ]
            }
        ]
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Two-Way Computed Properties

You can create computed properties that support both getting and setting values.

```html
<div id="view">
    <p>Full Name: <input data-bind="value: fullName" /></p>
    <p>First Name: <span data-bind="text: firstName"></span></p>
    <p>Last Name: <span data-bind="text: lastName"></span></p>
</div>

<script>
    var viewModel = kendo.observable({
        firstName: "John",
        lastName: "Doe",
        
        // Two-way computed property
        fullName: function(value) {
            if (value !== undefined) {
                // Setter: split the full name into first and last
                var parts = value.split(" ");
                this.set("firstName", parts[0] || "");
                this.set("lastName", parts[1] || "");
            } else {
                // Getter: combine first and last names
                return this.get("firstName") + " " + this.get("lastName");
            }
        }
    });
    
    kendo.bind($("#view"), viewModel);
</script>
```

### Manually Triggering Updates

Sometimes you need to manually trigger UI updates:

```javascript
var viewModel = kendo.observable({
    items: [],
    
    loadItems: function() {
        // Simulate loading data
        $.ajax({
            url: "/api/items",
            success: function(data) {
                // Update array reference to trigger binding update
                viewModel.set("items", data);
                
                // Or trigger change manually
                viewModel.trigger("change", { field: "items" });
            }
        });
    }
});
```

---

## Best Practices

### 1. Always Use get() and set()

❌ **Wrong:**
```javascript
var viewModel = kendo.observable({
    count: 0,
    total: function() {
        return this.count * 2; // Direct property access - won't track dependencies!
    }
});
```

✅ **Correct:**
```javascript
var viewModel = kendo.observable({
    count: 0,
    total: function() {
        return this.get("count") * 2; // Properly tracks dependencies
    }
});
```

### 2. Initialize with kendo.observable()

❌ **Wrong:**
```javascript
var viewModel = {
    name: "John"
};

kendo.bind($("#view"), viewModel);

// This will fail - viewModel is not observable
viewModel.set("name", "Jane"); // Error: set is not a function
```

✅ **Correct:**
```javascript
var viewModel = kendo.observable({
    name: "John"
});

kendo.bind($("#view"), viewModel);

// This works
viewModel.set("name", "Jane");
```

### 3. Use valuePrimitive for Select Widgets

When binding to dropdown values, decide whether you want the whole object or just the ID:

```html
<!-- Bind to the entire object -->
<select data-role="dropdownlist"
        data-text-field="name"
        data-value-field="id"
        data-bind="source: products, value: selectedProduct">
</select>

<!-- Bind to just the ID (primitive value) -->
<select data-role="dropdownlist"
        data-text-field="name"
        data-value-field="id"
        data-value-primitive="true"
        data-bind="source: products, value: selectedProductId">
</select>
```

### 4. Avoid Inline Code in Bindings

❌ **Wrong (doesn't work with CSP compliance):**
```html
<div data-bind="text: name.toLowerCase()"></div>
```

✅ **Correct:**
```html
<div data-bind="text: lowerCaseName"></div>

<script>
var viewModel = kendo.observable({
    name: "JOHN DOE",
    lowerCaseName: function() {
        return this.get("name").toLowerCase();
    }
});
</script>
```

### 5. Keep ViewModels Focused

Organize your ViewModels logically. Don't create one massive ViewModel for your entire application.

```javascript
// Instead of one giant ViewModel
var appViewModel = kendo.observable({
    user: { /* user data */ },
    products: [],
    cart: [],
    orders: [],
    // ... hundreds of properties
});

// Break it into logical pieces
var userViewModel = kendo.observable({ /* user stuff */ });
var shopViewModel = kendo.observable({ /* shopping stuff */ });
var orderViewModel = kendo.observable({ /* order stuff */ });
```

### 6. Clean Up Bindings When Done

If you dynamically create and destroy views, unbind them to prevent memory leaks:

```javascript
// Bind
kendo.bind($("#dynamicView"), viewModel);

// Later, when removing the view
kendo.unbind($("#dynamicView"));
$("#dynamicView").remove();
```

### 7. Use DataSource for Complex Data

For grids, lists, and other data-bound widgets, use `kendo.data.DataSource`:

```javascript
var viewModel = kendo.observable({
    products: new kendo.data.DataSource({
        transport: {
            read: {
                url: "/api/products",
                dataType: "json"
            }
        },
        schema: {
            model: {
                id: "id",
                fields: {
                    name: { type: "string" },
                    price: { type: "number" }
                }
            }
        },
        pageSize: 20
    })
});
```

### 8. Validate Input with Schema

Define validation rules in your DataSource schema:

```javascript
schema: {
    model: {
        fields: {
            email: { 
                type: "string",
                validation: {
                    required: true,
                    email: true
                }
            },
            age: {
                type: "number",
                validation: {
                    required: true,
                    min: 18,
                    max: 120
                }
            }
        }
    }
}
```

---

## Summary

MVVM is a powerful pattern that:
- ✅ Separates UI from business logic
- ✅ Provides automatic two-way data binding
- ✅ Makes code more testable and maintainable
- ✅ Reduces boilerplate DOM manipulation code

**Kendo UI MVVM** takes this further by:
- ✅ Providing `kendo.observable()` for easy ViewModel creation
- ✅ Supporting rich data bindings (`value`, `text`, `visible`, `events`, etc.)
- ✅ Seamlessly integrating with all Kendo UI widgets
- ✅ Working with `kendo.data.DataSource` for complex data scenarios
- ✅ Offering declarative widget initialization via `data-role`

**Key Takeaways:**
1. Always use `kendo.observable()` to create ViewModels
2. Use `get()` and `set()` methods for property access in computed properties
3. Leverage `data-bind` attributes for declarative bindings
4. Use `data-role` to initialize Kendo widgets declaratively
5. Keep ViewModels focused and organized
6. Use DataSource for complex data operations

For more information, refer to the [official Kendo UI MVVM documentation](https://docs.telerik.com/kendo-ui/framework/mvvm/overview).