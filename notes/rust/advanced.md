# Advanced
## Ownership and Borrowing
- Scope
    - Scope of variable is limited between `{}`
    - Variable is limited to scope if it is referred outside scope we will get error  
    at compile-time.
- Copying
    - There is `Copy` trait if it is implemented by type then, when we reassign value to other  
    variable the ownership is not transferred.
    - e.g. `i32`
- Moving
    - If `Copy` trait is *NOT* implemented by type then ownership is transferred or moved.
    - e.g. `String`
- Cloning
    - If `Copy` trait is *NOT* implemented by type but you don't want to lose variable value  
    we can clone value and use it for later.
    - e.g. `String`
- Ownership
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
- Borrowing
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
- Function parameters and returns
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
- Nested Functions  
TODO: add more info

- Closures  
TODO: add more info

## Structs and traits  
TODO: add more info
