#pragma once

#include <memory>
#include <utility>

template<typename T, typename A>
class string;

template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const string<T, A>& str)
{
    out << str.c_str();
    return out;
}

size_t strlen(const char* str)
{
    size_t size{};
    while (*str != '\0')
    {
        size++;
        str++;
    }

    return size;
}

template<typename charT = char, typename Allocator = std::allocator<charT>>
class string final
{
public:
    using value_type = charT;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = charT*;
    using const_pointer = const charT*;
    using reference = charT&;
    using const_reference = const charT&;

    string() = default;

    string(const char* str)
        : m_buffer(m_allocator.allocate(strlen(str) + 1))
        , m_size(strlen(str))
    {
        for (size_t i = 0; i < m_size; ++i)
            m_buffer[i] = str[i];

        m_buffer[m_size] = '\0';
    }

    template<size_t N>
    string(const char (&str)[N])
        : m_buffer(m_allocator.allocate(strlen(str) + 1))
        , m_size(N)
    {
        for (size_t i = 0; i < m_size; ++i)
            m_buffer[i] = str[i];

        m_buffer[m_size] = '\0';
    }

    string(const string& str)
        : m_allocator(str.m_allocator)
        , m_buffer(m_allocator.allocate(strlen(str) + 1))
        , m_size(strlen(str))

    {
        for (size_t i = 0; i < m_size; ++i)
            m_buffer[i] = str[i];

        m_buffer[m_size] = '\0';
    }

    string& operator=(const string& other)
    {
        if (&other == this) return *this;

        string temp{other};
        swap(*this, temp);

        return *this;
    }

    string(string&& str)
        : m_buffer(nullptr)
        , m_size(0)
    {
        swap(*this, str);
    }

    string& operator=(string&& str)
    {
        if (&str == this) return *this;

        m_allocator = std::swap(str.m_allocator);
        m_buffer = std::exchange(str.m_buffer, nullptr);
        m_size = std::exchange(str.m_size, 0);

        return *this;
    }

    ~string()
    {
        if (m_buffer) m_allocator.deallocate(m_buffer, m_size);
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

    const_pointer c_str() const { return m_buffer; }
    size_t size() const { return m_size; }

    void swap(string& other)
    {
        using std::swap;
        swap(m_buffer, other.m_buffer);
        swap(m_size, other.m_size);
        swap(m_allocator, other.m_allocator);
    }
private:
    Allocator m_allocator{};
    pointer m_buffer{nullptr};
    size_t m_size{0};
};