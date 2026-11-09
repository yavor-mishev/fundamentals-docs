# Kendo UI MVVM & Data Bindings

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
