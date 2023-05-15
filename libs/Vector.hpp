#pragma once

template<class T>
class Vector {
private:
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;
    using value_type = T;

    size_type m_size;
    iterator m_elements;

public:
    // Constructors / Destructors

    Vector()
        : m_size(0),
          m_elements(new T[0]) 
    {}

    explicit Vector(int size)
        : m_size(size),
          m_elements(new T[size])
    {}

    Vector(int size, int fill_element)
        : m_size(size),
          m_elements(new T[size]) {
        std::fill(m_elements, m_elements + m_size, fill_element);
    }

    Vector(std::initializer_list<T> elementList)
        : m_size(static_cast<int>(elementList.size())), 
          m_elements(new T[elementList.size()]) {
        std::copy(elementList.begin(), elementList.end(), m_elements);
    }

    Vector(Vector& v)
        : m_size(v.m_size) {
        std::copy(v.m_elements, v.m_size, m_elements);
    }

    Vector(Vector&& v) noexcept
        : m_size(v.m_size), m_elements(std::move(v.m_elements, v.m_size)) {
        v.m_size = 0;
    }

    ~Vector() {
        delete [] m_elements;
    }

    // Getters

    size_t size() const { return m_size; }

    T at(size_t index) const {
        try {
            if (index >= m_size) throw std::out_of_range("Index out of bounds");

            return m_elements[index];
        } catch (std::out_of_range& error) {
            std::cout << "Error: " << error.what() << std::endl;

            exit(1);
        }
    }

    // Setters

    // Operator overloads

    T operator[](size_t index) const {
        try {
            if (index >= m_size) throw std::out_of_range("Index out of bounds");

            return m_elements[index];
        } catch (std::out_of_range error) {
            std::cout << "Error: " << error.what() << std::endl;
            
            exit(1);
        }
    }

    // Friend functions

    friend std::ostream& operator<< (std::ostream& out, Vector<T>& obj) {
        for (size_t i = 0; i < obj.size(); i++) out << obj[i] << " ";

        return out;
    }
};