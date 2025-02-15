### Functions

Declaration ...

`<return type> name([param=initializer])`

and definition

```
<return type> name([param=initializer]) {
    statements / body
}
```

Return statement is optional in "void" functions.

Calling a function - must match the numbers of params, unless deafult values used.

#### Function Overloading

Same name but with different parameters list. Compiler determines which based on
params passed.

Example

```
int foo(int x, int y) {
    ...
    return x + y;
}
//foo(1, 2)

void foo(char x) {
    ...
}
//foo('X')

void foo(std::string s) {
    ...
}
//foo("X")

int foo(char x) {};
// error; can't overload with same params, even if return type differs
```

Notice that return types can also be different. But can't overload based only
on return type. The parameters must differ.

Selection process by the compiler:
 - number and types of arguments
 - implicit conversions
 - default arguments

#### Generic Programming using Templates

Generic programming paradigm = work with any data type. In C++, main mechanism
is "templates".
 - type flexibility
 - code reusability
 - compile-time instantiation (compiler generates specific versions of function)


```
template <typename T>
T add(T x, T y) {
    return x + y;
}
// add(1, 2)
// add(std::string("A"), std::string("B"))
```

In the above, a template is declared with T as "type" (can also be 'classname').
Then T is a placeholder for a data type.A
In the function above, the type T must support the '+' operator.


**auto keyword**

using the 'auto' keyword above achieves a similar result

```
auto add(auto x, auto y) {
    return x + y;
}

add(2, 3)   // x, y -> int; return -> int
add(2, 3.4) // x -> int, y -> double; return -> double (implicit conv)
```

Pros: simpler syntax, can mix types.

#### Function pointers

A variable that holds the address of a function, allowing indirect, dynamic,
runtime detected calls. (callbacks, dispatcher ...)

```
int (*func)(int);
if (rand()%2) func = increase;
func(2); // increase(2)
```

To improve readability (and safety)

```
include <functional>
std::function<int(int)> func;
// can store also lambdas, member functions, function objects
// calling a NULL one -> exception, not undefined behaviour (crash usually)
```

#### Lambdas

Anonymous functions defined in-line

`[]() { return 42 }()`

Capture clause `[]` - capture variables from surrounding scope
The last `()` - invocation of the lambda function

Capture by value - internal copy at the time when lambda was defined

```
auto a = 5
auto f = [a](int x) { return a * x; };
cout << f(2) << endl; // 10
a = 7;
cout << f(2) << endl; // 10 (a was captured before, when it was 5)
```

By default, treats them as const inside the lambda. To modify, mark the
lambda as "mutable".

```
auto f = [a](int x) mutable { return ++a * x; };
f(2) // still does not modify a outside the lambda, but from call to call
f(2) // a in lambda was increased before; a outside lambda not touched
```

Capture by reference - refers to the original variable in the outside scope

```
auto f = [&a](int x) { return ++a * x; };
```

Capture expressions (C++14) - evaluated when value is created. Known as lambda
capture with initialization.

```
auto f = [value = 42]() { return value; };
// scope is local to the lambda
// can use initialization to avoid relying on external variables
```

Factory of functions 

```
function<int(int)> f(int x) {
    return [x](int a) -> int { return x * a; };
}

auto double = f(2) creates a multiplier that multiples by 2
```

 - can create multiple customized functions dynamically

Usage in STL algorithm functions

```
std::vector<int> v(10);
std::generate(v.begin(), v.end(), [](){ return rand()%100; });
//or
std::vector v{1, 3, 5}, v2(v1.size());
std::transform(v.begin(), v.end(), v1.begin(), [](int x){ return 2 * x;});

std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
std::cout << std::endl;
```

or `all_of` to check if elements match a condition, a predicate (lambda)
or `sort` with a decending order (return x > y)
or `accumulate`, or ...

Generic lambdas (C++14)

`auto add = [](auto x, auto y) { return x + y; };`

 - uses the auto keyword in parameter list


### Constant declaration

 - `#define` discouraged in modern C++
 - `const` requires memory allocation
 - `enum` a common type, int
 - modern C++ `enum class`

**const**

`const int x = 123;` - compiler enforces immutability
pointers and const - read from right to left

**unscoped enums**

`enum Task { todo, done };` - integer constants; C++98
starts from 0
namespace pollution of the global namespace - "todo", "done" ...

Warning: implicit conversion to int, which may be handy, but also unsafe
or confusing. e.g.: `20*done` is 40 ...(?)

**scoped enumbs / class enums (C++11)**

`enum class Task { todo, done };` - scope is the Task class
usage: `auto status = Task::todo`

"todo" is of type Task, not int, so there are no implicit arithmetic
operations done when used. Explicit cast: `int(day::Mon)`

can be "forward declared" (underlying type defaults to int)
can specify an underlying type for the values, not necessarily int
`enum class Task: unsigned long;`

can iterate over an enum class, by defining an operator ++

```
enum class day { Mon, Tue, ... };

day& operator++(day& d) {
    return d = day(int(d) + 1));
}
// NOTE: can add a not_a_day sentinel value as last to hit the end

...
for (day d = day::Mon; d <= day::Sat; d++) {
    cout << int(d) << endl;
}
```
=> strong type safety and flexibilty

can have markers, as for the first and last element (better future extension)

```
enum class day { weekday_min, Mon = weekday_min, ..., Fri, weekday_max = Fri, not_a_day };
```

**constexpr** (C++11)

Evaluation at compile time, even of a function, if all inputs are const. If
not will be evaluated at runtime.

```
constexpr double mToCm(double x) { return x * 100; }
...
mToCm(y); // runtime
mToCm(5); // compile time
```

 - take and return only types that can be evalulated at compile time
 - can recurse; can be virtual; =default / =delete (what?)
 - no "go to", no "try catch"

Note: a VARIABLE with constexpr must be initialized at compile time, not like
const, which can be initialized at runtime as well.

```
int b = 0, c = 0;
const int b1 = b + 123; // ok
constexpr int c1 = c + 123; // compile error
```

### Extra notes

Terms from C++ standard: "undefined behaviour", "unspecificed behaviour".
When compiler cannot guarantee how the behaviour observed on a given platform
does not match the way the could would run on a "perfect" C++ standard virtual
machine.

Lambdas (anon functions) - to avoid namespace pollution, to make code more
readable.

### Resources

 - cppreference.com -> example: search "cppreference string"

