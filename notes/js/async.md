# Asynchronous execution

## [ES5 callbacks feature]

- _Anything_ added to callback queue will not be executed before all the synchronous code is executed.
- The _Event Loop_ is the feature / function that checks before dequeueing the elements from call back queue if there is any synchronous code left to run.
  If there is no synchronous code remaining execution in global scope then it will dequeue the callback to execute.
- eg. The Hello (`printHello`) will be printed after '0','1'..'50','done' is printed or synchronous code is executed. <br>
- The callbacks will be executed after synchronous code is run i.e. if the callback accesses some data from global scope and during execution of synchronous code the data is changed then it will use changed data not the original.
- i.e. here in below example test won't be 1000 even though it was 1000 when `setTimeout` was called.

```javascript
let test = 1000;
function printHello() {
  console.log("Hello");
  console.log(test);
}
function blockingTimeout(time) {
  let currentTime = new Date().getTime();
  const target = currentTime + time;
  while (currentTime < target) {
    currentTime = new Date().getTime();
  }
}
console.log(0);
setTimeout(printHello, 0);
blockingTimeout(10000);
let i = 0;
while (i < 50) {
  console.log(++i);
  test += i;
}
console.log("done");
```

## [ES6 Promises feature]

- The callback feature does not have a way to track the execution in JS.
  But Promises return a `Promise` object. _Promise_ object has _value_ which will be assigned when promise completes
  and _onFulfilled_ array which will keep track of what should be done with returned value.
  The functions in _onFulfilled_ can be added when using _.then_ method.
- Similar to _Callback Queue_, there is a _Microtask Queue_ for promises,
  where the function to execute after promise is fulfilled is stored.
  Similar to _Callback Queue_ the _Microtask Queue_ will also wait for synchronous code to execute
  then it will execute the function in the queue.
  The _Microtask Queue_ has higher priority that _Callback Queue_ hence the promise's data will be handled first.
- In below example 'start', 'done' will be printed first as they are synchronous calls.
  Then 'data' will be printed as it is on _Microtask Queue_ and then `setTimeoutData` as it will be on _Callback Queue_.

**NOTE:** If we use promises which will recursively add functions to _Microtask Queue_ without stopping then it might starve the _Callback Queue_.

```javascript
function printData(data) {
  console.log(`data: ${data}`);
}

function blockingTimeout(time) {
  let currentTime = new Date().getTime();
  const target = currentTime + time;
  while (currentTime < target) {
    currentTime = new Date().getTime();
  }
}

function promisedData() {
  return new Promise((resolve) => {
    resolve("data");
  });
}

console.log("start");

setTimeout(() => printData("setTimeoutData"), 0);

const dataPromise = promisedData();
dataPromise.then(printData);

blockingTimeout(1000);

console.log("done");
```

## [`async` / `await`]

- `await` keyword does **not** block the global execution. The `await` pauses the `async` function but continues the global synchronous execution.
- `async` / `await` keywords pauses the execution context using generator functions.
- Similar to `Promise` with `then`, after promise resolves the paused function using `async` / `await` goes on Microtask Queue to resume???????
- In below example the 'start' and 'done' are still printed first then `data` 'xxx' is printed and at last `done testAwait`
- The `testAwait` is psuedo-paused at `await` statement till promise resolves.

```
function promiseFunction() {
    return new Promise(resolve => {
        resolve('xxx')
    })
}

async function testAwait() {
    const data = await promiseFunction()
    console.log(data)
    console.log('done testAwait')
}

console.log('start')
testAwait()
console.log('done')
```

- Refer [Async Generator Functions](./misc.md#async-generators)
