#pragma once

#include <memory>
#include <cassert>

template<typename T, size_t N>
struct array final
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    constexpr size_t size() const { return N; }
    constexpr size_t length() const { return N; }

    iterator begin() { return &elements[0]; }
    const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[N]; }
    const_iterator end() const { return &elements[N]; }

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

    // Iternal array
    T elements[N];
};

// Explicit deduction guides
template<typename T, typename... Types>
array(T, Types...) -> array<T, 1 + sizeof...(Types)>;