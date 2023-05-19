#include <iostream>
#include "../libs/Vector.hpp"
#include <chrono>
#include <vector>

class Entity {
public:
    Entity() {
        std::cout << "Constructor was called" << std::endl;
    }
};

int main() {
    // Constructors
    std::cout << "Constructor tests:" << std::endl;

    Vector<std::string> words1 { "123", "321", "213" };
    std::cout << words1 << std::endl;

    Vector<std::string> words2(words1.begin(), words1.end());
    std::cout << words2 << std::endl;

    Vector<std::string> words3(words1);
    std::cout << words3 << std::endl;

    Vector<std::string> words4(5, "Hello");
    std::cout << words4 << std::endl;

    // Assignments
    std::cout << "Assignment tests: " << std::endl;

    Vector<int> x { 1, 2, 3 }, y, z;
    const auto w = { 4, 5, 6, 7 };

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    y = x;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    z = std::move(x);
    std::cout << "x = " << x << std::endl;
    std::cout << "z = " << z << std::endl;

    z = w;
    std::cout << "w = ";
    for (auto i : w) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "z = " << z << std::endl;

    // Assign method
    Vector<char> characters;
    characters.assign(5, 'a');
    std::cout << characters << std::endl;

    Vector<char> extraCharacters(6, 'b');
    characters.assign(extraCharacters.begin(), extraCharacters.end());
    std::cout << characters << std::endl;

    characters.assign({'L', 'a', 'b', 'a', 's'});
    std::cout << characters << std::endl;

    // At method
    Vector<int> data = { 1, 2, 4, 5, 5, 6 };
    data.at(1) = 88;

    std::cout << "Element at index 2 has value " << data.at(2) << '\n';
    std::cout << "data size = " << data.size() << '\n';

    try {
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';
    }

    std::cout << data << std::endl;


    /*
    Vector<int> t5;
    t5.push_back(10);
    t5.push_back(20);
    t5.push_back(30);
    std::cout << "Size: " << t5.size() << ", capacity: " << t5.capacity() << std::endl;
    std::cout << t5 << " " << t5.front() << " " << t5.back() << std::endl;

    Vector<int> t6 = {5, 6, 7, 8, 9};
    std::cout << "Size: " << t6.size() << ", capacity: " << t6.capacity() << std::endl;
    Vector<int> t7 = t6;
    t7.push_back(500);
    std::cout << "Size: " << t7.size() << ", capacity: " << t7.capacity() << std::endl;
    std::cout << t6 << " " << t7 << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    Vector<int> test;
    for (int i = 0; i < 10000000; i++) {
        test.push_back(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << diff.count() / 1000.0 << std::endl;
    std::cout << test.capacity() << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    Vector<Entity> test2;
//    Entity e;
    for (int i = 0; i < 10000000; i++) {
//        test2.push_back(e);
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2);
    std::cout << diff2.count() / 1000.0 << std::endl;
    std::cout << test2.capacity() << '\n';

    Vector<int> p;
    std::cout << "Size: " << p.size() << ", capacity: " << p.capacity() << std::endl;
//    p.reserve(5);
    for (int i = 0; i < 300; i++) {
        p.push_back(i);
    }


//    p.reserve(6);
//    std::cout << p << std::endl;
    std::cout << "Size: " << p.size() << ", capacity: " << p.capacity() << std::endl;
    p.clear();
    std::cout << "Size: " << p.size() << ", capacity: " << p.capacity() << std::endl;
//    std::cout << p << std::endl;
    std::cout << "Is empty? " << p.empty() << std::endl;

    p.clear();

    for (int i = 0; i < 300; i++) std::cout << p[i] << " ";

    // Assign
//    std::vector<Entity> test4;
////    for (auto i : test4) { std::cout << i << " "; }
//    std::cout << std::endl;
//
//    test4.assign(5, Entity());
//
////    for (auto i : test4) { std::cout << i << " "; }
//    std::cout << std::endl;
//    std::cout << "Size: " << test4.size() << ", capacity: " << test4.capacity() << std::endl;
//
//    Vector<Entity> test5;
////    for (auto i : test5) { std::cout << i << " "; }
//    std::cout << std::endl;
//
////    test5.assign(5, Entity());
//
////    for (auto i : test5) { std::cout << i << " "; }
//    std::cout << std::endl;
//    std::cout << "Size: " << test5.size() << ", capacity: " << test5.capacity() << std::endl;
    */

    return 0;
}
