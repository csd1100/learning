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

