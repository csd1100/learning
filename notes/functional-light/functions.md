# Functions

- Anything that doesn't return a value is not a function but a procedure.
- There should be explicit relation between inputs and outputs.
  Label of function should be based on semantic relation between those inputs and outputs.
- Functions should not have side-effects.
  i.e. it shouldn't have indirect inputs and indirect outputs.
  It shouldn't affect anything outside of inputs.
- Practically avoid side-effects i.e. minimize them.
  And make them explicitly identifiable/ obvious.
  Because we will most likely find bugs there.
- **Pure Functions** - The function that has well defined inputs and outputs,
  It does not have side-effects, It only operates on passed in inputs not some other data.
  But some other data is constant then it's fine. But we should explicitly state that it is constant because others should also understand that it is constant and not changing. Given a same input it always returns same output.

```javascript

```
