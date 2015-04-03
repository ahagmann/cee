## Calculations ##

Calculations can be done by entering the calculation in infix notation and hit ENTER.

In addition to the usual arithmethic functions, _cee_ also supports some logical and statistical functions.

After calculations valid inputs are stored in a history, use the UP and DOWN arrow keys to navigate through it.


## Numbers ##

_cee_ can interpret a variety of different numbers. Heres a list:
  * decimal numbers
  * numbers starting with `0x` are interpreted a hexadecimal values
  * numbers starting with `0b` are interpreted a binary values
  * SI base units can be appanded to decimal numbers, for example `3m` is interpreted as 0,003


## Commands ##

Commands control the behaviour of _cee_. A command starts always by a colon ':'.

  * `bin` or `0b`: set the output format to binary
  * `oct` : set the output format to octal
  * `dec` or `d`: set the output format to decimal
  * `hex` or `0x`: set the output format to hexadecimal
  * `eng` : set the output format to engineering
  * `siu`: set the output format to _si base units_
  * `quit`, `q` or `exit`: close _cee_

For example

`:bin`

changes the output format to binary.


### Overrides ###

Overrides can be used to change the output format, only for the next calculation. An override always starts with a dot '.'.

For example

`.bin 4+5`

executes the calulation and prints the result in binary form, without changing the output format permanently.

This could be used to show the last result in hexadecimal form

`.hex #`

Supported overrides are
  * bin
  * hex
  * oct
  * dec
  * eng
  * siu


## Variables ##

Variables can be defined by the `=` operator. For example

`a = 40 + 2`

defines a new variable _a_ with a value of 42. If _a_ was already defined, its value gets overwritten.

A variable that is always defines is `ans`, it represents the last result.


## Constants ##

Constants are similar to variables, expect once defined, a constant cannot be overwritten. To define a new constant use the `:=` operator. For example:

`a := 40 + 2`

_cee_ already has some buildin constants:
  * pi


## Buildin Functions ##

_cee_ supports these buildin functions, some if them have also an infix operator, which is stated after the comma if available. Multiple arguments are seperated by a semicolon ';'.

  * add(a;...), +
  * sub(a; b), -
  * mul(a; b), `*`
  * div(a; b), /
  * mod(a; m), %
  * max(a;...)
  * min(a;...)
  * avg(a;...)
  * sin(a)
  * cos(a)
  * tan(a)
  * asin(a)
  * acos(a)
  * atan(a)
  * sinh(a)
  * cosh(a)
  * tanh(a)
  * round(a)
  * floor(a)
  * ceil(a)
  * ln(a)
  * log(a)
  * sqrt(a)
  * and(a; b), AND
  * or(a; b), OR
  * xor(a; b), XOR
  * not(a), NOT
  * abs(a)
  * pow(a; p), ^


## User defined Functions ##

A new function can be defined like a variable with the `=` operator. For example

`mulAndAdd2(val1; val2) = val1 * val2 + 2`

defines a new function `mulAndAdd2` which takes 2 arguments.


## Commandline Interface ##

```
USAGE: cee [ -i | -g | -v | -h] [ immediate input ]

    -i, --interactive   read input from stdin
    -g, --gui           open gui window
    -v, --version       print version
    -h, --help          print usage info
```
Immediate input is always processed before any
other action is performed.
If -i and -g are specified simultaniously, first
input from stdin is processed until EOF is read,
then the gui window is started.
If no immediate input is given, cee starts
in interactive mode.

Note: Mixed executables, which support both, commandline and gui mode, are available only for Linux and Mac.