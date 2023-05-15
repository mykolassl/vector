#include <iostream>
#include "../libs/Vector.hpp"

// template<class T>
// class Vector {
// private:
//     int m_size;
//     T* m_elements;

// public:
//     Vector() : m_size(0), m_elements(new T[m_size]) {};
//     Vector(int size) : m_size(size), m_elements(new T[m_size] {}) {};
//     Vector(int size, T value) : m_size(size), m_elements(new T[m_size] { value }) {
//     };
//     ~Vector() {
//         delete [] m_elements;
//         std::cout << "Suveike destruktorius!" << std::endl;
//     }
//     void setElement(int id, T element) {};
//     T getElement(int id) {
//         try {
//             return m_elements[id];
//         } catch(...) {
//             std::cout << "Index out of bounds" << std::endl;
//         }
//     }

//     friend std::ostream& operator<< (std::ostream& out, Vector<T>& obj) {
//         if (obj.m_size == 0) return out;

//         for (int i = 0; i < obj.m_size; i++) {
//             out << obj.getElement(i) << " ";
//         }

//         // for (auto& i : obj.m_elements) out << i << " ";

//         return out;
//     }

//     // friend std::ostream& operator>> (std::ostream& in, Vector<T>& elements) {

//     // }
// };

int main() {
    Vector<int> pirmas;
    Vector<double> antras(5);
    Vector<int> trecias(7, 8);
    Vector<int> ketvirtas{1, 2, 3};
    
    std::cout << trecias[6] << " " << trecias[100];

    return 0;
}
