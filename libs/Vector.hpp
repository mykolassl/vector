#pragma once

template<class T>
class Vector {
public:
    // Type definitions

    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;
    using value_type = T;

    // Constructors / Destructors

    Vector()
        : m_size(0),
          m_capacity(0),
          m_elements(nullptr) {}

    explicit Vector(int size)
        : m_size(size),
          m_capacity(size),
          m_elements(new value_type[size]{}) {}

    Vector(int size, int fill_element)
        : m_size(size),
          m_capacity(size),
          m_elements(new value_type[size]) {
        std::fill(m_elements, m_elements + m_size, fill_element);
    }

    Vector(std::initializer_list<value_type> elementList)
        : m_size(static_cast<int>(elementList.size())),
          m_capacity(static_cast<int>(elementList.size())),
          m_elements(new value_type[elementList.size()]) {
        std::move(elementList.begin(), elementList.end(), m_elements);
    }

    Vector(Vector& v)
        : m_size(v.m_size),
          m_capacity(v.m_capacity),
          m_elements(new value_type[v.m_size]) {
        std::copy(v.m_elements, v.m_elements + v.m_size, m_elements);
    }

    Vector(Vector&& v) noexcept
        : m_size(v.m_size),
          m_capacity(v.m_capacity),
          m_elements(std::move(v.m_elements, v.m_elements + v.m_size)) {
        v.m_size = v.m_capacity = 0;
    }

    ~Vector() {
        m_size = m_capacity = 0;
        delete [] m_elements;
    }

    // Getters

    size_type size() const { return m_size; }

    size_type capacity() const { return m_capacity; }

    iterator begin() { return m_elements; }

    iterator end() { return m_elements + m_size; }

    const_iterator cbegin() const { return m_elements; }

    const_iterator cend() const { return m_elements + m_size; }

    value_type at(size_type index) const {
        try {
            if (index >= m_size) throw std::out_of_range("Index out of bounds");

            return m_elements[index];
        } catch (std::out_of_range& error) {
            std::cout << "Error: " << error.what() << std::endl;

            exit(1);
        }
    }

    // Setters

    void push_back(const value_type& element) {
//        if (m_capacity)
    }

    // Operator overloads

    value_type operator[](size_type index) const {
        try {
            if (index >= m_size) throw std::out_of_range("Index out of bounds");

            return m_elements[index];
        } catch (std::out_of_range& error) {
            std::cout << "Error: " << error.what() << std::endl;
            
            exit(1);
        }
    }

    Vector<value_type>& operator=(const Vector<value_type>& v) {
        m_size = v.m_size;
        m_capacity = v.m_capacity;
        std::copy(v.m_elements, v.m_elements + v.m_size, m_elements);
    }

    Vector<value_type>& operator=(Vector<value_type>&& v) noexcept {
        m_size = v.m_size;
        m_capacity = v.m_capacity;
        std::move(v.m_elements, v.m_elements + v.m_size, m_elements);
        v.m_size = v.m_capacity = 0;
    }

    // Friend functions

    friend std::ostream& operator<<(std::ostream& out, Vector<value_type>& v) {
        for (size_type i = 0; i < v.m_size; i++) out << v[i] << " ";

        return out;
    }

private:
    size_type m_size;
    size_type m_capacity;
    iterator m_elements;

};