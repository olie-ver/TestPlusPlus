#include <tester/Tests.hpp>

#include <tester/Tests.hpp>

D_TEST(assert_rel_near) {
    float a = 5.0;
    double b = 6.0;
    long double rel_tol = 0.5;

    ASSERT_REL_NEAR(a, b, rel_tol); //passes

    long double rel_tol_two = 0.1;
    ASSERT_REL_NEAR(a, b, rel_tol_two); //passes
}