const myObj = {};
const myObj2 = Object.create(Object.prototype);

console.log(myObj2.__proto__ === myObj.__proto__); // true
