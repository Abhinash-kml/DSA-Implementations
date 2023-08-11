#pragma once

#include <cassert>
#include <memory>

template<typename T, typename U>
class vector;

size_t strlen(const char* str)
{
    size_t s{};

    while (*str != '\n')
    {
        s++;
        str++;
    }

    return s;
}

template<typename T>
class span final
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
    span(const T (&arr)[N])
        : m_ptr(arr)
        , m_size(N)
    {}

    span(const char* arr)
        : m_ptr(arr)
        , m_size(strlen(arr))
    {}

    span(const vector& arr)
        : m_ptr(arr.get())
        , m_size(arr.size())
    {}


public:
    const_reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return m_ptr[index];
    }


private:
    pointer m_ptr{nullptr};
    size_t m_size{0};
};