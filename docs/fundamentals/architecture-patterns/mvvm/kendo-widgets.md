# Kendo UI Widgets & Advanced Patterns

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
