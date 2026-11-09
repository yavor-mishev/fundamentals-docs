# Kendo MVVM Best Practices

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
