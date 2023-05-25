#include <memory>
using namespace std;

template<class T>
class Vector2 {
public:
    // Type definitions

    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;
    using value_type = T;

    Vector2() { create(); }

    explicit Vector2(size_type size, const T& fill_element = T{}) { create(size, fill_element); }

    Vector2(const Vector2& v) { create(v.begin(), v.end()); }

    Vector2& operator=(const Vector2& rhs) {
        if (&rhs == this) return;

        uncreate();
        create(rhs.begin(), rhs.end());
    }

    ~Vector2() { uncreate(); }

    iterator begin() { return data; }

    iterator end() { return limit; }

    const_iterator cbegin() const { return data; }

    const_iterator cend() const { return limit; }

    size_type size() const { return limit - data; }

    void push_back(const T& val) {

    }

    const value_type& operator[](size_type index) const { return data[index]; }

    value_type& operator[](size_type index) { return data[index]; }

private:
    iterator data;
    iterator limit;
};
