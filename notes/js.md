# Points to remember

- Javascript function always returns value not reference to value. i.e. After the value is returned it has nothing to do with function that it came from.
- When we require a file it creates a new execution context (execution and local memory for execution). So if we require a file in 2 files it will run same file twice but each require will have it's own separate execution context. i.e. objects will not be shared between the 2 requires. (Maybe?? Unless specified to have reference to global object)
- Javascript has lexical/static scope. The function has scope where it was defined. Not where it runs it. example closure. eg.
```
function outer() {
    let x = 'test'
    function inner() {
        console.log(x)
    }
    return inner
}
function outer2() {
    let x = 'outer2'
    let func = outer()
    func()
    // here scope of func (-> inner) has scope of outer not outer2
    // func will print 'test' not 'outer2'
}
```
- [ES5 callbacks feature] *Anything* added to callback queue will not be executed before all the synchronous code is executed.
The *Event Loop* is the feature / function that checks before dequeueing the elements from call back queue if there is any synchronous code left to run. If there is no synchronous code remaining execution in global scope then it will dequeue the callback to execute.
eg. The Hello (`printHello`) will be printed after 0,1-50,done is printed or synchronous code is executed. <br>
The callbacks will be executed after synchronous code is run i.e. if the callback accesses some data from global scope and during execution of synchronous code the data is changed then it will use changed data not the original.
i.e. here in below example test won't be 1000 even thought it was 1000 when *setTimeout* was called.
```
function blockingTimeoutAndCallbackQueue() {
    let test = 1000
    function printHello() {
        console.log('Hello')
        console.log(test)
    }
    function blockingTimeout(time) {
        let currentTime = new Date().getTime()
        const target = currentTime + time
        while (currentTime < target) {
            currentTime = new Date().getTime()
        }
    }
    console.log(0)
    setTimeout(printHello, 0)
    blockingTimeout(10000)
    let i = 0
    while (i < 50) {
        console.log(++i)
        test += i
    }
    console.log('done')
}
```
- [ES6 Promises feature] The callback feature does not have a way to track the execution in JS. But Promises return a Promise object which has *value* which will be assigned when promise completes and *onFulfilled* array which will keep track of what should be done with returend value. The functions in *onFulfilled* will be added when using *.then* method.<br>
Similar to *Callback Queue*, there is a *Microtask Queue* for promises where the function to execute after promise is fulfilled is stored. Similar to *Callback Queue* the *Microtask Queue* will also wait for synchronous code to execute the it will execute the function in the queue. But here the *Microtask Queue* has higher priority that *Callback Queue* hence the promise's data will be handled first.<br>
In below example start, done will be printed first as they are synchronous calls. Then 'data' will be printed as it is on *Microtask Queue* and then 'setTimeoutData' as it will be on *Callback Queue*.
```
function promisesAndCallback() {
    function printData(data) {
        console.log(`data: ${data}`)
    }

    function blockingTimeout(time) {
        let currentTime = new Date().getTime()
        const target = currentTime + time
        while (currentTime < target) {
            currentTime = new Date().getTime()
        }
    }

    function promisedData() {
        return new Promise((resolve) => {
            resolve('data')
        })
    }

    console.log('start')

    setTimeout(()=>printData('setTimeoutData'), 0)

    const dataPromise = promisedData()
    dataPromise.then(printData)

    blockingTimeout(1000)

    console.log('done')
}

```
