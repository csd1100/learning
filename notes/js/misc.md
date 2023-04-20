# Miscellaneous
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
