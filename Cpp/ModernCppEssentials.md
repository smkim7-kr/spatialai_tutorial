# C++ In a Nutshell - Notes

## Module Import
- **Pre-C++20:** Use `#include <iostream>` for including libraries.
- **From C++20:** `import <iostream>` can be used instead, improving compilation times and dependency management.

## Build Process
1. **Preprocessing:** Handles source code metadata like `#include` directives, macros, and conditional compilation.
2. **Compilation:** Translates the preprocessed code into machine-readable object files (.obj or .o).
3. **Linking:** Links multiple object files into a final executable or library.

## Declaration and Definition
- **Before C++20:** Declarations typically resided in header files (`.h`), while definitions were in source files (`.cpp`).
- **From C++20:** Modules allow declarations and definitions to exist together, reducing redundancy.

> **Note:** C library headers like `<stdio.h>` may still require `#include`.

## `#pragma once`
- Prevents redundant inclusion of the same header file multiple times during compilation.

## I/O Stream
- **From C++20:** Use `std::format()` for string formatting instead of concatenation.
    ```cpp
    std::cout << std::format("There are {} bananas", 2) << std::endl;
    ```
- **`endl` vs `\n`:**
    - `endl` flushes the output buffer and may slow down performance, especially in loops.
    - `\n` does not flush the buffer, so it’s faster.

- **Why not `printf()` or `scanf()`?**
    - These functions do not ensure type safety, making them less reliable than C++ alternatives.

## Namespaces
- Used to avoid name conflicts, especially between external libraries and your code.
- **Using Keyword:**
    - `using namespace myspace`: Makes `myspace::` namespace the default.
    - `using std::cout`: Only applies `std` namespace to `cout`.
    - **Warning:** Do not use `using` in header files, as it can cause unexpected conflicts.
- **Nested Namespaces:**
    - Before C++17: `namespace A { namespace B { ... } }`
    - From C++17: `namespace A::B { ... }`
- **Namespace Alias:**
    - Shorten long namespace names:
      ```cpp
      namespace AtoD = A::B::C::D;
      ```

## Variables
- **Initialization:**
    - Uniform initialization is recommended:
      ```cpp
      int var { 10 }; float f { 2.4f }; bool b { true };
      ```
- **C++ is a strongly typed language**, meaning variables must be explicitly typed.
- **`std::byte` (from C++17):**
    - Used to explicitly indicate a byte rather than a character.
    ```cpp
    std::byte b { 42 };
    ```
- **`std::numeric_limits`:**
    - Displays the minimum and maximum values for types:
      ```cpp
      numeric_limits<int>::max();
      ```

### Type Casting
- **Recommended:**
    ```cpp
    float f { 3.14f };
    int i { static_cast<int>(f) };
    ```
- **Implicit Cast:**
    ```cpp
    short s { 5U };
    long l { s };  // Implicit because long has a wider precision.
    ```

### Enumerations
- **Strongly Typed Enums (enum class):**
    ```cpp
    enum class PieceType { K, Q, R, P };
    PieceType p { PieceType::K };
    ```
- **From C++20:**
    - Can use `using enum PieceType` to simplify code.

### Module File (.cppm)
- Modules are introduced to replace header files and improve build times and maintainability.

## Functions
- **`__func__`:** Outputs the current function name, useful for logging.
- **Function Overloading:** Same function name but with different parameter types or return types.

### Attributes (From C++11)
- **`[[nodiscard]]`:** Warns if return values are ignored.
- **`[[maybe_unused]]`:** Prevents unused variable warnings.
- **`[[noreturn]]`:** Indicates that the function will never return.
- **`[[deprecated]]`:** Marks code as deprecated.

## Arrays
- **C-style Arrays:**
    ```cpp
    int arr[3] = {0};  // Array of size 3, initialized to 0.
    ```
- **C++-style Arrays:**
    - Use `std::array` for fixed-size arrays:
      ```cpp
      std::array<int, 2> arr { 1, 2 };
      ```
    - Use `std::vector` for dynamic-size arrays:
      ```cpp
      std::vector<int> v { 1, 2 };
      ```

## Object-Oriented Programming (OOP)
- A major distinction between C and C++.
- In C++, class definitions can be stored in module interface files (`.cppm`).

## Pointers and Dynamic Memory
- Use pointers for handling memory that cannot be determined at compile time.
- **Dynamic Memory Allocation:**
    ```cpp
    int* ptr = new int;
    *ptr = 10;
    delete ptr;  // Always free memory manually!
    ```

## Constants and References
- **`const` Keyword:**
    - Replaces `#define` constants in C.
    ```cpp
    const int var { 5 };
    ```
- **`constexpr`:** Compile-time constant expression.
- **References:** 
    - A reference is an alias for another variable. Once initialized, it cannot be changed.
    ```cpp
    int x { 3 };
    int& ref { x };  // ref and x are now aliases.
    ```

## Exception Handling
- C++ provides robust error handling mechanisms:
    ```cpp
    try {
        // code
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
    }
    ```

## Type Inference and Aliasing
- **Type Aliases:**
    ```cpp
    using intptr = int*;
    intptr p;
    ```
- **`auto` Keyword:**
    - Allows type inference:
    ```cpp
    auto x = 5;
    ```

## Standard Libraries
- Always prefer using standard libraries over custom implementations. They are well-tested and optimized.
    - e.g., `std::string`, `std::vector`, `std::optional`.

