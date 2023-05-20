#include <iostream>
#include "../libs/Vector.hpp"
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

class Entity {
public:
    Entity() {
        std::cout << "Constructor was called" << std::endl;
    }

    ~Entity() {
        std::cout << "Destructor was called" << std::endl;
    }
};

void pointer_func(const int* p, size_t size) {
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << std::endl;
}

int main() {
    // Constructors
    std::cout << std::endl << "Constructor tests:" << std::endl;

    Vector<std::string> words1 { "123", "321", "213" };
    std::cout << words1 << std::endl;

    Vector<std::string> words2(words1.begin(), words1.end());
    std::cout << words2 << std::endl;

    Vector<std::string> words3(words1);
    std::cout << words3 << std::endl;

    Vector<std::string> words4(5, "Hello");
    std::cout << words4 << std::endl;

    // Assignments
    std::cout << std::endl << "Assignment tests: " << std::endl;

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
    std::cout << std::endl << "Assign method tests:" << std::endl;

    Vector<char> characters;
    characters.assign(5, 'a');
    std::cout << characters << std::endl;

    Vector<char> extraCharacters(6, 'b');
    characters.assign(extraCharacters.begin(), extraCharacters.end());
    std::cout << characters << std::endl;

    characters.assign({'L', 'a', 'b', 'a', 's'});
    std::cout << characters << std::endl;

    // At method
    std::cout << std::endl << "At method tests:" << std::endl;

    Vector<int> data = { 1, 2, 4, 5, 5, 6 };
    data.at(1) = 88;

    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;

    try {
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << std::endl;
    }

    std::cout << data << std::endl;

    // Front and back methods
    std::cout << std::endl << "Front and back method tests:" << std::endl;

    Vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};
    if (!letters.empty()) {
        std::cout << "The first letter is " << letters.front() << std::endl;
        std::cout << "The last letter is " << letters.back() << std::endl;
    }

    // Data method
    std::cout << std::endl << "Data method tests:" << std::endl;

    Vector<int> container {1, 2, 3, 4};
    pointer_func(container.data(), container.size());

    // Begin and end methods
    std::cout << std::endl << "Begin and end method tests:" << std::endl;

    Vector<int> nums {1, 2, 4, 8, 16};
    Vector<std::string> fruits {"orange", "apple", "raspberry"};
    Vector<char> empty;

    std::for_each(nums.begin(), nums.end(), [](const int n) { std::cout << n << ' '; });
    std::cout << std::endl;

    std::cout << "Sum of nums: " << std::accumulate(nums.begin(), nums.end(), 0) << std::endl;

    if (!fruits.empty()) std::cout << "First fruit: " << *fruits.begin() << std::endl;

    if (empty.begin() == empty.end()) std::cout << "vector 'empty' is indeed empty." << std::endl;

    // Empty method
    std::cout << std::endl << "Empty method tests:" << std::endl << std::boolalpha;

    Vector<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;

    numbers.push_back(42);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;

    // Size method
    std::cout << std::endl << "Size and max_size method tests:" << std::endl;

    Vector<int> ns {1, 3, 5, 7};

    std::cout << "'ns' contains " << ns.size() << " elements." << std::endl;

    // Reserve method
    std::cout << std::endl << "Reserve method tests:" << std::endl;

    const int maxElements = 32;
    {
        int reallocationCount = 0;
        Vector<int> v1;
        v1.reserve(maxElements);

        for (int i = 0; i < maxElements; i++) {
            if (v1.size() == v1.capacity()) reallocationCount++;
            v1.push_back(i);
        }
        std::cout << v1 << std::endl;

        std::cout << "Vector memory was reallocated " << reallocationCount << " times (reserve was used)." << std::endl;
    }
    {
        int reallocationCount = 0;
        Vector<int> v1;

        for (int i = 0; i < maxElements; i++) {
            if (v1.size() == v1.capacity()) reallocationCount++;
            v1.push_back(i);
        }
        std::cout << v1 << std::endl;

        std::cout << "Vector memory was reallocated " << reallocationCount << " times (reserve wasn't used)." << std::endl;
    }

    // Capacity method
    std::cout << std::endl << "Capacity method tests:" << std::endl;

    int sz = 100;
    Vector<int> v;

    auto cap = v.capacity();
    std::cout << "Initial size: " << v.size() << ", capacity: " << cap << '\n';

    std::cout << "\nDemonstrate the capacity's growth policy."
                 "\nSize:  Capacity:  Ratio:\n" << std::left;
    while (sz-- > 0) {
        v.push_back(sz);
        if (cap != v.capacity()) {
            std::cout << std::setw( 7) << v.size()
                      << std::setw(11) << v.capacity()
                      << std::setw(10) << v.capacity() / static_cast<float>(cap) << '\n';
            cap = v.capacity();
        }
    }

    std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';

    // Shrink_to_fit method
    std::cout << std::endl << "Shrink_to_fit method tests:" << std::endl;

    Vector<int> v1;
    std::cout << "Default-constructed capacity is " << v1.capacity() << '\n';
    v1.resize(100);
    std::cout << "Capacity of a 100-element vector is " << v1.capacity() << '\n';
    v1.resize(50);
    std::cout << "Capacity after resize(50) is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';
    v1.clear();
    std::cout << "Capacity after clear() is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';
    for (int i = 1000; i < 1300; ++i) v1.push_back(i);
    std::cout << "Capacity after adding 300 elements is " << v1.capacity() << '\n';
    v1.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v1.capacity() << '\n';

    // Clear method
    std::cout << std::endl << "Clear method tests:" << std::endl;

    Vector<int> v3{1, 2, 3};

    std::cout << "Before clear: ";
    std::cout << v3;
    std::cout << "\nSize=" << v3.size() << ", Capacity=" << v3.capacity() << '\n';

    std::cout << "Clear\n";
    v3.clear();

    std::cout << "After clear:";
    std::cout << v3;
    std::cout << "\nSize=" << v3.size() << ", Capacity=" << v3.capacity() << '\n';

    // Insert method
    std::cout << std::endl << "Insert method tests:" << std::endl;

    Vector<int> c1(3, 100);
    std::cout << c1 << std::endl;

    c1.insert(c1.begin(), 200);
    std::cout << c1 << std::endl;

    c1.insert(c1.begin(), 2, 300);
    std::cout << c1 << std::endl;

    Vector<int> c2(2, 400);
    c1.insert(c1.begin() + 2, c2.begin(), c2.end());
    std::cout << c1 << std::endl;

    int arr[] = {501, 502, 503};
    c1.insert(c1.begin(), arr, arr + std::size(arr));
    std::cout << c1 << std::endl;

    c1.insert(c1.end(), {601, 602, 603});
    std::cout << c1 << std::endl;

    return 0;
}
