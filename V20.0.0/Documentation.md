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
5. [Null Tests](#null-tests)
    1. [Assert Null](#assert_null)
    2. [Assert Not Null](#assert_not_null)
    3. [Expect Null](#expect_null)
    4. [Expect Not Null](#expect_not_null)
6. [String Tests](#string-tests)
    1. [Assert String Equals](#assert_str_eq)
        1. [std::string](#stdstring)
        2. [const char*](#const-char)
        3. [char[]](#char)
    2. [Assert String Not Equals](#assert_str_ne)
        1. [std::string](#stdstring-1)
        2. [const char*](#const-char-1)
        3. [char[]](#char-1)
    3. [Assert String Empty](#assert_str_emt)
        1. [std::string](#stdstring-2)
        2. [const char*](#const-char-2)
        3. [char[]](#char-2)
    4. [Assert String Not Empty](#assert_str_nemt)
        1. [std::string](#stdstring-3)
        2. [const char*](#const-char-3)
        3. [char[]](#char-3)
    5. [Assert String Contains](#assert_str_contains)
        1. [std::string](#stdstring-4)
        2. [const char*](#const-char-4)
        3. [char[]](#char-4)
    6. [Assert String Starts With](#assert_str_starts_with)
        1. [std::string](#stdstring-5)
        2. [const char*](#const-char-5)
        3. [char[]](#char-5)
    7. [Assert String Ends With](#assert_str_ends_with)
        1. [std::string](#stdstring-6)
        2. [const char*](#const-char-6)
        3. [char[]](#char-6)
    8. [Expect String Equals](#expect_str_eq)
        1. [std::string](#stdstring-7)
        2. [const char*](#const-char-7)
        3. [char[]](#char-7)
    9. [Expect String Not Equals](#expect_str_ne)
        1. [std::string](#stdstring-8)
        2. [const char*](#const-char-8)
        3. [char[]](#char-8)
    10. [Expect String Empty](#expect_str_emt)
        1. [std::string](#stdstring-9)
        2. [const char*](#const-char-9)
        3. [char[]](#char-9)
    11. [Expect String Not Empty](#expect_str_nemt)
        1. [std::string](#stdstring-10)
        2. [const char*](#const-char-10)
        3. [char[]](#char-10)
    12. [Expect String Contains](#expect_str_contains)
        1. [std::string](#stdstring-11)
        2. [const char*](#const-char-11)
        3. [char[]](#char-11)
    13. [Expect String Starts With](#expect_str_starts_with)
        1. [std::string](#stdstring-12)
        2. [const char*](#const-char-12)
        3. [char[]](#char-12)
    14. [Expect String Ends With](#expect_str_ends_with)
        1. [std::string](#stdstring-13)
        2. [const char*](#const-char-13)
        3. [char[]](#char-13)
7. [Throws Tests](#throws-tests)
    1. [Assert Throws](#assert_throws)
    2. [Assert Does Not Throw](#assert_does_not_throw)
    3. [Expect Throws](#expect_throws)
    4. [Expect Does Not Throw](#expect_does_not_throw)
8. [Float Tests](#float-tests)
    1. [Assert Near](#assert_near)
    2. [Assert Relatively Near](#assert_rel_near)
    3. [Assert Absolutely Near](#assert_abs_near)
    4. [Assert NaN](#assert_nan)
    5. [Assert Not NaN](#assert_not_nan)
    6. [Expect Near](#expect_near)
    7. [Expect Relatively Near](#expect_rel_near)
    8. [Expect Absolutely Near](#expect_abs_near)
    9. [Expect NaN](#expect_nan)
    10. [Expect Not NaN](#expect_not_nan)
9. [Iterable Tests](#iterable-tests)
    1. [Assert Ordered Equals](#assert_ordered_eq)
    2. [Assert Unordered Equals](#assert_unordered_eq)
    3. [Expect Ordered Equals](#expect_ordered_eq)
    4. [Expect Unordered Equals](#expect_unordered_eq)
10. [Test Tests](#test-tests)
    1. [Assert Passes](#assert_passes)
    2. [Assert Fails](#assert_fails)
    3. [Expect Passes](#expect_passes)
    4. [Expect Fails](#expect_fails)

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

## Null Tests
Null tests are used to check if a value is equal to the `nullptr` or not. Since it checks solely for the `nullptr`, passing in the macro `NULL` is not a valid parameter type for any of the test. 

1. [Assert Null](#assert_null)
2. [Assert Not Null](#assert_not_null)
3. [Expect Null](#expect_null)
4. [Expect Not Null](#expect_not_null)

### ASSERT_NULL()
`ASSERT_NULL(val)` takes in a single parameter `val` and asserts that it's the nullptr. This test passes iff `val == nullptr` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_null) {
    ASSERT_NULL(nullptr) //passes
    ASSERT_NULL(NULL) //doesn't even compile
}
```

### ASSERT_NOT_NULL()
`ASSERT_NOT_NULL(val)` takes in a single parameter `val` and asserts that it's not the nullptr. This test passes iff `val != nullptr` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_null) {
    ASSERT_NOT_NULL("hello") //passes
    ASSERT_NOT_NULL(nullptr) //fails
    ASSERT_NOT_NULL(NULL) //doesn't even compile
}
```

### EXPECT_NULL()
`EXPECT_NULL(val)` takes in a single parameter `val` and checks that it's the nullptr. This test passes iff `val == nullptr` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(assert_null) {
    void* ptr = nullptr;
    void*& ref = ptr;
    EXPECT_NULL(ref) //passes
    EXPECT_NULL(NULL) //doesn't even compile
}
```

### EXPECT_NOT_NULL()
`EXPECT_NOT_NULL(val)` takes in a single parameter `val` and checks that it's not the nullptr. This test passes iff `val != nullptr` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(assert_null) {
    void* ptr = nullptr;
    void*& ref = ptr;
    EXPECT_NOT_NULL(ref) //fails
    EXPECT_NOT_NULL(NULL) //doesn't even compile
}
```

## String Tests
Strings tests are used for checking the (in)equality of strings and whether or not they're empty. Null strings should be checked with using the [null tests](#null-tests). The string tests are defined on `std::string`, `char*`, and `char[]`. Different overloads are used on depending on which parameter type you pass in. Note that for the `char[]`, passing in arrays of different lengths is not enough to disqualify equality as one could pass in two arrays of the "same string" but one padded with extra null-terminator characters `'\0'`. The tests will only look at everything that comes before the first null-terminator character, if any.


1. [Assert String Equals](#assert_str_eq)
    1. [std::string](#stdstring)
    2. [const char*](#const-char)
    3. [char[]](#char)
2. [Assert String Not Equals](#assert_str_ne)
    1. [std::string](#stdstring-1)
    2. [const char*](#const-char-1)
    3. [char[]](#char-1)
3. [Assert String Empty](#assert_str_emt)
    1. [std::string](#stdstring-2)
    2. [const char*](#const-char-2)
    3. [char[]](#char-2)
4. [Assert String Not Empty](#assert_str_nemt)
    1. [std::string](#stdstring-3)
    2. [const char*](#const-char-3)
    3. [char[]](#char-3)
5. [Assert String Contains](#assert_str_contains)
    1. [std::string](#stdstring-4)
    2. [const char*](#const-char-4)
    3. [char[]](#char-4)
6. [Assert String Starts With](#assert_str_starts_with)
    1. [std::string](#stdstring-5)
    2. [const char*](#const-char-5)
    3. [char[]](#char-5)
7. [Assert String Ends With](#assert_str_ends_with)
    1. [std::string](#stdstring-6)
    2. [const char*](#const-char-6)
    3. [char[]](#char-6)
8. [Expect String Equals](#expect_str_eq)
    1. [std::string](#stdstring-7)
    2. [const char*](#const-char-7)
    3. [char[]](#char-7)
9. [Expect String Not Equals](#expect_str_ne)
    1. [std::string](#stdstring-8)
    2. [const char*](#const-char-8)
    3. [char[]](#char-8)
10. [Expect String Empty](#expect_str_emt)
    1. [std::string](#stdstring-9)
    2. [const char*](#const-char-9)
    3. [char[]](#char-9)
11. [Expect String Not Empty](#expect_str_nemt)
    1. [std::string](#stdstring-10)
    2. [const char*](#const-char-10)
    3. [char[]](#char-10)
12. [Expect String Contains](#expect_str_contains)
    1. [std::string](#stdstring-11)
    2. [const char*](#const-char-11)
    3. [char[]](#char-11)
13. [Expect String Starts With](#expect_str_starts_with)
    1. [std::string](#stdstring-12)
    2. [const char*](#const-char-12)
    3. [char[]](#char-12)
14. [Expect String Ends With](#expect_str_ends_with)
    1. [std::string](#stdstring-13)
    2. [const char*](#const-char-13)
    3. [char[]](#char-13)

### ASSERT_STR_EQ()
`ASSERT_STR_EQ(a, b)` takes in two arguments, both are strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. Both arguments must be of the same type. Depending on which type is passed in, a different overload, and therefore different method of determining equality will be used. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
In the case where both `a` and `b` are of type `std::string`, their equality is evaluated based on the `==` operator.

```
#include <tester/Tests.hpp>
#include <string>

TEST(assert_str_eq, std_strings) {
    std::string a = "hello";
    std::string b = "hello";

    ASSERT_STR_EQ(a, b); //passes
    
    std::string c = "hello\0";
    
    ASSERT_STR_EQ(a, c); //passes
    ASSERT_STR_EQ(b, c); //passes

    std::string d = "goodbye";
    ASSERT_STR_EQ(c, d); //fails
}
```

#### `const char*`:
In the case where both `a` and `b` are of type `const char*`, their equality is evaluated based on the `strcmp()` function. Passing in two null `const char*` pointers will be considered equal, and will pass.

```
#include <tester/Tests.hpp>

TEST(assert_str_eq, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    ASSERT_STR_EQ(a, b); //passes

    const char* c = "hello\0";

    ASSERT_STR_EQ(a, c); //passes
    ASSERT_STR_EQ(b, c); //passes

    const char* d = "goodbye";
    ASSERT_STR_EQ(c, d); //fails
}
```

#### `char[]`:
In the case where both `a` and `b` are of type `char[]`, their equality is evaluated based on the contents of each `char[]`. It is not enough for the lengths of the arrays to be different to disqualify equality as one could pass in two arrays of the "same string" but one padded with extra null-terminator characters `'\0'`.

```
#include <tester/Tests.hpp>

TEST(assert_str_eq, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    ASSERT_STR_EQ(a, b); //passes

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    ASSERT_STR_EQ(a, c); //passes because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    ASSERT_STR_EQ(a, d); //fails because the length of d[] is different than the length of a[]
}
```

### ASSERT_STR_NE()
`ASSERT_STR_NE(a, b)` takes in two arguments, both are strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. Both arguments must be of the same type. Depending on which type is passed in, a different overload, and therefore different method of determining equality will be used. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
In the case where both `a` and `b` are of type `std::string`, their equality is evaluated based on the `!=` operator.

```
#include <tester/Tests.hpp>
#include <string>

TEST(assert_str_ne, std_strings) {
    std::string a = "hello";
    std::string b = "hello!";

    ASSERT_STR_NE(a, b); //passes
    
    std::string c = "hi";
    
    ASSERT_STR_NE(a, c); //passes
    ASSERT_STR_NE(b, c); //passes

    std::string d = "hello\0";
    ASSERT_STR_NE(a, d); //fails
}
```

#### `const char*`:
In the case where both `a` and `b` are of type `const char*`, their equality is evaluated based on the `strcmp()` function. Passing in two null `const char*` pointers will be considered equal, and will fail.

```
#include <tester/Tests.hpp>

TEST(assert_str_ne, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    ASSERT_STR_NE(a, b); //fails

    const char* c = "hello\0";

    ASSERT_STR_NE(a, c); //doesn't run, but would fail
    ASSERT_STR_NE(b, c); //doesn't run, but would fail

    const char* d = "goodbye";
    ASSERT_STR_NE(c, d); //doesn't run, but would pass
}
```

#### `char[]`:
In the case where both `a` and `b` are of type `char[]`, their equality is evaluated based on the contents of each `char[]`. It is not enough for the lengths of the arrays to be different to disqualify inequality.

```
#include <tester/Tests.hpp>

TEST(assert_str_ne, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    ASSERT_STR_NE(a, b); //fails

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    ASSERT_STR_NE(a, c);    //doesn't run, but if it did, it fails because everything 
                            //before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    ASSERT_STR_NE(a, d);    //doesn't run, but if it did, it passes because the 
                            //length of d[] is different than the length of a[]
}
```

### ASSERT_STR_EMT()
`ASSERT_STR_EMT(a)` takes in one parameter, being a string. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. This test checks that the passed in string is empty. String emptiness is determined by the type of parameter being passed in. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
For `std::string`, emptiness is determined by the `empty()` method.

```
#include <tester/Tests.hpp>

TEST(assert_str_emt, std_string) {
    std::string a = "";
    ASSERT_STR_EMT(a); //passes

    std::string b = "hi";
    ASSERT_STR_EMT(b); //fails

    std::string c = nullptr;
    ASSERT_STR_EMT(c); //doesn't run but would have a segmentation fault. You have been warned.
}
```

#### `const char*`:
For `const char*`, emptiness is determined by whether or not the first character is the null terminator character `'\0'`.

```
#include <tester/Tests.hpp>

TEST(assert_str_emt, char_ptr) {
    const char* a = "";
    ASSERT_STR_EMT(a); //passes

    const char* b = "hi";
    ASSERT_STR_EMT(b); //fails

    const char* c = nullptr;
    ASSERT_STR_EMT(c); //doesn't run, but would fail
}
```

#### `char[]`:
For `char[]`, emptiness is determined by whether whether or not the first character in the array is the null terminator character `'0'`.

```
#include <tester/Tests.hpp>

TEST(assert_str_emt, char_arr) {
    char a[] = "";
    ASSERT_STR_EMT(a); //passes

    const char b[] = "hi";
    ASSERT_STR_EMT(b); //fails

    const char c[] = nullptr;
    ASSERT_STR_EMT(c); //doesn't run, but there would be a segmentation fault. You have been warned.
}
```

### ASSERT_STR_NEMT()
`ASSERT_STR_NEMT(a)` takes in one parameter, being a string. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String non-emptiness is determined by the type of parameter being passed in. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
For `std::string`, non-emptiness is determined by the `empty()` method.

```
#include <tester/Tests.hpp>

TEST(assert_str_nemt, std_string) {
    std::string a = "";
    ASSERT_STR_NEMT(a); //fails

    std::string b = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    std::string c = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would segmentation fault. You have been warned.
}
```

#### `const char*`:
For `const char*`, non-emptiness is determined by whether or not the first character is the null terminator character `'\0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_nemt, char_ptr) {
    const char* a = "";
    ASSERT_STR_NEMT(a); //fails

    const char* b = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    const char* c = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would fail
}
```

#### `char[]`:
For `char[]`, non-emptiness is determined by whether whether or not the first character in the array is the null terminator character `'0'`.

```
#include <tester/Tests.hpp>

TEST(assert_str_nemt, char_arr) {
    char a[] = "";
    ASSERT_STR_NEMT(a); //fails

    const char b[] = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    const char c[] = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would segmentation fault. You have been warned.
}
```

### ASSERT_STR_CONTAINS()
`ASSERT_STR_CONTAINS(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String contains is dependent on what kind of parameter is passed in. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
For `std::string`, string contains is determined by the `find()` method. This test passes iff `string.find(substr)` does not return `std::string::npos` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(assert_str_contains, string) {
    std::string a = "hello";
    std::string b = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //would pass
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_contains, char_ptr) {
    const char* a = "hello";
    const char* b = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //passes
    
    const char* c = nullptr;

    ASSERT_STR_CONTAINS(a, c); //fails
    ASSERT_STR_CONTAINS(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_CONTAINS(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_contains, char_arr) {
    char a[] = "hello";
    char b[] = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //passes
}
```

### ASSERT_STR_STARTS_WITH()
`ASSERT_STR_STARTS_WITH(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String starts-with is dependent on what kind of parameter is passed in. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
For `std::string`, string contains is determined by the `starts_with()` method. This test passes iff `string.starts_with(substr)` does not return `false` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(assert_str_starts_with, string) {
    std::string a = "hello";
    std::string b = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_starts_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes

    const char* c = nullptr;

    ASSERT_STR_STARTS_WITH(a, c); //fails
    ASSERT_STR_STARTS_WITH(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_STARTS_WITH(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_starts_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes
}
```

### ASSERT_STR_ENDS_WITH()
`ASSERT_STR_ENDS_WITH(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String starts-with is dependent on what kind of parameter is passed in. Upon failure it will terminate testing for the test suite it was called in.

#### `std::string`:
For `std::string`, string contains is determined by the `starts_with()` method. This test passes iff `string.ends_with(substr)` does not return `false` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(assert_str_ends_with, string) {
    std::string a = "hello";
    std::string b = "lo";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_ends_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes

    const char* c = nullptr;

    ASSERT_STR_ENDS_WITH(a, c); //fails
    ASSERT_STR_ENDS_WITH(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_ENDS_WITH(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(assert_str_ends_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes
}
```

### EXPECT_STR_EQ()
`EXPECT_STR_EQ(a, b)` takes in two arguments, both are strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. Both arguments must be of the same type. Depending on which type is passed in, a different overload, and therefore different method of determining equality will be used. 

#### `std::string`:
In the case where both `a` and `b` are of type `std::string`, their equality is evaluated based on the `==` operator.

```
#include <tester/Tests.hpp>
#include <string>

TEST(expect_str_eq, std_strings) {
    std::string a = "hello";
    std::string b = "hello";

    EXPECT_STR_EQ(a, b); //passes
    
    std::string c = "hello\0";
    
    EXPECT_STR_EQ(a, c); //passes
    EXPECT_STR_EQ(b, c); //passes

    std::string d = "goodbye";
    EXPECT_STR_EQ(c, d); //fails
}
```

#### `const char*`:
In the case where both `a` and `b` are of type `const char*`, their equality is evaluated based on the `strcmp()` function. Passing in two null `const char*` pointers will be considered equal, and will pass.

```
#include <tester/Tests.hpp>

TEST(expect_str_eq, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    EXPECT_STR_EQ(a, b); //passes

    const char* c = "hello\0";

    EXPECT_STR_EQ(a, c); //passes
    EXPECT_STR_EQ(b, c); //passes

    const char* d = "goodbye";
    EXPECT_STR_EQ(c, d); //fails
}
```

#### `char[]`:
In the case where both `a` and `b` are of type `char[]`, their equality is evaluated based on the contents of each `char[]`. It is not enough for the lengths of the arrays to be different to disqualify equality as one could pass in two arrays of the "same string" but one padded with extra null-terminator characters `'\0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_eq, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    EXPECT_STR_EQ(a, b); //passes

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    EXPECT_STR_EQ(a, c); //passes because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    EXPECT_STR_EQ(a, d); //fails because the length of d[] is different than the length of a[]
}
```

### EXPECT_STR_NE()
`EXPECT_STR_NE(a, b)` takes in two arguments, both are strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. Both arguments must be of the same type. Depending on which type is passed in, a different overload, and therefore different method of determining equality will be used. 

#### `std::string`:
In the case where both `a` and `b` are of type `std::string`, their equality is evaluated based on the `!=` operator.

```
#include <tester/Tests.hpp>
#include <string>

TEST(expect_str_ne, std_strings) {
    std::string a = "hello";
    std::string b = "hello!";

    EXPECT_STR_NE(a, b); //passes
    
    std::string c = "hi";
    
    EXPECT_STR_NE(a, c); //passes
    EXPECT_STR_NE(b, c); //passes

    std::string d = "hello\0";
    EXPECT_STR_NE(a, d); //fails
}
```

#### `const char*`:
In the case where both `a` and `b` are of type `const char*`, their equality is evaluated based on the `strcmp()` function. Passing in two null `const char*` pointers will be considered equal, and will fail.

```
#include <tester/Tests.hpp>

TEST(expect_str_ne, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    EXPECT_STR_NE(a, b); //fails

    const char* c = "hello\0";

    EXPECT_STR_NE(a, c); //fails
    EXPECT_STR_NE(b, c); //fails

    const char* d = "goodbye";
    EXPECT_STR_NE(c, d); //passes
}
```

#### `char[]`:
In the case where both `a` and `b` are of type `char[]`, their equality is evaluated based on the contents of each `char[]`. It is not enough for the lengths of the arrays to be different to disqualify inequality.

```
#include <tester/Tests.hpp>

TEST(expect_str_ne, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    EXPECT_STR_NE(a, b); //fails

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    EXPECT_STR_NE(a, c); //fails because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    EXPECT_STR_NE(a, d); //passes because the length of d[] is different than the length of a[]
}
```

### EXPECT_STR_EMT()
`EXPECT_STR_EMT(a)` takes in one parameter, being a string. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. This test checks that the passed in string is empty. String emptiness is determined by the type of parameter being passed in. 

#### `std::string`:
For `std::string`, emptiness is determined by the `empty()` method.

```
#include <tester/Tests.hpp>

TEST(expect_str_emt, std_string) {
    std::string a = "";
    EXPECT_STR_EMT(a); //passes

    std::string b = "hi";
    EXPECT_STR_EMT(b); //fails

    std::string c = nullptr;
    EXPECT_STR_EMT(c); //segmentation fault. You have been warned.
}
```

#### `const char*`:
For `const char*`, emptiness is determined by whether or not the first character is the null terminator character `'\0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_emt, char_ptr) {
    const char* a = "";
    EXPECT_STR_EMT(a); //passes

    const char* b = "hi";
    EXPECT_STR_EMT(b); //fails

    const char* c = nullptr;
    EXPECT_STR_EMT(c); //fails
}
```

#### `char[]`:
For `char[]`, emptiness is determined by whether whether or not the first character in the array is the null terminator character `'0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_emt, char_arr) {
    char a[] = "";
    EXPECT_STR_EMT(a); //passes

    const char b[] = "hi";
    EXPECT_STR_EMT(b); //fails

    const char c[] = nullptr;
    EXPECT_STR_EMT(c); //segmentation fault. You have been warned.
}
```

### EXPECT_STR_NEMT()
`EXPECT_STR_NEMT(a)` takes in one parameter, being a string. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String non-emptiness is determined by the type of parameter being passed in. 

#### `std::string`:
For `std::string`, non-emptiness is determined by the `empty()` method.

```
#include <tester/Tests.hpp>

TEST(expect_str_nemt, std_string) {
    std::string a = "";
    EXPECT_STR_NEMT(a); //fails

    std::string b = "hi";
    EXPECT_STR_NEMT(b); //passes

    std::string c = nullptr;
    EXPECT_STR_NEMT(c); //segmentation fault. You have been warned.
}
```

#### `const char*`:
For `const char*`, non-emptiness is determined by whether or not the first character is the null terminator character `'\0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_nemt, char_ptr) {
    const char* a = "";
    EXPECT_STR_NEMT(a); //fails

    const char* b = "hi";
    EXPECT_STR_NEMT(b); //passes

    const char* c = nullptr;
    EXPECT_STR_NEMT(c); // fails
}
```

#### `char[]`:
For `char[]`, non-emptiness is determined by whether whether or not the first character in the array is the null terminator character `'0'`.

```
#include <tester/Tests.hpp>

TEST(expect_str_nemt, char_arr) {
    char a[] = "";
    EXPECT_STR_NEMT(a); //fails

    const char b[] = "hi";
    EXPECT_STR_NEMT(b); //passes

    const char c[] = nullptr;
    EXPECT_STR_NEMT(c); //segmentation fault. You have been warned.
}
```

### EXPECT_STR_CONTAINS()
`EXPECT_STR_CONTAINS(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String contains is dependent on what kind of parameter is passed in.

#### `std::string`:
For `std::string`, string contains is determined by the `find()` method. This test passes iff `string.find(substr)` does not return `std::string::npos` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(expect_str_contains, string) {
    std::string a = "hello";
    std::string b = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_contains, char_ptr) {
    const char* a = "hello";
    const char* b = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
    
    const char* c = nullptr;

    EXPECT_STR_CONTAINS(a, c); //fails
    EXPECT_STR_CONTAINS(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_CONTAINS(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_contains, char_arr) {
    char a[] = "hello";
    char b[] = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
}
```

### EXPECT_STR_STARTS_WITH()
`EXPECT_STR_STARTS_WITH(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String starts-with is dependent on what kind of parameter is passed in.

#### `std::string`:
For `std::string`, string contains is determined by the `starts_with()` method. This test passes iff `string.starts_with(substr)` does not return `false` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(expect_str_starts_with, string) {
    std::string a = "hello";
    std::string b = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_starts_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes

    const char* c = nullptr;

    EXPECT_STR_STARTS_WITH(a, c); //fails
    EXPECT_STR_STARTS_WITH(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_STARTS_WITH(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_starts_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes
}
```

### EXPECT_STR_ENDS_WITH()
`EXPECT_STR_ENDS_WITH(string, substr)` takes in two arguments, both being strings. There are three types of strings that can be passed in: `std::string`, `const char*`, and `char[]`. String starts-with is dependent on what kind of parameter is passed in.

#### `std::string`:
For `std::string`, string contains is determined by the `starts_with()` method. This test passes iff `string.ends_with(substr)` does not return `false` and fails otherwise.

```
#include <tester/Tests.hpp>
#include <string>

TEST(expect_str_ends_with, string) {
    std::string a = "hello";
    std::string b = "lo";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes
}
```

#### `const char*`:
For `const char*`, string contains first checks if either `char*` is the `nullptr`. If only one of them are, this test fails. Note that this means that passing in two `nullptr` parameters will result in a passing test case. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_ends_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes

    const char* c = nullptr;

    EXPECT_STR_ENDS_WITH(a, c); //fails
    EXPECT_STR_ENDS_WITH(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_ENDS_WITH(c, d); //passes
}
```

#### `char[]`:
For `const char[]`, string contains first checks if the length of `string` is less than the length of `substr`. If it is, this test fails. If this is not the case, both `string` and `substr` are converted to `std::string` and then tested on using the above test case. 

```
#include <tester/Tests.hpp>

TEST(expect_str_ends_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes
}
```

## Throws Tests
Throws tests are used to check whether or not a function throws or does not throw an error. You are able to pass in anonymous functions, as well as functions that require parameters. Since functions can take parameters or none, you must pass in the function with `()` at the end of the function name.

1. [Assert Throws](#assert_throws)
2. [Assert Does Not Throw](#assert_does_not_throw)
3. [Expect Throws](#expect_throws)
4. [Expect Does Not Throw](#expect_does_not_throw)

### ASSERT_THROWS()
`ASSERT_THROWS(func, ex)` takes in up to two parameters: a function and optionally a type of exception that should be thrown. In the case that `ex` is not provided, it will pass iff `func` throws anything. In the case that `ex` is provided, it will pass iff `func` throws the same exception type as `ex`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

void dumbFunc() {
    throws 42;
}

void anotherFunc() { }

TEST(assert_throws, no_exception_type) {
    ASSERT_THROWS(dumbFunc); //passes

    ASSERT_THROWS(anotherFunc); //fails because it doesn't throw anything
}
```

```
#include <tester/Tests.hpp>

void dumbFunc() {
    throw 42;
}

TEST(assert_throws, with_exception_type) {
    ASSERT_THROWS(dumbFunc, int); //passes
    
    ASSERT_THROWS(dumbFunc, std::invalid_argument); //fails because it doesn't throw the specified type
}
```

### ASSERT_DOES_NOT_THROW()
`ASSERT_DOES_NOT_THROW(func)` takes in one parameter, which is just a function. It passes iff `func` does not throw anything. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_does_not_throw) {
    ASSERT_DOES_NOT_THROW([&]() { }); //passes
    ASSERT_DOES_NOT_THROW([&]() { throw 42; }); //fails
}
```

### EXPECT_THROWS()
`EXPECT_THROWS(func, ex)` takes in up to two parameters: a function and optionally a type of exception that should be thrown. In the case that `ex` is not provided, it will pass iff `func` throws anything. In the case that `ex` is provided, it will pass iff `func` throws the same exception type as `ex`. 

```
#include <tester/Tests.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

void anotherFunc() { }

TEST(expect_throws, no_exception_type) {
    EXPECT_THROWS(dumbFunc(40, 2)); //passes
    EXPECT_THROWS(anotherFunc()); //fails
}
```

```
#include <tester/Tests.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

TEST(expect_throws, with_exception_type) {
    EXPECT_THROWS(dumbFunc(40, 2), float); //fails because it throws an int
    EXPECT_THROWS(dumbFunc(40, 2), int); //passes
}
```

### EXPECT_DOES_NOT_THROW()
`EXPECT_DOES_NOT_THROW(func)` takes in one parameter, which is just a function. It passes iff `func` does not throw anything. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

D_TEST(expect_does_not_throw) {
    EXPECT_DOES_NOT_THROW(dumbFunc(40, 2)); //fails
    EXPECT_DOES_NOT_THROW([&]() { }); //passes
}
```

## Float Tests
Float tests are used to check something about a float, generally absolute/relative tolerance. These can also be used to check for `NaN`. Each test can take in any combination of floating point types. Ie, for tests that take in multiple floating point values, it's possible to mix the type parameters (eg. pass in a `float` and `double`). In this case, they are cast to the common floating point type and these commonly cast versions are used in the tests.

1. [Assert Near](#assert_near)
2. [Assert Absolutely Near](#assert_abs_near)
3. [Assert Relatively Near](#assert_rel_near)
4. [Assert NaN](#assert_nan)
5. [Assert Not NaN](#assert_not_nan)
6. [Expect Near](#expect_near)
7. [Expect Absolutely Near](#expect_abs_near)
8. [Expect Relatively Near](#expect_rel_near)
9. [Expect NaN](#expect_nan)
10. [Expect Not NaN](#expect_not_nan)

### ASSERT_NEAR()
`ASSERT_NEAR(a, b, abs_tol, rel_tol)` takes in up to four arguments. `a` and `b` are two floating point values of any two floating point types. `abs_tol` is the absolute tolerance that should be between `a` and `b`. `rel_tol` is an optional parameter that defines how relatively near `a` and `b` should be.

In the case that `rel_tol` is not provided, this test becomes the same as [Assert Absolutely Near](#assert_abs_near). 

In the case that `rel_tol` is provided, this test passes iff `|a - b| <= max(|abs_tol|, |rel_tol| * max(|a|, |b|))`. That is, the absolute difference of `a` and `b` must be smaller than the larger of the absolute value of `abs_tol` and the product of the absolute value of `rel_tol` and the larger of `|a|` and `|b|`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

TEST(assert_near, three_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;

    ASSERT_NEAR(a, b, abs_tol); //fails
}

TEST(assert_near, four_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;
    long double rel_tol_pass = 0.5;
    long double rel_tol_fail = 0.05;

    ASSERT_NEAR(a, b, abs_tol, rel_tol_pass); //passes
    ASSERT_NEAR(a, b, abs_tol, rel_tol_fail); //fails
}
```

### ASSERT_ABS_NEAR()
`ASSERT_ABS_NEAR(a, b, abs_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `abs_tol` defines the maximum difference `a` and `b` can be from each other. This test passes iff `|a - b| <= |abs_tol|`. That is, the absolute difference of `a` and `b` must be smaller than the absolute value of `abs_tol`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_abs_near) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 2.0;

    ASSERT_ABS_NEAR(a, b, abs_tol); //passes

    long double abs_tol_two = 0.5;
    ASSERT_ABS_NEAR(a, b, abs_tol_two); //fails because |a - b| > 0.5
}
```

### ASSERT_REL_NEAR()
`ASSERT_REL_NEAR(a, b, rel_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `rel_tol` defines how relatively near `a` and `b` should be. This test passes iff `|a - b| <= |rel_tol| * max(|a|, |b|)`. That is, the absolute difference of `a` and `b` must be smaller than the product of `rel_tol` and the larger of `|a|` and `|b|`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_rel_near) {
    float a = 5.0;
    double b = 6.0;
    long double rel_tol = 0.5;

    ASSERT_REL_NEAR(a, b, rel_tol); //passes

    long double rel_tol_two = 0.1;
    ASSERT_REL_NEAR(a, b, rel_tol_two); //fails because 0.1 * 0.6 = 0.06 < |a - b|
}
```

### ASSERT_NAN()
`ASSERT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is equivalent to `NAN` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_nan) {
    float a = 5.0;

    ASSERT_NAN(a); //fails
}
```

### ASSERT_NOT_NAN()
`ASSERT_NOT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is not equivalent to `NAN` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

D_TEST(assert_nan) {
    float a = 5.0;

    ASSERT_NOT_NAN(a); //passes
}
```

### EXPECT_NEAR()
`EXPECT_NEAR(a, b, abs_tol, rel_tol)` takes in up to four arguments. `a` and `b` are two floating point values of any two floating point types. `abs_tol` is the absolute tolerance that should be between `a` and `b`. `rel_tol` is an optional parameter that defines how relatively near `a` and `b` should be.

In the case that `rel_tol` is not provided, this test becomes the same as [Expect Absolutely Near](#expect_abs_near). 

In the case that `rel_tol` is provided, this test passes iff `|a - b| <= max(|abs_tol|, |rel_tol| * max(|a|, |b|))`. That is, the absolute difference of `a` and `b` must be smaller than the larger of the absolute value of `abs_tol` and the product of the absolute value of `rel_tol` and the larger of `|a|` and `|b|`.

```
#include <tester/Tests.hpp>

TEST(expect_near, three_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;

    EXPECT_NEAR(a, b, abs_tol); //fails
}

TEST(expect_near, four_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;
    long double rel_tol_pass = 0.5;
    long double rel_tol_fail = 0.05;

    EXPECT_NEAR(a, b, abs_tol, rel_tol_pass); //passes
    EXPECT_NEAR(a, b, abs_tol, rel_tol_fail); //fails
}
```

### EXPECT_ABS_NEAR()
`EXPECT_ABS_NEAR(a, b, abs_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `abs_tol` defines the maximum difference `a` and `b` can be from each other. This test passes iff `|a - b| <= |abs_tol|`. That is, the absolute difference of `a` and `b` must be smaller than the absolute value of `abs_tol`.

```
#include <tester/Tests.hpp>

D_TEST(expect_abs_near) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 2.0;

    EXPECT_ABS_NEAR(a, b, abs_tol); //passes

    long double abs_tol_two = 0.5;
    EXPECT_ABS_NEAR(a, b, abs_tol_two); //fails because |a - b| > 0.5
}
```

### EXPECT_REL_NEAR()
`EXPECT_REL_NEAR(a, b, rel_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `rel_tol` defines how relatively near `a` and `b` should be. This test passes iff `|a - b| <= |rel_tol| * max(|a|, |b|)`. That is, the absolute difference of `a` and `b` must be smaller than the product of `rel_tol` and the larger of `|a|` and `|b|`.

```
#include <tester/Tests.hpp>

D_TEST(expect_rel_near) {
    float a = 5.0;
    double b = 6.0;
    long double rel_tol = 0.5;

    EXPECT_REL_NEAR(a, b, rel_tol); //passes

    long double rel_tol_two = 0.1;
    EXPECT_REL_NEAR(a, b, rel_tol_two); //fails because 0.1 * 0.6 = 0.06 < |a - b|
}
```

### EXPECT_NAN()
`EXPECT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is equivalent to `NAN` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(expect_nan) {
    float a = 5.0;

    EXPECT_NAN(a); //fails
}
```

### EXPECT_NOT_NAN()
`ASSERT_NOT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is not equivalent to `NAN` and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(expect_nan) {
    float a = 5.0;

    EXPECT_NOT_NAN(a); //passes
}
```

## Iterable Tests
Iterable tests are used for iterable containers, such as arrays, maps, sets, etc. They require that whatever types are within the containers to have `==` defined. Items in the passed in containers don't necessarily need to be the same type.

In order to be an iterable container, the passed in container needs to satisfy the `std::ranges::range` concept.

1. [Assert Ordered Equals](#assert_ordered_eq)
2. [Assert Unordered Equals](#assert_unordered_eq)
3. [Expect Ordered Equals](#expect_ordered_eq)
4. [Expect Unordered Equals](#expect_unordered_eq)

### ASSERT_ORDERED_EQ
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_ORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_ORDERED_EQ(a, c); // fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_ORDERED_EQ(d, e); //would pass

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    ASSERT_ORDERED_EQ(f, g); //would pass

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_ORDERED_EQ(h, i); //undefined behavior, but most likely would fail
}
```

### ASSERT_UNORDERED_EQ
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_UNORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_UNORDERED_EQ(a, c); // passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_UNORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    ASSERT_UNORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_UNORDERED_EQ(h, i); //passes, unlike ASSERT_ORDERED_EQ()

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    ASSERT_UNORDERED_EQ(j, k); //fails because there is a mismatch in counts on 1 and 3
}
```

### EXPECT_ORDERED_EQ
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts.

```
#include <tester/Tests.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_ORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_ORDERED_EQ(a, c); // fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_ORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_ORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_ORDERED_EQ(h, i); //undefined behavior, but most likely to fail
}
```

### EXPECT_UNORDERED_EQ
`EXPECT_UNORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. This test can take in any kind of container, ordered or unordered, in fact, when this test is used on ordered containers, its behavior is the same as `EXPECT_ORDERED_EQ()`. This test passes iff both containers have the same elements (as defined by `==`) and the same count of each element, regardless of indexing, and fails otherwise. This test will also automatically fail when given two containers with different item counts.

```
#include <tester/Tests.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_UNORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_UNORDERED_EQ(a, c); // passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_UNORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_UNORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_UNORDERED_EQ(h, i); //passes, unlike EXPECT_ORDERED_EQ()

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    EXPECT_UNORDERED_EQ(j, k); //fails because there is a mismatch in counts on 1 and 3
}
```

## Test Tests
Test tests are used to see if a test will pass/fail. Ie, these are tests to ensure that tests are working. It is very important that you do not pass in random functions. These tests also have the capability of defining new tests, in a sense. For instance, there is no `STRING_DOES_NOT_CONTAIN()` test, however, you could combine `ASSERT_STRING_CONTAINS()` with `ASSERT_FAILS()` to create one that would have a similar functionality to what an `ASSERT_STRING_DOES_NOT_CONTAIN()` test would have.

1. [Assert Passes](#assert_passes)
2. [Assert Fails](#assert_fails)
3. [Expect Passes](#expect_passes)
4. [Expect Fails](#expect_fails)

### ASSERT_PASSES()
`ASSERT_PASSES(test)` takes in one parameter, which is a test. It passes iff the passed in test passes, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(assert_passes) {
    ASSERT_PASSES(EXPECT_TRUE(true)); //passes
    ASSERT_PASSES(EXPECT_TRUE(false)); //fails
    ASSERT_PASSES(gonnaBreakThings()); //don't do this, but it would pass 

    //fails, but the nested ASSERT_TRUE failing DOES NOT terminate testing for the rest of the suite
    ASSERT_PASSES(ASSERT_TRUE(false)); 
}
```

### ASSERT_FAILS()
`EXPECT_FAILS(test)` takes in one parameter, which is a test. It passes iff the passed in test fails, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <tester/Tests.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(assert_fails) {
    ASSERT_FAILS(EXPECT_TRUE(true)); //fails
    ASSERT_FAILS(EXPECT_TRUE(false)); //would pass
    ASSERT_FAILS(gonnaBreakThings()); //don't do this, but it would fail
    ASSERT_FAILS(ASSERT_TRUE(true)); //fails
}
```

### EXPECT_PASSES()
`EXPECT_PASSES(test)` takes in one parameter, which is a test. It passes iff the passed in test passes, and fails otherwise.

```
#include <tester/Tests.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(expect_passes) {
    EXPECT_PASSES(EXPECT_TRUE(true)); //passes
    EXPECT_PASSES(EXPECT_TRUE(false)); //fails
    EXPECT_PASSES(gonnaBreakThings()); //don't do this, but it would pass 

    //fails, but ASSERT_TRUE failing DOES NOT terminate testing for the rest of the suite
    EXPECT_PASSES(ASSERT_TRUE(false)); 
}
```

### EXPECT_FAILS()
`EXPECT_FAILS(test)` takes in one parameter, which is a test. It passes iff the passed in test fails, and fails otherwise.

```
#include <tester/Tests.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(expect_fails) {
    EXPECT_FAILS(EXPECT_TRUE(true)); //fails
    EXPECT_FAILS(EXPECT_TRUE(false)); //passes
    EXPECT_FAILS(gonnaBreakThings()); //don't do this, but it would fail
    EXPECT_FAILS(ASSERT_TRUE(true)); 
}
```