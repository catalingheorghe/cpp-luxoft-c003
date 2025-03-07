### Advanced programming

#### Storage duration and object lifetime

 - automatic - bounded to the scope in which it is defined
 - dynamic - allocated and deallocated manually at runtime
 - static - allocated at program startup, until the end
 - thread-local - bound to a thread

```
int main() {
    A a; // Ctor; automatic storage;
    {
        // other code
        A a; // Ctor; another A, created now, after other code
    } // dtor for inner A

    A* a = new A;
    // ...
    delete a;
} // Dtor for outer A
```

When a block is entered, each block creates a new stack frame on the stack.
Do not return references (or pointers) to local variables.

Default initialization for static storage (global) is 0.

A static class data member is shared accross all instances of a class. Can be
initialized and used without any objects being created.

#### Dynamic memory allocation

Using raw pointers (`A* a`) is tricky, can lead to memory leaks, dangling
pointers, double frees ...

Deprecated: `std::auto_ptr>T>` replaced by unique and shared since C++. When
pointer of that type went out of scope, dtor called. The problem with this
was that ownership was transferred when calling a function with `auto_ptr`
parameter, and the original pointer was left NULL. Unintuitive.

**Unique ptr smart pointer**

`unique_ptr` - only one of these pointers can hold a dynamically allocated
resource at any time

```
std::unique_ptr<A> p{new A{42}};
std::unique_ptr<A> p1 = p; // compilation error
// no copy constructor, no copy assignement

f(std::move(p)); // f(unique_ptr<A> p) ...
// to transfer ownership, must use move
// p is nullptr, not valid for accessing resource anymore
```

`make_unique<T1>` introduced to simplify creation of unique ptr objects,
properly handling exceptions if something goes wrong.

```
unique_ptr<A> p = make_unique<A>(42); // instead of unique_ptr(A{42})
// exception safety instead of calling the unique_ptr ctor directly
```

**Shared ptr smart pointer**

`shared_ptr` - manages lifetime through referece counting; when no shared ptr
instances reference the same object, it is destroyed

```
std::shared_ptr<A> p{new A{42}}; // p.use_count() = 1
f(p);
  f(void shared_ptr<A> p) {
    // p.use_count() = 2 (from the parameter)
    shared_ptr<A> p1 = p; // use_count = 3
  }
// p.use_count() back to 1
```

custom deallocators can be defined
```
shared_ptr<A> p(new A[5], [](A* p){ delete[] p; });
// free the mem of the array that was created
```

circular references
if you set the internal pointers of a shared ptr to another shared ptr and
viceversa, you will create a circular reference that will keep them both
alive forever

To adderss this: use `weak_ptr`; make a weak ptr out of a shared one `w{p1}`
then if you want another one `shared_ptr<A> p2 = w.lock()`
...?
object A -> object B -> object C -> object A (also circular dependency)
a weak ptr doesn't affect the ref count, it is not an owner of the object
...?

Guidelines:
 - avoid raw pointers, use smart ptrs
 - start with unique ptr
 - if required, shared ptr
 - if circular dependencies, weak ptr

#### Data representation

C-like casts are dangerous (e.g.: different memory representation).
No type safety, no runtime checks, potential memory corruption.

C++ casts: `const_cast<> static_cast<> dynamic_cast<> reinterpret_cast<>`

**Const cast**

```
class A {
public:
  int a;
  void changeA() const {
    const_cast<A*>(this)->a = 1; // remove const
  }
};
```
- generally not recommended, but can have valid use-cases like lazily
initializing a variable only the first time

- or could be used to remove const when passing to a function that expects
a non-const (API compatibility). If the function does modify it, this leads
to undefined behavior

- works only for same type (const int* -> int*)

**Static cast**

```
double a = 123.345;
static_cast<int>(a)   // 123
static_cast<float>(a) // 123.345 
static_cast<char>(a)  // { - ASCII value 123
static_cast<char*>(a) // compile error; unrelated types

```
- used for related types that compiler can determine are safe
- or related pointer types (base and derived class pointers)
- or can be used for a conversion to another type

```
class A {
public:
  int x;
  operator std::string() {
    return std::to_string(x);
  }
};

static_cast<std::string>(a)
```

- or pointer casts
```
int i = 123;
void *v = static_cast<void*>(&i);
int *p = static_cast<int*>(v);
```

**Dynamic cast**

- upcasting and downcasting - between based and derived class pointers
upcasting is treating a derived class as a base class (usually safe)
downcasting, the other way around and may not be safe

```
Child c1;
Parent *p = dynamic_cast<Parent*>(&c1); // safe; unnecessary
Child *c2 = dynamic_cast<Child*>(p); // base class must be polymorphic
  // (min 1 virtual function), it will then have RTTI (run time type info)
  // so the compiler can check if the base class pointer really points to
  // the expected derived class that it is casted to
```

**Reinterpret cast**

- no checks

#### Error handling

**Assertions**

assert macro => check what should always be true; execution stopped if false
in production code, defining NDEBUG turns off assert

`static_assert` => compile-time checks; usually to check portability
`static_assert(sizeof(int) == 4, "Invalid size of int.");`

**Exceptions**

report and handle runtime errors

```
try {
  throw std::string("Error!");
} catch (std::string s) {
  std::cout << s << std::endl;
}

class Error() {};
class SubError() : public Error() {};
...
try {
  throw new SubError;// throw a subclass 
} catch (Error* e) { // catch the base class
  ...
}
```

 - exceptions must be handled, or the program terminates
 - clearly separate happy-path from non-happy-path
 - hierarchical structure than can be more flexible and meaningful than error codes
 - requires more resources for saving stack states







Questions:

 - shared ptr: why are custom deallocators needed? Why isn't calling the dtor enough?
   slide 31
 - weak ptr: not clear
