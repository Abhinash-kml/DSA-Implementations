#pragma once

#include <cassert>

template<typename T, size_t N>
struct array;

template<typename T>
class span
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    span() = default;

    template<size_t N>
    span(value_type (&arr)[N])
        : internal{ arr }
        , m_size{ N }
    { }

    template<size_t N>
    span(std::array<T, N>& arr)
        : internal{ arr.data() }
        , m_size{ N }
    { }

    span(const span& other) = default;
    span& operator=(const span& other) = default;
    span(span&& other) = delete;
    span& operator=(span&& other) = delete;
    ~span()
    {
        internal = nullptr;
    }

public:
    constexpr reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return internal[index];
    }

    constexpr const_reference operator[](size_t index) const 
    {
        assert(index >= 0 && index < m_size);
        return internal[index];
    }

    constexpr size_t size() const { return m_size; }
    constexpr pointer data() { return internal; }

    constexpr pointer begin() { return &internal[0]; }
    constexpr const_pointer begin() const { return &internal[0]; }

    constexpr pointer end() { return &internal[m_size]; }
    constexpr const_pointer end() const { return &internal[m_size]; }

    constexpr pointer rbegin() { return &internal[m_size - 1]; }
    constexpr const_pointer rbegin() const { return &internal[m_size - 1]; }

    constexpr pointer rend() { return &internal[-1]; }
    constexpr const_pointer rend() const { return &internal[-1]; }

    constexpr reference front() { return internal[0]; }
    constexpr const_reference front() const { return internal[0]; }

    constexpr reference back() { return internal[m_size - 1]; }
    constexpr const_reference back() const { return internal[m_size - 1]; }

private:
    pointer internal{ nullptr };
    size_t m_size{ 0 };
};