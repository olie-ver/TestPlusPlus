#include <testpp/testpp.hpp>
#include <iostream>

TEST(asan, HeapOverflow) {
    int* arr = new int[4];
    arr[100] = 1;
    delete[] arr;
}