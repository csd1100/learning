# Points to remember

## Miscellaneous
- Javascript function always returns value not reference to value. i.e. After the value is returned it has nothing to do with function that it came from.
- When we require a file it creates a new execution context (execution and local memory for execution).
 So if we require a file in 2 files it will run same file twice but each require will have it's own separate execution context.
 i.e. Objects will not be shared between the 2 requires. (Maybe?? Unless specified to have reference to global object)
- In JS *function* is not just a function it is also an object.
- Javascript has lexical/static scope. The function has scope from where the it was defined. Not where it runs it. Example closure. eg.
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
outer2()
```
## Asynchronous execution
### [ES5 callbacks feature]
- *Anything* added to callback queue will not be executed before all the synchronous code is executed.
- The *Event Loop* is the feature / function that checks before dequeueing the elements from call back queue if there is any synchronous code left to run.
 If there is no synchronous code remaining execution in global scope then it will dequeue the callback to execute.
- eg. The Hello (`printHello`) will be printed after '0','1'..'50','done' is printed or synchronous code is executed. <br>
- The callbacks will be executed after synchronous code is run i.e. if the callback accesses some data from global scope and during execution of synchronous code the data is changed then it will use changed data not the original.
- i.e. here in below example test won't be 1000 even though it was 1000 when *setTimeout* was called.
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
 But Promises return a *Promise* object. *Promise* object has *value* which will be assigned when promise completes
 and *onFulfilled* array which will keep track of what should be done with returned value.
 The functions in *onFulfilled* can be added when using *.then* method.
- Similar to *Callback Queue*, there is a *Microtask Queue* for promises,
 where the function to execute after promise is fulfilled is stored.
 Similar to *Callback Queue* the *Microtask Queue* will also wait for synchronous code to execute
 then it will execute the function in the queue.
 The *Microtask Queue* has higher priority that *Callback Queue* hence the promise's data will be handled first.
- In below example 'start', 'done' will be printed first as they are synchronous calls.
 Then 'data' will be printed as it is on *Microtask Queue* and then 'setTimeoutData' as it will be on *Callback Queue*.

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
- *await* keyword blocks the global execution i.e. it blocks the thread till promise resolves or rejects.
## OOP
### [Prototype Chain *not standard but for understanding class and new keywords*]
- When calling *Object.create*, if any blueprint object is passed, it creates a new object with prototype of argument (blueprint object) that is passed to it.
 It updates a hidden *\_\_proto\_\_* property with blueprint of the passed in object.
- It creates a *__Prototype Chain__*, The chain is: *\_\_proto\_\_* of blueprint -> *\_\_proto\_\_* of *Object.prototype* -> *null*.
- The *this* reference is only accessible for properties or functions defined in *\_\_proto\_\_*.
- All objects have *\_\_proto\_\_* which is the value of *Object.prototype*.
 *Object.prototype* has few JS helper methods.
- In prototype function if we add a nested function,
 then inside nested function *this* property is actually global *window* object
 not the *this* object to which prototype is added. This is because of JS is lexically scoped language.
 i.e. Where we define the method that will be the scope of the function. Similar to closure, here *this* will be where we define prototype object, i.e. in global scope.
- ex. Here *method2* will throw an error because *this* is not *obj* but a global object which does not have *name* property.
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
- But if we use arrow function instead of *function* keyword then *this* will resolve to *obj*.
 Because we are defining arrow function when we run *method2*.
 JS is lexically scoped i.e. the scope of function will be where the function is defined.
 Hence, the *this* at that point will be *obj*.
 Arrow function can refer *this* as object not global *window*.
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
 i.e. if we use arrow function to define *method1* then it will print undefined,
 because here this will be *window* of global scope
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
### [OOP without *class* keyword *avoid it*]
- The *prototype* keyword / object property is linked to objects *\_\_proto\_\_* hidden property.
 We can add methods to *prototype* property then it will be added to *\_\_proto\_\_*.
 And *\_\_proto\_\_* is actual prototype chain and *prototype* property contains only methods added to that function.<br>
 **NOTE:** But accessing *prototype* will return *undefined* if we *console.log* it.
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
### [OOP with *class* keyword]
- *class* keyword is just a syntactic sugar on *prototype* keyword use.
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
