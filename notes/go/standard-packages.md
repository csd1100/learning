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
## testing
- Test is file with `_test.go` suffix.
- Write functions with prefix `Test` and argument `(t *testing.T)`.
- Inside call method on type `testing.T`.
- Can use goroutines for parallel execution of tests.
- CLI `go test -v ./...` for execution of all tests in subfolders.
- From go v1.19 supports "fuzzing" (using random inputs for function).
- Can use `package <package_name>_test` to test only public facing APIs instead of private functions.
- Community uses TableDrivenTest similar to `unroll` in spock framework.
    - e.g. **NOTE** example picked up from [internet](https://ieftimov.com/posts/testing-in-go-table-driven-tests/).
    ```go
	type TestCase struct {
		arg1     float64
		arg2     float64
		expected float64
	}

	func TestMax(t *testing.T) {
		cases := []TestCase{
			TestCase{
				arg1:     1.0,
				arg2:     2.0,
				expected: 2.0,
			},
			TestCase{
				arg1:     -100,
				arg2:     -200,
				expected: -100,
			},
			TestCase{
				arg1:     0,
				arg2:     -200,
				expected: 0,
			},
			TestCase{
				arg1:     -8.31373e-02,
				arg2:     1.84273e-02,
				expected: 1.84273e-02,
			},
		}
		for _, tc := range cases {
			got := math.Max(tc.arg1, tc.arg2)
			if got != tc.expected {
				t.Errorf("Max(%f, %f): Expected %f, got %f", tc.arg1, tc.arg2, tc.expected, got)
			}
		}
	}
    ```
