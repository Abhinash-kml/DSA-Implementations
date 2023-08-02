#pragma once

#include <memory>
#include <cassert>

template<typename T, size_t N>
class fstack final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    fstack() = default;
    fstack(const fstack& other) = default;
    fstack& operator=(const fstack& other) = default;
    fstack(fstack&& other) = default;
    fstack& operator=(fstack&& other) = default;
    ~fstack() = default;

    constexpr reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return m_elements[index];
    }

    constexpr const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_elements[index];
    }

public:

    template<typename... Args>
    constexpr void push(Args&&... args)
    {
        if (full()) return;

        new (m_elements + m_size) T(std::forward<Args>(args)...);
        m_size++;
    }

    constexpr void pop()
    {
        if (empty()) return;

        m_elements[--m_size].~T();
    }

    constexpr reference front() { return m_elements[0]; }
    constexpr const_reference front() const { return m_elements[0]; }

    constexpr reference back() { return m_elements[m_size - 1]; }
    constexpr const_reference back() const { return m_elements[m_size - 1]; }

    constexpr pointer begin() { return &m_elements[0]; }
    constexpr const_pointer begin() const { return &m_elements[0]; }

    constexpr pointer end() { return &m_elements[m_size]; }
    constexpr const_pointer end() const { return &m_elements[m_size]; }

    constexpr pointer rbegin() { return &m_elements[m_size - 1]; }
    constexpr const_pointer rbegin() const { return &m_elements[m_size - 1]; }

    constexpr pointer rend() { return &m_elements[-1]; }
    constexpr const_pointer rend() const { return &m_elements[-1]; }
 
    constexpr bool full() const { return m_size == N; }
    constexpr bool empty() const { return m_size == 0; }
    constexpr size_t size() const { return m_size; }
    constexpr size_t capacity() const { return N; }

private:
    T m_elements[N]{};
    size_t m_size{};
};