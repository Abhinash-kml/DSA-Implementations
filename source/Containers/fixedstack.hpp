#pragma once

#include <array>

template<typename T, size_t N>
class stack final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    stack() = default;

    stack(const stack& other) = default;
    stack& operator=(const stack& other) = default;
    stack(stack&& other) = default;
    stack& operator=(stack&& other) = default;
    ~stack() = default;

public:
    reference first() { return internal[0]; }
    const_reference first() const { return internal[0]; }

    reference last() { return internal[m_size - 1]; }
    const_reference last() const { return internal[m_size - 1]; }

    pointer begin() { return &internal[0]; }
    const_pointer begin() const { return &internal[0]; }

    pointer end() { return &internal[m_size]; }
    const_pointer end() const { return &internal[m_size]; }

    void push(const T& object)
    {
        if (m_size == N) return;
        internal[m_size++] = object;
    }

    void pop()
    {
        if (m_size == 0) return;
        internal[m_size--].~T();
    }

    const_reference get(size_t index)
    {
        assert(index >= 0 && index < m_size);
        return internal[index];
    }

    const_reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return internal[index];
    }

    size_t size() const { return m_size; }

private:
    T internal[N];
    size_t m_size{ 0 };
};