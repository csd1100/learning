# Go Basics
- `_` can be used for unused variables.
## Printing
- `fmt` package can be used for printing the data to either console, files, or buffers.
- There are 3 ways to print:
    - `Print()` - Prints without newline at the end.
    - `Println()` - Prints with newline at the end.
    - `Printf()` - C style string formatting (i.e. `%s` - string, `%d` - integers, `%f` - float, `%t` - boolean)
- `fmt` has 3 different set of functions for outputs
    1. `fmt.Print()`, `fmt.Println()`, and `fmt.Printf()` - Sends output to STDOUT / console.
    2. `fmt.Fprint()`, `fmt.Fprintln()`, and `fmt.Fprintf()` - Sends output to File.
    3. `fmt.Sprint()`, `fmt.Sprintln()`, and `fmt.Sprintf()` - Sends output to In memory buffer i.e. variables.
## Packages
- Each go file must have `package <name>` declaration at top.
- `main` package is where execution starts.
- Anything in package starting with Capital letter is automatically exported.
- Exported values should have comment above similar to JavaDoc or JSDoc.
- You can import packages with `import` keyword. `import` starts with repo name then internal path in repo.
- e.g.
```go
package utils
var temp int// not exported
// Some Data (go-doc)
var Data string// exported
func test(){} // not exported
// Function that does something
func Function(){} // exported
// Users with name and ID
type User struct{ // User struct is exported
    ID int // ID is exported
    name string // name is not exported
}
```
## Types and Variables
- Declaration - `var <identifier> <datatype> = <value>`
- Strings always in double quotes.
- Conversions - `<datatype>(another_value)` will type cast another_value to `type`
- There is a special `:=` operator that can be used to drop both use of `var` keyword and type definition.<br> The datatype will be inferred.
```go
    // all 3 are equivalent
    var a string = "Hello"
    var b = "Hello"
    b := "Hello"
```
## Conditionals
- `if`/`else if`/`else` are supported. Parenthesis are not required around condition.
- `if` block can execute code as well and variables defined in that will be scoped in `if`/`else`.
- e.g.
```go
    if err := someFunc(); err != nil {
        // err is scoped here
    }
```
- `switch` is similar to other C style languages but has `or` possible in `case`. Does not have `fallthrough`. i.e. no need for `break`. `fallthrough` can be used to go forward in switch.
- e.g.
```go
    a := 10
    switch a {
        case a < 11, a > 5:
            // or condition
        default:

    }
```
## Loops
- only `for` loop is available not `while`. `for` can be executed similar to while though.
- As java or c++ it does not strict condition of 2 `;`. So it can be used as while.
- e.g.
```go
    // while imitation
    i := 0
    for i < 100 {
        i += 1
    }
```
- `range` keyword can be used to iterate over things. For strings though `range` will need typecasting characters to string.
- e.g.
```go
var sentence = "Lorem ipsum dolor sit amet, qui minim labore adipisicing minim sint cillum sint consectetur cupidatat."
for index, letterNum := range sentence {
    if (index)%2 == 1 {
        fmt.Print(string(letterNum))
    }
}
```
## Functions
- Declared with `func` keyword. Parameters in parenthesis. The datatype of parameters is specified after parameter separated by space. After parenthesis specifies the return datatype.
- Can also return more than 1 values.
- e.g.
```go
// func identifier(param1 datatype, param2 datatype) return_type {}
func someFunc(data int) (int, int) {
    return 0, 1
}
```
- Return values can also have identifier. i.e. we can specify identifiers we want to use in functions for values to be returned. This can be used to remove specifying what should be returned with `return`.
- e.g.
```go
// returns 0,1
func someFunc(data int) (a int, b int) {
    a = 0
    b = 1
    return
}
```
- `...` can be used to pass in variable arguments.
- e.g. `ages` in below code block is list of `int`s.
```go
func someFunc(ages ...int) {
    // ....
}
```
## Arrays
- Declaration - `var identifier [<len>]<datatype>`
- e.g.
```go
scores := [5]int{1,2,3,4,5}
// inferred length of 4 when using `...`
scores := [...]int{1,2,3,4}

```
## Slices
- Slices can be slices of arrays. They are also dynamic in length. We can use `make` keyword to initialize the slice.
- Slices can defined as `var mySlice []<datatype> = make([]<datatype>, <size>, <cap>)`
- Where it will initialize `mySlice` with size of `size` with default values and `cap` will be maximum allocated size for the slice. `cap` is optional.
- `append()` can be used to add to slice. It returns new slice it does not mutate the original slice.
If we append more than `cap` of the slice then `cap` will be increased two-fold. i.e. If `cap` of slice is 4 and we append 5 elements to it then the new `cap` will be 8.
- Now if we append over cap by twice i.e. cap of `sliceOfArray` is 4, and if we create a new slice with element more than cap*2 i.e. more than 8 then it will increase cap by len+1.
- e.g.
```go
var arr [5]int = [5]int{1,2,3,4,5}
var sliceOfArray = arr[1:3]
fmt.Println(sliceOfArray) // will print [2,3]
fmt.Println(len(sliceOfArray)) // will print `2` because slice is of size 2
fmt.Println(cap(sliceOfArray)) // will print `4` because the arr is of len 5 and slice starts
// from index 1 so remaining length of the arr will be the cap for slice
newSlice := append(sliceOfArray, 6, 7, 8, 9, 10) // will return a new slice with
// [2,3,6,7,8,9,10]
fmt.Println(len(newSlice)) // will print `7` because slice is of size 7
fmt.Println(cap(newSlice)) // will print `8` because the increase will be twice for new slice 4->8
newSlice2 := append(sliceOfArray, 6, 7, 8, 9, 10, 11, 12) // will return a new slice with
// [2,3,6,7,8,9,10,11,12]
fmt.Println(len(newSlice2)) // will print `9` because slice is of size 9
fmt.Println(cap(newSlice2)) // will print `10` because the first increase will be twice
// for new slice 4->8 then onwards then cap will be len+1
```
## Maps
- Maps can be similar to dictionaries with key value pair.
- They can be declared as `var map1 map[<key_type>]<value_type>`.
- For maps as well we can initialize it with `make`.
- We can access values using keys like `map[key]`. It returns 2 values 1 -> value, 2 -> ok(boolean) if value is present.
- `delete` can be used to delete values in map. We cannot set value to `nil` delete the values.
- e.g. Here key can be only of datatype `int` and value of `string`.
```go
var map1 map[int]string = make(map[int]string)
map1[1]="sss"
map1[2]="abs"

// shorthand
map2 := map[int]string{
    1: "sss",
    2: "abs",
}
val1, status := map2[4] // returns nothing, false
delete(map2, 2) // will delete "abs"
```
## Structs
- Like C or C++ structs i.e. group of values.
- Example of complex and user-defined datatypes.
- Can be defined as `type <Name> struct {//...}`
- The `type` and `struct` are keywords used to define struct with name `Name`.
- It can have other struct values inside as well.
- Last value in struct when assignment should also have `,` appended.
- e.g.
```go
package main
type User struct {
    ID int
    Name string
}

func main() {
    u := User{
        ID: 1,
        Name: "Test", // `,` is necessary
    }
    fmt.Println(u) // prints {1 Test}
    fmt.Println(reflect.TypeOf(u)) // prints main.User where `main` is package name
}

```
## Pointers
- Pointers can be declared as `var ptr *<datatype>` where `ptr` will be pointer to value of type `<datatype>`.
- `*<datatype>` is different type altogether i.e. pointer type.
- As C and C++ go uses `*` for dereferencing, and `&` for address of variable.
- We can use `:=` operator for pointers by assigning address i.e. `&identifier`
- By default pointers have value of `nil`.
- We cannot assign value directly to pointer variables.
- e.g.
```go
var x int = 1
var intPtr *int = &x
var derefValue = *intPtr
fmt.Println("x: ", x) // prints 1
fmt.Println("intPtr: ", intPtr) // prints address
fmt.Println("TypeOf(intPtr): ", reflect.TypeOf(intPtr)) // prints *int
fmt.Println("derefValue: ", derefValue) // prints 1

name := "abs"
namePointer := &name
value := *namePointer
fmt.Println("name: ", name) // prints abs
fmt.Println("namePointer: ", namePointer) // prints address
fmt.Println("TypeOf(namePointer): ", reflect.TypeOf(namePointer)) // prints *string
fmt.Println("value: ", value) // abs
```
## Pass by Value / Pass by Reference
- Go supports both Pass by Value and Pass by Reference.
- For Pass by Reference pass pointer to variable.
- If we want to update `map` we will use Pass by Reference by using pointers.
- For `struct` we do not need to use `*` and `&`. We can directly access properties of struct.
```go
package utils

type User struct {
    ID int
    Name string
}

func EditName(u *User, name string) {
    u.Name = name
}
//---------------
package main

import (
    "test.com/this/utils"
    "fmt"
    "reflect"
)

func main() {
    u := utils.User{
        ID:   1,
        Name: "Test",
    }
    fmt.Println(u) // prints {1 Test}
    fmt.Println(reflect.TypeOf(u)) // prints utils.User
    utils.EditName(&u, "test2")
    fmt.Println(u) // prints {1 test2}
}
```
## Error handling
- Errors in go are values rather than exceptions.
- There are 2 types
    1. Error - Something bad happened but program doesn't stops.
    2. Panic - Program stops, this is unrecoverable error. Happens at run-time.
