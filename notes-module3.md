### Types and Classes

#### User Type Declaration

type aliases

C++98
```
typedef unique_ptr<map<string, int>> UPtrM;
typedef void (*p) (int, int);
```

C++11
more flexible and easier to read for template types and function pointers
```
using UPtrM = unique_ptr<map<string, int>>;
using P = void(*) (int, int);
```

typedef was designed for C, not convienent for complex types (e.g. templates)

#### Structures

struct = related data grouped together
struct members are public
(!) in C++ can have also member functions, not only variables

```
struct Person {
  std::string name;
  int age;
  void print() {
    std::cout << name << std::end;
  }
};
...
Person p;
p.name = "JD";
p.print();
```

Code organization:
 - in header file person.h -> struct with member function decl void print();
 - in impl file person.cpp -> `void Person::print() { ... }`

Constructors - even in structs, to set up initial state

```
struct Number {
  int value;
  Number(int n) : value(n) { cout << "Ctor << endl; }
};
...
Number n1 = 0; // work if only one member; invokes ctor(0)
Number n2(0);  // C++98
Number n3{0};  // C++11 (more modern, more uniform)
```

Narrowing conversion when intializing:
 - for ex from double to int
 - if {} used, the narrowing conversion is flagged as an error (possible loss
   of precision)

```
double a = 1, b = 2;
int z1(a + b); // impl conv
int z2 = a + b;// impl conv 
int z3{a + b}; // error - narrowing conversion flagged
```

Initializer list
 - commonly used to initialize containers

```
struct V {
  std::vector <int> vs;
  V(std::initializer_list<int> a) : vs{a} {
    for (auto v : vs) { cout << v; }
  }
}

V x{1, 2, 3}; // simple, works because of the initialize_list ctro
```

Constructors can be overloaded (different params). Init with {} will prefer the
ctor with initializer list.

There can be also a default ctor, no params - V().
```
V v1; // def ctor
V v2{}; // def ctor
V v3(); // is NOT a struct init, but a function declaration.
V v4({}); // initializer_list ctor, with empty list
V v5{{}}; // initializer list
```

Takeaway: braces matters (e.g. vector initialization)
```
std::vector<int> v1(5, 10); // vector of 5 elems, value 10
std::vector<int> v2{5, 10); // vector with 5 and 10
```

Access Modifiers

public/private/protected

```
struct A {
public:
  int a1; // can be modified from outside
  int getA2() { return a2; } // can return the private member
private:
  int a2{123}; // only access from within the struct
               // {} field initialization - has val of 123 in a new struct
};
```

#### Classes

Similar to struct - group data and functions.
But different default access levels (in `class` by default private).

Struct -> typically a data structure, access to data it holds
Class  -> encapsulate data and provide controlled access
(note that structs can also do inheritance)
(struct or class - if there are additional rules between members => class;
 if there are no rules => can be struct; )

Encapsulation helps to control dependencies between different parts of the code.

Pointer to an instance of a class

```
class A {
  int a;
public:
  int getA() const { return a; } // const prevents class state changes
  void setA(int a_) { a = a_; }  // setter
}

func() {
  A a1; // stack
  A* a2 = new A; // heap
  a2->getA() 
  ...
  delete a2;
}
```

The `this` pointer

implicit pointer available in non-static member functions

`this->name` can serve to show the reader that name is a member of this instance
but you can also pass the current instance to another function `bus->add(this)`

Note about public/private/protected:
(!) usually protected only for methods, not for members; create protected access
functions instead for use in subclasses

#### Operator overloading

Custom behavior for operators when applied to user defined classes. Allows 
using intuitive operators like with built-in type, making code more readable.

```
class Number {
  int value;
public:
  Number(int v) : value(v) {}
  int getValue() const { return value; }
  
  Number operator+(Number x) {
    return Number(value + x.value);
  }
}
```

What can be overloaded: operators, bitwise, logical, shift, comparison,
incr/decr, even member access.

#### Explicit keyword

For ctor, adding `explicit` tells the compiler to not use it in an implicit
chain of constructor conversions. 

```
class Number {
public:
  explicit Number(int x) {} // converting ctor from int to number
                            // but can't be used in other implicit conversions
}

class Square
  ctor (Number side)

Square s{100}; // err; implicit would be int -> Number -> Square
```

Best practice: mark all ctor-s with a single arugment as eplicit. (!)

### Object lifecycle

Rule of three: if you need a copy ctor, copy assignment ctor, or a destructor,
you usually need all three.

 - destructor - needed if a class allocates dynamic memory, for ex
 - copy ctor - to avoid shallow copies of dynamically allocated resources
 - copy assignment operator - same

```
template <typename T>
class P {
private:
  T* p;
public:
  P(T* p_) : p{p_} { };
  
  ~P() { delete p; }; // destructor
  
  P(const P& p_) {
    cout << "copy ctor" << endl;
    p = new T;
    p* = *p_.p;
  }

  P& operator=(const P& p_) {
    // assignment
    if (this != p_) {
      delete p;
      p = new T;
      *p = *p.p;
    }
    return *this;
  }

  T operator*() {
    return *p;
  }
}

int main() {
  P<int> a{new int(2)}, b{new int(3)}; // init with pointers to integers
  cout << *a << *b << endl; // 2 3; operator * retrieves the values
  P<int> tmp = a; // copy constuctor; allocates new memory and copies the value
  a = b; // copy assignment; free memory, allocates, copies
  b = tmp;
  cout << *a << *b << endl; // 3 2 
}
```

Rvalue references: special type of references for telling the compiler when
move operations can be applied.

```
int&& a = 42; // valid, but not used in practice; more for user-defined
              // a binds to the temp value 42

class A{};
A&& b = A();  // A() is a temp objects and b binds to it

A C = A();    // here c is an lvalue, an object with persistent state

A&& d = std::move(c); // converts c into an r value, allowing d to bind to it
                      // d should take ownership of the resources managed by c

```

Rule of five: extension for additional operations introduced in C++11

 - destructor
 - copy ctor
 - copy asisignment operator
 - move ctor - transfers resources from a temp object to a new object
 - move assignment operator

(move semantics introduced in C++11 => rule of five instead of three)

```
// move ctor - transfer ownership from p_ to the new object created
P(P&& p_) : p(p_.p) { // init new with resource pointer from source
  p_.p = nullptr;     // leave source in a valid, empty state
}
// P<int> tmp = std::move(a);

P& operator=(P&& p_) {
  delete p; // needed (to release current resource)
  p = p_.p;
  p_.p = nullptr;
  return *this;
}
// a = std::move(b);

int main() {
  P<int> a{new int(2)}, b{new int(3)}; // dynamic alloc of ints
  cout << *a << *b << endl;           
  P<int> tmp = move(a); // tmp -> "2"; a -> nullptr
  a = move(b); // a -> "3" (a holds resource prev held by b); b empty
  b = move(tmp);
  cout << *a << *b << endl;
}
// efficient transfer of resources, without copying resources
// after each move, the original object is left in a valid but empty state
```

"rvalue references" - not really references, but another way to assign variables

if move ctor is not defined, overloading will make it such that copy ctor is called

### Inheritance and polymorphism

Inheritance - extend classes without changing their definition
 - elimitate redundancy (more specific classes use code from generic ones)
 - define common interfaces (shared interfaces that all subclasses must implement)

```
class <name> : <visibility> <superclass name> {
  <class body>
};
```

"visibility" - what access level will members from base class have in derived
 - public - public and protected members will be inherited with same access
 - private - public and protected become private members
 - protected - they become protected

```
class Shape {
protected: // accessible in derived classes
  int x, y;
public:
  Shape(int x_, int y_) : x{x_}, y{y_} {}
  void print const { cout << "shape(" << x << "," << y << ")" : endl; }
}

class Circle : public Shape { // all public members in Shape remain public in Circle
public:
  using Shape::shape; // use the base class ctor (ctor inheritance)
  
  void print const { cout << "circle(" << x << "," << y << ")" : endl; }
  // error if x and y would have been "private"
}

Shape s{2, 3};
s.print();
Circle c{2, 3};
c.print();
```

private members are not available outside of class, not even in derived classes
but `protected`, yes

Object substitution - a subclass can stand for its superclass

```
Shape* s = new Circle{2, 3};
s->print(); // Shape(2,3), base class "print()"
```

Virtual functions (dynamic dispatch) - the derived class method will be called,
not like for object substitution
=> Enabled polymorphic behaviour

```
class Shape {
...
  virtual void print() const { ...conut ... }
...
};
class Circle : public Shape {
public:
  using Shape::Shape;
  void print() const override {
    ...
  }
};
```

based on v-table (each class with virtual methods has one); each object has a
pointer to this table, so it does not matter if you call a method through a
base class pointer

(!) a virtual destructor is important so that the destructor of a subclass is
called when a subclass is deleted through a base class pointer. Important for
proper cleanup. Subclass destructor called, then base destructor


Constructor calls order

 - base class ctor
 - member object ctors (member objects of the class)
 - derived class ctor

Diamond problem

Supporting multiple inheritance can lead to ambiguous inheritance. Base class
derived by mulitple paths and then subclass derives multiple of these paths.
Multiple instances of A for a single sub-object?

Solution: virtual inheritance; onlty a single instance of A.

```
class A { int x; };

class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {}; // only one instance of A
```


Q:
General
 - initilizaion () vs {} vs normal "=" ; what is the underlying difference, best practices
 - what is the rationale for the ctor syntax "ctor(...) : member(m), member(n) { } " instead of setting the members inside the ctor body
   (is it `initializer_list` related?)
 - override vs no override, what is the difference?
 - a bit of recap or more explanations about "move semantics"
 - in the move assignment operator, shouldn't the resources be "deleted" first, before copying the pointer from the argument?
 - can you implement abstract classes, pure interfaces, with no method implementation
 
 
Other notes:

Encapsulation
 - "getters and setters always" - not necessarily; you might not want to have a setter
 - indeed, narrowest possible interface, which can be opened up later

Interfaces
 - there is no dedicated way to create interfaces in Cpp, not a dedicated syntax
 - LE: you can have "pure virtual functions" - no implementation => so, yes
 - note that "interfaces" and "inheritance" are different concepts (e.g. in Go there
   are interfaces but not classic inheritance). E.g.: a lot of different type of objects
   that are all "orderable", or "printable". Inheritance shows difference/specialization,
   Interfaces shows commonality
 - concept of "mix-in" - you can extend a class to get its functionality; powerful, but
   can lead to a complicated design, class hierarchy
 - Note: "pure function" in standard programming - no side-effects; but here, no body
 
Polymorphism
 - write code in terms of base class (superclass); develop code in terms of "abstractions"
   not implementation
 - based on virtual functions and vtable (this accounts for the difference in performance
   between C and C++; the indirection of calls, dynamic dispatch)
 - avoid "object slicing" - base class = sub class (without using pointers) => extra
   variables in the "sub class" will be lost

Dtor
 - only if out object contains some managed state (pointers, OS resources etc)
 - if you will use inheritance, dtor should be virtual
 - (in C++14, at least no way to tell compiler that a class can't be inherited from)
 - consider RAII - resource acquisition is initialization

Initializations
 - avoid a(1); {} are better -> transforms to initializer list; "=" still ok if ctor
   has one argument
 - if there are no special concerns, use a uniform approach (use {})
 
Java
 - always use new when creating an object => heap
 - in C++ you can create them on the stack as well, without "new"




