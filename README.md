# MetaClass: Next-Generation Polymorphism in C++

## Overview

MetaClass is a cutting-edge C++ framework aiming to redefine polymorphism within the language. Leveraging the capabilities of C++20 and beyond, MetaClass introduces a high-performance, language-native, and non-intrusive design for polymorphism. By integrating macro metaprogramming, template metaprogramming, and multiple inheritance, alongside a sprinkle of type erasure, MetaClass allows for an innovative dynamic polymorphism solution in C++ that is both efficient and elegant.

## Key Features

- **Non-intrusive Design**: Enables polymorphic behavior without altering object design.
- **Ease of Use**: Simplifies the declaration and usage of polymorphic classes through macros and template metaprogramming.
- **Type-Safe Downcasting**: Allows for safe retrieval of the original object with complete type safety.
- **Reference Semantics Only**： MetaClass inherently adopts reference semantics, viewing it just as an observer, separating annoying lifecycle management from dynamic polymorphism.
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

### Defining Interfaces and Metalasses

1. **Define an Interface** using the `Interface` macro:

    ```cpp
    Interface(Add,
        Fn((string, string), string),
        Fn((int, int), int)
    ); 

    Interface(read,
        ((), void), 
    );
    ```
+ The first parameter defines the name of the interface.
+ All parameters, starting with the second parameter of the macro, make up the overload set of the interface.
+ The two parameters in each parameter correspond to the types of input and output parameters.
+ Fn is not mandatory and can be defaulted。
+ Due to the limitations of the macro recursion stack, the maximum size of the overload set for a single interface is 1024.

2. **Create a MetaClass** using the `Metaclass` macro::

    ```cpp
    Metaclass(Myclass, Add, read);
    ```
+ The first parameter defines the name of the Metaclass.
+ The parameters starting with the second parameter define the set of interfaces that the metaclass contains.
+ Due to the limitations of the macro recursion stack, the maximum size of the interface set for a single metaclass is 1024.
### Implementing and Using MetaClasses

1. **Implement your class** with the required methods:

    ```cpp
    struct MyClassImpl
    {
        int Add(int a, int b) { return a + b; }
        string Add(string a, string b) { return a + b; }
        void read() { std::cout << "read" << std::endl; }
    };
    ```
    
2. **Instantiate and use** your MetaClass:

    ```cpp
    MyClassImpl impl;
    Myclass metaObject(impl);

    std::cout << metaObject.Add("hello", "world") << std::endl;
    std::cout << metaObject.Add(2, 3) << std::endl;
    metaObject.read();
    ```
+ Since a metaclass is just an observer of the data, it can only be constructed from lvalues.
3. **Type-Safe Downcasting**:

    ```cpp
    auto& originalObject = Any_cast<MyClassImpl>(metaObject); // Safe
    auto& wrongCast = Any_cast<OtherType>(metaObject); // Compilation error
    ```
## Contributing

Contributions to MetaClass are welcome! Whether it's through submitting bug reports, writing documentation, or contributing code, we value your input and support.

## License

MetaClass is licensed under [insert your license here], making it suitable for both open source and private projects.

## Acknowledgments

Thank you to the entire C++ community, and to the ISO Committee, it was C++ that made this possible by making great strides in the metaprogramming space over the years.
