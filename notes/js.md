# Points to remember

## Miscellaneous
- Javascript function always returns value not reference to value. i.e. After the value is returned it has nothing to do with function that it came from.
- Also if we pass in a variable we are just passing value of the variable not the reference to it.
```
function add10(num) {
    num = num + 10
    return num
}
let number1 = 1
const result = add10(number1)
console.log(`result: ${result}`) // prints 11
console.log(`number1: ${number1}`) // prints 1
```
- ***BUT***, whenever we have a variable is not primitive or single value (array, objects) then what we get is actually a reference to that object and any changes we make to that object will be persistent. So below example `user1` is actually reference to object. And we are ***passing a value*** which is a **reference**.
```
function User(name) {
    this.name = name
}
User.prototype.getName = function() {
    return this.name
}
function changeName(user) {
    user1.name = 'Tim'
}
let user1 = new User('John')
console.log(`user1: ${JSON.stringify(user1)}`) // prints object with name John
changeName(user1)
console.log(`user1: ${JSON.stringify(user1)}`) // prints object with name Tim
```
- When we require a file it creates a new execution context (execution and local memory for execution).
 So if we require a file in 2 files it will run same file twice but each require will have it's own separate execution context.
 i.e. Objects will not be shared between the 2 requires. (Maybe?? Unless specified to have reference to global object)
- In JS *function* is not just a function it is also an object.
- Javascript has lexical/static scope. The function has scope from where the it was defined. Not where it runs it. Example closure. eg.
- ***NOTE:*** If we run `outer` again then it returns a new copy of `inner` function. i.e. `func2` below is different function altogether. `func` and `func2` functions will have same definition but they are different functions.
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
    let func2 = outer() //func2 is different function altogether
}
outer2()
```
## Asynchronous execution
### [ES5 callbacks feature]
- *Anything* added to callback queue will not be executed before all the synchronous code is executed.
- The *Event Loop* is the feature / function that checks before dequeueing the elements from call back queue if there is any synchronous code left to run.
 If there is no synchronous code remaining execution in global scope then it will dequeue the callback to execute.
- eg. The Hello (`printHello`) will be printed after '0','1'..'50','done' is printed or synchronous code is executed. <br>
- The callbacks will be executed after synchronous code is run i.e. if the callback accesses some data from global scope and during execution of synchronous code the data is changed then it will use changed data not the original.
- i.e. here in below example test won't be 1000 even though it was 1000 when `setTimeout` was called.
```
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
```
### [ES6 Promises feature]
- The callback feature does not have a way to track the execution in JS.
 But Promises return a `Promise` object. *Promise* object has *value* which will be assigned when promise completes
 and *onFulfilled* array which will keep track of what should be done with returned value.
 The functions in *onFulfilled* can be added when using *.then* method.
- Similar to *Callback Queue*, there is a *Microtask Queue* for promises,
 where the function to execute after promise is fulfilled is stored.
 Similar to *Callback Queue* the *Microtask Queue* will also wait for synchronous code to execute
 then it will execute the function in the queue.
 The *Microtask Queue* has higher priority that *Callback Queue* hence the promise's data will be handled first.
- In below example 'start', 'done' will be printed first as they are synchronous calls.
 Then 'data' will be printed as it is on *Microtask Queue* and then `setTimeoutData` as it will be on *Callback Queue*.

**NOTE:** If we use promises which will recursively add functions to *Microtask Queue* without stopping then it might starve the *Callback Queue*.
```
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
```
- `await` keyword blocks the global execution i.e. it blocks the thread till promise resolves or rejects.
## OOP
### [Prototype Chain *not standard but for understanding class and new keywords*]
- When calling `Object.create`, if any blueprint object is passed, it creates a new object with prototype of argument (blueprint object) that is passed to it.
 It updates a hidden `__proto__` property with blueprint of the passed in object.
- It creates a *__Prototype Chain__*, The chain is: `__proto__` of blueprint -> *__proto__` of *Object.prototype* -> *null*.
- The `this` reference is only accessible for properties or functions defined in `__proto__`.
- All objects have `__proto__` which is the value of `Object.prototype`.
 *Object.prototype* has few JS helper methods.
- In prototype function if we add a nested function,
 then inside nested function `this` property is actually global `window` object
 not the `this` object to which prototype is added. This is because of JS is lexically scoped language.
 i.e. Where we define the method that will be the scope of the function. Similar to closure, here `this` will be where we define prototype object, i.e. in global scope.
- ex. Here `method2` will throw an error because `this` is not `obj` but a global object which does not have `name` property.
```
const methodsProto = {
    method1: function() {
        console.log(this.name)
    },
    method2: function() {
        function printUpper() {
            console.log(this.name.toUpperCase())
        }
        printUpper()
    }
}
function createObj(name) {
    let obj = Object.create(methodsProto)
    obj.name = name
    return obj
}
let obj = createObj('name')
obj.method1() // prints name
obj.method2() // throws error as name is undefined and does not print name in uppercase
```
- But if we use arrow function instead of `function` keyword then `this` will resolve to `obj`.
 Because we are defining arrow function when we run `method2`.
 JS is lexically scoped i.e. the scope of function will be where the function is defined.
 Hence, the `this` at that point will be `obj`.
 Arrow function can refer `this` as object not global `window`.
```
const methodsProto = {
    method1: function() {
        console.log(this.name)
    },
    method2: function() {
        const printUpper = () => {
            console.log(this.name.toUpperCase())
        }
        printUpper()
    }
}
function createObj(name) {
    let obj = Object.create(methodsProto)
    obj.name = name
    return obj
}
let obj = createObj('name')
obj.method1() // prints name
obj.method2() // prints NAME
```
- Then again if we use arrow function in root prototype definition
 i.e. if we use arrow function to define `method1` then it will print undefined,
 because here this will be `window` of global scope
```
const methodsProto = {
    method1: () => {
        console.log(this.name)
    },
    method2: function() {
        const printUpper = () => {
            console.log(this.name.toUpperCase())
        }
        printUpper()
    }
}
function createObj(name) {
    let obj = Object.create(methodsProto)
    obj.name = name
    return obj
}
let obj = createObj('name')
obj.method1() // prints undefined
obj.method2() // prints NAME
```
### [OOP without `class` keyword *avoid it*]
- The `prototype` keyword / object property is linked to objects `__proto__` hidden property.
 We can add methods to *prototype* property then it will be added to `__proto__`.
 And `__proto__` is actual prototype chain and `prototype` property contains only methods added to that function.<br>
 **NOTE:** But accessing `prototype` will return `undefined` if we `console.log` it.
```
function User(name) {
    this.name = name
}
User.prototype.getName = function() {
    return this.name
}
let user1 = new User('John')
console.dir(user1) // prints user1 object
console.log(user1.getName()) // prints John
console.log(user1.prototype) // prints undefined
console.dir(user1.__proto__) // prints object with getName function
```
### [OOP with `class` keyword]
- `class` keyword is just a syntactic sugar on `prototype` keyword use.
 It groups object creator, methods and properties together.
```
class User {
    constructor(name) {
        this.name = name
    }
    getName() {
        return this.name
    }
}
let user1 = new User('John')
console.dir(user1) // prints user1 object
console.log(user1.getName()) // prints John
console.log(user1.prototype) // prints undefined
console.log(user1.__proto__) // prints empty object but when debugging we can see it there
```
## Functional Programming
- *__Higher Order Functions__* are functions which take function as input or return function as output.
- *__Callback Functions__* are functions which are passed to *__Higher Order Functions__*
- *reduce* operation has 2 parts:
    - *'accumulator'* - it collects the output e.g. string, array, number.
    - *'reducer'* - it generates the output by applying certain logic and adds it to *accumulator*.
- e.g. reducer reduces the data to accumulator. In below example we are reducing using add as reducer and number 0 as accumulator which will accumulate sum of elements of array.
```
const reduce = (dataToReduce, reducerLogic, accumulator) => {
    for(let i = 0; i < dataToReduce.length; i++) {
        accumulator = reducerLogic(accumulator, dataToReduce[i])
    }
    return accumulator
}
const add = (a,b) => a + b

reduce([1,2,3], add , 0) // outputs 6
```
- We are not just reducing an array to a number but we are reducing 2 things i.e. *accumulator* and *input* to 1 thing i.e. *result*.
We can also reduce array of numbers to an array of same size but here difference is that the output array is considered a single thing -> an accumulated output.
e.g.
```
const reduce = (dataToReduce, reducerLogic, accumulator) => {
    for(let i = 0; i < dataToReduce.length; i++) {
        accumulator = reducerLogic(accumulator, dataToReduce[i])
    }
    return accumulator
}
const multiplyAndPush = (a,b) => {
    let result = a * 2
    b.push(result)
    return result
}

reduce([1,2,3], multiplyAndPush , []) // outputs [2,4,6]
```
- Builtin Higher Order Functions for Array (defined in Array.prototype) can be used interchangeably sometimes but they have specific purpose and should be used according to that purpose.
    - `forEach` - It iterates through array and can perform any operation on it. So can `map` but `forEach` doesn't return an array. So, if you don't want a new array or if you want to update the current(original) array (mutate the original) then use `forEach`. (can mutate depends on user)
    - `map` - It iterates through array and performs a provided operation on element and pushes the element on to the new array. We should use this when we want a new copy of array with transformations applied on each element. (doesn't mutate)
    - `reduce` - It can be used as `map` as well but the intent matters. The `reduce` takes a reducer function which generates a single thing which is resultant accumulator. (doesn't mutate)
    - `filter` - Filter will return a new array with filtered values based on passed in function which returns a boolean value. (doesn't mutate)

    - `reduceRight` - It is same as reduce just it goes from right to left i.e. From end of array to start of the array. (doesn't mutate)
- **NOTE:**  Chaining of Higher Order Functions depends on what is the output of current function and what is the input of subsequent function.
- The term ***referentially transparent*** means we can replace the call to the function with the result without any consequences.
- `reduce` is one of the most important functions in functional programming. It can used for *function composition*. e.g.
Below the reduction is happening; 2 => 1 which: 1.function and 2.accumulator => 1.accumulator output.
```
const reduce = (dataToReduce, reducerLogic, accumulator) => {
    for(let i = 0; i < dataToReduce.length; i++) {
        accumulator = reducerLogic(accumulator, dataToReduce[i])
    }
    return accumulator
}
const runner = (a, toRun) => {
    return toRun(a)
}

const add2 = (a) => a + 2
const multiplyBy5 = (m) => m * 5
const divideBy3 = (d) => d / 3

reduce([add2, multiplyBy5, divideBy3], runner , 10 )
```
Graphical Representation:
```
 reduction:
                      add2    multiplyBy5     divideBy3
 reducer = runner_______|__________|_______________|
 accumulator = 10       12        60              20
 result = 20
```
- ***Pure Functions*** are functions that only affect the data within scope of it. And has clear name that describes what it is doing. Pure functions do **not** mutate the input data.
```
const add2 = x => x + 2 // pure function
let num = 10
const add3 = x => {
    num++
    return 3
} // impure function as it affects global data num
```
