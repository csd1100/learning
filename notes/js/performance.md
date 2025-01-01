# Performance

- Sometimes array can be faster than sets / hash sets.
  - We think hashsets will be faster because of o(1) fetch using key,  
    but sets also usually have linked list for collisions so traversing them takes some amount of time.
  - For small input set arrays can be faster as well because they are stored in contiguous memory so we just have iterate over it.

## [Garbage Collection in v8](https://v8.dev/blog/trash-talk):

- 2 types of Garbage Collection:
  1. Major GC (Full Mark-Compact)
     - Goes through all the references in the memory and checks if they are still alive.
     - If reference is dead it GCs the object.
     - Sometimes also does memory defragmentation.
     - Takes lot of time.
     - Rarely done because it takes long time.
  1. Minor GC (Scavenger)
     - Takes relatively small time.
     - Only Collects from newer object because there is a concept that most of  
       the js object are very short lived.
