# Asynchronous JavaScript

## Callbacks

```javascript
function fetchData(callback) {
    setTimeout(() => {
        callback('Data received');
    }, 1000);
}

fetchData((data) => {
    console.log(data);
});
```

## Promises

```javascript
const promise = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve('Success!');
        // or reject('Error!');
    }, 1000);
});

promise
    .then(result => console.log(result))
    .catch(error => console.error(error))
    .finally(() => console.log('Cleanup'));

// Promise methods
Promise.all([promise1, promise2]);      // Wait for all
Promise.race([promise1, promise2]);     // First to settle
Promise.allSettled([promise1, promise2]); // Wait for all to settle
Promise.any([promise1, promise2]);      // First to fulfill
```

## Async/Await

```javascript
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Error:', error);
    }
}

// Async functions always return a Promise
fetchData().then(data => console.log(data));
```
