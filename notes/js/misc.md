# Miscellaneous
## Pass by Value nature with Pass by reference possible
- Javascript function always returns value not reference to value. i.e. After the value is returned it has nothing to do with function that it came from.
- Also if we pass in a variable we are just passing value of the variable not the reference to it.
```javascript
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
```javascript
function User(name) {
    this.name = name
}
User.prototype.getName = function() {
    return this.name
}
function changeName(user) {
    user.name = 'Tim'
}
let user1 = new User('John')
console.log(`user1: ${JSON.stringify(user1)}`) // prints object with name John
changeName(user1)
console.log(`user1: ${JSON.stringify(user1)}`) // prints object with name Tim
## Misc
```
- When we require a file it creates a new execution context (execution and local memory for execution).
 So if we require a file in 2 files it will run same file twice but each require will have it's own separate execution context.
 i.e. Objects will not be shared between the 2 requires. (Maybe?? Unless specified to have reference to global object)
- In JS `function` is not just a function it is also an object.
## Lexical scoping
- Javascript has lexical/static scope. The function has scope from where the it was defined. Not where it runs it. Example closure. eg.
- ***NOTE:*** If we run `outer` again then it returns a new copy of `inner` function. i.e. `func2` below is different function altogether. `func` and `func2` functions will have same definition but they are different functions.
```javascript
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
## Generators
- Generator functions are declared with `*` at the start of the identifier. e.g. `function *generatorFunction(){}`
- In generator functions we use a special keyword `yield`.
- The `yield` keyword returns whatever value it has at it's right hand side. And somehow pauses the execution of the function.
- The `yield` keyword can only be used in generator functions. i.e. function declared using `*`. The `yield` can be called multiple times in generator function.
- We psuedo-pause the function execution by saving execution context i.e. what line we are in thread of execution and state (local memory) of execution context. We store memory in `[[scope]]` closure and location in `[[GeneratorLocation]]`
- Generator functions when called using parenthesis i.e. `generatorFunction()` do not execute the function code directly.
- They return a special object called `Generator` object which has a property function called `next()`.
- When the `next()` is invoked it will return whatever is returned by `yield` keyword
- It returns object with `{value:'yieldedValue', done: boolean }`. The value is what is returned by `yield` and `done` denotes if everything is yielded from generator function.
- If there are 2 `yield`'s then at 3rd `next()` call `value` will be `undefined` and `done` will be `true`.
- As said before `yield` keyword pauses the execution context. So whenever `next()` is called the execution context resumes.
- We can pass a value to `next()` which can be passed almost like argument to paused execution context.
- If we `yield` during assignment of variable / constant as in following example the argument to `next` can be assigned to the L.H.S of assignment operation. i.e. `newNum` will be assigned 2 which is argument to `next` call.
- Essentially, the statement `yield <someValue>` will evaluate to value passed to the `next`.
- The `next()` will run the code block till the next yield.
i.e. if there are 10 lines between 1st `yield` and second `yield` statement then 2nd `next()` call will execute everything till 2nd `yield`
i.e. 10 lines and return anything i.e. left of `yield` and pause the execution context of generator function.
- There are also hidden properties that can be seen in IDEs or at least in Intellij Idea `[[GeneratorState]]` which can be `suspended`, `closed`; `[[GeneratorFunction]]`; `[[IsGenerator]]` which is boolean denoting if function is generator function and `[[GeneratorReciever]]`.
- Generator functions can only be used with `function` keyword not arrow functions.
```javascript
function *createFlow(){
    const num = 10
    const newNum = yield 10
    yield newNum + 5
    yield 6
}

const returnNextElement = createFlow() // returns Generator object with next property function
const element1 = returnNextElement.next() // returns / yields 10
const element2 = returnNextElement.next(2) // returns 7
//as `yield 10` at line no 3 evaluates to 2 which is passed in via next(2)
```
## Async Generators
- In below example after `returnNextElement.next()` is called `yield` will return the result of fetch which is a `Promise` and then pause the `createFlow` execution context.
- The `Promise` is stored in `futureData`. When the `Promise` resolves we will get the async result.
- On `Promise`'s fulfillment we pass the resolved `value` to `returnNextElement.next` which will then pass the `value` to paused execution context of `createFlow`.
- The `value` will replace the `yield` statement. Because as stated before the `yield` statement evaluates to whatever is passed to next `next()` call.
- So value of `data` will be `value` from resolved `Promise`.
- So here essentially we are implementing `async` / `await` using async generator functions.
As we are assigning value of resolved `Promise` directly to `data`.
Similar to `const data = await fetch('https://test/somedata')`
```javascript
function doWhenDataReceived(value) {
    returnNextElement.next(value)
}
function *createFlow() {
    const data = yield fetch('https://test/somedata')
    console.log(data)
}
const returnNextElement = createFlow()
const futureData = returnNextElement.next()
futureData.then(doWhenDataReceived)
```
