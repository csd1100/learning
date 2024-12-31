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
- If we create a state in a component using `useState`. React will create a state
  variable with passed in initial value on first render. On next render react won't
  create a new state variable but it will still execute the function component.
- Suppose initial value for state is being computed using a function.
  The initialization function will be called every time the component is rendered.
  If that function is expensive the UI will be slow.
- So instead we can pass a reference to a function for `useState` to call when
  computing initial value. This will make initialization function called only once.
  This is called lazy-initialization.
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

## Lifting State

- The state can be moved only from parent component to child component.
- So if sibling component needs access to state we can lift the state to their
  common parent and pass the state variable and setter via props.
- But after refactor or change in code it might happen that shared state is now
  only needed for one component. In that case we should be take care of moving
  the state back to required component otherwise code will become unmaintainable.

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
  function as if you forget to input some dependency as argument to `useEffect` your
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
