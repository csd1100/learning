# Go Basics

- `_` can be used for unused variables.
- go prefers tabs over spaces. [docs](https://go.dev/doc/effective_go#formatting)

## Module

- A module is group of packages.

## Packages

- `main` package is where execution starts. ( and in `main` function. )
- Each go file must have `package <name>` declaration at top.
- Single directory can have only **one** package.
- All the files with same package should be in same directory.
- Everything in package scope is available for entire package. i.e.
  Each file in package shares everything without need to import the file.
- Package name and file / directory name may or may not to be same.
- Anything in package starting with Capital letter (TitleCase) is automatically exported.
- camelCase variables are private to package.
- Exported values should have comment above similar to JavaDoc or JSDoc.
- e.g.

```go
package utils

var temp int// not exported

// Some Data (go-doc)
var Data string// exported

func test(){} // not exported

// Function that does something (go-doc)
func Function(){} // exported

// Users with name and ID (go-doc)
type User struct{ // User struct is exported
	ID int // ID is exported
	name string // name is not exported
}
```

- Imports are per file though not package level.
- You can import packages with `import` keyword. `import` starts with module name
  then internal path in repo.
- To import the package we have to give directory path to `import` declaration,
  but to access exported values we need to use package name which might not be
  similar to directory.
- e.g. In following example the `not_tmp` package is in `tmp` directory.
  So we `import` directory `module/tmp`. But to access actual package we need
  to use package name i.e. `not_tmp`.

```go
// path: ./tmp/package-file.go
package not_tmp

const Test = 1
```

```go
// path: ./main.go
package main

import "module/tmp" // need to import directory `tmp`

func main() {
	print(not_tmp.Test) // need to use package name `not_tmp`
}
```

## Types, Variables and Constants

- Declaration - `var <identifier> <datatype> = <value>`
- Declaration - `const <identifier> <string|bool|int> = value`
- Constants can only be of type `string`, `bool`, or `int`. They **must** have
  value at the time of declaration.
- Strings always in double quotes.
- Conversions - `<datatype>(another_value)` will type cast another_value to `type`
- There is a special `:=` operator that can be used to drop both use of `var`
  keyword and type definition.
  The datatype will be inferred. Doesn't work outside functions.
- Each type has its own zero value like 0 , "", false.
- Strings are stored in memory as 2 WORDS (a WORD is of size int on that specific platform).
  1st WORD contain address of 1st char of the string and 2nd Word stores length of the string.

```go
const t bool = true
const i = 100000 // number is of `kind` integer, here precision can be high so number can be very big
// const i2 int8 = 10000 // number has `type` uint8 ,this will error as it has
// type `uint8` so value is out of bounds
const num = 12.1233 // here the precision of 256 bit, this is of `kind` floating
const num2 float64 = 23.11 // here the precision is of 64 bit, this is of `type` float64
// kinds have more precision than type
// all 3 are equivalent
var a string = "Hello"
var b = "Hello"
c := "Hello"
```

## Conditionals

- `if`/`else if`/`else` are supported. Parenthesis are not required around condition.
- `if` block can execute code as well and variables defined in that will be
  scoped in `if`/`else`.
- The condition should be last in execution though. Like in below example
  condition is last `err != nil`.
- e.g.

```go
if err := someFunc(); err != nil {
	// err is scoped here
}
```

- `switch` is kind of similar to other C style languages. But,
  - Does not have `break`.
  - To go to next cases `fallthrough` can be used.
  - Has logical OR possible in `case`.
  - The predicate itself can be removed and cases can have boolean evaluation.
- e.g.

```go
switch {
	case a == 9:
	// breaks here
	case a == 10:
	//...
		fallthrough // executes next conditions as well
	case a < 11, a > 5:
	// or condition
	default:
}
```

## Loops

- only `for` loop is available not `while`. `for` can be executed similar to
  while though.
- As java or c++ it does not strict condition of 2 `;`. So it can be used as while.
- e.g.

```go
// while imitation
i := 0
for i < 100 {
	i += 1
}
```

- `range` keyword can be used to iterate over things. For strings though `range`
  will need typecasting characters to string.
- e.g.

```go
var sentence = "Lorem ipsum dolor sit amet, qui minim labore adipisicing minim sint cillum sint consectetur cupidatat."
for index, letterNum := range sentence {
	if (index)%2 == 1 {
		fmt.Print(string(letterNum))
	}
}
```

### value and pointer semantics for `for..range`

- There are two variants to for..range in terms of mutability and value, pointer
  semantics.
- Value semantic variant:

  - here the values are copied when we are iterating over an array.
  - i.e. whenever we perform any operation the original array is not affected.
  - only values in scope of the loop are affected.
  - e.g. in following example original array `numbers` will not have "number"
    appended to its values.

  ```go
  func main() {
    var numbers [3]string
    numbers[0] = "one"
    numbers[1] = "two"
    numbers[2] = "three"
    for i, number := range numbers {
      number += " number"
      fmt.Println(i, number)
    }
    fmt.Println(numbers)
  }
  ```

- Pointer semantic variant:

  - in this case original array can be edited if we use indexes to edit original
    array rather than variable in array.
  - e.g. here original array will be affected as we are directly editing original
    values.

  ```go
  func main() {
    var numbers [3]string
    numbers[0] = "one"
    numbers[1] = "two"
    numbers[2] = "three"
    for i := range numbers {
      numbers[i] += " numbers"
    }
    fmt.Println(numbers)
  }
  ```

  OR

  ```go
  func main() {
    var numbers [3]string
    numbers[0] = "one"
    numbers[1] = "two"
    numbers[2] = "three"
    for i, number := range numbers {
      // updating array not var number which is a copy of numbers[i]
      numbers[i] += " numbers"
      fmt.Println(i, number)
    }
    fmt.Println(numbers)
  }
  ```

## Functions

- Declared with `func` keyword. Parameters in parenthesis.
  The datatype of parameters is specified after parameter separated by space.
  After parenthesis specifies the return datatype.
- Can also return more than 1 values. Greatly used for error handling.
- e.g.

```go
// func identifier(param1 datatype, param2 datatype) return_type {}
func someFunc(data int) (int, int) {
	return 0, 1
}
```

- Return values can also have identifier. i.e. We can specify identifiers we want
  to use in functions for values to be returned.
  This can be used to remove specifying what should be returned with `return`.
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

### Closures

- Go also supports closures but closure values are actually reference.
- So if actual value changes before execution the closure will also get updated value.
- e.g. The program will print `3` three times because at the time of execution
  of `printInt(i)` in goroutines,
  `i` is 3 because `i` is closure variable and will have reference to outer
  scope `i` whose value is already 3.

```go
// Don't do this
package main

import (
	"fmt"
	"sync"
)

func printInt(val int) {
	fmt.Println(val)
}

func main() {
	wg := sync.WaitGroup{}
	for  i := 0; i < 3 ; i++ {
		wg.Add(1)
		go func() {
			printInt(i) // will always print 3
			wg.Done()
		}()
	}
	wg.Wait()
}
```

### `init()` function

- There is a special function named `init()` which can be used to initialize the
  data.
- This is executed before execution of `main`.
- There can be multiple `init()` function definition in a same package.
- Multiple `init()` can be used to modularize initialization of data.
- The `init()` functions are executed in the order of definition. And for package
  `init()` whenever the package file is used in code before using that part `init()`
  is executed.
- e.g. `init()` is invoked before `main`.

```go
package main

var greeting string
func init() {
	greeting = "Hello"
}
func main() {
	println(greeting) // prints hello
}

```

### `defer` keyword

- `defer` keyword can defer the invocation of the functions till _before_ the
  `return` or the completion of function.
- `defer` calls can be used for cleanup for `panic`s.
- e.g. Will print in sequence in comments. The first `defer` will be done last
  because it was added before. It is similar to stack. We are stacking defer calls
  so last in is first out.

```go
functions test() int {
	defer fmt.Println("defer") // 6
	fmt.Println("first") // 1
	defer fmt.Println("defer 2") // 5
	fmt.Println("second") // 2
	defer fmt.Println("defer 3") // 4
	fmt.Println("third") // 3
	return 1
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

- It is type that can be classified as reference type.
- Slices can be slices of arrays. They are also dynamic in length. We can use
  `make` keyword to initialize the slice.
- Slices can be also considered as similar to vectors of other languages.
- They have similar syntax of array but the read and write is done similar to
  pointer semantics. i.e. internal data structure is mutated and **not** a copy of the
  data.
- Slices have different empty and zero value.

  - zero value of slice is 3 WORDS: nil, len: 0, cap: 0 , e.g.

  ```go
  var mySlice []string // zero value i.e. no internal array
  ```

  - the empty value of slice is again 3 WORDS: pointer to empty struct, len: 0, cap: 0.

  ```go
  var mySlice []string = []slice{} // empty value i.e. points to empty struct{}
  ```

- Slices can defined as `var mySlice []<datatype> = make([]<datatype>, <len>, <cap>)`
- Where it will initialize `mySlice` with length of `len` with default values and
  `cap` will be maximum allocated size for the slice. `cap` is optional.
- `append()` can be used to add to slice. It returns new slice it does not mutate
  the original slice.
- as `append` returns a copy, always try to assign it back to same variable as it
  will cause old reference cleaned up. Variable is referencing new copy, so old copy
  will get GC'd. i.e. `data = append(data, value)` <- Here data is reassigned to new copy.
- calling `append` on slice defined as `make([]int, 10, 10)` will cause appending value
  at index **11** and **not 0** because we have already initialized slice with 10 zero values.  
  To ensure append works as expected i.e. fill the slice do `make([]int, 0, 10.)`
- When `len` and `cap` become equal, and elements are less than 1024, the `cap`
  is increased by 100% (double).  
  If elements are more than 1024 `cap` will increase by around 25%.
- If we append more than `cap` of the slice then `cap` will be increased two-fold.
  i.e. If `cap` of slice is 4 and we append 5 elements to it then the new `cap`
  will be 8.
- Now if we append over cap by twice i.e. cap of `sliceOfArray` is 4, and if we
  create a new slice with element more than cap \* 2 i.e. more than 8 then it will
  increase cap by len+1.
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

- When we create slice of slice when we edit newly created slice original is also
  modified. If we append to the newly created slice then it will affect
  the original slice if it has capacity. e.g.
  ```go
  func main() {
  	b := make([]int, 3, 5)
  	b[0] = 0
  	b[1] = 1
  	b[2] = 2
  	// b - [0,1,2]
  	// c := b[0:1]
  	// c = append(c, 3) // b - 0 3 2; c - 0 3
  	// c := b[1:2]
  	// c = append(c, 4) // b - 0 1 4; c - 1 4
  	c := b[0:2:2]
  	c = append(c, 5) // as capacity was 2 and new (3rd) was added, a new copy was made
  	// b - 0 1 2; c - 0 1 5
  	c[0] = 100 // b - 0 1 2; c - 100 1 5
  	fmt.Println(b)
  	fmt.Println(c)
  }
  ```

### Arrays vs Slices

- arrays are of fixed length while slices are dynamic
- arrays are stored as 2 WORDS, 1. Pointer to array and 2. Length of the array
- slices are stored as 3 WORDS, 1. Pointer to the slice and 2. Length of the Slice 3. Capacity of the slice
- Array is a builtin primitive type and Slice can be considered a reference type
- When we pass an array using value semantics to a function a new copy of array is passed.
- i.e. original array is not modified.
- e.g.

```go
func updateOne(numbers [3]string) {
	numbers[0] = "1"
}

func main() {
	var numbers [3]string
	numbers[0] = "one"
	numbers[1] = "two"
	numbers[2] = "three"
	updateOne(numbers)
	fmt.Println(numbers) // prints - one two three
}
```

- When we pass a slice using value semantics to a function we can edit original
  slice as same as reference being passed to a function so there is no need to
  pass a pointer type to function i.e. do NOT pass `slice *[]string` but pass `slice []string`
- i.e. original slice is modified

```go
func updateOne(numbers []string) {
	numbers[0] = "1"
}

func main() {
	var numbers []string = make([]string, 3)
	numbers[0] = "one"
	numbers[1] = "two"
	numbers[2] = "three"
	updateOne(numbers)
	fmt.Println(numbers) // prints - 1 two three
}
```

## Maps

- map is of reference type i.e. when we pass map value to a function original
  is also modified.
- Maps can be similar to dictionaries with key value pair.
- They can be declared as `var map1 map[<key_type>]<value_type>`.
- For maps as well we can initialize it with `make`.
- We can access values using keys like `map[key]`. It returns 2 values 1 -> value,
  2 -> ok(boolean) if value is present.
- `delete` can be used to delete values in map. We cannot set value to `nil`
  delete the values.
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

## Custom types and Aliases

### Aliases

- Aliases are just alias/name for existing type. Similar to creating link to type.
- Values created with alias can be used with original type directly without need
  for casting.
- **Syntax** - `type <newName> = <type>`
- e.g.

```go
package main

// alias
type float = float64

func main() {
	var a float64 = 13.4
	var b float = 22.2
	c := a + b // can be done without any typecasting
	print(c)
}
```

### Custom Types

- Custom Types are types created using existing types.
- They can be used to add semantic meaning to code.
- We cannot perform operations between custom types and original types from
  they are created without typecasting.
- Can be used for creating functions with more semantic meaning.
- Can be used to add methods with semantic meaning on existing types.
- **Syntax** - `type <new_type_name> <existing_type>`
- e.g.

```go
package main
// type
type distance float64

func main() {
	var a float64 = 13.4
	var b distance = 22.2
	// c := a + b // cannot be done; will throw error about types
	c := distance(a) + b // need to typecast before using float64 values in arithmetics
	print(c)
}
```

### Methods

- A way to add functions specific to types.
- Can be only added on local types.
- e.g. It can be used to create `toString()` method for `map` or `struct`.
- `String()` method is default method like `toString()` for Java.  
   **_NOTE_**: `println()`(all other print methods) method do not use `String()`
  only `fmt.Println()`(all fmt functions) does.
- **Syntax** - `func (valOfType <type_for_which_method>) methodName([param1 <any_type>]) <return_type> {}`
- e.g.

```go
package main

import "fmt"

// type
type distanceKM float64
type distanceM float64

func (km distanceKM) toMeter() distanceM {
	return distanceM(float64(km) * 1000.) // the `.` at end of 1000 is not a typo
	// can be used to denote a floating point number - 1000. (1000.0)
}

func (km distanceKM) toString() string {
	return fmt.Sprintf("%v KM", km)
}

func (m distanceM) String() string {
	return fmt.Sprintf("%v M", float64(m))
}

func main() {
	var a float64 = 13.4
	var b distanceKM = 22.2
	c := distanceKM(a) + b
	fmt.Println(c)
	fmt.Println(c.toString())
	fmt.Println(c.toMeter()) // will automatically use `String()`
}
```

### Structures

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

#### Embedding

- Embedding type is similar to JavaScript's inheritance using prototypes.
- It's not like OOP inheritance. In the end they are different types altogether.
- For implementing _'embedding of a type_' just add a type in struct definition
  without identifier.
- The only problem is that we cannot directly add properties for embedded type
  in constructor.
- Methods are also embedded.
- There can be problem with name collision with multiple embeddings.
- We can override methods in embedded type. But we can also use base methods as
  is if not defined in embedded.
- e.g.

```go
type User struct {
	Id int
	Name string
}
type PaidUser struct {
	User //embedded type User
	Balance float64
}

func createPaidUser(id int, name string, balance float64) PaidUser {
	return PaidUser{
		// need to pass a User instead of properties separated
		User {
			Id: id,
			Name: name,
		},
		balance,
	}
}

// another way
func newPaidUser(id int, name string, balance float64) PaidUser {
	p := PaidUser{}
	p.Id = id
	p.Name = name
	p.Balance = balance
	return p
}
```

- e.g.2.

```go
package main

import "fmt"

type Interface interface {
	PrintsHello()
	PrintsXXX()
}

type Base struct {
	Name string
}

func (b Base) PrintsXXX() {
	fmt.Println("xxx")
}

func (b Base) PrintsHello() {
	fmt.Println("Hello ", b.Name)
}

type Embedded struct {
	Base
}

// override PrintsXXX from Base
func (e Embedded) PrintsXXX() {
	fmt.Println("yyy")
}

func main() {
	var B Interface = Base{
		Name: "Base",
	}
	B.PrintsXXX() // prints "xxx"
	B.PrintsHello() // prints "Hello Base"

	// implements same interface automatically cause of embedding
	// even though only PrintsXXX is implemented
	var E Interface = Embedded{
		Base{Name: "Embedded"},
	}
	E.PrintsXXX() // prints "yyy"
	E.PrintsHello() // prints "Hello Embedded"
}
```

- The base methods will be called only with embedded data not entire struct.

```go
package main

import (
	"fmt"
)

type Executable interface {
	Exec(args string) error
}

func IsExecutable(exe Executable) {
	fmt.Printf("\n%+v is Executable\n", exe)
}

type Base struct {
	Command string
}

func (base Base) Exec(args string) error {
	fmt.Printf("\nExecuting %+v\n", base)
	fmt.Println("args ", args)
	return nil
}

type Sub struct {
	sub string
	Base
}

func (sub Sub) Exec(args string) error {
	fmt.Printf("\nExecuting sub %+v\n", sub)
	fmt.Println("args ", args)
	return nil
}

func (sub Sub) Test(args string) error {
	fmt.Printf("\nsub Test\n%+v\n", sub)
	fmt.Println(args)
	return sub.Exec(args)
}

type Subber struct {
	subber string
	Sub
}

func (subber Subber) Exec(args string) error {
	return fmt.Errorf("some error")
}

func main() {
	base := Base{Command: "base"}
	IsExecutable(base)
	err := base.Exec("base")
	if err != nil {
		fmt.Println(err)
	}

	sub := Sub{
		sub: "sub",
		Base: Base{
			Command: "sub",
		},
	}

	IsExecutable(sub)
	err = sub.Test("sub")
	if err != nil {
		fmt.Println(err)
	}

	subber := Subber{
		subber: "subber",
		Sub: Sub{
			sub:  "subber",
			Base: Base{Command: "subber"},
		},
	}

	IsExecutable(subber)
	err = subber.Test("subber")
	if err != nil {
		fmt.Println(err)
	}
}
```

The Output of this will be

```stdout
{Command:base} is Executable

Executing {Command:base}
args  base

{sub:sub Base:{Command:sub}} is Executable

sub Test
{sub:sub Base:{Command:sub}}
sub

Executing sub {sub:sub Base:{Command:sub}}
args  sub

{subber:subber Sub:{sub:subber Base:{Command:subber}}} is Executable

sub Test
{sub:subber Base:{Command:subber}}
subber

Executing sub {sub:subber Base:{Command:subber}}
args  subber
```

In above output we can see for `subber.Test` only embedded `Sub` is passed.

### Interfaces

- List of of method signatures.
- Emulation of Polymorphism.
- If **ALL** method signatures in interface are implemented by `struct` or the
  type then it automatically (implicitly) implements the interface.
- i.e. We don't need to use any keyword.
- **Syntax** - `type <name> interface{ //... method signatures }`
- Using empty interface (without any methods so every type is considered to
  implement it) we can create slices of any type.
- We can cast value in interface by `value.(<type>)`
- e.g.

```go
package main

import "fmt"

type Printable interface {
	Prints() string
}

type User struct {
	Id   int
	Name string
}

type PaidUser struct {
	Id      int
	Name    string
	Balance float64
}

// implicit implementation of interface Printable
func (u User) Prints() string {
	return fmt.Sprintf("%v", u.Name)
}

// implicit implementation of interface Printable
func (p PaidUser) Prints() string {
	return fmt.Sprintf("%v*", p.Name)
}

type Any interface {}

func main() {
	u := User{
		Id:   1,
		Name: "John Doe",
	}
	pu := PaidUser{
		Id:      1,
		Name:    "Jane Doe",
		Balance: 10000.,
	}

	var printableUsers [2]Printable
	printableUsers[0] = u
	printableUsers[1] = pu

	// casting of value
	fmt.Println(printableUsers[0].(User).Prints()) // printableUsers[0] will be cast to User

	for _, user := range printableUsers {
		fmt.Println(user.Prints())
	}

	// slice of all types
	var sliceOfAnyType []Any
	sliceOfAnyType = append(sliceOfAnyType, "f32")
	sliceOfAnyType = append(sliceOfAnyType, 32)
	// ^Above can be easily done as
	var sliceOfAll []interface{}
	sliceOfAll = append(sliceOfAll, "f32")
	sliceOfAll = append(sliceOfAll, 32)
	fmt.Println(sliceOfAnyType)
	fmt.Println(sliceOfAll)
}
```

## Pointers

- Pointers can be declared as `var ptr *<datatype>` where `ptr` will be pointer
  to value of type `<datatype>`.
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

- Go supports both Pass by Value (always) and Pass by Reference (pointer).
- But it is always pass by value.
- For Pass by Reference pass pointer to variable.
- If we want to update `map` we will use Pass by Reference by using pointers.
- For `struct` we do not need to use `*` and `&`. We can directly access
  properties of struct.

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
  2. Panic - `panic()` - Program stops, this is unrecoverable error. Happens at run-time.

## GO-Routines

- Multi-threading approach in go.
- Go has main goroutine which runs `main.main()`.
- If we add `go` keyword at the start of the function call it will spawn a new
  goroutine to execute the function.
- e.g.

```go
package main

import "fmt"

func prints5Times(str string) {
	for i := 0; i < 5; i++ {
		fmt.Println(str)
	}
}

func main() {
	go prints5Times("hello") // spawns a new goroutine
	prints5Times("bye")
}
```

- In main if we run each function call in goroutine then most probably nothing
  happens because main goroutine ends
  after spawning goroutines.

```go
package main

import "fmt"

func prints5Times(str string) {
	for i := 0; i < 5; i++ {
		fmt.Println(str)
	}
}

func main() {
	// will do nothing as main goroutine will just spawn below 2 goroutine and exit
	go prints5Times("hello")
	go prints5Times("bye")
}
```

### Channels

- Can be used for communication between multiple goroutines.
- It is type of variable declared by using keyword `chan`
- **Syntax** - `var <name> chan <type>`
- A channel can be initialized with `make` function.
- Value can be assigned to channel by using `<-` operator.
- A goroutine can wait for value from channel also by using `<-` variable.
  Also we can access data passed through channel same way.
- We can use `close(chan)` method to close the channel.
- In `make` we can also define how many values to wait for.
  e.g. `c := make(chan string, 2)` then we can setup waiting for `c` for 2 values across channel.
  If we do not send `2` values for `c` but add 2 listeners then program will `panic`.
- e.g.

```go
package main

import (
	"fmt"
	"time"
)

func prints5Times(str string, done chan bool) {
	for i := 0; i < 5; i++ {
		fmt.Println(str)
	}
	time.Sleep(time.Second * 2) // pause for 2 sec
	done <- true                // send value across channel between goroutines
}

func main() {
	var done chan bool
	done = make(chan bool) // initialize channel *MUST*
	go prints5Times("hello", done)
	isDone := <-done // wait for value from other goroutine
	if isDone {
		fmt.Println("bye")
	}
}
```

- A channel sent to multiple goroutines will round-robin the sending of message.
- e.g. in below example 1st 2 messages will go to id 3 but after that every message
  is in round-robin manner. This behavior is noted when all 3 are available at
  same time. Need to look into further why 1st 2 messages are for 3.
- guess it's 3 because it was just started so was ready to receive the value.

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("Hello World!")
	ch := make(chan bool)
	go print_from(1, ch)
	go print_from(2, ch)
	go print_from(3, ch)
	for {
		ch <- true
		time.Sleep(5 * time.Second)
	}
}

func print_from(id int, ch chan bool) {
	for {
		<-ch
		fmt.Printf("[id: %+v]\n", id)
	}
}

```

```STDOUT
Hello World!
[id: 3]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
[id: 1]
[id: 2]
[id: 3]
^Csignal: interrupt
```

- Whichever goroutine is ready to read will be preferred if multiple are not available.
- e.g.

```go
package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	fmt.Println("Hello World!")
	ch := make(chan bool)
	go print_from(1, ch)
	go print_from(3, ch)
	go print_from(2, ch)
	for {
		ch <- true
		time.Sleep(1 * time.Second)
	}
}

func print_from(id int, ch chan bool) {
	for {
		<-ch
		rnd := rand.Intn(8)
		fmt.Printf("\t[rnd: %+v]\n", rnd)
		fmt.Printf("[id: %+v]\n", id)
		time.Sleep(time.Duration(rnd) * time.Second)
	}
}
```

```stdout
Hello World!
[timenow: 2024-02-19 14:49:39.834147829 +0000 UTC]
[id: 2]
	[rnd: 4]
[timenow: 2024-02-19 14:49:40.834255749 +0000 UTC]
[id: 1]
	[rnd: 0]
[timenow: 2024-02-19 14:49:41.834639688 +0000 UTC]
[id: 3]
	[rnd: 1]
[timenow: 2024-02-19 14:49:42.834718437 +0000 UTC]
[id: 1]
	[rnd: 6]
[timenow: 2024-02-19 14:49:43.834789701 +0000 UTC]
[id: 3]
	[rnd: 2]
[timenow: 2024-02-19 14:49:44.834833784 +0000 UTC]
[id: 2]
	[rnd: 7]
[timenow: 2024-02-19 14:49:45.834896261 +0000 UTC]
[id: 3]
	[rnd: 1]
[timenow: 2024-02-19 14:49:46.835257275 +0000 UTC]
[id: 3]
	[rnd: 2]
[timenow: 2024-02-19 14:49:48.8351038 +0000 UTC]
[id: 1]
	[rnd: 6]
[timenow: 2024-02-19 14:49:49.835367687 +0000 UTC]
[id: 3]
	[rnd: 2]
[timenow: 2024-02-19 14:49:51.835108717 +0000 UTC]
[id: 2]
	[rnd: 5]
[timenow: 2024-02-19 14:49:52.83525088 +0000 UTC]
[id: 3]
	[rnd: 1]
```
