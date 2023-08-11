#pragma once

#include <string>
#include <memory>
#include <utility>
#include <cassert>

size_t strlen(const char* str)
{
    size_t size = 0;

    while (*str != '\n')
    {
        size++;
        str++;
    }

    return size;
}

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

    string_view(const std::string& str)
        : m_ptr(str.c_str())
        , m_size(str.size())
    {}

    string_view(const char* str)
        : m_ptr(str)
        , m_size(strlen(str))
    {}

    string_view(const string_view& str) = default;
    string_view& operator=(const string_view& other) = default;

    string_view(string_view&& other)
        : m_ptr(std::move(other.m_ptr))
        , m_size(std::move(other.m_size))
    {}

    string_view& operator=(string_view&& other)
    {
        if (&other == this) return *this;

        m_ptr = std::exchange(other.m_ptr, nullptr);
        m_size = std::exchange(other.m_size, 0);
    }

    ~string_view()
    {
        if (m_ptr) m_ptr = nullptr;
        m_size = 0;
    }

public:
    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_ptr[index];
    }

    const_reference at(size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_ptr[index];
    }

    const_reference front() const { return m_ptr[0]; }
    const_reference back() const { return m_ptr[m_size]; }

    size_t size() const { return m_size; }

    const_pointer begin() const { return &m_ptr[0]; }
    const_pointer cbegin() const { return &m_ptr[0]; }

    const_pointer end() const { return &m_ptr[m_size]; }
    const_pointer cend() const { return &m_ptr[m_size]; }

private:
    const char* m_ptr{nullptr};
    size_t m_size{0};
};