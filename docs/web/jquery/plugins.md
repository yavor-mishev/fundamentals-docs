# jQuery Plugins

There is a very well written article about jQuery plugins in the official documentation that I suggest you read: [jQuery Plugins](https://learn.jquery.com/plugins/basic-plugin-creation/). There you will see how a plugin is created and why we would want to use them.

Kendo widgets are just jQuery plugins. You can initialize a Kendo widget on a jQuery object like this:

```javascript
$('#myElement').kendoButton({
  text: 'Click Me',
  click: function () {
    alert('Button clicked!');
  },
});
```

In the article above the code snippet you will see that for more complex plugins we have the option to pass options to the plugin during initialization. This is exactly what we do when initializing Kendo widgets. The object we pass to the widget contains configuration options and event handlers.

This whole operation is valid because the `kendoButton` method is added to the jQuery prototype, allowing you to call it on any jQuery object. This goes for all the othe kendo widgets as well.

## Basic plugin authoring

jQuery plugins alolow us to extend the jQuery prototype with our own methods. This is done using the `jQuery.fn` object. Anything added to `jQuery.fn` becomes available as a method on any jQuery object. Here is a simple example of how to create a jQuery plugin:

```javascript
$.fn.greet = function (name) {
  return this.each(function () {
    $(this).text('Hello, ' + name + '!');
  });
};
```

In this example, we define a plugin called `greet` that takes a `name` parameter. The plugin iterates over each element in the jQuery selection and sets its text to a greeting message.