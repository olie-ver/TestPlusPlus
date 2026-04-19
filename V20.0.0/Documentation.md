# C++ Unit Tester V20.0.0 (Beta)
A C++ Unit Tester for C++20 written by Oliver Lie. As a beta build/release, I make no guarantees that future versions will work the same, and implementations could change until the first working release.

### License/Conditions of Usage
You may consider this code open-source to be downloaded, modified, and released for others under the condition that any other subsidiary code will keep these same conditions. This includes keeping the software free of charge.

## Table of Contents
1. [Adding To Your Projects](#adding-to-your-projects)
    1. [Compiling And Linking](#compiling-and-linking)
    2. [Include Inside Your Project](#include-inside-your-project)
    3. [CLI Usage](#cli-usage)
2. [Testing](#testing)
    1. [Registering Tests](#registering-tests)
    2. [Different Types Of Tests](#different-types-of-tests)
3. [Boolean Tests](#boolean-tests)
    1. [Assert True](#assert_true)
    2. [Assert False](#assert_false)
    3. [Expect True](#expect_true)
    4. [Expect False](#expect_false)
4. [Comparison Tests](#comparison-tests)
    1. [Assert Equals](#assert_eq)
    2. [Assert Not Equals](#assert_ne)
    3. [Assert Less Than](#assert_lt)
    4. [Assert Less Than or Equals](#assert_le)
    5. [Assert Greater Than](#assert_gt)
    6. [Assert Greater Than or Equals](#assert_ge)
    7. [Expect Equals](#expect_eq)
    8. [Expect Not Equals](#expect_ne)
    9. [Expect Less Than](#expect_lt)
    10. [Expect Less Than or Equals](#expect_le)
    11. [Expect Greater Than](#expect_gt)
    12. [Expect Greater Than or Equals](#expect_ge)

## Adding To Your Projects

### Compiling And Linking
In order to add to your projects, you need the libtester.a library file. As a static library, it will need to be linked to in the compilation phase. A minimum working directory to compile and link the library is as follows: <br> 
Root/ <br> 
&emsp;include/ <br>
&emsp;&emsp;tester/ <br> 
&emsp;libtester.a <br> 
&emsp;Main.cpp <br> 
With this, the compile command would be: <br> 
`g++ -std=c++17 -Wall -Wextra -I./include -c Main.cpp` <br>
`g++ -std=c++17 -Wall -Wextra -I./include Main.o libtester.a -o NAME_OF_EXECUTABLE` <br> 
There are more ways to compile and link, and I expect the general user to have more complicated file systems. 

### Include Inside Your Project
Inside your project, you can include the library like so:
<br>
At the top of your file add:
`#include <tester/Tests.hpp>`.
<br>
And now you can start testing right away.

### CLI Usage
As of now, the way to use the unit tester is like so:
<br>
`PATH_TO_EXECUTABLE --verbosity-flag`  
<br>
The current verbosity flags are:
<br>
1. `--default`
2. `--verbose`
3. `--minimum`
4. `--all`
<br>
As of now, only `--minimum` changes the output, which only shows which tests pass/fail/skip and what test suite and test they belonged to.

## Testing

### Registering Tests
In order to register a test, there are two options: `TEST(suite_name, test_name)` or `D_TEST(test_name)`. Providing a suite_name is a great way to sort tests instead of having them all in random order. Suite names must be unique, and test names must be unique within a suite.

Some usage examples below:
```
#include <tester/Tests.hpp>

//No main() is required

D_TEST(name) { //Notice name has no quotes inside the macro
    ...
    NAME_OF_TEST(parameters...);
}
```

```
#include <tester/Tests.hpp>

//No main() is required

TEST(suite_name, test_name) { //Notice neither name have quotes
    ...
    NAME_OF_TEST(parameters...);
}
```

An example of an disallowed naming:

```
#include <tester/Tests.hpp>

D_TEST(not_unique_name) {
    ...
    NAME_OF_TEST(parameters...);
}

D_TEST(not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}
```
In the above example, compilation will fail because the test is defined twice. One more example with TEST() to drive it home:

```
#include <tester/Tests.hpp>

TEST(suite_name, not_unique_name) {
    ...
    NAME_OF_TEST(parameters...);
}

//Totally fine because it's registered under a different test suite

TEST(another_suite_name, not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}

//Not fine because this test is defined twice under the same suite

TEST(another_suite_name, not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}
```

### Different Types of Tests
There are two types of tests supported: Expects and Asserts. Expects tests will always run to fruition no matter what (failure or throws), but Asserts tests will stop testing the current test suite upon failure.

## Boolean Tests
Boolean tests are used to check the truthiness of a value/condition.

1. [Assert True](#assert_true)
2. [Assert False](#assert_false)
3. [Expect True](#expect_true)
4. [Expect False](#expect_false)

### ASSERT_TRUE()
`ASSERT_TRUE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_true) {
    ASSERT_TRUE(true); //passes
    ASSERT_TRUE(5 != 10); //passes
    ASSERT_TRUE(1 == 2); //fails
    ASSERT_TRUE("cool", "nice"); //doesn't get run
}
```

### ASSERT_FALSE()
`ASSERT_FALSE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `false` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_false) {
    ASSERT_FALSE(false); //passes
    ASSERT_FALSE(5 == 10); //passes
    ASSERT_FALSE(1 != 2); //fails
    ASSERT_FALSE("cool", "nice"); //doesn't get run
}
```

### EXPECT_TRUE()
`EXPECT_TRUE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `true` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(expect_true) {
    EXPECT_TRUE(true); //passes
    EXPECT_TRUE(5 != 10); //passes
    EXPECT_TRUE(1 == 2); //fails
    EXPECT_TRUE("cool", "nice"); //runs and fails
}
```

### EXPECT_FALSE()
`EXPECT_FALSE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `false` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(expect_false) {
    EXPECT_FALSE(false); //passes
    EXPECT_FALSE(5 == 10); //passes
    EXPECT_FALSE(1 != 2); //fails
    EXPECT_FALSE("cool", "nice"); //runs and passes
}
```

## Comparison Tests
Comparison tests are used to compare the relation between two different values. 

1. [Assert Equals](#assert_eq)
2. [Assert Not Equals](#assert_ne)
3. [Assert Less Than](#assert_lt)
4. [Assert Less Than or Equals](#assert_le)
5. [Assert Greater Than](#assert_gt)
6. [Assert Greater Than or Equals](#assert_ge)
7. [Expect Equals](#expect_eq)
8. [Expect Not Equals](#expect_ne)
9. [Expect Less Than](#expect_lt)
10. [Expect Less Than or Equals](#expect_le)
11. [Expect Greater Than](#expect_gt)
12. [Expect Greater Than or Equals](#expect_ge)

### ASSERT_EQ()
`ASSERT_EQ(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `==` operator. It passes iff `a == b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(assert_equals) {
    ASSERT_EQ(5, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    ASSERT_EQ(ref, numbers); //passes
    ASSERT_EQ(numbers, ref);
}
```

### ASSERT_NE()
`ASSERT_NE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `!=` operator. If the `!=` operator is not defined between the two parameters, it will fall back on using `==` for comparison. In the case that `!=` is defined on `a` and `b`, the test will pass iff `a != b` is `true` and fails otherwise. In the case that `!=` is not defined on `a` and `b`, the test will pass iff `!(a == b)` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(assert_not_equals) {
    ASSERT_NE(10, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    ASSERT_NE(ref, numbers); //fails
    ASSERT_NE(numbers, ref); //doesn't run
}
```

### ASSERT_LT()
`ASSERT_LT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<` operator. It passes iff `a < b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_less_than) {
    ASSERT_LT(-1, 5); //passes
    ASSERT_LT(-5.00, 0); //passes
}
```

### ASSERT_LE()
`ASSERT_LE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_less_than_equals) {
    ASSERT_LE(-1, 5); //passes
    ASSERT_LE(5, 5); //passes
    ASSERT_LE(1, 0); //fails
}
```

### ASSERT_GT()
`ASSERT_GT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>` operator. It passes iff `a > b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_greater_than) {
    ASSERT_GT(0x105, 5); //passes
    ASSERT_GT(-5.00, 0); //fails
}
```

### ASSERT_GE()
`ASSERT_GE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>=` operator. It passes iff `a >= b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_greater_than_equals) {
    ASSERT_GE(0x105, 5); //passes
    ASSERT_GE(0x105, 0x104); //passes
}
```

### EXPECT_EQ()
`EXPECT_EQ(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `==` operator. It passes iff `a == b` is `true` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(assert_equals) {
    EXPECT_EQ(5, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    EXPECT_EQ(ref, numbers); //passes
    EXPECT_EQ(numbers, ref);
}
```

### EXPECT_NE()
`EXPECT_NE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `!=` operator. If the `!=` operator is not defined between the two parameters, it will fall back on using `==` for comparison. In the case that `!=` is defined on `a` and `b`, the test will pass iff `a != b` is `true` and fails otherwise. In the case that `!=` is not defined on `a` and `b`, the test will pass iff `!(a == b)` is `true` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(assert_not_equals) {
    EXPECT_NE(10, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    EXPECT_NE(ref, numbers); //fails
    EXPECT_NE(numbers, ref); //runs and fails
}
```

### EXPECT_LT()
`EXPECT_LT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<` operator. It passes iff `a < b` is `true` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(assert_less_than) {
    EXPECT_LT(-1, 5); //passes
    EXPECT_LT(-5.00, 0); //passes
}
```

### EXPECT_LE()
`EXPECT_LE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise.
```
#include <tester/Tests.hpp>

D_TEST(assert_less_than_equals) {
    EXPECT_LE(-1, 5); //passes
    EXPECT_LE(5, 5); //passes
    EXPECT_LE(1, 0); //fails
}
```

### EXPECT_GT()
`EXPECT_GT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>` operator. It passes iff `a > b` is `true` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(assert_greater_than) {
    EXPECT_GT(0x105, 5); //passes
    EXPECT_GT(-5.00, 0); //fails
}
```

### EXPECT_GE()
`EXPECT_GE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise.
```
#include <tester/Tests.hpp>

D_TEST(assert_greater_than_equals) {
    EXPECT_GE(0x105, 5); //passes
    EXPECT_GE(0x105, 0x104); //passes
}
```