# Multithreading

## Basics

- Threads can be created using `std::thread` module.
- If we give multiple threads a task to do then we can't be sure which task will
  execute first as OS schedules the threads that will get chance to execute.
- We can use `spawn()` to spawn a thread to execute function definition passed to
  it.
- The `spawn` returns thread join handle which can be used to manage thread spawned.
- If `join` method is not called then main thread won't wait for thread to complete
  execution before exiting the program.  
  e.g. In below as `join` is not called (commented) the program will exit before
  "Hello from thread" is printed.

  ```
  fn hello_from_thread() {
    thread::sleep(Duration::from_millis(4000));
    println!("Hello from thread");
  }

  fn main() -> Result<()> {
      println!("Main 1");
      let thread_hdl = thread::spawn(hello_from_thread);
      println!("Main 2");
      // let res = thread_hdl.join();
      // println!("Done: {res:?}");
      Ok(())
  }
  ```

- Thread needs it's own copy of data in order to have memory safety as data should
  be present whenever thread needs it so we need to move data to thread.
