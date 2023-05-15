# Standard Packages
## Printing
- `fmt` package can be used for printing the data to either console, files, or buffers.
- There are 3 ways to print:
- `Print()` - Prints without newline at the end.
    - `Println()` - Prints with newline at the end.
- `Printf()` - C style string formatting (i.e. `%s` - string, `%d` - integers, `%f` - float, `%t` - boolean)
    - `fmt` has 3 different set of functions for outputs
    1. `fmt.Print()`, `fmt.Println()`, and `fmt.Printf()` - Sends output to STDOUT / console.
    2. `fmt.Fprint()`, `fmt.Fprintln()`, and `fmt.Fprintf()` - Sends output to File.
    3. `fmt.Sprint()`, `fmt.Sprintln()`, and `fmt.Sprintf()` - Sends output to In memory buffer i.e. variables.
