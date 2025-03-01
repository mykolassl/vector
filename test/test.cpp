#include "gtest/gtest.h"
#include <cmath>
#include <Vector.h>

TEST(Vector, DefaultConstructor) {
    Vector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(Vector, SizeConstructor) {
    Vector<int> vec(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());
}

TEST(Vector, FillConstructor) {
    Vector<int> vec(10, 10);

    EXPECT_EQ(vec.size(), 10);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_FALSE(vec.empty());

    for (auto& it : vec) {
        EXPECT_EQ(it, 10);
    }
}

