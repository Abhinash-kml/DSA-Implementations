#pragma once

#include <cstring>
#include <memory>

template<typename T>
class allocator;

template<typename T = char, typename A = allocator<T>>
class string final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = char*;
    using const_pointer = const char*;
    using reference = char&;
    using const_reference = const char&;
    static const int32_t npos = -1;

    string() = default;

    string(const string& other)
        : m_buffer{ m_allocator.allocate(other.m_size) }
        , m_size{ other.m_size }
    { }

    string(const char* cstr)
        : m_buffer{ m_allocator.allocate(strlen(cstr) + 1) }
        , m_size{ strlen(cstr) + 1 }
    { 
        for (size_t i = 0; i < m_size; ++i)
            new (m_buffer + i) char(cstr[i]);
        
        m_buffer[m_size] = '\0';
    }

    template<size_t N>
    string(const char (&arr)[N])
        : m_buffer{ m_allocator.allocate(N + 1) }
        , m_size{ N }
    { 
        for (size_t i = 0; i < m_size; ++i)
            new (m_buffer + i) char(arr[i]);

        m_buffer[m_size] = '\0';
    }

    string& operator=(const string& other)
    {
        if (&other == this) return *this;

        string temp{other}; 
        temp.swap(*this);

        return *this;
    }

    string(string&& other)
        : m_buffer{ nullptr }
        , m_size{ 0 }
    {
        other.swap(*this);
    }

    string& operator=(string&& other)
    {
        if (&other == this) return *this;

        m_allocator.deallocate(m_buffer, m_size);
        m_size = 0;

        other.swap(*this);

        return *this;
    }

    ~string()
    {
        if (!m_size) return;

        m_allocator.deallocate(m_buffer, m_size);
        m_size = 0;
    }

public:
    reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return m_buffer[index];
    }

    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_buffer[index];
    }

    pointer begin() { return &m_buffer[0]; }
    const_pointer begin() const { return &m_buffer[0]; }

    pointer end() { return &m_buffer[m_size]; }
    const_pointer end() const { return &m_buffer[m_size]; }

    pointer rbegin() { return &m_buffer[m_size - 1]; }
    const_pointer rbegin() const { return &m_buffer[m_size - 1]; }

    pointer rend() { return &m_buffer[-1]; }
    const_pointer rend() const { return &m_buffer[-1]; }

    const_pointer cbegin() const { return &m_buffer[0]; }
    const_pointer cend() const { return &m_buffer[m_size]; }
    const_pointer crbegin() const { return &m_buffer[m_size - 1]; }
    const_pointer crend() const { return &m_buffer[-1]; }

    size_t size() const { return m_size; }
    size_t length() const { return m_size; }
    pointer get() { return m_buffer; }
    pointer get() const { return m_buffer; }
    pointer c_str() { return m_buffer; }

public:
    void swap(string& other)
    { 
        using std::swap;
        swap(m_buffer, other.m_buffer);
        swap(m_size, other.m_size);
        swap(m_allocator, other.m_allocator);
    }

private:
    pointer m_buffer{ nullptr };
    size_t m_size{ 0 };
    A m_allocator{ };
};