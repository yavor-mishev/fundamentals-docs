# Regular expressions

Regular expressions are a tool for finding patterns in a string. They are used mainly to:
- validate text and
- search through text

1. Defining a regex

```javascript
// literal syntax
const regex = /Bob/; // exact match

// use the g flag to find all matches
regex = /Dancho/g;

// use | as a logical OR
regex = /Achkata|Mitaka/;
```