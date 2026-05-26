#include <tester/internal/Implementation/isolation/fatal.hpp>
#include <tester/Tests.hpp>

TEST(isolation, death) {
    internal::impl_iso::death([]{*(int*)nullptr = 5;});
}