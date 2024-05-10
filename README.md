# MetaClass: Next-Generation Polymorphism in C++

## Overview

MetaClass is a cutting-edge C++ framework aiming to redefine polymorphism within the language. Leveraging the capabilities of C++20 and beyond, MetaClass introduces a high-performance, language-native, and non-intrusive design for polymorphism. By integrating macro metaprogramming, template metaprogramming, and multiple inheritance, alongside a sprinkle of type erasure, MetaClass allows for an innovative dynamic polymorphism solution in C++ that is both efficient and elegant.

## Key Features

- **Non-intrusive Design**: Enables polymorphic behavior without altering object design.
- **Ease of Use**: Simplifies the declaration and usage of polymorphic classes through macros and template metaprogramming.
- **Type-Safe Downcasting**: Allows for safe retrieval of the original object with complete type safety.
- **Fine-grained memory control**：The interface is available in both owner and observer interfaces, allowing for a higher degree of freedom for in-depth memory control.
- **Seamless Interaction with the C++ Type System**: MetaClass is designed to work harmoniously with the C++ type system, providing a smooth integration that leverages the full capabilities of the First-order Type.
- **Intuitive Object.Method(...) Calling Convention**: A standout feature of MetaClass is its support for the Object.Method(args...) calling style, Perfectly imitating the syntax and feel of virtual function-based polymorphism. The ability to use the familiar Object.Method(...) syntax enhances readability and usability, making MetaClass a more natural fit for C++ developers.
- **Performance Comparable to Static Polymorphism**: MetaClass approaches the performance of static polymorphism solutions like CRTP combined with std::variant, offering a dynamic polymorphism solution without the typical overhead associated with virtual functions.
- **Transparent Memory Layout**: The design of MetaClass ensures that the memory layout of polymorphic objects is transparent and predictable, aiding in optimization and understanding of how objects are stored and accessed in memory.


## Requirements

- **C++20 or later**: Utilizes features introduced in C++20, ensuring modern practices and optimizations.
- **Compiler Support**: Requires support for the MSVC, GCC extension `__COUNTER__` for macro expansions and template metaprogramming functionalities.

## Getting Started

Use the header file "Metaclass.h" after including the project：
```cpp
#include "Metaclass.h"
```

### Defining the Interfaces

**using the `Interface` macro to define an Interface**

```cpp
Interface(Myclass,
    Fn(Add,
        ((int,int),int),
		((double,double),double),
		((string,string),string)
    ),
    Fn(read,
        ((),void)
    ),
    Paren(
        ((int),int),
		((double),double)
    ),
    Oper(+,
        ((int),int),
    )
)
```
+ The first parameter defines the name of the interface.
+ The Fn macro is used to create a common function in an interface, the first parameter of Fn is the function name, and the subsequent parameters are the type signature and constitute the overload set of the function.
+ The Paren macro is used to create the operator() function in the interface, and all the parameters in Paren are also type-signes and form the overload set of the function.
+ The Oper macro is used to create additional overloaded operators in the interface, where all parameters are also type-signes and form the overload set of the function.
+ Due to the limitations of the macro recursion stack, the maximum size of the overload set for a single function is 32, and the maximum size of the funvtion set for a Interface is 32 too.
+ Due to some limitations, ",""[]" and all binary operators are temporarily unreloaded and are waiting to be updated in the future.

### Implementing and Using Inteface
1.**Define Interface**
```cpp
Interface(Myclass,
    Fn(Add,
        ((int,int),int),
		((double,double),double),
		((string,string),string)
    ),
    Fn(read,
        ((),void)
    )
)//The Interface macro creates two types, Myclass<OwnerShip::Owner> and Myclass<OwnerShip::Observer>, with the former managing memory and the latter not managing memory.
```
2. **Implement your class with the required methods**:

```cpp
struct A
{
    int Add(int a, int b) { return a + b; }
    double Add(double a, double b) { return a + b; }
    string Add(string a, string b) { return a + b; }
    void read() { std::cout << "A" << std::endl; }
    ~A() { std::cout << "~A" << std::endl; }
};

struct B
{
    int Add(int a, int b) { return a + b; }
    double Add(double a, double b) { return a + b; }
    string Add(string a, string b) { return a + b; }
    void read() { std::cout << "B" << std::endl; }
    ~B() { std::cout << "~B" << std::endl; }
};
```
3. **Instantiate and use your Interface**:

```cpp
string str = "str";
auto a = new A();
auto b = new B();
Myclass<OwnerShip::Owner> owner(std::move(*a));
std::cout << owner.Add(1, 8) << std::endl;
std::cout << owner.Add(1.0,2.1) << std::endl;
std::cout << owner.Add(str, str) << std::endl;
owner.read();
owner = std::move(*b); //a automatic destructuring
Myclass<OwnerShip::Observer> obser(owner);
std::cout << obser.Add(str, str) << std::endl;
std::cout << obser.Add(8, 9) << std::endl;
std::cout << obser.Add(1.1, 1.1) << std::endl;
obser.read();
```
+ You can always create an observer interface from an owner interface efficiently.
+ What is not shown here is that if an interface A is a subset of another interface B, then A can be constructed from interface B just as efficiently.
4. **Type-Safe Downcasting**:

```cpp
auto& originalObject = as<A>(owner); // Safe
auto  getsource = as<A>(std::move(owner)) // get the source safely
auto& wrongCast = as<OtherType>(metaObject); // Compilation error
```
+ An observer interface can not downcast.
## Contributing

Contributions to MetaClass are welcome! Whether it's through submitting bug reports, writing documentation, or contributing code, we value your input and support.

## License

MetaClass is licensed under [insert your license here], making it suitable for both open source and private projects.

## Acknowledgments

Thank you to the entire C++ community, and to the ISO Committee, it was C++ that made this possible by making great strides in the metaprogramming space over the years.
