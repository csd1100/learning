# Basics

## Compiling / Building and Running a Rust program
- `rustc` is rust compiler which can be used to compile `*.rs` files.
- `rustc` creates a executable file which can be run.
- Cargo is preferred way to manage and build projects.

## Cargo
- Cargo is package manager and build system
- To create a new project run:
    ```bash
    cargo new <project_name>
    ```
    or run following in the new project directory:
    ```bash 
    cargo init
    ```
- `Cargo.toml` has package information like name, version, rust editions
and dependencies.
- To build:
    - With debug enabled it will create executables in `./target/debug/`:
    ```bash
    cargo build
    ```
    - With release mode it will create executable in `./target/release/`
    ```bash
    cargo build --release
    ```
- To build and run:
    - With debug enabled it will create executables in `./target/debug/` and run it:
    ```bash
    cargo run
    ```
    - With release mode it will create executable in `./target/release/` and run it:
    ```bash
    cargo run --release
    ```
- To check syntax:
    ```bash
    cargo check
    ```

## Syntax
### Basic Syntax
- a `main` function is needed for program to run.
- Expressions are those who evaluate to a value. The last expression in function can
be automatically returned.
- Statements are those who do not evaluate to a value. Semi-colons are needed for end of statements.
- Macros are designated by `!`
- Printing something:
    ```rust
    println!("The numbers are: {} {} {} {}", 8, 2, 3, 4);
    println!("The numbers are: {0} {1} {2} {3}", 8, 2, 3, 4);
    println!("The numbers in reverse order are: {3} {2} {1} {0}", 8, 2, 3, 4);
    println!("Printing Array: {:?}", [1, 2, 3, 4, 5]);
    ```
#### String extrapolation
`format!()` macro is used for string extrapolation and storing it in variable.
```rust
let str = "World";
let greeting = format!("Hello {}!", str);
```
#### Panic
    - `panic!()` is where we cannot recover from failure.
    - panic also supports string extrapolation.
#### Function returns
- If we have a expression at end of function without semi-colons then it will be returned.
    ```rust
    fn auto_return() -> i32 {
        let a = 11;
        // NO semi-colon at the end
        a
    }

    fn specified_return() -> i32 {
        let a = 11;
        // requires semi-colon at the end
        return a;
    }
    fn main() {
        println!("{}", auto_return());
        println!("{}", specified_return());
    }
    ```
### Variables and Types
#### Variable declaration
- Variable is declared as
    ```rust
    let <var_name>: <type> = value;
    let <var_name> = value; // type inference
    ```
- They are by default immutable meaning we cannot assign the values to them again.
- To make them mutable use `mut` keyword.
    ```rust
    let mut <var_name> = value;
    <var_name> = 2;
    ```
- To declare unused variable prepend variable name with `_`.
    ```rust
    let _<var_name> = value;
    ```
- Rust allows reuse of variable name called as shadowing. e.g.
    ```rust
    fn main() {
        let num = String::from("12345");
        println!("Number is {}", num);
        let num = num.parse::<i32>().unwrap();
        println!("Number is {}", num);
    }
    ```
this allows using same variable name `num` for data after we have it in required format.
#### Constants
- We can use `const` keyword
    ```rust
    const PI = 3.14;
    ```
- It will be replaced at compile time.

#### Integer Types:
- Signed: `i8`,`i16`,`i32`,`i64`,`i128`,`isize`
- Unsigned: `u8`,`u16`,`u32`,`u64`,`u128`,`usize`
- `isize` and `usize` depend target architecture.
- In case of integer division rust truncates decimal i.e. it does not use `ceil`
or `floor` operations.
- e.g.
    ```rust
    fn main() {
        let integer1: i8 = -100; // decimal
        let integer2: i16 = 0b0100; // binary
        let integer3: i32 = 0o157; // octal
        let integer4: i64 = 0xFF0000; // hexadecimal
        let integer_arch: isize = -1000; // platform dependent size

        // prints in decimal
        print!("Number integer1: {}\n", integer1);
        print!("Number integer2: {}\n", integer2);
        print!("Number integer3: {}\n", integer3);
        print!("Number integer4: {}\n", integer4);
        print!(
            "Number integer_arch: {}\n\t size: {} bytes",
            integer_arch,
            std::mem::size_of_val(&integer_arch)
        );
    }
    ```
#### Floating Types:
- `f32` and `f64`
- e.g.
    ```rust
    fn main() {
        let float1: f32 = 1.2233;
        let float2: f64 = 1.2233e2; // scientific notation

        println!(
            "Floating point numbers: float1: {} float2: {}",
            float1, float2
        );
        println!(
            "Floating point numbers precision upto 2 decimal: float1: {:.2} float2: {:.2}",
            float1, float2
        );
        println!(
            "Floating point numbers with spacing: float1: ***{:<10}*** ***float2: {:<10}***",
            float1, float2
        );
        println!(
            "Floating point numbers with spacing: float1: ***{:>10}*** ***float2: {:>10}***",
            float1, float2
        );
        println!(
            "Floating point numbers with spacing: float1: ***{:~<10}*** ***float2: {:~<10}***",
            float1, float2
        );
        println!(
            "Floating point numbers with spacing: float1: ***{:~>10}*** ***float2: {:~>10}***",
            float1, float2
        );
    }
    ```
- Output
    ```
    Floating point numbers: float1: 1.2233 float2: 122.33
    Floating point numbers precision upto 2 decimal: float1: 1.22 float2: 122.33
    Floating point numbers with spacing: float1: ***1.2233    *** ***float2: 122.33    ***
    Floating point numbers with spacing: float1: ***    1.2233*** ***float2:     122.33***
    Floating point numbers with spacing: float1: ***1.2233~~~~*** ***float2: 122.33~~~~***
    Floating point numbers with spacing: float1: ***~~~~1.2233*** ***float2: ~~~~122.33***
    ```
#### Other Types
- `bool` with values `true`/`false`
- `char`

#### Type conversion
- It can be done by using keyword `as`.
- The integers outside range can also be converted but it will rotate over.  
e.g.
```rust
fn main() {
    let a = 256;
    println!("{}", a as u8); // will print 0 as limit of u8 is 255
    let b = 257;
    println!("{}", b as u8); // will print 1 as limit of u8 is 255
}
```
#### Array
- Zero based index.
- We cannot change size of array.
- We can access elements using `[index]` syntax.
- `[` `]` can be used to declare array.  
e.g.
    ```rust
    let arr = [1, 2, 3];
    ```
- Bound checking is done at compile time and run time.
- Unless it is mutable we cannot change value at index.
- Implements `Debug` trait so it can be printed using `"{:?}"`
- Arrays can be declared before adding values using syntax:
    ```rust
    let <array_name> [<type>; <size_of_arr>];
    ```
size and type are separated by "`;`".
- Arrays can be de-structured. De-structuring makes original variable lose the partial ownership if type of elements of array does not implement `Copy` trait.
- We can use `.iter()` method to iterate over array in for loop.
- e.g.
    ```rust
    fn main() {
        let immut_arr: [i32; 5];
        immut_arr = [1, 2, 3, 4, 5];
        // immut_arr[2] = 6; // throws error
        println!("{:?}", immut_arr);

        let mut mut_arr = [1, 2, 3, 4, 5];
        mut_arr[2] = 6;
        println!("{:?}", mut_arr)

        let arr = [1, 2, 3];
        let [one, two, three] = arr;
        println!("{},{},{}", one , two, three)

    }
    ```
#### Vectors
- generic, sequential and resizable collection.
- `Vec::new()` method can be used to initialize value.
- If we know at compile time what is the least size our vector will be,
it is a best practise to use `Vec::with_capacity(<minimum_required_capacity>)` to initialize vector.
- `<var_name>.push()` is used to add values.
- `<var_name>.insert(<index>, <value>)` can be used to insert value at specified index.
- `vec![]` macro can be used to initialize vectors.
- `[index]` can be used to access values in vectors but can panic if index out of bounds.
- `<var_name>.get(<index>)` can be used to access values. This returns value of type `Option`.
- It is also iterable.
- Also implements `Debug` trait.
- e.g.
    ```rust
    fn main() {
        println!("Using a vector");

        let mut v1: Vec<i32> = Vec::new();

        // Note, could rewrite the above as:
        let mut _v1b = Vec::<i32>::new();

        v1.push(100);
        v1.push(200);
        v1.push(300);
        println!(
            "v1 is {:?}, length is {}, first element is {}",
            v1,
            v1.len(),
            v1[0]
        );

        let mut v2 = vec!["Huey", "Louis", "Dewey"];
        v2.insert(0, "Donald");
        println!("{:?}", v2);

        for item in v2 {
            println!("{}", item)
        }

        let v = [100, 101, 102];

        // This could cause the program to panic (i.e. crash).
        // let item = v[index];

        // Safer to call get(), which returns an Option<T>.
        // Option is an enum that either contains Some<T> or None.
        let index = 2;
        let opt = v.get(index);
        match opt {
            Some(value) => println!("At index {}, found value {}", index, value),
            None => println!("At index {}, no value found", index),
        }

        println!(
            "If you KNOW an Option isn't None, you can unwrap its value. Let's try... {}",
            opt.unwrap()
        )
    }
    ```
#### HashMap
- need to import it using
    ```rust
    use std::collections::HashMap;
    ````
- A dictionary with key value pair.
- `<` `>` are used to define types for key and value.
- Can be declared as:
    ```rust
    let <var_name>: HashMap<type_key, type_value>;
    ```
- `HashMap::new()` can be used to initialize HashMap.
- `<var_name>.insert(<key>,<value>)` can be used to insert values in HashMap.
- `<var_name>.get(<key>)` can be used to get value.
- `<var_name>.entry(<key>).or_insert(<value>)` can be used to insert key and value pair if it doesn't exists.  
    `<var_name>.entry(<key>)` returns `Entry<_, K, V>`.  
    `Entry` can be either `Occupied` or `Vacant`.

- e.g.
```rust
use std::collections::HashMap;

fn main() {
    println!("\nUsing a HashMap");

    let mut m: HashMap<String, i32> = HashMap::new();
    m.insert(String::from("UK"), 44);
    m.insert(String::from("NO"), 47);
    m.insert(String::from("SG"), 65);
    println!("m is {:?}, length is {}", m, m.len());

    println!("If you only want to insert if doesn't already exist...");
    let val = m.entry(String::from("UK")).or_insert(44);
    println!("Value for UK is {}", val);

    // This would cause the program to panic (i.e. crash).
    // let val = m["SA"];
    // println!("Value for SA is {}", val);

    // Better to call get(), which returns an Option<T>.
    // Option is an enum that either contains Some<T> or None.
    let opt = m.get("SA");
    match opt {
        Some(val) => println!("Value for SA is {}", val),
        None => println!("No value found for SA"),
    }
}
```

#### `String`
- `String` type is actually struct.
- It does not implement `Copy` trait.
- So `String`s can be mutated if defined so unlike other programming languages.
- It implements `Drop` trait. It has `drop()` method which is called when
`String` goes out of scope.

#### Tuple
- Has fixed size
- Can store values of different types.
- We can declare tuple using `(` `)`  
e.g.
    ```rust
    let tuple1 = (100, String::from"Hundred");
    ```
- "`.`" operator can be used to access values inside Tuple with index  
e.g.
    ```rust
    <tuple_var_name>.index
    ```
- Implements `Debug` trait.
- Tuples can be de-structured as well. For partial de-structuring use `_`.  
De-structuring makes original tuple variable lose the partial ownership if element of tuple
does not implement `Copy` trait.
- There is a special tuple called `Unit`. It is returned when function doesn't 
return anything.
- Can be mutable using `mut` keyword.
- e.g.
    ```rust
    fn main() {
        let number: (i32, String);
        number = (100, String::from("Hundred"));
        println!(
            "Number {:?}\n\t in numerical format {},\n\t in words {}",
            number, number.0, number.1
        );
        let number2 = (99, String::from("Ninety nine"));
        let (numeric, words) = number2;
        println!(
            "Number \n\t in numerical format {},\n\t in words {}",
            numeric, words
        );
        // let unit: () = ();
    }
    ```
#### Structs
- Structs are defined using `struct` keyword.
- `{`, `}` are used to Create and Define the struct.
- We can access fields using `<var_name>.<field_name>` notation.
- Structs can be de-structured as well with syntax:  
    ```rust
    let <struct_name> { <field_name1>, <field_name2> } = <struct_var>;
    ```
- The field name and de-structured variable name should match. i.e. In above
example `<field_name1>` should be actual field of `struct`.  
De-structuring `struct` can make original lose partial ownership if one of the field de-structured does not
implement `Copy` trait.
- Can be mutable using `mut` keyword.
- e.g.
```rust
struct Point {
    x: i64,
    y: i64,
    z: i64,
}

fn new_point(x: i64, y: i64, z: i64) -> Point {
    Point {
        x: x,
        y: y,
        z: z,
    }
}

fn simpler_new_point(x: i64, y: i64, z: i64) -> Point {
    // the variable names here must be x , y, z i.e. same as fields
    Point { x, y, z }
}

fn main() {
    let p1 = simpler_new_point(1, 2, 3);
    let x = p1.x;
    let y = p1.y;
    let z = p1.z;
    println!("{:?}", p1);
    println!("{},{},{}", x, y, z);

    let p2 = new_point(1, 2, 3);
    let Point { x, y, z } = p2;
    println!("{:?}", p2);
    println!("{},{},{}", x, y, z);

    // to ignore y
    // let Point { x, y: _, z } = p2;
    // to everything else than x, z use `..`
    // let Point { x, z, .. } = p2;
    // to everything else than x
    // let Point { x, .. } = p2;
}
```
#### Enums
- Closed set of values
- Values inside enums are called "variants"
- You can access variants using `::`.
- Different Types of enum
    - Simple enum:
        ```rust
        enum Color {
            Red,
            Green,
            Blue,
        }
        fn main() {
            let r = Color::Red;
            let _g = Color::Green;
            let _b = Color::Blue;

            let c = r;
            match c {
                Color::Red => {
                    println!("Red");
                }
                Color::Green => {
                    println!("Green");
                }
                Color::Blue => {
                    println!("Blue");
                }
            }
        }
        ```
    - Enums with variant values
        - Enums can have variants with `struct` values, `tuple` values or type parameters.
        - We can pass value to enum variants while defining a var with it.
        - Enums with data will have size of largest type used for values.  
        e.g. if enum has i32, string, f64 then the size will be of string because
        it is largest.
            ```rust
            enum Level {
                // enum with tuple variants
                TRACE(String),
                DEBUG(String),
                INFO(String),
                WARN(String),
                ERROR(String),
            }
            fn main() {
                let logger = Level::INFO(String::from("./info.log"));
                match logger {
                    Level::INFO(path) => {
                        println!("Logs will be saved at path {}", path);
                    }
                    _ => {
                        println!("Logs will be saved elsewhere");
                    }
                };
            }
            ```
##### Commonly used enums
- `Option<T>` - It can have 2 types of value
    1. `Some(T)` - i.e. it has atleast some value of some type(generic `T`).
    1. `None` - It has nothing stored (Similar to null value in nullables in other languages).
    - Here `T` is a type parameter.
    - `unwrap()` - can be used to get the value.
    - `unwrap_or(x)` - can be used to get the value if value is not there returns 'x'.
- `Result<T, E>` - It also has 2 types of values.
    1. `Ok(T)` - If result does not have a error and value.
    1. `Err(E)` - There is error `E` present.
    - We do not throw exceptions we use result type to handle errors.
    - `.expect(msg)` can be used if error is present to panic and exit with error 'msg'.
#### Methods
- `impl` keyword can be used to create a methods.
- We can use this to namespace functions.
- `self` (with lower case `s`) is a keyword that can be used to access `this` (which is not a keyword)
object in methods inside `impl` block.
- `Self` (with upper case `S`) is keyword that can be used as return type of method inside `impl`
block.

### Flow control
#### Branching statements
##### `if/else if/else`
```rust
fn main() {
    let a = 100;
    if a > 100 {
        println!("Greater than 100.")
    } else if a < 100 {
        println!("Less than 100.")
    } else {
        println!("Equals to 100.")
    }
}
```
- We can also return values from `if/else` statements. But we have to make sure  
value is returned in every case.  
e.g.
    ```rust
    fn main() {
        let a: String;
        let b = 100;
        a = if b == 100 {
            String::from("value")
        } else {
            String::from("none")
        };
        println!("{}", a)
    }
    ```
##### `match`
- similar to switch
- match on
    - specific value
    - range of value
    - multiple conditions
    - conditions
- First match is selected.
- Must handle all possible values and Must have a default case where all conditions  
that are not specifically matched should be handled.
- Can also return values similar to if.
```rust
fn main() {
    let a = 100;
    // only prints "Hundred!" as when 1st match is found it exits.
    match a {
        // exact match
        100 => println!("Hundred!"),
        // conditional
        x if x > 99 => {
            println!("Greater than 99!");
        }
        200 | 300 => println!("Multiples of Hundred!"),
        _ => {
            println!("Number {}", a);
        }
    }
    // range
    match a {
        10..=49 => println!("Between 10 and 49!"), //includes 49;
        50..=100 => println!("Between 50 and 100!"),
        _ => {
            println!("Number {}", a);
        }
    }
    let b;
    b = match a {
        100 => a * 2,
        _ => 0,
    };
    println!("b after matching a {}", b);
}
```
#### Loops
- `while`
    - While condition is true
- `for`
    - Iterate over iterable
```rust
fn main() {
    let mut i = 0;
    while i < 10 {
        println!("{}", i);
        i += 1;
    }

    for i in 1..=10 {
        println!("{}", i);
    }

    let arr = [1, 2, 3, 4, 5];
    for i in arr {
        println!("{}", i);
    }
}
```
- `loop`
    - Infinite loop.
    - Use `break` and `continue` to control execution flow.
