# ZSH

## Init system

- First `/etc/zshenv` is executed.
- Files read:

```zsh
  $ZDOTDIR/.zshenv
  $ZDOTDIR/.zprofile
  $ZDOTDIR/.zshrc
  $ZDOTDIR/.zlogin
  $ZDOTDIR/.zlogout
  ${TMPPREFIX}* (default is /tmp/zsh*)
  /etc/zshenv
  /etc/zprofile
  /etc/zshrc
  /etc/zlogin
  /etc/zlogout
```

## Misc

- `|` can be used to only pipe stdout.
- `|&` can be used to pipe both stdout and stderr.
- `<>` can be used to reading a file and redirecting it next to stdin.
- Execution precedence functions > builtins > executable in PATH.

## Pre-command modifiers

- `builtin` - executes shell builtin rather than shell function or script / executable.
- `command` - executes command rather than shell builtin or shell function.
- `exec` - executes the command without sub-process i.e. replaces current zsh process.
  - `-c` clears environment variables. ???
- `noglob` - globbing is not done.

## Builtins

- `alias` - to set alias; alias are just text replacements.
  `-g` can be used to set global aliases. Which can be used to even alias `|` operator.

## Aliasing

- Aliases are just text replacements can be done by `alias` builtin.
- `\` can be used before alias to avoid using aliased value.
- The alias builtin does not reject ineligible aliases, but they are not expanded.
- Use of functions is recommended rather than aliases in scripts, because aliases
  are expanded after reading entire line. e.g.  
  In scripts `alias echobar='echo bar'; echobar` fails because alias expansion
  happens before alias `echobar` is defined.

## Functions

- Functions are defined using `funcname(){}` syntax.
- They share execution environment of parent.
- `return` can be used to return from function.
- A trap on `EXIT` set inside a function is executed after the function
  completes in the environment of the caller.
- `unfunction` command can be used to delete function definition.
- function definitions are located in `fpath`.
- And `autoload` builtin can be used to automatically load the function.
- Anonymous functions can be defined using `(){<function_body>} <args_to_function>`
  or `function{<function_body>} <args_to_function>`. They are executed immediately.

### Hook functions

- Hook functions are executed on certain events like changing of pwd.
- If `<hook_function>_functions` array is created with list of name of Functions
  then `<hook_function>` and subsequently functions defined in array are executed.
  e.g.  
   if `$chpwd_functions` is an array containing
  the values `mychpwd`, `chpwd_save_dirstack`, then the shell attempts to execute
  the functions `chpwd`, `mychpwd` and `chpwd_save_dirstack`, in that order.
- If hook function executes successfully it is added to zsh history file.
- `chpwd` - executed when current directory is changed.
- `precmd` - executed before each prompt but that does not mean it is executed
  if prompt is redrawn like with `<Ctrl-l>` keypress.
- `preexec` - Executed after command is read but yet to be executed. It has 3
  arguments 1. 1st argument to original command, 2. Actual command to be executed
  after alias expansion in single line, 3. Same as 2 but actual text to be executed.
- `zshaddhistory` - is triggered just before saving the entry. ???
- `zshexit` - is executed when shell exits gracefully.

### TRAPs

- TRAP*NAL* - Are executed when shell catches SIG*NAL*
  - e.g. `TRAPINT` is triggered when `SIGINT` is received.

## Options

- `-<opts>` can be used to enable the option.
- `+<opts>` can be used to disable the option.

- `-i` forces interactive mode.
- `-s` forces input to be taken from stdin.
