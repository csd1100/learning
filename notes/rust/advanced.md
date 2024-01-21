# Advanced
## Ownership and Borrowing
### Scope
    - Scope of variable is limited between `{}`
    - Variable is limited to scope if it is referred outside scope we will get error  
    at compile-time.
### Copying
- There is `Copy` trait if it is implemented by type then, when we reassign value to other  
variable the ownership is not transferred.
- e.g. `i32`
### Moving
- If `Copy` trait is *NOT* implemented by type then ownership is transferred or moved.
- e.g. `String`
### Cloning
- If `Copy` trait is *NOT* implemented by type but you don't want to lose variable value  
we can clone value and use it for later.
- e.g. `String`
### Ownership
- Only a single variable(label??) can own a object.
- The rust can use this to deallocate memory if that variable reference becomes invalid.
- Reassignment or passing value to function will cause variable to lose the ownership if it doesn't  
implements `Copy` trait.
- e.g.
    ```rust
    fn function2(s: String) -> String {
        let changed;
        changed = s + " changed";
        return changed;
    }

    fn function1(i: i32) {
        println!("number {}", i);
    }

    fn main() {
        // Copying
        let num1 = 32;
        function1(num1); // will print 32
        let num2 = num1;
        function1(num1); // will print 32
        function1(num2); // will print 32

        // Moving
        let a = String::from("abc");
        println!("a: {:?}", a);
        let b = a;
        println!("b: {:?}", b);
        // following will panic since now owner is `b`
        // println!("a: {:?}", a);
        let c = function2(b);
        println!("c: {:?}", c);
        // following will panic since ownership was transferred to `function2.s`
        // println!("b: {:?}", b);
    }
    ```
### Borrowing
- We borrow variable using reference.
- We prepend variable name with `&` to borrow.
- We need to use `*` (dereference) operator to access borrowed **primitive** variable.
- References can have types as well.
- We can have *many immutable* references to variable.
- We can *only* have ***one** mutable* references to variable.
- We **can't** have both immutable and mutable reference to same variable.
- Immutable references
    - e.g.
        ```rust
        fn print_upper(s: &String) {
            let upper = s.clone().to_uppercase();
            println!("Upper: {}", upper);
        }

        fn print_lower(s: &String) {
            let lower = s.clone().to_lowercase();
            println!("lower: {}", lower);
        }

        fn main() {
            let str = String::from("hello");
            // multiple immutable references
            let r1 = &str;
            let r2 = &str;
            print_lower(r1);
            print_upper(r2);
            println!("str: {}", str);
        }

        ```
- Mutable references
    - e.g.
        ```rust
        fn change_string(s: &mut String) {
            s.push_str(" string");
        }

        fn main() {
            let mut str = String::from("hello");

            let s1 = &mut str;
            change_string(s1);

            // can't have more than one mutable references
            // let s2 = &mut str; // NOT possible

            // can't have both mutable and immutable references
            // let s3 = &str; // NOT possible

            println!("{}", str);
        }

        ```
### Lifetimes
- Lifetime of variable is time when it was allocated till it was deallocated (deleted) from memory.
#### Lifetime Annotations
- Lifetime Annotations are used to specify lifetime of a references and variables at compile-time.
- If structs and tuples have references as fields or elements you **MUST** specify the lifetime annotations
so that it will be clear when lifetime of the references inside a structs might end.
- Lifetime Annotations are declared using `'lifetime_annotation_name` (called tick).
- They are passed around to functions, structs and tuples as `<'lifetime_annotation_name'>`.  
e.g.`fn function_name<'lifetime_annotation_name>`,  
`struct Struct_name <'lifetime_annotation_name>`.
    ```rust
    fn main() {
        let numbers = vec![2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24];

        let sum_of_nums = sum(&numbers);
        let product_of_nums = product(&numbers);
        let average_of_nums = average(&numbers);

        println!("Sum of these numbers: {}", sum_of_nums);
        println!("Product of these numbers: {}", product_of_nums);
        println!("Average of these numbers: {}", average_of_nums);

        let other_numbers = vec![1, 2, 3, 4, 5, 6];
        let (slice1, slice2) = first_three(&numbers, &other_numbers);

        println!("The first three elements in `slice1` are:");

        for num in slice1 {
            println!("• {}", num);
        }

        println!("The first three elements in `slice2` are:");

        for num in slice2 {
            println!("• {}", num);
        }
    }

    fn sum(numbers: &[i64]) -> i64 {
        let mut total = 0;

        for num in numbers.iter() {
            total += num;
        }

        total
    }

    fn product(numbers: &[i64]) -> i64 {
        let mut total = 1;

        for num in numbers.iter() {
            total *= num;
        }

        total
    }

    fn average(numbers: &[i64]) -> i64 {
        let length = numbers.len() as i64;

        sum(numbers) / length
    }

    // here lifetime annotation / specifier is required because we are returning
    // are reference and we need to know what will be it's lifetime.
    fn first_three<'a>(numbers1: &'a [i64], numbers2: &'a [i64]) -> (&'a [i64], &'a [i64]) {
        (&numbers1[0..3], &numbers2[0..3])
    }

    ```
##### Lifetime Elision
- Lifetime Elision can be used to let compiler handle lifetime annotations.
- If there is need for specific annotation compiler will throw error otherwise let compiler
handle it.
- TODO: needs more information
#### Static Lifetime
- `'static` lifetime is for entire program.
- Mostly used with `&str`.  
    e.g.
    ```rust
    fn main() {
        let name = "John";
        // is similar to 
        let name: &'static str = "John";
        // is similar to 
        let name: &str = "John";
    }
    ```
- These are hard-coded in binary themselves.

### Function parameters and returns
- All parameters are immutable i.e. `a` in following example is immutable till
it is shadowed.  
e.g.
```rust
fn abc(a: i32) {
    // Cannot do following as a is immutable
    // a = 99;
    println!("{}", a);
    // but it can be shadowed
    let a = 99;
    println!("{}", a);
}

fn main() {
    let a = 31123;
    abc(a);
}
```
- We can not return a dangling references. i.e.  
we can only return a references if we have received it.
- e.g.
```rust
fn function2(s: &mut String) -> &mut String {
    s.push_str(" world!");
    s
}

fn function1(s: &mut String) {
    let s = function2(s);
    println!("{}", s);
}

// This won't compile, because it would return a dangling reference.
// fn function3() -> &String{
//     &String::from("hello")
// }

fn main() {
    let mut s = String::from("hello");
    let mut_ref = &mut s;
    function1(mut_ref);
}
```
### Nested Functions  
TODO: add more info

### Closures  
TODO: add more info
