# OOP

## [Prototype Chain, *not standard but for understanding class and new keywords*]

- When calling `Object.create`, if any blueprint object is passed, it creates a new object with prototype of argument (blueprint object) that is passed to it.
  It updates a hidden `__proto__` property with blueprint of the passed in object.
- It creates a _**Prototype Chain**_, The chain is: `__proto__` of blueprint -> ***proto**` of *Object.prototype* -> *null\*.
- The `this` reference is only accessible for properties or functions defined in `__proto__`.
- All objects have `__proto__` which is the value of `Object.prototype`.
  _Object.prototype_ has few JS helper methods.
- In prototype function if we add a nested function,
  then inside nested function `this` property is actually global `window` object
  not the `this` object to which prototype is added. This is because of JS is lexically scoped language.
  i.e. Where we define the method that will be the scope of the function. Similar to closure, here `this` will be where we define prototype object, i.e. in global scope.
- ex. Here `method2` will throw an error because `this` is not `obj` but a global object which does not have `name` property.

```javascript
const methodsProto = {
  method1: function () {
    console.log(this.name);
  },
  method2: function () {
    function printUpper() {
      console.log(this.name.toUpperCase());
    }
    printUpper();
  },
};
function createObj(name) {
  let obj = Object.create(methodsProto);
  obj.name = name;
  return obj;
}
let obj = createObj("name");
obj.method1(); // prints name
obj.method2(); // throws error as name is undefined and does not print name in uppercase
```

- But if we use arrow function instead of `function` keyword then `this` will resolve to `obj`.
  Because we are defining arrow function when we run `method2`.
  JS is lexically scoped i.e. the scope of function will be where the function is defined.
  Hence, the `this` at that point will be `obj`.
  Arrow function can refer `this` as object not global `window`.

```javascript
const methodsProto = {
  method1: function () {
    console.log(this.name);
  },
  method2: function () {
    const printUpper = () => {
      console.log(this.name.toUpperCase());
    };
    printUpper();
  },
};
function createObj(name) {
  let obj = Object.create(methodsProto);
  obj.name = name;
  return obj;
}
let obj = createObj("name");
obj.method1(); // prints name
obj.method2(); // prints NAME
```

- Then again if we use arrow function in root prototype definition
  i.e. if we use arrow function to define `method1` then it will print undefined,
  because here this will be `window` of global scope

```javascript
const methodsProto = {
  method1: () => {
    console.log(this.name);
  },
  method2: function () {
    const printUpper = () => {
      console.log(this.name.toUpperCase());
    };
    printUpper();
  },
};
function createObj(name) {
  let obj = Object.create(methodsProto);
  obj.name = name;
  return obj;
}
let obj = createObj("name");
obj.method1(); // prints undefined
obj.method2(); // prints NAME
```

## [OOP without `class` keyword, *avoid it cause not ES2015*]

- The `prototype` keyword / object property is linked to objects `__proto__` hidden property.
  We can add methods to _prototype_ property then it will be added to `__proto__`.
  And `__proto__` is actual prototype chain and `prototype` property contains only methods added to that function.<br>
  **NOTE:** But accessing `prototype` will return `undefined` if we `console.log` it.

```javascript
function User(name) {
  this.name = name;
}
User.prototype.getName = function () {
  return this.name;
};
let user1 = new User("John");
console.dir(user1); // prints user1 object
console.log(user1.getName()); // prints John
console.log(user1.prototype); // prints undefined
console.dir(user1.__proto__); // prints object with getName function
```

## `new` keyword

- The new keyword assigns this to new empty object. Then starts executing function used with `new` keyword.
- It also create link between methods defined using `prototype` keyword and object through `__proto__` property on object.
- It also automatically returns the newly created object.
- We use uppercase for function that is to be used with `new` keyword as best practise.
- **NOTE:** The `__proto__` property is on object itself and `prototype` is property of the function that is used to create the objects using `new` keyword. i.e. in example below `__proto__` is available on `user1` and `prototype` is on `Users` function.

```javascript
function Users(name, score) {
  this.name = name;
  this.score = score;
}
User.prototype.increment = function () {
  this.score++;
};
const user1 = new Users("John", 0);
user1.increment();
```

## Note about `this` keyword

- In javascript `this` when used with a new keyword will always refer to a newly created object.
- But in methods that are not called with new keyword it will refer to
  1. If function invocation is done using _dot-notation_ i.e. `obj.increment()` then it is implicitly assigned to the object on the left hand side of the dot. i.e. `obj`.
  2. If function is not invoked with _dot-notation_ then it will refer to `window`(in browser)/`global`(In node.js) object.
- So that's why the nested function in javascript OOP fails because the this that it refers to will be `window`/`global`.
  e.g.

```javascript
function CreateObj(name) {
  this.name = name; // here this is newly created empty object
}
CreateObj.prototype.print = function () {
  function getName() {
    return this.name;
  }
  console.log(getName());
};
let obj = new CreateObj("name");
obj.print(); // prints undefined
```

- The javascript is lexically scoped language.
- The arrow functions are lexically scoped so where we define arrow function, the scope there will be the scope for arrow function.
  In below example scope of `getName` will be scope of `print`. So `this` refers to `this` of `print` method.
  e.g.

```javascript
function CreateObj(name) {
    this.name = name // here this is newly created empty object
}
CreateObj.prototype.print = function() {
    function getName = () => {
        return this.name
    }
    console.log(getName())
}
let obj = new CreateObj('name')
obj.print() // prints name
```

- Then again, this will _backfire_ if we use arrow function in global scope, there `this` will be `window`/`global`. See code above related to `methodsProto`.
  e.g.

```javascript
function CreateObj(name) {
  this.name = name; // here this is newly created empty object
}
CreateObj.prototype.print = () => {
  console.log(this.name);
};
let obj = new CreateObj("name");
obj.print(); // prints undefined
```

## [OOP with `class` keyword]

- `class` keyword is just a syntactic sugar on `prototype` keyword use.
  It groups object creator, methods and properties together. But javascript is still using prototype keyword.
- The methods defined in class are added to `prototype` in object part of function - object combo.
- `constructor` is function of function - object combo.

```javascript
class User {
  constructor(name) {
    this.name = name;
  }
  getName() {
    return this.name;
  }
}
let user1 = new User("John");
console.dir(user1); // prints user1 object
console.log(user1.getName()); // prints John
console.log(user1.prototype); // prints undefined
console.log(user1.__proto__); // prints empty object but when debugging we can see it there
```

## Subclassing

### Using Prototype Chain

- `setPrototypeOf()` is a method that can be used to set `__proto__` of object.
- In this subclassing way of using prototype chain, what we do is we create a new object using super class's object.
- Then we set `__proto__` of new object using `setPrototypeOf()` to methods that we want in prototype of subclass.
- The we add base / super class's prototype in chain using `setPrototypeOf()` on prototype of subclass.

```javascript
const userFunctions = {
  sayName: function () {
    console.log(this.name);
  },
  increment: function () {
    this.score++;
  },
};
function userCreator(name, score) {
  const newUser = Object.create(userFunctions);
  newUser.name = name;
  newUser.score = score;
  return newUser;
}
const user1 = userCreator("John", 0);
user1.sayName();

const paidUserFunctions = {
  incrementBalance: function () {
    this.balance++;
  },
};
function paidUserCreator(paidName, paidScore, balance) {
  const newPaidUser = userCreator(paidName, paidScore);
  Object.setPrototypeOf(newPaidUser, paidUserFunctions);
  newPaidUser.balance = balance;
  return newPaidUser;
}
Object.setPrototypeOf(paidUserFunctions, userFunctions); // add link to base class functions using setPrototypeOf
const paidUser1 = paidUserCreator("Jane", 0, 100);
paidUser1.sayName();
```

### Subclassing for objects created using `new` keyword

**_NOTE for `Function` builtin `function`- object_**

- `Function` is a `function` - object that has some methods in it's `prototype`: `call` and `apply`.
- If we do `someFunction.call(obj)` or `someFunction.apply(obj)` then it will call `someFunction` with argument `obj` with `this ` set to `obj`.
  e.g.

```javascript
function someFunction(x) {
  this.x = x;
}
const obj = new someFunction("x"); // here this will be `obj` as we are using `new` keyword

const anotherObj = {}; // plain old normal object
someFunction.call(anotherObj, "y"); // it will invoke `someFunction` where `this` reference will be `anotherObj`
const anotherObj2 = {}; // plain old normal object
someFunction.apply(anotherObj2, ["z"]); // it will invoke `someFunction` where `this` reference will be `anotherObj2`
```

- We use `call` method in constructor of subclass on super constructor function that will create a subclass object using super function??.
- Then we can use `Object.create()` to create a empty `prototype` for subclass with chain / link to super class `prototype`.
  e.g.

```javascript
function User(name) {
  this.name = name;
}
User.prototype.getName = function () {
  return this.name;
};

let user1 = new User("John");

function PaidUser(name, balance) {
  // We are calling here `User` constructor function with this (this will be created when using `new` keyword)
  // So this inside `User` will be actually object created using `new PaidUser('name')`
  User.call(this, name);
  this.balance = balance;
}

// Object.create() creates an empty object but adds __proto__ link to object passed in as argument.
// So we are passing `User`'s prototype in prototype chain for `PaidUser`
PaidUser.prototype = Object.create(User.prototype);

PaidUser.prototype.incrementBalance = function () {
  this.balance++;
};
const newPaidUser = new PaidUser("Jane", 1000);
newPaidUser.getName(); // will return Jane
```

### Subclassing using class keyword

- use `extends` keyword. Just syntactic sugar on above approach.
- `extends` keyword does 2 things
  1. `extends` keyword adds `User` in below example to prototype chain for `PaidUser`. i.e. sets `__proto__` of `PaidUser.prototype` to link to `User.prototype`.
  2. sets `__proto__` of `PaidUser` (see the distinction here class/function `PaidUser` is used **_NOT_** `PaidUser.prototype`) to `User` (**_NOT_** `User.prototype` but `User`).
     <br>This is done for using `super()`, the `__proto__` of `PaidUser` has link to `User` to run `User` constructor when `super()` is invoked.
- `super()` calls constructor of base class (`User`)
- The `super()` internally uses `Reflect.construct()` ([`Reflect.construct()` MDN docs](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Reflect/construct)) which allows call constructor without `new` keyword.
- `this` is not accessible before `super()` is called. The value of `this` is born in `User` the we assign object created by `constructor` of `User` to `this` in `PaidUser`.
- **_NOTE:_** if we set `__proto__` of subclass (`PaidUser`) to the `null` the `super()` call will **fail**.

```javascript
class User {
  constructor(name) {
    this.name = name;
  }
  getName() {
    return this.name;
  }
}
let user1 = new User("John");
class PaidUser extends User {
  constructor(name, balance) {
    super(name);
    this.balance = balance;
  }
}
const newPaidUser = new PaidUser("Jane", 1000);
console.log(newPaidUser.getName()); // prints Jane
```
