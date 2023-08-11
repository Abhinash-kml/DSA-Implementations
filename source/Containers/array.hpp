#pragma once

#include <memory>

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

    reference operator[](size_t index)
    {
        assert(index >= 0 && index < N);
        return m_arr[index];
    }

    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < N);
        return m_arr[index];
    }

    size_t size() const { return N; }

    pointer begin() { return &m_arr[0]; }
    const_pointer begin() const { return &m_arr[0]; }

    pointer end() { return &m_arr[N]; }
    const_pointer end() const { return &m_arr[N]; }

    pointer rbegin() { return &m_arr[N - 1]; }
    const_pointer rbegin() const { return &m_arr[N - 1]; }

    pointer rend() { return &m_arr[-1]; }
    const_pointer rend() const { return &m_arr[-1]; }

    T m_arr[N];
};

// Deduction guide for CTAD
template<typename T, typename... U>
array(T, U...) -> array<std::enable_if_t<(std::is_same_v<T, U> && ...), T>, sizeof...(U) + 1>;

// Helper functions
template<typename T, typename... Args>
array make_array(const T& a, Args&&... args)
{
    return array{a, std::forward<Args>(args)...};
}