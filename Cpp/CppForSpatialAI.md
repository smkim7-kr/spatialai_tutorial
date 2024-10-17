
# Modern C++ for Robotics
### Based on https://github.com/LimHyungTae/moderncpp_study

## Functional Programming and Lambda Expressions

**Functional programming** essential for managing complex and parallelized code. In C++, functional programming can be achieved through **lambda expressions** and **STL algorithms**.

### Lambda Expressions (from C++11)
Lambda expressions are a powerful feature introduced in C++11 that allows to create **anonymous functions** directly within your code. They avoid searching for function definitions in different parts of the code thus make the code more concise.

**Syntax:**
```cpp
// return_type is optional 
[](parameters) -> return_type { function_body }
```


**Example:**
```cpp
// A lambda that calculates the square of a number
auto square = [](int a) -> int { return a * a; };
int result = square(5);  // result is 25
```

Lambda expressions can **capture external variables** in different ways:

1. **[]**: No external variables captured.
2. **[=]**: Capture external variables **by value**.
3. **[&]**: Capture external variables **by reference**.
4. **[var]** or **[&var]**: Capture a specific variable by value or reference.

Capture external variables by reference for large-sized objects thus to prevent unnecessary copy.

**Example:**
```cpp
int multiplier = 3;

// Capture by value (the value of multiplier is copied)
auto multiply_by_val = [=](int a) { return a * multiplier; };

// Capture by reference (changes to multiplier affect its external value)
auto multiply_by_ref = [&](int a) { return a * multiplier; };

int result1 = multiply_by_val(5);  // 15
int result2 = multiply_by_ref(5);  // 15

multiplier = 4;  // Change the value

int result3 = multiply_by_val(5);  // Still 15 (captured by value)
int result4 = multiply_by_ref(5);  // Now 20 (captured by reference)
```

### Lambda Expressions with STL Algorithms
Lambda expressions are most effective when used with **STL algorithms**. They simplify the code by eliminating the need for separate function definitions.

**Example with `std::for_each`:**
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};

// Use lambda to increase each value by 1, x iterates through numbers' elements
std::for_each(numbers.begin(), numbers.end(), [](int &x) { x += 1; });
```

### Anonymous and Named Lambda Functions
**Anonymous functions** (no name assigned) are useful when you need quick, throwaway functions.

**Example:**
```cpp
std::vector<int> vec = {1, 2, 3};
std::for_each(vec.begin(), vec.end(), [](int &x) { x *= 2; });  // Multiply each element by 2
```

**Named lambda functions** can be used as **first-class objects**, meaning they can be passed around or reused.

**Example:**
```cpp
auto increment = [](int &x) { x += 1; };  // Lambda assigned to a variable
std::for_each(vec.begin(), vec.end(), increment);  // Apply increment to each element
std::for_each(vec2.begin(), vec2.end(), increment);  // Named lambda functions can be reused
```

---

## std::for_each

The `for_each` loop offers a more streamlined way to iterate over elements of a container. 

- **C++98**: Traditional for-loop:
    ```cpp
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] += 1;
    }
    ```

- **C++11**: Range-based for-loop:
    ```cpp
    for (auto &val : vec) {
        val += 1;
    }
    ```

- **C++17**: `std::for_each` with lambda:
    ```cpp
    std::for_each(vec.begin(), vec.end(), [](int &x) { x += 1; });
    ```

**Parallel version** (C++17) allows for better performance in multi-core processors:
```cpp
#include <execution>
std::for_each(std::execution::par_unseq, vec.begin(), vec.end(), [](int &x) { x += 1; });
```

Be cautious with **dependencies** when using parallel algorithms. For example, modifying the container during parallel execution can lead to segmentation faults.

---

## std::insert()

`std::insert()` allows for efficient insertion of elements in **vectors**, **sets**, and other containers. However, performance may be impacted due to element shifts when inserting into vectors.

### Example: Insert into `std::vector`
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec.insert(vec.begin() + 2, 10);  // Insert 10 at index 2
```

### Example: Inserting a range from another container
```cpp
std::vector<int> vec2 = {6, 7, 8};
vec.insert(vec.end(), vec2.begin(), vec2.end());  // Append vec2 to vec

// better approach, prevent copying by using move semantics
vec.insert(vec.end(), std::make_move_iterator(vec2.begin()), std::make_move_iterator(vec2.end())); 
```

For **unique elements** like in `std::set`:
```cpp
std::set<int> set1 = {1, 2, 3};
std::set<int> set2 = {3, 4, 5};
set1.insert(set2.begin(), set2.end());  // Only unique elements are inserted
```

---

## std::move()

**Lvalues** are objects that have names, thus doesn’t disappear after expressions, whereas **rvalues** are temporary.

**Example:**
```cpp
int a = 10;   // a is an lvalue, 10 is an rvalue
int&& r = 20; // r is an rvalue reference
```

**std::move()** transfers ownership of resources, avoiding the overhead of copying.

**Example:**
```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = std::move(v1);  // v1's data is moved to v2
```

`std::move()` is particularly useful in **robotics** when dealing with **large datasets** like point clouds.

---

## std::transform()

`std::transform()` applies a transformation to each element in a source container and stores the result in a destination container.

**Example:**
```cpp
std::vector<int> src = {0, 1, 2, 3, 4};
std::vector<int> dst(5);

std::transform(src.begin(), src.end(), dst.begin(), [](int x) { return x + 1; });
// dst is now {1, 2, 3, 4, 5}
```

This function is commonly used in robotics for tasks like **coordinate transformations** or **sensor data processing**.

---

## std::accumulate()

`std::accumulate()` computes the sum or product of elements in a container.

**Example: Summing values:**
```cpp
int total = std::accumulate(vec.begin(), vec.end(), 0);  // Sum of elements
```

**Example: Finding the minimum value:**
```cpp
int min_val = std::accumulate(vec.begin(), vec.end(), vec[0], [](int a, int b) {
    return std::min(a, b);
});
```

---

## std::all_of(), std::any_of(), std::none_of()

These algorithms check for conditions across all elements in a container:

- **std::all_of**: Checks if **all elements** meet the condition.
    ```cpp
    bool allEven = std::all_of(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    ```

- **std::any_of**: Checks if **any element** meets the condition.
    ```cpp
    bool anyEven = std::any_of(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    ```

- **std::none_of**: Checks if **no elements** meet the condition.
    ```cpp
    bool noneEven = std::none_of(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    ```

---

## Conditional Algorithms: `*_if`

### std::copy_if()
`std::copy_if()` copies elements that meet a specific condition.

**Example:**
```cpp
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst;

std::copy_if(src.begin(), src.end(), std::back_inserter(dst), [](int x) {
    return x % 2 == 0;  // Copy only even numbers
});
// dst contains {2, 4}
```

### std::find_if()
`std::find_if()` searches for the first element that matches a condition:

**Example:**
```cpp
int search_val = 10;
auto it = std::find_if(vec.begin(), vec.end(), [search_val](const Object& obj) {
    return obj.m_var == search_val;  // Search for object with member variable m_var equal to search_val
});
```

### std::remove_if()

`std::remove_if()` is used to remove elements from a container based on a condition. It’s typically used with the `erase` function to actually remove the elements from the container, as `remove_if` only moves them to the end.

- **Example: Removing elements less than a certain value**

```cpp
std::vector<int> vec = {1, 9, 2, 8, 3, 7, 4};
const int threshold = 5;
vec.erase(std::remove_if(vec.begin(), vec.end(), [threshold](int x) {
    return x < threshold;  // Remove elements less than 5
}), vec.end());
// vec is now {9, 8, 7}
```

`std::remove_if()` can also be used with **custom object types**, typically for removing elements based on member variables.

- **Example: Removing objects based on a member variable**

```cpp
struct Object {
    int value;
};

std::vector<Object> objs = {{3}, {10}, {7}, {2}};
const int boundary = 6;
objs.erase(std::remove_if(objs.begin(), objs.end(), [boundary](const Object &obj) {
    return obj.value < boundary;  // Remove objects where value is less than 6
}), objs.end());
// objs now contains objects with values 10 and 7
```

---

### std::replace_if()

`std::replace_if()` replaces elements in a container that meet a specific condition with a new value.

- **Example: Replacing elements less than a threshold with zero**

```cpp
std::vector<int> vec = {1, 9, 2, 8, 3, 7, 4};
const int threshold = 5;
std::replace_if(vec.begin(), vec.end(), [threshold](int x) {
    return x < threshold;  // Replace elements less than 5
}, 0);
// vec is now {0, 9, 0, 8, 0, 7, 0}
```

Similarly, `replace_if()` can be used with custom objects to modify specific fields.

- **Example: Replacing object values**

```cpp
std::vector<Object> objs = {{3}, {10}, {7}, {2}};
const int boundary = 6;
std::replace_if(objs.begin(), objs.end(), [boundary](Object &obj) {
    return obj.value < boundary;  // Replace objects with value < 6
}, Object{0});  // Replace with Object having value 0
// objs now contains {Object{0}, Object{10}, Object{7}, Object{0}}
```
