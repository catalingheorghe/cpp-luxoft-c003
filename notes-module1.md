### Intro

C++ - versatility. Initially created as an OO version of C
1986 - first version; Bjarne Strosoup.

High-level language (like java, python). Low-level to high-level: one consideration
can be **semantic density**, how much do you need to write to achieve your goal.

 - C - lower level; control everything, more lines of code required = sem dens of 1
 - C++ = 4
 - java = 7
 - python = 9

C++ - general purpose language but excels in performance.

Functional vs imperative

 - func - usually immutable, no variables, based on functions
 - imperative - sequence of instructions
 - C++ = imperative; c++11 included functional features

Compiled language (not interpreted). Faster runtime, but bound to platform.

Strongly typed. Compiler checks if operations are valid for given data types.

OOP, template metaprogramming, lambda etc

Cpp standard sets out six language goals

 1) performance
 2) software and language evolution (C++ standard / 3 years)
 3) readability
 4) safety guarantees and testing mechanisms (not really achieved; ex mem issues)
 5) fast and scalable development (code reusability)
 6) hw, OS platforms evolve

Multi-paradigm language:

 - procedural (branching, loops, functions etc)
 - generic (templates, type parameters)
 - OOP (encapsulation, control of indirect flow - less/no function pointers)
 - functional

Evolution of C++ standards. A standard defines a subset of the language that works
predictably on all platforms.

 - 1998 C++98
 - 2003 C++03 (no major differences)
 - 2011 C++11 (a lot of new features, syntax changes)
 - 2014 C++14
 - 2017
 - 2020
 - 2023

Basic look and syntax of CPP program

function declaration: `void foo(int a, int b = 1);` -> h
function definition -> cpp file

all syntax from C works in CPP, but cpp has some more

entry point: `main() / main(int argc, char* argv[])`
`OS -> constat init -> non-local static init -> main() -> std::exit()`

building: preprocess (-E), compile, assemble, link
(preprocess: `g++ -E hello.cpp`)

namespaces - avoid naming conflicts in large programs

### Data types

int - basic integer, at least 16b, usually 32
short - at least 16b
long - at least 32b
long long - at least 64b

Actual size for a platfrom = "data model" a/b/c (integer/long/pointer)

Variable declarations require data types, to know how memory is interpreted.
**Best practice**:
 - meaningful names
 - declare variable as close as possible to the place of use
 - initialize variables
 - do not reuse for different goals

Type deduction (auto keyword)

```
auto x = 123; // compiler infers type from context

map<int, vector<string>>::iterator it = m.begin();
// or, simpler, more generic
auto it = m.begin();
```

"auto" always requires initialization, which is a plus

"auto" can help reduce the memory footprint of objects

```
int (*fp)(int, int) = add; // efficient mem, hard to read
function<int(int, int)> ff = add; // less efficient
auto fa = add; // efficient and easy to read
```

#### Integers

Operations over integers

 - unary: +, -, ~
 - arithmetic: +, -, *, /, % (remainder); always return an int
 - bitwise: |, &, ^, <<, >>
 - comparisons: ...
 - pre/post increment/decrement

Integer operations can lead to overflows and underflows. Results may wrap around.
Use boundary checks and/or checks before operaton.

Signed and unsigned comparison - compiler converts signed to unsigned (!)

Note: unsigned integers rarely used; bit manipulation, embedded programming.
Standard library functions usually returns size as unsigned.

`while (x < v.size() - 1)` can cause an underflow if vector v is empty

For sizes, vector size, string length, etc: type `size_t` (unsigned int type, but 
as large as needed).
**Best practice**: use size_t for sizes or indices.

#### Floating point

IEEE-754 standard

float - single-precision, up to 7 decimals, 32b usually; memory and performance
double - double-precision, 15 dec, 64b; precision, scientific calculation
long double - extended-precision; 128b or 80b, depends; less common use

representation: sign bit, exponent, mantissa

issues: 0.1 + 0.2 -> will not give exactly 0.3000000000; it will have a rounding
error because of the representation (0.3000000119)

**(!)** do not use float for discrete values like money (ints representing cents,
or specialized libraries)
**(!)** do not compare floating point numbers for equality (use a small value,
epsilon to see if they are close enough)

Precision loss: large float + very small float => the small one will be ignored
(1e10 + 1e-8 -> 1.e10)

Overflow: large float + large float -> infinity (special value)

#### bool type

true (1) / false (1)
size: 1B
output: "1" "0" (cout)

boolean ops: a || b , a && b, !a
ternary op: (condition) ? expression_if_true : if_false

#### pointer type

pointer = variable that holds the address in memory of another variable
size: 8 (on 64b arch)

```
char c = 'a';
char *p = nullptr;
p = &c;
std::cout << *p << std::endl; // A
```

(later: smart pointers, that try to avoid problems with pointers)

#### reference type

reference = references a specific variable, can't be changed later; becomes
another name for that value (like an alias)

```
int a = 1;
int& r = a; // must be initiliazed, can't be changed to refer something else
r = 123;    // r is another name for a now => a will change
```

Stroustrup: references are "syntax sugar" (easier to read and write, cleaner
and safer syntax than pointers)

can be used in function to pass parameters by reference, not by copy

```
void increase_it(int& n) { n = n + 1; }
int x = 1;
increase_it(x); // passes x by reference, not by copy
```

#### arrays

Properties:
 - sequence of elements of same type
 - adjacent memory (contiguous)
 - fixed size of array (number of elements)
 - constant time access
 - 0 based indexing

```
char c[] {'a', 'b', 'c'}; // same as putting an = before { }
float b[3] = {}; // zero initialization of 3 elem array
```

Modern C++ does NOT recommend using arrays because
 - safety issues; pointer to first element, no checks
 - fixed size at compile time
 - confusing, e.g. sizeof() returns size in bytes
 - do not provide collection interfaces (begin(), end())

Alternatives:
 - Vector std::vector - can grow and shrink; based on dyn memory
 - Array std::array - wrapper a fixed time array into a friendlier container
 - Span std::span - lightweight view of contiguous sequence of elements

Address arithmetic (like in C). Increase in sizeof() bytes, depending on type
of data the pointer points to.
 - can be confusing, can go over array bounds, harder to read ...

#### strings

std::basic_string - template type for sequence of any characters
std::string - one-byte characters, ascii

pointer to a dynamically allocated array of characters
keeps track of own length
keeps track of capacity (total amount of memory allocated to the string)

Operations examples

```
std::string s1 = "hello"
s1[0]
s1.size(), s1.length() // same
s1 + " " + "world" // concatecation, + overload
```

get C style string (which is supported), NULL terminated char array

```
const char* c = s1.c_str();
```

C style string functions can be used (strlen(), strcmp()), but should NOT be
used in modern C++ (buffer overflows, null terminator assumption, manual memory
management, no checks in overriding memory or going over bounds).

### C++ statements, control flow

if - { } recommended
since C++17 can include an initializer (scope limited to if statement)
```
if (auto pos = find(); pos < 0)
    std::cout << "not found" << std::endl;
```

switch (expression - enum or integer); case ... ; default
no break -> fall-through
C++17: `[[fallthrough]]` - intentional

while (expression) - until expression evaluates to true
empty body can be indicated by a `;`

do ... while (expression) - loop body executed at least once

for (initialization; condition; modification)
when condition is false, the loops terminates.
comma operator: multiple initialization, multiple modification
`for (auto i = 0, j = 10; i !=j; ++i, --j) ...`

range based for loops (C++11) - for (initialization : container) ...
simplicity, readability, safety
```
for (auto i : {1, 2, 3}) { ... }

std:vector<int> v{1, 2, 3, 4, 5};
for (auto& i: v) { // reference, to modify elements of vector
    i *= 2;
}

std::vector<std::string> v{ ... };
for (const auto& i: v) { // const ensures it is a read-only reference
    std::cout << i.value() << endl;
}
```

break and continue statements can control flow in loops


### Extra notes

Terms from C++ standard: "undefined behaviour", "unspecificed behaviour".
When compiler cannot guarantee how the behaviour observed on a given platform
does not match the way the could would run on a "perfect" C++ standard virtual
machine.

### Resources

 - cppreference.com -> example: search "cppreference string"

