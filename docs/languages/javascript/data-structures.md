# Data Structures

## Arrays

```javascript
// Creating arrays
const arr1 = [1, 2, 3];
const arr2 = new Array(1, 2, 3);
const arr3 = Array.of(1, 2, 3);

// Common methods
arr1.push(4);           // Add to end
arr1.pop();             // Remove from end
arr1.unshift(0);        // Add to beginning
arr1.shift();           // Remove from beginning

// Iteration
arr1.forEach(item => console.log(item));
arr1.map(item => item * 2);
arr1.filter(item => item > 2);
arr1.reduce((acc, item) => acc + item, 0);

// Other useful methods
arr1.find(item => item === 2);
arr1.findIndex(item => item === 2);
arr1.includes(2);
arr1.some(item => item > 2);
arr1.every(item => item > 0);
arr1.slice(1, 3);
arr1.splice(1, 2, 'a', 'b');
```

## Objects

```javascript
// Creating objects
const obj1 = { name: 'John', age: 30 };
const obj2 = new Object();
const obj3 = Object.create(null);

// Accessing properties
obj1.name;          // Dot notation
obj1['name'];       // Bracket notation

// Adding/Modifying properties
obj1.email = 'john@example.com';
obj1['phone'] = '555-1234';

// Deleting properties
delete obj1.email;

// Object methods
Object.keys(obj1);       // ['name', 'age']
Object.values(obj1);     // ['John', 30]
Object.entries(obj1);    // [['name', 'John'], ['age', 30]]
Object.assign({}, obj1); // Shallow copy
Object.freeze(obj1);     // Make immutable
Object.seal(obj1);       // Prevent adding/removing properties

// Destructuring
const { name, age } = obj1;

// Spread operator
const obj4 = { ...obj1, city: 'NYC' };
```

## Maps

Ordered key-value pairs where keys can be any type:

```javascript
const map = new Map();

// Setting values
map.set('name', 'John');
map.set(1, 'number key');
map.set(true, 'boolean key');

// Getting values
map.get('name');        // 'John'

// Other methods
map.has('name');        // true
map.delete('name');     // true
map.size;               // 2
map.clear();            // removes all

// Iteration
map.forEach((value, key) => {
    console.log(`${key}: ${value}`);
});

for (let [key, value] of map) {
    console.log(`${key}: ${value}`);
}
```

## Sets

Collection of unique values:

```javascript
const set = new Set([1, 2, 3, 3, 4]); // {1, 2, 3, 4}

// Adding values
set.add(5);
set.add(5);  // Duplicate ignored

// Checking values
set.has(3);  // true

// Removing values
set.delete(3);
set.clear(); // removes all

// Size
set.size;    // 4

// Iteration
set.forEach(value => console.log(value));
for (let value of set) {
    console.log(value);
}

// Convert to array
const arr = [...set];
const arr2 = Array.from(set);
```

## WeakMap and WeakSet

Similar to Map and Set but with weak references (can be garbage collected):

```javascript
// WeakMap - keys must be objects
const weakMap = new WeakMap();
let obj = { id: 1 };
weakMap.set(obj, 'data');
obj = null; // Object can now be garbage collected

// WeakSet - values must be objects
const weakSet = new WeakSet();
let obj2 = { id: 2 };
weakSet.add(obj2);
obj2 = null; // Object can now be garbage collected
```
