const array = [28, 14, 35, 10, 19];

function bubbleSort(array) {
    const arrLen = array.length;
    for (let i = 0; i < arrLen - 1; i ++) {
        for (let j = 0; j < arrLen - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                [array[j], array[j + 1]] = [array[j + 1], array[j]];
            }
        }
    }
    return array;
}

console.log(bubbleSort(array));