#pragma once

#include <memory>
#include <cassert>

#include "./string.hpp"
#include "../Allocators/allocator.hpp"

class string_view final
{
public:
    using value_type = char;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = char*;
    using const_pointer = const char*;
    using reference = char&;
    using const_reference = const char&;

    string_view() = default;

    template<typename T, typename A>
    string_view(const string<T, A>& other)
        : m_internal{ other.get() }
        , m_size{ other.size() }
    { }

    string_view(const char* str)
        : m_internal{ const_cast<char*>(str) }
        , m_size{ strlen(str) }
    { }

    template<size_t N>
    string_view(const char (&str)[N])
        : m_internal{ str }
        , m_size{ N }
    { }

    string_view(const string_view& other)
        : m_internal{ other.m_internal }
    { }

    string_view& operator=(const string_view& other)
    {
        if (&other == this) return *this;

        m_internal = other.m_internal;

        return *this;
    }

    string_view(string_view&& other)
        : m_internal{ other.m_internal }
    {
        other.m_internal = nullptr;
    }

    string_view& operator=(string_view&& other)
    {
        if (&other == this) return *this;

        m_internal = other.m_internal;
        other.m_internal = nullptr;

        return *this;
    }

    ~string_view()
    {
        m_internal = nullptr;
    }

public:

    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_internal[index];
    }

    size_t size() const { return m_size; }

private:
    pointer m_internal{ nullptr };
    size_t m_size{ 0 };
};