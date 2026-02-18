### HTML data-* attributes

The data-* attributes allow us to store extra information on standard, semantic HTML elements without other hacks such as non-standard attributes, extra properties on DOM, or using `class` or `id` to store data. The attributes are completely optional and safe to use without any impact on the presentation or behavior of the HTML elements. We use them to store custom data private to the page or application, for which there are no more appropriate attributes or elements. These attributes are invisible to screen readers and other assistive technologies so make sure to add only data that is not supposed to be seen by such technologies.

The data-* attributes can be accessed in JavaScript using the `HTMLElement.dataset` property or via jQuery's `data()` method. Everything after `data-` is converted from kebab-case to camelCase when accessed via JavaScript and set as the property name.

```html
<!-- Example of a div element with data-* attributes attatched to it-->
<div id="myDiv" data-name="Yavor" data-age="25">Sample text</div>
```

```javascript
// name and age are the properties of the dataset object
const myDiv = document.getElementById("myDiv");
console.log(myDiv.dataset.name); // Outputs: Yavor
console.log(myDiv.dataset.age);  // Outputs: 25
```

Apart from accessing the data-* attributes via the `dataset` property, we can also change the values associated with them or even add new data-* attributes dynamically:

```javascript
myDiv.dataset.name = "John"; // Change existing data-name attribute
myDiv.dataset.city = "New York"; // Add new data-city attribute
```