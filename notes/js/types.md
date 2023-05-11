# Types
- In JavaScript and other dynamically typed languages variables do not have types
but values do have types.
- Types are:
    - null
    - undefined
    - number
    - string
    - boolean - true, false
    - Symbol
    - BigInt
    - Object
## `typeof` operator
- `typeof` operator returns string representation of type.
So do **not** use ~~`typeof obj === undefined`~~. It should be `typeof obj === "undefined"`
- but `let v = null; typeof v` returns "object".
- but `let v = []; typeof v` returns "object".
- but `let v = function(){}; typeof v` returns "function".
- `typeof` returns `"undefined"` even for undeclared variables.
- `BigInt` and `number` do not mix well.
## `NaN`
- `NaN` is invalid number. It is not `Not a Number` it is `Invalid Number`
- Conversion of any non-number value (like `string`) in number results in `NaN`.
- Any numeric operation with one of it's operand as `NaN` will always returns `NaN`
- Subtracting `string` from `number` will try to coerce `string` value to `number`
and as it is not a number it will turn the `string` value to `NaN`.
 As said before any operation with `NaN` will return `NaN` so output of subtraction will be `NaN`.
- `NaN` are not equal to each other because of IEEE standard.
So we have JavaScript utility to `Number.isNaN` that can be used to check if value is `NaN`.
- `typeof` `NaN` returns `number`.
- ***NOTE:*** There is another utility `isNaN` (different from `Number.isNaN`) which
should not be used because if we pass string to `isNaN` it returns true.
Because it coerces value passed to it to number and checks if it is `NaN`.
Since `isNaN` shouldn't check the type but it should check if value is `NaN` use `Number.isNaN` (added in ES6).
## Negative Zero
- We can have `-0` value because of IEEE 754 standard.
- JavaScript has weird implementation for `-0`.
 `0 === -0` returns `true`. `-0 < 0 `returns` false`. `-0 > 0 `returns` false`
- But `Object.is` behaves as expected. It is added in ES6.
- `-0` to use for direction in map for still real-life object.
- Any `number` divided by `-0` returns `-Infinity` and if divided by `0` returns `Infinity`.
- e.g.
```javascript
var negZero = -0
negZero === -0 // returns true
negZero === 0 // returns true
Object.is(negZero, 0) //returns false
Object.is(negZero, -0) //returns true
```
## Fundamental Objects
- Use **with** `new` (constructor): `Object()`, `Array()`, `Function()`, `Date()`, `RegExp()`, `Error()`
- Use **without** `new` (constructor): `Number()`, `String()`, `Boolean()`
- `Date` uses 0 based months, i.e. January is 0.

## Type Conversion aka "Coercion"
- If we perform any operation which has requirement of certain type like string concatenation then JavaScript will coerce try to coerce the value in required type. It uses Abstract Operations like `ToPrimitive` for coercion.
- Abstract Operations
    - [`ToPrimitive(hint)`](https://262.ecma-international.org/9.0/#sec-toprimitive) where `hint` is preferred type.
     `hint` is a suggestion, `ToPrimitive` is not always going to return value of type `hint`.
     Generally `hint` is `string` or `number`. `ToPrimitive` is not actual method but conceptual
     operation defined in spec.
      `ToPrimitive` is called recursively till we get primitive value. <br>
      e.g. `valueOf()` -> `hint` is `number`, `toString()` -> `hint` is `string`.
    - [`toString()`](https://262.ecma-international.org/9.0/#sec-tostring) - Uses `ToPrimitive(string)` internally.
        It returns string representation.<br>
        - `null` and `undefined` returns `"null"` and `"undefined"`.
        - `[1,2,3]` returns `"1,2,3"`.
        - `{}` returns `[object Object]`
        <br>
        - ***Caveats*** -
            - `-0` returns `"0"`
            - `[]` empty array returns `""` empty string.
            - `[null, undefined]` returns `","` even though separate `null` and `undefined` returns `"null"` and `"undefined"`.
            - `[[[],[],[]],[]]` returns `",,,"`
            - `[,,,]` returns `",,,"`
            - `{}` returns `[object Object]`
            - `{a:2}` returns `[object Object]`
        - Because of these Caveats do not use `toString()` on arrays.
