#pragma once

#include <memory>
#include <cassert>

template<typename T, size_t N>
struct array final
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using this_type = array<T, N>;

    // Iterators
    pointer begin() { return &elements[0]; }
    const_pointer begin() const  { return &elements[0]; }

    pointer end() { return &elements[N]; }
    const_pointer end() const { return &elements[N]; }

    pointer rbegin() { return &elements[N - 1]; }
    const_pointer rbegin() const { return &elements[N - 1]; }

    pointer rend() { return &elements[-1]; }
    const_pointer rend() const { return &elements[-1]; }

    const_pointer cbegin() const { return &elements[0]; }
    const_pointer cend() const { return &elements[N]; }
    const_pointer crbegin() const { return &elements[N - 1]; }
    const_pointer crend() const { return &elements[-1]; }

    size_t size() const { return N; }
    size_t length() const { return N; }

    // Subscript operator overloads
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

    // Internal array
    T elements[N];
};

// Explicit type deduction
template<typename T, typename... U>
array(T, U...) -> array<std::enable_if_t<(std::is_same_v<T, U> && ...), T>, 1 + sizeof...(U)>;

template<typename T, typename... Args>
auto make_array(T&& a, Args&&... args)
{
    return array<T, 1 + sizeof...(args)>{a, args...};
}