# React Hooks

## State

### `useState`

- `useState` hook takes initial value as input and returns an array / tuple
of reference to the state variable and setter for that variable.
- React keeps track of all the state created using `useState`.
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
        const [someState, setSomeState] = useState(()=> {
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
