# React

## Vanilla JS

- We can use `<script>` tag to add JS to webpage.
- We can use `src` attribute on `<script>` tag to use file.
- `document` object can be used to interact with DOM.
- Body can be accessed using `document.body`.
- `document.createElement('div')` to create a new `div` in browser memory.  
  The div is not added to DOM directly when we call this method.  
  We also need to call `element.append(newElement)`|`element.prepend(newElement)`
  to add new element like `div` to DOM.
- `document.getElementById`|`document.getElementByClass` can be used to get
  element.
- The attributes of element can be accessed as property on DOM element Object.  
  eg. `id`, `textContent`, `className`.  
  NOTE: as `class` is JavaScript reserved keyword. It can be accessed by
  `element.className` property.
- We can access style of element by using `style` object property. The subsequent css
  properties can be accessed using `camelCase` on `element.style`.
  Style that take measurements (`px`, `rem`) can be set using string or number.
  If number is specified default unit used is `px`;

```js
const element = document.getElementById("box");
element.style.marginTop = "20px"; // eqvt to <div id="box" style="margin-top: 20px;"></div>
element.style.marginTop = 30; // eqvt to <div id="box" style="margin-top: 30px;"></div>
element.style.backgroundColor = "blue"; // eqvt to <div id="box" style="margin-top: 30px; background-color: blue;"></div>
```

- `role` attribute can be used to make application more accessible.
- When DOM events are being fired like input or change, the `event.currentTarget`
  will give access to the DOM element that has caused the event to fire.

- `popstate` event can be used to handle browser navigation.
  The `popstate` event is dispatched to the `window` object when the active history entry changes between two history entries for the same document. This event is triggered by a navigation action, such as:

  1. Clicking the browser’s back or forward button
  2. Calling `history.back()` or `history.forward()` programmatically
  3. Refreshing the page (F5 or Ctrl+R)

  The `popstate` event is not triggered by:

  1. Calling `history.pushState()` or `history.replaceState()` directly, as these methods modify the history stack without navigating to a new page.
  2. Navigating to a new page with a different origin (domain, protocol, or port).

  The `popstate` event has two properties:

  1. state: An object containing a copy of the history entry’s state, which was previously passed to `history.pushState()` or `history.replaceState()`.
  2. origin: The origin of the document (domain, protocol, and port) that triggered the event.

## React APIs

- React has 2 libraries to be used with web. `react` and `react-dom`.
- `react` contains all the react features like hooks, components and stuff.
- `react-dom` contains API to render things on browser and DOM related APIs.
- React also uses Browser DOM API internally to manipulate DOM.

### React.createElement

- `React.createElement` is used to create an element similar to `document.createElement`.
- Signature: `React.createElement('<element_to_create>', { <attribute_keys>:<attribute_values> children: [<child_elements>] }, [children])`  
  NOTE: `<element_to_create>` denotes placeholder we do not need to add `<`, `>` to
  element name.

- eg:

```js
const element = React.createElement("div", {
  className: "container",
  children: "Hello World",
});
```

```js
const element = React.createElement(
  "div",
  {
    className: "container",
  },
  "Hello",
  " ",
  "World",
);
```

- children can be element or the string (text node in DOM).

### ReactDom.createRoot

- `ReactDom.createRoot(<element>)` is used to create an root react element and render.
- where `<element>` is HTML element object.
- `render(<element>)` method can be used to add append element on root.
- e.g.

```js
const rootElement = document.getElementById("root");
const element = React.createElement(
  "div",
  {
    className: "container",
  },
  "Hello World",
);
ReactDom.createRoot(rootElement).render(element);
```

### JSX

- Browser does not know how to evaluate JSX so we need compiler like Babel.
- In JSX we need to use `className` attribute|prop for class.
- Props are arguments to function components.
- `{`, `}` are used for interpolation of JS in JSX.
- Anything inside `{`, `}` is evaluated JS expression and result is inserted.
- Mostly logic is done outside interpolations and result is passed inside
  interpolation.

- e.g.

```jsx
const element1 = <div className={className}> Something </div>;
const element2 = <div className={className}> {children} </div>;
const element3 = <div className={className} children={children} />;
```

- props can be directly passed from objects using spread operator.
  e.g.

```jsx
<div {...props} />
```

- To override anything from props that are spread, add them after it.
  e.g.

```jsx
<div {...props} className="new-class" />
```

- The child passed in between tags overrides children prop.
  e.g. in below example `Good Bye World!` will be displayed.

```jsx
const children = "Hello World";
const element2 = <div children={children}>Good Bye World!</div>;
```

- `<React.Fragment>` | `<>`:
  - can be used to add multiple direct children that are siblings

#### Babel

- Babel can compile script tag with `type="text/babel"` attribute.
- We can enable ESM using `data-type="module"`.
