# typescript

## basics

- We can use `keyof` operator on existing type to create a type with allowed values
  as keys of passed in type
- We can use `Record<key, value>` instead of Object type.
- We can make any key | param optional by adding `?` at the end of it
  `a?: number` means `a` is optional OR type is `number | undefined`.
