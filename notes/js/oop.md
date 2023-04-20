# OOP
## [Prototype Chain *not standard but for understanding class and new keywords*]
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
## [OOP without `class` keyword *avoid it*]
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
## [OOP with `class` keyword]
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
