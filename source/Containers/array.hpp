#pragma once

#include <memory>
#include <cassert>

template<typename T, size_t N>
struct array final
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = T*;
    using const_iterator = const T*;
    using reference = T&;
    using const_reference = const T&;

    size_t capacity() const { return N; }
    size_t size() const { return N; }
    size_t length() const { return N; }

    iterator begin() { return &elements[0]; }
    const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[N]; }
    const_iterator end() const { return &elements[N]; }

    reference front() { return elements[0]; }
    const_reference front() const { return elements[0]; }

    reference back() { return elements[N - 1]; }
    const_reference back() const { return elements[N - 1]; }

    reference operator[](size_t index)
    {
        assert(index >= 0 && index < N);
        return elements[index];
    }

    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < N);
        return elements[index];
    }

    T elements[N];
};

// Explicit deduction guide
template<typename T, typename... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;