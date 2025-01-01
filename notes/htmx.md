# [HTMX](https://htmx.org/)

## Introduction

- HTMX allows you to make HTTP request directly using HTML without js.
- To use HTMX we need to add the script to HTML.
  ```html
  <script src="https://unpkg.com/htmx.org@1.9.9"></script>
  <!-- have a button POST a click via AJAX -->
  <button hx-post="/clicked" hx-swap="outerHTML">Click Me</button>
  ```
- HTMX uses attributes for HTML elements.
- All HTMX attributes are of form `hx-<...>`
- For HTTP requests attributes used are `hx-<HTTP verb>` e.g. `hx-post`
- HTMX swaps or replaces `innerHTMl` of elements for which attribute is added.
- We can use `hx-target` to change which content to change.  
  Target value can be a css selector.
