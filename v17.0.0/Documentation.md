# C++ Unit Tester V17.0.0 (Beta)
A C++ Unit Tester for C++17 written by Oliver Lie. As a beta build/release, I make no guarantees that future versions will work the same, and implementations could change until the first working release.

### License/Conditions of Usage
You may consider this code open-source to be downloaded, modified, and released for others under the condition that any other subsidiary code will keep these same conditions. This includes keeping the software free of charge.

## Table Of Contents

1. [Adding To Your Projects](#adding-to-your-projects)
    1. [Compiling And Linking](#compiling-and-linking)
    2. [Include Inside Your Project](#include-inside-your-project)
    3. [CLI Usage](#cli-usage)
2. [Testing](#testing)
    1. [Registering Tests](#registering-tests)
    2. [Different Types Of Tests](#different-types-of-tests)
3. [Expects](#expects)
4. [Boolean Tests (Expects)](#boolean-tests-expects)
    1. [Expect True](#expect_true)
    2. [Expect False](#expect_false)
5. [Comparison Tests (Expects)](#comparison-tests-expects)
    1. [Expect Equal](#expect_eq)
    2. [Expect Not Equal](#expect_ne)
    3. [Expect Less Than](#expect_lt)
    4. [Expect Less Than Or Equal](#expect_le)
    5. [Expect Greater Than](#expect_gt)
    6. [Expect Greater Than Or Equal](#expect_ge)
6. [Float Tests (Expects)](#float-tests-expects)
    1. [Expect Relatively Near](#expect_rel_near)
    2. [Expect Absolutely Near](#expect_abs_near)
    3. [Expect Near](#expect_near)
    4. [Is NaN](#expect_nan)
    5. [Is Not NaN](#expect_not_nan)
7. [Null Tests (Expects)](#null-tests-expects)
    1. [Expect Null](#expect_null)
    2. [Expect Not Null](#expect_not_null)
8. [String Tests (Expects)](#string-tests-expects)
    1. [Expect String Equals](#expect_str_eq)
    2. [Expect String Not Equals](#expect_str_ne)
9. [Throws Tests (Expects)](#throws-tests-expects)
    1. [Expect Throws](#expect_throws)
    2. [Expect Does Not Throw](#expect_does_not_throw)

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
There are two different types of tests as of now: Asserts and Expects. Each kind of test have an Assert and an Expect counterpart. Asserts will terminate the program immediately upon failure, excluding logging and output, and Expects will record the failure but continue running until all tests have been completed or an Asserts fails. 

## Expects
Expects are tests that will evaluate the expression(s) being passed in and record any failures. Failures will not result in termination of the program, in other words, if you define tests using only Expects, it will run each test no matter how many failures occur. At the end of the test run, every passing/failure will be recorded.

## Boolean Tests (Expects)

### EXPECT_TRUE()
`EXPECT_TRUE()` takes in a condition that evaluates to a boolean value. It passes when passed in a condition that evaluates to true, and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_TRUE(1 == 1);

    int a = 5;
    int* b = &a;
    EXPECT_TRUE(a == *b);

    EXPECT_TRUE(true);
}
```

### EXPECT_FALSE()
`EXPECT_FALSE()` takes in a condition that evaluates to a boolean value. It passes when passed in a condition that evaluates to false, and fails otherwise.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_FALSE(100 == 1);

    int a = 5;
    int* b = &a;
    EXPECT_FALSE((a - 1) == *b);

    EXPECT_FALSE(false);
}
```

## Comparison Tests (Expects)

### EXPECT_EQ()
`EXPECT_EQ()` takes in any two values and passes iff they are equal to each other, as defined by the `==` operator, and fails otherwise. Ie, it evaluates the truthiness of `first == second`.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(example) {
    EXPECT_EQ(5, 5);

    std::vector v = {1, 2, 3, 4, 5};

    //int and std::vector have NOTHING to do with each other
    //but we can still use them as parameters to EXPECT_EQ()
    EXPECT_EQ(1, v);
    EXPECT_EQ(1, v.data());
}
```

### EXPECT_NE()
`EXPECT_NE()` takes in any two values and passes iff they are not equal to each other, as defined by the `==` operator, and fails otherwise. Ie, it evaluates the truthiness of `!(first == second)`.

```
#include <tester/Tests.hpp>
#include <vector>

D_TEST(example) {
    EXPECT_NE(5, 5.75);

    std::vector v = {1, 2, 3, 4, 5};
    std::vector k = {5};

    EXPECT_EQ(k, v);
    EXPECT_EQ(k.data(), v.data());
}
```

### EXPECT_LT()
`EXPECT_LT()` takes in any two values and passes when the first is strictly less than the other, as defined by the `<` operator, and fails otherwise. Ie, it evaluates the truthiness of `first < second`.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_LT(5, 5.75);

    int a = 5;
    int b = 6;
    int* a_adr = &a;
    int* b_adr = &b;
    EXPECT_LT(a_adr, b_adr);
}
```

### EXPECT_LE()
`EXPECT_LE()` takes in any two values and passes when the first is less than or equal to the other, as defined by the `<=` operator, and fails otherwise. Ie, it evaluates the truthiness of `first <= second`.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_LE(5, 5);

    int a = 5;
    int b = 6;
    EXPECT_LE(a, b);
    int* a_adr = &a;
    int* b_adr = &b;
    EXPECT_LE(a_adr, b_adr);
}
```

### EXPECT_GT()
`EXPECT_GT()` takes in any two values and passes when the first is strictly less than the other, as defined by the `>` operator, and fails otherwise. Ie, it evaluates the truthiness of `first > second`.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_GT(6, 5);

    int a = 5;
    int b = 6;
    EXPECT_GE(b, a);
    int* a_adr = &a;
    int* b_adr = &b;
    EXPECT_GE(b_adr, a_adr);
}
```

### EXPECT_GE()
`EXPECT_GE()` takes in any two values and passes when the first is strictly less than the other, as defined by the `>=` operator, and fails otherwise. Ie, it evaluates the truthiness of `first >= second`.

```
#include <tester/Tests.hpp>

D_TEST(example) {
    EXPECT_GE(5, 5);

    int a = 5;
    EXPECT_GE(a, a);
    int* a_adr = &a;
    EXPECT_LE(a_adr, a_adr);
}
```

## Float Tests (Expects)
All Float tests that take multiple parameters are capable of being used with mixed floating point types. Ie, it is valid to pass in a `float` and a `double` or some other combination of mixed floating point types. When this happens, each parameter will be cast to be the common type amongst the parameters. 

### EXPECT_REL_NEAR()
`EXPECT_REL_NEAR()` takes in three floating point values: two values and a relative tolerance. It then checks if `|first - second| <= |relativeTolerance| * max(first, second)`, verbally, it checks that the absolute value of the difference between the two values is less than or equal to the product of the relative tolerance and the larger of the two values. It passes iff the above condition is true and fails otherwise.

### EXPECT_ABS_NEAR()
`EXPECT_ABS_NEAR()` takes in three floating point values: two values and an absolute tolerance. It then checks if `|first - second| <= |absoluteTolerance|`. Verbally, if checks if the absolute value of the difference is less than or equal to the absolute value of the absolute tolerance. It passes iff this is true and fails otherwise.

### EXPECT_NEAR()
`EXPECT_NEAR()` takes in three or four floating values: two values, an absolute tolerance, and an optional parameter for a relative tolerance. In the case of a relative tolerance being missing, it will fall back onto checking absolute nearness [see above](#expect_abs_near). 
In the case that all four parameters are provided, it checks if `|first - second| <= max(|absoluteTolerance|, |relativeTolerance| * max(|first|, |second|))`. In other words, it computes the absolute difference of the first and second value and checks that it's less than or equal to the larger of the absolute values of the absolute and relative thresholds. Iff the above condition is satisfied, it passes, and fails otherwise. 

### EXPECT_NAN()
`EXPECT_NAN()` takes in a value and checks that it is equivalent to `NaN`. It passes if the passed in value is `NaN` and fails otherwise.

### EXPECT_NOT_NAN()
`EXPECT_NOT_NAN()` takes in a value and checks that it is not equivalent to `NaN`. It passes if the passed in value is not `NaN` and fails otherwise.

## Null Tests (Expects)

### EXPECT_NULL()
`EXPECT_NULL()` takes in a single value and checks if the passed in value is `nullptr`. It will pass iff it is and will fail otherwise.

### EXPECT_NOT_NULL()
`EXPECT_NOT_NULL()` takes in a single value and checks if the passed in value is `nullptr`. It will pass iff it is not and will fail otherwise.

## String Tests (Expects)
All string tests take in two parameters, which are "strings." Unlike the [float tests](#float-tests-expects), both parameters must be the same type. The allowed types to be passed in are: `std::string`, `char*`, and `char[]`. As of now, initializer lists of `char` and `char[]` are not allowed to be passed in.

### EXPECT_STR_EQ()
`EXPECT_STR_EQ()` takes in two parameters of the types defined [above](#string-tests-expects), and checks if they are equal. The test passes iff they are equal, and fails otherwise.

### EXPECT_STR_NE()
`EXPECT_STR_NE()` takes in two parameters of the types defined [above](#string-tests-expects), and checks if they are not equal. The test passes iff they are not equal, and fails otherwise.

## Throws Tests (Expects)
All Throws tests work best for debugging and printing with std::exception. This does not mean that you can't pass in an arbitrary type, it just means that there is no guarantee that the type can be printed. 

### EXPECT_THROWS()
`EXPECT_THROWS()` takes up to two arguments: a function, and an optional type that should be thrown. In the case that only a function is passed into the the macro, the test passes iff it throws at all and fails otherwise. In the case that you pass in the type of what should be thrown, the test passes iff that exact type is thrown and fails otherwise.

### EXPECT_DOES_NOT_THROW()
`EXPECT_DOES_NOT_THROW()` takes in only one argument, the function that should be called. It passes iff it does not throw any exception.