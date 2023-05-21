#pragma once

#include <compare>

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

    Vector(int size, value_type fill_element)
        : m_size(size),
          m_capacity(size),
          m_elements(new value_type[size]) {
        std::fill(m_elements, m_elements + m_size, fill_element);
    }

    Vector(iterator start, iterator end)
        : m_size(end-start),
          m_capacity(end-start),
          m_elements(new value_type[end-start]) {
        std::copy(start, end, m_elements);
    }

    Vector(std::initializer_list<value_type> element_list)
        : m_size(static_cast<int>(element_list.size())),
          m_capacity(static_cast<int>(element_list.size())),
          m_elements(new value_type[element_list.size()]) {
        std::move(element_list.begin(), element_list.end(), m_elements);
    }

    Vector(const Vector<value_type>& v)
        : m_size(v.m_size),
          m_capacity(v.m_capacity),
          m_elements(new value_type[v.m_size]) {
        std::copy(v.m_elements, v.m_elements + v.m_size, m_elements);
    }

    Vector(Vector<value_type>&& v) noexcept
        : m_size(v.m_size),
          m_capacity(v.m_capacity) {
        reallocate(m_capacity);
        std::move(v.m_elements, v.m_elements + v.m_size, m_elements);
        v.m_size = v.m_capacity = 0;
    }

    ~Vector() = default;

    // Getters

    [[nodiscard]] size_type size() const { return m_size; }

    [[nodiscard]] size_type capacity() const { return m_capacity; }

    iterator begin() { return m_elements; }

    iterator end() { return m_elements + m_size; }

    const_iterator cbegin() const { return m_elements; }

    const_iterator cend() const { return m_elements + m_size; }

    value_type front() const { return *m_elements; }

    value_type& front() { return *m_elements; }

    value_type back() const { return *(m_elements + m_size - 1); }

    value_type& back() { return *(m_elements + m_size - 1); }

    value_type at(size_type index) const {
        if (index >= m_size) throw std::out_of_range("Index out of vector bounds");
        return m_elements[index];
    }

    value_type& at(size_type index) {
        if (index >= m_size) throw std::out_of_range("Index out of vector bounds");
        return m_elements[index];
    }

    bool empty() { return m_elements == m_elements + m_size; }

    const_iterator data() const { return m_elements; }

    // Setters

    void push_back(const value_type& element) {
        if (m_size == m_capacity) reallocate();

        m_elements[m_size++] = element;
    }

    void push_back(value_type&& element) {
        if (m_size == m_capacity) reallocate();

        m_elements[m_size++] = std::move(element);
    }

    void reserve(const size_type& new_capacity) {
        if (new_capacity <= m_capacity || new_capacity <= 0) return;

        reallocate(new_capacity);
    }

    void resize(size_type size, const value_type& fill_element = value_type()) {
        if (size > m_capacity) {
            reallocate(size);
            std::fill(m_elements + m_size, m_elements + m_capacity, fill_element);
            m_size = size;
        } else if (size > m_size) {
            size_type old_size = m_size;
            m_size = size;
            std::fill(m_elements + old_size, m_elements + m_size, fill_element);
        } else {
            for (size_type i = size; i < m_size; i++) m_elements[i].~value_type();
            m_size = size;
        }
    }

    void shrink_to_fit() {
        for (int i = m_size - 1; i < m_capacity; i++) {
            m_elements[i].~value_type();
        }
        reallocate(m_size);
    }

    void clear() {
        for (size_type i = 0; i < m_size; i++) m_elements[i].~value_type();
        m_size = 0;
    }

    void assign(int size, value_type fill_element) {
        if (size > m_capacity) {
            reallocate(size);
            m_size = m_capacity;
        }

        m_size = size;
        std::fill(m_elements, m_elements + m_size, fill_element);
    }

    void assign(iterator start, iterator end) {
        size_type size = end - start;

        if (size > m_capacity || !m_elements) {
            reallocate(size);
            m_size = m_capacity;
        }

        m_size = size;
        std::copy(start, end, m_elements);
    }

    void assign(std::initializer_list<value_type>&& element_list) {
        if (element_list.size() > m_capacity) {
            reallocate(element_list.size());
        }

        m_size = element_list.size();
        std::move(element_list.begin(), element_list.end(), m_elements);
    }

    void insert(iterator position, value_type& element) {
        // Calculate the index in case vector is reallocated and
        // the position pointer is invalidated.
        size_type index = position - m_elements;
        if (m_size == m_capacity) reallocate();

        for (size_type i = m_size; i > index; i--) m_elements[i] = m_elements[i - 1];

        m_elements[index] = element;
        m_size++;
    }

    void insert(iterator position, value_type&& element) {
        // Calculate the index in case vector is reallocated and
        // the position pointer is invalidated.
        size_type index = position - m_elements;
        if (m_size == m_capacity) reallocate();

        for (size_type i = m_size; i > index; i--) m_elements[i] = m_elements[i - 1];

        m_elements[index] = std::move(element);
        m_size++;
    }

    void insert(iterator position, size_type size, value_type& element) {
        // Calculate the index in case vector is reallocated and
        // the position pointer is invalidated.
        size_type index = position - m_elements;
        if (m_size + size > m_capacity) reallocate(m_size + size);

        for (size_type i = m_size + size - 1; i > index; i--) {
            m_elements[i] = m_elements[i - size];
            if (i - size == 0) break;
        }

        std::fill(m_elements + index, m_elements + index + size, element);
        m_size += size;
    }

    void insert(iterator position, size_type size, value_type&& element) {
        // Calculate the index in case vector is reallocated and
        // the position pointer is invalidated.
        size_type index = position - m_elements;
        if (m_size + size > m_capacity) reallocate(m_size + size);

        for (size_type i = m_size + size - 1; i > index; i--) {
            m_elements[i] = m_elements[i - size];
            if (i - size == 0) break;
        }

        std::fill(m_elements + index, m_elements + index + size, element);
        m_size += size;
    }

    void insert(iterator position, iterator start, iterator end) {
        // Calculate the index in case vector is reallocated and
        // the position pointer is invalidated.
        size_type index = position - m_elements;
        size_type size = end - start;

        if (m_size + size > m_capacity) reallocate(m_size + size);

        for (size_type i = m_size + size - 1; i > index; i--) {
            m_elements[i] = m_elements[i - size];
            if (i - size == 0) break;
        }

        std::copy(start, end, m_elements + index);
        m_size += size;
    }

    void insert(iterator position, std::initializer_list<value_type>&& element_list) {
        size_type index = position - m_elements;
        size_type size = element_list.size();

        if (m_size + size > m_capacity) reallocate(m_size + size);

        for (size_type i = m_size + size - 1; i > index; i--) {
            m_elements[i] = m_elements[i - size];
            if (i - size == 0) break;
        }

        std::move(element_list.begin(), element_list.end(), m_elements + index);
        m_size += size;
    }

    template<class... Args>
    value_type& emplace(iterator position, Args&&... args) {
        size_type index = position - m_elements;

        if (m_size == m_capacity) reallocate();

        new (&m_elements[index]) value_type(std::forward<Args>(args)...);
        m_size++;

        return m_elements[index];
    }

    iterator erase(iterator position) {
        size_type index = position - m_elements;
        position->~value_type();
        for (size_type i = index; i < m_size; i++) m_elements[i] = m_elements[i + 1];

        m_size--;

        return position == end() ? end() : position;
    }

    iterator erase(iterator start, iterator end) {
        size_type index = start - m_elements;
        size_type size = end - start;

        for (iterator i = start; i != end; i++) i->~value_type();

        for (size_type i = index; i < m_size; i++) m_elements[i] = m_elements[i + size];

        auto oldEnd = m_elements + m_size;
        m_size -= size;

        if (end == oldEnd) {
            iterator newEnd = m_elements + m_size;
            return newEnd;
        } else if (end - start == 0) {
            return end;
        }

        return end + 1;
    }

    template<class... Args>
    value_type& emplace_back(Args&&... args) {
        if (m_size == m_capacity) reallocate();

        new (&m_elements[m_size]) value_type(std::forward<Args>(args)...);
        m_size++;

        return m_elements[m_size];
    }

    void pop_back() {
        if (m_size == 0) return;

        m_elements[--m_size].~value_type();
    }

    void swap(Vector<value_type>& v) {
        std::swap(m_elements, v.m_elements);
        std::swap(m_size, v.m_size);
        std::swap(m_capacity, v.m_capacity);
    }

    // Operator overloads

    value_type operator[](size_type index) const {
        if (index >= m_size) throw std::out_of_range("Index out of vector bounds");
        return m_elements[index];
    }

    Vector<value_type>& operator=(const Vector<value_type>& v) {
        if (&v == this) return *this;

        m_size = v.m_size;
        m_capacity = v.m_capacity;
        m_elements = new value_type[m_capacity];
        std::copy(v.m_elements, v.m_elements + v.m_size, m_elements);

        return *this;
    }

    Vector<value_type>& operator=(Vector<value_type>&& v) noexcept {
        if (&v == this) return *this;

        m_size = v.m_size;
        m_capacity = v.m_capacity;
        m_elements = new value_type[m_capacity];
        std::move(v.m_elements, v.m_elements + v.m_size, m_elements);
        v.m_size = v.m_capacity = 0;

        return *this;
    }

    // Friend functions

    friend std::ostream& operator<<(std::ostream& out, Vector<value_type>& v) {
        for (size_type i = 0; i < v.m_size; i++) out << v[i] << " ";

        return out;
    }

    auto operator<=> (const Vector<value_type>& v) const {
        return std::lexicographical_compare_three_way(cbegin(), cend(), v.cbegin(), v.cend());
    }

    bool operator== (const Vector<value_type>& v) const {
        for (int i = 0; i < v.m_size; i++) {
            if (v[i] != m_elements[i]) return false;
        }
        return true;
    }

private:
    size_type m_size;
    size_type m_capacity;
    iterator m_elements;

    void reallocate(const size_type& new_capacity = ((size_type) - 1)) noexcept {
        if (m_capacity == 0) {
            m_capacity = new_capacity == ((size_type) - 1) ? 2 : new_capacity;
            m_elements = new value_type[m_capacity];
        } else {
            if (new_capacity == ((size_type) - 1)) m_capacity *= 2;
            else m_capacity = new_capacity;

            iterator temporary = new value_type[new_capacity == ((size_type) - 1) ? m_capacity : new_capacity];
            std::move(m_elements, m_elements + m_size, temporary);
            delete [] m_elements;
            m_elements = temporary;
        }
    }
};