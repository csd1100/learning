# Custom Components

- Custom Components are functions that takes props object as input param and
returns a JSX element.
- We can also pass a function to `React.createElement(<fn>, <props>, [children])`.  
Where function `<fn>` returns JSX and takes `<props>`,`children` as input.
- JSX uses above internally to create custom components.
- The components are named using `PascalCase`.
- Rules for naming components:
    - `lowercase`, `kebab-case`, `lower_snake_case`,`Upper-Kebab-Case` will create
    elements with string like `'div'`.
    - `Capitalized`, `property.access`, `Property.Access`, `Upper_Snake_Case` will
    create custom components.
    - e.g.

    ```jsx
    const element = <Capitalized /> // React.createElement(Capitalized, null); // where `Capitalized` is a function
    const element = <property.access /> // React.createElement(property.access, null); // where `access` is a method|function on a `property` object
    const element = <Property.Access /> // React.createElement(Property.Access, null); // where `Access` is a method|function on a `Property` object
    const element = <Upper_Snake_Case /> // React.createElement(Upper_Snake_Case, null); // where `Upper_Snake_Case` is a function

    const element = <Property['Access'] />; // Syntax Error

    const element = <lowercase /> // React.createElement('lowercase', null); // where `lowercase` is a string
    const element = <kebab-case /> // React.createElement('kebab-case', null); // where `kebab-case` is a string
    const element = <Upper-Kebab-Case /> // React.createElement('Upper-Kebab-Case', null); // where `Upper-Kebab-Case` is a string
    const element = <lower_snake_case /> // React.createElement('lower_snake_case', null); // where `lower_snake_case` is a string
    ```

- We can have default values for components by making properties of `props` param
have a default value and making their type definition include `undefined` using `?`  
e.g.

    ```jsx
    function Greeting({ text = 'World' }: { text?: string }) {
        return (
            <h1>Hello, {text}!</h1>
        );
    }
    const element2 = <Greeting />;
    const element = <Greeting text="Name" />;
    ```

- Always compose props in such a way that component can be reusable.
i.e. Use following way:

    ```jsx
    function Box({ size, ...props }: React.ComponentProps<'div'> & { size?: 'small' | 'medium' | 'large' }) {
        const sizedClass = size ? 'box--' + size : '';
        return (
            <div
                {...props}
                // in below statement we are filtering falsy values in case props.className
                // is undefined and then joining with ' ' so we do not get `undefined` class
                // on element
                className={['box', props.className, sizedClass].filter(Boolean).join(' ')}
                style={{ fontStyle: 'italic', ...props.style }}
            />

        )
    }
    ```

    Instead of

    ```jsx
    function Box({ size, ...props }: React.ComponentProps<'div'> & { size?: 'small' | 'medium' | 'large' }) {
        return (
            <div className={size ? 'box box--' + size : 'box'} style={{ fontStyle: 'italic', ...props.style }} {...props} />

        )
    }
    ```

    This is because the in 1st component I can add other classes just by adding
    it to JSX element. In 2nd the class can only be `box` or `box box--${size}`.
    And developer will have to update component every time something needs to be
    changed.

## Error Handling

- Error Boundary is a component that wraps other components in order to handle
errors in them.
- Error Boundary can be created manually by using class component.
- We can use `react-error-boundary` npm package instead of manually creating
Error Boundary component ourselves.
- `react-error-boundary` package provides us `<ErrorBoundary/>` component.
- `<ErrorBoundary/>` should wrap components that might throw an error.
- If component that uses or contains `<ErrorBoundary/>` should throw an error,
it won't be handled by `<ErrorBoundary/>` that is specified in that component.
It needs to be handled further up the component chain or it will be unhandled.
- `FallbackComponent` prop on `<ErrorBoundary/>` takes component as input that will
be used to handle the error. The passed component has props of type `FallbackProps`.
- In cases like callbacks, we cannot handle the errors using `<ErrorBoundary/>`.
- `react-error-boundary` provides `useErrorBoundary` hook which provides
`showErrorBoundary` method to which can pass error. This will show the error
in `<ErrorBoundary/>` that is wrapping the component.
- `FallbackProps` type has `error` prop for error that has occurred.
- `FallbackProps` type has `resetErrorBoundary` prop which is a method that will
reset the error boundary. The state of component will **not** be preserved.

## Types

- `React.ReactNode` type can be used in typescript for react components.
- `React.ComponentProps<'element'>` type can be used for props for specific
element / component. Use this instead of creating unnecessary new props as this
will make sure common element props are type-checked.
- `react-error-boundary` provides us `FallbackProps` type for `FallbackComponent`
prop.
