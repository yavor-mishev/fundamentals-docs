# SASS - Sayntactically Awesome Stylesheets

[Documentation](https://sass-lang.com/documentation/)

SASS (Syntactically Awesome Stylesheets) is a preprocessor scripting language that is interpreted or compiled into CSS. It extends CSS by adding features such as `variables`, `nested rules`, `mixins`, and `functions`, making it easier to write and maintain complex stylesheets. SASS helps streamline the styling process and enhances the capabilities of standard CSS.

## Statements

### Universal statements

#### variable declarations
#### flow control @ rules
#### @error, @warn, @debug

### CSS statements

#### style rules
#### CSS @ rules
#### mixin declarations: @include
#### at-root declarations

### Top-level statements

#### module loads: @use, @forward, @import (deprecated)
#### mixin definitions: @mixin
#### function definitions: @function

## Mixins

Mixins allow you to create reusable chunks of code that can be included in other selectors. This helps to avoid code duplication and keeps your stylesheets DRY (Don't Repeat Yourself).

```scss
@mixin border-radius($radius) {
    -webkit-border-radius: $radius;
    -moz-border-radius: $radius;
    border-radius: $radius;
}
```