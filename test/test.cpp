#include "gtest/gtest.h"
#include <Vector.h>

TEST(Vector, DefaultConstructor) {
    Vector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(Vector, SizeConstructor) {
    const size_t initial_size = 5;
    Vector<int> vec(initial_size);

    EXPECT_EQ(vec.size(), initial_size);
    EXPECT_EQ(vec.capacity(), initial_size);
    EXPECT_FALSE(vec.empty());
}

TEST(Vector, FillConstructor) {
    const size_t initial_size = 10;
    const int fill_element = 10;
    Vector<int> vec(initial_size, fill_element);

    EXPECT_EQ(vec.size(), initial_size);
    EXPECT_EQ(vec.capacity(), initial_size);
    EXPECT_FALSE(vec.empty());

    for (auto& it : vec) {
        EXPECT_EQ(it, fill_element);
    }
}

TEST(Vector, InitializerListConstructor) {
    Vector<int> vec = {1, 2, 3};

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 3);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(Vector, IteratorConstructor) {
    const size_t initial_size = 3;
    const int fill_element = 1;
    Vector<int> vec_1(initial_size, fill_element);
    Vector<int> vec_2(vec_1.begin(), vec_1.end());

    EXPECT_EQ(vec_2.size(), initial_size);
    EXPECT_EQ(vec_2.capacity(), initial_size);
    EXPECT_NE(vec_1.begin(), vec_2.begin());
    EXPECT_FALSE(vec_2.empty());

    for (auto& it : vec_2) {
        EXPECT_EQ(it, fill_element);
    }
}

TEST(Vector, CopyConstructor) {
    const size_t initial_size = 3;
    const int fill_element = 1;
    Vector<int> vec_1(initial_size, fill_element);
    Vector<int> vec_2(vec_1);

    EXPECT_EQ(vec_2.size(), initial_size);
    EXPECT_EQ(vec_2.capacity(), initial_size);
    EXPECT_NE(vec_1.begin(), vec_2.begin());
    EXPECT_FALSE(vec_2.empty());

    for (auto& it : vec_2) {
        EXPECT_EQ(it, fill_element);
    }

    vec_1[0] = 60;

    EXPECT_NE(vec_1[0], vec_2[0]);
}

TEST(Vector, MoveConstructor) {
    Vector<int> vec_1(3, 1);
    Vector<int> vec_2(std::move(vec_1));

    EXPECT_EQ(vec_2.size(), 3);
    EXPECT_EQ(vec_2.capacity(), 3);
    EXPECT_FALSE(vec_2.empty());

    EXPECT_EQ(vec_1.size(), 0);
    EXPECT_EQ(vec_1.capacity(), 0);

    for (auto& it : vec_2) {
        EXPECT_EQ(it, 1);
    }
}

TEST(Vector, AtBounds) {
    Vector<int> vec = {1, 2, 3};

    EXPECT_NO_THROW({
        const int index = 1;
        int value_1 = vec.at(index);
        EXPECT_EQ(value_1, 2);
        value_1 = 10;
        EXPECT_NE(vec.at(index), 10);
    });

    EXPECT_NO_THROW({
        const int index = 2;
        int& value_2 = vec.at(index);
        EXPECT_EQ(value_2, 3);

        value_2 = 10;
        EXPECT_EQ(vec.at(index), 10);
    });

    EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(Vector, DataAccess) {
    Vector<int> vec = {1, 2, 3};

    EXPECT_EQ(vec.data(), &vec[0]);
}

TEST(Vector, PushBack) {
    Vector<int> vec;

    vec.push_back(89);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.capacity(), 2);

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.capacity(), 2);

    vec.push_back(21);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_EQ(vec.front(), 89);
    EXPECT_EQ(vec.back(), 21);
}

TEST(Vector, CompareOverload) {
    Vector<int> vec_1 = {1, 2, 3};
    Vector<int> vec_2 = {1, 2, 3};

    EXPECT_TRUE(vec_1 == vec_2);

    vec_1[0] = 75;

    EXPECT_FALSE(vec_1 == vec_2);
    EXPECT_TRUE(vec_1 > vec_2);
    EXPECT_TRUE(vec_2 < vec_1);
}

TEST(Vector, OutputStream) {
    Vector<int> vec = {1, 2, 3};
    std::stringstream stream;

    stream << vec;

    EXPECT_EQ(stream.str(), "1 2 3 ");
}

TEST(Vector, Swap) {
    Vector<int> vec_1 = {10, 20, 30, 40, 50};
    const size_t vec_1_initial_size = vec_1.size();
    const size_t vec_1_initial_cap = vec_1.capacity();

    Vector<int> vec_2 = {1, 2, 3};
    const size_t vec_2_initial_size = vec_2.size();
    const size_t vec_2_initial_cap = vec_2.capacity();

    vec_1.swap(vec_2);

    EXPECT_EQ(vec_1.size(), vec_2_initial_size);
    EXPECT_EQ(vec_1.capacity(), vec_2_initial_cap);
    EXPECT_EQ(vec_1[0], 1);

    EXPECT_EQ(vec_2.size(), vec_1_initial_size);
    EXPECT_EQ(vec_2.capacity(), vec_1_initial_cap);
    EXPECT_EQ(vec_2[0], 10);
}

TEST(Vector, Reserve) {
    const size_t initial_cap = 10;
    Vector<int> vec;
    vec.reserve(initial_cap);

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), initial_cap);

    vec.push_back(56);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.capacity(), initial_cap);
}

TEST(Vector, ResizeIncrease) {
    const size_t initial_size = 5;
    const int fill_element = 10;
    Vector<int> vec;
    vec.resize(initial_size, fill_element);

    EXPECT_EQ(vec.size(), initial_size);
    EXPECT_EQ(vec.capacity(), initial_size);
    EXPECT_EQ(vec.front(), fill_element);
    EXPECT_EQ(vec.back(), fill_element);
}

TEST(Vector, ResizeDecrease) {
    const size_t initial_size = 5;
    const int fill_element = 10;
    Vector<int> vec;
    vec.resize(initial_size, fill_element);

    const size_t new_size = 3;
    vec.resize(new_size);

    EXPECT_EQ(vec.size(), new_size);
    EXPECT_EQ(vec.capacity(), initial_size);
    EXPECT_EQ(vec.front(), fill_element);
    EXPECT_EQ(vec.back(), fill_element);
}

TEST(Vector, ShrinkUnchanged) {
    const size_t initial_size = 10;
    const int fill_element = 8736;
    Vector<int> vec(initial_size, fill_element);
    vec.shrink_to_fit();

    EXPECT_EQ(vec.size(), initial_size);
    EXPECT_EQ(vec.capacity(), initial_size);
}

TEST(Vector, ShrinkToFit) {
    const size_t initial_size = 10;
    const int fill_element = 8736;
    const int pop_cnt = 1;
    Vector<int> vec(initial_size, fill_element);

    for (int i = 0; i < pop_cnt; i++) {
        vec.pop_back();
    }

    EXPECT_EQ(vec.size(), initial_size - pop_cnt);
    EXPECT_EQ(vec.capacity(), initial_size);

    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), initial_size - pop_cnt);
    EXPECT_EQ(vec.capacity(), initial_size - pop_cnt);
}

TEST(Vector, Clear) {
    const size_t initial_size = 10;
    const int fill_element = 7;
    Vector<int> vec(initial_size, fill_element);
    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), initial_size);
}

TEST(Vector, Insert) {
    Vector<int> vec = {1, 5};
    vec.insert(&vec[1], {2, 3, 4});

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 5);
}
