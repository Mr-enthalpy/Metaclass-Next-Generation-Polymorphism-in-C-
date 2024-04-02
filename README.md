# MetaClass: Next-Generation Polymorphism in C++

## Overview

MetaClass is a cutting-edge C++ framework aiming to redefine polymorphism within the language. Leveraging the capabilities of C++20 and beyond, MetaClass introduces a high-performance, language-native, and non-intrusive design for polymorphism. By integrating macro metaprogramming, template metaprogramming, and multiple inheritance, alongside a sprinkle of type erasure, MetaClass allows for an innovative dynamic polymorphism solution in C++ that is both efficient and elegant.

## Key Features

- **Non-intrusive Design**: Enables polymorphic behavior without altering object design.
- **Enhanced Performance**: Optimizes polymorphic calls to be as close to native language performance as possible.
- **Ease of Use**: Simplifies the declaration and usage of polymorphic classes through macros and template metaprogramming.
- **Type-Safe Downcasting**: Allows for safe retrieval of the original object with complete type safety.
- **Reference Semantics Only**： MetaClass inherently adopts reference semantics, viewing it just as an observer, can only be constructed from lvalues.

## Requirements

- **C++20 or later**: Utilizes features introduced in C++20, ensuring modern practices and optimizations.
- **Compiler Support**: Requires support for the MSVC, GCC extension `__COUNTER__` for macro expansions and template metaprogramming functionalities.

## Getting Started

### Defining Interfaces and Classes

1. **Define an Interface** using the `Interface` macro:

    ```cpp
    Interface(Add,
        Fn((string, string), string),
        Fn((int, int), int)
    ); //The maximum number of overload sets that can be accepted for an interface is 1024

    Interface(read,
        ((), void), //The maximum number of metatypes contained in a metaclass is 1024.
    );
    ```

+ All parameters, starting with the second parameter of the macro, make up the overload set of the interface.
+ The two parameters in each parameter correspond to the types of input and output parameters
+ Fn is not mandatory and can be defaulted

2. **Create a MetaClass** with the defined interfaces:

    ```cpp
    Metaclass(Myclass, Add, read);
    ```

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

3. **Type-Safe Downcasting**:

    ```cpp
    auto originalObject = Any_cast<MyClassImpl>(metaObject); // Safe
    auto wrongCast = Any_cast<OtherType>(metaObject); // Compilation error
    ```

## Contributing

Contributions to MetaClass are welcome! Whether it's through submitting bug reports, writing documentation, or contributing code, we value your input and support.

## License

MetaClass is licensed under [insert your license here], making it suitable for both open source and private projects.

## Acknowledgments

Thank you to the entire C++ community, and to the ISO Committee, it was C++ that made this possible by making great strides in the metaprogramming space over the years.
