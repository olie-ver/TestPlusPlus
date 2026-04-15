# C++ Unit Tester V17.0.0 (Beta)
A C++ Unit Tester for C++17 written by Oliver Lie.

### License/Conditions of Usage
You may consider this code open-source to be downloaded, modified, and released for others under the condition that any other subsidiary code will keep these same conditions. This includes keeping the software free of charge.

## Adding To Your Projects

### Compiling And Linking
In order to add to your projects, you need the libtester.a library file. As a static library, it will need to be linked to in the compilation phase. A minimum working directory to compile and link the library is as follows: <br> 
Root <br> 
&emsp;/include <br>
&emsp;&emsp;/tester <br> 
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

### 