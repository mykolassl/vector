#include "gtest/gtest.h"

int main() {
    std::cout << "HELLO" << std::endl;
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}