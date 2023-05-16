#include <iostream>
#include "../libs/Vector.hpp"

int main() {
    Vector<int> t5;
    t5.push_back(10);
    t5.push_back(20);
    t5.push_back(30);
    std::cout << t5 << " " << t5.front() << " " << t5.back() << std::endl;

    Vector<int> t6(5, 10);
    Vector<int> t7 = t6;
    std::cout << t6 << " " << t7 << std::endl;

    return 0;
}
