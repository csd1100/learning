# Functional Programming

- _**Higher Order Functions**_ are functions which take function as input or return function as output.
- _**Callback Functions**_ are functions which are passed to _**Higher Order Functions**_
- _reduce_ operation has 2 parts:
  - _'accumulator'_ - it collects the output e.g. string, array, number.
  - _'reducer'_ - it generates the output by applying certain logic and adds it to _accumulator_.
- e.g. reducer reduces the data to accumulator. In below example we are reducing using add as reducer and number 0 as accumulator which will accumulate sum of elements of array.

```javascript
const reduce = (dataToReduce, reducerLogic, accumulator) => {
  for (let i = 0; i < dataToReduce.length; i++) {
    accumulator = reducerLogic(accumulator, dataToReduce[i]);
  }
  return accumulator;
};
const add = (a, b) => a + b;

reduce([1, 2, 3], add, 0); // outputs 6
```

- We are not just reducing an array to a number but we are reducing 2 things i.e. _accumulator_ and _input_ to 1 thing i.e. _result_.
  We can also reduce array of numbers to an array of same size but here difference is that the output array is considered a single thing -> an accumulated output.
  e.g.

```javascript
const reduce = (dataToReduce, reducerLogic, accumulator) => {
  for (let i = 0; i < dataToReduce.length; i++) {
    accumulator = reducerLogic(accumulator, dataToReduce[i]);
  }
  return accumulator;
};
const multiplyAndPush = (a, b) => {
  let result = a * 2;
  b.push(result);
  return result;
};

reduce([1, 2, 3], multiplyAndPush, []); // outputs [2,4,6]
```

- Builtin Higher Order Functions for Array (defined in Array.prototype) can be used interchangeably sometimes but they have specific purpose and should be used according to that purpose.

  - `forEach` - It iterates through array and can perform any operation on it. So can `map` but `forEach` doesn't return an array. So, if you don't want a new array or if you want to update the current(original) array (mutate the original) then use `forEach`. (can mutate depends on user)
  - `map` - It iterates through array and performs a provided operation on element and pushes the element on to the new array. We should use this when we want a new copy of array with transformations applied on each element. (doesn't mutate)
  - `reduce` - It can be used as `map` as well but the intent matters. The `reduce` takes a reducer function which generates a single thing which is resultant accumulator. (doesn't mutate)
  - `filter` - Filter will return a new array with filtered values based on passed in function which returns a boolean value. (doesn't mutate)

  - `reduceRight` - It is same as reduce just it goes from right to left i.e. From end of array to start of the array. (doesn't mutate)

- **NOTE:** Chaining of Higher Order Functions depends on what is the output of current function and what is the input of subsequent function.
- The term **_referentially transparent_** means we can replace the call to the function with the result without any consequences.
- `reduce` is one of the most important functions in functional programming. It can used for _function composition_. e.g.
  Below the reduction is happening; 2 => 1 which: 1.function and 2.accumulator => 1.accumulator output.

```javascript
const reduce = (dataToReduce, reducerLogic, accumulator) => {
  for (let i = 0; i < dataToReduce.length; i++) {
    accumulator = reducerLogic(accumulator, dataToReduce[i]);
  }
  return accumulator;
};
const runner = (a, toRun) => {
  return toRun(a);
};

const add2 = (a) => a + 2;
const multiplyBy5 = (m) => m * 5;
const divideBy3 = (d) => d / 3;

reduce([add2, multiplyBy5, divideBy3], runner, 10);
```

Graphical Representation:

```
 reduction:
                      add2    multiplyBy5     divideBy3
 reducer = runner_______|__________|_______________|
 accumulator = 10       12        60              20
 result = 20
```

- **_Pure Functions_** are functions that only affect the data within scope of it. And has clear name that describes what it is doing. Pure functions do **not** mutate the input data.

```javascript
const add2 = (x) => x + 2; // pure function
let num = 10;
const add3 = (x) => {
  num++;
  return 3;
}; // impure function as it affects global data num
```

- **Closure**
  - Javascript has lexical/static scoping. The function has scope from where the it was defined. Not where it runs it.<br>
  - When create a nested function (i.e. function inside a function) and we access a data from outer function in inner function the Javascript adds a backpack(closure) to the definition of inner function.
  - The backpack is a permanent memory attached to that function that is available to **only** that function.
  - The backpack is created as soon as we define the inner function.
  - If we want a permanent memory that needs to be used every time we run a function we use closures.
  - In reality JavaScript adds a new `[[scope]]` to that function. `[[scope]]` is hidden property for the function and it is as it is named,a scope for that function. Scope is where it can look for data.
  - in below example the `x` is added to the _Closure Scope_ if the function `inner`.

```javascript
function outer() {
  let x = "test";
  function inner() {
    console.log(x);
  }
  return inner;
}
function outer2() {
  let x = "outer2";
  let func = outer();
  func();
  // here scope of func (-> inner) has scope of outer not outer2
  // func will print 'test' not 'outer2'
}
outer2();
```

- **Function Decoration** creates a new function that has same output as before but has added functionality to it.
