# React Hooks

## State

### `useState`

- `useState` hook takes initial value as input and returns an array / tuple
  of reference to the state variable and setter for that variable.
- React keeps track of all the state created using `useState`.
- The reference to the variable is _immutable_ and state can only be mutated by
  setter.
- For `input` only bind the value to react state variable, when we want the value
  to be dynamically updated based on condition using `onChange`.

- The statements like function calls in the component are always executed when
  component is rendered. i.e. The same function calls are always made when component
  is rendered.
- If we create a state in a component using `useState`, React will create a state
  variable with passed in initial value on first render. On next render react won't
  create a new state variable but it will still execute the expression in component
  that creates the state i.e. `useState` statement.
- Suppose initial value for state is being computed using a function.
  The initialization function will be called every time the component is rendered.
  If that function is expensive the UI will be slow.
- So instead we can pass a reference of the initialization function for `useState`
  to call when computing initial value. This will make initialization function
  called only once. This is called lazy-initialization.
- i.e. Do **not** do following:

  ```jsx
  function SomeComponent(props) {
    const someInitValue = someInitValueCalculator(props.someProp);
    const [someState, setSomeState] = useState(someInitValue);
  }
  ```

  Instead do:

  ```jsx
  function SomeComponent(props) {
    const [someState, setSomeState] = useState(() => {
      return someInitValueCalculator(props.someProp);
    });
  }
  ```

  As `someInitValueCalculator` will be called only once.

- The Dispatch function (setter) can also take an callback function as input
  rather than just the value. The callback receives old value as input. This can
  be useful to avoid data inconsistency.
- The react does not re-render component if state has not change even though
  dispatch function was called. In case of objects though, even if value is same
  it might trigger re-render as object reference might change (i.e. new object
  with same value).
- In order to avoid this pass in callback that returns same thing if state has
  not changed.

  ```jsx
  const [someState, setSomeState] = useState({ key: 0 });
  setSomeState({ key: 0 }); //will cause re-render as new object is created
  setSomeState((previousState) => {
    key: previousState.key;
  }); //will cause re-render as new object is returned by callback
  setSomeState((previousState) => previousState); //will NOT cause re-render as
  // same object is returned by callback
  ```

### Derived State

- We don't have to always create state for dynamic values using `useState`.
- Suppose a value always changes based on an existing state, we can just
  derive the new value using existing without having to worry about creating
  a new state variable.
- If 2 values should always change together and we create 2 state variables
  for them using `useState`, we now have to worry about updating those two
  states together.
- And if in some place we forget to update one state we now have inconsistent
  state.
- So instead of creating new state variable, we can just use normal javascript
  operation to update a normal javascript variable based on state variable.

### Lifting State

- The state can be moved only from parent component to child component.
- So if sibling component needs access to state we can lift the state to their
  common parent and pass the state variable and setter via props.
- But after refactor or change in code it might happen that shared state is now
  only needed for one component. In that case we should be take care of moving
  the state back to required component otherwise code will become unmaintainable.

### `useReducer`

- `useReducer` can be used for state management.
- `useReducer` takes in 3 inputs:
  1.  a function that takes in _current state_ and _value passed to
      dispatcher_ (called `action`), and returning _new value_ that we want.
      It's better to have all the logic inside this function.
  2.  initial value of the state **or** if 3rd input is present then argument to
      3rd input function
  3.  A function to generate initial value i.e. lazy-initializer similar to `useState`
- It returns tuple of reference and dispatch function (setter) similar to `useState`.
  Dispatch function is generally named `dispatch`.
- The Dispatch function (setter) can also take an callback function as input
  rather than just the value. The callback receives old value as input.
- Using callback function in setter / dispatch function is better to use when
  state is changed based on old value.
- When we pass an value to dispatcher due to async operations the value can be
  out of sync so it's better to use callback.
- e.g. Do **NOT** update the state in the following manner:

  ```jsx
  function reducerFn(oldState, change) {
    return oldState + change;
  }
  const [state, changeState] = useReducer(reducerFn, "initialValue");
  setTimeout(() => {
    changeState(state + change);
  }, 500);
  ```

  - The `changeState` will be invoked with value of state when `setTimeout` was
    invoked. If state was 0 when `setTimeout` was called and user changed the state
    to 2 during that time, the `changeState` will still be called with 0 even though
    new state value has changed.

  - Also if we call `changeState` multiple times, say 3 times, it will still be
    called with same value 3 times so state won't be increased by 3 but will be
    updated to same value 3 times.

- Instead do the following here, as react will pass updated value of the state to
  `changeState` as `oldState` param:

  ```jsx
  function reducerFn(oldState, change) {
    return oldState + change(); // here change is a callback function to be called
  }
  const [state, changeState] = useReducer(reducerFn, 0);
  setTimeout(() => {
    changeState((oldState) => oldState + 10);
  }, 500);
  ```

- `useReducer` is better than `useState` we want to handle state change properly.
  Reducer function helps make state change easily manageable and debuggable.

## Side Effects

### `useEffect`

- `useEffect` hook is used to handle required side-effects in application.
- `useEffect` takes in 2 parameters:
  1. A callback function that will do required side-effect operation, and return
     a function that will be called in order to do the necessary cleanup after
     doing the side-effect operation.
  2. List / Array of dependencies, who when changed side-effect should be
     performed.
- `strict` mode in react during development will help you write clean `useEffect`.
- Do **not** update dependencies of `useEffect` inside the side-effect operation
  as it will cause infinite loops of `useEffect`.  
   If you need to do it think, before implementing it properly.
  If possible use well-known library that can do the things for you.
- Put as much logic as you can in the `useEffect` callback rather than external
  function. If you forget to add some dependency as argument to `useEffect` your
  callback will be called on inconsistent dependency.
- `useEffect` can cause memory leaks due not cleaning up, so remember to return
  cleanup function from `useEffect` callback.

- **NOTE:** `useEffect` is triggered whenever dependencies passed to it changes.
  The dependencies are checked not by value but reference if they are objects.
  So even if object value does not change but object itself is reconstructed,
  it will cause `useEffect` to be triggered even though we might not expect it.

- e.g. In below example the dependencies of `useEffect` in `MyComponentWithProps`
  component are `someStringProp` and `someNumberProp`.
  There is `someState` from `App` that is not passed to `MyComponentWithProps`.
- So we expect `useEffect` to be triggered only when `someNumberProp`, and
  `someStringProp` is changed and not `someState`.
- But `useEffect` is still triggered as dependency is not those 2 states but
  passed in prop object `somePropDep`.
- Whenever `someState` changes it will cause `App` to re-render as state has
  changed. It will cause `<MyComponentWithProps>` to be re-rendered with new
  `somePropDep` param object.
- As object is newly constructed it will have same value but reference will be
  different (i.e. `Object.is` will return `false`). So `useEffect` will be
  triggered.

  ```jsx
  import { useEffect, useState } from "react";

  function MyComponentWithProps(somePropDep: {
    someStringProp: string,
    someNumberProp: number,
  }) {
    useEffect(() => {
      console.log("effect triggered");
      return () => {
        console.log("effect cleanup");
      };
    }, [somePropDep]);
    return (
      <div>
        {somePropDep.someNumberProp} - {somePropDep.someStringProp}
      </div>
    );
  }

  export default function App() {
    const [someStringProp, setSomeStringProp] = useState < string > "";
    const [someNumberProp, setSomeNumberProp] = useState < number > 0;
    const [someState, setSomeState] = useState < boolean > false;

    return (
      <div>
        <input
          type="text"
          onChange={(evt) => setSomeStringProp(evt.currentTarget.value)}
        />
        <input
          type="number"
          onChange={(evt) => setSomeNumberProp(Number(evt.currentTarget.value))}
        />
        <button
          onClick={() => {
            setSomeState(!someState);
          }}
        >
          {someState.toString()}
        </button>
        <MyComponentWithProps
          someStringProp={someStringProp}
          someNumberProp={someNumberProp}
        />
      </div>
    );
  }
  ```

  - To avoid this make `someStringProp` and `someNumberProp` as dependency as those
    are not changing as they are states managed by react:

  ```jsx
  import { useEffect, useState } from "react";

  function MyComponentWithProps({
    someStringProp,
    someNumberProp,
  }: {
    someStringProp: string,
    someNumberProp: number,
  }) {
    useEffect(() => {
      console.log("effect triggered");
      return () => {
        console.log("effect cleanup");
      };
    }, [someStringProp, someNumberProp]);
    return (
      <div>
        {someNumberProp} - {someStringProp}
      </div>
    );
  }

  export default function App() {
    const [someStringProp, setSomeStringProp] = useState < string > "";
    const [someNumberProp, setSomeNumberProp] = useState < number > 0;
    const [someState, setSomeState] = useState < boolean > false;

    return (
      <div>
        <input
          type="text"
          onChange={(evt) => setSomeStringProp(evt.currentTarget.value)}
        />
        <input
          type="number"
          onChange={(evt) => setSomeNumberProp(Number(evt.currentTarget.value))}
        />
        <button
          onClick={() => {
            setSomeState(!someState);
          }}
        >
          {someState.toString()}
        </button>
        <MyComponentWithProps
          someStringProp={someStringProp}
          someNumberProp={someNumberProp}
        />
      </div>
    );
  }
  ```

## DOM Refs

### `useRef`

- `useRef` is used to hold a javascript value that is not related to rendering.
- `useRef` takes input parameter of initial value.
- The value can be accessed and directly mutated using `<ref_obj>.current`.
- The mutation in `ref` won't cause re-render of the component.
- The `ref`s should not be mutated during rendering. i.e. inside component. As
  mutation in `ref` won't cause re-render, if `ref` is mutated during component
  rendering, the rendered state will be inconsistent as value of `ref` has changed
  but it component is not rendered again with updated value.
- It should be mutated in `useEffect` or callbacks that will be called by react
  after DOM is rendered like in case of event handling.
- `ref`s are generally used with DOM nodes.
- As mentioned before mutation to a `ref` does not cause re-render, suppose if we
  want to update DOM node but do not want to re-render entire application or component
  we can use `useRef` to create the DOM node `ref` and mutate that in `useEffect`.
- We can create a `useRef` of type `HTMLElement` with null initial value. Then,
  We can access the DOM node by passing variable created by `useRef` to `ref` prop.
  The DOM node will be assigned to `ref`. We can mutate that in `useEffect`.  
  e.g.

  ```jsx
  function MyDiv() {
    const myDivRef = useRef < HTMLDivElement > null;
    useEffect(() => {
      const myDiv = myDivRef.current;
      console.log(myDiv);
    }, []);
    return <div ref={myDivRef}></div>;
  }
  ```

## Unique IDs

### `useId`

- `useId` hook will generate a unique identifier that we can use for elements.
- In `createRoot` we can pass `identifierPrefix` for `useId` to create IDs with
  specified prefix.
