#include <iostream>
#include <vector>
#include "../libs/Vector.hpp"

class Entity {
public:
    Entity() {
        std::cout << "Constructor called!" << std::endl;
    }
};

int main() {
    Vector<int> t1 = {1, 2, 3};
    Vector<int> t2(t1);
    std::cout << t1 << " " << t2 << std::endl;

    Vector<int> t3(Vector<int>(10, 5));
    std::cout << t3 << std::endl;
    std::cout << "Size: " << t3.size() << ", capacity: " << t3.capacity() << std::endl;

    Vector<double> t4(5);
    std::cout << t4 << std::endl;
    std::cout << "Size: " << t4.size() << ", capacity: " << t4.capacity() << std::endl;

//    for (auto& itr : t3) {
//        std::cout << "Element " << itr << std::endl;
//    }

    std::vector v1 = {1};
    v1.push_back(2);
    v1.push_back(3);
    std::cout << "Size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;

    std::vector v2 = v1;
    std::cout << v2.size() << " " << v2.capacity() << '\n';

    return 0;
}
